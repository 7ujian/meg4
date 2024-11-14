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

#define HISTLEN 128

static char hist[HISTLEN][256] = { 0 }, *getsscr, *getscur, *getsbuf, *getsend;
static int numcache, cache[640], histpos, doblink = 0;
static uint16_t conx, cony, conw;
static uint32_t conc;

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
    if(doblink) { x = bg; bg = fg; fg = x; }
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
        for(y = 0; y < 8; y++, dst += p)
            for(x = 0; x < 9; x++)
                dst[x] = bg;
        meg4_blit(meg4.vram, dx, dy, dp, 8, 8, meg4_icons.buf, c == 0x2328 ? 32 : (c == 0x1F3AE ? 40 : 48), 64, meg4_icons.w * 4, 1);
        cache[numcache++] = 9; meg4.mmio.conx += 9;
        return;
    } else
    /* emoji */
    if(c >= EMOJI_FIRST && c < EMOJI_LAST) {
        c -= EMOJI_FIRST; if(c >= (uint32_t)(sizeof(emoji)/sizeof(emoji[0])) || !emoji[c]) return;
        for(y = 0; y < 8; y++, dst += p)
            for(x = 0; x < 9; x++)
                dst[x] = bg;
        meg4_blit(meg4.vram, dx, dy, dp, 8, 8, meg4_icons.buf, ((int)emoji[c] % 13) * 8, 64 + ((int)emoji[c] / 13) * 8, meg4_icons.w * 4, 1);
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
 * Draw the cursor
 */
void meg4_getscsr(int blink)
{
    uint16_t ox = meg4.mmio.conx;
    doblink = blink;
    meg4_putc(conc ? conc : ' ');
    meg4.mmio.conx = ox;
    doblink = 0;
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
    uint32_t key, *dst, bg = (0xff << 24) | meg4.mmio.palette[(int)meg4.mmio.conb];
    uint16_t cx;
    char *s, *c, *cb, ctrl = meg4_api_getkey(MEG4_KEY_LCTRL) || meg4_api_getkey(MEG4_KEY_RCTRL);
    int x, y, l, dx, dy, p = 640;

    /* --- init --- */
    if(!(meg4.flg & 2)) {
        meg4.flg |= 16;
        histpos = -1;
        getsbuf = getsscr = getscur = getsend = (char*)meg4.data + sizeof(meg4.data) - 256;
        memset(getsbuf, 0, 256); meg4_conrst();
        conx = meg4.mmio.conx;
        cony = le16toh(meg4.mmio.cropx0); if(conx < cony) conx = cony;
        cony = le16toh(meg4.mmio.cropx1); conw = (cony < meg4.screen.w ? cony : meg4.screen.w) - conx;
        cony = meg4.mmio.cony;
        main_osk_show();
    }
    conc = 0;
    /* --- controller --- */
    meg4.flg &= ~2;
    key = meg4_api_popkey();
    meg4.flg |= 2;
    if(!key) return 0;
    l = meg4_api_lenkey(key);
    if(key == le32toh('\n')) {
        main_osk_hide();
        meg4_getscsr(0);
        meg4.mmio.conx = 0; meg4.mmio.cony += 8; meg4_conrst(); if(meg4.mmio.cony + 8 > meg4.screen.h) meg4.mmio.cony = 0;
        if(strcmp(hist[0], (char*)meg4.data + sizeof(meg4.data) - 256)) {
            memmove(hist[1], hist[0], (HISTLEN - 1) * 256);
            memcpy(hist[0], meg4.data + sizeof(meg4.data) - 256, 256);
        }
        histpos = -1;
        meg4.flg &= ~18;
        return (str_t)(MEG4_MEM_LIMIT - 256);
    } else
    if(!memcmp(&key, "Up", 3)) {
        if(histpos < HISTLEN - 1 && hist[histpos + 1][0]) {
            memcpy(getsbuf, hist[++histpos], 256);
            getscur = getsend = getsbuf + strlen(getsbuf); getsscr = getsbuf;
        }
    } else
    if(!memcmp(&key, "Down", 4)) {
        if(histpos > 0) memcpy(getsbuf, hist[--histpos], 256);
        else memset(getsbuf, 0, 256);
        getscur = getsend = getsbuf + strlen(getsbuf); getsscr = getsbuf;
    } else
    if(!memcmp(&key, "Left", 4)) {
        if(ctrl) {
            if(getscur > getsbuf && getscur[-1] == ' ') getscur--;
            while(getscur > getsbuf && *getscur == ' ') getscur--;
            while(getscur > getsbuf && getscur[-1] != ' ') getscur--;
        } else
            if(getscur > getsbuf)
                do { getscur--; } while(getscur > getsbuf && (*getscur & 0xC0) == 0x80);
    } else
    if(!memcmp(&key, "Rght", 4)) {
        if(ctrl) {
            while(getscur < getsend && *getscur == ' ') getscur++;
            while(getscur < getsend && *getscur != ' ') getscur++;
        } else
            if(getscur < getsend)
                do { getscur++; } while(getscur < getsend && (*getscur & 0xC0) == 0x80);
    } else
    if(!memcmp(&key, "Home", 4)) { getscur = getsbuf; } else
    if(!memcmp(&key, "End", 4)) { getscur = getsend; } else
    if(!memcmp(&key, "Del", 4)) {
        if(getscur < getsend) {
            s = getscur;
            do { s++; } while(s < getsend && (*s & 0xC0) == 0x80);
            for(l = 0; s + l <= getsend; l++) getscur[l] = s[l];
            getsend -= (uintptr_t)s - (uintptr_t)getscur;
            getsscr = getsbuf;
        }
    } else
    if(key == le32toh(8)) {
        if(getscur > getsbuf) {
            s = getscur;
            do { getscur--; } while(getscur > getsbuf && (*getscur & 0xC0) == 0x80);
            for(l = 0; s + l <= getsend; l++) getscur[l] = s[l];
            getsend -= (uintptr_t)s - (uintptr_t)getscur;
            getsscr = getsbuf;
        }
    } else
    if(!memcmp(&key, "Pst", 4)) {
        if((cb = main_getclipboard())) {
            /* we can't just insert the whole string, we need to do it character by character */
            for(c = cb; *c; c += l) {
                l = 1;
                if((*c & 128) != 0) {
                    if(!(*c & 32)) l += 1; else
                    if(!(*c & 16)) l += 2; else
                    if(!(*c & 8)) l += 3;
                    else break;
                }
                if(*c >= ' ' && (uintptr_t)getsend - (uintptr_t)getsbuf + l < 255) {
                    for(s = getsend; s >= getscur; s--) s[l] = s[0];
                    memcpy(getscur, c, l);
                    getscur += l;
                    getsend += l;
                }
            }
            *getsend = 0;
            free(cb);
        }
    } else
    if(!meg4_api_speckey(key) && (uintptr_t)getsend - (uintptr_t)getsbuf + l < 255) {
        for(s = getsend; s >= getscur; s--) s[l] = s[0];
        memcpy(getscur, &key, l);
        getscur += l;
        getsend += l;
        *getsend = 0;
    }
    /* --- view --- */
    /* scroll text in input box */
    if(getscur < getsscr) getsscr = getscur;
    do {
        if((uint16_t)meg4_width(meg4_font, 1, getsscr, getscur) < conw - 8) break;
        do { getsscr++; } while(getsscr < getsend && (*getsscr & 0xC0) == 0x80);
    } while(1);
    meg4.mmio.conx = cx = conx; meg4.mmio.cony = cony;
    /* clear the area */
    dx = (meg4.mmio.scrx > 320 ? 0 : meg4.mmio.scrx) + meg4.mmio.conx;
    dy = (meg4.mmio.scry > 200 ? 0 : meg4.mmio.scry) + meg4.mmio.cony;
    dst = &meg4.vram[dy * p + dx];
    l = conw - meg4.mmio.conx + 1;
    for(y = 0; y < 8 && dy + y < 400; y++, dst += p)
        for(x = 0; x < l && dx + x < p; x++)
            dst[x] = bg;
    /* display string, save the cursor's position and character (needed by meg4_getscsr() later) */
    for(s = getsscr; *s && s < getsend; ) {
        c = s; s = meg4_utf8(s, &key);
        if(c == getscur) { cx = meg4.mmio.conx; conc = key; }
        if(!key || meg4.mmio.conx + 8 >= conx + conw) break;
        numcache = 0;
        meg4_putc(key);
    }
    if(conc) meg4.mmio.conx = cx;
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
