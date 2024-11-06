/*
 * meg4/cons.c
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
 * @brief Console, high-level user input / output
 * @chapter Console
 *
 */

#include "meg4.h"
#include "misc/emoji.h"

#define HISTLEN 16

static char hist[HISTLEN][256] = { 0 };
static int numcache, cache[640], getspos, histpos;
static uint16_t conx, cony;

/**
 * Helper, convert UTF-8 to UNICODE codepoint
 */
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

/**
 * Reset console, clear cache
 */
void meg4_conrst(void)
{
    memset(cache, 0, sizeof(cache));
    numcache = 0;
}

/**
 * Parse and print a UNICODE codepoint to screen.
 */
void meg4_putc(uint32_t c)
{
    uint8_t *fnt;
    uint32_t *d, *dst, bg = (0xff << 24) | meg4.mmio.palette[(int)meg4.mmio.conb], fg = meg4.mmio.palette[(int)meg4.mmio.conf];
    int x, y, l, r, m, dx, dy, dp = 2560, p = 640;

    if(!c) return;
    if(c == '\r') { meg4.mmio.conx = 0; meg4_conrst(); return; }
    if(c == '\n') { meg4.mmio.conx = 0; meg4.mmio.cony += 8; meg4_conrst(); if(meg4.mmio.cony + 8 > meg4.screen.h) { meg4.mmio.cony = 0; } return; }
    if(c == '\t') { m = meg4.mmio.conx; meg4.mmio.conx = (meg4.mmio.conx + 32) & ~31; cache[numcache++] = meg4.mmio.conx - m; }
    if(meg4.mmio.conx + 8 > meg4.screen.w || numcache + 1 >= (int)sizeof(cache)) { meg4.mmio.conx = 0; meg4.mmio.cony += 8; meg4_conrst(); }
    if(meg4.mmio.cony + 8 > meg4.screen.h) { meg4.mmio.conx = meg4.mmio.cony = 0; meg4_conrst(); }
    dx = (meg4.mmio.scrx > 320 ? 0 : meg4.mmio.scrx) + meg4.mmio.conx;
    dy = (meg4.mmio.scry > 200 ? 0 : meg4.mmio.scry) + meg4.mmio.cony;
    dst = &meg4.vram[dy * p + dx];
    /* backspace */
    if(c == 8) {
        if(!numcache) return;
        numcache--;
        if(meg4.mmio.conx > cache[numcache]) {
            dst -= cache[numcache];
            meg4.mmio.conx = meg4.mmio.conx - cache[numcache];
        } else {
            dst -= meg4.mmio.conx;
            meg4.mmio.conx = 0;
        }
        for(y = 0; y < 8; y++, dst += p)
            for(x = 0; x < cache[numcache]; x++)
                dst[x] = bg;
        cache[numcache] = 0;
        return;
    } else
    /* special characters: keyboard, gamepad and mouse */
    if(c == 0x2328 || c == 0x1F3AE || c == 0x1F5B1) {
        meg4_blit(dst, dx, dy, dp, 8, 8, meg4_icons.buf, c == 0x2328 ? 32 : (c == 0x1F3AE ? 40 : 48), 64, meg4_icons.w * 4, 1);
        cache[numcache++] = 9; meg4.mmio.conx += 9;
        return;
    } else
    /* emoji */
    if(c >= EMOJI_FIRST && c < EMOJI_LAST) {
        c -= EMOJI_FIRST; if(c >= (uint32_t)(sizeof(emoji)/sizeof(emoji[0])) || !emoji[c]) return;
        meg4_blit(dst, dx, dy, dp, 8, 8, meg4_icons.buf, ((int)emoji[c] % 13) * 8, 64 + ((int)emoji[c] / 13) * 8, meg4_icons.w * 4, 1);
        cache[numcache++] = 9; meg4.mmio.conx += 9;
        return;
    } else
    if(c < 32 || c > 0xffff) return;
    l = meg4_font[8 * 65536 + c] & 0xf; r = meg4_font[8 * 65536 + c] >> 4;
    m = r - l + 1; cache[numcache++] = m + 1; meg4.mmio.conx += m + 1;
    fnt = meg4_font + 8 * c;
    for(y = 0; y < 8; y++, fnt++, dst += p)
        for(d = dst, x = l, m = (1 << l); x <= r; x++, d++, m <<= 1)
            d[0] = (*fnt & m) ? fg : bg;
}

/**
 * Print the gets buffer to console
 */
void meg4_getsprt(char *s)
{
    uint32_t c, *dst, bg = (0xff << 24) | meg4.mmio.palette[(int)meg4.mmio.conb];
    int x, y, l, dx, dy, p = 640;
    char *o = s;

    /* clear the area */
    dx = (meg4.mmio.scrx > 320 ? 0 : meg4.mmio.scrx) + conx;
    dy = (meg4.mmio.scry > 200 ? 0 : meg4.mmio.scry) + cony;
    dst = &meg4.vram[dy * p + dx];
    l = meg4.mmio.conx - conx + 1;
    if(meg4.mmio.cony < cony) {
        /* screen was scrolled, just clear the first line */
        dx -= conx; dy -= cony; dst = &meg4.vram[dy * p + dx];
        for(y = 0; y < 8 && dy + y < 400; y++, dst += p)
            for(x = 0; x < p && dx + x < p; x++)
                dst[x] = bg;
    } else
    if(meg4.mmio.cony == cony) {
        /* one line */
        for(y = 0; y < 8 && dy + y < 400; y++, dst += p)
            for(x = 0; x < l && dx + x < p; x++)
                dst[x] = bg;
    } else {
        /* more lines */
        for(y = 0; y < 8 && dy + y < 400; y++, dst += p)
            for(x = 0; dx + x < p; x++)
                dst[x] = bg;
        dx = (meg4.mmio.scrx > 320 ? 0 : meg4.mmio.scrx) + meg4.mmio.conx; dy += 8;
        dst = &meg4.vram[dy * p];
        for(y = 0; y < 8 && dy + y < 400; y++, dst += p)
            for(x = 0; x < dx && x < p; x++)
                dst[x] = bg;
    }
    /* reset to starting point and print new string filling up cache from the beginning */
    meg4.mmio.conx = conx; meg4.mmio.cony = cony; meg4_conrst();
    while(*s && (uintptr_t)s - (uintptr_t)o < 256) {
        s = meg4_utf8(s, &c);
        if(!c) break;
        meg4_putc(c);
    }
}

/**
 * Draw the cursor
 */
void meg4_getscsr(int blink)
{
    uint32_t *dst, bg = (0xff << 24) | meg4.mmio.palette[(int)(blink ? meg4.mmio.conf : meg4.mmio.conb)];
    int x, y, dx, dy, p = 640;

    /* clear the area */
    dx = (meg4.mmio.scrx > 320 ? 0 : meg4.mmio.scrx) + meg4.mmio.conx;
    dy = (meg4.mmio.scry > 200 ? 0 : meg4.mmio.scry) + meg4.mmio.cony;
    dst = &meg4.vram[dy * p + dx];
    for(y = 0; y < 8 && dy + y < 400; y++, dst += p)
        for(x = 0; x < 6 && dx + x < p; x++)
            dst[x] = bg;
}

/**
 * Prints a character to console.
 * @param chr UTF-8 character
 */
void meg4_api_putc(uint32_t chr)
{
    uint32_t c = 0;
    meg4_utf8((char*)&chr, &c);
    meg4_putc(c);
}

/**
 * Prints text to console.
 * @param fmt string to display, a [format string]
 * @param ... optional arguments
 */
void meg4_api_printf(str_t fmt, ...)
{
    uint32_t c;
    char tmp[256], *s;

    if(fmt >= MEG4_MEM_USER && fmt < MEG4_MEM_LIMIT - 1) {
        meg4_snprintf(tmp, sizeof(tmp), (char*)meg4.data + fmt - MEG4_MEM_USER);
        for(s = tmp; s < tmp + sizeof(tmp) && *s;) {
            s = meg4_utf8(s, &c);
            if(!c) break;
            meg4_putc(c);
        }
    }
}

/**
 * Reads a character from console, blocks program when there's no input.
 * @return An UTF-8 character the user entered.
 * @see [popkey]
 */
uint32_t meg4_api_getc(void)
{
    uint32_t key;
    meg4.flg &= ~2;
    key = meg4_api_popkey();
    if(!key) { meg4.flg |= 2; return 0; }
    /* hack: BASIC expects that this fuction returns a string reference */
    if(meg4.code_type == 1) {
        memcpy(meg4.data + MEG4_MEM_LIMIT - MEG4_MEM_USER - 8, &key, 4);
        meg4.data[MEG4_MEM_LIMIT - MEG4_MEM_USER - 4] = 0;
        return MEG4_MEM_LIMIT - 8;
    }
    return key;
}

/**
 * Reads in a newline terminated string from user (does not return the newline).
 * @return The bytes read in a string.
 */
str_t meg4_api_gets(void)
{
    uint32_t key;
    int l;

    if(!(meg4.flg & 2)) {
        meg4.flg |= 16;
        histpos = -1; conx = meg4.mmio.conx; cony = meg4.mmio.cony;
        getspos = sizeof(meg4.data) - 256; memset(meg4.data + getspos, 0, 256); meg4_conrst();
    }
    meg4.flg &= ~2;
    key = meg4_api_popkey();
    if(!key) { meg4.flg |= 2; return 0; }
    meg4_getscsr(0);
    l = meg4_api_lenkey(key);
    if(!memcmp(&key, "Up", l)) {
        if(histpos < HISTLEN - 1 && hist[histpos + 1][0]) {
            getspos = sizeof(meg4.data) - 256;
            memcpy(meg4.data + getspos, hist[++histpos], 256);
            meg4_getsprt((char*)meg4.data + getspos);
            getspos += strlen((char*)meg4.data + getspos);
        }
        meg4.flg |= 2;
    } else
    if(!memcmp(&key, "Down", l)) {
        getspos = sizeof(meg4.data) - 256;
        if(histpos > 0) memcpy(meg4.data + getspos, hist[--histpos], 256);
        else memset(meg4.data + getspos, 0, 256);
        meg4_getsprt((char*)meg4.data + getspos);
        getspos += strlen((char*)meg4.data + getspos);
        meg4.flg |= 2;
    } else
    if(key == le32toh('\n')) {
        if(strcmp(hist[0], (char*)meg4.data + sizeof(meg4.data) - 256)) {
            memmove(hist[1], hist[0], (HISTLEN - 1) * 256);
            memcpy(hist[0], meg4.data + sizeof(meg4.data) - 256, 256);
        }
        histpos = -1;
        meg4.flg &= ~16;
        return (str_t)(MEG4_MEM_LIMIT - 256);
    } else
    if(getspos + l < (int)sizeof(meg4.data) - 1) {
        meg4_api_putc(htole32(key));
        meg4.flg |= 2;
        if(key == le32toh(8)) {
            if(getspos > (int)sizeof(meg4.data) - 256) {
                do { meg4.data[getspos] = 0; getspos--; } while(getspos > (int)sizeof(meg4.data) - 256 && (meg4.data[getspos] & 0xC0) == 0x80);
            }
            meg4.data[getspos] = 0;
        } else {
            memcpy(meg4.data + getspos, &key, l);
            getspos += l;
        }
    }
    return 0;
}

/**
 * Trace execution by printing to stdout. Only works if `meg4` was started with the `-v` verbose flag.
 * @param fmt [format string]
 * @param ... optional arguments
 */
void meg4_api_trace(str_t fmt, ...)
{
    /* I know, admitedly not the best place, but I don't want to introduce a new chapter for three functions only */
#ifndef NOEDITORS
    char tmp[256];
    /* we can't specify command line flags on web, so verbose is always turned off there */
#ifndef __EMSCRIPTEN__
    extern int verbose;
    if(verbose &&
#else
    if(
#endif
      fmt >= MEG4_MEM_USER && fmt < MEG4_MEM_LIMIT - 1) {
        meg4_snprintf(tmp, sizeof(tmp), (char*)meg4.data + fmt - MEG4_MEM_USER);
        main_log(0, "trace: %s", tmp);
    }
#else
    (void)fmt;
#endif
}

/**
 * Delays program execution.
 * @param msec delay in milliseconds
 */
void meg4_api_delay(uint16_t msec)
{
    /* I know, admitedly not the best place, but I don't want to introduce a new chapter for three functions only */
    if(msec < 16) return;   /* one cycle is 60 FPS, 1000/60 = 16 */
    meg4.tmr = meg4.mmio.tick + msec;
    meg4.flg |= 4;
}

/**
 * Exits program.
 */
void meg4_api_exit(void)
{
    /* I know, admitedly not the best place, but I don't want to introduce a new chapter for three functions only */
    meg4.cp = meg4.pc = 0;
    meg4.flg |= 8;
}
