/*
 * meg4/tests/converter/advgame.h
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
 * @brief Data importer for Adventure Game Engine
 *
 */

#define NUMVERB 16
#define NUMNOUN 96

/* stored in overlay 0 */
typedef struct {
    char        lang[2];        /* language code */
    char        text[430];      /* intro text */
    char        answ[4][64];    /* default answers: unknown command, can't go there, can't use, saved */
    char        verb[NUMVERB + 8][4][16];   /* save, load, navigation and verbs */
    char        noun[NUMNOUN][16];          /* nouns */
    uint8_t     setup[256];     /* initial game state */
    uint8_t     colors[5];      /* intro background, intro foreground, room background, room foreground, prompt color */
    uint8_t     textpos;        /* text Y position */
    uint8_t     logic[74];      /* common game logic */
} __attribute__((packed))  ag_conf_t;
extern char c_assert1[sizeof(ag_conf_t) == 4096 ? 1 : -1];

typedef struct {
    uint8_t     verb;           /* verb to match, 1 to 8 */
    uint8_t     noun1;          /* noun to match, 0 (none) to 96 */
    uint8_t     noun2;          /* noun to match, 0 (none) to 96 */
    uint8_t     op[61];         /* operands */
} __attribute__((packed)) ag_cmds_t;

/* stored in overlays 1 to 254 */
typedef struct {
    char        msg[2][16][128];/* text messages */
    uint8_t     dir[6];         /* navigation, room numbers or 0 / 255 if script */
    ag_cmds_t   cmds[63];       /* commands understand in this room (script list) */
} __attribute__((packed)) ag_room_t;
extern char c_assert2[sizeof(ag_room_t) <= 8192 ? 1 : -1];

/* script opcodes */
enum { ARG_NONE, ARG_MUS, ARG_SFX, ARG_VAR, ARG_VAL, ARG_MSG, ARG_ROOM };
typedef struct { char *op; int len, arg[3]; } ag_ops_t;
static ag_ops_t ops[] = {
 /*  0 */ { "end",   3, { ARG_NONE, ARG_NONE, ARG_NONE } },
 /*  1 */ { "reset", 5, { ARG_NONE, ARG_NONE, ARG_NONE } },
 /*  2 */ { "mus",   3, { ARG_MUS,  ARG_NONE, ARG_NONE } },
 /*  3 */ { "sfx",   3, { ARG_SFX,  ARG_NONE, ARG_NONE } },
 /*  4 */ { "sfxz",  4, { ARG_SFX,  ARG_VAR,  ARG_NONE } },
 /*  5 */ { "sfxnz", 5, { ARG_SFX,  ARG_VAR,  ARG_NONE } },
 /*  6 */ { "say",   3, { ARG_MSG,  ARG_NONE, ARG_NONE } },
 /*  7 */ { "sayz",  4, { ARG_MSG,  ARG_VAR,  ARG_NONE } },
 /*  8 */ { "saynz", 5, { ARG_MSG,  ARG_VAR,  ARG_NONE } },
 /*  9 */ { "inc",   3, { ARG_VAR,  ARG_NONE, ARG_NONE } },
 /* 10 */ { "incz",  4, { ARG_VAR,  ARG_VAR,  ARG_NONE } },
 /* 11 */ { "incnz", 5, { ARG_VAR,  ARG_VAR,  ARG_NONE } },
 /* 12 */ { "dec",   3, { ARG_VAR,  ARG_NONE, ARG_NONE } },
 /* 13 */ { "decz",  4, { ARG_VAR,  ARG_VAR,  ARG_NONE } },
 /* 14 */ { "decnz", 5, { ARG_VAR,  ARG_VAR,  ARG_NONE } },
 /* 15 */ { "set",   3, { ARG_VAR,  ARG_VAL,  ARG_NONE } },
 /* 16 */ { "setz",  4, { ARG_VAR,  ARG_VAL,  ARG_VAR  } },
 /* 17 */ { "setnz", 5, { ARG_VAR,  ARG_VAL,  ARG_VAR  } },
 /* 18 */ { "jmp",   3, { ARG_ROOM, ARG_NONE, ARG_NONE } },
 /* 19 */ { "jz",    2, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 20 */ { "jnz",   3, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 21 */ { "nz",    2, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 22 */ { "nnz",   3, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 23 */ { "wz",    2, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 24 */ { "wnz",   3, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 25 */ { "ez",    2, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 26 */ { "enz",   3, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 27 */ { "sz",    2, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 28 */ { "snz",   3, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 29 */ { "uz",    2, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 20 */ { "unz",   3, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 31 */ { "dz",    2, { ARG_ROOM, ARG_VAR,  ARG_NONE } },
 /* 32 */ { "dnz",   3, { ARG_ROOM, ARG_VAR,  ARG_NONE } }
};

/* the MEG-4 Adventure Game interpreter program */
static char *program = "#!c\n\n"
"/**\n"
" * Adventure Game Engine - MEG-4 DEMO\n"
" * Copyright (c) bzt 2024 CC-0\n"
" */\n%s\n"
"/* variables */\n"
"uint8_t lang, state[256], colors[5], textpos, logic[74], dir[8], cmd[4096], say, rst;\n"
"char ans[256], verb[1536], noun[1536], msg[2048], inp[256];\n\n"
"/* customize your UI here */\n"
"void custom_intro()\n{\n%s\n}\n"
"void custom_room()\n{\n%s\n}\n\n"
"/* function to parse and execute opcodes */\n"
"void parse_ops(uint8_t *c)\n"
"{\n"
"  uint8_t op, arg1, arg2, arg3;\n"
"  while(*c) {\n"
"    op = *c++;\n"
"    switch(op) {\n"
"      case 1: inp[0] = 0; rst = 1;\n"
"      case 2: music(*c++, 0, 128); break;\n"
"      case 3: sfx(*c++, 0, 255); break;\n"
"      case 4: arg1 = *c++; arg2 = *c++; if(!state[arg2]) sfx(arg1, 0, 255); break;\n"
"      case 5: arg1 = *c++; arg2 = *c++; if(state[arg2]) sfx(arg1, 0, 255); break;\n"
"      case 6: arg1 = *c++; say = 255; if(arg1 < 16) say = arg1 + 4; break;\n"
"      case 7: arg1 = *c++; arg2 = *c++; say = 255; if(!state[arg2] && arg1 < 16) say = arg1 + 4; break;\n"
"      case 8: arg1 = *c++; arg2 = *c++; say = 255; if(state[arg2] && arg1 < 16) say = arg1 + 4; break;\n"
"      case 9: arg1 = *c++; if(state[arg1] < 255) state[arg1]++; break;\n"
"      case 10: arg1 = *c++; arg2 = *c++; if(!state[arg2] && state[arg1] < 255) state[arg1]++; break;\n"
"      case 11: arg1 = *c++; arg2 = *c++; if(state[arg2] && state[arg1] < 255) state[arg1]++; break;\n"
"      case 12: arg1 = *c++; if(state[arg1] > 0) state[arg1]--; break;\n"
"      case 13: arg1 = *c++; arg2 = *c++; if(!state[arg2] && state[arg1] > 0) state[arg1]--; break;\n"
"      case 14: arg1 = *c++; arg2 = *c++; if(state[arg2] && state[arg1] > 0) state[arg1]--; break;\n"
"      case 15: arg1 = *c++; arg2 = *c++; state[arg1] = arg2; break;\n"
"      case 16: arg1 = *c++; arg2 = *c++; arg3 = *c++; if(!state[arg3]) state[arg1] = arg2; break;\n"
"      case 17: arg1 = *c++; arg2 = *c++; arg3 = *c++; if(state[arg3]) state[arg1] = arg2; break;\n"
"      case 18: load_room(*c++); return;\n"
"      case 19: arg1 = *c++; arg2 = *c++; if(!state[arg2]) { load_room(arg1); return; } break;\n"
"      case 20: arg1 = *c++; arg2 = *c++; if(state[arg2]) { load_room(arg1); return; } break;\n"
"      case 21: arg1 = *c++; arg2 = *c++; if(!state[arg2]) { cmd[0] = arg1; custom_room(); } break;\n"
"      case 22: arg1 = *c++; arg2 = *c++; if(state[arg2]) { cmd[0] = arg1; custom_room(); } break;\n"
"      case 23: arg1 = *c++; arg2 = *c++; if(!state[arg2]) { cmd[1] = arg1; custom_room(); } break;\n"
"      case 24: arg1 = *c++; arg2 = *c++; if(state[arg2]) { cmd[1] = arg1; custom_room(); } break;\n"
"      case 25: arg1 = *c++; arg2 = *c++; if(!state[arg2]) { cmd[2] = arg1; custom_room(); } break;\n"
"      case 26: arg1 = *c++; arg2 = *c++; if(state[arg2]) { cmd[2] = arg1; custom_room(); } break;\n"
"      case 27: arg1 = *c++; arg2 = *c++; if(!state[arg2]) { cmd[3] = arg1; custom_room(); } break;\n"
"      case 28: arg1 = *c++; arg2 = *c++; if(state[arg2]) { cmd[3] = arg1; custom_room(); } break;\n"
"      case 29: arg1 = *c++; arg2 = *c++; if(!state[arg2]) { cmd[4] = arg1; custom_room(); } break;\n"
"      case 30: arg1 = *c++; arg2 = *c++; if(state[arg2]) { cmd[4] = arg1; custom_room(); } break;\n"
"      case 31: arg1 = *c++; arg2 = *c++; if(!state[arg2]) { cmd[5] = arg1; custom_room(); } break;\n"
"      case 32: arg1 = *c++; arg2 = *c++; if(state[arg2]) { cmd[5] = arg1; custom_room(); } break;\n"
"    }\n"
"  }\n"
"}\n"
"\n"
"/* function to load a room */\n"
"void load_room(int r)\n"
"{\n"
"  if(state[0] == r) return;\n"
"  state[0] = r;\n"
"  memload(0x10000, r, 32768);\n"
"  memcpy(&msg, 0x10000 + lang * 2048, 2048);\n"
"  memcpy(&dir, 0x11000, 6);\n"
"  memcpy(&cmd, 0x11006, 4096);\n"
"  inp[0] = 0; say = 255;\n"
"  parse_ops(&logic);\n"
"  parse_ops(&cmd[3]);\n"
"  cls(colors[2]);\n"
"  spr(32, 2, 128, 32, textpos > 96 ? 12 : textpos/8, 0, 0);\n"
"  custom_room();\n"
"}\n"
"\n"
"/* function to parse user input into verb and one or two nouns */\n"
"void parse_cmd(char *s)\n"
"{\n"
"  uint8_t v, n1, n2;\n"
"  int i, j, k, l, m;\n"
"  if(!s || !*s) return;\n"
"  memcpy(&inp, s, 256);\n"
"  say = 0;\n"
"  v = 255; n1 = n2 = 0;\n"
"  for(i = 0; i < 255 && inp[i] && !n2;) {\n"
"    while(i < 255 && inp[i] == ' ') i++;\n"
"    if(v == 255)\n"
"      for(m = j = 0; j < 24; j++)\n"
"        for(k = 0; k < 4; k++, m += 16) {\n"
"          l = strlen(&verb[m]);\n"
"          if(l && !memcmp(&inp[i], &verb[m], l)) { v = j; j = 24; break; }\n"
"        }\n"
"    for(m = j = 0; j < 96; j++, m += 16) {\n"
"      l = strlen(&noun[m]);\n"
"      if(l && !memcmp(&inp[i], &noun[m], l)) { j++; if(!n1) n1 = j; else n2 = j; break; }\n"
"    }\n"
"    while(i < 255 && inp[i] && inp[i] != ' ') i++;\n"
"  }\n"
"  trace(\"%%d %%d %%d\",v,n1,n2);\n"
"  /* built-in navigation verbs */\n"
"  if(v >= 2 && v <= 7) {\n"
"    v -= 2;\n"
"    if(dir[v] == 255) { v += 128; n1 = n2 = 0; }\n"
"    else { if(!dir[v]) say = 1; else load_room(dir[v]); return; }\n"
"  }\n"
"  /* built-in save and load game verbs */\n"
"  if(v == 0) { memsave(255, &state, 256); say = 3; } else\n"
"  if(v == 1) { memload(&state, 255, 256); load_room(state[0]); } else\n"
"  /* look for a room script for this verb and noun(s) */\n"
"  if(v != 255) {\n"
"    for(i = 64; i < 63*64; i += 64)\n"
"      if(cmd[i] == v) {\n"
"        say = cmd[i + 1] ? 2 : 255;\n"
"        if(cmd[i + 1] == n1 && cmd[i + 2] == n2) { say = 255; parse_ops(&cmd[i + 3]); break; }\n"
"      }\n"
"  }\n"
"}\n"
"\n"
"/* wait for a keypress and jump to the first room */\n"
"void reset_game()\n"
"{\n"
"  uint8_t r;\n"
"  getc();\n"
"  memload(0x10000, 0, 32768);\n"
"  memcpy(&state, 0x10EB0, 256);\n"
"  /* jump to the first room */\n"
"  r = state[0] ? state[0] : 1;\n"
"  state[0] = rst = 0;\n"
"  load_room(r);\n"
"}\n"
"\n"
"/* load game configuration and display intro screen */\n"
"void setup()\n"
"{\n"
"  memload(0x10000, 0, 32768);\n"
"  lang = inb(0x11000) && (inb(16) != inb(0x10000) || inb(17) != inb(0x10001)) ? 1 : 0;\n"
"  memcpy(&colors, 0x10FB0, 5);\n"
"  memcpy(&textpos, 0x10FB5, 1);\n"
"  memcpy(&logic, 0x10FB6, 74);\n"
"  memcpy(&msg, 0x10002 + lang * 4096, 750);\n"
"  memcpy(&ans, 0x101B0 + lang * 4096, 256);\n"
"  memcpy(&verb, 0x102B0 + lang * 4096, 1536);\n"
"  memcpy(&noun, 0x108B0 + lang * 4096, 1536);\n"
"  cls(colors[0]);\n"
"  spr(32, 2, 128, 32, textpos > 96 ? 12 : textpos/8, 0, 0);\n"
"  custom_intro();\n"
"  text(colors[1], 40, textpos, 1, 0, 0, &msg);\n"
"  reset_game();\n"
"}\n"
"\n"
"/* display prompt and parse user input */\n"
"void loop()\n"
"{\n"
"  frect(colors[2], 4, textpos, 315, 195);\n"
"  outw(0x49A, 4); outw(0x49C, textpos);\n"
"  if(inp[0]) {\n"
"    outb(0x498, colors[4]);\n"
"    printf(\"> %%s\\n\", &inp);\n"
"  }\n"
"  if(say <= 20) {\n"
"    outw(0x49A, 4); outb(0x498, colors[3]);\n"
"    printf(\"%%s\\n\", say < 4 ? &ans[say * 64] : &msg[(say - 4) * 128]);\n"
"  }\n"
"  if(!rst) {\n"
"    outw(0x49A, 4); outb(0x498, colors[4]); printf(\"> \");\n"
"    parse_cmd(gets());\n"
"  } else reset_game();\n"
"}\n";

int line;
char *vars[256] = { 0 };

/**
 * Helper to skip comments
 */
uint8_t *json_iscomment(uint8_t *src, uint8_t *end)
{
    if(src[0] == '/' && src[1] == '*')
        for(src += 2; src < end && (src[-2] != '*' || src[-1] != '/'); src++) if(*src == '\n') line++;
    if(src[0] == '/' && src[1] == '/')
        for(src += 2; src < end && *src != '\n'; src++);
    if(*src == '\n') line++;
    return src;
}

/**
 * Helper to skip characters
 */
uint8_t *json_skip(uint8_t *src, uint8_t *end, uint8_t delim1, uint8_t delim2)
{
    for(;src < end && *src != delim1 && *src != delim2 && *src != '}' && !(*src >= '0' && *src <= '9'); src++)
        src = json_iscomment(src, end);
    return src;
}

/**
 * Helper to copy unescaped string
 */
uint8_t *json_unescape(char *dst, uint8_t *src, uint8_t *end, int len)
{
    uint8_t *ptr;
    int l;

    memset(dst, 0, len);
    src = json_skip(src, end, '\"', ']');
    if(*src == '\"') {
        for(ptr = ++src; src < end && *src != '\"'; src++) if(*src == '\n') line++;
        if(*src == '\"') {
            for(l = 0; ptr < src && l + 1 < len; ptr++) {
                if(*ptr == '\\') {
                    ptr++;
                    switch(*ptr) {
                        case 't': dst[l++] = '\t'; break;
                        case 'n': dst[l++] = '\n'; break;
                        case '\\': dst[l++] = '\\'; break;
                        case '\'': dst[l++] = '\''; break;
                        case '\"': dst[l++] = '\"'; break;
                        default: break;
                    }
                } else
                if(*ptr == '\n' || *ptr >= 32) dst[l++] = *ptr;
            }
            if(l >= len - 1 && ptr < src) fprintf(stderr, "converter: line %u: string truncated to %u bytes\r\n", line, l);
            dst[l] = 0;
            src++;
        }
    }
    return src;
}

/**
 * Helper to parse opcodes
 */
uint8_t *json_opcodes(uint8_t *dst, uint8_t *src, uint8_t *end, int len, int n, int l)
{
    static char *err[] = { "argument", "music", "sound effect", "variable", "value", "message", "room" };
    uint8_t op[8];
    int i, j, k, m, o, p, e;

    for(i = 0; src < end && *src != ']' && *src != '}' && i < len - 1; src++) {
        src = json_iscomment(src, end);
        for(k = 0; k < (int)(sizeof(ops)/sizeof(ops[0])); k++) {
            if(!memcmp(src, ops[k].op, ops[k].len) && (src[ops[k].len] == '\"' || src[ops[k].len] <= ' ')) {
                j = 1; e = 0; op[0] = k; src += ops[k].len;
                for(m = 0; m < 3 && ops[k].arg[m]; m++) {
                    while(src < end && *src == ' ') src++;
                    if(strchr("\",;\r\n]}", *src)) { e = 1; break; }
                    switch(ops[k].arg[m]) {
                        case ARG_MUS:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(o > 7) e = 2; else op[j++] = o;
                        break;
                        case ARG_SFX:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(o > 63) e = 3; else op[j++] = o;
                        break;
                        case ARG_VAR:
                            if(*src >= '0' && *src <= '9') {
                                o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            } else
                                for(o = 0; o < 256; o++) {
                                    p = vars[o] ? strlen(vars[o]) : 0;
                                    if(p && !memcmp(src, vars[o], p) && (src[p] == '\"' || src[p] == ' ')) {
                                        src += p; break;
                                    }
                                }
                            if(!o || o > 255) e = 4; else op[j++] = o;
                        break;
                        case ARG_VAL:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(o > 255) e = 5; else op[j++] = o;
                        break;
                        case ARG_MSG:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(!o || o > 16) e = 6; else op[j++] = o - 1;
                        break;
                        case ARG_ROOM:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(!o || o > 254 || !meg4.ovls[o].data) e = 7; else op[j++] = o;
                        break;
                    }
                }
                if(e)
                    fprintf(stderr, "converter: line %u: bad %s in script %u in room %u: %s %s\r\n", line, ops[k].op, n, l,
                        e == 1 ? "missing" : (e == 5 ? "out of bounds" : "no such"), err[e - 1]);
                else
                if(i + j < len - 1) { memcpy(dst + i, op, j); i += j; }
                else {
                    fprintf(stderr, "converter: line %u: not enough buffer for %s script %u in room %u\r\n", line, ops[k].op, n, l);
                    break;
                }
            }
        }
    }
    return src;
}

/**
 * Import AdvGame JSON
 */
int main_advgame(char *fn, uint8_t *buf, int len)
{
    ag_conf_t *game = (ag_conf_t*)meg4.mmio.sprites;
    ag_room_t *room;
    ag_cmds_t *cmds;
    char tmp[4096], *verbs[NUMVERB] = { 0 }, *nouns[NUMNOUN] = { 0 }, *comment = NULL, custom[2][4096] = { "", "" };
    FILE *f;
    uint8_t *end = buf + len, *img, *s, *e, *iend;
    int i, j, k, l, m, n, p, flen, size;

    line = 1;

    /* check arguments */
    if(!fn || !buf || len < 13) return 0;
    /* skip optional leading comment and check magic */
    if(buf[0] == '/' && buf[1] == '*') { comment= (char*)buf; buf = json_skip(buf, end, '\"', 0); }
    if(memcmp(buf, "\"AdvGame\"", 9)) return 0;

    /* get path from JSON file's name */
    flen = strlen(fn);
    while(flen > 0 && fn[flen - 1] != '/') flen--;
    if(flen > 0) {
        memcpy(tmp, fn, flen);
        if(tmp[flen - 1] != '/') tmp[flen++] = '/';
    }

    /* collect defined rooms in advance */
    for(s = buf + 9, l = line; s < end; s++) {
        if(*s == '\n') l++;
        if(s[0] == '\"' && s[1] >= '0' && s[1] <= '9') {
            s++; i = atoi((char*)s);
            if(i > 0 && i < 255) {
                if(meg4.ovls[i].data)
                    fprintf(stderr, "converter: line %u: duplicate room %u\r\n", l, i);
                meg4.ovls[i].size = 32768;
                if((meg4.ovls[i].data = (uint8_t*)realloc(meg4.ovls[i].data, 32768)))
                    memset(meg4.ovls[i].data, 0, 32768);
                else meg4.ovls[i].size = 0;
            }
        }
    }

    /* parse JSON */
    vars[0] = "room";
    for(buf += 9; buf < end; buf++) {

        /* skip comments */
        buf = json_iscomment(buf, end);

        /* sprites key */
        if(!memcmp(buf, "\"sprites\"", 9)) {
            buf = json_unescape(tmp + flen, buf + 9, end, 256);
            f = fopen(tmp, "rb");
            if(f) {
                fseek(f, 0, SEEK_END);
                size = (int)ftell(f);
                fseek(f, 0, SEEK_SET);
                img = malloc(size);
                if(img) fread(img, 1, size, f);
                fclose(f);
                if(img) {
                    if(!memcmp(img, "\x89PNG", 4)) {
                        i = ((img[18] << 8) | img[19]); j = ((img[22] << 8) | img[23]);
                        if(i == 256 && j == 256) {
                            for(s = img + 8, iend = img + size, k = l = 1; s < iend - 12 && k > 0; s += k + 12) {
                                k = ((s[0] << 24) | (s[1] << 16) | (s[2] << 8) | s[3]);
                                /* indexed png, also load the palette */
                                if(!memcmp(s + 4, "PLTE", 4)) {
                                    memset(meg4.mmio.palette, 0, sizeof(meg4.mmio.palette));
                                    memset(meg4.mmio.sprites, 0, sizeof(meg4.mmio.sprites));
                                    for(s += 8, e = s + k + 4, i = 0; s < e - 4 && i < 256; i++, s += 3)
                                        meg4.mmio.palette[i] = (0xff << 24) | (s[2] << 16) | (s[1] << 8) | s[0];
                                    if(!memcmp(e + 4, "tRNS", 4)) {
                                        k = ((e[0] << 24) | (e[1] << 16) | (e[2] << 8) | e[3]); if(k > 256) k = 256;
                                        for(i = 0, e += 8; i < k; i++, e++)
                                            *((uint8_t*)&meg4.mmio.palette[i] + 3) = e[0];
                                    }
                                    if((s = (uint8_t*)stbi_load_from_memory(img, size, &i, &j, &k, 1))) {
                                        i *= j; if(i > (int)sizeof(meg4.mmio.sprites)) i = sizeof(meg4.mmio.sprites);
                                        memcpy(meg4.mmio.sprites, s, i);
                                        free(s);
                                    } else l = 0;
                                }
                            }
                            if(!l) {
                                /* no palette chunk, this must be a truecolor image */
                                if((s = (uint8_t*)stbi_load_from_memory(img, size, &i, &j, &k, 4))) {
                                    memcpy(meg4.mmio.palette, default_pal, sizeof(meg4.mmio.palette));
                                    memset(meg4.mmio.sprites, 0, sizeof(meg4.mmio.sprites));
                                    for(j = k = 0, e = s; j < 256; j++)
                                        for(i = 0; i < 256; i++, k++, e += 4)
                                            meg4.mmio.sprites[k] = meg4_palidx(e);
                                    free(s);
                                }
                            }
                        } else
                            fprintf(stderr, "converter: line %u: not 256 x 256 pixels '%s'\r\n", line, tmp);
                    } else
                        fprintf(stderr, "converter: line %u: not a PNG '%s'\r\n", line, tmp);
                    free(img);
                }
            } else
                fprintf(stderr, "converter: line %u: unable to load '%s'\r\n", line, tmp);
            memset(meg4.mmio.sprites, 0, 2*sizeof(ag_conf_t));
        } else

        /* setup key */
        if(!memcmp(buf, "\"setup\"", 7)) {
            for(buf += 7, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '}');
                if(*buf < '0' || *buf > '9') break;
                if(i < 256) game[0].setup[i] = atoi((char*)buf); else j = 1;
                while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 256);
        } else

        /* colors key */
        if(!memcmp(buf, "\"colors\"", 8)) {
            for(buf += 8, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '}');
                if(*buf < '0' || *buf > '9') break;
                if(i < 5) game[0].colors[i] = atoi((char*)buf); else j = 1;
                while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 5);
        } else

        /* text position */
        if(!memcmp(buf, "\"textpos\"", 9)) {
            buf = json_skip(buf + 9, end, ',', 0);
            game[0].textpos = atoi((char*)buf);
        } else

        /* custom ui code */
        if(!memcmp(buf, "\"custom\"", 8)) {
            for(buf += 8, i = 0; buf < end && *buf != ']' && i < 2; i++)
                buf = json_unescape(custom[i], buf, end, sizeof(custom[0]));
            for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
            if(*buf != ']' && i >= 2) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 2); }
        } else

        /* verbs (JSON-only aliases) */
        if(!memcmp(buf, "\"verbs\"", 7)) {
            for(buf += 7, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '\"');
                if(*buf != '\"') break; else buf++;
                if(i < NUMVERB) verbs[i] = (char*)buf; else j = 1;
                buf = json_skip(buf, end, ']', '\"');
                *buf++ = 0;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, NUMVERB);
        } else

        /* nouns (JSON-only aliases) */
        if(!memcmp(buf, "\"nouns\"", 7)) {
            for(buf += 7, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '\"');
                if(*buf != '\"') break; else buf++;
                if(i < NUMNOUN) nouns[i] = (char*)buf; else j = 1;
                buf = json_skip(buf, end, ']', '\"');
                *buf++ = 0;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, NUMNOUN);
        } else

        /* variables (JSON-only aliases) */
        if(!memcmp(buf, "\"vars\"", 6)) {
            for(buf += 6, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '\"');
                if(*buf != '\"') break; else buf++;
                if(i < 256) vars[i] = (char*)buf; else j = 1;
                buf = json_skip(buf, end, ']', '\"');
                *buf++ = 0;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 256);
        } else

        /* common game logic for all rooms */
        if(!memcmp(buf, "\"logic\"", 7)) {
            buf = json_opcodes(game[0].logic, buf + 7, end, 74, 0, 0);
        } else

        /* configurations */
        if(!memcmp(buf, "\"config", 7)) {
            l = buf[7] == '1' ? 1 : 0;
            buf = json_skip(buf + 8, end, '{', '}');
            for(buf++; buf < end && *buf != '}'; buf++) {
                buf = json_iscomment(buf, end);
                /* config properties */
                if(!memcmp(buf, "\"lang\"", 6)) {
                    buf = json_skip(buf + 6, end, '\"', 0);
                    if(*buf == '\"') { game[l].lang[0] = buf[1]; game[l].lang[1] = buf[2]; buf += 4; }
                } else
                if(!memcmp(buf, "\"text\"", 6))     buf = json_unescape(game[l].text, buf + 6, end, sizeof(game[0].text)); else
                if(!memcmp(buf, "\"answers\"", 9)) {
                    for(buf += 9, i = 0; buf < end && *buf != ']' && *buf != '}' && i < 4; i++)
                        buf = json_unescape(game[l].answ[i], buf, end, sizeof(game[0].answ[0]));
                    for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
                    if(*buf != ']' && i >= 4) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 4); }
                } else
                if(!memcmp(buf, "\"save\"", 6))  { buf += 6; j = 0; goto readverb; } else
                if(!memcmp(buf, "\"load\"", 6))  { buf += 6; j = 1; goto readverb; } else
                if(!memcmp(buf, "\"north\"", 7)) { buf += 7; j = 2; goto readverb; } else
                if(!memcmp(buf, "\"west\"", 6))  { buf += 6; j = 3; goto readverb; } else
                if(!memcmp(buf, "\"east\"", 6))  { buf += 6; j = 4; goto readverb; } else
                if(!memcmp(buf, "\"south\"", 7)) { buf += 7; j = 5; goto readverb; } else
                if(!memcmp(buf, "\"up\"", 4))    { buf += 4; j = 6; goto readverb; } else
                if(!memcmp(buf, "\"down\"", 6))  { buf += 6; j = 7; goto readverb; } else
                if(!memcmp(buf, "\"nouns\"", 7)) {
                    for(buf += 7, i = 0; buf < end && *buf != ']' && *buf != '}' && i < NUMNOUN; i++)
                        buf = json_unescape(game[l].noun[i], buf, end, sizeof(game[0].noun[0]));
                    for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
                    if(*buf != ']' && i >= NUMNOUN) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, NUMNOUN); }
                } else
                if(!memcmp(buf, "\"verb", 5)) {
                    buf += 5; j = atoi((char*)buf);
                    while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
                    buf = json_skip(buf, end, '[', 0);
                    if(j >= 1 && j <= NUMVERB) {
                        j += 7;
readverb:               for(i = 0; buf < end && *buf != ']' && *buf != '}' && i < 4; i++)
                            buf = json_unescape(game[l].verb[j][i], buf, end, sizeof(game[0].verb[0][0]));
                        for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
                        if(*buf != ']' && i >= 4) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 4); }
                    } else { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: bad verb %u\r\n", line, j); }
                } else
                if(*buf == '\"') {
                    for(buf++, i = 0; i < NUMVERB; i++) {
                        j = verbs[i] ? strlen(verbs[i]) : 0;
                        if(j && !memcmp(buf, verbs[i], j) && buf[j] == '\"') { buf += j + 1; j = i + 8; goto readverb; }
                    }
                }
            }
        } else

        /* room definitions */
        if(buf[0] == '\"' && buf[1] >= '0' && buf[1] <= '9') {
            buf++; l = atoi((char*)buf);
            if(l > 0 && l < 255) {
                memset(meg4.ovls[l].data, 0, 32768);
                room = (ag_room_t*)meg4.ovls[l].data;
                for(buf++, n = 0; buf < end && *buf != '}'; buf++) {
                    buf = json_iscomment(buf, end);
                    /* room properties */
                    if(!memcmp(buf, "\"image\"", 7)) {
                        buf = json_unescape(tmp + flen, buf + 7, end, 256);
                        f = fopen(tmp, "rb");
                        if(f) {
                            fseek(f, 0, SEEK_END);
                            size = (int)ftell(f);
                            fseek(f, 0, SEEK_SET);
                            img = malloc(size);
                            if(img) fread(img, 1, size, f);
                            fclose(f);
                            if(img) {
                                if(!memcmp(img, "\x89PNG", 4)) {
                                    m = ((img[18] << 8) | img[19]); p = ((img[22] << 8) | img[23]);
                                    if(m <= 256 && p <= 96) {
                                        if((s = (uint8_t*)stbi_load_from_memory(img, size, &m, &p, &k, 4))) {
                                            for(j = 0, e = s; j < p; j++)
                                                for(i = 0; i < m; i++, e += 4)
                                                    meg4.ovls[l].data[(32 + j) * 256 + i] = meg4_palidx(e);
                                            free(s);
                                        }
                                    } else
                                        fprintf(stderr, "converter: line %u: maximum 256 x 96 pixels '%s'\r\n", line, tmp);
                                } else
                                    fprintf(stderr, "converter: line %u: not a PNG '%s'\r\n", line, tmp);
                                free(img);
                            }
                        } else
                            fprintf(stderr, "converter: line %u: unable to load '%s'\r\n", line, tmp);
                    } else
                    if(!memcmp(buf, "\"north\"", 7)) { buf += 7; j = 0; goto readdir; } else
                    if(!memcmp(buf, "\"west\"", 6))  { buf += 6; j = 1; goto readdir; } else
                    if(!memcmp(buf, "\"east\"", 6))  { buf += 6; j = 2; goto readdir; } else
                    if(!memcmp(buf, "\"south\"", 7)) { buf += 7; j = 3; goto readdir; } else
                    if(!memcmp(buf, "\"up\"", 4))    { buf += 4; j = 4; goto readdir; } else
                    if(!memcmp(buf, "\"down\"", 6))  {
                        buf += 6; j = 5;
readdir:                buf = json_skip(buf, end, '[', 0);
                        if(*buf == '[') {
                            if(n >= 63)
                                fprintf(stderr, "converter: line %u: too many scripts in room %u\r\n", line, l);
                            else {
                                room->dir[j] = 255;
                                cmds = &room->cmds[n++];
                                cmds->verb = 0x80 | j;
                                buf = json_opcodes(cmds->op, buf, end, 61, n, l);
                            }
                        } else {
                            i = atoi((char*)buf);
                            if(i >= 255 || (!i && !meg4.ovls[i].data)) {
                                fprintf(stderr, "converter: line %u: invalid navigation to %u in room %u\r\n", line, i, l);
                                i = 0;
                            }
                            room->dir[j] = i;
                        }
                    } else
                    if(!memcmp(buf, "\"text", 5)) {
                        j = buf[5] == '1' ? 1 : 0;
                        buf = json_skip(buf + 6, end, '[', ']');
                        for(i = 0; buf < end && *buf != ']' && *buf != '}' && i < 16; i++)
                            buf = json_unescape(room->msg[j][i], buf, end, 128);
                        for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
                        if(*buf != ']' && i >= 16) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 16); }
                    } else
                    if(!memcmp(buf, "\"logic\"", 7)) { buf += 7; j = 0; goto readops; } else
                    if(!memcmp(buf, "\"verb", 5)) {
                        buf += 5; j = atoi((char*)buf);
                        while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
                        buf = json_skip(buf, end, '[', ']');
readops:                if(j >= 0 && j <= NUMVERB) {
                            cmds = NULL;
                            if(!j) cmds = &room->cmds[0]; else {
                                if(n >= 63)
                                    fprintf(stderr, "converter: line %u: too many scripts in room %u\r\n", line, l);
                                else {
                                    cmds = &room->cmds[n++];
                                    cmds->verb = j;
                                    if(*buf == ' ') {
                                        buf++;
                                        if(*buf >= '0' && *buf <= '9') {
                                            cmds->noun1 = atoi((char*)buf);
                                            while(buf < end && *buf >= '0' && *buf <= '9') buf++;
                                        } else
                                            for(i = 0; i < NUMNOUN; i++) {
                                                k = nouns[i] ? strlen(nouns[i]) : 0;
                                                if(k && !memcmp(buf, nouns[i], k) && (buf[k] == '\"' || buf[k] == ' ')) {
                                                    buf += k; cmds->noun1 = i + 1; break;
                                                }
                                            }
                                        if(*buf == ' ') {
                                            buf++;
                                            if(*buf >= '0' && *buf <= '9') {
                                                cmds->noun2 = atoi((char*)buf);
                                                while(buf < end && *buf >= '0' && *buf <= '9') buf++;
                                            } else
                                                for(i = 0; i < NUMNOUN; i++) {
                                                    k = nouns[i] ? strlen(nouns[i]) : 0;
                                                    if(k && !memcmp(buf, nouns[i], k) && (buf[k] == '\"' || buf[k] == ' ')) {
                                                        buf += k; cmds->noun2 = i + 1; break;
                                                    }
                                                }
                                        }
                                    }
                                    for(i = 0; i < n - 1; i++)
                                        if(room->cmds[i].verb == cmds->verb &&
                                          room->cmds[i].noun1 == cmds->noun1 && room->cmds[i].noun2 == cmds->noun2) {
                                            fprintf(stderr, "converter: line %u: duplicate script 'verb%u %u %u' in room %u\r\n",
                                                line, cmds->verb, cmds->noun1, cmds->noun2, l);
                                            break;
                                        }
                                }
                            }
                            if(cmds) buf = json_opcodes(cmds->op, buf, end, 61, j ? n : 0, l);
                        } else
                            fprintf(stderr, "converter: line %u: invalid verb %u in room %u\r\n", line, j, l);
                    } else
                    if(*buf == '\"')
                        for(buf++, i = 0; i < NUMVERB; i++) {
                            j = verbs[i] ? strlen(verbs[i]) : 0;
                            if(j && !memcmp(buf, verbs[i], j) && buf[j] == '\"') { buf += j + 1; j = i + 1; goto readops; }
                        }
                }
            } else
                fprintf(stderr, "converter: line %u: invalid room number %u\r\n", line, l);
        }
    }

    /* save game configuration to overlay */
    meg4.ovls[0].size = 32768;
    if((meg4.ovls[0].data = (uint8_t*)realloc(meg4.ovls[0].data, meg4.ovls[0].size))) {
        memcpy(meg4.ovls[0].data, meg4.mmio.sprites, meg4.ovls[0].size);
    } else meg4.ovls[0].size = 0;

    /* add game interpreter */
    if(comment) { for(s = (uint8_t*)comment + 3; memcmp(s - 3, "*/\n", 3); s++) {} *s = 0; } else comment = "";
    if((meg4.src = (char*)realloc(meg4.src, strlen(program) + strlen(comment) + strlen(custom[0]) + strlen(custom[1]) + 1)))
        meg4.src_len = sprintf(meg4.src, program, comment, custom[0], custom[1]) + 1;
    else meg4.src_len = 0;

    return 1;
}
