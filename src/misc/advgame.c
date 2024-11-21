#!c

/**
 * Adventure Game Engine - MEG-4 DEMO
 * Copyright (c) bzt 2024 CC-0
 */

/* variables */
uint8_t lang, state[256], init[256], stat[2], colors[5], textpos, logic[4104], dir[8], cmd[4096], say, say2, say3, rst;
char ans[256], verb[1536], noun[1536], msg[4096], inp[256];
uint16_t midx[64];

/* customize your UI here */
void custom_intro()
{
%s}
void custom_room()
{
%s}

/* function to parse and execute opcodes */
void parse_ops(uint8_t *c)
{
  uint8_t op, cnd, arg1, arg2, p, l, so;
  p = l = 0;
  while(*c) {
    op = *c++;
    switch(op & 7) {
       case 0: cnd = 1; break;
       case 1: arg1 = *c++; arg2 = *c++; cnd = (arg1==249?lang:((arg1>=250?dir[arg1-250]:state[arg1]))) == arg2; break;
       case 2: arg1 = *c++; arg2 = *c++; cnd = (arg1==249?lang:((arg1>=250?dir[arg1-250]:state[arg1]))) != arg2; break;
       case 3: arg1 = *c++; arg2 = *c++; cnd = (arg1==249?lang:((arg1>=250?dir[arg1-250]:state[arg1]))) <= arg2; break;
       case 4: arg1 = *c++; arg2 = *c++; cnd = (arg1==249?lang:((arg1>=250?dir[arg1-250]:state[arg1]))) < arg2; break;
       case 5: arg1 = *c++; arg2 = *c++; cnd = (arg1==249?lang:((arg1>=250?dir[arg1-250]:state[arg1]))) > arg2; break;
       case 6: arg1 = *c++; cnd = state[255 - (arg1 >> 3)] & (1 << (arg1 & 7)); break;
       case 7: arg1 = *c++; cnd = !(state[255 - (arg1 >> 3)] & (1 << (arg1 & 7))); break;
    }
    if(p == 1) cnd = cnd && l; else if(p == 2) cnd = cnd || l;
    p = l = 0;
    switch(op >> 3) {
      case  0: if(cnd) return; break;
      case  1: p = 1; l = cnd; break;
      case  2: p = 2; l = cnd; break;
      case  3: arg1 = *c++; if(cnd) { if(arg1 < 8) music(arg1, 0, 128); else music(0, 0, 0); } break;
      case  4: arg1 = *c++; if(cnd) { if(arg1 < 64) sfx(arg1, 0, 255); else sfx(0, 0, 0); } break;
      case  5: arg1 = *c++; if(cnd && arg1 < 255) { load_room(arg1); return; } break;
      case  6: arg1 = *c++; if(cnd && state[arg1] < 255) { load_room(state[arg1]); return; } break;
      case  7: arg1 = *c++; if(cnd && arg1 && arg1 < 63) { so = say3; say3 = 32; parse_ops(&logic[77 + (arg1 - 1) * 64]); say3 = so; } break;
      case  8: arg1 = *c++; if(cnd && state[arg1] && state[arg1] < 63) { so = say3; say3 = 32; parse_ops(&logic[77 + (state[arg1] - 1) * 64]); say3 = so; } break;
      case  9: arg1 = *c++; if(cnd) state[255 - (arg1 >> 3)] |= (1 << (arg1 & 7)); break;
      case 10: arg1 = *c++; if(cnd) state[255 - (arg1 >> 3)] &= ~(1 << (arg1 & 7)); break;
      case 11: arg1 = *c++; if(cnd && arg1 && arg1 < 33) { say2 = say; say = arg1 + 3 + say3; } break;
      case 12: arg1 = *c++; arg2 = *c++; arg2 += state[arg1]; if(cnd && arg2 && arg2 < 33) { say2 = say; say = arg2 + 3 + say3; } break;
      case 13: arg1 = *c++; arg2 = *c++; if(arg1 && arg1 < 33 && arg2 && arg2 < 33) { say2 = say; say = (cnd ? arg2 : arg1) + 3 + say3; } break;
      case 14: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg1] + arg2 < 255 ? state[arg1] + arg2 : 255; break;
      case 15: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg1] + state[arg2] < 255 ? state[arg1] + state[arg2] : 255; break;
      case 16: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg1] > arg2 ? state[arg1] - arg2 : 0; break;
      case 17: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg1] > state[arg2] ? state[arg1] - state[arg2] : 0; break;
      case 18: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = arg2; break;
      case 19: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = rand() %% arg2; break;
      case 20: arg1 = *c++; arg2 = *c++; if(cnd) state[arg1] = state[arg2]; break;
      case 21: c += 3; break;
      case 22: case 23: case 24: case 25: c += 5; break;
      case 26: c += 6; break;
      case 27: c += 10; break;
      case 28: c += 10; break;
      case 29: c += 14; break;
    }
  }
}

/* function to load a room */
void load_room(int r)
{
  int i, m, l;
  if(r < 1 || r > 254) { inp[0] = 0; rst = 1; return; }
  if(state[0] != r) {
    state[0] = r;
    memload(0x10000, r, 32768);
    memcpy(&msg, 0x10000 + lang * 2048, 2048);
    memcpy(&dir, 0x11000, 6);
    memcpy(&cmd, 0x11006, 4096);
    memset(&midx, 0, 64);
    for(m = i = 0, l = 1; i < 32 && m < 2048 && l > 0; i++, m += l + 1) { midx[i] = m; l = strlen(&msg[m]); }
    inp[0] = 0; say = 255; say2 = say3 = 0;
    parse_ops(&cmd[3]);
  }
  cls(colors[2]);
  spr(32, 2, 128, 32, textpos > 96 ? 12 : textpos/8, 0, 0);
  if(stat[0]) printf(" %%3u", state[stat[0]]);
  if(stat[1]) printf(" %%3u", state[stat[1]]);
  custom_room();
}

/* function to parse user input */
void parse_cmd(char *s)
{
  uint8_t v, n1, n2;
  int i, j, k, l, m, n;
  if(!s || !*s) { say = 255; return; }
  memcpy(&inp, s, 256);
  /* detect verb and noun(s) */
  v = n1 = n2 = 0;
  for(i = n = 0; i < 255 && inp[i] && !n2;) {
    while(i < 255 && inp[i] == ' ') i++;
    if(!v)
      for(m = j = 0; j < 42; j++)
        for(k = 0; k < 8 && m < 1536; k++, m += l + 1) {
          l = strlen(&verb[m]);
          if(l > n && (mblen(&verb[m]) > 2 || !inp[i + l] || inp[i + l] == ' ') && !memcmp(&inp[i], &verb[m], l)) { v = j + 1; n = l; }
        }
    for(m = n = j = 0, l = 1; j < 255 && m < 1536 && l; j++, m += l + 1) {
      l = strlen(&noun[m]);
      if(l && (mblen(&noun[m]) > 2 || !inp[i + l] || inp[i + l] == ' ') && l > n && !memcmp(&inp[i], &noun[m], l)) { n = l; j++; if(!n1) n1 = j; else n2 = j; break; }
    }
    while(i < 255 && inp[i] && inp[i] != ' ') i++;
  }
  parse_ops(&logic[0]);
  if(rst) return;
  say = say2 = say3 = 0;
  /* built-in navigation verbs (might fall-through into room script case) */
  if(v >= 4 && v <= 9) {
    if(n1) { say = 2; return; } else v -= 4;
    if(dir[v] == 255) { v += 250; n1 = n2 = 0; }
    else { if(!dir[v]) say = 1; else load_room(dir[v]); return; }
  }
  /* built-in save, load game and list inventory verbs */
  if(v == 1) { say = memsave(255, &state, 256) ? 3 : 2; } else
  if(v == 2) { say = 2; memload(&state, 255, 256); v = state[0] ? state[0] : 1; state[0] = 255; load_room(v); return; } else
  if(v == 3) { say = 254; } else
  /* look for a script for this verb and noun(s) */
  if(v) {
    /* room specific */
    for(say = 2, i = 64; i < 63*64; i += 64)
      if(cmd[i] == v && ((cmd[i + 1] == n1 && cmd[i + 2] == n2) || (cmd[i + 1] == n2 && cmd[i + 2] == n1))) {
        say = 255; parse_ops(&cmd[i + 3]); custom_room(); return;
      }
    /* common */
    for(i = 72; i < 4104; i += 64)
      if(logic[i] == v && ((logic[i + 1] == n1 && logic[i + 2] == n2) || (logic[i + 1] == n2 && logic[i + 2] == n1))) {
        say = 255; say3 = 32; parse_ops(&logic[i + 3]); custom_room(); return;
      }
  }
}

/* wait for a keypress and force jump to the first room */
void reset_game()
{
  getc();
  memcpy(&state, &init, 256);
  state[0] = 255; rst = 0;
  load_room(init[0] ? init[0] : 1);
}

/* load game configuration and display intro screen */
void setup()
{
  int i, m, l;
  outw(0x14, PTR_NONE);
  memload(0x10000, 0, 32768);
  lang = inb(0x11000) && (inb(16) != inb(0x10000) || inb(17) != inb(0x10001)) ? 1 : 0;
  memcpy(&init, 0x10EB0, 256);
  memcpy(&stat, 0x10FB0, 2);
  memcpy(&colors, 0x10FB2, 5);
  memcpy(&textpos, 0x10FB7, 1);
  memcpy(&logic, 0x10FB8, 72);
  memcpy(&msg, 0x10002 + lang * 4096, 430);
  memcpy(&ans, 0x101B0 + lang * 4096, 256);
  memcpy(&verb, 0x102B0 + lang * 4096, 1536);
  memcpy(&noun, 0x108B0 + lang * 4096, 1536);
  memload(0x10000, 1, 32768);
  memcpy(&logic[72], 0x11046, 4032);
  memcpy(&msg[2048], 0x10000 + lang * 2048, 2048);
  memset(&midx[32], 0, 64);
  for(m = 2048, i = 32, l = 1; i < 64 && m < 4096 && l > 0; i++, m += l + 1) { midx[i] = m; l = strlen(&msg[m]); }
  memload(0x10000, 0, 32768);
  cls(colors[0]);
  spr(32, 2, 128, 32, textpos > 96 ? 12 : textpos/8, 0, 0);
  custom_intro();
  text(colors[1], 40, textpos, 1, 0, 0, &msg);
  reset_game();
}

/* display prompt and parse user input */
void loop()
{
  int m, j, l;
  frect(colors[2], 4, textpos, 315, 195);
  outw(0x49A, 4); outw(0x49C, textpos);
  if(inp[0]) {
    outb(0x498, colors[4]);
    printf("> %%s\n", &inp);
  }
  if(say <= 68) {
    outb(0x498, colors[3]);
    if(say2 >= 4 && say2 <= 36) { outw(0x49A, 4); printf("%%s\n\n", &msg[midx[say2 - 4]]); }
    outw(0x49A, 4); printf("%%s\n", say < 4 ? &ans[say * 64] : &msg[midx[say - 4]]);
  } else
  if(say == 254) {
    outb(0x498, colors[3]); outw(0x49A, 0);
    for(m = 0, j = l = 1; j < 256 && m < 1536 && l; j++, m += l + 1)
      if((l = strlen(&noun[m])) && state[255 - (j >> 3)] & (1 << (j & 7))) {
        if(inw(0x49A) + width(1, &noun[m]) > 308) printf("\n");
        printf(" %%s", &noun[m]);
      }
    printf("\n");
  }
  if(!rst) {
    outw(0x49A, 4); outb(0x498, colors[4]); printf("> ");
    parse_cmd(gets());
  } else reset_game();
}
