# Minneskarta

## Allehanda

Alla värden är små endian, så den mindre siffran lagras på den mindre adressen.

| Offset |    Storlek | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  00000 |          1 | MEG-4 firmwareversion major                                        |
|  00001 |          1 | MEG-4 firmwareversion minor                                        |
|  00002 |          1 | MEG-4 firmwareversion bugfix                                       |
|  00003 |          1 | prestandaräknare, sista bildens outnyttjade tid på 1/1000:e sek    |
|  00004 |          4 | antal 1/1000:e sekundstickar sedan strömmen slogs på               |
|  00008 |          8 | UTC unix tidsstämpel                                               |
|  00010 |          2 | nuvarande lokalitet                                                |

Prestandaräknaren visar tiden som inte användes när den sista bilden genererades. Om detta är noll eller negativt betyder det hur
mycket din loop()-funktion har överskridit sin tillgängliga tidsram.

## Pekare

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  00012 |          2 | pekarknapparnas status (se [getbtn] och [getclk])                  |
|  00014 |          2 | pekare sprite index                                                |
|  00016 |          2 | pekarens X-koordinat                                               |
|  00018 |          2 | pekarens Y-koordinat                                               |

Pekarknapparna är som följer:

| Define  | Bitmask   | Beskrivning                                                        |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | Vänster musknapp                                                   |
| `BTN_M` |         2 | Mellersta musknappen                                               |
| `BTN_R` |         4 | Höger musknapp                                                     |
| `SCR_U` |         8 | Bläddra åt uppåt                                                   |
| `SCR_D` |        16 | Bläddra åt ner                                                     |
| `SCR_L` |        32 | Bläddra åt vänster                                                 |
| `SCR_R` |        64 | Bläddra åt höger                                                   |

De övre bitarna i pekarens sprite-index används för hotspots: bit 13-15 hotspot Y, bit 10-12 hotspot X, bit 0-9 sprite.
Det finns några fördefinierade inbyggda markörer:

| Define       | Värde     | Beskrivning                                                   |
|--------------|----------:|---------------------------------------------------------------|
| `PTR_NORM`   |      03fb | Normal (pil) pekare                                           |
| `PTR_TEXT`   |      03fc | Textpekare                                                    |
| `PTR_HAND`   |      0bfd | Länkpekare                                                    |
| `PTR_ERR`    |      93fe | Felpekare                                                     |
| `PTR_NONE`   |      ffff | Pekaren är dold                                               |

## Tangentbord

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0001A |          1 | tangentbordskösvans                                                |
|  0001B |          1 | tangentbordsköhuvud                                                |
|  0001C |         64 | tangentbordskö, 16 element, vardera 4 byte (se [popkey])           |
|  0005C |         18 | tangentbordsknappar som trycks in av skanningskoder (se [getkey])  |

De nycklar som öppnas från kön är representerade i UTF-8. Vissa ogiltiga UTF-8-sekvenser representerar speciella (ej utskrivbara)
nycklar, till exempel:

| Nyckelkod | Beskrivning                                   |
|---------|-------------------------------------------------|
| `\x8`   | Tecknet 8, <kbd>←Backsteg</kbd>-tangenten       |
| `\x9`   | Tecknet 9, <kbd>Tab</kbd>-tangenten             |
| `\n`    | Tecknet 10, <kbd>⏎Enter</kbd>-tangenten         |
| `\x1b`  | Tecknet 27, <kbd>Esc</kbd>-tangenten            |
| `Del`   | <kbd>Del</kbd>-tangenten                        |
| `Up`    | Markörpiltangenten <kbd>▴</kbd>                 |
| `Down`  | Markörpiltangenten <kbd>▾</kbd>                 |
| `Left`  | Markörpiltangenten <kbd>◂</kbd>                 |
| `Rght`  | Markörpiltangenten <kbd>▸</kbd>                 |
| `Cut`   | "Cut"-tangenten (eller <kbd>Ctrl</kbd>+<kbd>X</kbd>) |
| `Cpy`   | "Copy"-tangenten (eller <kbd>Ctrl</kbd>+<kbd>C</kbd>)  |
| `Pst`   | "Paste"-tangenten (eller <kbd>Ctrl</kbd>+<kbd>V</kbd>) |

Skanningskoderna är följande:

| ScanKod  | Adress  | Bitmask | Define            |
|---------:|---------|--------:|-------------------|
|        0 |   0005C |       1 | `KEY_CHEAT`       |
|        1 |   0005C |       2 | `KEY_F1`          |
|        2 |   0005C |       4 | `KEY_F2`          |
|        3 |   0005C |       8 | `KEY_F3`          |
|        4 |   0005C |      16 | `KEY_F4`          |
|        5 |   0005C |      32 | `KEY_F5`          |
|        6 |   0005C |      64 | `KEY_F6`          |
|        7 |   0005C |     128 | `KEY_F7`          |
|        8 |   0005D |       1 | `KEY_F8`          |
|        9 |   0005D |       2 | `KEY_F9`          |
|       10 |   0005D |       4 | `KEY_F10`         |
|       11 |   0005D |       8 | `KEY_F11`         |
|       12 |   0005D |      16 | `KEY_F12`         |
|       13 |   0005D |      32 | `KEY_PRSCR`       |
|       14 |   0005D |      64 | `KEY_SCRLOCK`     |
|       15 |   0005D |     128 | `KEY_PAUSE`       |
|       16 |   0005E |       1 | `KEY_BACKQUOTE`   |
|       17 |   0005E |       2 | `KEY_1`           |
|       18 |   0005E |       4 | `KEY_2`           |
|       19 |   0005E |       8 | `KEY_3`           |
|       20 |   0005E |      16 | `KEY_4`           |
|       21 |   0005E |      32 | `KEY_5`           |
|       22 |   0005E |      64 | `KEY_6`           |
|       23 |   0005E |     128 | `KEY_7`           |
|       24 |   0005F |       1 | `KEY_8`           |
|       25 |   0005F |       2 | `KEY_9`           |
|       26 |   0005F |       4 | `KEY_0`           |
|       27 |   0005F |       8 | `KEY_MINUS`       |
|       28 |   0005F |      16 | `KEY_EQUAL`       |
|       29 |   0005F |      32 | `KEY_BACKSPACE`   |
|       30 |   0005F |      64 | `KEY_TAB`         |
|       31 |   0005F |     128 | `KEY_Q`           |
|       32 |   00060 |       1 | `KEY_W`           |
|       33 |   00060 |       2 | `KEY_E`           |
|       34 |   00060 |       4 | `KEY_R`           |
|       35 |   00060 |       8 | `KEY_T`           |
|       36 |   00060 |      16 | `KEY_Y`           |
|       37 |   00060 |      32 | `KEY_U`           |
|       38 |   00060 |      64 | `KEY_I`           |
|       39 |   00060 |     128 | `KEY_O`           |
|       40 |   00061 |       1 | `KEY_P`           |
|       41 |   00061 |       2 | `KEY_LBRACKET`    |
|       42 |   00061 |       4 | `KEY_RBRACKET`    |
|       43 |   00061 |       8 | `KEY_ENTER`       |
|       44 |   00061 |      16 | `KEY_CAPSLOCK`    |
|       45 |   00061 |      32 | `KEY_A`           |
|       46 |   00061 |      64 | `KEY_S`           |
|       47 |   00061 |     128 | `KEY_D`           |
|       48 |   00062 |       1 | `KEY_F`           |
|       49 |   00062 |       2 | `KEY_G`           |
|       50 |   00062 |       4 | `KEY_H`           |
|       51 |   00062 |       8 | `KEY_J`           |
|       52 |   00062 |      16 | `KEY_K`           |
|       53 |   00062 |      32 | `KEY_L`           |
|       54 |   00062 |      64 | `KEY_SEMICOLON`   |
|       55 |   00062 |     128 | `KEY_APOSTROPHE`  |
|       56 |   00063 |       1 | `KEY_BACKSLASH`   |
|       57 |   00063 |       2 | `KEY_LSHIFT`      |
|       58 |   00063 |       4 | `KEY_LESS`        |
|       59 |   00063 |       8 | `KEY_Z`           |
|       60 |   00063 |      16 | `KEY_X`           |
|       61 |   00063 |      32 | `KEY_C`           |
|       62 |   00063 |      64 | `KEY_V`           |
|       63 |   00063 |     128 | `KEY_B`           |
|       64 |   00064 |       1 | `KEY_N`           |
|       65 |   00064 |       2 | `KEY_M`           |
|       66 |   00064 |       4 | `KEY_COMMA`       |
|       67 |   00064 |       8 | `KEY_PERIOD`      |
|       68 |   00064 |      16 | `KEY_SLASH`       |
|       69 |   00064 |      32 | `KEY_RSHIFT`      |
|       70 |   00064 |      64 | `KEY_LCTRL`       |
|       71 |   00064 |     128 | `KEY_LSUPER`      |
|       72 |   00065 |       1 | `KEY_LALT`        |
|       73 |   00065 |       2 | `KEY_SPACE`       |
|       74 |   00065 |       4 | `KEY_RALT`        |
|       75 |   00065 |       8 | `KEY_RSUPER`      |
|       76 |   00065 |      16 | `KEY_MENU`        |
|       77 |   00065 |      32 | `KEY_RCTRL`       |
|       78 |   00065 |      64 | `KEY_INS`         |
|       79 |   00065 |     128 | `KEY_HOME`        |
|       80 |   00066 |       1 | `KEY_PGUP`        |
|       81 |   00066 |       2 | `KEY_DEL`         |
|       82 |   00066 |       4 | `KEY_END`         |
|       83 |   00066 |       8 | `KEY_PGDN`        |
|       84 |   00066 |      16 | `KEY_UP`          |
|       85 |   00066 |      32 | `KEY_LEFT`        |
|       86 |   00066 |      64 | `KEY_DOWN`        |
|       87 |   00066 |     128 | `KEY_RIGHT`       |
|       88 |   00067 |       1 | `KEY_NUMLOCK`     |
|       89 |   00067 |       2 | `KEY_KP_DIV`      |
|       90 |   00067 |       4 | `KEY_KP_MUL`      |
|       91 |   00067 |       8 | `KEY_KP_SUB`      |
|       92 |   00067 |      16 | `KEY_KP_7`        |
|       93 |   00067 |      32 | `KEY_KP_8`        |
|       94 |   00067 |      64 | `KEY_KP_9`        |
|       95 |   00067 |     128 | `KEY_KP_ADD`      |
|       96 |   00068 |       1 | `KEY_KP_4`        |
|       97 |   00068 |       2 | `KEY_KP_5`        |
|       98 |   00068 |       4 | `KEY_KP_6`        |
|       99 |   00068 |       8 | `KEY_KP_1`        |
|      100 |   00068 |      16 | `KEY_KP_2`        |
|      101 |   00068 |      32 | `KEY_KP_3`        |
|      102 |   00068 |      64 | `KEY_KP_ENTER`    |
|      103 |   00068 |     128 | `KEY_KP_0`        |
|      104 |   00069 |       1 | `KEY_KP_DEC`      |
|      105 |   00069 |       2 | `KEY_INT1`        |
|      106 |   00069 |       4 | `KEY_INT2`        |
|      107 |   00069 |       8 | `KEY_INT3`        |
|      108 |   00069 |      16 | `KEY_INT4`        |
|      109 |   00069 |      32 | `KEY_INT5`        |
|      110 |   00069 |      64 | `KEY_INT6`        |
|      111 |   00069 |     128 | `KEY_INT7`        |
|      112 |   0006A |       1 | `KEY_INT8`        |
|      113 |   0006A |       2 | `KEY_LNG1`        |
|      114 |   0006A |       4 | `KEY_LNG2`        |
|      115 |   0006A |       8 | `KEY_LNG3`        |
|      116 |   0006A |      16 | `KEY_LNG4`        |
|      117 |   0006A |      32 | `KEY_LNG5`        |
|      118 |   0006A |      64 | `KEY_LNG6`        |
|      119 |   0006A |     128 | `KEY_LNG7`        |
|      120 |   0006B |       1 | `KEY_LNG8`        |
|      121 |   0006B |       2 | `KEY_APP`         |
|      122 |   0006B |       4 | `KEY_POWER`       |
|      123 |   0006B |       8 | `KEY_KP_EQUAL`    |
|      124 |   0006B |      16 | `KEY_EXEC`        |
|      125 |   0006B |      32 | `KEY_HELP`        |
|      126 |   0006B |      64 | `KEY_SELECT`      |
|      127 |   0006B |     128 | `KEY_STOP`        |
|      128 |   0006C |       1 | `KEY_AGAIN`       |
|      129 |   0006C |       2 | `KEY_UNDO`        |
|      130 |   0006C |       4 | `KEY_CUT`         |
|      131 |   0006C |       8 | `KEY_COPY`        |
|      132 |   0006C |      16 | `KEY_PASTE`       |
|      133 |   0006C |      32 | `KEY_FIND`        |
|      134 |   0006C |      64 | `KEY_MUTE`        |
|      135 |   0006C |     128 | `KEY_VOLUP`       |
|      136 |   0006D |       1 | `KEY_VOLDN`       |


## Gamepad

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0006E |          2 | gamepad joystick tröskel (standard till 8000)                      |
|  00070 |          8 | primär gamepad - tangentbordsavläsningskodmappningar (se [tangentbord]) |
|  00078 |          4 | 4 gamepads knapp nedtryckt läge (se [getpad])                     |

Spelplattans knappar är som följer:

| Define  | Bitmask   | Beskrivning                                                        |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | `◁`-knappen eller joysticken till vänster                          |
| `BTN_U` |         2 | `△`-knappen eller joysticken upp                                   |
| `BTN_R` |         4 | `▷`-knappen eller joysticken till höger                            |
| `BTN_D` |         8 | `▽`-knappen eller joysticken nedåt                                 |
| `BTN_A` |        16 | Knappen `Ⓐ`                                                       |
| `BTN_B` |        32 | Knappen `Ⓑ`                                                       |
| `BTN_X` |        64 | Knappen `Ⓧ`                                                       |
| `BTN_Y` |       128 | Knappen `Ⓨ`                                                       |

Sekvensen `△△▽▽◁▷◁▷ⒷⒶ` gör att `KEY_CHEAT` "tangenten" trycks ned.

## Grafikbearbetningsenhet

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0007E |          1 | UNICODE-kodpunktens övre bitar för teckensnittsmappning            |
|  0007F |          1 | sprite bankväljare för kartan                                      |
|  00080 |       1024 | palett, 256 färger, varje post 4 byte, RGBA                        |
|  00480 |          2 | x0, beskärningsområde X börjar i pixlar (för alla ritfunktioner)   |
|  00482 |          2 | x1, beskärningsområde X slutar i pixlar                            |
|  00484 |          2 | y0, beskärningsområde Y börjar i pixlar                            |
|  00486 |          2 | y1, beskärningsområde Y slutar i pixlar                            |
|  00488 |          2 | visad vram X-förskjutning i pixlar eller 0xffff                    |
|  0048A |          2 | visad vram Y-förskjutning i pixlar eller 0xffff                    |
|  0048C |          1 | sköldpadda penna ner flagga (se [up], [down])                      |
|  0048D |          1 | sköldpaddspenna färg, palettindex 0 till 255 (se [color])          |
|  0048E |          2 | sköldpaddans riktning i grader, 0 till 359 (se [left], [right])    |
|  00490 |          2 | sköldpadda X offset i pixlar (se [move])                           |
|  00492 |          2 | sköldpadda Y offset i pixlar                                       |
|  00494 |          2 | labyrints gånghastighet i 1/128 brickor (se [maze])                |
|  00496 |          2 | labyrints rotationshastighet i grader (1 till 90)                  |
|  00498 |          1 | konsolens förgrundsfärg, palettindex 0 till 255 (se [printf])      |
|  00499 |          1 | konsolens bakgrundsfärg, palettindex 0 till 255                    |
|  0049A |          2 | konsolens X-förskjutning i pixlar                                  |
|  0049C |          2 | konsolens Y-förskjutning i pixlar                                  |
|  0049E |          2 | kamera X-förskjutning i [3D-utrymme] (se [tri3d], [tritx], [mesh]) |
|  004A0 |          2 | kamera Y-förskjutning                                              |
|  004A2 |          2 | kamera Z-förskjutning                                              |
|  004A4 |          2 | kamerariktning, pitch (0 upp, 90 framåt)                           |
|  004A6 |          2 | kamerariktning, gir (0 vänster, 90 framåt)                         |
|  004A8 |          1 | kamerans synfält i vinklar (45, negativ ger ortografi)             |
|  004AA |          2 | ljuskällans position X offset-förskjutning (se [tri3d], [tritx], [mesh]) |
|  004AC |          2 | ljuskällans position Y offset-förskjutning                         |
|  004AE |          2 | ljuskällans position Z offset-förskjutning                         |
|  00600 |      64000 | map, 320 x 200 sprite-index (se [map] och [maze])                  |
|  10000 |      65536 | sprites, 256 x 256 palettindex, 1024 8 x 8 pixlar (se [spr])       |
|  28000 |      32768 | fönster för teckensnitt 4096 (se 0007E, [width] och [text])        |

## Digital signalprocessor

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0007C |          1 | vågformsbanksväljare (1 till 31)                                   |
|  0007D |          1 | musikspårsbankväljare (0 till 7)                                   |
|  004BA |          1 | aktuellt tempo (i bockar per rad, skrivskyddad)                    |
|  004BB |          1 | aktuellt spår som spelas (skrivskyddat)                            |
|  004BC |          2 | nuvarande rad som spelas (skrivskyddad)                            |
|  004BE |          2 | antal totala rader i aktuellt spår (skrivskyddat)                  |
|  004C0 |         64 | 16 kanalstatusregister, vardera 4 byte (skrivskyddad)              |
|  00500 |        256 | 64 ljudeffekter, vardera 4 byte                                    |
|  20000 |      16384 | fönster för vågformsprov (se 0007C)                                |
|  24000 |      16384 | fönster för musikmönster (se 0007D)                                |

DSP-statusregistren är alla skrivskyddade och för varje kanal ser de ut så här:

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | aktuell position i vågformen som spelas                            |
|      2 |          1 | aktuell vågform (1 till 31, 0 om kanalen är tyst)                  |
|      3 |          1 | aktuell volym (0 betyder att kanalen är avstängd)                  |

De första 4 kanalerna är för musiken, resten för ljudeffekterna.

Observera att vågformsindex 0 betyder "använd föregående vågform", så index 0 kan inte användas i väljaren.
Formatet för varannan vågform:

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | antal prover                                                       |
|      2 |          2 | sling start                                                        |
|      4 |          2 | slinglängd                                                         |
|      6 |          1 | finjustera värde, -8 till 7                                        |
|      7 |          1 | volym, 0 till 64                                                   |
|      8 |      16376 | signerade 8-bitars monosampel                                      |

Formatet på ljudeffekterna och musikspåren är desamma, den enda skillnaden är att musikspår har 4 toner per rad, en för varje
kanal, och det finns 1024 rader; medan det för ljudeffekter bara finns en ton och 64 rader.

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          1 | notnummer, se `NOTE_x` definierar, 0 till 96                       |
|      1 |          1 | vågformsindex, 0 till 31                                           |
|      2 |          1 | effekttyp, 0 till 255 (se [notera effekter])                       |
|      3 |          1 | effektparameter                                                    |

Räkningen av sedlar går till som följer: 0 betyder ingen not satt. Följt av 8 oktaver, var och en med 12 toner, så 1 är lika med
C-0, 12 är B-0 (på den lägsta oktaven), 13 är C-1 (en oktav högre) och 14 är C#1 (C skarp, halvton högre). Till exempel skulle
D-noten på 4:e oktaven vara 1 + 4\*12 + 2 = 51. B-7 är 96, den högsta tonen på den högsta oktaven. Du har också inbyggda
definitioner, till exempel är C-1 `NOTE_C_1` och C#1 är `NOTE_Cs1`, om du inte vill räkna kan du använda dessa också i ditt program.

## Notera effekter

För enkelhetens skull använder MEG-4 samma koder som Amiga MOD-filen (på så sätt kommer du att se detsamma i den inbyggda
redigeraren såväl som i en musikspårare från tredje part), men den stöder inte alla. Som tidigare nämnts representeras dessa koder
av tre hexadecimala tal, den första är typen `t`, och de två sista parametern `xy` (eller `xx`). Typerna `E1` till `ED` är alla lagrade i
typbyten, även om det ser ut som att en av deras nibble kan tillhöra parametern, men det är den inte.


| Effect | Code | Beskrivning                                                |
|--------|------|------------------------------------------------------------|
| ...    | 000  | Ingen effekt                                               |
| Arp    | 0xy  | Arpeggio, spela not, not+x halvton och not+y halvton       |
| Po/    | 1xx  | Portamento upp, skjut punkten x uppåt                      |
| Po\\   | 2xx  | Portamento ner, skjut punkten x nedåt                      |
| Ptn    | 3xx  | Tonportamento, skjutperiod till punkt x                    |
| Vib    | 4xy  | Vibrera, oscillera tonhöjden med y halvtoner vid x frekv   |
| Ctv    | 5xy  | Fortsätt Tonportamento + skjut volymen x uppåt eller y nedåt |
| Cvv    | 6xy  | Fortsätt Vibrato + volym skjut x uppåt eller y nedåt       |
| Trm    | 7xy  | Tremolo, oscillera volymen med y amplitud vid x frekv      |
| Ofs    | 9xx  | Ställ in provoffset till x \* 256                          |
| Vls    | Axy  | Skjut volymen med x uppåt eller med y nedåt                |
| Jmp    | Bxx  | Positionshopp, ställ in raden till x \* 64                 |
| Vol    | Cxx  | Ställ in volymen på x                                      |
| Fp/    | E1x  | Fint portamento upp, öka perioden med x                    |
| Fp\\   | E2x  | Fint portamento ner, minska perioden med x                 |
| Svw    | E4x  | Ställ in vibratovågform, 0 sinus, 1 såg, 2 kvadrat, 3 brus |
| Ftn    | E5x  | Ställ in finjustering, ändra inställning med x (-8 till 7) |
| Stw    | E7x  | Ställ in tremolo-vågform, 0 sinus, 1 såg, 2 kvadrat, 3 brus |
| Rtg    | E9x  | Retrigger note, trigga aktuellt sampel varje x tick        |
| Fv/    | EAx  | Fin volym glider upp, öka med x                            |
| Fv\\   | EBx  | Sänk volymen fint, minska med x                            |
| Cut    | ECx  | Klipp anteckningen i x bockar                              |
| Dly    | EDx  | Fördröjningsanteckning i x bockar                          |
| Tpr    | Fxx  | Ställ in antalet bockar per rad till x (kryss för 6)       |

## Användarminne

Minnesadresser från 00000 till 2FFFF tillhör MMIO, allt ovan (med början från 30000 eller `MEM_USER`) är fritt användbar
användarminne.

| Offset | Storlek    | Beskrivning                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  30000 |          4 | (endast BASIC) offset av DATA                                      |
|  30004 |          4 | (endast BASIC) aktuell READ-räknare                                |
|  30008 |          4 | (endast BASIC) maximalt READ, antal DATA                           |

Detta följs av de globala variablerna som du har deklarerat i ditt program, följt av konstanterna, som strängliteraler.
När det gäller BASIC följs detta av de faktiska DATA-posterna.

Minnesadresser ovanför initialiserade data kan tilldelas och frigöras dynamiskt i ditt program via [malloc] och [free] samtal.

Slutligen stacken, som är överst (med början från C0000 eller `MEM_LIMIT`) och växer *nedåt*. Ditt programs lokala variabler (som
du deklarerade i en funktion) går här. Storleken på stacken ändras alltid beroende på vilken funktion som anropar vilken annan
funktion i ditt program.

Om toppen av den dynamiskt allokerade datan och botten av stapeln av någon slump skulle överlappa varandra, så ger MEG-4 ett
felmeddelande "om att minnet är slut".

## Formatera sträng

Vissa funktioner, [printf], [sprintf] och [trace] använder en formatsträng som kan innehålla specialtecken för att referera till argument
och för att beskriva hur de ska visas. Dessa är:

| Kod  | Beskrivning                                                |
|------|------------------------------------------------------------|
| `%%` | `%`-tecknet                                                |
| `%d` | Nästa parameter som ett decimaltal                         |
| `%u` | Nästa parameter som ett decimaltal utan tecken             |
| `%x` | Nästa parameter som ett hexadecimalt tal                   |
| `%o` | Nästa parameter som ett oktalt tal                         |
| `%b` | Nästa parameter som ett binärt tal                         |
| `%f` | Nästa parameter som ett flyttal                            |
| `%s` | Nästa parameter som en sträng                              |
| `%c` | Nästa parameter som ett UTF-8-tecken                       |
| `%p` | Nästa parameter som adress (pekare)                        |
| `\t` | Tab, fixera vertikal position innan du fortsätter          |
| `\n` | Starta en ny rad                                           |

Du kan lägga till utfyllnad genom att ange längden mellan `%` och koden. Om det börjar med `0`, kommer värdet att fyllas med nollor,
annars med mellanslag. Till exempel `%4d` fyller värdet till höger med mellanslag och `%04x` med nollor. `f` accepterar ett tal efter en
punkt, som talar om antalet siffror i bråkdelen (upp till 8), t.ex. `%.6f`.

## 3D-utrymme

I MEG-4 hanteras det tredimensionella utrymmet enligt högerregeln: +X är till höger, +Y är upp och +Z är mot betraktaren.

```
  +Y
   |
   |__ +X
  /
+Z
```

Varje poäng måste placeras i intervallet -32767 till +32767. Hur denna 3D-värld projiceras på din 2D-skärm beror på hur du
konfigurerar kameran (se [Grafikbearbetningsenhet] adress 0049E). Naturligtvis måste du placera kameran i världen, med
X, Y, Z-koordinater. Sedan måste du tala om var kameran tittar på, med hjälp av pitch och yaw. Slutligen måste du också
berätta vilken typ av objektiv kameran har, genom att ange synfältsvinkeln. Den senare bör normalt vara mellan 30 (mycket
smal) och 180 grader (som fiskar och fåglar). MEG-4 stöder upp till 127 grader, men det finns ett knep. Positiva FOV-värden
kommer att projiceras som perspektiv (ju längre bort objektet är, desto mindre är det), men negativa värden hanteras också,
bara med ortografisk projektion (oavsett avstånd kommer objektets storlek att vara densamma). Perspektiv används i FPS-spel,
medan den ortografiska projektionen mest föredras av strategispel.

Du kan visa en uppsättning trianglar (en komplett 3D-modell) med hjälp av [mesh]-funktionen effektivt. Eftersom modeller
förmodligen har lokala koordinater, skulle det rita alla modeller ovanpå varandra runt origo. Så om du vill visa flera
modeller i världen, bör du först översätta dem (placera dem) till världskoordinater med hjälp av [trns] och sedan använda
det översatta vertexmolnet med [mesh] (att flytta och rotera modellen runt kommer inte att ändra trianglarna, bara deras
vertexkoordinater).

## Genvägar för kodredigerare

Ytterligare [tangentbord] genvägar du kan använda när du redigerar källan:

| Nyckel                       | Beskrivning                                                                          |
|------------------------------|--------------------------------------------------------------------------------------|
| <kbd>Ctrl</kbd>+<kbd>F</kbd> | Hitta sträng                                                                         |
| <kbd>Ctrl</kbd>+<kbd>G</kbd> | Hitta igen                                                                           |
| <kbd>Ctrl</kbd>+<kbd>H</kbd> | Sök och ersätt (i den markerade texten, eller i brist på det, i hela källan)         |
| <kbd>Ctrl</kbd>+<kbd>J</kbd> | Gå till raden                                                                        |
| <kbd>Ctrl</kbd>+<kbd>D</kbd> | Gå till funktionsdefinition                                                          |
| <kbd>Ctrl</kbd>+<kbd>N</kbd> | Lista bokmärken                                                                      |
| <kbd>Ctrl</kbd>+<kbd>B</kbd> | Växla bokmärke på aktuell linje                                                      |
| <kbd>Ctrl</kbd>+<kbd>▴</kbd> | Gå till föregående bokmärke                                                          |
| <kbd>Ctrl</kbd>+<kbd>▾</kbd> | Gå till nästa bokmärke                                                               |
| <kbd>Ctrl</kbd>+<kbd>◂</kbd> | Gå till början av föregående ord                                                     |
| <kbd>Ctrl</kbd>+<kbd>▸</kbd> | Gå till slutet av nästa ord                                                          |
| <kbd>Ctrl</kbd>+<kbd>,</kbd> | Minska indrag av markering                                                           |
| <kbd>Ctrl</kbd>+<kbd>.</kbd> | Öka indraget i urvalet                                                               |
| <kbd>Home</kbd>              | Flytta markören till början av raden                                                 |
| <kbd>End</kbd>               | Flytta markören till slutet av rad                                                   |
| <kbd>PgUp</kbd>              | Flytta markören 42 rader (en sida) uppåt                                             |
| <kbd>PgDown</kbd>            | Flytta markören 42 rader (en sida) nedåt                                             |
| <kbd>F1</kbd>                | Om markören finns i ett API:s argumentlista, gå till funktionens inbyggda hjälpsida  |

Oavsett plattformens tangentbordslayout kan alla tecken som krävs för programmering (och några till) alltid nås:

| Vänster <kbd>Alt</kbd> + |
|-----///------------------|
| <kbd> </kbd> <kbd>(</kbd> <kbd>)</kbd> <kbd>{</kbd> <kbd>}</kbd> <kbd>〈</kbd> <kbd>〉</kbd> <kbd>!</kbd> <kbd>^</kbd> <kbd>_</kbd> <kbd>-</kbd> <kbd>=</kbd> |
| <kbd>⇥</kbd> <kbd> </kbd> <kbd> </kbd> <kbd>€</kbd> <kbd>₹</kbd> <kbd>~</kbd> <kbd>¥</kbd> <kbd> </kbd> <kbd> </kbd> <kbd>°</kbd> <kbd>"</kbd> <kbd>\[</kbd> <kbd>\]</kbd> |
| <kbd>↨</kbd> <kbd>&</kbd> <kbd>$</kbd> <kbd>@</kbd> <kbd>¦</kbd> <kbd> </kbd> <kbd>#</kbd> <kbd> </kbd> <kbd> </kbd> <kbd>£</kbd> <kbd>;</kbd> <kbd>'</kbd> <kbd>\\</kbd> |
| <kbd>⇮</kbd> <kbd>:</kbd> <kbd>?</kbd> <kbd> </kbd> <kbd>元</kbd> <kbd>%</kbd> <kbd>+</kbd> <kbd>✶</kbd> <kbd>,</kbd> <kbd>.</kbd> <kbd>/</kbd> |

Se även menyn för alternativa inmatningsmetoder och deras kortkommandon.

# Konsolen

## putc

```c
void putc(uint32_t chr)
```
<dl>
<dt>Beskrivning</dt><dd>
Skriver ut ett tecken till konsolen.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| chr | UTF-8 tecken |
</dd>
</dl>
<hr>
## printf

```c
void printf(str_t fmt, ...)
```
<dl>
<dt>Beskrivning</dt><dd>
Skriver ut text till konsolen.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| fmt | sträng att visa, [formatera sträng] |
| ... | valfria argument |
</dd>
</dl>
<hr>
## getc

```c
uint32_t getc(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Läser en karaktär från konsolen, blockerar program när det inte finns någon inmatning.
</dd>
<dt>Returvärde</dt><dd>
Ett UTF-8-tecken som användaren angav.
</dd>
<dt>Se även</dt><dd>
[popkey]
</dd>
</dl>
<hr>
## gets

```c
str_t gets(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Läser in en nyradsavslutad sträng från användaren (returnerar inte nyraden).
</dd>
<dt>Returvärde</dt><dd>
Byten läses i en sträng.
</dd>
</dl>
<hr>
## trace

```c
void trace(str_t fmt, ...)
```
<dl>
<dt>Beskrivning</dt><dd>
Spåra utförande genom att skriva ut till standard. Fungerar bara om `meg4` startades med den verbose flaggan `-v`.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| fmt | [formatera sträng] |
| ... | valfria argument |
</dd>
</dl>
<hr>
## delay

```c
void delay(uint16_t msec)
```
<dl>
<dt>Beskrivning</dt><dd>
Fördröjer programexekveringen.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| msec | fördröjning i millisekunder |
</dd>
</dl>
<hr>
## exit

```c
void exit(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Avslutar programmet.
</dd>
</dl>

# Audio

## sfx

```c
void sfx(uint8_t sfx, uint8_t channel, uint8_t volume)
```
<dl>
<dt>Beskrivning</dt><dd>
Spelar en ljudeffekt.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| sfx | index för ljudeffekten, 0 till 63 |
| channel | kanal som ska användas, 0 till 11 |
| volume | volym som ska användas, 0 till 255, 0 stänger av kanalen |
</dd>
</dl>
<hr>
## music

```c
void music(uint8_t track, uint16_t row, uint8_t volume)
```
<dl>
<dt>Beskrivning</dt><dd>
Spelar ett musikspår.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| track | indexet för musikspåret, 0 till 7 |
| row | rad att börja spela från, 0 till 1023 (max låtlängd) |
| volume | volym som ska användas, 0 till 255, 0 stänger av musik |
</dd>
</dl>

# GPIO

## gpio_rev

```c
uint32_t gpio_rev(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Fråga GPIO-kortets versionsnummer. Returnerar 0 om plattformen inte är GPIO-kompatibel.
</dd>
<dt>Returvärde</dt><dd>
Styrelsens revisionsnummer eller 0 om det inte stöds.
</dd>
</dl>
<hr>
## gpio_get

```c
int gpio_get(uint8_t pin)
```
<dl>
<dt>Beskrivning</dt><dd>
Läs värdet på ett GPIO-stift.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| pin | fysiskt pin-nummer, 1 till 40 |
</dd>
<dt>Returvärde</dt><dd>
Returnerar 1 om stiftet är högt, 0 om det är lågt, -1 vid fel (GPIO-stift stöds inte).
</dd>
<dt>Se även</dt><dd>
[gpio_set]
</dd>
</dl>
<hr>
## gpio_set

```c
int gpio_set(uint8_t pin, int value)
```
<dl>
<dt>Beskrivning</dt><dd>
Skriv värdet till ett GPIO-stift.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| pin | fysiskt pin-nummer, 1 till 40 |
| value | 1 för att ställa in stiftet högt, 0 för lågt |
</dd>
<dt>Returvärde</dt><dd>
Returnerar 0 vid framgång, -1 vid fel (GPIO-stift stöds inte).
</dd>
<dt>Se även</dt><dd>
[gpio_get]
</dd>
</dl>

# Grafik

## cls

```c
void cls(uint8_t palidx)
```
<dl>
<dt>Beskrivning</dt><dd>
Rensar hela skärmen och återställer skärmförskjutningar, ställer även in konsolens bakgrundsfärg.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
</dd>
<dt>Se även</dt><dd>
[pget], [pset]
</dd>
</dl>
<hr>
## cget

```c
uint32_t cget(uint16_t x, uint16_t y)
```
<dl>
<dt>Beskrivning</dt><dd>
Få pixel vid en koordinat och returnera färg RGBA.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| x | X-koordinat i pixlar |
| y | Y-koordinat i pixlar |
</dd>
<dt>Returvärde</dt><dd>
En packad färg med RGBA-kanaler (röd är den minst signifikanta byten).
</dd>
<dt>Se även</dt><dd>
[cls], [pget], [pset]
</dd>
</dl>
<hr>
## pget

```c
uint8_t pget(uint16_t x, uint16_t y)
```
<dl>
<dt>Beskrivning</dt><dd>
Få pixel vid en koordinat och returnera dess palettindex.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| x | X-koordinat i pixlar |
| y | Y-koordinat i pixlar |
</dd>
<dt>Returvärde</dt><dd>
Färg i palettindex, 0 till 255.
</dd>
<dt>Se även</dt><dd>
[cls], [pset], [cget]
</dd>
</dl>
<hr>
## pset

```c
void pset(uint8_t palidx, uint16_t x, uint16_t y)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en pixel vid en koordinat.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x | X-koordinat i pixlar |
| y | Y-koordinat i pixlar |
</dd>
<dt>Se även</dt><dd>
[cls], [pget]
</dd>
</dl>
<hr>
## width

```c
uint16_t width(int8_t type, str_t str)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar den visade textens bredd i pixlar.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| type | teckensnitt, -4 till 4 |
| str | sträng att mäta |
</dd>
<dt>Returvärde</dt><dd>
Antal pixlar som krävs för att visa text.
</dd>
<dt>Se även</dt><dd>
[text]
</dd>
</dl>
<hr>
## text

```c
void text(uint8_t palidx, int16_t x, int16_t y, int8_t type, uint8_t shidx, uint8_t sha, str_t str)
```
<dl>
<dt>Beskrivning</dt><dd>
Skriver ut text på skärmen.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x | X-koordinat i pixlar |
| y | Y-koordinat i pixlar |
| type | teckensnittstyp, -4 till -1 monospace, 1 till 4 proportionell |
| shidx | skuggans färg, palettindex 0 till 255 |
| sha | skuggans alfa, 0 (helt transparent) till 255 (helt ogenomskinlig) |
| str | sträng att visa |
</dd>
<dt>Se även</dt><dd>
[width]
</dd>
</dl>
<hr>
## line

```c
void line(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en kantutjämningslinje.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | start X-koordinaten i pixlar |
| y0 | start Y-koordinaten i pixlar |
| x1 | slutar X-koordinaten i pixlar |
| y1 | slutar Y-koordinaten i pixlar |
</dd>
<dt>Se även</dt><dd>
[qbez], [cbez]
</dd>
</dl>
<hr>
## qbez

```c
void qbez(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t cx, int16_t cy)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en kvadratisk Bezier-kurva.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | start X-koordinaten i pixlar |
| y0 | start Y-koordinaten i pixlar |
| x1 | slutar X-koordinaten i pixlar |
| y1 | slutar Y-koordinaten i pixlar |
| cx | kontrollpunkt X-koordinat i pixlar |
| cy | kontrollpunkt Y-koordinat i pixlar |
</dd>
<dt>Se även</dt><dd>
[line], [cbez]
</dd>
</dl>
<hr>
## cbez

```c
void cbez(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t cx0, int16_t cy0, int16_t cx1, int16_t cy1)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en kubisk Bezier-kurva.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | start X-koordinaten i pixlar |
| y0 | start Y-koordinaten i pixlar |
| x1 | slutar X-koordinaten i pixlar |
| y1 | slutar Y-koordinaten i pixlar |
| cx0 | första kontrollpunktens X-koordinat i pixlar |
| cy0 | första kontrollpunktens Y-koordinat i pixlar |
| cx1 | andra kontrollpunktens X-koordinat i pixlar |
| cy1 | andra kontrollpunktens Y-koordinat i pixlar |
</dd>
<dt>Se även</dt><dd>
[line], [qbez]
</dd>
</dl>
<hr>
## tri

```c
void tri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en triangel.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | första kant X-koordinat i pixlar |
| y0 | första kant Y-koordinat i pixlar |
| x1 | andra kantens X-koordinat i pixlar |
| y1 | andra kantens Y-koordinat i pixlar |
| x2 | tredje kantens X-koordinat i pixlar |
| y2 | tredje kantens Y-koordinat i pixlar |
</dd>
<dt>Se även</dt><dd>
[ftri], [tri2d], [tri3d], [tritx], [mesh], [trns]
</dd>
</dl>
<hr>
## ftri

```c
void ftri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en fylld triangel.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | första kant X-koordinat i pixlar |
| y0 | första kant Y-koordinat i pixlar |
| x1 | andra kantens X-koordinat i pixlar |
| y1 | andra kantens Y-koordinat i pixlar |
| x2 | tredje kantens X-koordinat i pixlar |
| y2 | tredje kantens Y-koordinat i pixlar |
</dd>
<dt>Se även</dt><dd>
[tri], [tri2d], [tri3d], [tritx], [mesh], [trns]
</dd>
</dl>
<hr>
## tri2d

```c
void tri2d(uint8_t pi0, int16_t x0, int16_t y0,
    uint8_t pi1, int16_t x1, int16_t y1,
    uint8_t pi2, int16_t x2, int16_t y2)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en fylld triangel med färggradienter.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| pi0 | första kantfärg, palettindex 0 till 255 |
| x0 | första kant X-koordinat i pixlar |
| y0 | första kant Y-koordinat i pixlar |
| pi1 | andra kantfärg, palettindex 0 till 255 |
| x1 | andra kantens X-koordinat i pixlar |
| y1 | andra kantens Y-koordinat i pixlar |
| pi2 | tredje kantfärg, palettindex 0 till 255 |
| x2 | tredje kantens X-koordinat i pixlar |
| y2 | tredje kantens Y-koordinat i pixlar |
</dd>
<dt>Se även</dt><dd>
[tri], [ftri], [tri3d], [tritx], [mesh], [trns]
</dd>
</dl>
<hr>
## tri3d

```c
void tri3d(uint8_t pi0, int16_t x0, int16_t y0, int16_t z0,
    uint8_t pi1, int16_t x1, int16_t y1, int16_t z1,
    uint8_t pi2, int16_t x2, int16_t y2, int16_t z2)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en fylld triangel med färggradienter i [3D-utrymme].
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| pi0 | första kantfärg, palettindex 0 till 255 |
| x0 | första kant X-koordinat i rymden |
| y0 | första kant Y-koordinat i rymden |
| z0 | första kant Z-koordinat i rymden |
| pi1 | andra kantfärg, palettindex 0 till 255 |
| x1 | andra kant X-koordinat i rymden |
| y1 | andra kant Y-koordinat i rymden |
| z1 | andra kant Z-koordinat i rymden |
| pi2 | tredje kantfärg, palettindex 0 till 255 |
| x2 | tredje kantens X-koordinat i rymden |
| y2 | tredje kantens Y-koordinat i rymden |
| z2 | tredje kantens Z-koordinat i rymden |
</dd>
<dt>Se även</dt><dd>
[tri], [ftri], [tri2d], [tritx], [mesh], [trns]
</dd>
</dl>
<hr>
## tritx

```c
void tritx(uint8_t u0, uint8_t v0, int16_t x0, int16_t y0, int16_t z0,
    uint8_t u1, uint8_t v1, int16_t x1, int16_t y1, int16_t z1,
    uint8_t u2, uint8_t v2, int16_t x2, int16_t y2, int16_t z2)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en strukturerad triangel i [3D-utrymme].
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| u0 | första kanttextur X-koordinat 0 till 255 |
| v0 | första kanttextur Y-koordinat 0 till 255 |
| x0 | första kant X-koordinat i rymden |
| y0 | första kant Y-koordinat i rymden |
| z0 | första kant Z-koordinat i rymden |
| u1 | andra kanttextur X-koordinat 0 till 255 |
| v1 | andra kanttextur Y-koordinat 0 till 255 |
| x1 | andra kant X-koordinat i rymden |
| y1 | andra kant Y-koordinat i rymden |
| z1 | andra kant Z-koordinat i rymden |
| u2 | tredje kantstruktur X-koordinat 0 till 255 |
| v2 | tredje kantstruktur Y-koordinat 0 till 255 |
| x2 | tredje kantens X-koordinat i rymden |
| y2 | tredje kantens Y-koordinat i rymden |
| z2 | tredje kantens Z-koordinat i rymden |
</dd>
<dt>Se även</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [mesh], [trns]
</dd>
</dl>
<hr>
## mesh

```c
void mesh(addr_t verts, addr_t uvs, uint16_t numtri, addr_t tris)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar ett nät av trianglar i [3D-utrymme], med hjälp av index till hörn och texturkoordinater (eller palett).
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| verts | adress för vertices array, 3 x 2 byte vardera, X, Y, Z |
| uvs | adress för UV-array (om 0 används palett), 2 x 1 byte vardera, textur X, Y |
| numtri | antal trianglar |
| tris | adress för trianglar array med index, 6 x 1 byte vardera, vi1, ui1/pi1, vi2, ui2/pi2, vi3, ui3/pi3 |
</dd>
<dt>Se även</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [tritx], [trns]
</dd>
</dl>
<hr>
## rect

```c
void rect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en rektangel.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | övre vänstra hörnet X-koordinat i pixlar |
| y0 | övre vänstra hörnet Y-koordinat i pixlar |
| x1 | nedre högra X-koordinaten i pixlar |
| y1 | nedre högra Y-koordinaten i pixlar |
</dd>
<dt>Se även</dt><dd>
[frect]
</dd>
</dl>
<hr>
## frect

```c
void frect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en fylld rektangel.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | övre vänstra hörnet X-koordinat i pixlar |
| y0 | övre vänstra hörnet Y-koordinat i pixlar |
| x1 | nedre högra X-koordinaten i pixlar |
| y1 | nedre högra Y-koordinaten i pixlar |
</dd>
<dt>Se även</dt><dd>
[rect]
</dd>
</dl>
<hr>
## circ

```c
void circ(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en cirkel.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x | center X-koordinaten i pixlar |
| y | center Y-koordinaten i pixlar |
| r | radie i pixlar |
</dd>
<dt>Se även</dt><dd>
[fcirc], [ellip], [fellip]
</dd>
</dl>
<hr>
## fcirc

```c
void fcirc(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en fylld cirkel.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x | center X-koordinaten i pixlar |
| y | center Y-koordinaten i pixlar |
| r | radie i pixlar |
</dd>
<dt>Se även</dt><dd>
[circ], [ellip], [fellip]
</dd>
</dl>
<hr>
## ellip

```c
void ellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en ellips.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | övre vänstra hörnet X-koordinat i pixlar |
| y0 | övre vänstra hörnet Y-koordinat i pixlar |
| x1 | nedre högra X-koordinaten i pixlar |
| y1 | nedre högra Y-koordinaten i pixlar |
</dd>
<dt>Se även</dt><dd>
[circ], [fcirc], [fellip]
</dd>
</dl>
<hr>
## fellip

```c
void fellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar en fylld ellips.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
| x0 | övre vänstra hörnet X-koordinat i pixlar |
| y0 | övre vänstra hörnet Y-koordinat i pixlar |
| x1 | nedre högra X-koordinaten i pixlar |
| y1 | nedre högra Y-koordinaten i pixlar |
</dd>
<dt>Se även</dt><dd>
[circ], [fcirc], [ellip]
</dd>
</dl>
<hr>
## move

```c
void move(int16_t x, int16_t y, uint16_t deg)
```
<dl>
<dt>Beskrivning</dt><dd>
Flyttar sköldpaddan till den givna positionen på skärmen eller i labyrinten.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| x | X-koordinat i pixlar (eller 1/128 brickor med [maze]) |
| y | Y-koordinat i pixlar |
| deg | riktning i grader, 0 till 359, 0 är uppåt på skärmen, 90 är till höger |
</dd>
<dt>Se även</dt><dd>
[left], [right], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## left

```c
void left(uint16_t deg)
```
<dl>
<dt>Beskrivning</dt><dd>
Svänger sköldpaddan till vänster.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| deg | förändring i grader, 0 till 359 |
</dd>
<dt>Se även</dt><dd>
[move], [right], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## right

```c
void right(uint16_t deg)
```
<dl>
<dt>Beskrivning</dt><dd>
Svänger sköldpaddan till höger.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| deg | förändring i grader, 0 till 359 |
</dd>
<dt>Se även</dt><dd>
[move], [left], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## up

```c
void up(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Lyfter upp sköldpaddans svans. Sköldpaddan kommer att röra sig utan att dra en linje.
</dd>
<dt>Se även</dt><dd>
[move], [left], [right], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## down

```c
void down(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Lägger ner sköldpaddans svans. Sköldpaddan kommer att flytta och dra en linje (se [color]).
</dd>
<dt>Se även</dt><dd>
[move], [left], [right], [up], [color], [forw], [back]
</dd>
</dl>
<hr>
## color

```c
void color(uint8_t palidx)
```
<dl>
<dt>Beskrivning</dt><dd>
Ställer in sköldpaddsfärg.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| palidx | färg, palettindex 0 till 255 |
</dd>
<dt>Se även</dt><dd>
[move], [left], [right], [up], [down], [forw], [back]
</dd>
</dl>
<hr>
## forw

```c
void forw(uint16_t cnt)
```
<dl>
<dt>Beskrivning</dt><dd>
Flyttar sköldpaddan framåt.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| cnt | mängd i pixlar (eller 1/128 brickor med [maze]) |
</dd>
<dt>Se även</dt><dd>
[move], [left], [right], [up], [down], [color], [back]
</dd>
</dl>
<hr>
## back

```c
void back(uint16_t cnt)
```
<dl>
<dt>Beskrivning</dt><dd>
Flyttar sköldpaddan bakåt.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| cnt | mängd i pixlar (eller 1/128 brickor med [maze]) |
</dd>
<dt>Se även</dt><dd>
[move], [left], [right], [up], [down], [color], [forw]
</dd>
</dl>
<hr>
## spr

```c
void spr(int16_t x, int16_t y, uint16_t sprite, uint8_t sw, uint8_t sh, int8_t scale, uint8_t type)
```
<dl>
<dt>Beskrivning</dt><dd>
Visar en sprite eller flera intilliggande sprites.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| x | X-koordinat i pixlar |
| y | Y-koordinat i pixlar |
| sprite | sprite-id, 0 till 1023 |
| sw | antal horisontella sprites |
| sh | antal vertikala sprites |
| scale | skala, -3 till 4 |
| type | transformera, 0=normal, 1=rotera 90, 2=rotera 180, 3=rotera 270, 4=vänd vertik., 5=vänd+90, 6=vänd horis., 7=vänd+270 |
</dd>
<dt>Se även</dt><dd>
[dlg], [stext]
</dd>
</dl>
<hr>
## dlg

```c
void dlg(int16_t x, int16_t y, uint16_t w, uint16_t h, int8_t scale,
    uint16_t tl, uint16_t tm, uint16_t tr,
    uint16_t ml, uint16_t bg, uint16_t mr,
    uint16_t bl, uint16_t bm, uint16_t br)
```
<dl>
<dt>Beskrivning</dt><dd>
Visar ett dialogfönster med sprites.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| x | X-koordinat i pixlar |
| y | Y-koordinat i pixlar |
| w | dialogrutans bredd i pixlar |
| h | dialogrutans höjd i pixlar |
| scale | skala, -3 till 4 |
| tl | övre vänstra hörnet sprite id |
| tm | övre mitten sprite id |
| tr | övre högra hörnet sprite id |
| ml | mitten vänster sida sprite id |
| bg | bakgrund sprite id |
| mr | mitten höger sida sprite id |
| bl | nedre vänstra hörnet sprite id |
| bm | nedre mitten sprite id |
| br | nedre högra hörnet sprite id |
</dd>
<dt>Se även</dt><dd>
[spr], [stext]
</dd>
</dl>
<hr>
## stext

```c
void stext(int16_t x, int16_t y, uint16_t fs, uint16_t fu, uint8_t sw, uint8_t sh, int8_t scale, str_t str)
```
<dl>
<dt>Beskrivning</dt><dd>
Visar text på skärmen med sprites.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| x | X-koordinat i pixlar |
| y | Y-koordinat i pixlar |
| fs | första sprite-id som ska användas för visning |
| fu | första UNICODE (minsta tecknet) i strängen |
| sw | antal horisontella sprites |
| sh | antal vertikala sprites |
| scale | skala, -3 till 4 |
| str | noll avslutad UTF-8-sträng |
</dd>
<dt>Se även</dt><dd>
[spr], [dlg]
</dd>
</dl>
<hr>
## remap

```c
void remap(addr_t replace)
```
<dl>
<dt>Beskrivning</dt><dd>
Ersätter brickor på map. Kan användas för att animera brickor på map.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| replace | en uppsättning av 256 sprite id |
</dd>
<dt>Se även</dt><dd>
[mget], [mset], [map], [maze]
</dd>
</dl>
<hr>
## mget

```c
uint16_t mget(uint16_t mx, uint16_t my)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar en bricka på map.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| mx | X-koordinat på map i brickor |
| my | Y-koordinat på map i brickor |
</dd>
<dt>Returvärde</dt><dd>
Brickans sprite-id vid den givna koordinaten.
</dd>
<dt>Se även</dt><dd>
[remap], [mset], [map], [maze]
</dd>
</dl>
<hr>
## mset

```c
void mset(uint16_t mx, uint16_t my, uint16_t sprite)
```
<dl>
<dt>Beskrivning</dt><dd>
Sätter en bricka på map.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| mx | X-koordinat på map i brickor |
| my | Y-koordinat på map i brickor |
| sprite | sprite id, 0 till 1023 |
</dd>
<dt>Se även</dt><dd>
[remap], [mget], [map], [maze]
</dd>
</dl>
<hr>
## map

```c
void map(int16_t x, int16_t y, uint16_t mx, uint16_t my, uint16_t mw, uint16_t mh, int8_t scale)
```
<dl>
<dt>Beskrivning</dt><dd>
Ritar (en del av) map.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| x | X-koordinat i pixlar |
| y | Y-koordinat i pixlar |
| mx | X-koordinat på map i brickor |
| my | Y-koordinat på map i brickor |
| mw | antal horisontella brickor |
| mh | antal vertikala brickor |
| scale | skala, -3 till 4 |
</dd>
<dt>Se även</dt><dd>
[remap], [mget], [mset], [maze]
</dd>
</dl>
<hr>
## maze

```c
void maze(uint16_t mx, uint16_t my, uint16_t mw, uint16_t mh, uint8_t scale,
    uint16_t sky, uint16_t grd, uint16_t door, uint16_t wall, uint16_t obj, uint8_t numnpc, addr_t npc)
```
<dl>
<dt>Beskrivning</dt><dd>
Visar map som en 3D-labyrint, med hjälp av sköldpaddans position.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| mx | X-koordinat på map i brickor |
| my | Y-koordinat på map i brickor |
| mw | antal horisontella brickor |
| mh | antal vertikala brickor |
| scale | antal sprites per bricka i kraft av två, 0 till 3 |
| sky | himmel kakel index |
| grd | markplattor index |
| door | första dörrkakelindex |
| wall | första väggkakelindex |
| obj | första objektbricka index |
| numnpc | antal NPC-poster |
| npc | en uint32_t array av numnpc gånger x,y,sprite id tripletter |
</dd>
<dt>Se även</dt><dd>
[remap], [mget], [mset], [map]
</dd>
</dl>

# Indata

## getpad

```c
int getpad(int pad, int btn)
```
<dl>
<dt>Beskrivning</dt><dd>
Hämtar det aktuella tillståndet för en gamepad-knapp.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| pad | gamepad-index, 0 till 3 |
| btn | en av [gamepad]-knapparna, `BTN_` |
</dd>
<dt>Returvärde</dt><dd>
Noll om den inte trycks ned, inte noll om den trycks ned.
</dd>
<dt>Se även</dt><dd>
[prspad], [relpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## prspad

```c
int prspad(int pad, int btn)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar sant om gamepad-knappen trycktes in sedan senaste samtalet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| pad | gamepad-index, 0 till 3 |
| btn | en av [gamepad]-knapparna, `BTN_` |
</dd>
<dt>Returvärde</dt><dd>
Noll om den inte trycks ned, inte noll om den trycks ned.
</dd>
<dt>Se även</dt><dd>
[relpad], [getpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## relpad

```c
int relpad(int pad, int btn)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar sant om gamepad-knappen släpptes sedan senaste samtalet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| pad | gamepad-index, 0 till 3 |
| btn | en av [gamepad]-knapparna, `BTN_` |
</dd>
<dt>Returvärde</dt><dd>
Noll om den inte släpptes, icke-noll om den släpptes.
</dd>
<dt>Se även</dt><dd>
[prspad], [getpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## getbtn

```c
int getbtn(int btn)
```
<dl>
<dt>Beskrivning</dt><dd>
Får musknapparnas tillstånd.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| btn | en av [pekare]-knapparna, `BTN_` eller `SCR_` |
</dd>
<dt>Returvärde</dt><dd>
Noll om den inte trycks ned, inte noll om den trycks ned.
</dd>
<dt>Se även</dt><dd>
[prspad], [relpad], [getpad], [getclk], [getkey]
</dd>
</dl>
<hr>
## getclk

```c
int getclk(int btn)
```
<dl>
<dt>Beskrivning</dt><dd>
Får musknappsklickning.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| btn | en av [pekare]-knapparna, `BTN_` |
</dd>
<dt>Returvärde</dt><dd>
Noll om man inte klickar, inte noll om man klickar.
</dd>
<dt>Se även</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getkey]
</dd>
</dl>
<hr>
## getkey

```c
int getkey(int sc)
```
<dl>
<dt>Beskrivning</dt><dd>
Hämtar det aktuella tillståndet för en nyckel.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| sc | skanningskod, 1 till 144, se [tangentbord] |
</dd>
<dt>Returvärde</dt><dd>
Noll om den inte trycks ned, inte noll om den trycks ned.
</dd>
<dt>Se även</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getclk]
</dd>
</dl>
<hr>
## popkey

```c
uint32_t popkey(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Poppa en UTF-8-nyckel från tangentbordskön. Se [tangentbord] och för blockeringsversionen [getc].
</dd>
<dt>Returvärde</dt><dd>
UTF-8-representationen av nyckeln, eller 0 om kön var tom (ingen blockering).
</dd>
<dt>Se även</dt><dd>
[pendkey], [lenkey], [speckey], [getc]
</dd>
</dl>
<hr>
## pendkey

```c
int pendkey(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar sant om det finns en väntande nyckel i kön (men lämnar nyckeln i kön, poppar den inte).
</dd>
<dt>Returvärde</dt><dd>
Returnerar 1 om det finns nycklar i kön väntande.
</dd>
<dt>Se även</dt><dd>
[popkey], [lenkey], [speckey]
</dd>
</dl>
<hr>
## lenkey

```c
int lenkey(uint32_t key)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar längden på en UTF-8-nyckel i byte.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| key | nyckeln, ploppade ur kön |
</dd>
<dt>Returvärde</dt><dd>
UTF-8-representationens längd i byte.
</dd>
<dt>Se även</dt><dd>
[popkey], [pendkey], [speckey]
</dd>
</dl>
<hr>
## speckey

```c
int speckey(uint32_t key)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar sant om nyckeln är en specialnyckel.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| key | nyckeln, ploppade ur kön |
</dd>
<dt>Returvärde</dt><dd>
Returnerar 1 om det är en specialnyckel och 0 om det är en utskrivbar.
</dd>
<dt>Se även</dt><dd>
[popkey], [pendkey], [lenkey]
</dd>
</dl>

# Matematik

## rand

```c
uint32_t rand(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Bli slumpmässig. Använd `%` modulo för att göra den mindre, till exempel returnerar `1 + rand() % 6` slumpmässigt
mellan 1 och 6, som en tärning.
</dd>
<dt>Returvärde</dt><dd>
Ett slumptal mellan 0 och 2^^32^^-1 (4294967295).
</dd>
<dt>Se även</dt><dd>
[rnd]
</dd>
</dl>
<hr>
## rnd

```c
float rnd(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Bli slumpmässig. Samma som [rand], men returnerar ett flyttal.
</dd>
<dt>Returvärde</dt><dd>
Ett slumptal mellan 0.0 och 1.0.
</dd>
<dt>Se även</dt><dd>
[rand]
</dd>
</dl>
<hr>
## float

```c
float float(int val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar flyttalsmotsvarigheten till ett heltal.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Värdets flytande punkt.
</dd>
<dt>Se även</dt><dd>
[int]
</dd>
</dl>
<hr>
## int

```c
int int(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar heltalsekvivalenten till ett flyttal.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Heltalet för värde.
</dd>
<dt>Se även</dt><dd>
[float]
</dd>
</dl>
<hr>
## floor

```c
float floor(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar det största heltal som inte är större än värdet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Värdegolvet.
</dd>
<dt>Se även</dt><dd>
[ceil]
</dd>
</dl>
<hr>
## ceil

```c
float ceil(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar det minsta heltal som inte är mindre än värdet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Värdets tak.
</dd>
<dt>Se även</dt><dd>
[floor]
</dd>
</dl>
<hr>
## sgn

```c
float sgn(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar värdets tecken.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Antingen 1.0 eller -1.0.
</dd>
<dt>Se även</dt><dd>
[abs]
</dd>
</dl>
<hr>
## abs

```c
float abs(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar värdets absoluta värde.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Antingen värde eller -värde, alltid positivt.
</dd>
<dt>Se även</dt><dd>
[sgn]
</dd>
</dl>
<hr>
## exp

```c
float exp(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar värdets exponential, dvs basen av naturliga logaritmer upphöjda till värdets potens.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Returnerar e^^val^^.
</dd>
<dt>Se även</dt><dd>
[log], [pow]
</dd>
</dl>
<hr>
## log

```c
float log(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar den naturliga logaritmen för värdet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Returnerar naturlig logaritm av värde.
</dd>
<dt>Se även</dt><dd>
[exp]
</dd>
</dl>
<hr>
## pow

```c
float pow(float val, float exp)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar värdet upphöjt till exponentpotensen. Detta är en långsam operation, försök att undvika.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
| exp | exponent |
</dd>
<dt>Returvärde</dt><dd>
Returnerar val^^exp^^.
</dd>
<dt>Se även</dt><dd>
[exp], [sqrt], [rsqrt]
</dd>
</dl>
<hr>
## sqrt

```c
float sqrt(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar kvadratroten av värdet. Detta är en långsam operation, försök att undvika.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Kvadratroten av värdet.
</dd>
<dt>Se även</dt><dd>
[pow], [rsqrt]
</dd>
</dl>
<hr>
## rsqrt

```c
float rsqrt(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar den reciproka av kvadratroten av värdet (`1 / sqrt(val)`). Använder John Carmacks snabbmetod.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
</dd>
<dt>Returvärde</dt><dd>
Reciprok av kvadratroten av värdet.
</dd>
<dt>Se även</dt><dd>
[pow], [sqrt]
</dd>
</dl>
<hr>
## clamp

```c
float clamp(float val, float minv, float maxv)
```
<dl>
<dt>Beskrivning</dt><dd>
Klämmer ett värde mellan gränserna.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde |
| minv | lägsta värde |
| maxv | högsta värde |
</dd>
<dt>Returvärde</dt><dd>
Inspänt värde.
</dd>
<dt>Se även</dt><dd>
[clampv2], [clampv3], [clampv4]
</dd>
</dl>
<hr>
## lerp

```c
float lerp(float a, float b, float t)
```
<dl>
<dt>Beskrivning</dt><dd>
Linjär interpolerar två tal.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | första flytnummer |
| b | andra flytnummer |
| t | interpolationsvärde mellan 0.0 och 1.0 |
</dd>
<dt>Se även</dt><dd>
[lerpv2], [lerpv3], [lerpv4], [lerpq], [slerpq]
</dd>
</dl>
<hr>
## pi

```c
float pi(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar π som ett flyttal.
</dd>
<dt>Returvärde</dt><dd>
Värdet 3.14159265358979323846.
</dd>
</dl>
<hr>
## cos

```c
float cos(uint16_t deg)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar cosinus.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| deg | grad, 0 till 359, 0 är upp, 90 till höger |
</dd>
<dt>Returvärde</dt><dd>
Cosinus för graden, mellan -1.0 till 1.0.
</dd>
<dt>Se även</dt><dd>
[sin], [tan], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## sin

```c
float sin(uint16_t deg)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar sinus.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| deg | grad, 0 till 359, 0 är upp, 90 till höger |
</dd>
<dt>Returvärde</dt><dd>
Gradens sinus, mellan -1.0 till 1.0.
</dd>
<dt>Se även</dt><dd>
[cos], [tan], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## tan

```c
float tan(uint16_t deg)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar tangent.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| deg | grad, 0 till 359, 0 är upp, 90 till höger |
</dd>
<dt>Returvärde</dt><dd>
Tangent av graden, mellan -1.0 till 1.0.
</dd>
<dt>Se även</dt><dd>
[cos], [sin], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## acos

```c
uint16_t acos(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar arcus cosinus.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde, -1.0 till 1.0 |
</dd>
<dt>Returvärde</dt><dd>
Arcus cosinus i grad, 0 till 359, 0 är upp, 90 till höger.
</dd>
<dt>Se även</dt><dd>
[cos], [sin], [tan], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## asin

```c
uint16_t asin(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar arcus sinus.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde, -1.0 till 1.0 |
</dd>
<dt>Returvärde</dt><dd>
Arcus sinus i grad, 0 till 359, 0 är upp, 90 till höger.
</dd>
<dt>Se även</dt><dd>
[cos], [sin], [tan], [acos], [atan], [atan2]
</dd>
</dl>
<hr>
## atan

```c
uint16_t atan(float val)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar arcus tangent.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| val | värde, -1.0 till 1.0 |
</dd>
<dt>Returvärde</dt><dd>
Arcus tangent i grad, 0 till 359, 0 är uppåt, 90 åt höger.
</dd>
<dt>Se även</dt><dd>
[cos], [sin], [tan], [acos], [asin], [atan2]
</dd>
</dl>
<hr>
## atan2

```c
uint16_t atan2(float y, float x)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar arcus tangens för y/x, med hjälp av tecknen för y och x för att bestämma kvadranten.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| y | Y koordinat |
| x | X koordinat |
</dd>
<dt>Returvärde</dt><dd>
Arcus tangent i grad, 0 till 359, 0 är uppåt, 90 åt höger.
</dd>
<dt>Se även</dt><dd>
[cos], [sin], [tan], [acos], [asin]
</dd>
</dl>
<hr>
## dotv2

```c
float dotv2(addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar punktprodukt av två vektorer med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för två flottörer |
| b | adress för två flottörer |
</dd>
<dt>Returvärde</dt><dd>
Punktprodukt av vektorerna.
</dd>
<dt>Se även</dt><dd>
[lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## lenv2

```c
float lenv2(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar längden på en vektor med två element. Detta är långsamt, försök att undvika (se [normv2]).
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för två flottörer |
</dd>
<dt>Returvärde</dt><dd>
Längden på vektorn.
</dd>
<dt>Se även</dt><dd>
[dotv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## scalev2

```c
void scalev2(addr_t a, float s)
```
<dl>
<dt>Beskrivning</dt><dd>
Skalar en vektor med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för två flottörer |
| s | skalningsvärde |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## negv2

```c
void negv2(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Negerar en vektor med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för två flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [scalev2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## addv2

```c
void addv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Lägger ihop vektorer med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för två flottörer |
| a | adress för två flottörer |
| b | adress för två flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## subv2

```c
void subv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Subtraherar vektorer med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för två flottörer |
| a | adress för två flottörer |
| b | adress för två flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## mulv2

```c
void mulv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Multiplicerar vektorer med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för två flottörer |
| a | adress för två flottörer |
| b | adress för två flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## divv2

```c
void divv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Delar vektorer med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för två flottörer |
| a | adress för två flottörer |
| b | adress för två flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## clampv2

```c
void clampv2(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Beskrivning</dt><dd>
Klämmer vektorer med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för två flottörer |
| v | adress för två flottörer, indata |
| minv | adress för två flottörer, minimum |
| maxv | adress för två flottörer, maximum |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## lerpv2

```c
void lerpv2(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Beskrivning</dt><dd>
Linjär interpolerar vektorer med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för två flottörer |
| a | adress för två flottörer |
| b | adress för två flottörer |
| t | interpolationsvärde mellan 0.0 och 1.0 |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [normv2]
</dd>
</dl>
<hr>
## normv2

```c
void normv2(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Normaliserar en vektor med två element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för två flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2]
</dd>
</dl>
<hr>
## dotv3

```c
float dotv3(addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar punktprodukt av två vektorer med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för tre flottörer |
| b | adress för tre flottörer |
</dd>
<dt>Returvärde</dt><dd>
Punktprodukt av vektorerna.
</dd>
<dt>Se även</dt><dd>
[lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## lenv3

```c
float lenv3(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar längden på en vektor med tre element. Detta är långsamt, försök att undvika (se [normv3]).
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för tre flottörer |
</dd>
<dt>Returvärde</dt><dd>
Längden på vektorn.
</dd>
<dt>Se även</dt><dd>
[dotv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## scalev3

```c
void scalev3(addr_t a, float s)
```
<dl>
<dt>Beskrivning</dt><dd>
Skalar en vektor med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för tre flottörer |
| s | skalningsvärde |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## negv3

```c
void negv3(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Negerar en vektor med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## addv3

```c
void addv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Lägger ihop vektorer med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| a | adress för tre flottörer |
| b | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## subv3

```c
void subv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Subtraherar vektorer med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| a | adress för tre flottörer |
| b | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## mulv3

```c
void mulv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Multiplicerar vektorer med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| a | adress för tre flottörer |
| b | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## divv3

```c
void divv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Delar vektorer med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| a | adress för tre flottörer |
| b | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## crossv3

```c
void crossv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar korsprodukten av vektorer med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| a | adress för tre flottörer |
| b | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## clampv3

```c
void clampv3(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Beskrivning</dt><dd>
Klämmer vektorer med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| v | adress för tre flottörer, indata |
| minv | adress för tre flottörer, minimum |
| maxv | adress för tre flottörer, maximum |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## lerpv3

```c
void lerpv3(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Beskrivning</dt><dd>
Linjär interpolerar vektorer med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| a | adress för tre flottörer |
| b | adress för tre flottörer |
| t | interpolationsvärde mellan 0.0 och 1.0 |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [normv3]
</dd>
</dl>
<hr>
## normv3

```c
void normv3(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Normaliserar en vektor med tre element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3]
</dd>
</dl>
<hr>
## dotv4

```c
float dotv4(addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar punktprodukt av två vektorer med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Returvärde</dt><dd>
Punktprodukt av vektorerna.
</dd>
<dt>Se även</dt><dd>
[lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## lenv4

```c
float lenv4(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar längden på en vektor med fyra element. Detta är långsamt, försök att undvika (se [normv4]).
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
</dd>
<dt>Returvärde</dt><dd>
Längden på vektorn.
</dd>
<dt>Se även</dt><dd>
[dotv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## scalev4

```c
void scalev4(addr_t a, float s)
```
<dl>
<dt>Beskrivning</dt><dd>
Skalar en vektor med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
| s | skalningsvärde |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## negv4

```c
void negv4(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Negerar en vektor med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [scalev4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## addv4

```c
void addv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Lägger ihop vektorer med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [negv4], [scalev4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## subv4

```c
void subv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Subtraherar vektorer med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## mulv4

```c
void mulv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Multiplicerar vektorer med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## divv4

```c
void divv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Delar vektorer med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## clampv4

```c
void clampv4(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Beskrivning</dt><dd>
Klämmer vektorer med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| v | adress för fyra flottörer, indata |
| minv | adress för fyra flottörer, minimum |
| maxv | adress för fyra flottörer, maximum |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## lerpv4

```c
void lerpv4(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Beskrivning</dt><dd>
Linjär interpolerar vektorer med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
| t | interpolationsvärde mellan 0.0 och 1.0 |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [normv4]
</dd>
</dl>
<hr>
## normv4

```c
void normv4(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Normaliserar en vektor med fyra element.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4]
</dd>
</dl>
<hr>
## idq

```c
void idq(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Laddar identitetskvartjon.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## eulerq

```c
void eulerq(addr_t dst, uint16_t pitch, uint16_t yaw, uint16_t roll)
```
<dl>
<dt>Beskrivning</dt><dd>
Laddar en kvartjon med Euler-vinklar.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| pitch | rotation runt X-axeln i grader, 0 till 359 |
| yaw | rotation runt Y-axeln i grader, 0 till 359 |
| roll | rotation runt Z-axeln i grader, 0 till 359 |
</dd>
<dt>Se även</dt><dd>
[idq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## dotq

```c
float dotq(addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar punktprodukt av en kvartjon.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Returvärde</dt><dd>
Prickprodukt av quaternion.
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## lenq

```c
float lenq(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar längden på en kvartjon.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
</dd>
<dt>Returvärde</dt><dd>
Kvaternionens längd.
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## scaleq

```c
void scaleq(addr_t a, float s)
```
<dl>
<dt>Beskrivning</dt><dd>
Skalar en kvartjon.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
| s | skalningsvärde |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## negq

```c
void negq(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Negerar en kvartjon.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## addq

```c
void addq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Lägger samman kvaternioner.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## subq

```c
void subq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Subtraherar kvaternioner.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## mulq

```c
void mulq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Multiplicerar kvaternioner.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## rotq

```c
void rotq(addr_t dst, addr_t q, addr_t v)
```
<dl>
<dt>Beskrivning</dt><dd>
Roterar en vektor med tre element med en kvaternion.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| q | adress för fyra flottörer |
| v | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## lerpq

```c
void lerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Beskrivning</dt><dd>
Linjär interpolerar två kvaternioner.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
| t | interpolationsvärde mellan 0.0 och 1.0 |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [slerpq], [normq]
</dd>
</dl>
<hr>
## slerpq

```c
void slerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Beskrivning</dt><dd>
Sfärisk interpolerar en kvaternion.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| a | adress för fyra flottörer |
| b | adress för fyra flottörer |
| t | interpolationsvärde mellan 0.0 och 1.0 |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [normq]
</dd>
</dl>
<hr>
## normq

```c
void normq(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Normaliserar en quaternion.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq]
</dd>
</dl>
<hr>
## idm4

```c
void idm4(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Laddar en 4 x 4 identitetsmatris.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för 16 flottörer |
</dd>
<dt>Se även</dt><dd>
[trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## trsm4

```c
void trsm4(addr_t dst, addr_t t, addr_t r, addr_t s)
```
<dl>
<dt>Beskrivning</dt><dd>
Skapar en 4 x 4 matris med translation, rotation och skalning.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för 16 flottörer, destinationsmatris |
| t | adress för tre flottörer, översättningsvektor |
| r | adress för fyra flottörer, rotation kvaternion |
| s | adress för tre flottörer, skalningsvektor |
</dd>
<dt>Se även</dt><dd>
[idm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## detm4

```c
float detm4(addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar matrisens determinant.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| a | adress för 16 flottörer |
</dd>
<dt>Returvärde</dt><dd>
Matrisens determinant.
</dd>
<dt>Se även</dt><dd>
[idm4], [trsm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## addm4

```c
void addm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Lägger ihop matriser.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för 16 flottörer |
| a | adress för 16 flottörer |
| b | adress för 16 flottörer |
</dd>
<dt>Se även</dt><dd>
[idm4], [trsm4], [detm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## subm4

```c
void subm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Subtraherar matriser.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för 16 flottörer |
| a | adress för 16 flottörer |
| b | adress för 16 flottörer |
</dd>
<dt>Se även</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4

```c
void mulm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Beskrivning</dt><dd>
Multiplicerar matriser.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för 16 flottörer |
| a | adress för 16 flottörer |
| b | adress för 16 flottörer |
</dd>
<dt>Se även</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4v3

```c
void mulm4v3(addr_t dst, addr_t m, addr_t v)
```
<dl>
<dt>Beskrivning</dt><dd>
Multiplicerar en vektor med tre element med en matris.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för tre flottörer |
| m | adress för 16 flottörer |
| v | adress för tre flottörer |
</dd>
<dt>Se även</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4v4

```c
void mulm4v4(addr_t dst, addr_t m, addr_t v)
```
<dl>
<dt>Beskrivning</dt><dd>
Multiplicerar en vektor med fyra element med en matris.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för fyra flottörer |
| m | adress för 16 flottörer |
| v | adress för fyra flottörer |
</dd>
<dt>Se även</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [invm4], [trpm4]
</dd>
</dl>
<hr>
## invm4

```c
void invm4(addr_t dst, addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Beräknar invers matris.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för 16 flottörer |
| a | adress för 16 flottörer |
</dd>
<dt>Se även</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [trpm4]
</dd>
</dl>
<hr>
## trpm4

```c
void trpm4(addr_t dst, addr_t a)
```
<dl>
<dt>Beskrivning</dt><dd>
Transponera matris.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress för 16 flottörer |
| a | adress för 16 flottörer |
</dd>
<dt>Se även</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4]
</dd>
</dl>
<hr>
## trns

```c
void trns(addr_t dst, addr_t src, uint8_t num,
    int16_t x, int16_t y, int16_t z,
    uint16_t pitch, uint16_t yaw, uint16_t roll,
    float scale)
```
<dl>
<dt>Beskrivning</dt><dd>
Översätt ett vertexmoln, aka. placera en 3D-modell i [3D-utrymme].
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | destinationspunktsarray, 3 x 2 byte vardera, X, Y, Z |
| src | källvertices array, 3 x 2 byte vardera, X, Y, Z |
| num | antal vertexkoordinattripletter i arrayen |
| x | världens X-koordinat, -32767 till 32767 |
| y | världens Y-koordinat, -32767 till 32767 |
| z | världens Z-koordinat, -32767 till 32767 |
| pitch | rotation runt X-axeln i grader, 0 till 359 |
| yaw | rotation runt Y-axeln i grader, 0 till 359 |
| roll | rotation runt Z-axeln i grader, 0 till 359 |
| scale | skalning, använd 1.0 för att behålla originalstorleken |
</dd>
<dt>Se även</dt><dd>
[mesh]
</dd>
</dl>

# Minne

## inb

```c
uint8_t inb(addr_t src)
```
<dl>
<dt>Beskrivning</dt><dd>
Läs i en byte från minnet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| src | adress, 0x00000 till 0xBFFFF |
</dd>
<dt>Returvärde</dt><dd>
Returnerar värdet på den adressen.
</dd>
</dl>
<hr>
## inw

```c
uint16_t inw(addr_t src)
```
<dl>
<dt>Beskrivning</dt><dd>
Läs in ett ord (word, två byte) från minnet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| src | adress, 0x00000 till 0xBFFFE |
</dd>
<dt>Returvärde</dt><dd>
Returnerar värdet på den adressen.
</dd>
</dl>
<hr>
## ini

```c
uint32_t ini(addr_t src)
```
<dl>
<dt>Beskrivning</dt><dd>
Läs in ett heltal (int, fyra byte) från minnet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| src | adress, 0x00000 till 0xBFFFC |
</dd>
<dt>Returvärde</dt><dd>
Returnerar värdet på den adressen.
</dd>
</dl>
<hr>
## outb

```c
void outb(addr_t dst, uint8_t value)
```
<dl>
<dt>Beskrivning</dt><dd>
Skriv ut en byte till minnet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress, 0x00000 till 0xBFFFF |
| value | värde att ställa in, 0 till 255 |
</dd>
</dl>
<hr>
## outw

```c
void outw(addr_t dst, uint16_t value)
```
<dl>
<dt>Beskrivning</dt><dd>
Skriv ut ett ord (word, två byte) till minnet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress, 0x00000 till 0xBFFFE |
| value | värde att ställa in, 0 till 65535 |
</dd>
</dl>
<hr>
## outi

```c
void outi(addr_t dst, uint32_t value)
```
<dl>
<dt>Beskrivning</dt><dd>
Skriv ut ett heltal (int, fyra byte) till minnet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | adress, 0x00000 till 0xBFFFC |
| value | värde att ställa in, 0 till 4294967295 |
</dd>
</dl>
<hr>
## memsave

```c
int memsave(uint8_t overlay, addr_t src, uint32_t size)
```
<dl>
<dt>Beskrivning</dt><dd>
Sparar minnesområde för överlagring.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| overlay | index för överlagring att skriva till, 0 till 255 |
| src | minnesoffset att spara från, 0x00000 till 0xBFFFF |
| size | antal byte att spara |
</dd>
<dt>Returvärde</dt><dd>
Returnerar 1 vid framgång, 0 vid fel.
</dd>
<dt>Se även</dt><dd>
[memload]
</dd>
</dl>
<hr>
## memload

```c
int memload(addr_t dst, uint8_t overlay, uint32_t maxsize)
```
<dl>
<dt>Beskrivning</dt><dd>
Laddar en överlagring i det angivna minnesområdet.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | minnesoffset att ladda till, 0x00000 till 0xBFFFF |
| overlay | index för överlagring att läsa från, 0 till 255 |
| maxsize | maximalt antal byte att ladda |
</dd>
<dt>Returvärde</dt><dd>
Returnerar antalet byte som faktiskt laddats.
</dd>
<dt>Se även</dt><dd>
[memsave]
</dd>
</dl>
<hr>
## memcpy

```c
void memcpy(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Beskrivning</dt><dd>
Kopiera minnesområden.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | destinationsadress, 0x00000 till 0xBFFFF |
| src | källadress, 0x00000 till 0xBFFFF |
| len | antal byte att kopiera |
</dd>
</dl>
<hr>
## memset

```c
void memset(addr_t dst, uint8_t value, uint32_t len)
```
<dl>
<dt>Beskrivning</dt><dd>
Ställ in minnesregionen till ett givet värde.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | destinationsadress, 0x00000 till 0xBFFFF |
| value | värde att ställa in, 0 till 255 |
| len | antal byte att ställa in |
</dd>
</dl>
<hr>
## memcmp

```c
int memcmp(addr_t addr0, addr_t addr1, uint32_t len)
```
<dl>
<dt>Beskrivning</dt><dd>
Jämför minnesregioner.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| addr0 | första adressen, 0x00000 till 0xBFFFF |
| addr1 | andra adress, 0x00000 till 0xBFFFF |
| len | antal byte att jämföra |
</dd>
<dt>Returvärde</dt><dd>
Returnerar skillnaden, 0 om de två minnesregionerna matchar.
</dd>
</dl>
<hr>
## deflate

```c
int deflate(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Beskrivning</dt><dd>
Komprimera en buffert med RFC1950 deflate (zlib).
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | destinationsadress, 0x30000 till 0xBFFFF |
| src | källadress, 0x30000 till 0xBFFFF |
| len | antal byte att komprimera |
</dd>
<dt>Returvärde</dt><dd>
0 eller negativ vid fel, annars längden på den komprimerade bufferten och komprimerade data i dst.
</dd>
<dt>Se även</dt><dd>
[inflate]
</dd>
</dl>
<hr>
## inflate

```c
int inflate(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Beskrivning</dt><dd>
Dekomprimera en buffert med RFC1950 deflate (zlib) komprimerad data.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| dst | destinationsadress, 0x30000 till 0xBFFFF |
| src | källadress, 0x30000 till 0xBFFFF |
| len | antal komprimerade byte |
</dd>
<dt>Returvärde</dt><dd>
0 eller negativ vid fel, annars längden på den okomprimerade bufferten och okomprimerade data i dst.
</dd>
<dt>Se även</dt><dd>
[deflate]
</dd>
</dl>
<hr>
## time

```c
float time(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar antalet bockar sedan strömmen slogs på.
</dd>
<dt>Returvärde</dt><dd>
Den förflutna tiden i millisekunder sedan strömmen slogs på.
</dd>
<dt>Se även</dt><dd>
[now]
</dd>
</dl>
<hr>
## now

```c
uint32_t now(void)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar UNIX-tidsstämpeln. Kontrollera byten vid offset 0000C för att se om den svämmar över.
</dd>
<dt>Returvärde</dt><dd>
Den förflutna tiden i sekunder sedan midnatt den 1 januari 1970, Greenwich Mean Time.
</dd>
<dt>Se även</dt><dd>
[time]
</dd>
</dl>
<hr>
## atoi

```c
int atoi(str_t src)
```
<dl>
<dt>Beskrivning</dt><dd>
Konverterar en ASCII-decimalsträng till ett heltal.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| src | strängadress, 0x00000 till 0xBFFFF |
</dd>
<dt>Returvärde</dt><dd>
The number value of the string.
</dd>
<dt>Se även</dt><dd>
[itoa], [str], [val]
</dd>
</dl>
<hr>
## itoa

```c
str_t itoa(int value)
```
<dl>
<dt>Beskrivning</dt><dd>
Konverterar ett heltal till en ASCII-decimalsträng.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| value | värdet, -2147483648 till 2147483647 |
</dd>
<dt>Returvärde</dt><dd>
Den konverterade strängen.
</dd>
<dt>Se även</dt><dd>
[atoi], [str], [val]
</dd>
</dl>
<hr>
## val

```c
float val(str_t src)
```
<dl>
<dt>Beskrivning</dt><dd>
Konverterar en ASCII-decimalsträng till ett flyttal.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| src | strängadress, 0x00000 till 0xBFFFF |
</dd>
<dt>Returvärde</dt><dd>
Strängens talvärde.
</dd>
<dt>Se även</dt><dd>
[itoa], [atoi], [str]
</dd>
</dl>
<hr>
## str

```c
str_t str(float value)
```
<dl>
<dt>Beskrivning</dt><dd>
Konverterar ett flyttal till en ASCII-decimalsträng.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| value | värdet |
</dd>
<dt>Returvärde</dt><dd>
Den konverterade strängen.
</dd>
<dt>Se även</dt><dd>
[atoi], [itoa], [val]
</dd>
</dl>
<hr>
## sprintf

```c
str_t sprintf(str_t fmt, ...)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnerar en noll avslutad UTF-8-sträng skapad med format och argument.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| fmt | [formatera sträng] |
| ... | valfria argument |
</dd>
<dt>Returvärde</dt><dd>
Konstruerad sträng.
</dd>
</dl>
<hr>
## strlen

```c
int strlen(str_t src)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnera antalet byte i en sträng (utan den avslutande nollan).
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| src | strängadress, 0x00000 till 0xBFFFF |
</dd>
<dt>Returvärde</dt><dd>
Antalet byte i strängen.
</dd>
<dt>Se även</dt><dd>
[mblen]
</dd>
</dl>
<hr>
## mblen

```c
int mblen(str_t src)
```
<dl>
<dt>Beskrivning</dt><dd>
Returnera antalet UTF-8 multi-byte-tecken i en sträng (utan den avslutande nollan).
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| src | strängadress, 0x00000 till 0xBFFFF |
</dd>
<dt>Returvärde</dt><dd>
Antalet tecken i strängen.
</dd>
<dt>Se även</dt><dd>
[strlen]
</dd>
</dl>
<hr>
## malloc

```c
addr_t malloc(uint32_t size)
```
<dl>
<dt>Beskrivning</dt><dd>
Tilldelar användarminne dynamiskt.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| size | antal byte att tilldela |
</dd>
<dt>Returvärde</dt><dd>
Adress till den nya tilldelade bufferten eller NULL vid fel.
</dd>
<dt>Se även</dt><dd>
[realloc], [free]
</dd>
</dl>
<hr>
## realloc

```c
addr_t realloc(addr_t addr, uint32_t size)
```
<dl>
<dt>Beskrivning</dt><dd>
Ändra storlek på en tidigare tilldelad buffert.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| addr | adress för den tilldelade bufferten |
| size | antal byte att ändra storlek till |
</dd>
<dt>Returvärde</dt><dd>
Adress till den nya tilldelade bufferten eller NULL vid fel.
</dd>
<dt>Se även</dt><dd>
[malloc], [free]
</dd>
</dl>
<hr>
## free

```c
int free(addr_t addr)
```
<dl>
<dt>Beskrivning</dt><dd>
Frigör dynamiskt allokerat användarminne.
</dd>
<dt>Parametrar</dt><dd>
| Argument | Beskrivning |
| addr | adress för den tilldelade bufferten |
</dd>
<dt>Returvärde</dt><dd>
1 på framgång, 0 på fel.
</dd>
<dt>Se även</dt><dd>
[malloc], [realloc]
</dd>
</dl>
