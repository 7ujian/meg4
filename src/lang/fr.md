# Carte mémoire

## Divers

Toutes les valeurs sont en Little Endian, donc le plus petit chiffre est stocké sur la plus petite adresse.

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  00000 |          1 | MEG-4 version majeure du firmware                                  |
|  00001 |          1 | MEG-4 version mineure du firmware                                  |
|  00002 |          1 | MEG-4 version bugfix du firmware                                   |
|  00003 |          1 | compteur de performances, temps non dépensé en 1/1000ème de seconde |
|  00004 |          4 | nombre de ticks de 1/1000ème de seconde depuis la mise sous tension |
|  00008 |          8 | horodatage unix UTC                                                |
|  00010 |          2 | langue actuelle                                                    |

Le compteur de performances affiche le temps non dépensé lors de la génération de la dernière image. Si la valeur est nulle ou
négative, cela signifie à quel point votre fonction loop() a dépassé son délai disponible.

## Pointeur

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  00012 |          2 | état des boutons du pointeur (voir [getbtn] et [getclk])           |
|  00014 |          2 | index des sprites de pointeur                                      |
|  00016 |          2 | coordonnée X du pointeur                                           |
|  00018 |          2 | coordonnée Y du pointeur                                           |

Les boutons du pointeur sont les suivants:

| Define  | Bitmask   | Description                                                        |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | Bouton gauche de la souris                                         |
| `BTN_M` |         2 | Bouton central de la souris                                        |
| `BTN_R` |         4 | Bouton droit de la souris                                          |
| `SCR_U` |         8 | Bouton de défilement vers le haut                                  |
| `SCR_D` |        16 | Bouton de défilement vers le bas                                   |
| `SCR_L` |        32 | Bouton de défilement vers la gauche                                |
| `SCR_R` |        64 | Bouton de défilement vers la droite                                |

Les bits supérieurs de l'index du sprite du pointeur sont utilisés pour les points chauds: bits 13 à 15 du point chaud Y,
bits 10 à 12 du point chaud X, bits 0 à 9 du sprite. Il existe des curseurs intégrés prédéfinis:

| Define       | Valeur    | Description                                                   |
|--------------|----------:|---------------------------------------------------------------|
| `PTR_NORM`   |      03fb | Pointeur normal (flèche)                                      |
| `PTR_TEXT`   |      03fc | Pointeur de texte                                             |
| `PTR_HAND`   |      0bfd | Pointeur de lien                                              |
| `PTR_ERR`    |      93fe | Pointeur d'erreur                                             |
| `PTR_NONE`   |      ffff | Le pointeur est caché                                         |

## Clavier

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0001A |          1 | pied de file d'attente du clavier                                  |
|  0001B |          1 | tête de file d'attente du clavier                                  |
|  0001C |         64 | file d'attente du clavier, 16 éléments, chacun 4 octets (voir [popkey]) |
|  0005C |         18 | les touches du clavier sont enfoncées par les scancodes (voir [getkey]) |

Les clés extraites de la file d'attente sont représentées en UTF-8. Certaines séquences UTF-8 non valides représentent des clés
spéciales (non imprimables), par exemple:

| CodeClé | Description                                     |
|---------|-------------------------------------------------|
| `\x8`   | Le caractère 8, touche <kbd>←Backspace</kbd>    |
| `\x9`   | Le caractère 9, touche <kbd>Tab</kbd>           |
| `\n`    | Le caractère 10, touche <kbd>⏎Enter</kbd>       |
| `\x1b`  | Le caractère 27, touche<kbd>Esc</kbd>           |
| `Del`   | Le touche <kbd>Del</kbd>                        |
| `Up`    | La touche fléchée du curseur <kbd>▴</kbd>       |
| `Down`  | La touche fléchée du curseur <kbd>▾</kbd>       |
| `Left`  | La touche fléchée du curseur <kbd>◂</kbd>       |
| `Rght`  | La touche fléchée du curseur <kbd>▸</kbd>       |
| `Cut`   | Le touche Cut (ou <kbd>Ctrl</kbd>+<kbd>X</kbd>) |
| `Cpy`   | Le touche Copy (ou <kbd>Ctrl</kbd>+<kbd>C</kbd>) |
| `Pst`   | Le touche Paste (ou <kbd>Ctrl</kbd>+<kbd>V</kbd>) |

Les scancodes sont les suivants:

| ScanCode | Compenser | Bitmask | Define          |
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

## Manette de jeu

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0006E |          2 | seuil du joystick de la manette de jeu (8000 par défaut)           |
|  00070 |          8 | manette de jeu principale - mappages de scancode du clavier (voir [clavier]) |
|  00078 |          4 | 4 boutons de manettes de jeu enfoncés (voir [getpad])              |

Les boutons de la manette de jeu sont les suivants:

| Define  | Bitmask   | Description                                                        |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | Le bouton `◁` ou le joystick gauche                               |
| `BTN_U` |         2 | Le bouton `△` ou le joystick vers le haut                         |
| `BTN_R` |         4 | Le bouton `▷` ou le joystick droit                                |
| `BTN_D` |         8 | Le bouton `▽` ou le joystick vers le bas                          |
| `BTN_A` |        16 | Le bouton `Ⓐ`                                                     |
| `BTN_B` |        32 | Le bouton `Ⓑ`                                                     |
| `BTN_X` |        64 | Le bouton `Ⓧ`                                                     |
| `BTN_Y` |       128 | Le bouton `Ⓨ`                                                     |

La séquence `△△▽▽◁▷◁▷ⒷⒶ` fait appuyer sur la "touche" `KEY_CHEAT`.

## Processeur Graphique

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0007E |          1 | Bits supérieurs UNICODE pour le mappage des glyphes de police      |
|  0007F |          1 | sélecteur de banque de sprites pour la carte                       |
|  00080 |       1024 | palette, 256 couleurs, chaque entrée 4 octets, RGBA                |
|  00480 |          2 | x0, début de la zone de recadrage X en pixels (pour toutes les fonctions) |
|  00482 |          2 | x1, fin de la zone de recadrage X en pixels                        |
|  00484 |          2 | y0, début de la zone de recadrage Y en pixels                      |
|  00486 |          2 | y1, fin de la zone de recadrage Y en pixels                        |
|  00488 |          2 | affichage du décalage vram X en pixels ou 0xffff                   |
|  0048A |          2 | affichage du décalage vram Y en pixels ou 0xffff                   |
|  0048C |          1 | stylo tortue vers le bas drapeau (voir [up], [down])               |
|  0048D |          1 | couleur du stylo tortue, indice de palette 0 à 255 (voir [color])  |
|  0048E |          2 | direction de la tortue en degrés, 0 à 359 (voir [left], [right])   |
|  00490 |          2 | décalage X de la tortue en pixels (voir [move])                    |
|  00492 |          2 | décalage Y de la tortue en pixels                                  |
|  00494 |          2 | vitesse de marche du labyrinthe en tuiles 1/128 (voir [maze])      |
|  00496 |          2 | vitesse de rotation du labyrinthe en degrés (1 à 90)               |
|  00498 |          1 | couleur de premier plan de la console, indice de palette 0 à 255 (voir [printf]) |
|  00499 |          1 | couleur de fond de la console, indice de palette 0 à 255           |
|  0049A |          2 | décalage de la console X en pixels                                 |
|  0049C |          2 | décalage de la console Y en pixels                                 |
|  0049E |          2 | décalage de la caméra X dans [espace 3D] (voir [tri3d], [tritx], [mesh]) |
|  004A0 |          2 | décalage de la caméra Y                                            |
|  004A2 |          2 | décalage de la caméra Z                                            |
|  004A4 |          2 | direction de la caméra, inclinaison (0 vers le haut, 90 vers l'avant) |
|  004A6 |          2 | direction de la caméra, lacet (0 à gauche, 90 vers l'avant)        |
|  004A8 |          1 | champ de vision de la caméra en angles (45, le négatif donne l'orthographe) |
|  004AA |          2 | position de la source lumineuse décalage X (voir [tri3d], [tritx], [mesh]) |
|  004AC |          2 | position de la source lumineuse décalage Y                         |
|  004AE |          2 | position de la source lumineuse décalage Z                         |
|  00600 |      64000 | carte, 320 x 200 indices de sprite (voir [map] et [maze])          |
|  10000 |      65536 | sprites, 256 x 256 indices de palette, 1024 8 x 8 pixels (voir [spr]) |
|  28000 |       2048 | fenêtre pour 4096 glyphes de police (voir 0007E, [width] et [text]) |

## Processeur de Signal Numérique

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0007C |          1 | sélecteur de banque de formes d'onde (1 à 31)                      |
|  0007D |          1 | sélecteur de banque de piste de musique (0 à 7)                    |
|  004BA |          1 | tempo actuel (en ticks par ligne, lecture seule)                   |
|  004BB |          1 | piste en cours de lecture (lecture seule)                          |
|  004BC |          2 | ligne en cours de lecture (lecture seule)                          |
|  004BE |          2 | nombre total de lignes dans la piste actuelle (lecture seule)      |
|  004C0 |         64 | 16 registres d'état de canal, chacun 4 octets (lecture seule)      |
|  00500 |        256 | 64 effets sonores, chacun 4 octets                                 |
|  20000 |      16384 | fenêtre pour les échantillons de forme d'onde (voir 0007C)         |
|  24000 |      16384 | fenêtre pour les motifs musicaux (voir 0007D)                      |

Les registres d'état DSP sont tous en lecture seule et, pour chaque canal, ils ressemblent à:

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | position actuelle dans la forme d'onde en cours de lecture         |
|      2 |          1 | forme d'onde actuelle (1 à 31, 0 si le canal est silencieux)       |
|      3 |          1 | volume actuel (0 signifie que la chaîne est éteinte)               |

Les 4 premiers canaux sont destinés à la musique, le reste aux effets sonores.

Notez que l'indice de forme d'onde 0 signifie "utiliser la forme d'onde précédente", donc l'indice 0 ne peut pas être utilisé
dans le sélecteur. Le format de chaque autre forme d'onde:

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | nombre d'échantillons                                              |
|      2 |          2 | début de boucle                                                    |
|      4 |          2 | longueur de boucle                                                 |
|      6 |          1 | valeur de réglage précis, -8 à 7                                   |
|      7 |          1 | volume, 0 à 64                                                     |
|      8 |      16376 | échantillons mono 8 bits signés                                    |

Le format des effets sonores et des pistes musicales est le même, la seule différence est que les pistes musicales ont 4 notes par
rangée, une pour chaque canal, et il y a 1024 lignes; tandis que pour les effets sonores, il n'y a qu'une seule note et 64 lignes.

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          1 | numéro de note, voir les définitions de `NOTE_x`, 0 à 96           |
|      1 |          1 | indice de forme d'onde, 0 à 31                                     |
|      2 |          1 | type d'effet, 0 à 255 (voir [effets sonores])                      |
|      3 |          1 | paramètre d'effet                                                  |

Le comptage des notes se déroule comme suit : 0 signifie aucune note définie. Suivi de 8 octaves, chacune avec 12 notes, donc 1
est égal à C-0, 12 est B-0 (sur l'octave la plus basse), 13 est C-1 (une octave plus haut) et 14 est C#1 (Do dièse, demi-ton plus
haut). Par exemple, la note D sur la 4ème octave serait 1 + 4\*12 + 2 = 51. Le B-7 est 96, la note la plus haute de l'octave la
plus élevée. Vous avez également des définitions intégrées, par exemple C-1 est `NOTE_C_1` et C#1 est `NOTE_Cs1`, si vous ne
voulez pas compter, vous pouvez également les utiliser dans votre programme.

## Effets sonores

Pour plus de simplicité, MEG-4 utilise les mêmes codes que le fichier Amiga MOD (de cette façon, vous verrez la même chose dans
l'éditeur intégré ainsi que dans un tracker musical tiers), mais il ne les prend pas tous en charge. Comme indiqué précédemment,
ces codes sont représentés par trois nombres hexadécimaux, le premier étant le type `t` et les deux derniers le paramètre `xy`
(ou `xx`). Les types `E1` à `ED` sont tous stockés dans l'octet de type, bien qu'il semble que l'un de leurs quartets puisse
appartenir au paramètre, mais ce n'est pas le cas.

| Effet  | Code | Description                                                |
|--------|------|------------------------------------------------------------|
| ...    | 000  | Aucun effet                                                |
| Arp    | 0xy  | Arpeggio, jouer une note, une note+x demi-ton et une note+y demi-ton |
| Po/    | 1xx  | Portamento haut, faites glisser la période de x vers le haut |
| Po\\   | 2xx  | Portamento bas, faites glisser la période de x vers le bas |
| Ptn    | 3xx  | Portamento de tonalité, faites glisser la période vers la période x |
| Vib    | 4xy  | Vibrato, faire osciller la hauteur de y demi-tons à x fréquence |
| Ctv    | 5xy  | Continuer Tonalité portamento + volume glisser de x vers le haut ou y vers le bas |
| Cvv    | 6xy  | Continuer Vibrato + volume glisser de x vers le haut ou de y vers le bas |
| Trm    | 7xy  | Trémolo, faire osciller le volume selon l'amplitude y à la fréquence x |
| Ofs    | 9xx  | Définir le décalage de l'échantillon sur x \* 256          |
| Vls    | Axy  | Faire glisser le volume de x vers le haut ou de y vers le bas |
| Jmp    | Bxx  | Saut de position, définissez la ligne sur x \* 64          |
| Vol    | Cxx  | Régler le volume sur x                                     |
| Fp/    | E1x  | Portamento précis vers le haut, augmentation de la période de x |
| Fp\\   | E2x  | Portamento précis vers le bas, diminuer la période de x    |
| Svw    | E4x  | Définir la forme d'onde du vibrato, 0 sinusoïdal, 1 scie, 2 carrés, 3 bruits |
| Ftn    | E5x  | Réglez un réglage précis, modifiez le réglage par x (-8 à 7) |
| Stw    | E7x  | Définir la forme d'onde du trémolo, 0 sinusoïdal, 1 scie, 2 carrés, 3 bruits |
| Rtg    | E9x  | Redéclencher la note, déclencher l'échantillon actuel tous les x ticks |
| Fv/    | EAx  | Le volume précis glisse vers le haut, augmente de x        |
| Fv\\   | EBx  | Le volume précis glisse vers le bas, diminué de x          |
| Cut    | ECx  | Couper la note après x ticks                               |
| Dly    | EDx  | Retard note x ticks                                        |
| Tpr    | Fxx  | Définissez le nombre de ticks par ligne sur x (par défaut est 6) |

## Mémoire utilisateur

Les adresses mémoire de 00000 à 2FFFF appartiennent au MMIO, tout ce qui précède (à partir de 30000 ou `MEM_USER`) est une
mémoire utilisateur librement utilisable.

| Compenser | Taille  | Description                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  30000 |          4 | (BASIC uniquement) décalage de DATA                                |
|  30004 |          4 | (BASIC uniquement) compteur READ actuel                            |
|  30008 |          4 | (BASIC uniquement) READ maximum, nombre de DATA                    |

Viennent ensuite les variables globales que vous avez déclarées dans votre programme, suivies des constantes, comme les chaînes
littérales. Dans le cas du BASIC, ceci est suivi par les enregistrements DATA réels.

Les adresses mémoire au-dessus des données initialisées peuvent être allouées et libérées dynamiquement dans votre programme via
les appels [malloc] et [free].

Enfin la pile, qui est en haut (en commençant à partir de C0000 ou `MEM_LIMIT`) et en augmentant *vers le bas*. Les variables locales
de votre programme (que vous avez déclarées dans une fonction) vont ici. La taille de la pile change toujours en fonction de la
fonction qui appelle quelle autre fonction de votre programme.

Si, par hasard, le haut des données allouées dynamiquement et le bas de la pile se chevauchent, alors MEG-4 renvoie une erreur
"Mémoire insuffisante".

## Formater la chaîne

Certaines fonctions, [printf], [sprintf] et [trace] utilisent une chaîne de format qui peut contenir des caractères spéciaux pour
référencer les arguments et décrire comment les afficher. Ceux-ci sont:

| Code | Description                                                |
|------|------------------------------------------------------------|
| `%%` | Le caractère `%`                                           |
| `%d` | Paramètre suivant sous forme de nombre décimal             |
| `%u` | Paramètre suivant sous forme de nombre décimal non signé   |
| `%x` | Paramètre suivant sous forme de nombre hexadécimal         |
| `%o` | Paramètre suivant sous forme de nombre octal               |
| `%b` | Paramètre suivant sous forme de nombre binaire             |
| `%f` | Paramètre suivant sous forme de nombre à virgule flottante |
| `%s` | Paramètre suivant sous forme de chaîne                     |
| `%c` | Paramètre suivant en tant que caractère UTF-8              |
| `%p` | Paramètre suivant comme adresse (pointeur)                 |
| `\t` | Tab, fixer la position verticale avant de continuer        |
| `\n` | Commencer une nouvelle ligne                               |

Vous pouvez ajouter du remplissage en spécifiant la longueur entre `%` et le code. Si cela commence par `0`, alors la valeur sera
complétée par des zéros, sinon par des espaces. Par exemple, `%4d` remplira la valeur à droite avec des espaces et `%04x` avec des
zéros. Le `f` accepte un nombre après un point, qui indique le nombre de chiffres dans la partie fractionnaire (jusqu'à 8), par
exemple `%.6f`.

## Espace 3D

Dans MEG-4, l'espace tridimensionnel est géré selon la règle de la main droite: +X est à droite, +Y est vers le haut et +Z est
vers le spectateur.

```
  +Y
   |
   |__ +X
  /
+Z
```

Chaque point doit être placé entre -32767 et +32767. La façon dont ce monde 3D est projeté sur votre écran 2D dépend de la
façon dont vous configurez la caméra (voir l'adresse [Processeur Graphique] 0049E). Bien entendu, il faut placer la caméra dans le
monde, avec les coordonnées X, Y, Z. Ensuite, vous devez déterminer où la caméra regarde, en utilisant le tangage et le lacet.
Enfin, vous devez également indiquer de quel type d'objectif la caméra dispose, en spécifiant l'angle du champ de vision. Cette
dernière devrait normalement être comprise entre 30 (très étroit) et 180 degrés (comme les poissons et les oiseaux). MEG-4 prend en
charge jusqu'à 127 degrés, mais il existe une astuce. Les valeurs positives du FOV seront projetées en perspective (plus l'objet est
loin, plus il est petit), mais les valeurs négatives seront également traitées, uniquement avec la projection orthographique (quelle
que soit la distance, la taille de l'objet sera la même). La perspective est utilisée dans les jeux FPS, tandis que la projection
orthographique est surtout préférée dans les jeux de stratégie.

Vous pouvez afficher efficacement un ensemble de triangles (un modèle 3D complet) en utilisant la fonction [mesh]. Étant donné que
les modèles ont probablement des coordonnées locales, cela dessinerait tous les modèles les uns sur les autres autour de l'origo.
Donc, si vous souhaitez afficher plusieurs modèles dans le monde, vous devez d'abord les traduire (les placer) en coordonnées
mondiales à l'aide de [trns], puis utiliser le nuage de sommets traduit avec [mesh] (déplacer et faire pivoter le modèle ne changera
pas les triangles, juste leurs coordonnées de sommet).

## Raccourcis de l'éditeur de code

Raccourcis [clavier] supplémentaires que vous pouvez également utiliser lors de l'édition de la source:

| Touche | Description |
|------------------------------|--------------------------------------------------------------------------------------|
| <kbd>Ctrl</kbd>+<kbd>F</kbd> | Rechercher une chaîne |
| <kbd>Ctrl</kbd>+<kbd>G</kbd> | Rechercher à nouveau |
| <kbd>Ctrl</kbd>+<kbd>H</kbd> | Rechercher et remplacer (dans le texte sélectionné, ou à défaut, dans la source entière) |
| <kbd>Ctrl</kbd>+<kbd>J</kbd> | Aller à la ligne |
| <kbd>Ctrl</kbd>+<kbd>D</kbd> | Aller à la définition de la fonction |
| <kbd>Ctrl</kbd>+<kbd>N</kbd> | Lister les signets |
| <kbd>Ctrl</kbd>+<kbd>B</kbd> | Activer/désactiver le signet sur la ligne actuelle |
| <kbd>Ctrl</kbd>+<kbd>▴</kbd> | Aller au signet précédent |
| <kbd>Ctrl</kbd>+<kbd>▾</kbd> | Aller au signet suivant |
| <kbd>Ctrl</kbd>+<kbd>◂</kbd> | Aller au début du mot précédent |
| <kbd>Ctrl</kbd>+<kbd>▸</kbd> | Aller à la fin du mot suivant |
| <kbd>Ctrl</kbd>+<kbd>,</kbd> | Diminuer l'indentation de la sélection |
| <kbd>Ctrl</kbd>+<kbd>.</kbd> | Augmenter l'indentation de la sélection |
| <kbd>Accueil</kbd> | Déplacer le curseur au début de la ligne |
| <kbd>Fin</kbd> | Déplacer le curseur à la fin de la ligne |
| <kbd>PgUp</kbd> | Déplacer le curseur de 42 lignes (une page) vers le haut |
| <kbd>PgDown</kbd> | Déplacer le curseur de 42 lignes (une page) vers le bas |
| <kbd>F1</kbd> | Si le curseur se trouve dans la liste d'arguments d'une API, accédez à la page d'aide intégrée de la fonction |

Quelle que soit la disposition du clavier de la plateforme, tous les caractères nécessaires à la programmation (et bien d'autres)
sont toujours accessibles:

| Gauche <kbd>Alt</kbd> + |
|-------------------------|
| <kbd> </kbd> <kbd>(</kbd> <kbd>)</kbd> <kbd>{</kbd> <kbd>}</kbd> <kbd>〈</kbd> <kbd>〉</kbd> <kbd>!</kbd> <kbd>^</kbd> <kbd>_</kbd> <kbd>-</kbd> <kbd>=</kbd> |
| <kbd>⇥</kbd> <kbd> </kbd> <kbd> </kbd> <kbd>€</kbd> <kbd>₹</kbd> <kbd>~</kbd> <kbd>¥</kbd> <kbd> </kbd> <kbd> </kbd> <kbd>°</kbd> <kbd>"</kbd> <kbd>\[</kbd> <kbd>\]</kbd> |
| <kbd>↨</kbd> <kbd>&</kbd> <kbd>$</kbd> <kbd>@</kbd> <kbd>¦</kbd> <kbd> </kbd> <kbd>#</kbd> <kbd> </kbd> <kbd> </kbd> <kbd>£</kbd> <kbd>;</kbd> <kbd>'</kbd> <kbd>\\</kbd> |
| <kbd>⇮</kbd> <kbd>:</kbd> <kbd>?</kbd> <kbd> </kbd> <kbd>元</kbd> <kbd>%</kbd> <kbd>+</kbd> <kbd>✶</kbd> <kbd>,</kbd> <kbd>.</kbd> <kbd>/</kbd> |

Voir également le menu pour les méthodes de saisie alternatives et leurs raccourcis clavier.

# Console

## putc

```c
void putc(uint32_t chr)
```
<dl>
<dt>Description</dt><dd>
Imprime un personnage sur la console.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| chr | Caractère UTF-8 |
</dd>
</dl>
<hr>
## printf

```c
void printf(str_t fmt, ...)
```
<dl>
<dt>Description</dt><dd>
Imprime le texte sur la console.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| fmt | chaîne à afficher, une [formater la chaîne] |
| ... | arguments facultatifs |
</dd>
</dl>
<hr>
## getc

```c
uint32_t getc(void)
```
<dl>
<dt>Description</dt><dd>
Lit un personnage depuis la console, bloque le programme lorsqu'il n'y a aucune entrée.
</dd>
<dt>Valeur de retour</dt><dd>
Caractère UTF-8 saisi par l’utilisateur.
</dd>
<dt>Voir aussi</dt><dd>
[popkey]
</dd>
</dl>
<hr>
## gets

```c
str_t gets(void)
```
<dl>
<dt>Description</dt><dd>
Lit une chaîne terminée par une nouvelle ligne de l'utilisateur (ne renvoie pas la nouvelle ligne).
</dd>
<dt>Valeur de retour</dt><dd>
Les octets lus dans une chaîne.
</dd>
</dl>
<hr>
## trace

```c
void trace(str_t fmt, ...)
```
<dl>
<dt>Description</dt><dd>
Tracez l'exécution en imprimant sur la sortie standard. Ne fonctionne que si `meg4` a été démarré avec l'indicateur détaillé `-v`.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| fmt | chaîne à afficher, une [formater la chaîne] |
| ... | arguments facultatifs |
</dd>
</dl>
<hr>
## delay

```c
void delay(uint16_t msec)
```
<dl>
<dt>Description</dt><dd>
Retarde l’exécution du programme.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| msec | délai en millisecondes |
</dd>
</dl>
<hr>
## exit

```c
void exit(void)
```
<dl>
<dt>Description</dt><dd>
Quitte le programme.
</dd>
</dl>

# Audio

## sfx

```c
void sfx(uint8_t sfx, uint8_t channel, uint8_t volume)
```
<dl>
<dt>Description</dt><dd>
Joue un effet sonore.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| sfx | l'indice de l'effet sonore, 0 à 63 |
| channel | canal à utiliser, 0 à 11 |
| volume | volume à utiliser, 0 à 255, 0 désactive la chaîne |
</dd>
</dl>
<hr>
## music

```c
void music(uint8_t track, uint16_t row, uint8_t volume)
```
<dl>
<dt>Description</dt><dd>
Joue une piste musicale.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| track | l'index de la piste musicale, 0 à 7 |
| row | ligne à partir de laquelle commencer la lecture, 0 à 1023 (durée maximale de la chanson) |
| volume | volume à utiliser, 0 à 255, 0 désactive la musique |
</dd>
</dl>

# GPIO

## gpio_rev

```c
uint32_t gpio_rev(void)
```
<dl>
<dt>Description</dt><dd>
Recherchez le numéro de révision de la carte GPIO. Renvoie 0 si la plate-forme n'est pas compatible GPIO.
</dd>
<dt>Valeur de retour</dt><dd>
Numéro de révision de la carte ou 0 s'il n'est pas pris en charge.
</dd>
</dl>
<hr>
## gpio_get

```c
int gpio_get(uint8_t pin)
```
<dl>
<dt>Description</dt><dd>
Lisez la valeur d'une broche GPIO.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| pin | numéro de broche physique, 1 à 40 |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie 1 si la broche est haute, 0 si elle est basse, -1 en cas d'erreur (broche GPIO non prise en charge).
</dd>
<dt>Voir aussi</dt><dd>
[gpio_set]
</dd>
</dl>
<hr>
## gpio_set

```c
int gpio_set(uint8_t pin, int value)
```
<dl>
<dt>Description</dt><dd>
Écrivez la valeur sur une broche GPIO.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| pin | numéro de broche physique, 1 à 40 |
| value | 1 pour régler la broche haute, 0 pour basse |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie 0 en cas de succès, -1 en cas d'erreur (broche GPIO non prise en charge).
</dd>
<dt>Voir aussi</dt><dd>
[gpio_get]
</dd>
</dl>

# Graphique

## cls

```c
void cls(uint8_t palidx)
```
<dl>
<dt>Description</dt><dd>
Efface tout l'écran et réinitialise les décalages d'affichage, définit également la couleur d'arrière-plan de la console.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
</dd>
<dt>Voir aussi</dt><dd>
[pget], [pset]
</dd>
</dl>
<hr>
## cget

```c
uint32_t cget(uint16_t x, uint16_t y)
```
<dl>
<dt>Description</dt><dd>
Obtenez un pixel à une coordonnée et renvoyez la couleur RGBA.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| x | coordonnée X en pixels |
| y | coordonnée Y en pixels |
</dd>
<dt>Valeur de retour</dt><dd>
Une couleur riche, avec des canaux RGBA (le rouge est dans l'octet de poids faible).
</dd>
<dt>Voir aussi</dt><dd>
[cls], [pget], [pset]
</dd>
</dl>
<hr>
## pget

```c
uint8_t pget(uint16_t x, uint16_t y)
```
<dl>
<dt>Description</dt><dd>
Obtenez un pixel à une coordonnée et renvoyez son index de palette.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| x | coordonnée X en pixels |
| y | coordonnée Y en pixels |
</dd>
<dt>Valeur de retour</dt><dd>
Couleur dans l'indice de palette, 0 à 255.
</dd>
<dt>Voir aussi</dt><dd>
[cls], [pset], [cget]
</dd>
</dl>
<hr>
## pset

```c
void pset(uint8_t palidx, uint16_t x, uint16_t y)
```
<dl>
<dt>Description</dt><dd>
Trace un pixel à une coordonnée.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x | coordonnée X en pixels |
| y | coordonnée Y en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[cls], [pget]
</dd>
</dl>
<hr>
## width

```c
uint16_t width(int8_t type, str_t str)
```
<dl>
<dt>Description</dt><dd>
Renvoie la largeur du texte affiché en pixels.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| type | type de police, -4 à 4 |
| str | corde à mesurer |
</dd>
<dt>Valeur de retour</dt><dd>
Nombre de pixels requis pour afficher le texte.
</dd>
<dt>Voir aussi</dt><dd>
[text]
</dd>
</dl>
<hr>
## text

```c
void text(uint8_t palidx, int16_t x, int16_t y, int8_t type, uint8_t shidx, uint8_t sha, str_t str)
```
<dl>
<dt>Description</dt><dd>
Imprime le texte à l'écran.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x | coordonnée X en pixels |
| y | coordonnée Y en pixels |
| type | type de police, -4 à -1 monospace, 1 à 4 proportionnel |
| shidx | couleur de l'ombre, indice de palette 0 à 255 |
| sha | alpha de l'ombre, 0 (entièrement transparent) à 255 (entièrement opaque) |
| str | chaîne à afficher |
</dd>
<dt>Voir aussi</dt><dd>
[width]
</dd>
</dl>
<hr>
## line

```c
void line(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Description</dt><dd>
Dessine une ligne anti-aliasée.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X de départ en pixels |
| y0 | coordonnée Y de départ en pixels |
| x1 | coordonnée X de fin en pixels |
| y1 | coordonnée Y de fin en pixels |
</dd>
<dt>Voir aussi</dt><dd>
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
<dt>Description</dt><dd>
Dessine une courbe de Bézier quadratique.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X de départ en pixels |
| y0 | coordonnée Y de départ en pixels |
| x1 | coordonnée X de fin en pixels |
| y1 | coordonnée Y de fin en pixels |
| cx | coordonnée X du point de contrôle en pixels |
| cy | coordonnée Y du point de contrôle en pixels |
</dd>
<dt>Voir aussi</dt><dd>
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
<dt>Description</dt><dd>
Dessine une courbe de Bézier cubique.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X de départ en pixels |
| y0 | coordonnée Y de départ en pixels |
| x1 | coordonnée X de fin en pixels |
| y1 | coordonnée Y de fin en pixels |
| cx0 | coordonnée X du premier point de contrôle en pixels |
| cy0 | coordonnée Y du premier point de contrôle en pixels |
| cx1 | coordonnée X du deuxième point de contrôle en pixels |
| cy1 | coordonnée Y du deuxième point de contrôle en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[line], [qbez]
</dd>
</dl>
<hr>
## tri

```c
void tri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dl>
<dt>Description</dt><dd>
Dessine un triangle.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X du premier bord en pixels |
| y0 | coordonnée Y du premier bord en pixels |
| x1 | coordonnée X du deuxième bord en pixels |
| y1 | coordonnée Y du deuxième bord en pixels |
| x2 | coordonnée X du troisième bord en pixels |
| y2 | coordonnée Y du troisième bord en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[ftri], [tri2d], [tri3d], [tritx], [mesh], [trns]
</dd>
</dl>
<hr>
## ftri

```c
void ftri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dl>
<dt>Description</dt><dd>
Dessine un triangle rempli.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X du premier bord en pixels |
| y0 | coordonnée Y du premier bord en pixels |
| x1 | coordonnée X du deuxième bord en pixels |
| y1 | coordonnée Y du deuxième bord en pixels |
| x2 | coordonnée X du troisième bord en pixels |
| y2 | coordonnée Y du troisième bord en pixels |
</dd>
<dt>Voir aussi</dt><dd>
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
<dt>Description</dt><dd>
Dessine un triangle rempli avec des dégradés de couleurs.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| pi0 | couleur du premier bord, indice de palette 0 à 255 |
| x0 | coordonnée X du premier bord en pixels |
| y0 | coordonnée Y du premier bord en pixels |
| pi1 | couleur du deuxième bord, indice de palette 0 à 255 |
| x1 | coordonnée X du deuxième bord en pixels |
| y1 | coordonnée Y du deuxième bord en pixels |
| pi2 | couleur du troisième bord, indice de palette 0 à 255 |
| x2 | coordonnée X du troisième bord en pixels |
| y2 | coordonnée Y du troisième bord en pixels |
</dd>
<dt>Voir aussi</dt><dd>
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
<dt>Description</dt><dd>
Dessine un triangle rempli avec des dégradés de couleurs dans [espace 3D].
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| pi0 | couleur du premier bord, indice de palette 0 à 255 |
| x0 | coordonnée X du premier bord dans l'espace |
| y0 | coordonnée Y du premier bord dans l'espace |
| z0 | coordonnée Z du premier bord dans l'espace |
| pi1 | couleur du deuxième bord, indice de palette 0 à 255 |
| x1 | coordonnée X du deuxième bord dans l'espace |
| y1 | coordonnée Y du deuxième bord dans l'espace |
| z1 | coordonnée Z du deuxième bord dans l'espace |
| pi2 | couleur du troisième bord, indice de palette 0 à 255 |
| x2 | coordonnée X du troisième bord dans l'espace |
| y2 | coordonnée Y du troisième bord dans l'espace |
| z2 | coordonnée Z du troisième bord dans l'espace |
</dd>
<dt>Voir aussi</dt><dd>
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
<dt>Description</dt><dd>
Dessine un triangle texturé dans [espace 3D].
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| u0 | première texture de bord coordonnée X 0 à 255 |
| v0 | première texture de bord coordonnée Y 0 à 255 |
| x0 | coordonnée X du premier bord dans l'espace |
| y0 | coordonnée Y du premier bord dans l'espace |
| z0 | coordonnée Z du premier bord dans l'espace |
| u1 | deuxième texture de bord coordonnée X 0 à 255 |
| v1 | deuxième texture de bord coordonnée Y 0 à 255 |
| x1 | coordonnée X du deuxième bord dans l'espace |
| y1 | coordonnée Y du deuxième bord dans l'espace |
| z1 | coordonnée Z du deuxième bord dans l'espace |
| u2 | troisième texture de bord coordonnée X 0 à 255 |
| v2 | troisième texture de bord coordonnée Y 0 à 255 |
| x2 | coordonnée X du troisième bord dans l'espace |
| y2 | coordonnée Y du troisième bord dans l'espace |
| z2 | coordonnée Z du troisième bord dans l'espace |
</dd>
<dt>Voir aussi</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [mesh], [trns]
</dd>
</dl>
<hr>
## mesh

```c
void mesh(addr_t verts, addr_t uvs, uint16_t numtri, addr_t tris)
```
<dl>
<dt>Description</dt><dd>
Dessine un maillage composé de triangles dans [espace 3D], en utilisant des indices de sommets et des coordonnées de texture
(ou palette).
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| verts | adresse du tableau de sommets, 3 x 2 octets chacun, X, Y, Z |
| uvs | adresse du tableau UV (si 0, alors la palette est utilisée), 2 x 1 octets chacun, texture X, Y |
| numtri | nombre de triangles |
| tris | adresse du tableau de triangles avec indices, 6 x 1 octets chacun, vi1, ui1/pi1, vi2, ui2/pi2, vi3, ui3/pi3 |
</dd>
<dt>Voir aussi</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [tritx], [trns]
</dd>
</dl>
<hr>
## rect

```c
void rect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Description</dt><dd>
Dessine un rectangle.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X du coin supérieur gauche en pixels |
| y0 | coordonnée Y du coin supérieur gauche en pixels |
| x1 | coordonnée X en bas à droite en pixels |
| y1 | coordonnée Y en bas à droite en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[frect]
</dd>
</dl>
<hr>
## frect

```c
void frect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Description</dt><dd>
Dessine un rectangle rempli.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X du coin supérieur gauche en pixels |
| y0 | coordonnée Y du coin supérieur gauche en pixels |
| x1 | coordonnée X en bas à droite en pixels |
| y1 | coordonnée Y en bas à droite en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[rect]
</dd>
</dl>
<hr>
## circ

```c
void circ(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dl>
<dt>Description</dt><dd>
Dessine un cercle.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x | coordonnée X du centre en pixels |
| y | coordonnée Y du centre en pixels |
| r | rayon en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[fcirc], [ellip], [fellip]
</dd>
</dl>
<hr>
## fcirc

```c
void fcirc(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dl>
<dt>Description</dt><dd>
Dessine un cercle rempli.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x | coordonnée X du centre en pixels |
| y | coordonnée Y du centre en pixels |
| r | rayon en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[circ], [ellip], [fellip]
</dd>
</dl>
<hr>
## ellip

```c
void ellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Description</dt><dd>
Dessine une ellipse.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X du coin supérieur gauche en pixels |
| y0 | coordonnée Y du coin supérieur gauche en pixels |
| x1 | coordonnée X en bas à droite en pixels |
| y1 | coordonnée Y en bas à droite en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[circ], [fcirc], [fellip]
</dd>
</dl>
<hr>
## fellip

```c
void fellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Description</dt><dd>
Dessine une ellipse remplie.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
| x0 | coordonnée X du coin supérieur gauche en pixels |
| y0 | coordonnée Y du coin supérieur gauche en pixels |
| x1 | coordonnée X en bas à droite en pixels |
| y1 | coordonnée Y en bas à droite en pixels |
</dd>
<dt>Voir aussi</dt><dd>
[circ], [fcirc], [ellip]
</dd>
</dl>
<hr>
## move

```c
void move(int16_t x, int16_t y, uint16_t deg)
```
<dl>
<dt>Description</dt><dd>
Déplace la tortue à la position donnée à l'écran ou dans le labyrinthe.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| x | coordonnée X en pixels (ou 1/128 tuiles avec [maze]) |
| y | coordonnée Y en pixels |
| deg | direction en degrés, 0 à 359, 0 est vers le haut sur l'écran, 90 est vers la droite |
</dd>
<dt>Voir aussi</dt><dd>
[left], [right], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## left

```c
void left(uint16_t deg)
```
<dl>
<dt>Description</dt><dd>
Tourne la tortue vers la gauche.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| deg | changement en degrés, 0 à 359 |
</dd>
<dt>Voir aussi</dt><dd>
[move], [right], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## right

```c
void right(uint16_t deg)
```
<dl>
<dt>Description</dt><dd>
Tourne la tortue à droite.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| deg | changement en degrés, 0 à 359 |
</dd>
<dt>Voir aussi</dt><dd>
[move], [left], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## up

```c
void up(void)
```
<dl>
<dt>Description</dt><dd>
Soulève la queue de la tortue. La tortue se déplacera sans tracer de ligne.
</dd>
<dt>Voir aussi</dt><dd>
[move], [left], [right], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## down

```c
void down(void)
```
<dl>
<dt>Description</dt><dd>
Abaisse la queue de la tortue. La tortue se déplacera en traçant une ligne (voir [color]).
</dd>
<dt>Voir aussi</dt><dd>
[move], [left], [right], [up], [color], [forw], [back]
</dd>
</dl>
<hr>
## color

```c
void color(uint8_t palidx)
```
<dl>
<dt>Description</dt><dd>
Définit la couleur de la peinture de la tortue.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| palidx | couleur, indice de palette 0 à 255 |
</dd>
<dt>Voir aussi</dt><dd>
[move], [left], [right], [up], [down], [forw], [back]
</dd>
</dl>
<hr>
## forw

```c
void forw(uint16_t cnt)
```
<dl>
<dt>Description</dt><dd>
Fait avancer la tortue.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| cnt | quantité en pixels (ou 1/128 tuiles avec [maze]) |
</dd>
<dt>Voir aussi</dt><dd>
[move], [left], [right], [up], [down], [color], [back]
</dd>
</dl>
<hr>
## back

```c
void back(uint16_t cnt)
```
<dl>
<dt>Description</dt><dd>
Fait reculer la tortue.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| cnt | quantité en pixels (ou 1/128 tuiles avec [maze]) |
</dd>
<dt>Voir aussi</dt><dd>
[move], [left], [right], [up], [down], [color], [forw]
</dd>
</dl>
<hr>
## spr

```c
void spr(int16_t x, int16_t y, uint16_t sprite, uint8_t sw, uint8_t sh, int8_t scale, uint8_t type)
```
<dl>
<dt>Description</dt><dd>
Affiche un sprite ou plusieurs sprites adjacents.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| x | coordonnée X en pixels |
| y | coordonnée Y en pixels |
| sprite | identifiant du sprite, 0 à 1023 |
| sw | nombre de sprites horizontaux |
| sh | nombre de sprites verticaux |
| scale | échelle, -3 à 4 |
| type | transformation, 0=normal, 1=rot 90, 2=rot 180, 3=rot 270, 4=retourn vert, 5=retourn+90, 6=retourn horiz, 7=retourn+270 |
</dd>
<dt>Voir aussi</dt><dd>
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
<dt>Description</dt><dd>
Affiche une fenêtre de dialogue utilisant des sprites.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| x | coordonnée X en pixels |
| y | coordonnée Y en pixels |
| w | largeur de la boîte de dialogue en pixels |
| h | hauteur de la boîte de dialogue en pixels |
| scale | échelle, -3 à 4 |
| tl | identifiant du sprite dans le coin supérieur gauche |
| tm | identifiant du sprite supérieur au milieu |
| tr | identifiant du sprite dans le coin supérieur droit |
| ml | identifiant du sprite du côté gauche du milieu |
| bg | identifiant du sprite d'arrière-plan |
| mr | identifiant du sprite du côté droit du milieu |
| bl | identifiant du sprite dans le coin inférieur gauche |
| bm | identifiant du sprite en bas au milieu |
| br | identifiant du sprite dans le coin inférieur droit |
</dd>
<dt>Voir aussi</dt><dd>
[spr], [stext]
</dd>
</dl>
<hr>
## stext

```c
void stext(int16_t x, int16_t y, uint16_t fs, uint16_t fu, uint8_t sw, uint8_t sh, int8_t scale, str_t str)
```
<dl>
<dt>Description</dt><dd>
Displays text on screen using sprites.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| x | coordonnée X en pixels |
| y | coordonnée Y en pixels |
| fs | premier identifiant de sprite à utiliser pour l'affichage |
| fu | premier UNICODE (plus petit caractère) dans la chaîne |
| sw | nombre de sprites horizontaux |
| sh | nombre de sprites verticaux |
| scale | échelle, -3 à 4 |
| str | chaîne UTF-8 terminée par zéro |
</dd>
<dt>Voir aussi</dt><dd>
[spr], [dlg]
</dd>
</dl>
<hr>
## remap

```c
void remap(addr_t replace)
```
<dl>
<dt>Description</dt><dd>
Remplace les tuiles sur la carte. Peut être utilisé pour animer des tuiles sur la carte.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| replace | un tableau de 256 identifiants de sprite |
</dd>
<dt>Voir aussi</dt><dd>
[mget], [mset], [map], [maze]
</dd>
</dl>
<hr>
## mget

```c
uint16_t mget(uint16_t mx, uint16_t my)
```
<dl>
<dt>Description</dt><dd>
Renvoie une tuile sur la carte.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| mx | coordonnée X sur la carte en tuiles |
| my | coordonnée Y sur la carte en tuiles |
</dd>
<dt>Valeur de retour</dt><dd>
L'identifiant du sprite de la tuile à la coordonnée donnée.
</dd>
<dt>Voir aussi</dt><dd>
[remap], [mset], [map], [maze]
</dd>
</dl>
<hr>
## mset

```c
void mset(uint16_t mx, uint16_t my, uint16_t sprite)
```
<dl>
<dt>Description</dt><dd>
Définit une tuile sur la carte.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| mx | coordonnée X sur la carte en tuiles |
| my | coordonnée Y sur la carte en tuiles |
| sprite | identifiant du sprite, 0 à 1023 |
</dd>
<dt>Voir aussi</dt><dd>
[remap], [mget], [map], [maze]
</dd>
</dl>
<hr>
## map

```c
void map(int16_t x, int16_t y, uint16_t mx, uint16_t my, uint16_t mw, uint16_t mh, int8_t scale)
```
<dl>
<dt>Description</dt><dd>
Dessine (une partie de) la carte.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| x | coordonnée X en pixels |
| y | coordonnée Y en pixels |
| mx | coordonnée X sur la carte en tuiles |
| my | coordonnée Y sur la carte en tuiles |
| mw | nombre de tuiles horizontales |
| mh | nombre de tuiles verticales |
| scale | échelle, -3 à 4 |
</dd>
<dt>Voir aussi</dt><dd>
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
<dt>Description</dt><dd>
Affiche la carte sous forme de labyrinthe 3D, en utilisant la position de la tortue.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| mx | coordonnée X sur la carte en tuiles |
| my | coordonnée Y sur la carte en tuiles |
| mw | nombre de tuiles horizontales |
| mh | nombre de tuiles verticales |
| scale | nombre de sprites par tuile en puissance de deux, 0 à 3 |
| sky | index des tuiles du ciel |
| grd | index des tuiles de sol |
| door | index des tuiles de la première porte |
| wall | index des tuiles de la première mural |
| obj | index des tuiles de la première objet |
| numnpc | nombre d'enregistrements de PNJ |
| npc | un tableau uint32_t de triplets d'index numnpc fois x, y, tuile |
</dd>
<dt>Voir aussi</dt><dd>
[remap], [mget], [mset], [map]
</dd>
</dl>

# Saisir

## getpad

```c
int getpad(int pad, int btn)
```
<dl>
<dt>Description</dt><dd>
Obtient l'état actuel d'un bouton de manette de jeu.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| pad | indice de la manette de jeu, 0 à 3 |
| btn | l'un des boutons de la [manette de jeu], `BTN_` |
</dd>
<dt>Valeur de retour</dt><dd>
Zéro si vous n’appuyez pas, différent de zéro si vous appuyez.
</dd>
<dt>Voir aussi</dt><dd>
[prspad], [relpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## prspad

```c
int prspad(int pad, int btn)
```
<dl>
<dt>Description</dt><dd>
Renvoie vrai si le bouton de la manette de jeu a été enfoncé depuis le dernier appel.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| pad | indice de la manette de jeu, 0 à 3 |
| btn | l'un des boutons de la [manette de jeu], `BTN_` |
</dd>
<dt>Valeur de retour</dt><dd>
Zéro si vous n’appuyez pas, différent de zéro si vous appuyez.
</dd>
<dt>Voir aussi</dt><dd>
[relpad], [getpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## relpad

```c
int relpad(int pad, int btn)
```
<dl>
<dt>Description</dt><dd>
Renvoie vrai si le bouton de la manette de jeu a été relâché depuis le dernier appel.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| pad | indice de la manette de jeu, 0 à 3 |
| btn | l'un des boutons de la [manette de jeu], `BTN_` |
</dd>
<dt>Valeur de retour</dt><dd>
Zéro s'il n'a pas été publié, différent de zéro s'il a été publié.
</dd>
<dt>Voir aussi</dt><dd>
[prspad], [getpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## getbtn

```c
int getbtn(int btn)
```
<dl>
<dt>Description</dt><dd>
Obtient l'état du bouton de la souris.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| btn | l'un des boutons [pointeur], `BTN_` ou `SCR_` |
</dd>
<dt>Valeur de retour</dt><dd>
Zéro si vous n’appuyez pas, différent de zéro si vous appuyez.
</dd>
<dt>Voir aussi</dt><dd>
[prspad], [relpad], [getpad], [getclk], [getkey]
</dd>
</dl>
<hr>
## getclk

```c
int getclk(int btn)
```
<dl>
<dt>Description</dt><dd>
Obtient un clic sur le bouton de la souris.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| btn | l'un des boutons [pointeur], `BTN_` |
</dd>
<dt>Valeur de retour</dt><dd>
Zéro si vous ne cliquez pas, différent de zéro si vous cliquez.
</dd>
<dt>Voir aussi</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getkey]
</dd>
</dl>
<hr>
## getkey

```c
int getkey(int sc)
```
<dl>
<dt>Description</dt><dd>
Obtient l'état actuel d'une clé.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| sc | scancode, 1 à 144, voir [clavier] |
</dd>
<dt>Valeur de retour</dt><dd>
Zéro si vous n’appuyez pas, différent de zéro si vous appuyez.
</dd>
<dt>Voir aussi</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getclk]
</dd>
</dl>
<hr>
## popkey

```c
uint32_t popkey(void)
```
<dl>
<dt>Description</dt><dd>
Extrayez une clé UTF-8 de la file d’attente du clavier. Voir [clavier] et pour la version bloquante [getc].
</dd>
<dt>Valeur de retour</dt><dd>
La représentation UTF-8 de la clé, ou 0 si la file d'attente était vide (pas de blocage).
</dd>
<dt>Voir aussi</dt><dd>
[pendkey], [lenkey], [speckey], [getc]
</dd>
</dl>
<hr>
## pendkey

```c
int pendkey(void)
```
<dl>
<dt>Description</dt><dd>
Renvoie vrai s'il y a une clé en attente dans la file d'attente (mais laisse la clé dans la file d'attente, ne la supprime pas).
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie 1 s'il y a des clés en attente dans la file d'attente.
</dd>
<dt>Voir aussi</dt><dd>
[popkey], [lenkey], [speckey]
</dd>
</dl>
<hr>
## lenkey

```c
int lenkey(uint32_t key)
```
<dl>
<dt>Description</dt><dd>
Renvoie la longueur d'une clé UTF-8 en octets.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| key | la clé, récupérée dans la file d'attente |
</dd>
<dt>Valeur de retour</dt><dd>
Longueur de la représentation UTF-8 en octets.
</dd>
<dt>Voir aussi</dt><dd>
[popkey], [pendkey], [speckey]
</dd>
</dl>
<hr>
## speckey

```c
int speckey(uint32_t key)
```
<dl>
<dt>Description</dt><dd>
Renvoie vrai si la clé est une clé spéciale.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| key | la clé, récupérée dans la file d'attente |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie 1 s'il s'agit d'une clé spéciale et 0 si elle est imprimable.
</dd>
<dt>Voir aussi</dt><dd>
[popkey], [pendkey], [lenkey]
</dd>
</dl>

# Mathématiques

## rand

```c
uint32_t rand(void)
```
<dl>
<dt>Description</dt><dd>
Soyez aléatoire. Utilisez `%` modulo pour le rendre plus petit, par exemple `1 + rand() % 6` renvoie un nombre aléatoire entre
1 et 6, comme un dé.
</dd>
<dt>Valeur de retour</dt><dd>
Un nombre aléatoire compris entre 0 et 2^^32^^-1 (4294967295).
</dd>
<dt>Voir aussi</dt><dd>
[rnd]
</dd>
</dl>
<hr>
## rnd

```c
float rnd(void)
```
<dl>
<dt>Description</dt><dd>
Soyez aléatoire. Identique à [rand], mais renvoie un nombre à virgule flottante.
</dd>
<dt>Valeur de retour</dt><dd>
Un nombre aléatoire compris entre 0.0 et 1.0.
</dd>
<dt>Voir aussi</dt><dd>
[rand]
</dd>
</dl>
<hr>
## float

```c
float float(int val)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'équivalent en virgule flottante d'un nombre entier.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
La valeur à virgule flottante.
</dd>
<dt>Voir aussi</dt><dd>
[int]
</dd>
</dl>
<hr>
## int

```c
int int(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'équivalent entier d'un nombre à virgule flottante.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
L'entier de la valeur.
</dd>
<dt>Voir aussi</dt><dd>
[float]
</dd>
</dl>
<hr>
## floor

```c
float floor(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie le plus grand nombre entier qui n'est pas supérieur à la valeur.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
Le plancher de valeur.
</dd>
<dt>Voir aussi</dt><dd>
[ceil]
</dd>
</dl>
<hr>
## ceil

```c
float ceil(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie le plus petit nombre entier qui n'est pas inférieur à la valeur.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
Le plafond de valeur.
</dd>
<dt>Voir aussi</dt><dd>
[floor]
</dd>
</dl>
<hr>
## sgn

```c
float sgn(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie le signe de la valeur.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
Soit 1.0 ou -1.0.
</dd>
<dt>Voir aussi</dt><dd>
[abs]
</dd>
</dl>
<hr>
## abs

```c
float abs(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'absolu de la valeur.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
Soit valeur, ou -valeur, toujours positive.
</dd>
<dt>Voir aussi</dt><dd>
[sgn]
</dd>
</dl>
<hr>
## exp

```c
float exp(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'exponentielle de la valeur, c'est-à-dire la base des logarithmes naturels élevés à la puissance de la valeur.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie e^^val^^.
</dd>
<dt>Voir aussi</dt><dd>
[log], [pow]
</dd>
</dl>
<hr>
## log

```c
float log(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie le logarithme népérien de la valeur.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie le logarithme népérien de val.
</dd>
<dt>Voir aussi</dt><dd>
[exp]
</dd>
</dl>
<hr>
## pow

```c
float pow(float val, float exp)
```
<dl>
<dt>Description</dt><dd>
Renvoie la valeur élevée à la puissance de l'exposant. C'est une opération lente, essayez de l'éviter.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
| exp | exposant |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie val^^exp^^.
</dd>
<dt>Voir aussi</dt><dd>
[exp], [sqrt], [rsqrt]
</dd>
</dl>
<hr>
## sqrt

```c
float sqrt(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie la racine carrée de la valeur. C'est une opération lente, essayez de l'éviter.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
Racine carrée de la valeur.
</dd>
<dt>Voir aussi</dt><dd>
[pow], [rsqrt]
</dd>
</dl>
<hr>
## rsqrt

```c
float rsqrt(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'inverse de la racine carrée de la valeur (`1 / sqrt(val)`). Utilise la méthode rapide de John Carmack.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
</dd>
<dt>Valeur de retour</dt><dd>
Réciproque de la racine carrée de la valeur.
</dd>
<dt>Voir aussi</dt><dd>
[pow], [sqrt]
</dd>
</dl>
<hr>
## clamp

```c
float clamp(float val, float minv, float maxv)
```
<dl>
<dt>Description</dt><dd>
Coince une valeur entre les limites.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur |
| minv | valeur minimum |
| maxv | valeur maximum |
</dd>
<dt>Valeur de retour</dt><dd>
Valeur serrée.
</dd>
<dt>Voir aussi</dt><dd>
[clampv2], [clampv3], [clampv4]
</dd>
</dl>
<hr>
## lerp

```c
float lerp(float a, float b, float t)
```
<dl>
<dt>Description</dt><dd>
Linéaire interpole deux nombres.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | premier numéro flottant |
| b | deuxième numéro flottant |
| t | valeur d'interpolation entre 0.0 et 1.0 |
</dd>
<dt>Voir aussi</dt><dd>
[lerpv2], [lerpv3], [lerpv4], [lerpq], [slerpq]
</dd>
</dl>
<hr>
## pi

```c
float pi(void)
```
<dl>
<dt>Description</dt><dd>
Renvoie π sous forme de nombre à virgule flottante.
</dd>
<dt>Valeur de retour</dt><dd>
La valeur 3.14159265358979323846.
</dd>
</dl>
<hr>
## cos

```c
float cos(uint16_t deg)
```
<dl>
<dt>Description</dt><dd>
Renvoie le cosinus.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| deg | degré, 0 à 359, 0 est en haut, 90 à droite |
</dd>
<dt>Valeur de retour</dt><dd>
Cosinus du degré, entre -1.0 et 1.0.
</dd>
<dt>Voir aussi</dt><dd>
[sin], [tan], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## sin

```c
float sin(uint16_t deg)
```
<dl>
<dt>Description</dt><dd>
Renvoie le sinus.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| deg | degré, 0 à 359, 0 est en haut, 90 à droite |
</dd>
<dt>Valeur de retour</dt><dd>
Sinus du degré, entre -1.0 et 1.0.
</dd>
<dt>Voir aussi</dt><dd>
[cos], [tan], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## tan

```c
float tan(uint16_t deg)
```
<dl>
<dt>Description</dt><dd>
Renvoie la tangente.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| deg | degré, 0 à 359, 0 est en haut, 90 à droite |
</dd>
<dt>Valeur de retour</dt><dd>
Tangente du degré, entre -1.0 et 1.0.
</dd>
<dt>Voir aussi</dt><dd>
[cos], [sin], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## acos

```c
uint16_t acos(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'arcus cosinus.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur, -1.0 à 1.0 |
</dd>
<dt>Valeur de retour</dt><dd>
Arcus cosinus en degré, 0 à 359, 0 est en haut, 90 à droite.
</dd>
<dt>Voir aussi</dt><dd>
[cos], [sin], [tan], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## asin

```c
uint16_t asin(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'arcus sinus.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur, -1.0 à 1.0 |
</dd>
<dt>Valeur de retour</dt><dd>
Arcus sinus en degré, 0 à 359, 0 en haut, 90 à droite.
</dd>
<dt>Voir aussi</dt><dd>
[cos], [sin], [tan], [acos], [atan], [atan2]
</dd>
</dl>
<hr>
## atan

```c
uint16_t atan(float val)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'arcus tangent.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| val | valeur, -1.0 à 1.0 |
</dd>
<dt>Valeur de retour</dt><dd>
Arcus tangent en degré, 0 à 359, 0 est en haut, 90 à droite.
</dd>
<dt>Voir aussi</dt><dd>
[cos], [sin], [tan], [acos], [asin], [atan2]
</dd>
</dl>
<hr>
## atan2

```c
uint16_t atan2(float y, float x)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'arcus tangent pour y/x, en utilisant les signes de y et x pour déterminer le quadrant.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| y | coordonnée Y |
| x | coordonnée X |
</dd>
<dt>Valeur de retour</dt><dd>
Arcus tangent en degré, 0 à 359, 0 est en haut, 90 à droite.
</dd>
<dt>Voir aussi</dt><dd>
[cos], [sin], [tan], [acos], [asin]
</dd>
</dl>
<hr>
## dotv2

```c
float dotv2(addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Calcule le produit scalaire de deux vecteurs avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de deux flotteurs |
| b | adresse de deux flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Produit scalaire des vecteurs.
</dd>
<dt>Voir aussi</dt><dd>
[lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## lenv2

```c
float lenv2(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Calcule la longueur d'un vecteur avec deux éléments. C'est lent, essayez de l'éviter (voir [normv2]).
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de deux flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Longueur du vecteur.
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## scalev2

```c
void scalev2(addr_t a, float s)
```
<dl>
<dt>Description</dt><dd>
Met à l'échelle un vecteur avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de deux flotteurs |
| s | valeur d'échelle |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## negv2

```c
void negv2(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Annule un vecteur avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de deux flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [scalev2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## addv2

```c
void addv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Additionne les vecteurs avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de deux flotteurs |
| a | adresse de deux flotteurs |
| b | adresse de deux flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## subv2

```c
void subv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Soustrait les vecteurs à deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de deux flotteurs |
| a | adresse de deux flotteurs |
| b | adresse de deux flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## mulv2

```c
void mulv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Multiplie les vecteurs avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de deux flotteurs |
| a | adresse de deux flotteurs |
| b | adresse de deux flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## divv2

```c
void divv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Divise les vecteurs avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de deux flotteurs |
| a | adresse de deux flotteurs |
| b | adresse de deux flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## clampv2

```c
void clampv2(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Description</dt><dd>
Serre les vecteurs avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de deux flotteurs |
| v | adresse de deux flotteurs |
| minv | adresse de deux flotteurs, minimum |
| maxv | adresse de deux flotteurs, maximum |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## lerpv2

```c
void lerpv2(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Description</dt><dd>
Linéaire interpole les vecteurs avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de deux flotteurs |
| a | adresse de deux flotteurs |
| b | adresse de deux flotteurs |
| t | valeur d'interpolation entre 0.0 et 1.0 |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [normv2]
</dd>
</dl>
<hr>
## normv2

```c
void normv2(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Normalise un vecteur avec deux éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de deux flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2]
</dd>
</dl>
<hr>
## dotv3

```c
float dotv3(addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Calcule le produit scalaire de deux vecteurs avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de trois flotteurs |
| b | adresse de trois flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Produit scalaire des vecteurs.
</dd>
<dt>Voir aussi</dt><dd>
[lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## lenv3

```c
float lenv3(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Calcule la longueur d'un vecteur à trois éléments. C'est lent, essayez de l'éviter (voir [normv3]).
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de trois flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Longueur du vecteur.
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## scalev3

```c
void scalev3(addr_t a, float s)
```
<dl>
<dt>Description</dt><dd>
Met à l'échelle un vecteur avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de trois flotteurs |
| s | valeur d'échelle |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## negv3

```c
void negv3(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Annule un vecteur avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## addv3

```c
void addv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Additionne les vecteurs avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| a | adresse de trois flotteurs |
| b | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## subv3

```c
void subv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Soustrait les vecteurs à trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| a | adresse de trois flotteurs |
| b | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## mulv3

```c
void mulv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Multiplie les vecteurs avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| a | adresse de trois flotteurs |
| b | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## divv3

```c
void divv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Divise les vecteurs avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| a | adresse de trois flotteurs |
| b | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## crossv3

```c
void crossv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Calcule le produit vectoriel de vecteurs à trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| a | adresse de trois flotteurs |
| b | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## clampv3

```c
void clampv3(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Description</dt><dd>
Serre les vecteurs avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| v | adresse de trois flotteurs |
| minv | adresse de trois flotteurs, minimum |
| maxv | adresse de trois flotteurs, maximum |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## lerpv3

```c
void lerpv3(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Description</dt><dd>
Linéaire interpole les vecteurs avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| a | adresse de trois flotteurs |
| b | adresse de trois flotteurs |
| t | valeur d'interpolation entre 0.0 et 1.0 |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [normv3]
</dd>
</dl>
<hr>
## normv3

```c
void normv3(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Normalise un vecteur avec trois éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3]
</dd>
</dl>
<hr>
## dotv4

```c
float dotv4(addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Calcule le produit scalaire de deux vecteurs avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Produit scalaire des vecteurs.
</dd>
<dt>Voir aussi</dt><dd>
[lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## lenv4

```c
float lenv4(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Calcule la longueur d'un vecteur à quatre éléments. C'est lent, essayez de l'éviter (voir [normv4]).
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Longueur du vecteur.
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## scalev4

```c
void scalev4(addr_t a, float s)
```
<dl>
<dt>Description</dt><dd>
Met à l'échelle un vecteur avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
| s | valeur d'échelle |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## negv4

```c
void negv4(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Annule un vecteur avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [scalev4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## addv4

```c
void addv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Additionne les vecteurs avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [negv4], [scalev4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## subv4

```c
void subv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Soustrait les vecteurs à quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## mulv4

```c
void mulv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Multiplie les vecteurs avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## divv4

```c
void divv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Divise les vecteurs avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## clampv4

```c
void clampv4(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Description</dt><dd>
Serre les vecteurs avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| v | adresse de quatre flotteurs |
| minv | adresse de quatre flotteurs, minimum |
| maxv | adresse de quatre flotteurs, maximum |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## lerpv4

```c
void lerpv4(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Description</dt><dd>
Linéaire interpole les vecteurs avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
| t | valeur d'interpolation entre 0.0 et 1.0 |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [normv4]
</dd>
</dl>
<hr>
## normv4

```c
void normv4(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Normalise un vecteur avec quatre éléments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4]
</dd>
</dl>
<hr>
## idq

```c
void idq(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Charge le quaternion d'identité.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## eulerq

```c
void eulerq(addr_t dst, uint16_t pitch, uint16_t yaw, uint16_t roll)
```
<dl>
<dt>Description</dt><dd>
Charge un quaternion en utilisant les angles d'Euler.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| pitch | rotation autour de l'axe X en degrés, 0 à 359 |
| yaw | rotation autour de l'axe Y en degrés, 0 à 359 |
| roll | rotation autour de l'axe Z en degrés, 0 à 359 |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## dotq

```c
float dotq(addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Calcule le produit scalaire d'un quaternion.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Produit scalaire du quaternion.
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## lenq

```c
float lenq(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Calcule la longueur d'un quaternion.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Longueur du quaternion.
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## scaleq

```c
void scaleq(addr_t a, float s)
```
<dl>
<dt>Description</dt><dd>
Met à l'échelle un quaternion.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
| s | valeur d'échelle |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## negq

```c
void negq(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Annule un quaternion.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## addq

```c
void addq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Additionne les quaternions.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## subq

```c
void subq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Soustrait les quaternions.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## mulq

```c
void mulq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Multiplie les quaternions.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## rotq

```c
void rotq(addr_t dst, addr_t q, addr_t v)
```
<dl>
<dt>Description</dt><dd>
Fait pivoter un vecteur à trois éléments d'un quaternion.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| q | adresse de quatre flotteurs |
| v | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## lerpq

```c
void lerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Description</dt><dd>
Linéaire interpole deux quaternions.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
| t | interpolation value between 0.0 and 1.0 |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [slerpq], [normq]
</dd>
</dl>
<hr>
## slerpq

```c
void slerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Description</dt><dd>
Sphérique interpole un quaternion.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| a | adresse de quatre flotteurs |
| b | adresse de quatre flotteurs |
| t | interpolation value between 0.0 and 1.0 |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [normq]
</dd>
</dl>
<hr>
## normq

```c
void normq(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Normalise un quaternion.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq]
</dd>
</dl>
<hr>
## idm4

```c
void idm4(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Charge une matrice d'identité 4 x 4.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de 16 flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## trsm4

```c
void trsm4(addr_t dst, addr_t t, addr_t r, addr_t s)
```
<dl>
<dt>Description</dt><dd>
Crée une matrice 4 x 4 avec traduction, rotation et mise à l'échelle.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de 16 flotteurs, matrice de destination |
| t | adresse de trois flotteurs, vecteur de traduction |
| r | adresse de quatre flotteurs, quaternion de rotation |
| s | adresse de trois flotteurs, vecteur de mise à l'échelle |
</dd>
<dt>Voir aussi</dt><dd>
[idm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## detm4

```c
float detm4(addr_t a)
```
<dl>
<dt>Description</dt><dd>
Renvoie le déterminant de la matrice.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| a | adresse de 16 flotteurs |
</dd>
<dt>Valeur de retour</dt><dd>
Le déterminant de la matrice.
</dd>
<dt>Voir aussi</dt><dd>
[idm4], [trsm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## addm4

```c
void addm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Additionne les matrices ensemble.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de 16 flotteurs |
| a | adresse de 16 flotteurs |
| b | adresse de 16 flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idm4], [trsm4], [detm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## subm4

```c
void subm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Soustrait les matrices.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de 16 flotteurs |
| a | adresse de 16 flotteurs |
| b | adresse de 16 flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4

```c
void mulm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Description</dt><dd>
Multiplie les matrices.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de 16 flotteurs |
| a | adresse de 16 flotteurs |
| b | adresse de 16 flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4v3

```c
void mulm4v3(addr_t dst, addr_t m, addr_t v)
```
<dl>
<dt>Description</dt><dd>
Multiplie un vecteur avec trois éléments par une matrice.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de trois flotteurs |
| m | adresse de 16 flotteurs |
| v | adresse de trois flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4v4

```c
void mulm4v4(addr_t dst, addr_t m, addr_t v)
```
<dl>
<dt>Description</dt><dd>
Multiplie un vecteur avec quatre éléments par une matrice.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de quatre flotteurs |
| m | adresse de 16 flotteurs |
| v | adresse de quatre flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [invm4], [trpm4]
</dd>
</dl>
<hr>
## invm4

```c
void invm4(addr_t dst, addr_t a)
```
<dl>
<dt>Description</dt><dd>
Calcule la matrice inverse.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de 16 flotteurs |
| a | adresse de 16 flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [trpm4]
</dd>
</dl>
<hr>
## trpm4

```c
void trpm4(addr_t dst, addr_t a)
```
<dl>
<dt>Description</dt><dd>
Transposer la matrice.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de 16 flotteurs |
| a | adresse de 16 flotteurs |
</dd>
<dt>Voir aussi</dt><dd>
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
<dt>Description</dt><dd>
Traduisez un nuage de sommets, alias. placez un modèle 3D dans [espace 3D].
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | tableau de sommets de destination, 3 x 2 octets chacun, X, Y, Z |
| src | tableau de sommets source, 3 x 2 octets chacun, X, Y, Z |
| num | nombre de triplets de coordonnées de sommet dans le tableau |
| x | coordonnée X du monde, -32767 à 32767 |
| y | coordonnée Y du monde, -32767 à 32767 |
| z | coordonnée Z du monde, -32767 à 32767 |
| pitch | rotation autour de l'axe X en degrés, 0 à 359 |
| yaw | rotation autour de l'axe Y en degrés, 0 à 359 |
| roll | rotation autour de l'axe Z en degrés, 0 à 359 |
| scale | échelle, utilisez 1.0 pour conserver la taille d'origine |
</dd>
<dt>Voir aussi</dt><dd>
[mesh]
</dd>
</dl>

# Mémoire

## inb

```c
uint8_t inb(addr_t src)
```
<dl>
<dt>Description</dt><dd>
Lire dans un octet (byte) de la mémoire.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| src | adresse, 0x00000 à 0xBFFFF |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie la valeur à cette adresse.
</dd>
</dl>
<hr>
## inw

```c
uint16_t inw(addr_t src)
```
<dl>
<dt>Description</dt><dd>
Lire un mot (word, deux octets) de la mémoire.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| src | adresse, 0x00000 à 0xBFFFE |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie la valeur à cette adresse.
</dd>
</dl>
<hr>
## ini

```c
uint32_t ini(addr_t src)
```
<dl>
<dt>Description</dt><dd>
Lit un entier (int, quatre octets) depuis la mémoire.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| src | adresse, 0x00000 à 0xBFFFC |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie la valeur à cette adresse.
</dd>
</dl>
<hr>
## outb

```c
void outb(addr_t dst, uint8_t value)
```
<dl>
<dt>Description</dt><dd>
Écrivez un octet (byte) en mémoire.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse, 0x00000 à 0xBFFFF |
| value | valeur à définir, 0 à 255 |
</dd>
</dl>
<hr>
## outw

```c
void outw(addr_t dst, uint16_t value)
```
<dl>
<dt>Description</dt><dd>
Écrivez un mot (word, deux octets) en mémoire.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse, 0x00000 à 0xBFFFE |
| value | valeur à définir, 0 à 65535 |
</dd>
</dl>
<hr>
## outi

```c
void outi(addr_t dst, uint32_t value)
```
<dl>
<dt>Description</dt><dd>
Écrivez un entier (int, quatre octets) en mémoire.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse, 0x00000 à 0xBFFFC |
| value | valeur à définir, 0 à 4294967295 |
</dd>
</dl>
<hr>
## memsave

```c
int memsave(uint8_t overlay, addr_t src, uint32_t size)
```
<dl>
<dt>Description</dt><dd>
Enregistre la zone mémoire à superposer.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| overlay | indice de superposition dans lequel écrire, 0 à 255 |
| src | décalage de mémoire à partir duquel enregistrer, 0x00000 à 0xBFFFF |
| size | nombre d'octets à sauvegarder |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie 1 en cas de succès, 0 en cas d'erreur.
</dd>
<dt>Voir aussi</dt><dd>
[memload]
</dd>
</dl>
<hr>
## memload

```c
int memload(addr_t dst, uint8_t overlay, uint32_t maxsize)
```
<dl>
<dt>Description</dt><dd>
Charge une superposition dans la zone mémoire spécifiée.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | décalage de mémoire vers lequel charger, 0x00000 à 0xBFFFF |
| overlay | indice de superposition à lire, 0 à 255 |
| maxsize | nombre maximum d'octets à charger |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie le nombre d'octets réellement chargés.
</dd>
<dt>Voir aussi</dt><dd>
[memsave]
</dd>
</dl>
<hr>
## memcpy

```c
void memcpy(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Description</dt><dd>
Copiez les régions de mémoire.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de destination, 0x00000 à 0xBFFFF |
| src | adresse source, 0x00000 à 0xBFFFF |
| len | nombre d'octets à copier |
</dd>
</dl>
<hr>
## memset

```c
void memset(addr_t dst, uint8_t value, uint32_t len)
```
<dl>
<dt>Description</dt><dd>
Définissez la région mémoire sur une valeur donnée.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de destination, 0x00000 à 0xBFFFF |
| value | valeur à définir, 0 à 255 |
| len | nombre d'octets à définir |
</dd>
</dl>
<hr>
## memcmp

```c
int memcmp(addr_t addr0, addr_t addr1, uint32_t len)
```
<dl>
<dt>Description</dt><dd>
Comparez les régions de mémoire.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| addr0 | première adresse, 0x00000 à 0xBFFFF |
| addr1 | deuxième adresse, 0x00000 à 0xBFFFF |
| len | nombre d'octets à comparer |
</dd>
<dt>Valeur de retour</dt><dd>
Renvoie la différence, 0 si les deux régions de mémoire correspondent.
</dd>
</dl>
<hr>
## deflate

```c
int deflate(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Description</dt><dd>
Compressez un tampon à l'aide de RFC1950 deflate (zlib).
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de destination, 0x00000 à 0xBFFFF |
| src | adresse source, 0x00000 à 0xBFFFF |
| len | nombre d'octets à compresser |
</dd>
<dt>Valeur de retour</dt><dd>
0 ou négatif en cas d'erreur, sinon la longueur du tampon compressé et des données compressées en dst.
</dd>
<dt>Voir aussi</dt><dd>
[inflate]
</dd>
</dl>
<hr>
## inflate

```c
int inflate(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Description</dt><dd>
Décompressez un tampon avec des données compressées RFC1950 deflate (zlib).
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| dst | adresse de destination, 0x00000 à 0xBFFFF |
| src | adresse source, 0x00000 à 0xBFFFF |
| len | nombre d'octets compressés |
</dd>
<dt>Valeur de retour</dt><dd>
0 ou négatif en cas d'erreur, sinon la longueur du tampon non compressé et des données non compressées en dst.
</dd>
<dt>Voir aussi</dt><dd>
[deflate]
</dd>
</dl>
<hr>
## time

```c
float time(void)
```
<dl>
<dt>Description</dt><dd>
Renvoie le nombre de ticks depuis la mise sous tension.
</dd>
<dt>Valeur de retour</dt><dd>
Le temps écoulé en millisecondes depuis la mise sous tension.
</dd>
<dt>Voir aussi</dt><dd>
[now]
</dd>
</dl>
<hr>
## now

```c
uint32_t now(void)
```
<dl>
<dt>Description</dt><dd>
Renvoie l'horodatage UNIX. Vérifiez l'octet au décalage 0000C pour voir s'il déborde.
</dd>
<dt>Valeur de retour</dt><dd>
Temps écoulé en secondes depuis le 1er janvier 1970 à minuit, heure moyenne de Greenwich.
</dd>
<dt>Voir aussi</dt><dd>
[time]
</dd>
</dl>
<hr>
## atoi

```c
int atoi(str_t src)
```
<dl>
<dt>Description</dt><dd>
Convertit une chaîne décimale ASCII en nombre entier.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| src | adresse de chaîne, 0x00000 à 0xBFFFF |
</dd>
<dt>Valeur de retour</dt><dd>
La valeur numérique de la chaîne.
</dd>
<dt>Voir aussi</dt><dd>
[itoa], [str], [val]
</dd>
</dl>
<hr>
## itoa

```c
str_t itoa(int value)
```
<dl>
<dt>Description</dt><dd>
Convertit un nombre entier en chaîne décimale ASCII.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| value | la valeur, -2147483648 à 2147483647 |
</dd>
<dt>Valeur de retour</dt><dd>
La chaîne convertie.
</dd>
<dt>Voir aussi</dt><dd>
[atoi], [str], [val]
</dd>
</dl>
<hr>
## val

```c
float val(str_t src)
```
<dl>
<dt>Description</dt><dd>
Convertit une chaîne décimale ASCII en nombre à virgule flottante.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| src | adresse de chaîne, 0x00000 à 0xBFFFF |
</dd>
<dt>Valeur de retour</dt><dd>
La valeur numérique de la chaîne.
</dd>
<dt>Voir aussi</dt><dd>
[itoa], [atoi], [str]
</dd>
</dl>
<hr>
## str

```c
str_t str(float value)
```
<dl>
<dt>Description</dt><dd>
Convertit un nombre à virgule flottante en chaîne décimale ASCII.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| value | la valeur |
</dd>
<dt>Valeur de retour</dt><dd>
La chaîne convertie.
</dd>
<dt>Voir aussi</dt><dd>
[atoi], [itoa], [val]
</dd>
</dl>
<hr>
## sprintf

```c
str_t sprintf(str_t fmt, ...)
```
<dl>
<dt>Description</dt><dd>
Renvoie une chaîne UTF-8 terminée par zéro créée à l'aide du format et des arguments.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| fmt | chaîne à afficher, une [formater la chaîne] |
| ... | arguments facultatifs |
</dd>
<dt>Valeur de retour</dt><dd>
Chaîne construite.
</dd>
</dl>
<hr>
## strlen

```c
int strlen(str_t src)
```
<dl>
<dt>Description</dt><dd>
Renvoie le nombre d'octets dans une chaîne (sans le zéro final).
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| src | adresse de chaîne, 0x00000 à 0xBFFFF |
</dd>
<dt>Valeur de retour</dt><dd>
Le nombre d'octets dans la chaîne.
</dd>
<dt>Voir aussi</dt><dd>
[mblen]
</dd>
</dl>
<hr>
## mblen

```c
int mblen(str_t src)
```
<dl>
<dt>Description</dt><dd>
Renvoie le nombre de caractères multi-octets UTF-8 dans une chaîne (sans le zéro final).
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| src | adresse de chaîne, 0x00000 à 0xBFFFF |
</dd>
<dt>Valeur de retour</dt><dd>
Le nombre de caractères dans la chaîne.
</dd>
<dt>Voir aussi</dt><dd>
[strlen]
</dd>
</dl>
<hr>
## malloc

```c
addr_t malloc(uint32_t size)
```
<dl>
<dt>Description</dt><dd>
Alloue la mémoire utilisateur de manière dynamique.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| size | nombre d'octets à allouer |
</dd>
<dt>Valeur de retour</dt><dd>
Adresse du nouveau buffer alloué ou NULL en cas d'erreur.
</dd>
<dt>Voir aussi</dt><dd>
[realloc], [free]
</dd>
</dl>
<hr>
## realloc

```c
addr_t realloc(addr_t addr, uint32_t size)
```
<dl>
<dt>Description</dt><dd>
Redimensionnez un tampon précédemment alloué.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| addr | adresse du tampon alloué |
| size | nombre d'octets à redimensionner |
</dd>
<dt>Valeur de retour</dt><dd>
Adresse du nouveau buffer alloué ou NULL en cas d'erreur.
</dd>
<dt>Voir aussi</dt><dd>
[malloc], [free]
</dd>
</dl>
<hr>
## free

```c
int free(addr_t addr)
```
<dl>
<dt>Description</dt><dd>
Libère la mémoire utilisateur allouée dynamiquement.
</dd>
<dt>Paramètres</dt><dd>
| Argument | Description |
| addr | adresse du tampon alloué |
</dd>
<dt>Valeur de retour</dt><dd>
1 en cas de succès, 0 en cas d'erreur.
</dd>
<dt>Voir aussi</dt><dd>
[malloc], [realloc]
</dd>
</dl>
