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

/* do not change these unless you know what you're doing! Must change "program" string too */
#define NUMVERB 32
#define NUMNOUN 255
#define NUMMSG  32

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
} __attribute__((packed))  ag_conf_t;
extern char c_assert1[sizeof(ag_conf_t) == 4096 ? 1 : -1];

/* stored in overlays 1 to 254 */
typedef struct {
    uint8_t     verb;           /* verb to match, 1 to 32 */
    uint8_t     noun1;          /* noun to match, 0 (none) to 255 */
    uint8_t     noun2;          /* noun to match, 0 (none) to 255 */
    uint8_t     op[61];         /* script operands */
} __attribute__((packed)) ag_cmds_t;

typedef struct {
    char        msg[2][2048];   /* text messages */
    uint8_t     dir[6];         /* navigation, room numbers or 0 if none / 255 if script */
    ag_cmds_t   cmds[63];       /* commands understood in this room (script list) */
} __attribute__((packed)) ag_room_t;
extern char c_assert2[sizeof(ag_room_t) <= 8192 ? 1 : -1];

/* directions */
static char *dirs[6] = { "north", "west", "east", "south", "up", "down" };

/* script opcodes */
enum { ARG_NONE, ARG_IF, ARG_CND, ARG_VAR, ARG_NUM, ARG_MUS, ARG_SFX, ARG_SCR, ARG_MSG, ARG_ROOM, ARG_NOUN };
typedef struct { char *op; int len, arg[6]; } ag_ops_t;
static ag_ops_t ops[] = {
 /*  0 */ { "end",   3, { ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE, ARG_NONE } },
 /*  1 */ { "and",   3, { ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE, ARG_NONE } },
 /*  2 */ { "or",    2, { ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE, ARG_NONE } },
 /*  3 */ { "bgm",   3, { ARG_MUS,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /*  4 */ { "sfx",   3, { ARG_SFX,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /*  5 */ { "jmp",   3, { ARG_ROOM, ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /*  6 */ { "jmpv",  4, { ARG_VAR,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /*  7 */ { "call",  4, { ARG_SCR,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /*  8 */ { "callv", 5, { ARG_VAR,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /*  9 */ { "give",  4, { ARG_NOUN, ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /* 10 */ { "take",  4, { ARG_NOUN, ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /* 11 */ { "say",   3, { ARG_MSG,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM,  ARG_NONE } },
 /* 12 */ { "sayv",  4, { ARG_VAR,  ARG_MSG,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } },
 /* 13 */ { "sayc",  4, { ARG_MSG,  ARG_MSG,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } },
 /* 14 */ { "add",   3, { ARG_VAR,  ARG_NUM,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } },
 /* 15 */ { "addv",  4, { ARG_VAR,  ARG_VAR,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } },
 /* 16 */ { "sub",   3, { ARG_VAR,  ARG_NUM,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } },
 /* 17 */ { "subv",  4, { ARG_VAR,  ARG_VAR,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } },
 /* 18 */ { "set",   3, { ARG_VAR,  ARG_NUM,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } },
 /* 19 */ { "rnd",   3, { ARG_VAR,  ARG_NUM,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } },
 /* 20 */ { "mov",   3, { ARG_VAR,  ARG_VAR,  ARG_IF,   ARG_VAR,  ARG_CND,  ARG_NUM  } }
};
static char *cnds[] = { "=", "!=", "<=", "<", ">" };

/* the MEG-4 Adventure Game Interpreter program (will be added to the output so that MEG-4 can run the project) */
static char *program = "#!c\n\n"
"/**\n"
" * Adventure Game Engine - MEG-4 DEMO\n"
" * Copyright (c) bzt 2024 CC-0\n"
" */\n%s\n"
"/* variables */\n"
"uint8_t lang, state[256], stat[2], colors[5], textpos, logic[4104], dir[8], cmd[4096], com[1024], say, say2, say3, rst;\n"
"char ans[256], verb[1536], noun[1536], msg[4096], inp[256];\n"
"uint16_t midx[64];\n\n"
"/* customize your UI here */\n"
"void custom_intro()\n{\n%s\n}\n"
"void custom_room()\n{\n%s\n}\n\n"
"/* function to parse and execute opcodes */\n"
"void parse_ops(uint8_t *c)\n"
"{\n"
"  uint8_t op, cnd, arg1, arg2, p, l;\n"
"  p = l = 0;\n"
"  while(*c) {\n"
"    op = *c++;\n"
"    switch(op & 7) {\n"
"       case 0: cnd = 1; break;\n"
"       case 1: arg1 = *c++; arg2 = *c++; cnd = state[arg1] == arg2; break;\n"
"       case 2: arg1 = *c++; arg2 = *c++; cnd = state[arg1] != arg2; break;\n"
"       case 3: arg1 = *c++; arg2 = *c++; cnd = state[arg1] <= arg2; break;\n"
"       case 4: arg1 = *c++; arg2 = *c++; cnd = state[arg1] < arg2; break;\n"
"       case 5: arg1 = *c++; arg2 = *c++; cnd = state[arg1] > arg2; break;\n"
"       case 6: arg1 = *c++; cnd = state[255 - (arg1 >> 3)] & (1 << (arg1 & 7)); break;\n"
"       case 7: arg1 = *c++; cnd = !(state[255 - (arg1 >> 3)] & (1 << (arg1 & 7))); break;\n"
"    }\n"
"    if(p == 1) cnd = cnd && l; else if(p == 2) cnd = cnd || l;\n"
"    p = l = 0;\n"
"    switch(op >> 3) {\n"
"      case  1: p = 1; l = cnd; break;\n"
"      case  2: p = 2; l = cnd; break;\n"
"      case  3: arg1 = *c++; if(cnd && arg1 < 8) music(arg1, 0, 128); break;\n"
"      case  4: arg1 = *c++; if(cnd && arg1 < 64) sfx(arg1, 0, 255); break;\n"
"      case  5: arg1 = *c++; if(cnd && arg1 < 255) {load_room(arg1); return; } break;\n"
"      case  6: arg1 = *c++; if(cnd && state[arg1] < 255) {load_room(state[arg1]); return; } break;\n"
"      case  7: arg1 = *c++; if(cnd && arg1 < 63) parse_ops(&logic[77 + arg1 * 64]); break;\n"
"      case  8: arg1 = *c++; if(cnd && state[arg1] < 63) parse_ops(&logic[77 + state[arg1] * 64]); break;\n"
"      case  9: arg1 = *c++; if(cnd) state[255 - (arg1 >> 3)] |= (1 << (arg1 & 7)); break;\n"
"      case 10: arg1 = *c++; if(cnd) state[255 - (arg1 >> 3)] &= ~(1 << (arg1 & 7)); break;\n"
"      case 11: arg1 = *c++; if(cnd && arg1 < 32) { say2 = say; say = arg1 + 4 + say3; } break;\n"
"      case 12: arg1 = *c++; arg2 = *c++; arg2 += state[arg1]; if(cnd && arg2 < 32) { say2 = say; say = arg2 + 4 + say3; } break;\n"
"      case 13: arg1 = *c++; arg2 = *c++; if(arg1 < 32 && arg2 < 32) { say2 = say; say = (cnd ? arg2 : arg1) + 4 + say3; } break;\n"
"      case 14: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg1] + arg2 < 255 ? state[arg1] + arg2 : 255; break;\n"
"      case 15: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg1] + state[arg2] < 255 ? state[arg1] + state[arg2] : 255; break;\n"
"      case 16: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg1] > arg2 ? state[arg1] - arg2 : 0; break;\n"
"      case 17: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg1] > state[arg2] ? state[arg1] - state[arg2] : 0; break;\n"
"      case 18: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = arg2; break;\n"
"      case 19: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = rand() %% arg2; break;\n"
"      case 20: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg2]; break;\n"
"    }\n"
"    if(!(op >> 3) && cnd) break;\n"
"  }\n"
"}\n"
"\n"
"/* function to load a room */\n"
"void load_room(int r)\n"
"{\n"
"  int i, m, l;\n"
"  if(state[0] == r || r == 255) return;\n"
"  if(!r) { inp[0] = 0; rst = 1; return; }\n"
"  state[0] = r;\n"
"  memload(0x10000, r, 32768);\n"
"  memcpy(&msg, 0x10000 + lang * 2048, 2048);\n"
"  memcpy(&dir, 0x11000, 6);\n"
"  memcpy(&cmd, 0x11006, 4096);\n"
"  memset(&midx, 0, 64);\n"
"  for(m = i = 0, l = 1; i < 32 && m < 2048 && l > 0; i++, m += l + 1) { midx[i] = m; l = strlen(&msg[m]); }\n"
"  inp[0] = 0; say = 255; say2 = say3 = 0;\n"
"  parse_ops(&cmd[3]);\n"
"  cls(colors[2]);\n"
"  spr(32, 2, 128, 32, textpos > 96 ? 12 : textpos/8, 0, 0);\n"
"  if(stat[0]) printf(\" %%3u\", state[stat[0]]);\n"
"  if(stat[1]) printf(\" %%3u\", state[stat[1]]);\n"
"  custom_room();\n"
"}\n"
"\n"
"/* function to parse user input */\n"
"void parse_cmd(char *s)\n"
"{\n"
"  uint8_t v, n1, n2;\n"
"  int i, j, k, l, m, n;\n"
"  if(!s || !*s) { say = 255; return; }\n"
"  memcpy(&inp, s, 256);\n"
"  /* detect verb and noun(s) */\n"
"  v = 255; n1 = n2 = 0;\n"
"  for(i = n = 0; i < 255 && inp[i] && !n2;) {\n"
"    while(i < 255 && inp[i] == ' ') i++;\n"
"    if(v == 255)\n"
"      for(m = j = 0; j < 40; j++)\n"
"        for(k = 0; k < 8 && m < 1536; k++, m += l + 1) {\n"
"          l = strlen(&verb[m]);\n"
"          if(l > n && (mblen(&verb[m]) > 2 || !inp[i + l] || inp[i + l] == ' ') && !memcmp(&inp[i], &verb[m], l)) { v = j; n = l; }\n"
"        }\n"
"    for(m = j = 0, l = 1; j < 255 && m < 1536 && l; j++, m += l + 1) {\n"
"      l = strlen(&noun[m]);\n"
"      if(l && (mblen(&noun[m]) > 2 || !inp[i + l] || inp[i + l] == ' ') && !memcmp(&inp[i], &noun[m], l)) { j++; if(!n1) n1 = j; else n2 = j; break; }\n"
"    }\n"
"    while(i < 255 && inp[i] && inp[i] != ' ') i++;\n"
"  }\n"
"  parse_ops(&logic[0]);\n"
"  say = say2 = say3 = 0;\n"
"  /* built-in navigation verbs (might fall-through into room script case) */\n"
"  if(v >= 3 && v <= 8) {\n"
"    if(n1) { say = 2; return; } else v -= 3;\n"
"    if(dir[v] == 255) { v += 128; n1 = n2 = 0; }\n"
"    else { if(!dir[v]) say = 1; else load_room(dir[v]); return; }\n"
"  }\n"
"  /* built-in save, load game and list inventory verbs */\n"
"  if(v == 0) { say = memsave(255, &state, 256) ? 3 : 2; } else\n"
"  if(v == 1) { say = 2; memload(&state, 255, 256); v = state[0] ? state[0] : 1; state[0] = 255; load_room(v); } else\n"
"  if(v == 2) { say = 254; } else\n"
"  /* look for a script for this verb and noun(s) */\n"
"  if(v != 255) {\n"
"    /* room specific */\n"
"    for(say = 2, i = 64; i < 63*64; i += 64)\n"
"      if(cmd[i] == v && cmd[i + 1] == n1 && cmd[i + 2] == n2) { say = 255; parse_ops(&cmd[i + 3]); custom_room(); return; }\n"
"    /* common */\n"
"    for(i = 72; i < 4104; i += 64)\n"
"      if(logic[i] == v && logic[i + 1] == n1 && logic[i + 2] == n2) { say = 255; say3 = 32; parse_ops(&logic[i + 3]); custom_room(); return; }\n"
"  }\n"
"}\n"
"\n"
"/* wait for a keypress and force jump to the first room */\n"
"void reset_game()\n"
"{\n"
"  uint8_t r;\n"
"  getc();\n"
"  memload(0x10000, 0, 32768);\n"
"  memcpy(&state, 0x10EB0, 256);\n"
"  r = state[0] ? state[0] : 1;\n"
"  state[0] = 255; rst = 0;\n"
"  load_room(r);\n"
"}\n"
"\n"
"/* load game configuration and display intro screen */\n"
"void setup()\n"
"{\n"
"  int i, m, l;\n"
"  outw(0x14, PTR_NONE);\n"
"  memload(0x10000, 1, 32768);\n"
"  memcpy(&logic[72], 0x11046, 4032);\n"
"  memcpy(&msg[2048], 0x10000 + lang * 2048, 2048);\n"
"  memset(&midx[32], 0, 64);\n"
"  for(m = 2048, i = 32, l = 1; i < 64 && m < 4096 && l > 0; i++, m += l + 1) { midx[i] = m; l = strlen(&msg[m]); }\n"
"  memload(0x10000, 0, 32768);\n"
"  lang = inb(0x11000) && (inb(16) != inb(0x10000) || inb(17) != inb(0x10001)) ? 1 : 0;\n"
"  memcpy(&stat, 0x10FB0, 2);\n"
"  memcpy(&colors, 0x10FB2, 5);\n"
"  memcpy(&textpos, 0x10FB7, 1);\n"
"  memcpy(&logic, 0x10FB8, 72);\n"
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
"  int m, j, l;\n"
"  frect(colors[2], 4, textpos, 315, 195);\n"
"  outw(0x49A, 4); outw(0x49C, textpos);\n"
"  if(inp[0]) {\n"
"    outb(0x498, colors[4]);\n"
"    printf(\"> %%s\\n\", &inp);\n"
"  }\n"
"  if(say <= 68) {\n"
"    outb(0x498, colors[3]);\n"
"    if(say2 >= 4 && say2 <= 36) { outw(0x49A, 4); printf(\"%%s\\n\\n\", &msg[midx[say2 - 4]]); }\n"
"    outw(0x49A, 4); printf(\"%%s\\n\", say < 4 ? &ans[say * 64] : &msg[midx[say - 4]]);\n"
"  } else\n"
"  if(say == 254) {\n"
"    outb(0x498, colors[3]); outw(0x49A, 0);\n"
"    for(m = 0, j = l = 1; j < 256 && m < 1536 && l; j++, m += l + 1)\n"
"      if((l = strlen(&noun[m])) && state[255 - (j >> 3)] & (1 << (j & 7))) {\n"
"        if(inw(0x49A) + width(1, &noun[m]) > 308) printf(\"\\n\");\n"
"        printf(\" %%s\", &noun[m]);\n"
"      }\n"
"    printf(\"\\n\");\n"
"  }\n"
"  if(!rst) {\n"
"    outw(0x49A, 4); outb(0x498, colors[4]); printf(\"> \");\n"
"    parse_cmd(gets());\n"
"  } else reset_game();\n"
"}\n";

/* global variables needed for compiling the JSON */
extern int isbinary;
int line, varslen[256] = { 0 }, roomslen[254] = { 0 }, nounslen[NUMNOUN] = { 0 }, numinst = 0;
char *vars[256] = { 0 }, *rooms[254] = { 0 }, roomref[256] = { 0 }, *nouns[NUMNOUN] = { 0 };

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
    int l;

    memset(dst, 0, len); len--;
    src = json_skip(src, end, '\"', ']');
    if(*src == '\"') {
        for(l = 0, src++; *src && *src != '\"'; src++) {
            if(*src == '\n') line++;
            if(*src == '\\') {
                src++;
                if(l < len)
                    switch(*src) {
                        case 't': dst[l++] = '\t'; break;
                        case 'n': dst[l++] = '\n'; break;
                        case '\\': dst[l++] = '\\'; break;
                        case '\'': dst[l++] = '\''; break;
                        case '\"': dst[l++] = '\"'; break;
                        default: break;
                    }
            } else
            if((*src == '\n' || *src >= 32) && l < len) dst[l++] = *src;
        }
        if(l >= len) fprintf(stderr, "converter: line %u: string truncated to %u bytes\r\n\"%s\"\r\n", line, len, dst);
        if(*src == '\"') src++;
    }
    return src;
}

/**
 * Helper, convert UTF-8 to UNICODE codepoint
 */
char *json_utf8(char *str, uint32_t *out)
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
 * Helper to wrap text (uses MEG-4 built-in proportional font to calculate line width in pixels)
 */
void json_wrap(char *dst, char *src, int len)
{
    uint32_t c;
    char *bef;
    int space = 0, l, s, w = 0, o = 0;

    memset(dst, 0, len);
    for(l = 0; l + 1 < len && *src;) {
        bef = src; src = json_utf8(src, &c);
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
        if(w > 310 && space > 0) {
            memmove(dst + space + 1, dst + space, l - space + 1);
            dst[space] = '\n'; space = 0; w -= o; l++;
        }
        s = (uintptr_t)src - (uintptr_t)bef;
        if(s > 0) {
            if(l + s + 1 >= len) { dst[l] = 0; l = len - 1; break; }
            memcpy(dst + l, bef, s); l += s;
        }
    }
    dst[l] = 0;
    if(l >= len - 1) fprintf(stderr, "converter: line %u: string truncated to %u bytes\r\n\"%s\"\r\n", line, l, dst);
}

/**
 * Helper to return a line (or word) for error reporting
 */
char *json_line(uint8_t *str, char sep)
{
    static char tmp[256];
    int i;

    for(i = 0; i < 255 && str[i] && str[i] != sep && !strchr("\r\n\",[]{}", str[i]); i++)
        tmp[i] = str[i];
    tmp[i] = 0;
    return tmp;
}

/**
 * Helper to parse script opcodes from mnemonics
 */
uint8_t *json_opcodes(uint8_t *dst, uint8_t *src, uint8_t *end, int len, int n, int l, int nt)
{
    static char *err[] = { "argument", "condition", "music", "sound effect", "script", "variable", "value", "message", "room", "noun" };
    uint8_t op[8];
    int i, j, k, m, o, p, e, t, h, c, r;

    for(i = 0; src < end && *src != ']' && *src != '}' && i < len - 1; src++) {
        for(; src < end && strchr(":[\",\r\n /", *src); src++) src = json_iscomment(src, end);
        if(src == end || *src == ']' || *src == '}') break;
        for(k = 0; k < (int)(sizeof(ops)/sizeof(ops[0])); k++) {
            /* if instruction mnemonic found */
            if(!memcmp(src, ops[k].op, ops[k].len) && (src[ops[k].len] == '\"' || src[ops[k].len] <= ' ')) {
                j = t = 1; e = h = r = c = 0; op[0] = k << 3; src += ops[k].len;
                /* iterate on arguments (k: opcode, t: total length, j: next argument's position) */
                for(m = 0; m < 6 && ops[k].arg[m] && !e; m++, t++) {
                    while(src < end && (*src == ' ' || *src == '(' || *src == ')')) src++;
                    if(strchr("\",\r\n]}", *src)) { if(ops[k].arg[m] != ARG_IF) { e = 1; } break; }
                    switch(ops[k].arg[m]) {
                        case ARG_IF:
                            if(!memcmp(src, "has ", 4)) { t--; op[4] = op[3]; op[3] = op[2]; op[2] = op[1]; op[0] |= 6; j = h = 1; src += 3; m += 2; } else
                            if(!memcmp(src, "not ", 4)) { t--; op[4] = op[3]; op[3] = op[2]; op[2] = op[1]; op[0] |= 7; j = h = 1; src += 3; m += 2; } else
                            if(!memcmp(src, "if ", 3)) { t--; op[5] = op[3]; op[4] = op[2]; op[3] = op[1]; j = 1; src += 2; c = 1; } else e = 2;
                        break;
                        case ARG_CND:
                            for(o = 0; o < (int)(sizeof(cnds)/sizeof(cnds[0])); o++) {
                                p = cnds[o][1] ? 2 : 1;
                                if(!memcmp(src, cnds[o], p) && src[p] == ' ') { src += p; break; }
                            }
                            if(o >= (int)(sizeof(cnds)/sizeof(cnds[0]))) e = 2;
                            else { t--; op[0] |= o + 1; }
                        break;
                        case ARG_VAR:
                            if(*src >= '0' && *src <= '9') {
                                o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            } else
                                for(o = 0; o < 256; o++)
                                    if((p = varslen[o]) && !memcmp(src, vars[o], p) && (src[p] == '\"' || src[p] == ' ' || src[p] == ')')) {
                                        src += p; break;
                                    }
                            /* variable in a condition can be 0 (current room), and then number that follows can be a room alias */
                            if((!o && !c) || o > 255) e = 6; else { op[j++] = o; if(!o && !c) r = 1; }
                        break;
                        case ARG_NUM:
                            if(*src >= '0' && *src <= '9') {
                                o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            } else
                            if(h) {
                                for(o = 0; o < NUMNOUN; o++)
                                    if((p = nounslen[o]) && !memcmp(src, nouns[o], p) && src[p] == '\"') { src += p; o++; break; }
                                if(!o || o >= NUMNOUN) e = 10;
                            } else
                            if(r) {
                                for(o = 0; o < 255; o++)
                                    if((p = roomslen[o]) && !memcmp(src, rooms[o], p) && src[p] == '\"') { src += p; break; }
                                if(o > 254) e = 9; else roomref[o] = 1;
                            } else
                            if(!memcmp(src, "false", 5)) { o = 0; src += 5; } else
                            if(!memcmp(src, "true", 4)) { o = 1; src += 4; }
                            if(o > 255) e = 7; else op[j++] = o;
                        break;
                        case ARG_MUS:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(o > 7) e = 3; else op[j++] = o;
                        break;
                        case ARG_SFX:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(o > 63) e = 4; else op[j++] = o;
                        break;
                        case ARG_SCR:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(!o || o > 63) e = 5; else op[j++] = o - 1;
                        break;
                        case ARG_MSG:
                            o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            if(!o || o > NUMMSG || o > nt) e = 8; else op[j++] = o - 1;
                        break;
                        case ARG_ROOM:
                            if(*src >= '0' && *src <= '9') {
                                o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            } else {
                                for(o = 0; o < 255; o++)
                                    if((p = roomslen[o]) && !memcmp(src, rooms[o], p) && (src[p] == '\"' || src[p] == ' ')) {
                                        src += p; break;
                                    }
                            }
                            if(o > 254 || (o && !meg4.ovls[o].data)) e = 9; else { op[j++] = o; roomref[o] = 1; }
                        break;
                        case ARG_NOUN:
                            if(*src >= '0' && *src <= '9') {
                                o = atoi((char*)src); while(src < end && *src >= '0' && *src <= '9') src++;
                            } else
                                for(o = 0; o < NUMNOUN; o++)
                                    if((p = nounslen[o]) && !memcmp(src, nouns[o], p) && (src[p] == '\"' || src[p] == ' ' || src[p] == ')')) {
                                        src += p; o++; break;
                                    }
                            if(!o || o >= NUMNOUN) e = 10; else op[j++] = o;
                        break;
                    }
                }
                /* report error (if any) */
                if(e) fprintf(stderr, "converter: line %u: bad %s in script %u in room %u: %s %s \"%s\"\r\n", line, ops[k].op,
                    n, l, e == 1 ? "missing" : (e == 7 ? "out of bounds" : "no such"), err[e - 1], json_line(src, ' ')); else
                /* otherwise add the generated binary opcode to the script */
                if(i + t < len - 1) { memcpy(dst + i, op, t); i += t; numinst += t; }
                else fprintf(stderr, "converter: line %u: not enough buffer for '%s' in script %u in room %u\r\n", line, ops[k].op, n, l);
                /* skip to the next mnemonic (needed if there was a problem with parsing the arguments or if there's a comment) */
                for(; src < end && !strchr("\",\r\n)]}", *src); src++) src = json_iscomment(src, end);
                break;
            }
        }
        /* if mnemonic wasn't recognized */
        if(k >= (int)(sizeof(ops)/sizeof(ops[0])))
            fprintf(stderr, "converter: line %u: unknown instruction \"%s\" in script %u in room %u\r\n", line, json_line(src, 0), n, l);
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
    char tmpverb[NUMVERB + 9][8][16];   /* save, load, list, navigation and verbs */
    char tmpnoun[NUMNOUN][16];          /* nouns */
    char tmpmsg[NUMMSG][256];           /* room messages */
    char tmp[4096], str[1024], *verbs[NUMVERB] = { 0 }, *comment = NULL, custom[2][4096] = { "", "" };
    uint8_t *end = buf + len, *img, *s, *e, *iend, verbref[NUMVERB + 9] = { 0 };
    int i, j, k, l, m, n, p, flen, size, verbslen[NUMVERB] = { 0 }, numnoun = 0, numcmd = 0, numtxt = 0, nt = 0;
    char *keywords1[] = { "sprites", "music", "sounds", "setup", "rooms", "verbs", "nouns", "vars", "status", "colors", "textpos",
        "custom", "logic", "config", "config0", "config1" };
    char *keywords2[] = { "lang", "text", "text0", "text1", "answers", "save", "load", "list", "north", "west", "east",
        "south", "up", "down", "nouns", "image", "logic", "verb1", "verb2", "verb3", "verb4", "verb5", "verb6", "verb7",
        "verb8", "verb9", "verb10", "verb11", "verb12", "verb13", "verb14", "verb15", "verb16", "verb17", "verb18", "verb19",
        "verb20", "verb21", "verb22", "verb23", "verb24", "verb25", "verb26", "verb27", "verb28", "verb29", "verb30",
        "verb31", "verb32" };

    line = 1; vars[0] = "room";
    verbref[0] = verbref[1] = verbref[2] = verbref[3] = verbref[4] = verbref[5] = verbref[6] = verbref[7] = verbref[8] = 1;

    /* check arguments */
    if(!fn || !buf || len < 13) return 0;
    /* skip optional leading comment (will be copied to program.c as might have copyright info) and check magic */
    if(buf[0] == '/' && buf[1] == '*') { comment= (char*)buf; buf = json_skip(buf, end, '\"', 0); }
    if(memcmp(buf, "\"AdvGame\"", 9)) return 0;

    /* get path from JSON file's name (all paths must be relative to this) */
    flen = strlen(fn);
    while(flen > 0 && fn[flen - 1] != '/') flen--;
    if(flen > 0) { memcpy(tmp, fn, flen); if(tmp[flen - 1] != '/') tmp[flen++] = '/'; }

    /* collect defined rooms in advance */
    for(s = buf + 9, l = line, k = p = 0; s < end; s++) {
        if(s[0] == '/' && s[1] == '*') for(s += 2; s < end && (s[-2] != '*' || s[-1] != '/'); s++) if(*s == '\n') l++;
        if(s[0] == '/' && s[1] == '/') for(s += 2; s < end && *s != '\n'; s++);
        if(*s == '\n') l++;
        if(*s == '[') p++;
        if(*s == ']') p--;
        if(*s == '{') k++;
        if(*s == '}') {
            if(p > 0) fprintf(stderr, "converter: line %u: unclosed [\r\n", l);
            if(p < 0) fprintf(stderr, "converter: line %u: no opening for ]\r\n", l);
            k--; p = 0;
        }
        if(p && *s == '\"') for(s++; s < end && (*s != '\"' || s[-1] == '\\'); s++) if(*s == '\n') l++;
        if(k != 1 || p) continue;

        /* rooms (JSON-only aliases) */
        if(!memcmp(s, "\"rooms\"", 7)) {
            for(s += 7, i = j = 0; s < end && *s != ']'; i++) {
                for(;s < end && *s != '\"' && *s != ']'; s++) if(*s == '\n') l++;
                if(*s != '\"') break; else s++;
                if(i < 254) {
                    rooms[i] = (char*)s;
                    for(m = 0; m < (int)(sizeof(keywords1)/sizeof(keywords1[0])); m++)
                        if(!strcmp((char*)s, keywords1[m])) {
                            rooms[i] = NULL;
                            fprintf(stderr, "converter: line %u: keyword '%s' cannot be a room alias\r\n", l, keywords1[m]);
                        }
                } else j = 1;
                for(;s < end && *s != '\"'; s++) if(*s == '\n') l++;
                if(rooms[i]) roomslen[i] = (uintptr_t)s - (uintptr_t)rooms[i];
                *s++ = 0;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", l, 254);
        } else

        /* room definiton with an alias */
        if(s[0] == '\"' && ((s[1] >= 'a' && s[1] <= 'z') || (s[1] >= 'A' && s[1] <= 'Z'))) {
            for(s++, i = 0; i < 254; i++)
                if((j = roomslen[i]) && !memcmp(s, rooms[i], j) && s[j] == '\"') { s += j + 1; i++; goto isroom; }
        } else

        /* room definition with a number */
        if(s[0] == '\"' && s[1] >= '0' && s[1] <= '9') {
            s++; i = atoi((char*)s); for(;s < end && *s >= '0' && *s <= '9'; s++);
isroom:     if(i > 0 && i < 255) {
                if(meg4.ovls[i].data) fprintf(stderr, "converter: line %u: duplicate room %u\r\n", l, i);
                meg4.ovls[i].size = 32768;
                if((meg4.ovls[i].data = (uint8_t*)realloc(meg4.ovls[i].data, 32768)))
                    memset(meg4.ovls[i].data, 0, 32768);
                else meg4.ovls[i].size = 0;
            }
        }
    }
    if(k > 0) fprintf(stderr, "converter: line %u: unclosed {\r\n", l);
    if(k < 0) fprintf(stderr, "converter: line %u: no opening for }\r\n", l);
    if(p > 0) fprintf(stderr, "converter: line %u: unclosed [\r\n", l);
    if(p < 0) fprintf(stderr, "converter: line %u: no opening for ]\r\n", l);

    /* parse JSON */
    for(buf += 9; buf < end; buf++) {

        /* skip comments */
        buf = json_iscomment(buf, end);

        /* sprites key, we need its palette and we must convert it into indexed */
        if(!memcmp(buf, "\"sprites\"", 9)) {
            buf = json_unescape(tmp + flen, buf + 9, end, 256);
            if((img = main_readfile(tmp, &size))) {
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
                    } else fprintf(stderr, "converter: line %u: not 256 x 256 pixels '%s'\r\n", line, tmp);
                } else fprintf(stderr, "converter: line %u: not a PNG '%s'\r\n", line, tmp);
                free(img);
            } else fprintf(stderr, "converter: line %u: unable to load '%s'\r\n", line, tmp);
            memset(meg4.mmio.sprites, 0, 2*sizeof(ag_conf_t));
        } else

        /* music tracks and sound effects */
        if(!memcmp(buf, "\"music\"", 7) || !memcmp(buf, "\"sounds\"", 8)) {
            for(j = buf[1] == 's' ? 31 : 8, buf += 8, i = 0; buf < end && *buf != ']' && i < j; i++) {
                buf = json_unescape(tmp + flen, buf, end, 256);
                if(tmp[flen]) {
                    if((img = main_readfile(tmp, &size))) {
                        if(!meg4_import(tmp + flen, img, size, 0)) fprintf(stderr, "converter: line %u: unable to import '%s'\r\n", line, tmp);
                        else if(j == 31) { meg4.mmio.sounds[i * 4] = MEG4_NOTE_C_4; meg4.mmio.sounds[i * 4 + 1] = i + 1; }
                        free(img);
                    } else fprintf(stderr, "converter: line %u: unable to load '%s'\r\n", line, tmp);
                }
            }
            for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
            if(*buf != ']' && i >= j) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, j); }
        } else

        /* setup key, contains the initial game state, up to 256 elements byte array */
        if(!memcmp(buf, "\"setup\"", 7)) {
            for(buf += 7, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '}');
                if(*buf < '0' || *buf > '9') break;
                if(i < 256) game[0].setup[i] = atoi((char*)buf); else j = 1;
                while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 256);
            roomref[(int)game[0].setup[0]] = 1;
        } else

        /* status bar, which game state variables to display */
        if(!memcmp(buf, "\"status\"", 8)) {
            for(buf += 8, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '}');
                if(*buf < '0' || *buf > '9') break;
                if(i < 2) game[0].status[i] = atoi((char*)buf); else j = 1;
                while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 2);
        } else

        /* colors key, 5 elements colors (palette indeces) */
        if(!memcmp(buf, "\"colors\"", 8)) {
            for(buf += 8, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '}');
                if(*buf < '0' || *buf > '9') break;
                if(i < 5) game[0].colors[i] = atoi((char*)buf); else j = 1;
                while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 5);
        } else

        /* text position (from top, in pixels) */
        if(!memcmp(buf, "\"textpos\"", 9)) {
            buf = json_skip(buf + 9, end, ',', 0);
            game[0].textpos = atoi((char*)buf);
        } else

        /* custom ui code (two elements string array with C code) */
        if(!memcmp(buf, "\"custom\"", 8)) {
            for(buf += 8, i = 0; buf < end && *buf != ']' && i < 2; i++)
                buf = json_unescape(custom[i], buf, end, sizeof(custom[0]));
            for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
            if(*buf != ']' && i >= 2) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 2); }
        } else

        /* rooms (JSON-only aliases) */
        if(!memcmp(buf, "\"rooms\"", 7)) {
            /* we have already parsed these, so now just skip */
            for(buf += 7; buf < end && *buf != ']'; buf++) if(*buf == '\n') line++;
        } else

        /* verbs (JSON-only aliases) */
        if(!memcmp(buf, "\"verbs\"", 7)) {
            for(buf += 7, i = j = 0; buf < end && *buf != ']'; i++) {
                buf = json_skip(buf, end, ']', '\"');
                if(*buf != '\"') break; else buf++;
                if(i < NUMVERB) {
                    verbs[i] = (char*)buf;
                    for(m = 0; m < (int)(sizeof(keywords2)/sizeof(keywords2[0])); m++)
                        if(!strcmp((char*)buf, keywords2[m])) {
                            verbs[i] = NULL;
                            fprintf(stderr, "converter: line %u: keyword '%s' cannot be a verb alias\r\n", l, keywords2[m]);
                        }
                } else j = 1;
                buf = json_skip(buf, end, ']', '\"');
                if(verbs[i]) verbslen[i] = (uintptr_t)buf - (uintptr_t)verbs[i];
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
                if(nouns[i]) nounslen[i] = (uintptr_t)buf - (uintptr_t)nouns[i];
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
                if(vars[i]) varslen[i] = (uintptr_t)buf - (uintptr_t)vars[i];
                *buf++ = 0;
            }
            if(j) fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 256);
        } else

        /* common game logic for all rooms */
        if(!memcmp(buf, "\"logic\"", 7)) {
            buf = json_opcodes(game[0].logic, buf + 7, end, 72, 0, 0, 0);
        } else

        /* configurations (just language specific strings really) */
        if(!memcmp(buf, "\"config", 7)) {
            l = buf[7] == '1' ? 1 : 0;
            buf = json_skip(buf + 8, end, '{', '}');
            memset(tmpverb, 0, sizeof(tmpverb));
            memset(tmpnoun, 0, sizeof(tmpnoun));
            for(buf++; buf < end && *buf != '}'; buf++) {
                buf = json_iscomment(buf, end);
                /* config properties */
                if(!memcmp(buf, "\"lang\"", 6)) {
                    buf = json_skip(buf + 6, end, '\"', 0);
                    if(*buf == '\"') { game[l].lang[0] = buf[1]; game[l].lang[1] = buf[2]; buf += 3; }
                } else
                if(!memcmp(buf, "\"text\"", 6)) { numtxt++; buf = json_unescape(game[l].text, buf + 6, end, sizeof(game[0].text)); } else
                if(!memcmp(buf, "\"answers\"", 9)) {
                    for(buf += 9, i = 0; buf < end && *buf != ']' && *buf != '}' && i < 4; i++)
                        buf = json_unescape(game[l].answ[i], buf, end, sizeof(game[0].answ[0]));
                    for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
                    if(*buf != ']' && i >= 4) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 4); }
                } else
                if(!memcmp(buf, "\"save\"", 6))  { buf += 6; j = 0; goto readverb; } else
                if(!memcmp(buf, "\"load\"", 6))  { buf += 6; j = 1; goto readverb; } else
                if(!memcmp(buf, "\"list\"", 6))  { buf += 6; j = 2; goto readverb; } else
                if(!memcmp(buf, "\"north\"", 7)) { buf += 7; j = 3; goto readverb; } else
                if(!memcmp(buf, "\"west\"", 6))  { buf += 6; j = 4; goto readverb; } else
                if(!memcmp(buf, "\"east\"", 6))  { buf += 6; j = 5; goto readverb; } else
                if(!memcmp(buf, "\"south\"", 7)) { buf += 7; j = 6; goto readverb; } else
                if(!memcmp(buf, "\"up\"", 4))    { buf += 4; j = 7; goto readverb; } else
                if(!memcmp(buf, "\"down\"", 6))  { buf += 6; j = 8; goto readverb; } else
                if(!memcmp(buf, "\"nouns\"", 7)) {
                    for(buf += 7, i = 0; buf < end && *buf != ']' && *buf != '}' && i < NUMNOUN; i++)
                        buf = json_unescape(tmpnoun[i], buf, end, sizeof(tmpnoun[0]));
                    for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
                    if(*buf != ']' && i >= NUMNOUN) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, NUMNOUN); }
                    if(!l) numnoun = i; else if(i != numnoun) fprintf(stderr, "converter: line %u: different number of nouns in \"config0\" and \"config1\"\r\n", line);
                } else
                if(!memcmp(buf, "\"verb", 5)) {
                    buf += 5; j = atoi((char*)buf);
                    while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
                    buf = json_skip(buf, end, '[', 0);
                    if(j >= 1 && j <= NUMVERB) {
                        j += 8;
readverb:               for(verbref[j] = 1, i = 0; buf < end && *buf != ']' && *buf != '}' && i < 8; i++)
                            buf = json_unescape(tmpverb[j][i], buf, end, sizeof(tmpverb[0][0]));
                        for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
                        if(*buf != ']' && i >= 8) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, 8); }
                    } else { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: bad verb %u\r\n", line, j); }
                } else
                if(*buf == '\"') {
                    for(buf++, i = 0; i < NUMVERB; i++)
                        if((j = verbslen[i]) && !memcmp(buf, verbs[i], j) && buf[j] == '\"') { buf += j + 1; j = i + 9; goto readverb; }
                    fprintf(stderr, "converter: line %u: unknown verb \"%s\" in \"config%u\"\r\n", line, json_line(buf, 0), l);
                }
            }
            /* serialize verbs and nouns */
            for(m = i = 0; i < NUMVERB; i++)
                for(j = 0; j < 8 && m < (int)sizeof(game[0].verb); j++, m += k + 1)
                    if((k = strlen(tmpverb[i][j])) && m + k < (int)sizeof(game[0].verb)) memcpy(game[l].verb + m, tmpverb[i][j], k);
            if(m >= (int)sizeof(game[0].verb)) fprintf(stderr, "converter: line %u: too many verbs in \"config%u\"\r\n", line, l);
            for(m = i = 0; i < NUMNOUN && m < (int)sizeof(game[0].noun); i++, m += k + 1)
                if((k = strlen(tmpnoun[i])) && m + k < (int)sizeof(game[0].noun)) memcpy(game[l].noun + m, tmpnoun[i], k);
            if(m >= (int)sizeof(game[0].noun)) fprintf(stderr, "converter: line %u: too many nouns in \"config%u\"\r\n", line, l);
        } else

        /* room definiton with an alias */
        if(buf[0] == '\"' && ((buf[1] >= 'a' && buf[1] <= 'z') || (buf[1] >= 'A' && buf[1] <= 'Z'))) {
            for(buf++, l = 0; l < 254; l++)
                if((j = roomslen[l]) && !memcmp(buf, rooms[l], j) && buf[j] == '\"') { buf += j + 1; l++; goto readroom; }
            fprintf(stderr, "converter: line %u: unknown keyword or room alias \"%s\"\r\n", line, json_line(buf, 0));
            break;
        } else

        /* room definition with a number */
        if(buf[0] == '\"' && buf[1] >= '0' && buf[1] <= '9') {
            buf++; l = atoi((char*)buf); while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
readroom:   if(l > 0 && l < 255 && meg4.ovls[l].data) {
                memset(meg4.ovls[l].data, 0, 32768);
                room = (ag_room_t*)meg4.ovls[l].data;
                /* room properties */
                buf = json_skip(buf, end, '{', 0);
                for(n = 1; buf < end && *buf != '}'; buf++) {
                    buf = json_iscomment(buf, end);
                    /* room image */
                    if(!memcmp(buf, "\"image\"", 7)) {
                        buf = json_unescape(tmp + flen, buf + 7, end, 256);
                        if((img = main_readfile(tmp, &size))) {
                            if(!memcmp(img, "\x89PNG", 4)) {
                                m = ((img[18] << 8) | img[19]); p = ((img[22] << 8) | img[23]);
                                if(m <= 256 && p <= 96) {
                                    if((s = (uint8_t*)stbi_load_from_memory(img, size, &m, &p, &k, 4))) {
                                        for(j = 0, e = s; j < p; j++)
                                            for(i = 0; i < m; i++, e += 4)
                                                meg4.ovls[l].data[(32 + j) * 256 + i] = meg4_palidx(e);
                                        free(s);
                                    }
                                } else fprintf(stderr, "converter: line %u: maximum 256 x 96 pixels '%s'\r\n", line, tmp);
                            } else fprintf(stderr, "converter: line %u: not a PNG '%s'\r\n", line, tmp);
                            free(img);
                        } else fprintf(stderr, "converter: line %u: unable to load '%s'\r\n", line, tmp);
                    } else

                    /* room texts (up to 2 variants) */
                    if(!memcmp(buf, "\"text", 5)) {
                        memset(tmpmsg, 0, sizeof(tmpmsg));
                        j = buf[5] == '1' ? 1 : 0;
                        buf = json_skip(buf + 6, end, '[', ']');
                        for(i = 0; buf < end && *buf != ']' && *buf != '}' && i < NUMMSG; i++, numtxt++) {
                            buf = json_unescape(str, buf, end, sizeof(str));
                            json_wrap(tmpmsg[i], str, 256);
                        }
                        for(;buf < end && (*buf == ' ' || *buf == '\r' || *buf == '\n'); buf++) if(*buf == '\n') line++;
                        if(*buf != ']' && i >= NUMMSG) { buf = json_skip(buf, end, ']', 0); fprintf(stderr, "converter: line %u: more than %u elements in array\r\n", line, NUMMSG); }
                        if(!j) nt = i; else if(i != nt) fprintf(stderr, "converter: line %u: different number of texts in \"text0\" and \"text1\"\r\n", line);
                        /* serialize room messages */
                        for(m = i = 0, k = 1; i < NUMMSG && m < 2048 && k > 0; i++, m += k + 1)
                            if((k = strlen(tmpmsg[i])) && m + k < 2048) memcpy(&room->msg[j][m], tmpmsg[i], k);
                        if(m >= 2048) fprintf(stderr, "converter: line %u: too many messages in room %u\r\n", line, l);
                    } else

                    /* room verbs */
                    if(!memcmp(buf, "\"save\"", 6) || !memcmp(buf, "\"load\"", 6) || !memcmp(buf, "\"list\"", 6)) {
                        fprintf(stderr, "converter: line %u: keyword \"%s\" not allowed here\r\n", line, json_line(buf + 1, 0));
                    } else
                    if(!memcmp(buf, "\"north\"", 7)) { buf += 7; j = 0; goto readdir; } else
                    if(!memcmp(buf, "\"west\"", 6))  { buf += 6; j = 1; goto readdir; } else
                    if(!memcmp(buf, "\"east\"", 6))  { buf += 6; j = 2; goto readdir; } else
                    if(!memcmp(buf, "\"south\"", 7)) { buf += 7; j = 3; goto readdir; } else
                    if(!memcmp(buf, "\"up\"", 4))    { buf += 4; j = 4; goto readdir; } else
                    if(!memcmp(buf, "\"down\"", 6))  {
                        buf += 6; j = 5;
readdir:                buf = json_skip(buf, end, '[', '\"');
                        if(*buf == '[') {   /* script given for this direction */
                            if(n >= 63) {
                                fprintf(stderr, "converter: line %u: too many scripts in room %u\r\n", line, l);
                                i = 0;
                            } else {
                                cmds = &room->cmds[n++];
                                cmds->verb = 0x80 | j;
                                buf = json_opcodes(cmds->op, buf, end, 61, n, l, nt);
                                i = 255;
                            }
                        } else
                        if(*buf == '\"') {  /* room alias given */
                            for(buf++, i = 0; i < 254; i++)
                                if((k = roomslen[i]) && !memcmp(buf, rooms[i], k) && buf[k] == '\"') { buf += k + 1; i++; break; }
                            if(i >= 254 || (i && !meg4.ovls[i].data)) {
                                fprintf(stderr, "converter: line %u: invalid %s room alias \"%s\" in room %u\r\n", line, dirs[j], json_line(buf, ' '), l);
                                i = 0;
                            }
                        } else {            /* room number given */
                            i = atoi((char*)buf); while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
                            if(i >= 255 || (i && !meg4.ovls[i].data)) {
                                fprintf(stderr, "converter: line %u: invalid %s direction to %u in room %u\r\n", line, dirs[j], i, l);
                                i = 0;
                            }
                        }
                        if(i && i < 255) roomref[i] = 1;
                        room->dir[j] = i;
                        verbref[3 + j] |= 2;
                        numcmd++;
                    } else
                    if(!memcmp(buf, "\"logic\"", 7)) { buf += 7; j = 0; goto readops; } else
                    if(!memcmp(buf, "\"verb", 5)) {
                        buf += 5; j = atoi((char*)buf);
                        while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
                        if(j) j += 8;
readops:                if(j >= 0 && j < NUMVERB + 9) {
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
                                        } else {
                                            for(i = 0; i < NUMNOUN; i++)
                                                if((k = nounslen[i]) && !memcmp(buf, nouns[i], k) && (buf[k] == '\"' || buf[k] == ' ')) {
                                                    buf += k; cmds->noun1 = i + 1; break;
                                                }
                                            if(i >= NUMNOUN) {
                                                fprintf(stderr, "converter: line %u: unknown noun \"%s\" for verb %u in room %u\r\n", line, json_line(buf, ' '), j, l);
                                                buf = json_skip(buf, end, ' ', '\"');
                                            }
                                        }
                                        if(*buf == ' ') {
                                            buf++;
                                            if(*buf >= '0' && *buf <= '9') {
                                                cmds->noun2 = atoi((char*)buf);
                                                while(buf < end && *buf >= '0' && *buf <= '9') buf++;
                                            } else {
                                                for(i = 0; i < NUMNOUN; i++)
                                                    if((k = nounslen[i]) && !memcmp(buf, nouns[i], k) && (buf[k] == '\"' || buf[k] == ' ')) {
                                                        buf += k; cmds->noun2 = i + 1; break;
                                                    }
                                                if(i >= NUMNOUN) {
                                                    fprintf(stderr, "converter: line %u: unknown noun \"%s\" for verb %u in room %u\r\n", line, json_line(buf, ':'), j, l);
                                                    buf = json_skip(buf, end, ':', '\"');
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
                            if(cmds) {
                                if(*buf == '\"') buf++;
                                buf = json_skip(buf, end, '[', '\"');
                                if(*buf == '[') {   /* script given for this verb */
                                    buf = json_opcodes(cmds->op, buf, end, 61, j ? n - 1 : 0, l, nt);
                                } else
                                if(*buf == '\"') {  /* room alias given */
                                    for(buf++, i = 0; i < 254; i++)
                                        if((k = roomslen[i]) && !memcmp(buf, rooms[i], k) && buf[k] == '\"') { buf += k + 1; i++; break; }
                                    if(i >= 254 || (i && !meg4.ovls[i].data)) {
                                        fprintf(stderr, "converter: line %u: invalid jump to room alias \"%s\" in room %u\r\n", line, json_line(buf, 0), l);
                                    } else { cmds->op[0] = 5 << 3; cmds->op[1] = i; roomref[i] = 1; }
                                } else {            /* room number given */
                                    i = atoi((char*)buf); while(buf < end && (*buf >= '0' && *buf <= '9')) buf++;
                                    if(i >= 255 || (i && !meg4.ovls[i].data))
                                        fprintf(stderr, "converter: line %u: invalid jump to %u in room %u\r\n", line, i, l);
                                    else { cmds->op[0] = 5 << 3; cmds->op[1] = i; roomref[i] = 1; }
                                }
                                verbref[j] |= 2;
                                numcmd++;
                            }
                        } else fprintf(stderr, "converter: line %u: invalid verb %u in room %u\r\n", line, j, l);
                    } else
                    if(*buf == '\"') {
                        for(buf++, i = 0; i < NUMVERB; i++)
                            if((j = verbslen[i]) && !memcmp(buf, verbs[i], j) && (buf[j] == '\"' || buf[j] == ' ')) { buf += j; j = i + 9; goto readops; }
                        fprintf(stderr, "converter: line %u: unknown verb \"%s\" in room %u\r\n", line, json_line(buf, 0), l);
                    }
                }
            } else fprintf(stderr, "converter: line %u: invalid room number %u\r\n", line, l);
        }
    }

    /* check verb references */
    for(i = 0; i < NUMVERB && verbref[i + 9] != 1; i++);
    if(i < NUMVERB) {
        fprintf(stderr, "converter: defined but unused verb(s):");
        for(i = 0; i < NUMVERB; i++) if(verbref[i + 9] == 1) fprintf(stderr, " %u", i);
        fprintf(stderr, "\r\n");
    }
    for(i = k = l = 0; i < NUMVERB + 9; l += !!verbref[i], k += !!(verbref[i] == 2), i++);
    if(k > 0) {
        fprintf(stderr, "converter: undefined but used verb(s):");
        for(i = 0; i < NUMVERB + 9; i++) if(verbref[i] == 2) fprintf(stderr, " %u", i);
        fprintf(stderr, "\r\n");
    }

    /* check room references */
    for(i = 1, j = 1; i < 255; j += !!meg4.ovls[i].data, i++)
        if(!roomref[i] && meg4.ovls[i].data) {
            fprintf(stderr, "converter: unreferenced room(s):");
            for(i = 1; i < 255; i++) if(!roomref[i] && meg4.ovls[i].data) fprintf(stderr, " %u", i);
            fprintf(stderr, "\r\n");
            break;
        }

    fprintf(stderr, "converter: done (verbs %u nouns %u rooms %u commands %u texts %u bytecode %u)\r\n", l, numnoun, j,
        numcmd, numtxt, numinst);

    /* save game configuration to overlay 0 */
    meg4.ovls[0].size = 32768;
    if((meg4.ovls[0].data = (uint8_t*)realloc(meg4.ovls[0].data, meg4.ovls[0].size))) {
        memcpy(meg4.ovls[0].data, meg4.mmio.sprites, meg4.ovls[0].size);
    } else meg4.ovls[0].size = 0;

    /* add game interpreter program */
    if(comment) { for(s = (uint8_t*)comment + 3; memcmp(s - 3, "*/\n", 3); s++) {} *s = 0; } else comment = "";
    if((meg4.src = (char*)realloc(meg4.src, strlen(program) + strlen(comment) + strlen(custom[0]) + strlen(custom[1]) + 1)))
        meg4.src_len = sprintf(meg4.src, program, comment, custom[0], custom[1]) + 1;
    else meg4.src_len = 0;

    /* tell the exporter to save in binary format */
    isbinary = 1;
    return 1;
}
