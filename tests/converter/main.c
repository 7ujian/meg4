/*
 * meg4/tests/converter/main.c
 *
 * Copyright (C) 2023 bzt
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * @brief Tests MEG-4 import/export capabilities
 *
 */

#define _POSIX_C_SOURCE 199309L    /* needed for timespec and nanosleep() */
#include <stdio.h>
#include "../../src/meg4.h"
#include "editors.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_WRITE_ONLY_PNG
#define STBI_WRITE_NO_FAILURE_STRINGS
#define STBI_WRITE_NO_SIMD
#define STBI_WRITE_NO_STDIO
#define STBIW_ASSERT(x)
#include "../../src/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_NO_FAILURE_STRINGS
#define STBI_NO_SIMD
#define STBI_NO_STDIO
#define STBI_ASSERT(x)
#include "../../src/stb_image.h"
#include "../../src/floppy.h"

meg4_t meg4;
uint8_t *meg4_font = NULL, *meg4_defwaves = NULL, *meg4_init = NULL;
uint32_t meg4_init_len = 0;
char meg4_title[64], meg4_author[64], meg4_pro = 0;
void meg4_switchmode(int mode) { (void)mode; }
void meg4_recalcmipmap(void) { }
int  gpio_init(uint8_t *buf, int len) { (void)buf; (void)len; return 0; }
void meg4_recalcfont(int s, int e)
{
    uint8_t *fnt = meg4.font + 8 * s, *ptr = meg4.font + 8 * 65536 + s;
    int i, x, y, l, r;

    if(s < 0 || s > 0xffff || e < 0 || e > 0xffff || e < s) return;
    memset(ptr, 0, e - s + 1);
    for(i = s; i <= e; i++, fnt += 8, ptr++) {
        if(i == 32 || i == 160) { *ptr = 0x30; continue; }
        for(l = 7, r = y = 0; y < 8; y++)
            for(x = 0; x < 8; x++)
                if(fnt[y] & (1 << x)) {
                    if(l > x) l = x;
                    if(r < x) r = x;
                }
        if(l > r) l = r;
        *ptr = (r << 4) | l;
    }
}

uint8_t meg4_palidx(uint8_t *rgba)
{
    uint8_t ret = 0, *b;
    int i, dr, dg, db, d, dm = 0x7fffffff;

    for(i = 0; i < 256 && dm > 0; i++) {
        b = (uint8_t*)&meg4.mmio.palette[i];
        if(rgba[0] == b[0] && rgba[1] == b[1] && rgba[2] == b[2]) return i;
        db = rgba[2] > b[2] ? rgba[2] - b[2] : b[2] - rgba[2];
        dg = rgba[1] > b[1] ? rgba[1] - b[1] : b[1] - rgba[1];
        dr = rgba[0] > b[0] ? rgba[0] - b[0] : b[0] - rgba[0];
        d = ((dr*dr) << 1) + (db*db) + ((dg*dg) << 2);
        if(d < dm) { dm = d; ret = i; }
    }
    return ret;
}
char *meg4_utf8(char *str, uint32_t *out)
{
    if((*str & 128) != 0) {
        if(!(*str & 32)) { *out = ((*str & 0x1F)<<6)|(*(str+1) & 0x3F); str += 1; } else
        if(!(*str & 16)) { *out = ((*str & 0xF)<<12)|((*(str+1) & 0x3F)<<6)|(*(str+2) & 0x3F); str += 2; } else
        if(!(*str & 8)) { *out = ((*str & 0x7)<<18)|((*(str+1) & 0x3F)<<12)|((*(str+2) & 0x3F)<<6)|(*(str+3) & 0x3F); str += 3; }
        else *out = 0;
    } else *out = *str;
    return str + 1;
}

void sound_addwave(int wave) { (void)wave; }
void code_init(void) { }
int overlay_idx = 0;

int main_cfgsave(char *cfg, uint8_t *buf, int len) { (void)cfg; (void)buf; (void)len; return 1; }

uint8_t* main_readfile(char *file, int *size)
{
    uint8_t *data = NULL;
    FILE *f;

    if(!file || !*file || !size) return NULL;
    *size = 0;
    f = fopen(file, "rb");
    if(f) {
        fseek(f, 0L, SEEK_END);
        *size = (int)ftell(f);
        fseek(f, 0L, SEEK_SET);
        data = (uint8_t*)malloc(*size);
        if(data) {
            memset(data, 0, *size);
            if((int)fread(data, 1, *size, f) != *size) { free(data); data = NULL; *size = 0; }
        }
        fclose(f);
    }
    return data;
}

int main_writefile(char *file, uint8_t *buf, int size)
{
    int ret = 0;
    FILE *f;

    if(!file || !*file || !buf || size < 1) return 0;
    f = fopen(file, "wb");
    if(f) {
        ret = ((int)fwrite(buf, 1, size, f) == size);
        fclose(f);
    }
    return ret;
}
int main_savefile(const char *name, uint8_t *buf, int len) { return main_writefile((char*)name, buf, len); }

/**
 * Log messages
 */
void main_log(int lvl, const char* fmt, ...)
{
    __builtin_va_list args;
    __builtin_va_start(args, fmt);
    (void)lvl;
    printf("meg4: "); vprintf(fmt, args); printf("\r\n");
    __builtin_va_end(args);
}

/**
 * Import files
 */
int main_import(char *name, uint8_t *buf, int len)
{
    uint32_t s;
    uint8_t *end = buf + len - 12, *floppy = NULL;

    if(!buf) return 0;
    if(!memcmp(buf, "\x89PNG", 4) && ((buf[18] << 8) | buf[19]) == 210 && ((buf[22] << 8) | buf[23]) == 220) {
        for(buf += 8; buf < end; buf += s + 12) {
            s = ((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
            if(!memcmp(buf + 4, "flPy", 4) && stbiw__crc32(buf + 4, s + 4) == (uint32_t)((buf[8+s]<<24)|(buf[9+s]<<16)|(buf[10+s]<<8)|buf[11+s])) {
                floppy = (uint8_t*)stbi_zlib_decode_malloc_guesssize_headerflag((const char *)buf + 8, s, 65536, &len, 1);
                break;
            }
        }
        if(!floppy) return 0;
        s = meg4_deserialize(floppy, len);
        free(floppy);
        return s;
    } else
        return meg4_import(name, buf, len, 0);
}

/**
 * Initialize stuff because we haven't turn on the MEG-4
 */
void main_init(char *fn)
{
    char *v = MEG4_VERSION;
    int c, i, j, k, l, m, n, s;
    uint8_t *font, *ptr, *frg, *buf, *o;

    memset(&meg4, 0, sizeof(meg4));
    meg4.mmio.fwver[0] = atoi(v); while(*v != '.') { v++; } v++;
    meg4.mmio.fwver[1] = atoi(v); while(*v != '.') { v++; } v++;
    meg4.mmio.fwver[2] = atoi(v);
    memcpy(meg4.mmio.palette, default_pal, sizeof(meg4.mmio.palette));
    if((v = strrchr(fn, '/')) || (v = strrchr(fn, '\\'))) v++; else v = fn;
    strncpy(meg4_title, v, sizeof(meg4_title) - 1);
    if((v = strrchr(meg4_title, '.'))) *v = 0;
    /* just in case, if someone wants to import MIDI files */
    meg4_defwaves = (uint8_t*)stbi_zlib_decode_malloc_guesssize_headerflag((const char *)binary_sounds_mod, sizeof(binary_sounds_mod), 65536, &i, 1);
    /* uncompress and set default font */
    meg4_font = (uint8_t*)malloc(9 * 65536);
    if(meg4_font) {
        memset(meg4_font, 0, 9 * 65536);
        ptr = (uint8_t*)binary_default_sfn + 3;
        i = *ptr++; ptr += 6; if(i & 4) { k = *ptr++; k += (*ptr++ << 8); ptr += k; } if(i & 8) { while(*ptr++ != 0); }
        if(i & 16) { while(*ptr++ != 0); } j = sizeof(binary_default_sfn) - (size_t)(ptr - binary_default_sfn);
        font = (uint8_t*)stbi_zlib_decode_malloc_guesssize_headerflag((const char*)ptr, j, 65536, &s, 0);
        if(font) {
            for(buf = font + le32toh(*((uint32_t*)(font + 16))), c = 0; c < 0x010000 && buf < font + s; c++) {
                if(buf[0] == 0xFF) { c += 65535; buf++; } else
                if((buf[0] & 0xC0) == 0xC0) { j = (((buf[0] & 0x3F) << 8) | buf[1]); c += j; buf += 2; } else
                if((buf[0] & 0xC0) == 0x80) { j = (buf[0] & 0x3F); c += j; buf++; } else {
                    ptr = buf + 6; o = meg4_font + c * 8;
                    for(i = n = 0; i < buf[1]; i++, ptr += buf[0] & 0x40 ? 6 : 5) {
                        if(ptr[0] == 255 && ptr[1] == 255) continue;
                        frg = font + (buf[0] & 0x40 ? ((ptr[5] << 24) | (ptr[4] << 16) | (ptr[3] << 8) | ptr[2]) :
                            ((ptr[4] << 16) | (ptr[3] << 8) | ptr[2]));
                        if((frg[0] & 0xE0) != 0x80) continue;
                        o += (int)(ptr[1] - n); n = ptr[1]; k = ((frg[0] & 0x0F) + 1) << 3; j = frg[1] + 1; frg += 2;
                        for(m = 1; j; j--, n++, o++)
                            for(l = 0; l < k; l++, m <<= 1) {
                                if(m > 0x80) { frg++; m = 1; }
                                if(*frg & m) *o |= m;
                            }
                    }
                    buf += 6 + buf[1] * (buf[0] & 0x40 ? 6 : 5);
                }
            }
            free(font);
        }
        memcpy(meg4.font, meg4_font, 8 * 65536);
        meg4_recalcfont(0, 0xffff);
        memcpy(meg4_font + 8 * 65536, meg4.font + 8 * 65536, 65536);
        /* clear control codes */
        memset(meg4.font, 0, 8 * 32);
        memset(meg4.font + 8 * 65536, 0, 32);
        memset(meg4.font + 8 * 128, 0, 8 * 32);
        memset(meg4.font + 8 * 65536 + 128, 0, 32);
    }
}

/**
 * Main function
 */
int main(int argc, char **argv)
{
    uint8_t *buf;
    int len, isbinary = 0, i = 1;

    /* load input */
    if(argc < 1 || !argv[1]) {
        printf("MEG-4 Converter by bzt Copyright (C) 2023 GPLv3+\r\n\r\n");
        printf("%s [-b] <somefile> [output.zip]\r\n", argv[0]);
        exit(1);
    }
    if(argv[1][0] == '-') { isbinary = 1; i++; }
    buf = main_readfile(argv[i], &len);
    main_init(argv[1]);
    printf("importing...\n");

    /* import */
    if(!main_import(argv[i], buf, len)) {
        free(buf); free(meg4_defwaves); free(meg4_font);
        printf("unable to load file\n");
        exit(1);
    }
    free(buf);

    printf("exporting...\n");

    /* export */
    meg4_export(argv[i + 1] ? argv[i + 1] : "output.zip", isbinary);

    /* free resources */
    free(meg4_defwaves);
    free(meg4_font);
    return 0;
}
