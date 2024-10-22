# Speicherkarte

## Diverses

Alle Werte sind Little-Endian-Werte, sodass die kleinere Ziffer an der kleineren Adresse gespeichert wird.

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|  00000 |          1 | MEG-4 Firmware-Version Major                                       |
|  00001 |          1 | MEG-4 Firmware-Version Minor                                       |
|  00002 |          1 | MEG-4 Firmware-Version Bugfix                                      |
|  00003 |          1 | Leistungsindikator, nicht verbrauchte Zeit in 1/1000 Sekunden      |
|  00004 |          4 | Anzahl der 1/1000-Sekunden-Ticks seit dem Einschalten              |
|  00008 |          8 | UTC-Unix-Zeitstempel                                               |
|  00010 |          2 | Aktuelles Gebietsschema                                            |

Der Leistungsindikator zeigt die nicht verbrauchte Zeit an, als der letzte Frame generiert wurde. Wenn dieser Null oder
negativ ist, bedeutet dies, um wie viel Ihre Funktion loop() ihren verfügbaren Zeitrahmen überschritten hat.

## Mauszeiger

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|  00012 |          2 | Zustand der Zeigertasten (siehe [getbtn] und [getclk])             |
|  00014 |          2 | Zeiger-Sprite-Index                                                |
|  00016 |          2 | Zeiger-X-Koordinate                                                |
|  00018 |          2 | Zeiger-Y-Koordinate                                                |

Die Zeigertasten sind wie folgt:

| Define  | Bitmask   | Beschreibung                                                       |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | Linke Maustaste                                                    |
| `BTN_M` |         2 | Mittlere Maustaste                                                 |
| `BTN_R` |         4 | Rechte Maustaste                                                   |
| `SCR_U` |         8 | Hochscrollen                                                       |
| `SCR_D` |        16 | Runterscrollen                                                     |
| `SCR_L` |        32 | Nach links scrollen                                                |
| `SCR_R` |        64 | Nack rechts scrollen                                               |

Die oberen Bits des Zeiger-Sprite-Index werden für Hotspots verwendet: Bit 13-15 Hotspot Y, Bit 10-12 Hotspot X, Bit 0-9 Sprite.
Es gibt einige vordefinierte integrierte Cursor:

| Define       | Wert      | Beschreibung                                                  |
|--------------|----------:|---------------------------------------------------------------|
| `PTR_NORM`   |      03fb | Normaler (Pfeil-)Zeiger                                       |
| `PTR_TEXT`   |      03fc | Textzeiger                                                    |
| `PTR_HAND`   |      0bfd | Linkzeiger                                                    |
| `PTR_ERR`    |      93fe | Fehlerzeiger                                                  |
| `PTR_NONE`   |      ffff | Der Zeiger ist ausgeblendet                                   |

## Tastatur

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|  0001A |          1 | Ende der Tastaturwarteschlange                                     |
|  0001B |          1 | Kopf der Tastaturwarteschlange                                     |
|  0001C |         64 | Tastaturwarteschlange, 16 Elemente, jeweils 4 Bytes (siehe [popkey]) |
|  0005C |         18 | Status der gedrückten Tastaturtasten nach Scancodes (siehe [getkey]) |

Die aus der Warteschlange entnommenen Schlüssel werden in UTF-8 dargestellt. Einige ungültige UTF-8-Sequenzen stellen spezielle
(nicht druckbare) Schlüssel dar, zum Beispiel:

| Keycode | Beschreibung                                    |
|---------|-------------------------------------------------|
| `\x8`   | Das Zeichen 8, die <kbd>←Backspace</kbd>-Taste  |
| `\x9`   | Das Zeichen 9, die <kbd>Tab</kbd>-Taste         |
| `\n`    | Das Zeichen 10, die <kbd>⏎Enter</kbd>-Taste     |
| `\x1b`  | Das Zeichen 27, <kbd>Esc</kbd>-Taste            |
| `Del`   | Die <kbd>Del</kbd>-Taste                        |
| `Up`    | Die Cursor-Pfeiltaste <kbd>▴</kbd>-Taste        |
| `Down`  | Die Cursor-Pfeiltaste <kbd>▾</kbd>-Taste        |
| `Left`  | Die Cursor-Pfeiltaste <kbd>◂</kbd>-Taste        |
| `Rght`  | Die Cursor-Pfeiltaste <kbd>▸</kbd>-Taste        |
| `Cut`   | Die Cut-Taste (oder <kbd>Strg</kbd>+<kbd>X</kbd>) |
| `Cpy`   | Die Copy-Taste (oder <kbd>Strg</kbd>+<kbd>C</kbd>) |
| `Pst`   | Die Paste-Taste (oder <kbd>Strg</kbd>+<kbd>V</kbd>) |

Die Scancodes lauten wie folgt:

| ScanCode | Address | Bitmask | Define            |
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

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|  0006E |          2 | Gamepad-Joystick-Grenzwert (Standard: 8000)                        |
|  00070 |          8 | Primäres Gamepad – Tastatur-Scancode-Zuordnungen (siehe [Tastatur]) |
|  00078 |          4 | 4-Gamepad-Taste gedrückter Zustand (siehe [getpad])                |

Die Gamepad-Tasten sind wie folgt:

| Define  | Bitmask   | Beschreibung                                                       |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | Die `◁`-Taste oder der Joystick nach links                         |
| `BTN_U` |         2 | Die `△`-Taste oder der Joystick nach oben                          |
| `BTN_R` |         4 | Die `▷`-Taste oder der Joystick nach rechts                        |
| `BTN_D` |         8 | Die `▽`-Taste oder der Joystick nach unten                         |
| `BTN_A` |        16 | Die `Ⓐ`-Taste                                                     |
| `BTN_B` |        32 | Die `Ⓑ`-Taste                                                     |
| `BTN_X` |        64 | Die `Ⓧ`-Taste                                                     |
| `BTN_Y` |       128 | Die `Ⓨ`-Taste                                                     |

Die Sequenz `△△▽▽◁▷◁▷ⒷⒶ` bewirkt, dass die „Taste“ `KEY_CHEAT` gedrückt wird.

## Grafikverarbeitungseinheit

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|  0007E |          1 | Obere Bits des UNICODE-Codepunkts für die Zuordnung von Schriftartglyphen |
|  0007F |          1 | Sprite-Bank-Auswahl für die Karte                                  |
|  00080 |       1024 | Palette, 256 Farben, jeder Eintrag 4 Bytes, RGBA                   |
|  00480 |          2 | x0, Zuschneidebereich X Start in Pixel (für alle Zeichenfunktionen) |
|  00482 |          2 | x1, Zuschneidebereich X Ende in Pixel                              |
|  00484 |          2 | y0, Zuschneidebereich Y Start in Pixel                             |
|  00486 |          2 | y1, Zuschneidebereich Y Ende in Pixel                              |
|  00488 |          2 | Angezeigter VRAM-X-Offset in Pixel oder 0xffff                     |
|  0048A |          2 | Angezeigter VRAM-Y-Offset in Pixel oder 0xffff                     |
|  0048C |          1 | Schildkröten-Pen-Down-Flagge (siehe [up], [down])                  |
|  0048D |          1 | Schildkrötenstiftfarbe, Palettenindex 0 bis 255 (siehe [color])    |
|  0048E |          2 | Schildkrötenrichtung in Grad, 0 bis 359 (siehe [left], [right])    |
|  00490 |          2 | Schildkröten-X-Versatz in Pixel (siehe [move])                     |
|  00492 |          2 | Schildkröten-Y-Versatz in Pixel                                    |
|  00494 |          2 | Labyrinth-Gehgeschwindigkeit in 1/128 Kacheln (siehe [maze])       |
|  00496 |          2 | Rotationsgeschwindigkeit des Labyrinths in Grad (1 bis 90)         |
|  00498 |          1 | Vordergrundfarbe der Konsole, Palettenindex 0 bis 255 (siehe [printf]) |
|  00499 |          1 | Hintergrundfarbe der Konsole, Palettenindex 0 bis 255              |
|  0049A |          2 | Konsolen-X-Offset in Pixel                                         |
|  0049C |          2 | Konsolen-Y-Offset in Pixel                                         |
|  0049E |          2 | Kamera-X-Versatz im [3D-Welt] (siehe [tri3d], [tritx], [mesh])     |
|  004A0 |          2 | Kamera-Y-Versatz                                                   |
|  004A2 |          2 | Kamera-Z-Versatz                                                   |
|  004A4 |          2 | Kamerarichtung, Neigung (0 nach oben, 90 nach vorne)               |
|  004A6 |          2 | Kamerarichtung, Gieren (0 nach links, 90 nach vorne)               |
|  004A8 |          1 | Kamerasichtfeld in Winkeln (45, negativ ergibt orthografisch)      |
|  004AA |          2 | Lichtquellenposition X-Versatz (siehe [tri3d], [tritx], [mesh])    |
|  004AC |          2 | Lichtquellenposition Y-Versatz                                     |
|  004AE |          2 | Lichtquellenposition Z-Versatz                                     |
|  00600 |      64000 | Karte, 320 x 200 Sprite-Indizes (siehe [map] und [maze])           |
|  10000 |      65536 | Sprites, 256 x 256 Palettenindizes, 1024 8 x 8 Pixel (siehe [spr]) |
|  28000 |       2048 | Fenster für 4096 Schriftartglyphen (siehe 0007E, [width] und [text]) |

## Digitaler Signalprozessor

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|  0007C |          1 | Auswahl der Wellenformbank (1 bis 31)                              |
|  0007D |          1 | Auswahl der Musiktitelbank (0 bis 7)                               |
|  004BA |          1 | Aktuelles Tempo (in Ticks pro Zeile, schreibgeschützt)             |
|  004BB |          1 | Aktuell abgespielter Titel (schreibgeschützt)                      |
|  004BC |          2 | Aktuelle Zeile wird abgespielt (schreibgeschützt)                  |
|  004BE |          2 | Anzahl der Gesamtzeilen im aktuellen Titel (schreibgeschützt)      |
|  004C0 |         64 | 16 Kanalstatusregister, jeweils 4 Bytes (schreibgeschützt)         |
|  00500 |        256 | 64 Soundeffekte, jeweils 4 Bytes                                   |
|  20000 |      16384 | Fenster für Wellenform-Samples (siehe 0007C)                       |
|  24000 |      16384 | Fenster für Musikmuster (siehe 0007D)                              |

Die DSP-Statusregister sind alle schreibgeschützt und sehen für jeden Kanal folgendermaßen aus:

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | Aktuelle Position in der wiedergegebenen Wellenform                |
|      2 |          1 | Aktuelle Wellenform (1 bis 31, 0, wenn der Kanal still ist)        |
|      3 |          1 | Aktuelle Lautstärke (0 bedeutet, dass der Kanal ausgeschaltet ist) |

Die ersten 4 Kanäle sind für die Musik, der Rest für die Soundeffekte.

Beachten Sie, dass der Wellenformindex 0 „die vorherige Wellenform verwenden“ bedeutet, sodass Index 0 nicht im Selektor
verwendet werden kann. Das Format jeder anderen Wellenform:

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | Anzahl von Samples                                                 |
|      2 |          2 | Schleifenstart                                                     |
|      4 |          2 | Schleifenlänge                                                     |
|      6 |          1 | Feinstimmung, -8 bis 7                                             |
|      7 |          1 | Lautstärke, 0 bis 64                                               |
|      8 |      16376 | signierte 8-Bit-Mono-Samples                                       |

Das Format der Soundeffekte und der Musiktitel ist das gleiche, der einzige Unterschied besteht darin, dass Musiktitel 4 Noten
pro Zeile haben, eine für jeden Kanal, und es 1024 Zeilen gibt; Für Soundeffekte hingegen gibt es nur eine Note und 64 Zeilen.

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          1 | Notennummer, siehe `NOTE_x`-Definitionen, 0 bis 96                 |
|      1 |          1 | Wellenformindex, 0 bis 31                                          |
|      2 |          1 | Effekttyp, 0 bis 255 (siehe [Klangeffekte])                        |
|      3 |          1 | Effektparameter                                                    |

Die Notenzählung erfolgt wie folgt: 0 bedeutet, dass keine Note gesetzt ist. Es folgen 8 Oktaven mit jeweils 12 Noten, also
entspricht 1 C-0, 12 H-0 (auf der tiefsten Oktave), 13 C-1 (eine Oktave höher) und 14 C#1 (Cis, Halbton höher). Beispielsweise
wäre die D-Note in der 4. Oktave 1 + 4\*12 + 2 = 51. Die H-7 ist 96, die höchste Note in der höchsten Oktave. Sie haben auch
integrierte Definitionen, zum Beispiel ist C-1 `NOTE_C_1` und C#1 ist `NOTE_Cs1`. Wenn Sie nicht zählen möchten, können Sie
diese auch in Ihrem Programm verwenden.

## Klangeffekte

Der Einfachheit halber verwendet MEG-4 dieselben Codes wie die Amiga MOD-Datei (auf diese Weise sehen Sie dasselbe sowohl im
integrierten Editor als auch in einem Musik-Tracker eines Drittanbieters), es werden jedoch nicht alle davon unterstützt. Wie
bereits erwähnt, werden diese Codes durch drei Hexadezimalzahlen dargestellt, wobei die erste der Typ `t` und die letzten beiden
der Parameter `xy` (oder `xx`) ist. Die Typen `E1` bis `ED` werden alle im Typbyte gespeichert, obwohl es so aussieht, als ob
eines ihrer Halbbytes zum Parameter gehören könnte, aber das ist nicht der Fall.

| Effekt | Code | Beschreibung                                               |
|--------|------|------------------------------------------------------------|
| ...    | 000  | Kein Effekt                                                |
| Arp    | 0xy  | Arpeggio, Note, Note+x-Halbton und Note+y-Halbton spielen  |
| Po/    | 1xx  | Portamento nach oben, Periode um x nach oben verschieben   |
| Po\\   | 2xx  | Portamento nach unten, Periode um x nach unten verschieben |
| Ptn    | 3xx  | Ton-Portamento, von Periode zu Periode x gleiten           |
| Vib    | 4xy  | Vibrato, oszillieren die Tonhöhe um y Halbtöne bei x Frequenz |
| Ctv    | 5xy  | Weiter Ton-Portamento + Lautstärke mit x nach oben oder y nach unten schieben |
| Cvv    | 6xy  | Weiter Vibrato + Lautstärke um x nach oben oder um y nach unten schieben |
| Trm    | 7xy  | Tremolo, oszillieren Sie die Lautstärke um y Amplitude bei x Frequenz |
| Ofs    | 9xx  | Stellen Sie den Sample-Offset auf x \* 256 ein             |
| Vls    | Axy  | Schieben Sie die Lautstärke um x nach oben oder um y nach unten |
| Jmp    | Bxx  | Positionssprung, Zeile auf x \* 64 setzen                  |
| Vol    | Cxx  | Lautstärke auf x einstellen                                |
| Fp/    | E1x  | Feines Portamento nach oben, Periode um x erhöhen          |
| Fp\\   | E2x  | Feines Portamento nach unten, Periode um x verringern      |
| Svw    | E4x  | Vibrato-Wellenform einstellen: 0 Sinus, 1 Sägezahn, 2 Rechteck, 3 Rauschen |
| Ftn    | E5x  | Feinstimmung einstellen, Stimmung um x ändern (-8 bis 7)   |
| Stw    | E7x  | Tremolo-Wellenform einstellen: 0 Sinus, 1 Sägezahn, 2 Rechteck, 3 Rauschen |
| Rtg    | E9x  | Note erneut auslösen, aktuelles Sample alle x Ticks auslösen |
| Fv/    | EAx  | Feinlautstärke nach oben schieben, um x erhöhen            |
| Fv\\   | EBx  | Feinkautstärke nach unten schieben, um x verringern        |
| Cut    | ECx  | Note in x Ticks schneiden                                  |
| Dly    | EDx  | Verzögerungsnotiz für x Ticks                              |
| Tpr    | Fxx  | Anzahl der Ticks pro Zeile auf x setzen (Tick-Standard ist 6) |

## Benutzergedächtnis

Speicheradressen von 00000 bis 2FFFF gehören zum MMIO, alles darüber (ab 30000 oder `MEM_USER`) ist frei nutzbarer
Benutzerspeicher.

| Offset | Größe      | Beschreibung                                                       |
|--------|-----------:|--------------------------------------------------------------------|
|  30000 |          4 | (nur BASIC) offset von DATA                                        |
|  30004 |          4 | (nur BASIC) aktueller READ-Zähler                                  |
|  30008 |          4 | (nur BASIC) maximale READ-Zähler, Anzahl der DATA                  |

Darauf folgen die globalen Variablen, die Sie in Ihrem Programm deklariert haben, gefolgt von den Konstanten, wie z. B.
String-Literalen. Im Falle von BASIC folgen dann die eigentlichen DATA-Records.

Speicheradressen über den initialisierten Daten können in Ihrem Programm über die Aufrufe [malloc] und [free] dynamisch zugewiesen
und freigegeben werden.

Zuletzt der Stapel, der ganz oben liegt (beginnend bei C0000 oder `MEM_LIMIT`) und *nach unten* wächst. Hier finden Sie die
lokalen Variablen Ihres Programms (die Sie innerhalb einer Funktion deklariert haben). Die Größe des Stapels ändert sich immer
abhängig davon, welche Funktion welche andere Funktion in Ihrem Programm aufruft.

Wenn sich zufällig der obere Teil der dynamisch zugewiesenen Daten und der untere Teil des Stapels überlappen würden, gibt MEG-4
den Fehler „Nicht genügend Speicher“ aus.

## Formatierungszeichenfolge

Einige Funktionen, [printf], [sprintf] und [trace], verwenden eine Formatzeichenfolge, die Sonderzeichen enthalten kann, um auf
Argumente zu verweisen und zu beschreiben, wie sie angezeigt werden. Diese sind:

| Code | Beschreibung                                               |
|------|------------------------------------------------------------|
| `%%` | Das Zeichen `%`                                            |
| `%d` | Nächster Parameter als Dezimalzahl                         |
| `%u` | Nächster Parameter als vorzeichenlose Dezimalzahl          |
| `%x` | Nächster Parameter als Hexadezimalzahl                     |
| `%o` | Nächster Parameter als Oktalzahl                           |
| `%b` | Nächster Parameter als Binärzahl                           |
| `%f` | Nächster Parameter als Gleitkommazahl                      |
| `%s` | Nächster Parameter als Zeichenfolge                        |
| `%c` | Nächster Parameter als UTF-8-Zeichen                       |
| `%p` | Nächster Parameter als Adresse (Zeiger)                    |
| `\t` | Tab, fixieren Sie die vertikale Position, bevor Sie fortfahren |
| `\n` | Beginnen Sie eine neue Zeile                               |

Sie können Auffüllungen hinzufügen, indem Sie die Länge zwischen `%` und dem Code angeben. Wenn dieser mit `0` beginnt, wird der
Wert mit Nullen aufgefüllt, andernfalls mit Leerzeichen. Beispielsweise füllt `%4d` den Wert rechts mit Leerzeichen und `%04x` mit
Nullen auf. Das `f` akzeptiert eine Zahl nach einem Punkt, die die Anzahl der Ziffern im Bruchteil angibt (bis zu 8), z. B. `%.6f`.

## 3D-Welt

In MEG-4 wird der dreidimensionale Raum nach der Rechte-Hand-Regel behandelt: +X ist rechts, +Y ist oben und +Z ist zum Betrachter hin.

```
  +Y
   |
   |__ +X
  /
+Z
```

Jeder Punkt muss im Bereich von -32767 bis +32767 liegen. Wie diese 3D-Welt auf Ihren 2D-Bildschirm projiziert wird, hängt davon
ab, wie Sie die Kamera konfigurieren (siehe [Grafikverarbeitungseinheit] Adresse 0049E). Natürlich müssen Sie die Kamera mit X-, Y-
und Z-Koordinaten in der Welt platzieren. Dann müssen Sie anhand von Nick- und Gierbewegungen erkennen, wohin die Kamera blickt.
Schließlich müssen Sie noch angeben, über welche Art von Objektiv die Kamera verfügt, indem Sie den Blickwinkel angeben. Letzterer
sollte normalerweise zwischen 30 (sehr eng) und 180 Grad (wie bei Fischen und Vögeln) liegen. MEG-4 unterstützt bis zu 127 Grad,
aber es gibt einen Trick. Positive FOV-Werte werden perspektivisch projiziert (je weiter das Objekt entfernt ist, desto kleiner
ist es), negative Werte werden jedoch auch verarbeitet, nur mit orthografischer Projektion (unabhängig von der Entfernung bleibt
die Größe des Objekts gleich). Die Perspektive wird in FPS-Spielen verwendet, während die orthographische Projektion vor allem in
Strategiespielen bevorzugt wird.

Mit der Funktion [mesh] können Sie eine Reihe von Dreiecken (ein vollständiges 3D-Modell) effizient anzeigen. Da Modelle wahrscheinlich
lokale Koordinaten haben, würden dadurch alle Modelle übereinander um den Ursprung herum gezeichnet. Wenn Sie also mehrere Modelle
auf der Welt anzeigen möchten, sollten Sie sie zuerst mit [trns] in Weltkoordinaten übersetzen (platzieren) und dann die übersetzte
Scheitelpunktwolke mit [mesh] verwenden (das Verschieben und Drehen des Modells ist nicht möglich). Ändern Sie die Dreiecke, nur
ihre Scheitelpunktkoordinaten).

## Tastenkombinationen im Code-Editor

Weitere [Tastatur]-Tastenkombinationen, die Sie auch beim Bearbeiten der Quelle verwenden können:

| Taste                        | Beschreibung                                                                         |
|------------------------------|--------------------------------------------------------------------------------------|
| <kbd>Strg</kbd>+<kbd>F</kbd> | Zeichenfolge suchen                                                                  |
| <kbd>Strg</kbd>+<kbd>G</kbd> | Erneut suchen                                                                        |
| <kbd>Strg</kbd>+<kbd>H</kbd> | Suchen und Ersetzen (im ausgewählten Text oder, falls in der gesamten Quelle)        |
| <kbd>Strg</kbd>+<kbd>J</kbd> | Gehe zu Zeile                                                                        |
| <kbd>Strg</kbd>+<kbd>D</kbd> | Gehe zu Funktionsdefinition                                                          |
| <kbd>Strg</kbd>+<kbd>N</kbd> | Lesezeichen auflisten                                                                |
| <kbd>Strg</kbd>+<kbd>B</kbd> | Lesezeichen in aktueller Zeile umschalten                                            |
| <kbd>Strg</kbd>+<kbd>▴</kbd> | Zum vorherigen Lesezeichen gehen                                                     |
| <kbd>Strg</kbd>+<kbd>▾</kbd> | Zum nächsten Lesezeichen gehen                                                       |
| <kbd>Strg</kbd>+<kbd>,</kbd> | Einzug der Auswahl verkleinern                                                       |
| <kbd>Strg</kbd>+<kbd>.</kbd> | Einzug der Auswahl vergrößern                                                        |
| <kbd>Pos1</kbd>              | Cursor an den Zeilenanfang bewegen                                                   |
| <kbd>Ende</kbd>              | Cursor an das Zeilenende bewegen                                                     |
| <kbd>Bild auf</kbd>          | Cursor 42 Zeilen (eine Seite) nach oben bewegen                                      |
| <kbd>Bild ab</kbd>           | Cursor 42 Zeilen (eine Seite) nach unten bewegen                                     |
| <kbd>F1</kbd>                | Wenn sich der Cursor in der Argumentliste einer API befindet, gehe zur Hilfeseite der Funktion |

Siehe auch das Menü für alternative Eingabemethoden und deren Tastaturkürzel.

# Konsole

## putc

```c
void putc(uint32_t chr)
```
<dt>Beschreibung</dt><dd>
Gibt ein Zeichen an die Konsole aus.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| chr | UTF-8-Zeichen |
</dd>
<hr>
## printf

```c
void printf(str_t fmt, ...)
```
<dt>Beschreibung</dt><dd>
Gibt Text an die Konsole aus.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| fmt | anzuzeigende Zeichenfolge, eine [Formatierungszeichenfolge] |
| ... | optionale Argumente |
</dd>
<hr>
## getc

```c
uint32_t getc(void)
```
<dt>Beschreibung</dt><dd>
Liest ein Zeichen von der Konsole und blockiert das Programm, wenn keine Eingabe erfolgt.
</dd>
<dt>Rückgabewert</dt><dd>
Ein vom Benutzer eingegebenes UTF-8-Zeichen.
</dd>
<dt>Siehe auch</dt><dd>
[popkey]
</dd>
<hr>
## gets

```c
str_t gets(void)
```
<dt>Beschreibung</dt><dd>
Liest eine mit einer neuen Zeile abgeschlossene Zeichenfolge vom Benutzer ein (gibt die neue Zeile nicht zurück).
</dd>
<dt>Rückgabewert</dt><dd>
Die in einem String gelesenen Bytes.
</dd>
<hr>
## trace

```c
void trace(str_t fmt, ...)
```
<dt>Beschreibung</dt><dd>
Verfolgen Sie die Ausführung durch Drucken auf stdout. Funktioniert wenn `meg4` mit dem Verbose-Flag `-v` gestartet wurde.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| fmt | [Formatierungszeichenfolge] |
| ... | optionale Argumente |
</dd>
<hr>
## delay

```c
void delay(uint16_t msec)
```
<dt>Beschreibung</dt><dd>
Verzögert die Programmausführung.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| msec | Verzögerung in Millisekunden |
</dd>
<hr>
## exit

```c
void exit(void)
```
<dt>Beschreibung</dt><dd>
Beendet das Programm.
</dd>

# Audio

## sfx

```c
void sfx(uint8_t sfx, uint8_t channel, uint8_t volume)
```
<dt>Beschreibung</dt><dd>
Spielt einen Soundeffekt ab.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| sfx | der Index des Soundeffekts, 0 bis 63 |
| channel | Kanal, der verwendet werden soll, 0 bis 11 |
| volume | verwendende Lautstärke, 0 bis 255, 0 schaltet den Kanal aus |
</dd>
<hr>
## music

```c
void music(uint8_t track, uint16_t row, uint8_t volume)
```
<dt>Beschreibung</dt><dd>
Spielt einen Musiktitel ab.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| track | der Index des Musiktitels, 0 bis 7 |
| row | Zeile, ab der mit der Wiedergabe begonnen wird, 0 bis 1023 (maximale Songlänge) |
| volume | verwendende Lautstärke, 0 bis 255, 0 schaltet die Musik aus |
</dd>

# GPIO

## gpio_rev

```c
uint32_t gpio_rev(void)
```
<dt>Beschreibung</dt><dd>
Fragen Sie die Revisionsnummer des GPIO-Boards ab. Gibt 0 zurück, wenn die Plattform nicht GPIO-fähig ist.
</dd>
<dt>Rückgabewert</dt><dd>
Revisionsnummer des Boards oder 0, falls nicht unterstützt.
</dd>
<hr>
## gpio_get

```c
int gpio_get(uint8_t pin)
```
<dt>Beschreibung</dt><dd>
Lesen Sie den Wert eines GPIO-Pins.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| pin | physische Pin-Nummer, 1 bis 40 |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt 1 zurück, wenn der Pin hoch ist, 0, wenn er niedrig ist, -1 bei Fehler (GPIO-Pin wird nicht unterstützt).
</dd>
<dt>Siehe auch</dt><dd>
[gpio_set]
</dd>
<hr>
## gpio_set

```c
int gpio_set(uint8_t pin, int value)
```
<dt>Beschreibung</dt><dd>
Schreiben Sie den Wert auf einen GPIO-Pin.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| pin | physische Pin-Nummer, 1 bis 40 |
| value | 1, um den Pin auf hoch zu setzen, 0 für niedrig |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt 0 bei Erfolg zurück, -1 bei Fehler (GPIO-Pin wird nicht unterstützt).
</dd>
<dt>Siehe auch</dt><dd>
[gpio_get]
</dd>

# Grafik

## cls

```c
void cls(uint8_t palidx)
```
<dt>Beschreibung</dt><dd>
Löscht den gesamten Bildschirm, setzt Anzeigeversätze zurück und legt außerdem die Hintergrundfarbe der Konsole fest.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
</dd>
<dt>Siehe auch</dt><dd>
[pget], [pset]
</dd>
<hr>
## cget

```c
uint32_t cget(uint16_t x, uint16_t y)
```
<dt>Beschreibung</dt><dd>
Pixel an einer Koordinate abrufen und geben Sie die Farbe RGBA zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| x | X-Koordinate in Pixel |
| y | Y-Koordinate in Pixel |
</dd>
<dt>Rückgabewert</dt><dd>
Eine gepackte Farbe mit RGBA-Kanälen (Rot befindet sich im niederwertigsten Byte).
</dd>
<dt>Siehe auch</dt><dd>
[cls], [pget], [pset]
</dd>
<hr>
## pget

```c
uint8_t pget(uint16_t x, uint16_t y)
```
<dt>Beschreibung</dt><dd>
Pixel an einer Koordinate abrufen und deren Palettenindex zurückgeben.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| x | X-Koordinate in Pixel |
| y | Y-Koordinate in Pixel |
</dd>
<dt>Rückgabewert</dt><dd>
Farbe im Palettenindex, 0 bis 255.
</dd>
<dt>Siehe auch</dt><dd>
[cls], [pset], [cget]
</dd>
<hr>
## pset

```c
void pset(uint8_t palidx, uint16_t x, uint16_t y)
```
<dt>Beschreibung</dt><dd>
Plottet ein Pixel an einer Koordinate.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x | X-Koordinate in Pixel |
| y | Y-Koordinate in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[cls], [pget]
</dd>
<hr>
## width

```c
uint16_t width(int8_t type, str_t str)
```
<dt>Beschreibung</dt><dd>
Gibt die Breite des angezeigten Texts in Pixel zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| type | Schrifttyp, -4 bis 4 |
| str | Zeichenfolge zum Messen |
</dd>
<dt>Rückgabewert</dt><dd>
Anzahl der Pixel, die zum Anzeigen von Text erforderlich sind.
</dd>
<dt>Siehe auch</dt><dd>
[text]
</dd>
<hr>
## text

```c
void text(uint8_t palidx, int16_t x, int16_t y, int8_t type, uint8_t shidx, uint8_t sha, str_t str)
```
<dt>Beschreibung</dt><dd>
Druckt Text auf dem Bildschirm.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x | X-Koordinate in Pixel |
| y | Y-Koordinate in Pixel |
| type | Schrifttyp, -4 bis -1 Monospace, 1 bis 4 Proportional |
| shidx | Schattenfarbe, Palettenindex 0 bis 255 |
| sha | Alpha des Schattens, 0 (vollständig transparent) bis 255 (vollständig undurchsichtig) |
| str | Zeichenfolge, die angezeigt werden soll |
</dd>
<dt>Siehe auch</dt><dd>
[width]
</dd>
<hr>
## line

```c
void line(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Beschreibung</dt><dd>
Zeichnet eine geglättete Linie.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | Start-X-Koordinate in Pixel |
| y0 | Start-Y-Koordinate in Pixel |
| x1 | Ende-X-Koordinate in Pixel |
| y1 | Ende-Y-Koordinate in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[qbez], [cbez]
</dd>
<hr>
## qbez

```c
void qbez(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t cx, int16_t cy)
```
<dt>Beschreibung</dt><dd>
Zeichnet eine quadratische Bezier-Kurve.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | Start-X-Koordinate in Pixel |
| y0 | Start-Y-Koordinate in Pixel |
| x1 | Ende-X-Koordinate in Pixel |
| y1 | Ende-Y-Koordinate in Pixel |
| cx | X-Koordinate des Kontrollpunkts in Pixel |
| cy | Y-Koordinate des Kontrollpunkts in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[line], [cbez]
</dd>
<hr>
## cbez

```c
void cbez(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t cx0, int16_t cy0, int16_t cx1, int16_t cy1)
```
<dt>Beschreibung</dt><dd>
Zeichnet eine kubische Bezier-Kurve.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | Start-X-Koordinate in Pixel |
| y0 | Start-Y-Koordinate in Pixel |
| x1 | Ende-X-Koordinate in Pixel |
| y1 | Ende-Y-Koordinate in Pixel |
| cx0 | X-Koordinate des ersten Kontrollpunkts in Pixel |
| cy0 | Y-Koordinate des ersten Kontrollpunkts in Pixel |
| cx1 | X-Koordinate des zweiten Kontrollpunkts in Pixel |
| cy1 | Y-Koordinate des zweiten Kontrollpunkts in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[line], [qbez]
</dd>
<hr>
## tri

```c
void tri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dt>Beschreibung</dt><dd>
Zeichnet ein Dreieck.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | X-Koordinate der ersten Kante in Pixel |
| y0 | Y-Koordinate der ersten Kante in Pixel |
| x1 | X-Koordinate der zweiten Kante in Pixel |
| y1 | Y-Koordinate der zweiten Kante in Pixel |
| x2 | X-Koordinate der dritten Kante in Pixel |
| y2 | Y-Koordinate der dritten Kante in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[ftri], [tri2d], [tri3d], [tritx], [mesh], [trns]
</dd>
<hr>
## ftri

```c
void ftri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dt>Beschreibung</dt><dd>
Zeichnet ein gefülltes Dreieck.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | X-Koordinate der ersten Kante in Pixel |
| y0 | Y-Koordinate der ersten Kante in Pixel |
| x1 | X-Koordinate der zweiten Kante in Pixel |
| y1 | Y-Koordinate der zweiten Kante in Pixel |
| x2 | X-Koordinate der dritten Kante in Pixel |
| y2 | Y-Koordinate der dritten Kante in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[tri], [tri2d], [tri3d], [tritx], [mesh], [trns]
</dd>
<hr>
## tri2d

```c
void tri2d(uint8_t pi0, int16_t x0, int16_t y0,
    uint8_t pi1, int16_t x1, int16_t y1,
    uint8_t pi2, int16_t x2, int16_t y2)
```
<dt>Beschreibung</dt><dd>
Zeichnet ein gefülltes Dreieck mit Farbverläufen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| pi0 | Farbe der ersten Kante, Palettenindex 0 bis 255 |
| x0 | X-Koordinate der ersten Kante in Pixel |
| y0 | Y-Koordinate der ersten Kante in Pixel |
| pi1 | Farbe der zweiten Kante, Palettenindex 0 bis 255 |
| x1 | X-Koordinate der zweiten Kante in Pixel |
| y1 | Y-Koordinate der zweiten Kante in Pixel |
| pi2 | Farbe der dritten Kante, Palettenindex 0 bis 255 |
| x2 | X-Koordinate der dritten Kante in Pixel |
| y2 | Y-Koordinate der dritten Kante in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[tri], [ftri], [tri3d], [tritx], [mesh], [trns]
</dd>
<hr>
## tri3d

```c
void tri3d(uint8_t pi0, int16_t x0, int16_t y0, int16_t z0,
    uint8_t pi1, int16_t x1, int16_t y1, int16_t z1,
    uint8_t pi2, int16_t x2, int16_t y2, int16_t z2)
```
<dt>Beschreibung</dt><dd>
Zeichnet ein gefülltes Dreieck mit Farbverläufen in [3D-Welt].
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| pi0 | Farbe der ersten Kante, Palettenindex 0 bis 255 |
| x0 | X-Koordinate der ersten Kante im Welt |
| y0 | Y-Koordinate der ersten Kante im Welt |
| z0 | Z-Koordinate der ersten Kante im Welt |
| pi1 | Farbe der zweiten Kante, Palettenindex 0 bis 255 |
| x1 | X-Koordinate der zweiten Kante im Welt |
| y1 | Y-Koordinate der zweiten Kante im Welt |
| z1 | Z-Koordinate der zweiten Kante im Welt |
| pi2 | Farbe der dritten Kante, Palettenindex 0 bis 255 |
| x2 | X-Koordinate der dritten Kante im Welt |
| y2 | Y-Koordinate der dritten Kante im Welt |
| z2 | Z-Koordinate der dritten Kante im Welt |
</dd>
<dt>Siehe auch</dt><dd>
[tri], [ftri], [tri2d], [tritx], [mesh], [trns]
</dd>
<hr>
## tritx

```c
void tritx(uint8_t u0, uint8_t v0, int16_t x0, int16_t y0, int16_t z0,
    uint8_t u1, uint8_t v1, int16_t x1, int16_t y1, int16_t z1,
    uint8_t u2, uint8_t v2, int16_t x2, int16_t y2, int16_t z2)
```
<dt>Beschreibung</dt><dd>
Zeichnet ein Dreieck mit Textur in [3D-Welt].
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| u0 | X-Koordinate der ersten Kantentextur 0 bis 255 |
| v0 | Y-Koordinate der ersten Kantentextur 0 bis 255 |
| x0 | X-Koordinate der ersten Kante im Welt |
| y0 | Y-Koordinate der ersten Kante im Welt |
| z0 | Z-Koordinate der ersten Kante im Welt |
| u1 | X-Koordinate der zweiten Kantentextur 0 bis 255 |
| v1 | Y-Koordinate der zweiten Kantentextur 0 bis 255 |
| x1 | X-Koordinate der zweiten Kante im Welt |
| y1 | Y-Koordinate der zweiten Kante im Welt |
| z1 | Z-Koordinate der zweiten Kante im Welt |
| u2 | X-Koordinate der dritten Kantentextur 0 bis 255 |
| v2 | Y-Koordinate der dritten Kantentextur 0 bis 255 |
| x2 | X-Koordinate der dritten Kante im Welt |
| y2 | Y-Koordinate der dritten Kante im Welt |
| z2 | Z-Koordinate der dritten Kante im Welt |
</dd>
<dt>Siehe auch</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [mesh], [trns]
</dd>
<hr>
## mesh

```c
void mesh(addr_t verts, addr_t uvs, uint16_t numtri, addr_t tris)
```
<dt>Beschreibung</dt><dd>
Zeichnet ein Netz aus Dreiecken in [3D-Welt] und verwendet dabei Indizes für Scheitelpunkte und Texturkoordinaten (oder Palette).
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| verts | Adresse des Vertices-Arrays, jeweils 3 x 2 Bytes, X, Y, Z |
| uvs | Adresse des UVs-Arrays (wenn 0, dann wird Palette verwendet), jeweils 2 x 1 Byte, Textur X, Y |
| numtri | Anzahl der Dreiecke |
| tris | Adresse des Dreiecks-Arrays mit Indizes, jeweils 6 x 1 Byte, vi1, ui1/pi1, vi2, ui2/pi2, vi3, ui3/pi3 |
</dd>
<dt>Siehe auch</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [tritx], [trns]
</dd>
<hr>
## rect

```c
void rect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Beschreibung</dt><dd>
Zeichnet ein Rechteck.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | X-Koordinate der oberen linken Ecke in Pixel |
| y0 | Y-Koordinate der oberen linken Ecke in Pixel |
| x1 | X-Koordinate der unten rechts Ecke in Pixel |
| y1 | Y-Koordinate der unten rechts Ecke in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[frect]
</dd>
<hr>
## frect

```c
void frect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Beschreibung</dt><dd>
Zeichnet ein gefülltes Rechteck.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | X-Koordinate der oberen linken Ecke in Pixel |
| y0 | Y-Koordinate der oberen linken Ecke in Pixel |
| x1 | X-Koordinate der unten rechts Ecke in Pixel |
| y1 | Y-Koordinate der unten rechts Ecke in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[rect]
</dd>
<hr>
## circ

```c
void circ(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dt>Beschreibung</dt><dd>
Zeichnet einen Kreis.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x | Mittelpunkt-X-Koordinate in Pixel |
| y | Mittelpunkt-Y-Koordinate in Pixel |
| r | Radius in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[fcirc], [ellip], [fellip]
</dd>
<hr>
## fcirc

```c
void fcirc(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dt>Beschreibung</dt><dd>
Zeichnet einen gefüllten Kreis.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x | Mittelpunkt-X-Koordinate in Pixel |
| y | Mittelpunkt-Y-Koordinate in Pixel |
| r | Radius in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[circ], [ellip], [fellip]
</dd>
<hr>
## ellip

```c
void ellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Beschreibung</dt><dd>
Zeichnet eine Ellipse.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | X-Koordinate der oberen linken Ecke in Pixel |
| y0 | Y-Koordinate der oberen linken Ecke in Pixel |
| x1 | X-Koordinate der unten rechts Ecke in Pixel |
| y1 | Y-Koordinate der unten rechts Ecke in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[circ], [fcirc], [fellip]
</dd>
<hr>
## fellip

```c
void fellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Beschreibung</dt><dd>
Zeichnet eine gefüllte Ellipse.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
| x0 | X-Koordinate der oberen linken Ecke in Pixel |
| y0 | Y-Koordinate der oberen linken Ecke in Pixel |
| x1 | X-Koordinate der unten rechts Ecke in Pixel |
| y1 | Y-Koordinate der unten rechts Ecke in Pixel |
</dd>
<dt>Siehe auch</dt><dd>
[circ], [fcirc], [ellip]
</dd>
<hr>
## move

```c
void move(int16_t x, int16_t y, uint16_t deg)
```
<dt>Beschreibung</dt><dd>
Bewegt die Schildkröte an die angegebene Position auf dem Bildschirm oder im Labyrinth.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| x | X-Koordinate in Pixel (oder 1/128 Kacheln mit [maze]) |
| y | Y-Koordinate in Pixel |
| deg | Richtung in Grad, 0 bis 359, 0 bedeutet auf dem Bildschirm nach oben, 90 bedeutet nach rechts |
</dd>
<dt>Siehe auch</dt><dd>
[left], [right], [up], [down], [color], [forw], [back]
</dd>
<hr>
## left

```c
void left(uint16_t deg)
```
<dt>Beschreibung</dt><dd>
Dreht die Schildkröte nach links.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| deg | Änderung in Grad, 0 bis 359 |
</dd>
<dt>Siehe auch</dt><dd>
[move], [right], [up], [down], [color], [forw], [back]
</dd>
<hr>
## right

```c
void right(uint16_t deg)
```
<dt>Beschreibung</dt><dd>
Dreht die Schildkröte nach rechts.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| deg | Änderung in Grad, 0 bis 359 |
</dd>
<dt>Siehe auch</dt><dd>
[move], [left], [up], [down], [color], [forw], [back]
</dd>
<hr>
## up

```c
void up(void)
```
<dt>Beschreibung</dt><dd>
Hebt den Schwanz der Schildkröte an. Die Schildkröte bewegt sich, ohne eine Linie zu zeichnen.
</dd>
<dt>Siehe auch</dt><dd>
[move], [left], [right], [down], [color], [forw], [back]
</dd>
<hr>
## down

```c
void down(void)
```
<dt>Beschreibung</dt><dd>
Legt den Schwanz der Schildkröte nach unten. Die Schildkröte bewegt sich und zeichnet eine Linie (siehe [color]).
</dd>
<dt>Siehe auch</dt><dd>
[move], [left], [right], [up], [color], [forw], [back]
</dd>
<hr>
## color

```c
void color(uint8_t palidx)
```
<dt>Beschreibung</dt><dd>
Legt die Farbe der Schildkrötenfarbe fest.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| palidx | Farbe, Palettenindex 0 bis 255 |
</dd>
<dt>Siehe auch</dt><dd>
[move], [left], [right], [up], [down], [forw], [back]
</dd>
<hr>
## forw

```c
void forw(uint16_t cnt)
```
<dt>Beschreibung</dt><dd>
Bewegt die Schildkröte vorwärts.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| cnt | Menge in Pixeln (oder 1/128 Kacheln mit [maze]) |
</dd>
<dt>Siehe auch</dt><dd>
[move], [left], [right], [up], [down], [color], [back]
</dd>
<hr>
## back

```c
void back(uint16_t cnt)
```
<dt>Beschreibung</dt><dd>
Bewegt die Schildkröte rückwärts.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| cnt | Menge in Pixeln (oder 1/128 Kacheln mit [maze]) |
</dd>
<dt>Siehe auch</dt><dd>
[move], [left], [right], [up], [down], [color], [forw]
</dd>
<hr>
## spr

```c
void spr(int16_t x, int16_t y, uint16_t sprite, uint8_t sw, uint8_t sh, int8_t scale, uint8_t type)
```
<dt>Beschreibung</dt><dd>
Zeigt ein Sprite oder mehrere benachbarte Sprites an.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| x | X-Koordinate in Pixel |
| y | Y-Koordinate in Pixel |
| sprite | Sprite-ID, 0 bis 1023 |
| sw | Anzahl der horizontalen Sprites |
| sh | Anzahl der vertikalen Sprites |
| scale | Skala, -3 bis 4 |
| type | transformieren, 0=normal, 1=90°, 2=180°, 3=270°, 4=vert. spiegeln, 5=90°+spiegeln, 6=horiz. spiegeln, 7=270°+spiegeln |
</dd>
<dt>Siehe auch</dt><dd>
[dlg], [stext]
</dd>
<hr>
## dlg

```c
void dlg(int16_t x, int16_t y, uint16_t w, uint16_t h, int8_t scale,
    uint16_t tl, uint16_t tm, uint16_t tr,
    uint16_t ml, uint16_t bg, uint16_t mr,
    uint16_t bl, uint16_t bm, uint16_t br)
```
<dt>Beschreibung</dt><dd>
Zeigt ein Dialogfenster mit Sprites an.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| x | X-Koordinate in Pixel |
| y | Y-Koordinate in Pixel |
| w | Dialogbreite in Pixel |
| h | Dialoghöhe in Pixel |
| scale | Skala, -3 bis 4 |
| tl | Sprite-ID in der oberen linken Ecke |
| tm | Sprite-ID oberen in der Mitte |
| tr | Sprite-ID in der oberen rechten Ecke |
| ml | Mittlere linke Sprite-ID |
| bg | Hintergrund-Sprite-ID |
| mr | Mittlere rechte Sprite-ID |
| bl | Sprite-ID in der unteren linken Ecke |
| bm | Sprite-ID unten in der Mitte |
| br | Sprite-ID in der unteren rechten Ecke |
</dd>
<dt>Siehe auch</dt><dd>
[spr], [stext]
</dd>
<hr>
## stext

```c
void stext(int16_t x, int16_t y, uint16_t fs, uint16_t fu, uint8_t sw, uint8_t sh, int8_t scale, str_t str)
```
<dt>Beschreibung</dt><dd>
Zeigt Text mithilfe von Sprites auf dem Bildschirm an.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| x | X-Koordinate in Pixel |
| y | Y-Koordinate in Pixel |
| fs | Erste Sprite-ID, die zur Anzeige verwendet werden soll |
| fu | Erster UNICODE (kleinstes Zeichen) in der Zeichenfolge |
| sw | Anzahl der horizontalen Sprites |
| sh | Anzahl der vertikalen Sprites |
| scale | Skala, -3 bis 4 |
| str | nullterminierte UTF-8-Zeichenfolge |
</dd>
<dt>Siehe auch</dt><dd>
[spr], [dlg]
</dd>
<hr>
## remap

```c
void remap(addr_t replace)
```
<dt>Beschreibung</dt><dd>
Ersetzt Kacheln auf der Karte. Kann zum Animieren von Kacheln auf der Karte verwendet werden.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| replace | Ein Array von 256 Sprite-IDs |
</dd>
<dt>Siehe auch</dt><dd>
[mget], [mset], [map], [maze]
</dd>
<hr>
## mget

```c
uint16_t mget(uint16_t mx, uint16_t my)
```
<dt>Beschreibung</dt><dd>
Gibt eine Kachel auf der Karte zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| mx | X-Koordinate auf der Karte in Kacheln |
| my | Y-Koordinate auf der Karte in Kacheln |
</dd>
<dt>Rückgabewert</dt><dd>
Die Sprite-ID der Kachel an der angegebenen Koordinate.
</dd>
<dt>Siehe auch</dt><dd>
[remap], [mset], [map], [maze]
</dd>
<hr>
## mset

```c
void mset(uint16_t mx, uint16_t my, uint16_t sprite)
```
<dt>Beschreibung</dt><dd>
Legt eine Kachel auf der Karte fest.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| mx | X-Koordinate auf der Karte in Kacheln |
| my | Y-Koordinate auf der Karte in Kacheln |
| sprite | Sprite-ID, 0 bis 1023 |
</dd>
<dt>Siehe auch</dt><dd>
[remap], [mget], [map], [maze]
</dd>
<hr>
## map

```c
void map(int16_t x, int16_t y, uint16_t mx, uint16_t my, uint16_t mw, uint16_t mh, int8_t scale)
```
<dt>Beschreibung</dt><dd>
Zeichnet die Karte (oder einen Teil davon).
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| x | X-Koordinate in Pixel |
| y | Y-Koordinate in Pixel |
| mx | X-Koordinate auf der Karte in Kacheln |
| my | Y-Koordinate auf der Karte in Kacheln |
| mw | Anzahl der horizontalen Kacheln |
| mh | Anzahl der vertikalen Kacheln |
| scale | Skala, -3 bis 4 |
</dd>
<dt>Siehe auch</dt><dd>
[remap], [mget], [mset], [maze]
</dd>
<hr>
## maze

```c
void maze(uint16_t mx, uint16_t my, uint16_t mw, uint16_t mh, uint8_t scale,
    uint16_t sky, uint16_t grd, uint16_t door, uint16_t wall, uint16_t obj, uint8_t numnpc, addr_t npc)
```
<dt>Beschreibung</dt><dd>
Zeigt die Karte als 3D-Labyrinth unter Verwendung der Position der Schildkröte an.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| mx | X-Koordinate auf der Karte in Kacheln |
| my | Y-Koordinate auf der Karte in Kacheln |
| mw | Anzahl der horizontalen Kacheln |
| mh | Anzahl der vertikalen Kacheln |
| scale | Anzahl der Sprites pro Kachel in Zweierpotenzen, 0 bis 3 |
| sky | Index der Himmelskacheln |
| grd | Index der Bodenkacheln |
| door | Index der ersten Türfliesen |
| wall | Index der ersten Wandfliesen |
| obj | Index der ersten Objekt |
| numnpc | Anzahl der NPC-Datensätze |
| npc | ein uint32_t-Array aus numnpc mal x, y, Tile-Indextripeln |
</dd>
<dt>Siehe auch</dt><dd>
[remap], [mget], [mset], [map]
</dd>

# Benutzereingabe

## getpad

```c
int getpad(int pad, int btn)
```
<dt>Beschreibung</dt><dd>
Ruft den aktuellen Status einer Gamepad-Taste ab.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| pad | Gamepad-Index, 0 bis 3 |
| btn | eine der [Gamepad]-Tasten, `BTN_` |
</dd>
<dt>Rückgabewert</dt><dd>
Null, wenn nicht gedrückt, ungleich Null, wenn gedrückt.
</dd>
<dt>Siehe auch</dt><dd>
[prspad], [relpad], [getbtn], [getclk], [getkey]
</dd>
<hr>
## prspad

```c
int prspad(int pad, int btn)
```
<dt>Beschreibung</dt><dd>
Gibt treu zurück, wenn die Gamepad-Taste seit dem letzten Aufruf gedrückt wurde.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| pad | Gamepad-Index, 0 bis 3 |
| btn | eine der [Gamepad]-Tasten, `BTN_` |
</dd>
<dt>Rückgabewert</dt><dd>
Null, wenn nicht gedrückt, ungleich Null, wenn gedrückt.
</dd>
<dt>Siehe auch</dt><dd>
[relpad], [getpad], [getbtn], [getclk], [getkey]
</dd>
<hr>
## relpad

```c
int relpad(int pad, int btn)
```
<dt>Beschreibung</dt><dd>
Gibt treu zurück, wenn die Gamepad-Taste seit dem letzten Aufruf losgelassen wurde.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| pad | Gamepad-Index, 0 bis 3 |
| btn | eine der [Gamepad]-Tasten, `BTN_` |
</dd>
<dt>Rückgabewert</dt><dd>
Null, wenn nicht freigegeben, ungleich Null, wenn freigegeben.
</dd>
<dt>Siehe auch</dt><dd>
[prspad], [getpad], [getbtn], [getclk], [getkey]
</dd>
<hr>
## getbtn

```c
int getbtn(int btn)
```
<dt>Beschreibung</dt><dd>
Ruft den Zustand der Maustasten ab.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| btn | eine der [Mauszeiger]-Tasten, `BTN_` oder `SCR_` |
</dd>
<dt>Rückgabewert</dt><dd>
Null, wenn nicht gedrückt, ungleich Null, wenn gedrückt.
</dd>
<dt>Siehe auch</dt><dd>
[prspad], [relpad], [getpad], [getclk], [getkey]
</dd>
<hr>
## getclk

```c
int getclk(int btn)
```
<dt>Beschreibung</dt><dd>
Ruft das Klicken mit der Maustaste ab.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| btn | eine der [Mauszeiger]-Tasten, `BTN_` |
</dd>
<dt>Rückgabewert</dt><dd>
Null, wenn nicht geklickt wird, ungleich Null, wenn geklickt wird.
</dd>
<dt>Siehe auch</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getkey]
</dd>
<hr>
## getkey

```c
int getkey(int sc)
```
<dt>Beschreibung</dt><dd>
Ruft den aktuellen Status eines Tasten ab.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| sc | Scancode, 1 bis 144, siehe [Tastatur] |
</dd>
<dt>Rückgabewert</dt><dd>
Null, wenn nicht gedrückt, ungleich Null, wenn gedrückt.
</dd>
<dt>Siehe auch</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getclk]
</dd>
<hr>
## popkey

```c
uint32_t popkey(void)
```
<dt>Beschreibung</dt><dd>
Holen Sie sich einen UTF-8-Schlüssel aus der Tastaturwarteschlange. Siehe [Tastatur] und für die Blockierungsversion [getc].
</dd>
<dt>Rückgabewert</dt><dd>
Die UTF-8-Darstellung des Tasten oder 0, wenn die Warteschlange leer war (keine Blockierung).
</dd>
<dt>Siehe auch</dt><dd>
[pendkey], [lenkey], [speckey], [getc]
</dd>
<hr>
## pendkey

```c
int pendkey(void)
```
<dt>Beschreibung</dt><dd>
Gibt treu zurück, wenn ein Taste in der Warteschlange aussteht (bleibt jedoch in der Warteschlange und wird nicht entfernt).
</dd>
<dt>Rückgabewert</dt><dd>
Gibt 1 zurück, wenn Taste in der Warteschlange ausstehen.
</dd>
<dt>Siehe auch</dt><dd>
[popkey], [lenkey], [speckey]
</dd>
<hr>
## lenkey

```c
int lenkey(uint32_t key)
```
<dt>Beschreibung</dt><dd>
Gibt die Länge eines UTF-8-Teasten in Bytes zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| key | die Tastaturtaste, aus der Warteschlange entfernt |
</dd>
<dt>Rückgabewert</dt><dd>
UTF-8 representation's length in bytes.
</dd>
<dt>Siehe auch</dt><dd>
[popkey], [pendkey], [speckey]
</dd>
<hr>
## speckey

```c
int speckey(uint32_t key)
```
<dt>Beschreibung</dt><dd>
Gibt treu zurück, wenn der Taste ein Sondertasten ist.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| key | die Tastaturtaste, aus der Warteschlange entfernt |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt 1 zurück, wenn es sich um einen Sondertasten handelt, und 0, wenn es sich um einen druckbaren Tasten handelt.
</dd>
<dt>Siehe auch</dt><dd>
[popkey], [pendkey], [lenkey]
</dd>

# Mathematik

## rand

```c
uint32_t rand(void)
```
<dt>Beschreibung</dt><dd>
Werden Sie zufällig. Verwenden Sie `%` Modulo, um es kleiner zu machen, zum Beispiel gibt `1 + rand() % 6` einen
Zufallswert zwischen 1 und 6 zurück, wie ein Würfel.
</dd>
<dt>Rückgabewert</dt><dd>
Eine Zufallszahl zwischen 0 und 2^^32^^-1 (4294967295).
</dd>
<dt>Siehe auch</dt><dd>
[rnd]
</dd>
<hr>
## rnd

```c
float rnd(void)
```
<dt>Beschreibung</dt><dd>
Werden Sie zufällig. Wie [rand], gibt aber eine Gleitkommazahl zurück.
</dd>
<dt>Rückgabewert</dt><dd>
Eine Zufallszahl zwischen 0.0 und 1.0.
</dd>
<dt>Siehe auch</dt><dd>
[rand]
</dd>
<hr>
## float

```c
float float(int val)
```
<dt>Beschreibung</dt><dd>
Gibt das Gleitkomma-Äquivalent einer Ganzzahl zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Der Gleitkommawert.
</dd>
<dt>Siehe auch</dt><dd>
[int]
</dd>
<hr>
## int

```c
int int(float val)
```
<dt>Beschreibung</dt><dd>
Gibt das ganzzahlige Äquivalent einer Gleitkommazahl zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Die Ganzzahl des Werts.
</dd>
<dt>Siehe auch</dt><dd>
[float]
</dd>
<hr>
## floor

```c
float floor(float val)
```
<dt>Beschreibung</dt><dd>
Gibt die größte ganze Zahl zurück, die nicht größer als der Wert ist.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Die Wertuntergrenze.
</dd>
<dt>Siehe auch</dt><dd>
[ceil]
</dd>
<hr>
## ceil

```c
float ceil(float val)
```
<dt>Beschreibung</dt><dd>
Gibt die kleinste ganze Zahl zurück, die nicht kleiner als der Wert ist.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Die Wertobergrenze.
</dd>
<dt>Siehe auch</dt><dd>
[floor]
</dd>
<hr>
## sgn

```c
float sgn(float val)
```
<dt>Beschreibung</dt><dd>
Gibt das Vorzeichen des Werts zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Entweder 1.0 oder -1.0.
</dd>
<dt>Siehe auch</dt><dd>
[abs]
</dd>
<hr>
## abs

```c
float abs(float val)
```
<dt>Beschreibung</dt><dd>
Gibt den Absolutwert des Werts zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Entweder Wert oder -Wert, immer positiv.
</dd>
<dt>Siehe auch</dt><dd>
[sgn]
</dd>
<hr>
## exp

```c
float exp(float val)
```
<dt>Beschreibung</dt><dd>
Gibt die Exponentialfunktion des Werts zurück, d. h. die Basis des natürlichen Logarithmus hoch mit dem Wert.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt e^^val^^ zurück.
</dd>
<dt>Siehe auch</dt><dd>
[log], [pow]
</dd>
<hr>
## log

```c
float log(float val)
```
<dt>Beschreibung</dt><dd>
Gibt den natürlichen Logarithmus des Werts zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Den natürlichen Logarithmus des Werts.
</dd>
<dt>Siehe auch</dt><dd>
[exp]
</dd>
<hr>
## pow

```c
float pow(float val, float exp)
```
<dt>Beschreibung</dt><dd>
Gibt den Wert hoch mit dem Exponenten zurück. Dies ist ein langsamer Vorgang, den Sie vermeiden sollten.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
| exp | exponent |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt val^^exp^^ zurück.
</dd>
<dt>Siehe auch</dt><dd>
[exp], [sqrt], [rsqrt]
</dd>
<hr>
## sqrt

```c
float sqrt(float val)
```
<dt>Beschreibung</dt><dd>
Gibt die Quadratwurzel des Werts zurück. Dies ist ein langsamer Vorgang, den Sie vermeiden sollten.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Quadratwurzel des Werts.
</dd>
<dt>Siehe auch</dt><dd>
[pow], [rsqrt]
</dd>
<hr>
## rsqrt

```c
float rsqrt(float val)
```
<dt>Beschreibung</dt><dd>
Gibt den Kehrwert der Quadratwurzel des Werts zurück (`1 / sqrt(val)`). Verwendet die schnelle Methode von John Carmack.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Kehrwert der Quadratwurzel des Werts.
</dd>
<dt>Siehe auch</dt><dd>
[pow], [sqrt]
</dd>
<hr>
## clamp

```c
float clamp(float val, float minv, float maxv)
```
<dt>Beschreibung</dt><dd>
Klemmt einen Wert zwischen den Grenzwerten.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert |
| minv | Mindestwert |
| maxv | Maximalwert |
</dd>
<dt>Rückgabewert</dt><dd>
Geklemmter Wert.
</dd>
<dt>Siehe auch</dt><dd>
[clampv2], [clampv3], [clampv4]
</dd>
<hr>
## lerp

```c
float lerp(float a, float b, float t)
```
<dt>Beschreibung</dt><dd>
Linear interpoliert zwei Zahlen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Erste Gleitkommazahl |
| b | Zweite Gleitkommazahl |
| t | Interpolationswert zwischen 0.0 und 1.0 |
</dd>
<dt>Siehe auch</dt><dd>
[lerpv2], [lerpv3], [lerpv4], [lerpq], [slerpq]
</dd>
<hr>
## pi

```c
float pi(void)
```
<dt>Beschreibung</dt><dd>
Gibt π als Gleitkommazahl zurück.
</dd>
<dt>Rückgabewert</dt><dd>
Der Wert 3.14159265358979323846.
</dd>
<hr>
## cos

```c
float cos(uint16_t deg)
```
<dt>Beschreibung</dt><dd>
Gibt den Kosinus zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| deg | Grad, 0 bis 359, 0 ist oben, 90 rechts |
</dd>
<dt>Rückgabewert</dt><dd>
Kosinus des Grades, zwischen -1.0 und 1.0.
</dd>
<dt>Siehe auch</dt><dd>
[sin], [tan], [acos], [asin], [atan], [atan2]
</dd>
<hr>
## sin

```c
float sin(uint16_t deg)
```
<dt>Beschreibung</dt><dd>
Gibt Sinus zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| deg | Grad, 0 bis 359, 0 ist oben, 90 rechts |
</dd>
<dt>Rückgabewert</dt><dd>
Sinus des Grades, zwischen -1.0 und 1.0.
</dd>
<dt>Siehe auch</dt><dd>
[cos], [tan], [acos], [asin], [atan], [atan2]
</dd>
<hr>
## tan

```c
float tan(uint16_t deg)
```
<dt>Beschreibung</dt><dd>
Gibt Tangente zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| deg | Grad, 0 bis 359, 0 ist oben, 90 rechts |
</dd>
<dt>Rückgabewert</dt><dd>
Tangens des Grades, zwischen -1.0 und 1.0.
</dd>
<dt>Siehe auch</dt><dd>
[cos], [sin], [acos], [asin], [atan], [atan2]
</dd>
<hr>
## acos

```c
uint16_t acos(float val)
```
<dt>Beschreibung</dt><dd>
Gibt Arcuskosinus zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert, -1.0 bis 1.0 |
</dd>
<dt>Rückgabewert</dt><dd>
Arcuskosinus in Grad, 0 bis 359, 0 ist oben, 90 nach rechts.
</dd>
<dt>Siehe auch</dt><dd>
[cos], [sin], [tan], [asin], [atan], [atan2]
</dd>
<hr>
## asin

```c
uint16_t asin(float val)
```
<dt>Beschreibung</dt><dd>
Gibt Arcussinus zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert, -1.0 bis 1.0 |
</dd>
<dt>Rückgabewert</dt><dd>
Arcussinus in Grad, 0 bis 359, 0 ist oben, 90 nach rechts.
</dd>
<dt>Siehe auch</dt><dd>
[cos], [sin], [tan], [acos], [atan], [atan2]
</dd>
<hr>
## atan

```c
uint16_t atan(float val)
```
<dt>Beschreibung</dt><dd>
Gibt den Arcus-Tangens zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| val | Wert, -1.0 bis 1.0 |
</dd>
<dt>Rückgabewert</dt><dd>
Arcus-Tangens in Grad, 0 bis 359, 0 ist oben, 90 nach rechts.
</dd>
<dt>Siehe auch</dt><dd>
[cos], [sin], [tan], [acos], [asin], [atan2]
</dd>
<hr>
## atan2

```c
uint16_t atan2(float y, float x)
```
<dt>Beschreibung</dt><dd>
Gibt den Arcus-Tangens für y/x zurück und verwendet die Vorzeichen von y und x, um den Quadranten zu bestimmen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| y | Y-Koordinate |
| x | X-Koordinate |
</dd>
<dt>Rückgabewert</dt><dd>
Arcus-Tangens in Grad, 0 bis 359, 0 ist oben, 90 nach rechts.
</dd>
<dt>Siehe auch</dt><dd>
[cos], [sin], [tan], [acos], [asin]
</dd>
<hr>
## dotv2

```c
float dotv2(addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Berechnet das Skalarprodukt zweier Vektoren mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von zwei Gleitkommazahlen |
| b | Adresse von zwei Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Skalarprodukt der Vektoren.
</dd>
<dt>Siehe auch</dt><dd>
[lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## lenv2

```c
float lenv2(addr_t a)
```
<dt>Beschreibung</dt><dd>
Berechnet die Länge eines Vektors mit zwei Elementen. Das ist langsam, versuchen Sie es zu vermeiden (siehe [normv2]).
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von zwei Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Länge des Vektors.
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## scalev2

```c
void scalev2(addr_t a, float s)
```
<dt>Beschreibung</dt><dd>
Skaliert einen Vektor mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von zwei Gleitkommazahlen |
| s | Skaliererwert |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## negv2

```c
void negv2(addr_t a)
```
<dt>Beschreibung</dt><dd>
Negiert einen Vektor mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von zwei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [scalev2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## addv2

```c
void addv2(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Addiert Vektoren mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von zwei Gleitkommazahlen, Ergebnis |
| a | Adresse von zwei Gleitkommazahlen |
| b | Adresse von zwei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## subv2

```c
void subv2(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Subtrahiert Vektoren mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von zwei Gleitkommazahlen, Ergebnis |
| a | Adresse von zwei Gleitkommazahlen |
| b | Adresse von zwei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## mulv2

```c
void mulv2(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Multipliziert Vektoren mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von zwei Gleitkommazahlen, Ergebnis |
| a | Adresse von zwei Gleitkommazahlen |
| b | Adresse von zwei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## divv2

```c
void divv2(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Teilt Vektoren durch zwei Elemente.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von zwei Gleitkommazahlen, Ergebnis |
| a | Adresse von zwei Gleitkommazahlen |
| b | Adresse von zwei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## clampv2

```c
void clampv2(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dt>Beschreibung</dt><dd>
Klemmt Vektoren mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von zwei Gleitkommazahlen, Ergebnis |
| v | Adresse von zwei Gleitkommazahlen, Eingabe |
| minv | Adresse von zwei Gleitkommazahlen, Ninimum |
| maxv | Adresse von zwei Gleitkommazahlen, Maximum |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [lerpv2], [normv2]
</dd>
<hr>
## lerpv2

```c
void lerpv2(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Beschreibung</dt><dd>
Linear interpoliert Vektoren mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von zwei Gleitkommazahlen, Ergebnis |
| a | Adresse von zwei Gleitkommazahlen |
| b | Adresse von zwei Gleitkommazahlen |
| t | Interpolationswert zwischen 0.0 und 1.0 |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [normv2]
</dd>
<hr>
## normv2

```c
void normv2(addr_t a)
```
<dt>Beschreibung</dt><dd>
Normalisiert einen Vektor mit zwei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von zwei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2]
</dd>
<hr>
## dotv3

```c
float dotv3(addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Berechnet das Skalarprodukt zweier Vektoren mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von drei Gleitkommazahlen |
| b | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Skalarprodukt der Vektoren.
</dd>
<dt>Siehe auch</dt><dd>
[lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## lenv3

```c
float lenv3(addr_t a)
```
<dt>Beschreibung</dt><dd>
Berechnet die Länge eines Vektors mit drei Elementen. Das ist langsam, versuchen Sie es zu vermeiden (siehe [normv3]).
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Länge des Vektors.
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## scalev3

```c
void scalev3(addr_t a, float s)
```
<dt>Beschreibung</dt><dd>
Skaliert einen Vektor mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von drei Gleitkommazahlen |
| s | Skaliererwert |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## negv3

```c
void negv3(addr_t a)
```
<dt>Beschreibung</dt><dd>
Negiert einen Vektor mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## addv3

```c
void addv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Addiert Vektoren mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| a | Adresse von drei Gleitkommazahlen |
| b | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## subv3

```c
void subv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Subtrahiert Vektoren mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| a | Adresse von drei Gleitkommazahlen |
| b | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## mulv3

```c
void mulv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Multipliziert Vektoren mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| a | Adresse von drei Gleitkommazahlen |
| b | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## divv3

```c
void divv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Teilt Vektoren durch drei Elemente.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| a | Adresse von drei Gleitkommazahlen |
| b | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## crossv3

```c
void crossv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Berechnet das Kreuzprodukt von Vektoren mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| a | Adresse von drei Gleitkommazahlen |
| b | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## clampv3

```c
void clampv3(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dt>Beschreibung</dt><dd>
Klemmt Vektoren mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| v | Adresse von drei Gleitkommazahlen, Eingabe |
| minv | Adresse von drei Gleitkommazahlen, Minimum |
| maxv | Adresse von drei Gleitkommazahlen, Maximum |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [lerpv3], [normv3]
</dd>
<hr>
## lerpv3

```c
void lerpv3(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Beschreibung</dt><dd>
Linear interpoliert Vektoren mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| a | Adresse von drei Gleitkommazahlen |
| b | Adresse von drei Gleitkommazahlen |
| t | Interpolationswert zwischen 0.0 und 1.0 |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [normv3]
</dd>
<hr>
## normv3

```c
void normv3(addr_t a)
```
<dt>Beschreibung</dt><dd>
Normalisiert einen Vektor mit drei Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3]
</dd>
<hr>
## dotv4

```c
float dotv4(addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Berechnet das Skalarprodukt zweier Vektoren mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Skalarprodukt der Vektoren.
</dd>
<dt>Siehe auch</dt><dd>
[lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## lenv4

```c
float lenv4(addr_t a)
```
<dt>Beschreibung</dt><dd>
Berechnet die Länge eines Vektors mit vier Elementen. Das ist langsam, versuchen Sie es zu vermeiden (siehe [normv4]).
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Länge des Vektors.
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## scalev4

```c
void scalev4(addr_t a, float s)
```
<dt>Beschreibung</dt><dd>
Skaliert einen Vektor mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
| s | Skaliererwert |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## negv4

```c
void negv4(addr_t a)
```
<dt>Beschreibung</dt><dd>
Negiert einen Vektor mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [scalev4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## addv4

```c
void addv4(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Addiert Vektoren mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [negv4], [scalev4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## subv4

```c
void subv4(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Subtrahiert Vektoren mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## mulv4

```c
void mulv4(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Multipliziert Vektoren mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## divv4

```c
void divv4(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Teilt Vektoren durch vier Elemente.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## clampv4

```c
void clampv4(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dt>Beschreibung</dt><dd>
Klemmt Vektoren mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| v | Adresse von vier Gleitkommazahlen, Eingabe |
| minv | Adresse von vier Gleitkommazahlen, Minimum |
| maxv | Adresse von vier Gleitkommazahlen, Maximum |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [lerpv4], [normv4]
</dd>
<hr>
## lerpv4

```c
void lerpv4(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Beschreibung</dt><dd>
Linear interpoliert Vektoren mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
| t | Interpolationswert zwischen 0.0 und 1.0 |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [normv4]
</dd>
<hr>
## normv4

```c
void normv4(addr_t a)
```
<dt>Beschreibung</dt><dd>
Normalisiert einen Vektor mit vier Elementen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4]
</dd>
<hr>
## idq

```c
void idq(addr_t a)
```
<dt>Beschreibung</dt><dd>
Lädt die Identitätsquaternion.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## eulerq

```c
void eulerq(addr_t dst, uint16_t pitch, uint16_t yaw, uint16_t roll)
```
<dt>Beschreibung</dt><dd>
Lädt eine Quaternion unter Verwendung von Euler-Winkeln.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| pitch | Drehung um die X-Achse in Grad, 0 bis 359 |
| yaw | Drehung um die Y-Achse in Grad, 0 bis 359 |
| roll | Drehung um die Z-Achse in Grad, 0 bis 359 |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## dotq

```c
float dotq(addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Berechnet das Skalarprodukt einer Quaternion.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Skalarprodukt der Quaternion.
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## lenq

```c
float lenq(addr_t a)
```
<dt>Beschreibung</dt><dd>
Berechnet die Länge einer Quaternion.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Länge der Quaternion.
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## scaleq

```c
void scaleq(addr_t a, float s)
```
<dt>Beschreibung</dt><dd>
Skaliert eine Quaternion.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
| s | Skaliererwert |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## negq

```c
void negq(addr_t a)
```
<dt>Beschreibung</dt><dd>
Negiert eine Quaternion.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## addq

```c
void addq(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Addiert Quaternionen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## subq

```c
void subq(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Subtrahiert Quaternionen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## mulq

```c
void mulq(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Multipliziert Quaternionen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## rotq

```c
void rotq(addr_t dst, addr_t q, addr_t v)
```
<dt>Beschreibung</dt><dd>
Dreht einen Vektor mit drei Elementen um ein Quaternion.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| q | Adresse von vier Gleitkommazahlen |
| v | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## lerpq

```c
void lerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Beschreibung</dt><dd>
Linear interpoliert zwei Quaternionen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
| t | Interpolationswert zwischen 0.0 und 1.0 |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [slerpq], [normq]
</dd>
<hr>
## slerpq

```c
void slerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Beschreibung</dt><dd>
Sphärisch interpoliert zwei Quaternionen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| a | Adresse von vier Gleitkommazahlen |
| b | Adresse von vier Gleitkommazahlen |
| t | Interpolationswert zwischen 0.0 und 1.0 |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [normq]
</dd>
<hr>
## normq

```c
void normq(addr_t a)
```
<dt>Beschreibung</dt><dd>
Normalisiert eine Quaternion.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq]
</dd>
<hr>
## idm4

```c
void idm4(addr_t a)
```
<dt>Beschreibung</dt><dd>
Lädt eine 4 x 4-Identitätsmatrix.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von 16 Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## trsm4

```c
void trsm4(addr_t dst, addr_t t, addr_t r, addr_t s)
```
<dt>Beschreibung</dt><dd>
Erstellt eine 4 x 4-Matrix mit Übersetzung, Rotation und Skalierung.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von 16 Gleitkommazahlen, Zielmatrix |
| t | Adresse von drei Gleitkommazahlen, Übersetzungsvektor |
| r | Adresse von vier Gleitkommazahlen, Rotationsquaternion |
| s | Adresse von drei Gleitkommazahlen, Skalierungsvektor |
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## detm4

```c
float detm4(addr_t a)
```
<dt>Beschreibung</dt><dd>
Gibt die Determinante der Matrix zurück.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| a | Adresse von 16 Gleitkommazahlen |
</dd>
<dt>Rückgabewert</dt><dd>
Die Determinante der Matrix.
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [trsm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## addm4

```c
void addm4(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Addiert Matrizen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von 16 Gleitkommazahlen, Ergebnis |
| a | Adresse von 16 Gleitkommazahlen |
| b | Adresse von 16 Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [trsm4], [detm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## subm4

```c
void subm4(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Subtrahiert Matrizen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von 16 Gleitkommazahlen, Ergebnis |
| a | Adresse von 16 Gleitkommazahlen |
| b | Adresse von 16 Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## mulm4

```c
void mulm4(addr_t dst, addr_t a, addr_t b)
```
<dt>Beschreibung</dt><dd>
Multipliziert Matrizen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von 16 Gleitkommazahlen, Ergebnis |
| a | Adresse von 16 Gleitkommazahlen |
| b | Adresse von 16 Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## mulm4v3

```c
void mulm4v3(addr_t dst, addr_t m, addr_t v)
```
<dt>Beschreibung</dt><dd>
Multipliziert einen Vektor mit drei Elementen mit einer Matrix.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von drei Gleitkommazahlen, Ergebnis |
| m | Adresse von 16 Gleitkommazahlen |
| v | Adresse von drei Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## mulm4v4

```c
void mulm4v4(addr_t dst, addr_t m, addr_t v)
```
<dt>Beschreibung</dt><dd>
Multipliziert einen Vektor mit vier Elementen mit einer Matrix.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von vier Gleitkommazahlen, Ergebnis |
| m | Adresse von 16 Gleitkommazahlen |
| v | Adresse von vier Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [invm4], [trpm4]
</dd>
<hr>
## invm4

```c
void invm4(addr_t dst, addr_t a)
```
<dt>Beschreibung</dt><dd>
Berechnet die inverse Matrix.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von 16 Gleitkommazahlen, Ergebnis |
| a | Adresse von 16 Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [trpm4]
</dd>
<hr>
## trpm4

```c
void trpm4(addr_t dst, addr_t a)
```
<dt>Beschreibung</dt><dd>
Matrix transponieren.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse von 16 Gleitkommazahlen, Ergebnis |
| a | Adresse von 16 Gleitkommazahlen |
</dd>
<dt>Siehe auch</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4]
</dd>
<hr>
## trns

```c
void trns(addr_t dst, addr_t src, uint8_t num,
    int16_t x, int16_t y, int16_t z,
    uint16_t pitch, uint16_t yaw, uint16_t roll,
    float scale)
```
<dt>Beschreibung</dt><dd>
Vertexwolke verschieben, 3D-Modell in [3D-Welt] platzieren.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Zielscheitelpunkt-Array, jeweils 3 x 2 Bytes, X, Y, Z |
| src | Quellscheitelpunkt-Array, jeweils 3 x 2 Bytes, X, Y, Z |
| num | Anzahl der Scheitelpunktkoordinatentripel im Array |
| x | Welt-X-Koordinate, -32767 bis 32767 |
| y | Welt-Y-Koordinate, -32767 bis 32767 |
| z | Welt-Z-Koordinate, -32767 bis 32767 |
| pitch | Drehung um die X-Achse in Grad, 0 bis 359 |
| yaw | Drehung um die Y-Achse in Grad, 0 bis 359 |
| roll | Drehung um die Z-Achse in Grad, 0 bis 359 |
| scale | Skalierungswert, verwenden Sie 1.0 für Originalgröße |
</dd>
<dt>Siehe auch</dt><dd>
[mesh]
</dd>

# Speicher

## inb

```c
uint8_t inb(addr_t src)
```
<dt>Beschreibung</dt><dd>
Ein Byte aus dem Speicher einlesen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| src | Adresse, 0x00000 bis 0xBFFFF |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt den Wert an dieser Adresse zurück.
</dd>
<hr>
## inw

```c
uint16_t inw(addr_t src)
```
<dt>Beschreibung</dt><dd>
Ein Wort (word, zwei Bytes) aus dem Speicher einlesen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| src | Adresse, 0x00000 bis 0xBFFFE |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt den Wert an dieser Adresse zurück.
</dd>
<hr>
## ini

```c
uint32_t ini(addr_t src)
```
<dt>Beschreibung</dt><dd>
Eine Ganzzahl (int, vier Bytes) aus dem Speicher einlesen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| src | Adresse, 0x00000 bis 0xBFFFC |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt den Wert an dieser Adresse zurück.
</dd>
<hr>
## outb

```c
void outb(addr_t dst, uint8_t value)
```
<dt>Beschreibung</dt><dd>
Schreiben Sie ein Byte in den Speicher.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse, 0x00000 bis 0xBFFFF |
| value | Einzustellender Wert, 0 bis 255 |
</dd>
<hr>
## outw

```c
void outw(addr_t dst, uint16_t value)
```
<dt>Beschreibung</dt><dd>
Schreiben Sie ein Wort (word, zwei Bytes) in den Speicher.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse, 0x00000 bis 0xBFFFE |
| value | Einzustellender Wert, 0 bis 65535 |
</dd>
<hr>
## outi

```c
void outi(addr_t dst, uint32_t value)
```
<dt>Beschreibung</dt><dd>
Schreiben Sie eine Ganzzahl (int, vier Bytes) in den Speicher.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Adresse, 0x00000 bis 0xBFFFC |
| value | Einzustellender Wert, 0 bis 4294967295 |
</dd>
<hr>
## memsave

```c
int memsave(uint8_t overlay, addr_t src, uint32_t size)
```
<dt>Beschreibung</dt><dd>
Speichert Speicherbereich zum Overlay.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| overlay | Index des Overlays, in das geschrieben werden soll, 0 bis 255 |
| src | Speicheroffset, ab dem gespeichert werden soll, 0x00000 bis 0xBFFFF |
| size | Anzahl der zu speichernden Bytes |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt 1 bei Erfolg zurück, 0 bei Fehler.
</dd>
<dt>Siehe auch</dt><dd>
[memload]
</dd>
<hr>
## memload

```c
int memload(addr_t dst, uint8_t overlay, uint32_t maxsize)
```
<dt>Beschreibung</dt><dd>
Lädt ein Overlay in den angegebenen Speicherbereich.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Speicheroffset, in den geladen werden soll, 0x00000 bis 0xBFFFF |
| overlay | Index des Overlays, von dem gelesen werden soll, 0 bis 255 |
| maxsize | Maximale Anzahl zu ladender Bytes |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt die Anzahl der tatsächlich geladenen Bytes zurück.
</dd>
<dt>Siehe auch</dt><dd>
[memsave]
</dd>
<hr>
## memcpy

```c
void memcpy(addr_t dst, addr_t src, uint32_t len)
```
<dt>Beschreibung</dt><dd>
Speicherbereiche kopieren.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Zieladresse, 0x00000 bis 0xBFFFF |
| src | Quelladresse, 0x00000 bis 0xBFFFF |
| len | Anzahl der zu kopierenden Bytes |
</dd>
<hr>
## memset

```c
void memset(addr_t dst, uint8_t value, uint32_t len)
```
<dt>Beschreibung</dt><dd>
Speicherbereich auf einen bestimmten Wert setzen.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Zieladresse, 0x00000 bis 0xBFFFF |
| value | Einzustellender Wert, 0 bis 255 |
| len | Anzahl der festzulegenden Bytes |
</dd>
<hr>
## memcmp

```c
int memcmp(addr_t addr0, addr_t addr1, uint32_t len)
```
<dt>Beschreibung</dt><dd>
Vergleichen Sie Speicherbereiche.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| addr0 | Erste Adresse, 0x00000 bis 0xBFFFF |
| addr1 | Zweiste Adresse, 0x00000 bis 0xBFFFF |
| len | Anzahl der zu vergleichenden Bytes |
</dd>
<dt>Rückgabewert</dt><dd>
Gibt den Unterschied zurück, 0, wenn die beiden Speicherbereiche übereinstimmen.
</dd>
<hr>
## deflate

```c
int deflate(addr_t dst, addr_t src, uint32_t len)
```
<dt>Beschreibung</dt><dd>
Komprimieren Sie einen Puffer mit RFC1950 deflate (zlib).
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Zieladresse, 0x30000 bis 0xBFFFF |
| src | Quelladresse, 0x30000 bis 0xBFFFF |
| len | Anzahl der zu komprimierenden Bytes |
</dd>
<dt>Rückgabewert</dt><dd>
0 oder negativ bei Fehler, andernfalls die Länge des komprimierten Puffers und der komprimierten Daten in dst.
</dd>
<dt>Siehe auch</dt><dd>
[inflate]
</dd>
<hr>
## inflate

```c
int inflate(addr_t dst, addr_t src, uint32_t len)
```
<dt>Beschreibung</dt><dd>
Dekomprimieren Sie einen Puffer mit komprimierten RFC1950 deflate (zlib) Daten.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| dst | Zieladresse, 0x30000 bis 0xBFFFF |
| src | Quelladresse, 0x30000 bis 0xBFFFF |
| len | Anzahl der komprimierten Bytes |
</dd>
<dt>Rückgabewert</dt><dd>
0 oder negativ bei Fehler, andernfalls die Länge des unkomprimierten Puffers und der unkomprimierten Daten in dst.
</dd>
<dt>Siehe auch</dt><dd>
[deflate]
</dd>
<hr>
## time

```c
float time(void)
```
<dt>Beschreibung</dt><dd>
Gibt die Anzahl der Ticks seit dem Einschalten zurück.
</dd>
<dt>Rückgabewert</dt><dd>
Die seit dem Einschalten verstrichene Zeit in Millisekunden.
</dd>
<dt>Siehe auch</dt><dd>
[now]
</dd>
<hr>
## now

```c
uint32_t now(void)
```
<dt>Beschreibung</dt><dd>
Gibt den UNIX-Zeitstempel zurück. Überprüfen Sie das Byte bei Offset 0000C, um festzustellen, ob es überläuft.
</dd>
<dt>Rückgabewert</dt><dd>
Die seit dem 1. Januar 1970 um Mitternacht verstrichene Zeit in Sekunden, Greenwich Mean Time.
</dd>
<dt>Siehe auch</dt><dd>
[time]
</dd>
<hr>
## atoi

```c
int atoi(str_t src)
```
<dt>Beschreibung</dt><dd>
Konvertiert eine ASCII-Dezimalzeichenfolge in eine Ganzzahl.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| src | Zeichenfolgenadresse, 0x00000 bis 0xBFFFF |
</dd>
<dt>Rückgabewert</dt><dd>
Der Zahlenwert der Zeichenfolge.
</dd>
<dt>Siehe auch</dt><dd>
[itoa], [str], [val]
</dd>
<hr>
## itoa

```c
str_t itoa(int value)
```
<dt>Beschreibung</dt><dd>
Konvertiert eine Ganzzahl in eine ASCII-Dezimalzeichenfolge.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| value | Wert, -2147483648 bis 2147483647 |
</dd>
<dt>Rückgabewert</dt><dd>
Die konvertierte Zeichenfolge.
</dd>
<dt>Siehe auch</dt><dd>
[atoi], [str], [val]
</dd>
<hr>
## val

```c
float val(str_t src)
```
<dt>Beschreibung</dt><dd>
Konvertiert eine ASCII-Dezimalzeichenfolge in eine Gleitkommazahl.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| src | Zeichenfolgenadresse, 0x00000 bis 0xBFFFF |
</dd>
<dt>Rückgabewert</dt><dd>
Der Zahlenwert der Zeichenfolge.
</dd>
<dt>Siehe auch</dt><dd>
[itoa], [atoi], [str]
</dd>
<hr>
## str

```c
str_t str(float value)
```
<dt>Beschreibung</dt><dd>
Konvertiert eine Gleitkommazahl in eine ASCII-Dezimalzeichenfolge.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| value | Wert |
</dd>
<dt>Rückgabewert</dt><dd>
Die konvertierte Zeichenfolge.
</dd>
<dt>Siehe auch</dt><dd>
[atoi], [itoa], [val]
</dd>
<hr>
## sprintf

```c
str_t sprintf(str_t fmt, ...)
```
<dt>Beschreibung</dt><dd>
Gibt eine mit Null terminierte UTF-8-Zeichenfolge zurück, die mithilfe von Format und Argumenten erstellt wurde.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| fmt | [Formatierungszeichenfolge] |
| ... | optionale Argumente |
</dd>
<dt>Rückgabewert</dt><dd>
Konstruierte Zeichenfolge.
</dd>
<hr>
## strlen

```c
int strlen(str_t src)
```
<dt>Beschreibung</dt><dd>
Gibt die Anzahl der Bytes in einer Zeichenfolge zurück (ohne die abschließende Null).
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| src | Zeichenfolgenadresse, 0x00000 bis 0xBFFFF |
</dd>
<dt>Rückgabewert</dt><dd>
Die Anzahl der Bytes in der Zeichenfolge.
</dd>
<dt>Siehe auch</dt><dd>
[mblen]
</dd>
<hr>
## mblen

```c
int mblen(str_t src)
```
<dt>Beschreibung</dt><dd>
Gibt die Anzahl der UTF-8-Multibyte-Zeichen in einer Zeichenfolge zurück (ohne die abschließende Null).
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| src | Zeichenfolgenadresse, 0x00000 bis 0xBFFFF |
</dd>
<dt>Rückgabewert</dt><dd>
Die Anzahl der Zeichen in der Zeichenfolge.
</dd>
<dt>Siehe auch</dt><dd>
[strlen]
</dd>
<hr>
## malloc

```c
addr_t malloc(uint32_t size)
```
<dt>Beschreibung</dt><dd>
Weist Puffer dynamisch zu.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| size | Anzahl der zuzuordnenden Bytes |
</dd>
<dt>Rückgabewert</dt><dd>
Adresse des neu zugewiesenen Puffers oder NULL im Fehlerfall.
</dd>
<dt>Siehe auch</dt><dd>
[realloc], [free]
</dd>
<hr>
## realloc

```c
addr_t realloc(addr_t addr, uint32_t size)
```
<dt>Beschreibung</dt><dd>
Ändern Sie die Größe eines zuvor zugewiesenen Puffers.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| addr | Adresse des zugewiesenen Puffers |
| size | Anzahl der Bytes, auf die die Größe geändert werden soll |
</dd>
<dt>Rückgabewert</dt><dd>
Adresse des neu zugewiesenen Puffers oder NULL im Fehlerfall.
</dd>
<dt>Siehe auch</dt><dd>
[malloc], [free]
</dd>
<hr>
## free

```c
int free(addr_t addr)
```
<dt>Beschreibung</dt><dd>
Gibt dynamisch zugewiesenen Benutzerspeicher frei.
</dd>
<dt>Argumente</dt><dd>
| Argument | Beschreibung |
| addr | Adresse des zugewiesenen Puffers |
</dd>
<dt>Rückgabewert</dt><dd>
1 bei Erfolg, 0 bei Fehler.
</dd>
<dt>Siehe auch</dt><dd>
[malloc], [realloc]
</dd>
