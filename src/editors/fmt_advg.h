/*
 * meg4/editors/fmt_advg.h
 *
 * Copyright (C) 2024 bzt
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
 * @brief AdvGame 2.0 importer
 * https://bztsrc.gitlab.io/meg4_advgame/
 */

/*** AdvGame 1.0 ***/

/* stored in overlay 0 */
typedef struct {
    char        lang[2];        /* language code */
    char        text[430];      /* intro text */
    char        answ[4][64];    /* default answers: unknown command, can't go there, can't use, saved */
    char        verb[1536];     /* save, load, navigation and verbs */
    char        noun[1536];     /* nouns */
    uint8_t     setup[256];     /* initial game state */
    uint8_t     status[2];      /* status variables */
    uint8_t     colors[5];      /* intro background, intro foreground, room background, room foreground, prompt color */
    uint8_t     textpos;        /* text Y position */
    uint8_t     logic[72];      /* common game logic script operands */
} __attribute__((packed)) ag1_conf_t;
extern char c_assert1[sizeof(ag1_conf_t) == 4096 ? 1 : -1];

/* stored in overlays 1 to 254 */
typedef struct {
    uint8_t     verb;           /* verb to match, 1 to 32 */
    uint8_t     noun1;          /* noun to match, 0 (none) to 255 */
    uint8_t     noun2;          /* noun to match, 0 (none) to 255 */
    uint8_t     op[61];         /* script operands */
} __attribute__((packed)) ag1_cmds_t;

typedef struct {
    char        msg[2][2048];   /* text messages */
    uint8_t     dir[6];         /* navigation, room numbers or 0 if none / 255 if script */
    ag1_cmds_t   cmds[63];      /* commands understood in this room (script list) */
} __attribute__((packed)) ag1_room_t;
extern char c_assert2[sizeof(ag1_room_t) <= 8192 ? 1 : -1];

/*** AdvGame 2.0 ***/

/* on-disk format */

#define ADVG_MAGIC "ADVG"

typedef struct {
    uint8_t     magic[4];       /* file magic */
    uint32_t    size;           /* total file size including this header */
    uint32_t    uncomp;         /* uncompressed payload size */
    uint32_t    crc;            /* uncompressed payload crc */
    uint8_t     name[48];       /* UNIX name of the game */
             /* compressed payload[size - 64] */
} __attribute__((packed)) advg_t;

typedef struct {
    uint8_t     setup[256];     /* initial game state */
    uint8_t     status[8];      /* status variables */
    uint8_t     colors[7];      /* intro background, intro foreground, room background, room foreground, prompt color */
    uint8_t     version;        /* format version (2) */
    uint16_t    pos[16];        /* text Y position (room image height), game screen width, height, inventory x, y, w, h, item w, h, scroll w */
    uint8_t     logic[1024];    /* common game logic script operands */
    uint8_t     iface[2][1024]; /* custom user interface for intro and rooms */
    uint32_t    palette[256];   /* palette */
    uint16_t    items[510];     /* inventory sprites for nouns, 255 times x, y pairs */
    uint8_t     numconf;        /* number of configuration blocks (1 to 32) */
    uint8_t     numroom;        /* number of room blocks (1 to 254) */
    uint8_t     numverb;        /* number of verbs (0 to 127) */
    uint8_t     numnoun;        /* number of nouns (0 to 255) */
    uint16_t    numassets;      /* number of assets (0 to 1023) */
    uint16_t    icon;           /* application icon asset or FFFF */
    uint16_t    font;           /* font asset index or FFFF */
    uint16_t    sprites;        /* sprites asset index or FFFF */
    uint16_t    music[16];      /* music asset indeces or FFFF */
    uint16_t    sound[64];      /* sound effect indeces or FFFF */
             /* numconf * advg_conf_t */
             /* numroom * advg_room_t */
             /* numassets * advg_asset_t */
} __attribute__((packed)) advg_payload_t;

typedef struct {
    uint32_t    size;           /* total size of the configuration block */
    char        lang[2];        /* language code */
             /* introtext, zero terminated UTF-8 */
             /* messages, 4 * zero terminated UTF-8 */
             /* verbs, numverb * 16 * zero terminated UTF-8 */
             /* nouns, numnoun * 16 * zero terminated UTF-8 */
} __attribute__((packed)) advg_conf_t;

typedef struct {
    uint8_t     dir[6];         /* navigation, room numbers or 0 if none / 255 if script */
    uint8_t     numimgs;        /* number of images */
    uint8_t     numtext;        /* number of text messages */
    uint8_t     numcmds;        /* number of commands */
             /* images, numimgs * 2 bytes, asset indeces */
             /* texts, numtext * numconf * zero terminated UTF-8 */
             /* commands, numcmds * ag2_cmds_t */
} __attribute__((packed)) advg_room_t;

typedef struct {
    uint32_t    w;              /* image width / number of frames */
    uint32_t    h;              /* image height / frame size (number of channels * 2) */
             /* asset data, w * h bytes in total (8 bit palette index or 16 bit PCM) */
} __attribute__((packed)) advg_asset_t;

/* must match ops[] in advcomp.c */
int opsizes[] = { 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 6, 6, 6, 6, 7, 11, 11, 15 }, numop = 0;

/**
 * Copy text wrapped (uses MEG-4 proportional font to calculate line width in pixels)
 */
int advg_wrap(char *dst, char *src, int len, int width)
{
    uint32_t c;
    char *bef;
    int space = 0, l, s, w = 6, o = 0;

    for(l = 0; l + 1 < len && *src;) {
        bef = src; src = meg4_utf8(src, &c);
        if(c == ' ') { if(l && dst[l - 1] == ' ') { continue; } space = l; o = w; }
        if(c == '\r') { w = 0; continue; } else
        if(c == '\n') { w = 0; dst[l++] = '\n'; dst[l] = ' '; space = 0; continue; } else
        if(c == 0x2328 || c == 0x1F3AE || c == 0x1F5B1 ||
          (c >= EMOJI_FIRST && c < EMOJI_LAST && c - EMOJI_FIRST < (uint32_t)(sizeof(emoji)/sizeof(emoji[0]))))
            w += 8 + 1; else
        if(c <= 0xffff) {
            if(!meg4.font[8 * 65536 + c] && meg4_isbyte(meg4.font + 8 * c, 0, 8)) c = 0;
            w += ((meg4.font[8 * 65536 + c] >> 4) - (meg4.font[8 * 65536 + c] & 0xf) + 1) + 1;
        }
        if(w > width && space > 0) {
            memmove(dst + space + 1, dst + space, l - space + 1);
            dst[space] = '\n'; space = 0; w -= o; l++;
        }
        s = (uintptr_t)src - (uintptr_t)bef;
        if(s > 0) {
            if(l + s + 1 >= len) { dst[l] = 0; l = len - 1; break; }
            memcpy(dst + l, bef, s); l += s;
        }
    }
    dst[l++] = 0;
    return l;
}

/**
 * Copy instructions with buffer limit
 */
void advg_copyopcodes(uint8_t *dst, uint8_t *src, int dlen)
{
    uint8_t *ptr = src;
    int i, l = 0;

    dlen--;
    for(l = 0; *ptr; ptr += i) {
        i = opsizes[(uint32_t)(*ptr >> 3)] + ((*ptr & 7) ? ((*ptr & 7) < 6 ? 2 : 1) : 0);
        if((*ptr >> 3) < 21) {
            if(l + i >= dlen) break;
            else l += i;
        }
    }
    memcpy(dst, src, l);
    memset(dst + l, 0, dlen - l + 1);
}

/**
 * Generate a multiplied coordinate string
 */
void advg_mcrd(char *dst, uint8_t *arg)
{
    if(!arg[1] || !arg[2]) sprintf(dst, "%u", arg[0]<<3); else
    if(arg[2] > 248) sprintf(dst, "%u%s%d*lang", arg[0]<<3, (int8_t)arg[1] < 0 ? "" : "+", (int8_t)arg[1]); else
        sprintf(dst, "%u%s%d*state[%u]", arg[0]<<3, (int8_t)arg[1] < 0 ? "" : "+", (int8_t)arg[1], arg[2]);
}

/**
 * Generate a multiplied sprite index string
 */
void advg_sidx(char *dst, uint8_t *arg)
{
    uint16_t s = 128 + arg[0] + arg[3] * 32;
    char var[64];
    if(!arg[1] && !arg[4]) sprintf(dst, "%u", s); else
    if(arg[1] && !arg[4]) {
        if(arg[2] > 248) sprintf(dst, "%u%s%d*lang", s, (int8_t)arg[1] < 0 ? "" : "+", (int8_t)arg[1]/8); else
            sprintf(dst, "%u%s%d*state[%u]", s, (int8_t)arg[1] < 0 ? "" : "+", (int8_t)arg[1]/8, arg[2]);
    } else
    if(!arg[1] && arg[4]) {
        if(arg[5] > 248) sprintf(dst, "%u%s%d*lang", s, (int8_t)arg[4] < 0 ? "" : "+", (int16_t)(int8_t)arg[4] * 4); else
            sprintf(dst, "%u%s%d*state[%u]", s, (int8_t)arg[4] < 0 ? "" : "+", (int16_t)(int8_t)arg[4] * 4, arg[5]);
    } else {
        if(arg[5] > 248) sprintf(var, "%s%d*lang", (int8_t)arg[4] < 0 ? "" : "+", (int16_t)(int8_t)arg[4] * 4); else
            sprintf(var, "%s%d*state[%u]", (int8_t)arg[4] < 0 ? "" : "+", (int16_t)(int8_t)arg[4] * 4, arg[5]);
        if(arg[2] > 248) sprintf(dst, "%u%s%d*lang%s", s, (int8_t)arg[1] < 0 ? "" : "+", (int8_t)arg[1]/8, var); else
            sprintf(dst, "%u%s%d*state[%u]%s", s, (int8_t)arg[1] < 0 ? "" : "+", (int8_t)arg[1]/8, arg[2], var);
    }
}

/**
 * Generate MEG-4 code from instructions
 */
char *advg_gencode(uint8_t *src)
{
    static char *cnds[] = { "", "==", "!=", "<=", "<", ">" };
    uint8_t *ptr = src, *arg;
    uint16_t x, y, w, h, s;
    char *ret = NULL, cmd[256], var[3][64];
    int i, j = 0, l = 0, dlen = 0;

    for(l = 0; *ptr; ptr += i) {
        i = opsizes[(uint32_t)(*ptr >> 3)] + ((*ptr & 7) ? ((*ptr & 7) < 6 ? 2 : 1) : 0);
        arg = ptr + 1;
        if(!(*ptr >> 3) || (*ptr >> 3) >= 21) {
            memset(cmd, 0, sizeof(cmd)); j = 0;
            if(*ptr & 7) {
                j = sprintf(cmd, "if(");
                if((*ptr & 7) == 6) { j += sprintf(cmd + j, "state[%u] & %u", 255 - (arg[0] >> 3), 1 << (arg[0] & 7)); arg++; } else
                if((*ptr & 7) == 7) { j += sprintf(cmd + j, "!(state[%u] & %u)", 255 - (arg[0] >> 3), 1 << (arg[0] & 7)); arg++; } else {
                    if(arg[0] == 249) j += sprintf(cmd + j, "lang"); else
                    if(arg[0] >= 250) j += sprintf(cmd + j, "dir[%u]", arg[0] - 250); else
                        j += sprintf(cmd + j, "state[%u]", arg[0]);
                    j += sprintf(cmd + j, "%s%u", cnds[*ptr & 7], arg[1]);
                    arg += 2;
                }
                j += sprintf(cmd + j, ") ");
            }
            if(!(*ptr >> 3)) j += sprintf(cmd + j, "return"); else
                switch(*ptr >> 3) {
                    case 21: /* img */
                        if(arg[0] || arg[1] >= 320/8 || arg[2] >= 200/8) continue;
                        j += sprintf(cmd + j, "spr(%u,%u,128,32,12,0,0)",arg[1]<<3,arg[2]<<3);
                    break;
                    case 22: /* frect */
                        x = arg[1] << 3; y = arg[2] << 3; w = x + (arg[3] << 3), h = y + (arg[4] << 3);
                        if(x >= 320 || y >= 200) continue;
                        if(w >= 320) w = 320 - x;
                        if(h >= 200) h = 200 - y;
                        j += sprintf(cmd + j, "frect(%u,%u,%u,%u,%u)", arg[0], x, y, w - 1, h - 1);
                    break;
                    case 23: /* text */ case 24: /* verb */ case 25: /* noun */ continue;
                    case 26: /* spr */
                        x = arg[0] << 3; y = arg[1] << 3; w = arg[4], h = arg[5];
                        if(y == 2040) y = 200 - (h << 3);
                        s = 128 + arg[2] + (arg[3] << 5);
                        if(x >= 320 || y >= 200 || s > 1023 || !w || !h) continue;
                        j += sprintf(cmd + j, "spr(%u,%u,%u,%u,%u,0,0)", x, y, s, w, h);
                    break;
                    case 27: /* sprd */
                        x = arg[0] << 3; y = arg[3] << 3; w = arg[8], h = arg[9];
                        if(y == 2040) y = 200 - (h << 3);
                        s = 128 + arg[6] + (arg[7] << 5);
                        if(x >= 320 || y >= 200 || s > 1023 || !w || !h) continue;
                        advg_mcrd(var[0], arg + 0);
                        advg_mcrd(var[1], arg + 3);
                        j += sprintf(cmd + j, "spr(%s,%s,%u,%u,%u,0,0)", var[0], var[1], s, w, h);
                    break;
                    case 28: /* sprs */
                        x = arg[0] << 3; y = arg[1] << 3; w = arg[8], h = arg[9];
                        if(y == 2040) y = 200 - (h << 3);
                        if(x >= 320 || y >= 200 || !w || !h) continue;
                        advg_sidx(var[0], arg + 2);
                        j += sprintf(cmd + j, "spr(%u,%u,%s,%u,%u,0,0)", x, y, var[0], w, h);
                    break;
                    case 29: /* sprm */
                        x = arg[0] << 3; y = arg[3] << 3; w = arg[12], h = arg[13];
                        if(y == 2040) y = 200 - (h << 3);
                        if(x >= 320 || y >= 200 || !w || !h) continue;
                        advg_mcrd(var[0], arg + 0);
                        advg_mcrd(var[1], arg + 3);
                        advg_sidx(var[2], arg + 6);
                        j += sprintf(cmd + j, "spr(%s,%s,%s,%u,%u,0,0)", var[0], var[1], var[2], w, h);
                    break;
                    default: continue;
                }
            if(l + 256 > dlen) {
                dlen += 8192;
                if(!(ret = (char*)realloc(ret, dlen))) return NULL;
            }
            l += sprintf(ret + l, "  %s;\n", cmd);
        }
    }

    return ret;
}

/**
 * Import an AdvGame 2.0 archive file
 */
static int format_advg(uint8_t *buf, int len)
{
    char *ptr, *src, *pl = NULL, *end, *rooms, *empty = "", *custom[2] = { 0 };
    int i, j, k, l, m, n, size;
    advg_payload_t *payload;
    advg_room_t *room;
    advg_asset_t **assets;
    ag1_conf_t *c;
    ag1_room_t *r;

    /* uncompress payload */
    if(!buf || len < 64 || memcmp(buf, ADVG_MAGIC, 4) || !(pl = (char*)stbi_zlib_decode_malloc_guesssize_headerflag(
      (const char*)buf + sizeof(advg_t), ((advg_t*)buf)->size - sizeof(advg_t), ((advg_t*)buf)->uncomp, &size, 0)) ||
      ((advg_t*)buf)->uncomp != (uint32_t)size || stbiw__crc32((uint8_t*)pl, size) != ((advg_t*)buf)->crc) {
        if(pl) free(pl);
        return 0;
    }
    payload = (advg_payload_t *)pl;
    end = pl + size;

    /* load title */
    memset(meg4_title, 0, sizeof(meg4_title));
    strncpy(meg4_title, (char*)((advg_t*)buf)->name, 48);

    /* load asset pointers in advance */
    if(!(assets = (advg_asset_t**)malloc((payload->numassets + 1) * sizeof(void*)))) { free(pl); return 0; }
    memset(assets, 0, (payload->numassets + 1) * sizeof(void*));
    for(i = 0, rooms = pl + sizeof(advg_payload_t); i < payload->numconf && rooms < end; i++, rooms += ((advg_conf_t*)rooms)->size);
    for(i = 0, ptr = rooms; (uint8_t)i < payload->numroom && ptr < end; i++) {
        room = (advg_room_t*)ptr;
        ptr += sizeof(advg_room_t) + room->numimgs * 2;
        for(k = 0; (uint8_t)k < payload->numconf && ptr < end; k++)
            for(j = 0; (uint8_t)j < room->numtext && ptr < end; j++, ptr += l) l = strlen((char*)ptr) + 1;
        for(j = 0; (uint8_t)j < room->numcmds && ptr < end; j++, ptr += (ptr[1]<<8)|ptr[0]);
    }
    for(i = 0; (uint16_t)i < payload->numassets && ((advg_asset_t*)ptr)->w && ((advg_asset_t*)ptr)->h && ptr < end;
      i++, ptr += sizeof(advg_asset_t) + ((advg_asset_t*)ptr)->w * ((advg_asset_t*)ptr)->h)
        assets[i] = (advg_asset_t*)ptr;

    /* load palette */
    memcpy(meg4.mmio.palette, payload->palette, sizeof(meg4.mmio.palette));

    /* load sprites */
    memset(meg4.mmio.sprites, 0, sizeof(meg4.mmio.sprites));
    if(payload->sprites < payload->numassets && assets[payload->sprites]) {
        l = assets[payload->sprites]->w > 256 ? 256 : assets[payload->sprites]->w;
        for(j = k = 0; j < 224 && (uint32_t)j < assets[payload->sprites]->h; j++, k += assets[payload->sprites]->w)
            memcpy(meg4.mmio.sprites + 8192 + j * 256, (uint8_t*)&assets[payload->sprites]->w + sizeof(advg_asset_t) + k, l);
    }

    /* save game configuration to overlay 0 */
    meg4.ovls[0].size = 32768;
    if((meg4.ovls[0].data = (uint8_t*)realloc(meg4.ovls[0].data, meg4.ovls[0].size))) {
        memset(meg4.ovls[0].data, 0, meg4.ovls[0].size);
        c = (ag1_conf_t*)meg4.ovls[0].data;
        memcpy(c->setup, payload->setup, 256);
        memcpy(c->status, payload->status, 2);
        memcpy(c->colors, payload->colors, 5);
        c->textpos = payload->pos[0];
        advg_copyopcodes(c->logic, payload->logic, 72);
        /* we have room for 2 configurations */
        for(k = 0, ptr = pl + sizeof(advg_payload_t); (uint8_t)k < payload->numconf && k < 2 && ptr < end; k++, ptr += ((advg_conf_t*)ptr)->size) {
            c = (ag1_conf_t*)(meg4.ovls[0].data + k * sizeof(ag1_conf_t));
            src = ptr + sizeof(advg_conf_t);
            memcpy(c->lang, ((advg_conf_t *)ptr)->lang, 2);
            l = strlen(src) + 1; c->text[0] = ' '; advg_wrap(c->text + 1, src, 429, (payload->pos[1] && payload->pos[1] < 256 ? payload->pos[1] : 256) - 16); src += l;
            for(i = 0; i < 4; i++) { l = strlen(src); strncpy(c->answ[i], src, 63); src += l + 1; }
            for(i = m = 0; i < 42 && (uint8_t)i < payload->numverb; i++) {
                for(j = 0; j < 8; j++, m += l, src += l) { l = strlen(src) + 1; if(m + l < 1536) memcpy(c->verb + m, src, l); }
                for(j = 0; j < 8; j++, src += l) l = strlen(src) + 1;
            }
            for(i = m = 0; (uint8_t)i < payload->numnoun; i++) {
                l = strlen(src) + 1; if(m + l < 1536) memcpy(c->noun + m, src, l); m += l; src += l;
                for(j = 0; j < 15; j++, src += l) l = strlen(src) + 1;
            }
        }
        memcpy(meg4.ovls[0].data + 8192, meg4.mmio.sprites + 8192, meg4.ovls[0].size - 8192);
    } else meg4.ovls[0].size = 0;

    /* save rooms into overlays 1 to 254 */
    for(n = 0, ptr = rooms; (uint8_t)n < payload->numroom && n < 254 && ptr < end; n++) {
        meg4.ovls[n + 1].size = 32768;
        if((meg4.ovls[n + 1].data = (uint8_t*)realloc(meg4.ovls[n + 1].data, meg4.ovls[n + 1].size))) {
            memset(meg4.ovls[n + 1].data, 0, meg4.ovls[n + 1].size);
            r = (ag1_room_t*)meg4.ovls[n + 1].data;
            room = (advg_room_t*)ptr;
            ptr += sizeof(advg_room_t);
            k = (ptr[1]<<8)|ptr[0];
            ptr += room->numimgs * 2;
            /* copy directions */
            memcpy(r->dir, room->dir, 6);
            /* copy first room image only, up to 256 x 96 pixels */
            if(room->numimgs && (uint16_t)k < payload->numassets && assets[k]) {
                l = assets[k]->w > 256 ? 256 : assets[k]->w;
                for(j = m = 0; j < 96 && (uint32_t)j < assets[k]->h; j++, m += assets[k]->w)
                    memcpy(meg4.ovls[n + 1].data + 8192 + j * 256, (uint8_t*)&assets[k]->w + sizeof(advg_asset_t) + m, l);
            }
            /* copy up to 32 texts up to 2 configurations */
            for(k = 0; (uint8_t)k < payload->numconf && ptr < end; k++)
                for(j = m = 0; (uint8_t)j < room->numtext && ptr < end; j++, ptr += l) {
                    l = strlen((char*)ptr) + 1;
                    if(k < 2 && j < 32 && m < 2047) m += advg_wrap(r->msg[k] + m, ptr, 2048 - m > 256 ? 256 : 2048 - m, 310);
                }
            /* look up room logic script, it must be the first in AG1.0 */
            for(j = 0, src = ptr; (uint8_t)j < room->numcmds && src < end; j++, src += l) {
                l = (src[1]<<8)|src[0];
                if(!src[2] && !src[3] && !src[4]) { advg_copyopcodes(r->cmds[0].op, (uint8_t*)src + 5, 61); break; }
            }
            /* copy the rest, up to 63 scripts per room */
            for(j = 0, m = 1; (uint8_t)j < room->numcmds && ptr < end; j++, ptr += l) {
                l = (ptr[1]<<8)|ptr[0];
                if(ptr[2] && m < 63) { memcpy(&r->cmds[m].verb, ptr + 2, 3); advg_copyopcodes(r->cmds[m].op, (uint8_t*)ptr + 5, 61); m++; }
            }
        }
    }

    /* add game interpreter program */
    meg4.src_len = 0;
    if((ptr = (char*)stbi_zlib_decode_malloc_guesssize_headerflag((const char*)binary_advgame_c, sizeof(binary_advgame_c), 32768, &size, 1))) {
        if(!(custom[0] = advg_gencode(payload->iface[0]))) custom[0] = empty;
        if(!(custom[1] = advg_gencode(payload->iface[1]))) custom[1] = empty;
        if((meg4.src = (char*)realloc(meg4.src, strlen(ptr) + strlen(custom[0]) + strlen(custom[1]) + 1)))
            meg4.src_len = sprintf(meg4.src, ptr, custom[0], custom[1]) + 1;
        else meg4.src_len = 0;
        if(custom[0] != empty) free(custom[0]);
        if(custom[1] != empty) free(custom[1]);
        free(ptr);
    }

    free(assets);
    free(pl);
    return 1;
}
