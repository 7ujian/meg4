# Mapa pamięci

## Informacje ogólne

Wszystkie wartości w formie little endian, więc mniejsza cyfra jest przechowywana pod mniejszym adresem.

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|  00000 |          1 | MEG-4 wersja firmware - major                                      |
|  00001 |          1 | MEG-4 wersja firmware - minor                                      |
|  00002 |          1 | MEG-4 wersja firmware - poprawki                                   |
|  00003 |          1 | licznik wydajności, niewykorzystany czas ostatniej klatki w 1/1000 sekundy |
|  00004 |          4 | liczba tyknięć 1/1000 sekundy od włączenia zasilania               |
|  00008 |          8 | Znak czasu UTC UNIX                                                |
|  00010 |          2 | bieżąca lokalizacja                                                |

Licznik wydajności pokazuje czas niewykorzystany podczas generowania ostatniej ramki. Jeśli wartość ta wynosi zero lub jest ujemna, oznacza to
jak bardzo funkcja loop() przekroczyła dostępne ramy czasowe.

## Wskaźnik

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|  00012 |          2 | wskaźnik stanu przycisków (zobacz [getbtn] i [getclk])             |
|  00014 |          2 | wskaźnik indeksu sprite'a                                          |
|  00016 |          2 | wskaźnik współrzędnej X                                            |
|  00018 |          2 | wskaźnik współrzędnej Y                                            |

Wskaźniki przycisków:

| Define  | Bitmask   | Opis                                                               |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | Lewy przycisk myszy                                                |
| `BTN_M` |         2 | Środkowy przycisk myszy                                            |
| `BTN_R` |         4 | Prawy przycisk myszy                                               |
| `SCR_U` |         8 | Przewijanie do góry                                                |
| `SCR_D` |        16 | Przewijanie w dół                                                  |
| `SCR_L` |        32 | Przewijanie w lewo                                                 |
| `SCR_R` |        64 | Przewijanie w prawo                                                |

Górne bity indeksu wskaźnika sprite są używane dla hotspotów: bit 13-15 hotspot Y, bit 10-12 hotspot X, bit 0-9 sprite.
Istnieją pewne predefiniowane wbudowane kursory:

| Define       | Wartość   | Opis                                                          |
|--------------|----------:|---------------------------------------------------------------|
| `PTR_NORM`   |      03fb | Zwykły kursor (strzałka)                                      |
| `PTR_TEXT`   |      03fc | Kursor tekstu                                                 |
| `PTR_HAND`   |      0bfd | Kursor odnośnika                                              |
| `PTR_ERR`    |      93fe | Kursor błędu                                                  |
| `PTR_NONE`   |      ffff | Kursor jest ukryty                                            |

## Klawiatura

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|  0001A |          1 | ogon kolejki klawiatury                                            |
|  0001B |          1 | głowica kolejki klawiatury                                         |
|  0001C |         64 | kolejka klawiatury, 16 elementów, każdy po 4 bajty (patrz [popkey]) |
|  0005C |         18 | stan naciśniętych klawiszy klawiatury według kodów skanowania (patrz [getkey]) |

Klucze wyskakujące z kolejki są reprezentowane w UTF-8. Niektóre nieprawidłowe sekwencje UTF-8 reprezentują specjalne
(niedrukowalne) klucze, na przykład:

| Kod klucza | Opis                                         |
|---------|-------------------------------------------------|
| `\x8`   | Znak 8, klawisz <kbd>←Backspace</kbd>           |
| `\x9`   | Znak 9, klawisz <kbd>Tab</kbd>                  |
| `\n`    | Znak 10, klawisz <kbd>⏎Enter</kbd>              |
| `\x1b`  | Znak 27, klawisz <kbd>Esc</kbd>                 |
| `Del`   | Klawisz <kbd>Del</kbd>                          |
| `Up`    | Strzałka kursora, klawisz <kbd>▴</kbd>          |
| `Down`  | Strzałka kursora, klawisz <kbd>▾</kbd>          |
| `Left`  | Strzałka kursora, klawisz <kbd>◂</kbd>          |
| `Rght`  | Strzałka kursora, klawisz <kbd>▸</kbd>          |
| `Cut`   | Klawisz Ciąć (lub <kbd>Ctrl</kbd>+<kbd>X</kbd>) |
| `Cpy`   | Klawisz Kopiuj (lub <kbd>Ctrl</kbd>+<kbd>C</kbd>) |
| `Pst`   | Klawisz Wklej (lub <kbd>Ctrl</kbd>+<kbd>V</kbd>) |

Kody skanowania są następujące:

| Kod skanowania | Adres | Maska bitowa | Define   |
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

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|  0006E |          2 | próg joysticka gamepada (domyślnie 8000)                           |
|  00070 |          8 | główny gamepad - mapowania kodów skanowania klawiatury (patrz [klawiatura]) |
|  00078 |          4 | 4 stany naciśnięcia przycisków gamepada (patrz [getpad])           |

Przyciski gamepada:

| Define  | Maska bitowa | Opis                                                            |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | Przycisk `◁` lub joystick w lewo                                   |
| `BTN_U` |         2 | Przycisk `△` lub joystick w górę                                   |
| `BTN_R` |         4 | Przycisk `▷` lub joystick w prawo                                  |
| `BTN_D` |         8 | Przycisk `▽` lub joystick w dół                                    |
| `BTN_A` |        16 | Przycisk `Ⓐ`                                                       |
| `BTN_B` |        32 | Przycisk `Ⓑ`                                                       |
| `BTN_X` |        64 | Przycisk `Ⓧ`                                                       |
| `BTN_Y` |       128 | Przycisk `Ⓨ`                                                       |

Sekwencja `△△▽▽◁▷◁▷ⒷⒶ` powoduje naciśnięcie klawisza `KEY_CHEAT`.

## Procesor graficzny

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|  0007E |          1 | górne bity punktu kodowego UNICODE do mapowania glifów czcionek    |
|  0007F |          1 | selektor banku sprite'ów dla mapy                                  |
|  00080 |       1024 | paleta, 256 kolorów, każdy wpis 4 bajty, RGBA                      |
|  00480 |          2 | x0, obszar przycięcia X zaczyna w pikselach (dla wszystkich funkcji rysowania) |
|  00482 |          2 | x1, obszar przycięcia X koniec w pikselach                         |
|  00484 |          2 | y0, obszar przycięcia Y zaczyna się w pikselach                    |
|  00486 |          2 | y1, obszar przycięcia Y koniec w pikselach                         |
|  00488 |          2 | wyświetlana wartość przesunięcia VRAM X w pikselach lub 0xffff     |
|  0048A |          2 | wyświetlana wartość przesunięcia VRAM Y w pikselach lub 0xffff     |
|  0048C |          1 | opuszczona flaga żółwia (patrz [up], [down])                       |
|  0048D |          1 | kolor pisaka żółwia, indeks palety 0 do 255 (patrz [color])        |
|  0048E |          2 | kierunek żółwia w stopniach od 0 do 359 (patrz [left], [right])    |
|  00490 |          2 | żółw X przesunięcie w pikselach (patrz [move])                     |
|  00492 |          2 | żółw Y przesunięcie w pikselach                                    |
|  00494 |          2 | prędkość chodzenia po labiryncie w skali 1/128 płytek (patrz [maze]) |
|  00496 |          2 | prędkość obrotowa labiryntu w stopniach (od 1 do 90)               |
|  00498 |          1 | kolor pierwszego planu konsoli, indeks palety od 0 do 255 (patrz [printf]) |
|  00499 |          1 | kolor tła konsoli, indeks palety od 0 do 255                       |
|  0049A |          2 | przesunięcie konsoli X w pikselach                                 |
|  0049C |          2 | przesunięcie konsoli Y w pikselach                                 |
|  0049E |          2 | przesunięcie kamery X w [przestrzeni 3D] (patrz [tri3d], [tritx], [mesh]) |
|  004A0 |          2 | przesunięcie kamery Y                                              |
|  004A2 |          2 | przesunięcie kamery Z                                              |
|  004A4 |          2 | kierunek kamery, pochylenie (0 w górę, 90 do przodu)               |
|  004A6 |          2 | kierunek kamery, odchylenie (0 w lewo, 90 do przodu)               |
|  004A8 |          1 | pole widzenia kamery pod kątem (45, ujemne daje ortograficzne)     |
|  004AA |          2 | przesunięcie położenia źródła światła X (patrz [tri3d], [tritx], [mesh]) |
|  004AC |          2 | przesunięcie położenia źródła światła Y                            |
|  004AE |          2 | przesunięcie położenia źródła światła Z                            |
|  00600 |      64000 | mapa, indeksy sprite'ów 320 x 200 (zobacz [map] i [maze])          |
|  10000 |      65536 | sprite'y, indeksy palety 256 x 256, 1024 pikseli 8 x 8 (patrz [spr]) |
|  28000 |       2048 | okno dla glifów czcionki 4096 (patrz 0007E, [width] i [text])      |

## Cyfrowy Procesor Sygnałowy

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|  0007C |          1 | selektor banku przebiegów (1 do 31)                                |
|  0007D |          1 | selektor banku utworów muzycznych (0 do 7)                         |
|  004BA |          1 | aktualne tempo (w krokach na wiersz, tylko do odczytu)             |
|  004BB |          1 | aktualnie odtwarzany utwór (tylko do odczytu)                      |
|  004BC |          2 | aktualnie odtwarzany wiersz (tylko do odczytu)                     |
|  004BE |          2 | liczba wszystkich wierszy w bieżącym utworze (tylko do odczytu)    |
|  004C0 |         64 | 16 rejestrów stanu kanału, każdy 4 bajty (tylko do odczytu)        |
|  00500 |        256 | 64 efekty dźwiękowe, każdy 4 bajty                                 |
|  20000 |      16384 | okno dla próbek przebiegu (patrz 0007C)                            |
|  24000 |      16384 | okno dla wzorów muzycznych (patrz 0007D)                           |

Rejestry stanu DSP są tylko do odczytu i dla każdego kanału wyglądają następująco:

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | aktualna pozycja w odtwarzanym przebiegu                           |
|      2 |          1 | aktualny przebieg (od 1 do 31, 0 jeśli kanał jest cichy)           |
|      3 |          1 | aktualna głośność (0 oznacza, że ​​kanał jest wyłączony)             |

Pierwsze 4 kanały przeznaczone są na muzykę, reszta na efekty dźwiękowe.

Należy pamiętać, że indeks przebiegu 0 oznacza „użyj poprzedniego przebiegu”, więc indeks 0 nie może być użyty w selektorze.
Format każdego innego przebiegu:

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | liczba sampli                                                      |
|      2 |          2 | początek pętli                                                     |
|      4 |          2 | długość pętli                                                      |
|      6 |          1 | dostosuj wartość, od -8 do 7                                       |
|      7 |          1 | głośność, od 0 do 64                                               |
|      8 |      16376 | podpisane 8-bitowe próbki mono                                     |

Format efektów dźwiękowych i ścieżek muzycznych jest taki sam. Jedyną różnicą jest to, że ścieżki muzyczne mają 4 nuty w
każdym rzędzie, po jednej na każdy kanał, a rzędów jest 1024. W przypadku efektów dźwiękowych jest tylko jedna nuta i 64 rzędy.

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          1 | numer nuty, patrz definicja `NOTE_x`, od 0 do 96                   |
|      1 |          1 | indeks przebiegu, od 0 do 31                                       |
|      2 |          1 | typ efektu, od 0 do 255 (patrz [efekty nut])                       |
|      3 |          1 | parametr efektu                                                    |

Zliczanie nut przebiega następująco: 0 oznacza brak ustawionej nuty. Następnie następuje 8 oktaw, każda z 12 nutami, więc 1
równa się C-0, 12 to B-0 (w najniższej oktawie), 13 to C-1 (oktawa wyżej), a 14 to C#1 (C krzyżyk, półton wyżej). Na przykład
nuta D w 4. oktawie to 1 + 4\*12 + 2 = 51. B-7 to 96, najwyższa nuta w najwyższej oktawie. Masz również wbudowane definicje,
na przykład C-1 to `NOTE_C_1`, a C#1 to `NOTE_Cs1`, jeśli nie chcesz liczyć, możesz ich również użyć w swoim programie.

## Efekty nut

Dla uproszczenia MEG-4 używa tych samych kodów co plik Amiga MOD (w ten sposób zobaczysz to samo we wbudowanym edytorze, jak i
w zewnętrznym trackerze muzycznym), ale nie obsługuje ich wszystkich. Jak wspomniano wcześniej, kody te są reprezentowane przez
trzy liczby szesnastkowe, pierwsza to typ `t`, a dwie ostatnie to parametr, `xy` (lub `xx`). Typy `E1` do `ED` są wszystkie
przechowywane w bajcie typu, chociaż wygląda na to, że jeden z ich nibble'ów może należeć do parametru, ale tak nie jest.

| Efekt  | Kod  | Opis                                                       |
|--------|------|------------------------------------------------------------|
| ...    | 000  | Bez efektu                                                 |
| Arp    | 0xy  | Arpeggio, zagraj nutę, nuta + półton x i nuta + półton y   |
| Po/    | 1xx  | Portamento w górę, okres przesunięcia o x w górę           |
| Po\\   | 2xx  | Portamento w dół, okres slajdu x w dół                     |
| Ptn    | 3xx  | Ton portamento, przesuń okres do okresu x                  |
| Vib    | 4xy  | Vibrato, oscyluje wysokość dźwięku o y półtonów przy częstotliwości x |
| Ctv    | 5xy  | Kontynuuj ton portamento + głośność przesuwając o x w górę lub y w dół  |
| Cvv    | 6xy  | Kontynuuj Vibrato + przesuwanie głośności o x w górę lub o y w dół |
| Trm    | 7xy  | Tremolo, oscyluje głośność o amplitudę y przy częstotliwości x |
| Ofs    | 9xx  | Ustaw przesunięcie próbki na x \* 256                      |
| Vls    | Axy  | Przesuń głośność o x w górę lub o y w dół                  |
| Jmp    | Bxx  | Skok pozycji, ustaw wiersz na x \* 64                      |
| Vol    | Cxx  | Ustaw głośność na x                                        |
| Fp/    | E1x  | Drobny portamento w górę, zwiększ okres o x                |
| Fp\\   | E2x  | Delikatne portamento w dół, zmniejsz okres o x             |
| Svw    | E4x  | Ustaw kształt fali vibrato: 0 sinusoida, 1 piła, 2 kwadraty, 3 szum |
| Ftn    | E5x  | Ustaw dostrojenie, zmień strojenie o x (-8 do 7)           |
| Stw    | E7x  | Ustaw kształt fali tremolo: 0 sinusoida, 1 piła, 2 kwadraty, 3 szum |
| Rtg    | E9x  | Notatka o ponownym wyzwoleniu, próbka prądu wyzwalającego co x tyknięć |
| Fv/    | EAx  | Przesuń suwak głośności w górę, zwiększ o x                |
| Fv\\   | EBx  | Delikatny suwak głośności w dół, zmniejsz o x              |
| Cut    | ECx  | Wytnij notatkę w znacznikach x                             |
| Dly    | EDx  | Opóźnienie nuty w x tyknięciach                            |
| Tpr    | Fxx  | Ustaw liczbę znaczników na wiersz na x (domyślna liczba znaczników to 6) |

## Pamięć użytkownika

Adresy pamięci od 00000 do 2FFFF należą do MMIO, wszystko powyżej (zaczynając od 30000 lub `MEM_USER`) jest pamięcią użytkownika
dostępną bezpłatnie.

| Offset | Rozmiar    | Opis                                                               |
|--------|-----------:|--------------------------------------------------------------------|
|  30000 |          4 | (tylko BASIC) przesunięcie DATA                                    |
|  30004 |          4 | (tylko BASIC) bieżący licznik READ                                 |
|  30008 |          4 | (tylko BASIC) maksymalny READ, liczba DATA                         |

Następnie następują zmienne globalne, które zadeklarowałeś w swoim programie, a następnie stałe, takie jak literały stringów.
W przypadku BASIC-a, po nich następują rzeczywiste rekordy DATA.

Adresy pamięci powyżej zainicjowanych danych mogą być dynamicznie przydzielane i zwalniane w programie za pomocą wywołań [malloc]
i [free].

Na koniec stos, który jest na górze (zaczynając od C0000 lub `MEM_LIMIT`) i rośnie *w dół*. Zmienne lokalne programu (zadeklarowane
wewnątrz funkcji) znajdują się tutaj. Rozmiar stosu zawsze zmienia się w zależności od tego, która funkcja wywołuje inną funkcję
w programie.

Jeśli przypadkiem góra dynamicznie przydzielanych danych i dół stosu nałożą się na siebie, MEG-4 zgłosi błąd „Brak pamięci”.

## Formatowanie ciągów

Niektóre funkcje, [printf], [sprintf] i [trace] używają formatowania ciągów, można posłużyć się znakami specjalnymi, aby odwołać się do
argumentów i opisać sposób ich wyświetlania. Są to:

| Kod  | Opis                                                       |
|------|------------------------------------------------------------|
| `%%` | Znak `%`                                                   |
| `%d` | Następny parametr jako liczba dziesiętna                   |
| `%u` | Następny parametr jako liczba dziesiętna bez znaku         |
| `%x` | Następny parametr jako liczba szesnastkowa                 |
| `%o` | Następny parametr jako liczba ósemkowa                     |
| `%b` | Następny parametr jako liczba binarna                      |
| `%f` | Następny parametr jako liczba zmiennoprzecinkowa           |
| `%s` | Następny parametr jako ciąg znaków                         |
| `%c` | Następny parametr jako znak UTF-8                          |
| `%p` | Następny parametr jako adres (wskaźnik)                    |
| `\t` | Tab, napraw pozycję pionową przed kontynuowaniem           |
| `\n` | Rozpocznij nową linię                                      |

Możesz dodać wypełnienie, określając długość między `%` a kodem. Jeśli zaczyna się od `0`, wartość zostanie uzupełniona zerami,
w przeciwnym razie spacjami. Na przykład `%4d` uzupełni wartość po prawej stronie spacjami, a `%04x` zerami. `f` akceptuje liczbę
po kropce, która mówi o liczbie cyfr w części ułamkowej (do 8), np. `%.6f`.

## Przestrzeni 3D

W MEG-4 przestrzeń trójwymiarowa traktowana jest zgodnie z regułą prawej dłoni: +X jest po prawej stronie, +Y jest w górę, a +Z
jest skierowany w stronę patrzącego.

```
  +Y
   |
   |__ +X
  /
+Z
```

Każdy punkt musi być umieszczony w zakresie od -32767 do +32767. Sposób wyświetlania tego świata 3D na ekranie 2D zależy od
konfiguracji kamery (patrz adres [procesor graficzny] 0049E). Oczywiście musisz umieścić kamerę w świecie, używając
współrzędnych X, Y, Z. Następnie musisz określić, w którą stronę patrzy kamera, używając kąta pochylenia i odchylenia. Na koniec
musisz również określić, jaki obiektyw ma kamera, określając kąt pola widzenia. Ten ostatni powinien zwykle wynosić od 30
(bardzo wąski) do 180 stopni (jak ryby i ptaki). MEG-4 obsługuje do 127 stopni, ale jest pewien trik. Dodatnie wartości FOV będą
wyświetlane jako perspektywa (im dalej znajduje się obiekt, tym jest mniejszy), ale wartości ujemne są również obsługiwane, po
prostu za pomocą rzutowania ortograficznego (bez względu na odległość, rozmiar obiektu będzie taki sam). Perspektywa
wykorzystywana jest w grach FPS, natomiast rzutowanie ortograficzne preferowane jest głównie w grach strategicznych.

Możesz wyświetlić zestaw trójkątów (kompletny model 3D) za pomocą funkcji [mesh], co pozwoli na efektywne wyświetlanie. Ponieważ
modele prawdopodobnie mają współrzędne lokalne, narysowałoby to wszystkie modele jeden na drugim wokół origo. Tak więc, jeśli
chcesz wyświetlić wiele modeli w świecie, najpierw powinieneś je przetłumaczyć (umieścić) na współrzędne świata za pomocą [trns],
a następnie użyć przetłumaczonej chmury wierzchołków za pomocą [mesh] (przesuwanie i obracanie modelu nie zmieni trójkątów, tylko
ich współrzędne wierzchołków).

## Skróty klawiszowe Edytora Kodu

Dodatkowe skróty [klawiatura], których możesz również użyć podczas edycji źródła:

| Klawisz | Opis |
|------------------------------|--------------------------------------------------------------------------------------|
| <kbd>Ctrl</kbd>+<kbd>F</kbd> | Znajdź ciąg |
| <kbd>Ctrl</kbd>+<kbd>G</kbd> | Znajdź ponownie |
| <kbd>Ctrl</kbd>+<kbd>H</kbd> | Wyszukaj i zamień (w zaznaczonym tekście lub w całym źródle) |
| <kbd>Ctrl</kbd>+<kbd>J</kbd> | Przejdź do linii |
| <kbd>Ctrl</kbd>+<kbd>D</kbd> | Przejdź do definicji funkcji |
| <kbd>Ctrl</kbd>+<kbd>N</kbd> | Wyświetl listę zakładek |
| <kbd>Ctrl</kbd>+<kbd>B</kbd> | Przełącz zakładkę w bieżącym wierszu |
| <kbd>Ctrl</kbd>+<kbd>▴</kbd> | Przejdź do poprzedniej zakładki |
| <kbd>Ctrl</kbd>+<kbd>▾</kbd> | Przejdź do następnej zakładki |
| <kbd>Ctrl</kbd>+<kbd>,</kbd> | Zmniejsz wcięcie zaznaczenia |
| <kbd>Ctrl</kbd>+<kbd>.</kbd> | Zwiększ wcięcie zaznaczenia |
| <kbd>Home</kbd> | Przesuń kursor na początek wiersza |
| <kbd>End</kbd> | Przesuń kursor na koniec wiersza |
| <kbd>PgUp</kbd> | Przesuń kursor o 42 wiersze (jedną stronę) w górę |
| <kbd>PgDown</kbd> | Przesuń kursor o 42 wiersze (jedną stronę) w dół |
| <kbd>F1</kbd> | Jeśli kursor znajduje się na liście argumentów API, przejdź do wbudowanej strony pomocy funkcji |

Zobacz także menu, aby poznać alternatywne metody wprowadzania danych i ich skróty klawiaturowe.

# Konsola

## putc

```c
void putc(uint32_t chr)
```
<dt>Opis</dt><dd>
Wypisuje znak na konsoli.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| chr | Znak UTF-8 |
</dd>
<hr>
## printf

```c
void printf(str_t fmt, ...)
```
<dt>Opis</dt><dd>
Wyświetla tekst na konsoli.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| fmt | ciąg do wyświetlenia, [formatowanie ciągów] |
| ... | opcjonalne argumenty |
</dd>
<hr>
## getc

```c
uint32_t getc(void)
```
<dt>Opis</dt><dd>
Odczytuje znak z konsoli, blokuje program w przypadku braku danych wejściowych.
</dd>
<dt>Wartość zwracana</dt><dd>
Znak UTF-8 wprowadzony przez użytkownika.
</dd>
<dt>Zobacz także</dt><dd>
[popkey]
</dd>
<hr>
## gets

```c
str_t gets(void)
```
<dt>Opis</dt><dd>
Odczytuje ciąg znaków od użytkownika zakończony nową linią (nie zwraca nowej linii).
</dd>
<dt>Wartość zwracana</dt><dd>
Bajty odczytane w ciągu.
</dd>
<hr>
## trace

```c
void trace(str_t fmt, ...)
```
<dt>Opis</dt><dd>
Śledź wykonanie poprzez drukowanie do stdout. Działa tylko jeśli `meg4` został uruchomiony z flagą `-v` verbose.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| fmt | [formatowanie ciągów] |
| ... | opcjonalne argumenty |
</dd>
<hr>
## delay

```c
void delay(uint16_t msec)
```
<dt>Opis</dt><dd>
Opóźnia wykonanie programu.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| msec | opóźnienie w milisekundach |
</dd>
<hr>
## exit

```c
void exit(void)
```
<dt>Opis</dt><dd>
Wychodzi z programu.
</dd>

# Audio

## sfx

```c
void sfx(uint8_t sfx, uint8_t channel, uint8_t volume)
```
<dt>Opis</dt><dd>
Odtwarza efekt dźwiękowy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| sfx | indeks efektu dźwiękowego od 0 do 63 |
| channel | używany kanał, od 0 do 11 |
| volume | głośność, która ma być użyta, od 0 do 255, 0 wyłącza kanał |
</dd>
<hr>
## music

```c
void music(uint8_t track, uint16_t row, uint8_t volume)
```
<dt>Opis</dt><dd>
Odtwarza utwór muzyczny.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| track | indeks utworu muzycznego od 0 do 7 |
| row | wiersz, od którego należy rozpocząć odtwarzanie, od 0 do 1023 (maksymalna długość utworu) |
| volume | głośność, której należy użyć, od 0 do 255, 0 wyłącza muzykę |
</dd>

# GPIO

## gpio_rev

```c
uint32_t gpio_rev(void)
```
<dt>Opis</dt><dd>
Zapytaj o numer rewizji płyty GPIO. Zwraca 0, jeśli platforma nie obsługuje GPIO.
</dd>
<dt>Wartość zwracana</dt><dd>
Numer rewizji płyty lub 0, jeśli nie jest obsługiwana.
</dd>
<hr>
## gpio_get

```c
int gpio_get(uint8_t pin)
```
<dt>Opis</dt><dd>
Odczytaj wartość pinu GPIO.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| pin | fizyczny numer pinu od 1 do 40 |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca 1, jeśli pin jest w stanie wysokim, 0, jeśli jest w stanie niskim, -1 w przypadku błędu (pin GPIO nie jest obsługiwany).
</dd>
<dt>Zobacz także</dt><dd>
[gpio_set]
</dd>
<hr>
## gpio_set

```c
int gpio_set(uint8_t pin, int value)
```
<dt>Opis</dt><dd>
Zapisz wartość na pinie GPIO.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| pin | fizyczny numer pinu od 1 do 40 |
| value | 1, aby ustawić pin na wysoki, 0, aby ustawić pin na niski |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca 0 w przypadku powodzenia, -1 w przypadku błędu (pin GPIO nie jest obsługiwany).
</dd>
<dt>Zobacz także</dt><dd>
[gpio_get]
</dd>

# Grafika

## cls

```c
void cls(uint8_t palidx)
```
<dt>Opis</dt><dd>
Czyści cały ekran, resetuje przesunięcia wyświetlania i ustawia kolor tła konsoli.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
</dd>
<dt>Zobacz także</dt><dd>
[pget], [pset]
</dd>
<hr>
## cget

```c
uint32_t cget(uint16_t x, uint16_t y)
```
<dt>Opis</dt><dd>
Pobiera piksel o określonej współrzędnej i zwraca kolor RGBA.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| x | Współrzędna X w pikselach |
| y | Współrzędna Y w pikselach |
</dd>
<dt>Wartość zwracana</dt><dd>
Kolor wypełniony, z kanałami RGBA (czerwony znajduje się w najmniej znaczącym bajcie).
</dd>
<dt>Zobacz także</dt><dd>
[cls], [pget], [pset]
</dd>
<hr>
## pget

```c
uint8_t pget(uint16_t x, uint16_t y)
```
<dt>Opis</dt><dd>
Pobiera piksel o danej współrzędnej i zwraca jego indeks palety.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| x | Współrzędna X w pikselach |
| y | Współrzędna Y w pikselach |
</dd>
<dt>Wartość zwracana</dt><dd>
Kolor w indeksie palety od 0 do 255.
</dd>
<dt>Zobacz także</dt><dd>
[cls], [pset], [cget]
</dd>
<hr>
## pset

```c
void pset(uint8_t palidx, uint16_t x, uint16_t y)
```
<dt>Opis</dt><dd>
Rysuje piksel w określonym miejscu.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x | Współrzędna X w pikselach |
| y | Współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[cls], [pget]
</dd>
<hr>
## width

```c
uint16_t width(int8_t type, str_t str)
```
<dt>Opis</dt><dd>
Zwraca szerokość wyświetlanego tekstu w pikselach.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| type | typ czcionki, -4 do 4 |
| str | sznurek do pomiaru |
</dd>
<dt>Wartość zwracana</dt><dd>
Liczba pikseli wymagana do wyświetlenia tekstu.
</dd>
<dt>Zobacz także</dt><dd>
[text]
</dd>
<hr>
## text

```c
void text(uint8_t palidx, int16_t x, int16_t y, int8_t type, uint8_t shidx, uint8_t sha, str_t str)
```
<dt>Opis</dt><dd>
Drukuje tekst na ekranie.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x | Współrzędna X w pikselach |
| y | Współrzędna Y w pikselach |
| type | typ czcionki, -4 do -1 o stałej szerokości, 1 do 4 proporcjonalnie |
| shidx | kolor cienia, indeks palety od 0 do 255 |
| sha | alfa cienia, od 0 (całkowicie przezroczysty) do 255 (całkowicie nieprzezroczysty) |
| str | ciąg do wyświetlenia |
</dd>
<dt>Zobacz także</dt><dd>
[width]
</dd>
<hr>
## line

```c
void line(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Opis</dt><dd>
Rysuje wygładzoną linię.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | początkowa współrzędna X w pikselach |
| y0 | początkowa współrzędna Y w pikselach |
| x1 | końcowa współrzędna X w pikselach |
| y1 | końcowa współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[qbez], [cbez]
</dd>
<hr>
## qbez

```c
void qbez(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t cx, int16_t cy)
```
<dt>Opis</dt><dd>
Rysuje kwadratową krzywą Béziera.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | początkowa współrzędna X w pikselach |
| y0 | początkowa współrzędna Y w pikselach |
| x1 | końcowa współrzędna X w pikselach |
| y1 | końcowa współrzędna Y w pikselach |
| cx | współrzędna punktu kontrolnego X w pikselach |
| cy | współrzędna punktu kontrolnego Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[line], [cbez]
</dd>
<hr>
## cbez

```c
void cbez(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t cx0, int16_t cy0, int16_t cx1, int16_t cy1)
```
<dt>Opis</dt><dd>
Rysuje krzywą Béziera sześcienną.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | początkowa współrzędna X w pikselach |
| y0 | początkowa współrzędna Y w pikselach |
| x1 | końcowa współrzędna X w pikselach |
| y1 | końcowa współrzędna Y w pikselach |
| cx0 | pierwszy punkt kontrolny współrzędna X w pikselach |
| cy0 | pierwszy punkt kontrolny współrzędna Y w pikselach |
| cx1 | drugi punkt kontrolny współrzędna X w pikselach |
| cy1 | drugi punkt kontrolny współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[line], [qbez]
</dd>
<hr>
## tri

```c
void tri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dt>Opis</dt><dd>
Rysuje trójkąt.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | pierwsza współrzędna krawędzi X w pikselach |
| y0 | pierwsza współrzędna krawędzi Y w pikselach |
| x1 | druga współrzędna krawędzi X w pikselach |
| y1 | druga współrzędna krawędzi Y w pikselach |
| x2 | trzecia krawędź współrzędna X w pikselach |
| y2 | trzecia krawędź współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[ftri], [tri2d], [tri3d], [tritx], [mesh], [trns]
</dd>
<hr>
## ftri

```c
void ftri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dt>Opis</dt><dd>
Rysuje wypełniony trójkąt.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | pierwsza współrzędna krawędzi X w pikselach |
| y0 | pierwsza współrzędna krawędzi Y w pikselach |
| x1 | druga współrzędna krawędzi X w pikselach |
| y1 | druga współrzędna krawędzi Y w pikselach |
| x2 | trzecia krawędź współrzędna X w pikselach |
| y2 | trzecia krawędź współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[tri], [tri2d], [tri3d], [tritx], [mesh], [trns]
</dd>
<hr>
## tri2d

```c
void tri2d(uint8_t pi0, int16_t x0, int16_t y0,
    uint8_t pi1, int16_t x1, int16_t y1,
    uint8_t pi2, int16_t x2, int16_t y2)
```
<dt>Opis</dt><dd>
Rysuje wypełniony trójkąt z gradientami kolorów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| pi0 | pierwszy kolor krawędzi, indeks palety od 0 do 255 |
| x0 | pierwsza współrzędna krawędzi X w pikselach |
| y0 | pierwsza współrzędna krawędzi Y w pikselach |
| pi1 | drugi kolor krawędzi, indeks palety od 0 do 255 |
| x1 | druga współrzędna krawędzi X w pikselach |
| y1 | druga współrzędna krawędzi Y w pikselach |
| pi2 | trzeci kolor krawędzi, indeks palety od 0 do 255 |
| x2 | trzecia krawędź współrzędna X w pikselach |
| y2 | trzecia krawędź współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[tri], [ftri], [tri3d], [tritx], [mesh], [trns]
</dd>
<hr>
## tri3d

```c
void tri3d(uint8_t pi0, int16_t x0, int16_t y0, int16_t z0,
    uint8_t pi1, int16_t x1, int16_t y1, int16_t z1,
    uint8_t pi2, int16_t x2, int16_t y2, int16_t z2)
```
<dt>Opis</dt><dd>
Rysuje wypełniony trójkąt z gradientami kolorów w [przestrzeni 3D].
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| pi0 | pierwszy kolor krawędzi, indeks palety od 0 do 255 |
| x0 | pierwsza współrzędna krawędzi X w przestrzeni |
| y0 | pierwsza współrzędna krawędzi Y w przestrzeni |
| z0 | pierwsza współrzędna krawędzi Z w przestrzeni |
| pi1 | drugi kolor krawędzi, indeks palety od 0 do 255 |
| x1 | druga krawędź współrzędna X w przestrzeni |
| y1 | druga krawędź współrzędna Y w przestrzeni |
| z1 | druga krawędź współrzędna Z w przestrzeni |
| pi2 | trzeci kolor krawędzi, indeks palety od 0 do 255 |
| x2 | trzecia krawędź współrzędna X w przestrzeni |
| y2 | trzecia krawędź współrzędna Y w przestrzeni |
| z2 | trzecia krawędź współrzędna Z w przestrzeni |
</dd>
<dt>Zobacz także</dt><dd>
[tri], [ftri], [tri2d], [tritx], [mesh], [trns]
</dd>
<hr>
## tritx

```c
void tritx(uint8_t u0, uint8_t v0, int16_t x0, int16_t y0, int16_t z0,
    uint8_t u1, uint8_t v1, int16_t x1, int16_t y1, int16_t z1,
    uint8_t u2, uint8_t v2, int16_t x2, int16_t y2, int16_t z2)
```
<dt>Opis</dt><dd>
Rysuje teksturowany trójkąt w [przestrzeni 3D].
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| u0 | pierwsza tekstura krawędzi współrzędna X od 0 do 255 |
| v0 | pierwsza tekstura krawędzi współrzędna Y od 0 do 255 |
| x0 | pierwsza współrzędna krawędzi X w przestrzeni |
| y0 | pierwsza współrzędna krawędzi Y w przestrzeni |
| z0 | pierwsza współrzędna krawędzi Z w przestrzeni |
| u1 | druga tekstura krawędzi współrzędna X od 0 do 255 |
| v1 | druga tekstura krawędzi współrzędna Y od 0 do 255 |
| x1 | druga krawędź współrzędna X w przestrzeni |
| y1 | druga krawędź współrzędna Y w przestrzeni |
| z1 | druga krawędź współrzędna Z w przestrzeni |
| u2 | trzecia tekstura krawędzi współrzędna X od 0 do 255 |
| v2 | trzecia tekstura krawędzi współrzędna Y od 0 do 255 |
| x2 | trzecia krawędź współrzędna X w przestrzeni |
| y2 | trzecia krawędź współrzędna Y w przestrzeni |
| z2 | trzecia krawędź współrzędna Z w przestrzeni |
</dd>
<dt>Zobacz także</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [mesh], [trns]
</dd>
<hr>
## mesh

```c
void mesh(addr_t verts, addr_t uvs, uint16_t numtri, addr_t tris)
```
<dt>Opis</dt><dd>
Rysuje siatkę zbudowaną z trójkątów w [przestrzeni 3D], używając indeksów wierzchołków i współrzędnych tekstury (lub palety).
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| verts | adres tablicy wierzchołków, 3 x 2 bajty każdy, X, Y, Z |
| uvs | adres tablicy UVs (jeśli 0, to używana jest paleta), 2 x 1 bajt każdy, tekstura X, Y |
| numtri | liczba trójkątów |
| tris | adres tablicy trójkątów z indeksami, 6 x 1 bajt każdy, vi1, ui1/pi1, vi2, ui2/pi2, vi3, ui3/pi3 |
</dd>
<dt>Zobacz także</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [tritx], [trns]
</dd>
<hr>
## rect

```c
void rect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Opis</dt><dd>
Rysuje prostokąt.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | lewy górny róg współrzędna X w pikselach |
| y0 | lewy górny róg współrzędna Y w pikselach |
| x1 | prawy dolny róg współrzędna X w pikselach |
| y1 | prawy dolny róg współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[frect]
</dd>
<hr>
## frect

```c
void frect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Opis</dt><dd>
Rysuje wypełniony prostokąt.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | lewy górny róg współrzędna X w pikselach |
| y0 | lewy górny róg współrzędna Y w pikselach |
| x1 | prawy dolny róg współrzędna X w pikselach |
| y1 | prawy dolny róg współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[rect]
</dd>
<hr>
## circ

```c
void circ(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dt>Opis</dt><dd>
Rysuje okrąg.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x | współrzędna środka X w pikselach |
| y | współrzędna środka Y w pikselach |
| r | promień w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[fcirc], [ellip], [fellip]
</dd>
<hr>
## fcirc

```c
void fcirc(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dt>Opis</dt><dd>
Rysuje wypełnione koło.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x | współrzędna środka X w pikselach |
| y | współrzędna środka Y w pikselach |
| r | promień w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[circ], [ellip], [fellip]
</dd>
<hr>
## ellip

```c
void ellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Opis</dt><dd>
Rysuje elipsę.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | lewy górny róg współrzędna X w pikselach |
| y0 | lewy górny róg współrzędna Y w pikselach |
| x1 | prawy dolny róg współrzędna X w pikselach |
| y1 | prawy dolny róg współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[circ], [fcirc], [fellip]
</dd>
<hr>
## fellip

```c
void fellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dt>Opis</dt><dd>
Rysuje wypełnioną elipsę.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
| x0 | lewy górny róg współrzędna X w pikselach |
| y0 | lewy górny róg współrzędna Y w pikselach |
| x1 | prawy dolny róg współrzędna X w pikselach |
| y1 | prawy dolny róg współrzędna Y w pikselach |
</dd>
<dt>Zobacz także</dt><dd>
[circ], [fcirc], [ellip]
</dd>
<hr>
## move

```c
void move(int16_t x, int16_t y, uint16_t deg)
```
<dt>Opis</dt><dd>
Przesuwa żółwia do wskazanej pozycji na ekranie lub w labiryncie.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| x | Współrzędna X w pikselach (lub 1/128 kafelków z [maze]) |
| y | Współrzędna Y w pikselach |
| deg | kierunek w stopniach, od 0 do 359, 0 oznacza górę ekranu, 90 oznacza prawo |
</dd>
<dt>Zobacz także</dt><dd>
[left], [right], [up], [down], [color], [forw], [back]
</dd>
<hr>
## left

```c
void left(uint16_t deg)
```
<dt>Opis</dt><dd>
Skręca żółwia w lewo.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| deg | zmiana w stopniach od 0 do 359 |
</dd>
<dt>Zobacz także</dt><dd>
[move], [right], [up], [down], [color], [forw], [back]
</dd>
<hr>
## right

```c
void right(uint16_t deg)
```
<dt>Opis</dt><dd>
Skręca żółwia w prawo.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| deg | zmiana w stopniach od 0 do 359 |
</dd>
<dt>Zobacz także</dt><dd>
[move], [left], [up], [down], [color], [forw], [back]
</dd>
<hr>
## up

```c
void up(void)
```
<dt>Opis</dt><dd>
Podnosi ogon żółwia. Żółw będzie się poruszał bez rysowania linii.
</dd>
<dt>Zobacz także</dt><dd>
[move], [left], [right], [down], [color], [forw], [back]
</dd>
<hr>
## down

```c
void down(void)
```
<dt>Opis</dt><dd>
Opuszcza ogon żółwia. Żółw będzie się poruszał, rysując linię (patrz [color]).
</dd>
<dt>Zobacz także</dt><dd>
[move], [left], [right], [up], [color], [forw], [back]
</dd>
<hr>
## color

```c
void color(uint8_t palidx)
```
<dt>Opis</dt><dd>
Ustawia kolor farby żółwia.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| palidx | kolor, indeks palety od 0 do 255 |
</dd>
<dt>Zobacz także</dt><dd>
[move], [left], [right], [up], [down], [forw], [back]
</dd>
<hr>
## forw

```c
void forw(uint16_t cnt)
```
<dt>Opis</dt><dd>
Przesuwa żółwia do przodu.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| cnt | ilość w pikselach (lub 1/128 kafelków z [maze]) |
</dd>
<dt>Zobacz także</dt><dd>
[move], [left], [right], [up], [down], [color], [back]
</dd>
<hr>
## back

```c
void back(uint16_t cnt)
```
<dt>Opis</dt><dd>
Przesuwa żółwia do tyłu.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| cnt | ilość w pikselach (lub 1/128 kafelków z [maze]) |
</dd>
<dt>Zobacz także</dt><dd>
[move], [left], [right], [up], [down], [color], [forw]
</dd>
<hr>
## spr

```c
void spr(int16_t x, int16_t y, uint16_t sprite, uint8_t sw, uint8_t sh, int8_t scale, uint8_t type)
```
<dt>Opis</dt><dd>
Wyświetla duszka lub wiele sąsiadujących duszków.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| x | Współrzędna X w pikselach |
| y | Współrzędna Y w pikselach |
| sprite | identyfikator sprite'a, od 0 do 1023 |
| sw | liczba sprite'ów poziomych |
| sh | liczba pionowych duszków |
| scale | skala od -3 do 4 |
| type | transformacja, 0=norm., 1=90°, 2=180°, 3=270°, 4=odwróc. w pionie, 5=odwróc.+90°, 6=odwróc. w poziomie, 7=odwróc.+270° |
</dd>
<dt>Zobacz także</dt><dd>
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
<dt>Opis</dt><dd>
Wyświetla okno dialogowe przy użyciu sprite'ów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| x | Współrzędna X w pikselach |
| y | Współrzędna Y w pikselach |
| w | szerokość dialogu w pikselach |
| h | wysokość dialogu w pikselach |
| scale | skala od -3 do 4 |
| tl | lewy górny róg id sprite'a |
| tm | górny środkowy sprite id |
| tr | id sprite'a w prawym górnym rogu |
| ml | środkowy lewy sprite id |
| bg | identyfikator sprite'a tła |
| mr | środkowy prawy sprite id |
| bl | dolny lewy róg id sprite'a |
| bm | dolny środkowy sprite id |
| br | dolny prawy róg id sprite'a |
</dd>
<dt>Zobacz także</dt><dd>
[spr], [stext]
</dd>
<hr>
## stext

```c
void stext(int16_t x, int16_t y, uint16_t fs, uint16_t fu, uint8_t sw, uint8_t sh, int8_t scale, str_t str)
```
<dt>Opis</dt><dd>
Wyświetla tekst na ekranie za pomocą sprite'ów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| x | Współrzędna X w pikselach |
| y | Współrzędna Y w pikselach |
| fs | pierwszy identyfikator sprite'a, który będzie używany do wyświetlania |
| fu | pierwszy UNICODE (najmniejszy znak) w ciągu |
| sw | liczba sprite'ów poziomych |
| sh | liczba pionowych duszków |
| scale | skala od -3 do 4 |
| str | ciąg UTF-8 zakończony zerem |
</dd>
<dt>Zobacz także</dt><dd>
[spr], [dlg]
</dd>
<hr>
## remap

```c
void remap(addr_t replace)
```
<dt>Opis</dt><dd>
Zastępuje kafelki na mapie. Można użyć do animowania kafelków na mapie.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| replace | tablica 256 identyfikatorów sprite'ów |
</dd>
<dt>Zobacz także</dt><dd>
[mget], [mset], [map], [maze]
</dd>
<hr>
## mget

```c
uint16_t mget(uint16_t mx, uint16_t my)
```
<dt>Opis</dt><dd>
Zwraca jeden kafelek na mapie.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| mx | Współrzędna X na mapie w kafelkach |
| my | Współrzędna Y na mapie w kafelkach |
</dd>
<dt>Wartość zwracana</dt><dd>
Identyfikator duszka kafelka o podanych współrzędnych.
</dd>
<dt>Zobacz także</dt><dd>
[remap], [mset], [map], [maze]
</dd>
<hr>
## mset

```c
void mset(uint16_t mx, uint16_t my, uint16_t sprite)
```
<dt>Opis</dt><dd>
Ustawia jeden kafelek na mapie.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| mx | Współrzędna X na mapie w kafelkach |
| my | Współrzędna Y na mapie w kafelkach |
| sprite | identyfikator sprite'a, od 0 do 1023 |
</dd>
<dt>Zobacz także</dt><dd>
[remap], [mget], [map], [maze]
</dd>
<hr>
## map

```c
void map(int16_t x, int16_t y, uint16_t mx, uint16_t my, uint16_t mw, uint16_t mh, int8_t scale)
```
<dt>Opis</dt><dd>
Rysuje (część) mapy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| x | Współrzędna X w pikselach |
| y | Współrzędna Y w pikselach |
| mx | Współrzędna X na mapie w kafelkach |
| my | Współrzędna Y na mapie w kafelkach |
| mw | liczba poziomych płytek |
| mh | liczba pionowych płytek |
| scale | skala od -3 do 4 |
</dd>
<dt>Zobacz także</dt><dd>
[remap], [mget], [mset], [maze]
</dd>
<hr>
## maze

```c
void maze(uint16_t mx, uint16_t my, uint16_t mw, uint16_t mh, uint8_t scale,
    uint16_t sky, uint16_t grd, uint16_t door, uint16_t wall, uint16_t obj, uint8_t numnpc, addr_t npc)
```
<dt>Opis</dt><dd>
Wyświetla mapę jako labirynt 3D, wykorzystując pozycję żółwia.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| mx | Współrzędna X na mapie w kafelkach |
| my | Współrzędna Y na mapie w kafelkach |
| mw | liczba poziomych płytek |
| mh | liczba pionowych płytek |
| scale | liczba duszków na kafelku w potędze liczby dwa, od 0 do 3 |
| sky | indeks kafelków nieba |
| grd | indeks płytek gruntowych |
| door | indeks pierwszej płytki drzwiowej |
| wall | pierwszy indeks płytek ściennych |
| obj | pierwszy obiekt indeks kafelka |
| numnpc | liczba rekordów NPC |
| npc | tablica uint32_t zawierająca numnpc razy x,y,indeks kafelka triplety |
</dd>
<dt>Zobacz także</dt><dd>
[remap], [mget], [mset], [map]
</dd>

# Wejście

## getpad

```c
int getpad(int pad, int btn)
```
<dt>Opis</dt><dd>
Pobiera aktualny stan przycisku gamepada.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| pad | indeks gamepada, od 0 do 3 |
| btn | jeden z przycisków [gamepad], `BTN_` |
</dd>
<dt>Wartość zwracana</dt><dd>
Zero, jeśli nie naciśnięto, wartość różna od zera, jeśli naciśnięto.
</dd>
<dt>Zobacz także</dt><dd>
[prspad], [relpad], [getbtn], [getclk], [getkey]
</dd>
<hr>
## prspad

```c
int prspad(int pad, int btn)
```
<dt>Opis</dt><dd>
Zwraca wartość true, jeżeli przycisk gamepada został naciśnięty od ostatniego wywołania.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| pad | indeks gamepada, od 0 do 3 |
| btn | jeden z przycisków [gamepad], `BTN_` |
</dd>
<dt>Wartość zwracana</dt><dd>
Zero, jeśli nie naciśnięto, wartość różna od zera, jeśli naciśnięto.
</dd>
<dt>Zobacz także</dt><dd>
[relpad], [getpad], [getbtn], [getclk], [getkey]
</dd>
<hr>
## relpad

```c
int relpad(int pad, int btn)
```
<dt>Opis</dt><dd>
Zwraca wartość true, jeżeli przycisk gamepada został zwolniony od ostatniego wywołania.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| pad | indeks gamepada, od 0 do 3 |
| btn | jeden z przycisków [gamepad], `BTN_` |
</dd>
<dt>Wartość zwracana</dt><dd>
Zero jeśli nie został wydany, wartość różna od zera jeśli został wydany.
</dd>
<dt>Zobacz także</dt><dd>
[prspad], [getpad], [getbtn], [getclk], [getkey]
</dd>
<hr>
## getbtn

```c
int getbtn(int btn)
```
<dt>Opis</dt><dd>
Pobiera stan przycisków myszy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| btn | jeden z przycisków [wskaźnik]a, `BTN_` lub `SCR_` |
</dd>
<dt>Wartość zwracana</dt><dd>
Zero, jeśli nie naciśnięto, wartość różna od zera, jeśli naciśnięto.
</dd>
<dt>Zobacz także</dt><dd>
[prspad], [relpad], [getpad], [getclk], [getkey]
</dd>
<hr>
## getclk

```c
int getclk(int btn)
```
<dt>Opis</dt><dd>
Powoduje kliknięcie przycisku myszy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| btn | jeden z przycisków [wskaźnik]a, `BTN_` |
</dd>
<dt>Wartość zwracana</dt><dd>
Zero jeśli nie kliknięto, wartość różna od zera jeśli kliknięto.
</dd>
<dt>Zobacz także</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getkey]
</dd>
<hr>
## getkey

```c
int getkey(int sc)
```
<dt>Opis</dt><dd>
Pobiera aktualny stan klucza.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| sc | kod skanowania, od 1 do 144, patrz [klawiatura] |
</dd>
<dt>Wartość zwracana</dt><dd>
Zero, jeśli nie naciśnięto, wartość różna od zera, jeśli naciśnięto.
</dd>
<dt>Zobacz także</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getclk]
</dd>
<hr>
## popkey

```c
uint32_t popkey(void)
```
<dt>Opis</dt><dd>
Usuń klawisz UTF-8 z kolejki klawiatury. Zobacz [klawiatura] i dla wersji blokującej [getc].
</dd>
<dt>Wartość zwracana</dt><dd>
Reprezentacja klucza w formacie UTF-8 lub 0, jeśli kolejka jest pusta (bez blokowania).
</dd>
<dt>Zobacz także</dt><dd>
[pendkey], [lenkey], [speckey], [getc]
</dd>
<hr>
## pendkey

```c
int pendkey(void)
```
<dt>Opis</dt><dd>
Zwraca wartość true, jeśli w kolejce znajduje się klucz oczekujący (ale pozostawia klucz w kolejce, nie usuwa go).
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca wartość 1, jeśli w kolejce znajdują się oczekujące klucze.
</dd>
<dt>Zobacz także</dt><dd>
[popkey], [lenkey], [speckey]
</dd>
<hr>
## lenkey

```c
int lenkey(uint32_t key)
```
<dt>Opis</dt><dd>
Zwraca długość klucza UTF-8 w bajtach.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| key | klucz, wyskoczył z kolejki |
</dd>
<dt>Wartość zwracana</dt><dd>
Długość reprezentacji UTF-8 w bajtach.
</dd>
<dt>Zobacz także</dt><dd>
[popkey], [pendkey], [speckey]
</dd>
<hr>
## speckey

```c
int speckey(uint32_t key)
```
<dt>Opis</dt><dd>
Zwraca wartość true, jeśli klucz jest kluczem specjalnym.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| key | klucz, wyskoczył z kolejki |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca wartość 1, jeśli jest to klucz specjalny lub 0, jeśli jest to klucz drukowalny.
</dd>
<dt>Zobacz także</dt><dd>
[popkey], [pendkey], [lenkey]
</dd>

# Matematyka

## rand

```c
uint32_t rand(void)
```
<dt>Opis</dt><dd>
Uzyskaj losowość. Użyj `%` modulo, aby zmniejszyć wartość, na przykład `1 + rand() % 6` zwraca losowość między 1 a 6, jak kostka
do gry.
</dd>
<dt>Wartość zwracana</dt><dd>
Liczba losowa pomiędzy 0 i 2^^32^^-1 (4294967295).
</dd>
<dt>Zobacz także</dt><dd>
[rnd]
</dd>
<hr>
## rnd

```c
float rnd(void)
```
<dt>Opis</dt><dd>
Pobierz losowo. Tak samo jak [rand], ale zwraca liczbę zmiennoprzecinkową.
</dd>
<dt>Wartość zwracana</dt><dd>
Liczba losowa z zakresu od 0.0 do 1.0.
</dd>
<dt>Zobacz także</dt><dd>
[rand]
</dd>
<hr>
## float

```c
float float(int val)
```
<dt>Opis</dt><dd>
Zwraca wartość zmiennoprzecinkową odpowiadającą liczbie całkowitej.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Wartość zmiennoprzecinkowa.
</dd>
<dt>Zobacz także</dt><dd>
[int]
</dd>
<hr>
## int

```c
int int(float val)
```
<dt>Opis</dt><dd>
Zwraca wartość całkowitą odpowiadającą liczbie zmiennoprzecinkowej.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Liczba całkowita wartości.
</dd>
<dt>Zobacz także</dt><dd>
[float]
</dd>
<hr>
## floor

```c
float floor(float val)
```
<dt>Opis</dt><dd>
Zwraca największą liczbę całkowitą nie większą niż wartość.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Piętro wartości.
</dd>
<dt>Zobacz także</dt><dd>
[ceil]
</dd>
<hr>
## ceil

```c
float ceil(float val)
```
<dt>Opis</dt><dd>
Zwraca najmniejszą liczbę całkowitą nie mniejszą niż wartość.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Pułap wartości.
</dd>
<dt>Zobacz także</dt><dd>
[floor]
</dd>
<hr>
## sgn

```c
float sgn(float val)
```
<dt>Opis</dt><dd>
Zwraca znak wartości.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Albo 1.0 albo -1.0.
</dd>
<dt>Zobacz także</dt><dd>
[abs]
</dd>
<hr>
## abs

```c
float abs(float val)
```
<dt>Opis</dt><dd>
Zwraca wartość bezwzględną.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Albo wartość albo -wartość, zawsze dodatnia.
</dd>
<dt>Zobacz także</dt><dd>
[sgn]
</dd>
<hr>
## exp

```c
float exp(float val)
```
<dt>Opis</dt><dd>
Zwraca wykładnik wartości, tj. podstawę logarytmu naturalnego podniesioną do potęgi równej wartości.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca e^^val^^.
</dd>
<dt>Zobacz także</dt><dd>
[log], [pow]
</dd>
<hr>
## log

```c
float log(float val)
```
<dt>Opis</dt><dd>
Zwraca logarytm naturalny wartości.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca logarytm naturalny wartości.
</dd>
<dt>Zobacz także</dt><dd>
[exp]
</dd>
<hr>
## pow

```c
float pow(float val, float exp)
```
<dt>Opis</dt><dd>
Zwraca wartość podniesioną do potęgi wykładnika. To jest powolna operacja, staraj się jej unikać.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
| exp | wyraziciel |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca val^^exp^^.
</dd>
<dt>Zobacz także</dt><dd>
[exp], [sqrt], [rsqrt]
</dd>
<hr>
## sqrt

```c
float sqrt(float val)
```
<dt>Opis</dt><dd>
Zwraca pierwiastek kwadratowy wartości. To jest powolna operacja, staraj się jej unikać.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Pierwiastek kwadratowy wartości.
</dd>
<dt>Zobacz także</dt><dd>
[pow], [rsqrt]
</dd>
<hr>
## rsqrt

```c
float rsqrt(float val)
```
<dt>Opis</dt><dd>
Zwraca odwrotność pierwiastka kwadratowego wartości (`1 / sqrt(val)`). Używa szybkiej metody Johna Carmacka.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Odwrotność pierwiastka kwadratowego wartości.
</dd>
<dt>Zobacz także</dt><dd>
[pow], [sqrt]
</dd>
<hr>
## clamp

```c
float clamp(float val, float minv, float maxv)
```
<dt>Opis</dt><dd>
Zaciska wartość pomiędzy limitami.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość |
| minv | minimalna wartość |
| maxv | maksymalna wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Wartość zacięta.
</dd>
<dt>Zobacz także</dt><dd>
[clampv2], [clampv3], [clampv4]
</dd>
<hr>
## lerp

```c
float lerp(float a, float b, float t)
```
<dt>Opis</dt><dd>
Interpolacja liniowa dwóch liczb.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | pierwsza liczba zmiennoprzecinkowa |
| b | druga liczba zmiennoprzecinkowa |
| t | wartość interpolacji pomiędzy 0.0 i 1.0 |
</dd>
<dt>Zobacz także</dt><dd>
[lerpv2], [lerpv3], [lerpv4], [lerpq], [slerpq]
</dd>
<hr>
## pi

```c
float pi(void)
```
<dt>Opis</dt><dd>
Zwraca π jako liczbę zmiennoprzecinkową.
</dd>
<dt>Wartość zwracana</dt><dd>
Wartość 3.14159265358979323846.
</dd>
<hr>
## cos

```c
float cos(uint16_t deg)
```
<dt>Opis</dt><dd>
Zwraca cosinus.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| deg | stopień, od 0 do 359, 0 to góra, 90 to prawo |
</dd>
<dt>Wartość zwracana</dt><dd>
Cosinus stopnia, od -1.0 do 1.0.
</dd>
<dt>Zobacz także</dt><dd>
[sin], [tan], [acos], [asin], [atan], [atan2]
</dd>
<hr>
## sin

```c
float sin(uint16_t deg)
```
<dt>Opis</dt><dd>
Zwraca sinus.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| deg | stopień, od 0 do 359, 0 to góra, 90 to prawo |
</dd>
<dt>Wartość zwracana</dt><dd>
Sinus stopnia, od -1.0 do 1.0.
</dd>
<dt>Zobacz także</dt><dd>
[cos], [tan], [acos], [asin], [atan], [atan2]
</dd>
<hr>
## tan

```c
float tan(uint16_t deg)
```
<dt>Opis</dt><dd>
Zwraca tangens.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| deg | stopień, od 0 do 359, 0 to góra, 90 to prawo |
</dd>
<dt>Wartość zwracana</dt><dd>
Tangens stopnia, pomiędzy -1.0 a 1.0.
</dd>
<dt>Zobacz także</dt><dd>
[cos], [sin], [acos], [asin], [atan], [atan2]
</dd>
<hr>
## acos

```c
uint16_t acos(float val)
```
<dt>Opis</dt><dd>
Zwraca arcus cosinus.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość, -1.0 do 1.0 |
</dd>
<dt>Wartość zwracana</dt><dd>
Arcus cosinus w stopniach, od 0 do 359, gdzie 0 jest w górę, a 90 w prawo.
</dd>
<dt>Zobacz także</dt><dd>
[cos], [sin], [tan], [asin], [atan], [atan2]
</dd>
<hr>
## asin

```c
uint16_t asin(float val)
```
<dt>Opis</dt><dd>
Zwraca łuk sinus.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość, -1.0 do 1.0 |
</dd>
<dt>Wartość zwracana</dt><dd>
Arcus sinus w stopniach, od 0 do 359, gdzie 0 jest w górę, a 90 w prawo.
</dd>
<dt>Zobacz także</dt><dd>
[cos], [sin], [tan], [acos], [atan], [atan2]
</dd>
<hr>
## atan

```c
uint16_t atan(float val)
```
<dt>Opis</dt><dd>
Zwraca tangens łuku.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| val | wartość, -1.0 do 1.0 |
</dd>
<dt>Wartość zwracana</dt><dd>
Tangens łuku w stopniach, od 0 do 359, gdzie 0 jest w górę, a 90 w prawo.
</dd>
<dt>Zobacz także</dt><dd>
[cos], [sin], [tan], [acos], [asin], [atan2]
</dd>
<hr>
## atan2

```c
uint16_t atan2(float y, float x)
```
<dt>Opis</dt><dd>
Zwraca arcus tangens dla y/x, używając znaków y i x do określenia ćwiartki.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| y | Współrzędna Y |
| x | Współrzędna X |
</dd>
<dt>Wartość zwracana</dt><dd>
Tangens łuku w stopniach, od 0 do 359, gdzie 0 jest w górę, a 90 w prawo.
</dd>
<dt>Zobacz także</dt><dd>
[cos], [sin], [tan], [acos], [asin]
</dd>
<hr>
## dotv2

```c
float dotv2(addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Oblicza iloczyn skalarny dwóch wektorów o dwóch elementach.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres dwóch statków |
| b | adres dwóch statków |
</dd>
<dt>Wartość zwracana</dt><dd>
Iloczyn skalarny wektorów.
</dd>
<dt>Zobacz także</dt><dd>
[lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## lenv2

```c
float lenv2(addr_t a)
```
<dt>Opis</dt><dd>
Oblicza długość wektora z dwoma elementami. Jest to powolne, staraj się tego unikać (zobacz [normv2]).
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres dwóch statków |
</dd>
<dt>Wartość zwracana</dt><dd>
Długość wektora.
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## scalev2

```c
void scalev2(addr_t a, float s)
```
<dt>Opis</dt><dd>
Skaluje wektor składający się z dwóch elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres dwóch statków |
| s | wartość skalująca |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## negv2

```c
void negv2(addr_t a)
```
<dt>Opis</dt><dd>
Neguje wektor składający się z dwóch elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres dwóch statków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [scalev2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## addv2

```c
void addv2(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Dodaje wektory składające się z dwóch elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres dwóch statków |
| a | adres dwóch statków |
| b | adres dwóch statków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## subv2

```c
void subv2(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Odejmuje wektory dwuelementowe.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres dwóch statków |
| a | adres dwóch statków |
| b | adres dwóch statków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## mulv2

```c
void mulv2(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Mnoży wektory przez dwa elementy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres dwóch statków |
| a | adres dwóch statków |
| b | adres dwóch statków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## divv2

```c
void divv2(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Dzieli wektory dwuelementowe.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres dwóch statków |
| a | adres dwóch statków |
| b | adres dwóch statków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [clampv2], [lerpv2], [normv2]
</dd>
<hr>
## clampv2

```c
void clampv2(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dt>Opis</dt><dd>
Zaciska wektory dwuelementowe.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres dwóch statków |
| v | adres dwóch statków, input |
| minv | adres dwóch statków, minimum |
| maxv | adres dwóch statków, maximum |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [lerpv2], [normv2]
</dd>
<hr>
## lerpv2

```c
void lerpv2(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Opis</dt><dd>
Interpolacja liniowa wektorów dwuelementowych.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres dwóch statków |
| a | adres dwóch statków |
| b | adres dwóch statków |
| t | wartość interpolacji pomiędzy 0.0 i 1.0 |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [normv2]
</dd>
<hr>
## normv2

```c
void normv2(addr_t a)
```
<dt>Opis</dt><dd>
Normalizuje wektor składający się z dwóch elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres dwóch statków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2]
</dd>
<hr>
## dotv3

```c
float dotv3(addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Oblicza iloczyn skalarny dwóch wektorów trzyelementowych.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres trzech pływaków |
| b | adres trzech pływaków |
</dd>
<dt>Wartość zwracana</dt><dd>
Iloczyn skalarny wektorów.
</dd>
<dt>Zobacz także</dt><dd>
[lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## lenv3

```c
float lenv3(addr_t a)
```
<dt>Opis</dt><dd>
Oblicza długość wektora z trzema elementami. Jest to powolne, staraj się tego unikać (zobacz [normv3]).
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres trzech pływaków |
</dd>
<dt>Wartość zwracana</dt><dd>
Długość wektora.
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## scalev3

```c
void scalev3(addr_t a, float s)
```
<dt>Opis</dt><dd>
Skaluje wektor składający się z trzech elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres trzech pływaków |
| s | wartość skalująca |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## negv3

```c
void negv3(addr_t a)
```
<dt>Opis</dt><dd>
Neguje wektor składający się z trzech elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## addv3

```c
void addv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Dodaje wektory składające się z trzech elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| a | adres trzech pływaków |
| b | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## subv3

```c
void subv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Odejmuje wektory składające się z trzech elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| a | adres trzech pływaków |
| b | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## mulv3

```c
void mulv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Mnoży wektory przez trzy elementy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| a | adres trzech pływaków |
| b | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## divv3

```c
void divv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Dzieli wektory o trzech elementach.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| a | adres trzech pływaków |
| b | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## crossv3

```c
void crossv3(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Oblicza iloczyn wektorowy wektorów trójelementowych.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| a | adres trzech pływaków |
| b | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [clampv3], [lerpv3], [normv3]
</dd>
<hr>
## clampv3

```c
void clampv3(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dt>Opis</dt><dd>
Zaciska wektory o trzech elementach.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| v | adres trzech pływaków, input |
| minv | adres trzech pływaków, minimum |
| maxv | adres trzech pływaków, maximum |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [lerpv3], [normv3]
</dd>
<hr>
## lerpv3

```c
void lerpv3(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Opis</dt><dd>
Interpolacja liniowa wektorów o trzech elementach.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| a | adres trzech pływaków |
| b | adres trzech pływaków |
| t | wartość interpolacji pomiędzy 0.0 i 1.0 |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [normv3]
</dd>
<hr>
## normv3

```c
void normv3(addr_t a)
```
<dt>Opis</dt><dd>
Normalizuje wektor składający się z trzech elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3]
</dd>
<hr>
## dotv4

```c
float dotv4(addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Oblicza iloczyn skalarny dwóch wektorów czteroelementowych.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Wartość zwracana</dt><dd>
Iloczyn skalarny wektorów.
</dd>
<dt>Zobacz także</dt><dd>
[lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## lenv4

```c
float lenv4(addr_t a)
```
<dt>Opis</dt><dd>
Oblicza długość wektora z czterema elementami. To jest wolne, staraj się tego unikać (zobacz [normv4]).
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
</dd>
<dt>Wartość zwracana</dt><dd>
Długość wektora.
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## scalev4

```c
void scalev4(addr_t a, float s)
```
<dt>Opis</dt><dd>
Skaluje wektor o czterech elementach.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
| s | wartość skalująca |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## negv4

```c
void negv4(addr_t a)
```
<dt>Opis</dt><dd>
Neguje wektor składający się z czterech elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [scalev4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## addv4

```c
void addv4(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Dodaje wektory składające się z czterech elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [negv4], [scalev4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## subv4

```c
void subv4(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Odejmuje wektory czteroelementowe.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## mulv4

```c
void mulv4(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Mnoży wektory przez cztery elementy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## divv4

```c
void divv4(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Dzieli wektory czteroelementowe.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [clampv4], [lerpv4], [normv4]
</dd>
<hr>
## clampv4

```c
void clampv4(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dt>Opis</dt><dd>
Zaciska wektory czteroelementowe.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| v | adres czterech pływaków, input |
| minv | adres czterech pływaków, minimum |
| maxv | adres czterech pływaków, maximum |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [lerpv4], [normv4]
</dd>
<hr>
## lerpv4

```c
void lerpv4(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Opis</dt><dd>
Interpolacja liniowa wektorów czteroelementowych.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
| t | wartość interpolacji pomiędzy 0.0 i 1.0 |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [normv4]
</dd>
<hr>
## normv4

```c
void normv4(addr_t a)
```
<dt>Opis</dt><dd>
Normalizuje wektor składający się z czterech elementów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4]
</dd>
<hr>
## idq

```c
void idq(addr_t a)
```
<dt>Opis</dt><dd>
Ładuje kwaternion tożsamościowy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## eulerq

```c
void eulerq(addr_t dst, uint16_t pitch, uint16_t yaw, uint16_t roll)
```
<dt>Opis</dt><dd>
Ładuje kwaternion za pomocą kątów Eulera.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| pitch | obrót wokół osi X w stopniach, od 0 do 359 |
| yaw | obrót wokół osi Y w stopniach, od 0 do 359 |
| roll | obrót wokół osi Z w stopniach, od 0 do 359 |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## dotq

```c
float dotq(addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Oblicza iloczyn skalarny kwaternionu.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Wartość zwracana</dt><dd>
Iloczyn skalarny kwaternionu.
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## lenq

```c
float lenq(addr_t a)
```
<dt>Opis</dt><dd>
Oblicza długość kwaternionu.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
</dd>
<dt>Wartość zwracana</dt><dd>
Długość kwaternionu.
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## scaleq

```c
void scaleq(addr_t a, float s)
```
<dt>Opis</dt><dd>
Skala kwaternionu.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
| s | wartość skalująca |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## negq

```c
void negq(addr_t a)
```
<dt>Opis</dt><dd>
Neguje kwaternion.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## addq

```c
void addq(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Dodaje kwaterniony.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## subq

```c
void subq(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Odejmuje kwaterniony.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## mulq

```c
void mulq(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Mnoży kwaterniony.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [rotq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## rotq

```c
void rotq(addr_t dst, addr_t q, addr_t v)
```
<dt>Opis</dt><dd>
Obraca wektor składający się z trzech elementów o kwaternion.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| q | adres czterech pływaków |
| v | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [lerpq], [slerpq], [normq]
</dd>
<hr>
## lerpq

```c
void lerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Opis</dt><dd>
Interpolacja liniowa dwóch kwaternionów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
| t | wartość interpolacji pomiędzy 0.0 i 1.0 |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [slerpq], [normq]
</dd>
<hr>
## slerpq

```c
void slerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dt>Opis</dt><dd>
Interpolacja sferyczna kwaternionu.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| a | adres czterech pływaków |
| b | adres czterech pływaków |
| t | wartość interpolacji pomiędzy 0.0 i 1.0 |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [normq]
</dd>
<hr>
## normq

```c
void normq(addr_t a)
```
<dt>Opis</dt><dd>
Normalizuje kwaternion.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq]
</dd>
<hr>
## idm4

```c
void idm4(addr_t a)
```
<dt>Opis</dt><dd>
Ładuje macierz jednostkową 4 x 4.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres 16 pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## trsm4

```c
void trsm4(addr_t dst, addr_t t, addr_t r, addr_t s)
```
<dt>Opis</dt><dd>
Tworzy macierz 4 x 4 z translacją, obrotem i skalowaniem.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres 16 pływaków, destination matrix |
| t | adres trzech pływaków, translation vector |
| r | adres czterech pływaków, rotation quaternion |
| s | adres trzech pływaków, scaling vector |
</dd>
<dt>Zobacz także</dt><dd>
[idm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## detm4

```c
float detm4(addr_t a)
```
<dt>Opis</dt><dd>
Zwraca wyznacznik macierzy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| a | adres 16 pływaków |
</dd>
<dt>Wartość zwracana</dt><dd>
Wyznacznik macierzy.
</dd>
<dt>Zobacz także</dt><dd>
[idm4], [trsm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## addm4

```c
void addm4(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Dodaje macierze.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres 16 pływaków |
| a | adres 16 pływaków |
| b | adres 16 pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idm4], [trsm4], [detm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## subm4

```c
void subm4(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Odejmuje macierze.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres 16 pływaków |
| a | adres 16 pływaków |
| b | adres 16 pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## mulm4

```c
void mulm4(addr_t dst, addr_t a, addr_t b)
```
<dt>Opis</dt><dd>
Mnoży macierze.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres 16 pływaków |
| a | adres 16 pływaków |
| b | adres 16 pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## mulm4v3

```c
void mulm4v3(addr_t dst, addr_t m, addr_t v)
```
<dt>Opis</dt><dd>
Mnoży wektor składający się z trzech elementów przez macierz.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres trzech pływaków |
| m | adres 16 pływaków |
| v | adres trzech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v4], [invm4], [trpm4]
</dd>
<hr>
## mulm4v4

```c
void mulm4v4(addr_t dst, addr_t m, addr_t v)
```
<dt>Opis</dt><dd>
Mnoży wektor składający się z czterech elementów przez macierz.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres czterech pływaków |
| m | adres 16 pływaków |
| v | adres czterech pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [invm4], [trpm4]
</dd>
<hr>
## invm4

```c
void invm4(addr_t dst, addr_t a)
```
<dt>Opis</dt><dd>
Oblicza macierz odwrotną.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres 16 pływaków |
| a | adres 16 pływaków |
</dd>
<dt>Zobacz także</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [trpm4]
</dd>
<hr>
## trpm4

```c
void trpm4(addr_t dst, addr_t a)
```
<dt>Opis</dt><dd>
Transpozycja macierzy.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres 16 pływaków |
| a | adres 16 pływaków |
</dd>
<dt>Zobacz także</dt><dd>
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
<dt>Opis</dt><dd>
Przetłumacz chmurę wierzchołków, czyli umieść model 3D w [przestrzeni 3D].
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | tablica wierzchołków docelowych, 3 x 2 bajty każda, X, Y, Z |
| src | tablica wierzchołków źródłowych, 3 x 2 bajty każda, X, Y, Z |
| num | liczba trójek współrzędnych wierzchołków w tablicy |
| x | współrzędna świata X, od -32767 do 32767 |
| y | współrzędna świata Y, od -32767 do 32767 |
| z | współrzędna świata Z, od -32767 do 32767 |
| pitch | obrót wokół osi X w stopniach, od 0 do 359 |
| yaw | obrót wokół osi Y w stopniach, od 0 do 359 |
| roll | obrót wokół osi Z w stopniach, od 0 do 359 |
| scale | skala, użyj 1.0, aby zachować oryginalny rozmiar |
</dd>
<dt>Zobacz także</dt><dd>
[mesh]
</dd>

# Pamięć

## inb

```c
uint8_t inb(addr_t src)
```
<dt>Opis</dt><dd>
Odczytano jeden bajt z pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| src | adres, 0x00000 do 0xBFFFF |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca wartość pod danym adresem.
</dd>
<hr>
## inw

```c
uint16_t inw(addr_t src)
```
<dt>Opis</dt><dd>
Odczytać jedno słowo (word, dwa bajty) z pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| src | adres, 0x00000 do 0xBFFFE |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca wartość pod danym adresem.
</dd>
<hr>
## ini

```c
uint32_t ini(addr_t src)
```
<dt>Opis</dt><dd>
Odczyt liczby całkowitej (int, cztery bajty) z pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| src | adres, 0x00000 do 0xBFFFC |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca wartość pod danym adresem.
</dd>
<hr>
## outb

```c
void outb(addr_t dst, uint8_t value)
```
<dt>Opis</dt><dd>
Zapisz jeden bajt w pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres, 0x00000 do 0xBFFFF |
| value | wartość do ustawienia, od 0 do 255 |
</dd>
<hr>
## outw

```c
void outw(addr_t dst, uint16_t value)
```
<dt>Opis</dt><dd>
Zapisz słowo (word, dwa bajty) w pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres, 0x00000 do 0xBFFFE |
| value | wartość do ustawienia, od 0 do 65535 |
</dd>
<hr>
## outi

```c
void outi(addr_t dst, uint32_t value)
```
<dt>Opis</dt><dd>
Wypisz liczbę całkowitą (int, cztery bajty) do pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres, 0x00000 do 0xBFFFC |
| value | wartość do ustawienia, od 0 do 4294967295 |
</dd>
<hr>
## memsave

```c
int memsave(uint8_t overlay, addr_t src, uint32_t size)
```
<dt>Opis</dt><dd>
Zapisuje obszar pamięci do nałożenia.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| overlay | indeks nakładki do zapisu, od 0 do 255 |
| src | przesunięcie pamięci do zapisania, 0x00000 do 0xBFFFF |
| size | liczba bajtów do zapisania |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca 1 w przypadku powodzenia, 0 w przypadku błędu.
</dd>
<dt>Zobacz także</dt><dd>
[memload]
</dd>
<hr>
## memload

```c
int memload(addr_t dst, uint8_t overlay, uint32_t maxsize)
```
<dt>Opis</dt><dd>
Ładuje nakładkę do określonego obszaru pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | przesunięcie pamięci do załadowania, 0x00000 do 0xBFFFF |
| overlay | indeks nakładki do odczytu, od 0 do 255 |
| maxsize | maksymalna liczba bajtów do załadowania |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca liczbę faktycznie załadowanych bajtów.
</dd>
<dt>Zobacz także</dt><dd>
[memsave]
</dd>
<hr>
## memcpy

```c
void memcpy(addr_t dst, addr_t src, uint32_t len)
```
<dt>Opis</dt><dd>
Kopiuj obszary pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres docelowy, 0x00000 do 0xBFFFF |
| src | adres źródłowy, 0x00000 do 0xBFFFF |
| len | liczba bajtów do skopiowania |
</dd>
<hr>
## memset

```c
void memset(addr_t dst, uint8_t value, uint32_t len)
```
<dt>Opis</dt><dd>
Ustaw region pamięci na daną wartość.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres docelowy, 0x00000 do 0xBFFFF |
| value | wartość do ustawienia, od 0 do 255 |
| len | liczba bajtów do ustawienia |
</dd>
<hr>
## memcmp

```c
int memcmp(addr_t addr0, addr_t addr1, uint32_t len)
```
<dt>Opis</dt><dd>
Porównaj obszary pamięci.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| addr0 | pierwszy adres, 0x00000 do 0xBFFFF |
| addr1 | drugi adres, 0x00000 do 0xBFFFF |
| len | liczba bajtów do porównania |
</dd>
<dt>Wartość zwracana</dt><dd>
Zwraca różnicę, 0 jeśli dwa obszary pamięci są zgodne.
</dd>
<hr>
## deflate

```c
int deflate(addr_t dst, addr_t src, uint32_t len)
```
<dt>Opis</dt><dd>
Kompresja bufora przy użyciu RFC1950 deflate (zlib) opisanego.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres docelowy, 0x30000 do 0xBFFFF |
| src | adres źródłowy, 0x30000 do 0xBFFFF |
| len | liczba bajtów do skompresowania |
</dd>
<dt>Wartość zwracana</dt><dd>
0 lub wartość ujemna w przypadku błędu; w przeciwnym wypadku długość skompresowanego bufora i skompresowanych danych w dst.
</dd>
<dt>Zobacz także</dt><dd>
[inflate]
</dd>
<hr>
## inflate

```c
int inflate(addr_t dst, addr_t src, uint32_t len)
```
<dt>Opis</dt><dd>
Rozpakuj bufor przy użyciu skompresowanych danych RFC1950 deflate (zlib).
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| dst | adres docelowy, 0x30000 do 0xBFFFF |
| src | adres źródłowy, 0x30000 do 0xBFFFF |
| len | liczba skompresowanych bajtów |
</dd>
<dt>Wartość zwracana</dt><dd>
0 lub wartość ujemna w przypadku błędu; w przeciwnym wypadku długość nieskompresowanego bufora i nieskompresowanych danych w dst.
</dd>
<dt>Zobacz także</dt><dd>
[deflate]
</dd>
<hr>
## time

```c
float time(void)
```
<dt>Opis</dt><dd>
Zwraca liczbę impulsów od włączenia zasilania.
</dd>
<dt>Wartość zwracana</dt><dd>
Czas w milisekundach, który upłynął od włączenia zasilania.
</dd>
<dt>Zobacz także</dt><dd>
[now]
</dd>
<hr>
## now

```c
uint32_t now(void)
```
<dt>Opis</dt><dd>
Zwraca znacznik czasu UNIX. Sprawdź bajt w przesunięciu 0000C, aby zobaczyć, czy nie jest przepełniony.
</dd>
<dt>Wartość zwracana</dt><dd>
Czas w sekundach, który upłynął od północy 1 stycznia 1970 r. czasu Greenwich.
</dd>
<dt>Zobacz także</dt><dd>
[time]
</dd>
<hr>
## atoi

```c
int atoi(str_t src)
```
<dt>Opis</dt><dd>
Konwertuje ciąg dziesiętny ASCII na liczbę całkowitą.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| src | adres ciągu, 0x00000 do 0xBFFFF |
</dd>
<dt>Wartość zwracana</dt><dd>
Wartość liczbowa ciągu.
</dd>
<dt>Zobacz także</dt><dd>
[itoa], [str], [val]
</dd>
<hr>
## itoa

```c
str_t itoa(int value)
```
<dt>Opis</dt><dd>
Konwertuje liczbę całkowitą na ciąg dziesiętny ASCII.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| value | wartość od -2147483648 do 2147483647 |
</dd>
<dt>Wartość zwracana</dt><dd>
Przekonwertowany ciąg znaków.
</dd>
<dt>Zobacz także</dt><dd>
[atoi], [str], [val]
</dd>
<hr>
## val

```c
float val(str_t src)
```
<dt>Opis</dt><dd>
Konwertuje ciąg dziesiętny ASCII na liczbę zmiennoprzecinkową.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| src | adres ciągu, 0x00000 do 0xBFFFF |
</dd>
<dt>Wartość zwracana</dt><dd>
Wartość liczbowa ciągu.
</dd>
<dt>Zobacz także</dt><dd>
[itoa], [atoi], [str]
</dd>
<hr>
## str

```c
str_t str(float value)
```
<dt>Opis</dt><dd>
Konwertuje liczbę zmiennoprzecinkową na ciąg dziesiętny ASCII.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| value | wartość |
</dd>
<dt>Wartość zwracana</dt><dd>
Przekonwertowany ciąg znaków.
</dd>
<dt>Zobacz także</dt><dd>
[atoi], [itoa], [val]
</dd>
<hr>
## sprintf

```c
str_t sprintf(str_t fmt, ...)
```
<dt>Opis</dt><dd>
Zwraca zakończony zerem ciąg UTF-8 utworzony przy użyciu formatu i argumentów.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| fmt | [formatowanie ciągów] |
| ... | opcjonalne argumenty |
</dd>
<dt>Wartość zwracana</dt><dd>
Skonstruowany ciąg.
</dd>
<hr>
## strlen

```c
int strlen(str_t src)
```
<dt>Opis</dt><dd>
Zwraca liczbę bajtów w ciągu (bez końcowego zera).
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| src | adres ciągu, 0x00000 do 0xBFFFF |
</dd>
<dt>Wartość zwracana</dt><dd>
Liczba bajtów w ciągu.
</dd>
<dt>Zobacz także</dt><dd>
[mblen]
</dd>
<hr>
## mblen

```c
int mblen(str_t src)
```
<dt>Opis</dt><dd>
Zwraca liczbę wielobajtowych znaków UTF-8 w ciągu (bez końcowego zera).
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| src | adres ciągu, 0x00000 do 0xBFFFF |
</dd>
<dt>Wartość zwracana</dt><dd>
Liczba znaków w ciągu.
</dd>
<dt>Zobacz także</dt><dd>
[strlen]
</dd>
<hr>
## malloc

```c
addr_t malloc(uint32_t size)
```
<dt>Opis</dt><dd>
Dynamicznie przydziela pamięć użytkownikowi.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| size | liczba bajtów do przydzielenia |
</dd>
<dt>Wartość zwracana</dt><dd>
Adres nowego przydzielonego bufora lub NULL w przypadku błędu.
</dd>
<dt>Zobacz także</dt><dd>
[realloc], [free]
</dd>
<hr>
## realloc

```c
addr_t realloc(addr_t addr, uint32_t size)
```
<dt>Opis</dt><dd>
Zmień rozmiar wcześniej przydzielonego bufora.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| addr | adres przydzielonego bufora |
| size | liczba bajtów do zmiany rozmiaru |
</dd>
<dt>Wartość zwracana</dt><dd>
Adres nowego przydzielonego bufora lub NULL w przypadku błędu.
</dd>
<dt>Zobacz także</dt><dd>
[malloc], [free]
</dd>
<hr>
## free

```c
int free(addr_t addr)
```
<dt>Opis</dt><dd>
Zwalnia dynamicznie przydzieloną pamięć użytkownika.
</dd>
<dt>Parametry</dt><dd>
| Argument | Opis |
| addr | adres przydzielonego bufora |
</dd>
<dt>Wartość zwracana</dt><dd>
1 w przypadku powodzenia, 0 w przypadku błędu.
</dd>
<dt>Zobacz także</dt><dd>
[malloc], [realloc]
</dd>
