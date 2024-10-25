# Mapa de memoria

## Varios

Todos los valores son little endian, por lo que el dígito más pequeño se almacena en la dirección más pequeña.

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  00000 |          1 | MEG-4 versión de firmware mayor                                    |
|  00001 |          1 | MEG-4 versión de firmware minor                                    |
|  00002 |          1 | MEG-4 versión de firmware bugfix                                   |
|  00003 |          1 | contador de rendimiento, tiempo no utilizado en 1/1000 segundos    |
|  00004 |          4 | número de tics de 1/1000 de segundo desde el encendido             |
|  00008 |          8 | marca de tiempo UTC Unix                                           |
|  00010 |          2 | localidad actual                                                   |

El contador de rendimiento muestra el tiempo no utilizado cuando se generó el último fotograma. Si esto es cero o negativo,
entonces significa cuánto ha excedido su función loop() su período de tiempo disponible.

## Puntero

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  00012 |          2 | estado de los botones de puntero (consulte [getbtn] y [getclk])    |
|  00014 |          2 | índice de sprites de puntero                                       |
|  00016 |          2 | puntero X coordenada                                               |
|  00018 |          2 | puntero Y coordenada                                               |

Los botones del puntero son los siguientes:

| Define  | Bitmask   | Descripción                                                        |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | Boton izquierdo del raton                                          |
| `BTN_M` |         2 | Botón central del ratón                                            |
| `BTN_R` |         4 | Botón derecho del mouse                                            |
| `SCR_U` |         8 | Desplazarse hacia arriba                                           |
| `SCR_D` |        16 | Desplazarse hacia abajo                                            |
| `SCR_L` |        32 | Desplazarse hacia la izquierda                                     |
| `SCR_R` |        64 | Desplazarse hacia la derecha                                       |

Los bits superiores del índice de sprites del puntero se utilizan para puntos de acceso: bit 13-15 hotspot Y, bit 10-12 hotspot X,
bit 0-9 sprite. Hay algunos cursores integrados predefinidos:

| Define       | Valor     | Descripción                                                   |
|--------------|----------:|---------------------------------------------------------------|
| `PTR_NORM`   |      03fb | Puntero normal (flecha)                                       |
| `PTR_TEXT`   |      03fc | Puntero de texto                                              |
| `PTR_HAND`   |      0bfd | Puntero de enlace                                             |
| `PTR_ERR`    |      93fe | Puntero de error                                              |
| `PTR_NONE`   |      ffff | El puntero está escondido                                     |

## Teclado

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0001A |          1 | rabo de cola de teclado                                            |
|  0001B |          1 | cabeza de cola de teclado                                          |
|  0001C |         64 | cola de teclado, 16 elementos, cada 4 bytes (consulte [popkey])    |
|  0005C |         18 | estado presionado por códigos de escaneo (consulte [getkey])       |

Las claves extraídas de la cola se representan en UTF-8. Algunas secuencias UTF-8 no válidas representan claves especiales
(no imprimibles), por ejemplo:

| Keycode | Descripción                                     |
|---------|-------------------------------------------------|
| `\x8`   | El carácter 8, tecla <kbd>←Backspace</kbd>      |
| `\x9`   | El carácter 9, tecla <kbd>Tab</kbd>             |
| `\n`    | El carácter 10, tecla <kbd>⏎Enter</kbd>         |
| `\x1b`  | El carácter 27, tecla <kbd>Esc</kbd>            |
| `Del`   | La tecla <kbd>Del</kbd>                         |
| `Up`    | La flecha del cursor <kbd>▴</kbd>               |
| `Down`  | La flecha del cursor <kbd>▾</kbd>               |
| `Left`  | La flecha del cursor <kbd>◂</kbd>               |
| `Rght`  | La flecha del cursor <kbd>▸</kbd>               |
| `Cut`   | La tecla Cut (o <kbd>Ctrl</kbd>+<kbd>X</kbd>)   |
| `Cpy`   | La tecla Copy (o <kbd>Ctrl</kbd>+<kbd>C</kbd>)  |
| `Pst`   | La tecla Paste (o <kbd>Ctrl</kbd>+<kbd>V</kbd>) |

Los códigos de escaneo son los siguientes:

| ScanCode | Offset  | Bitmask | Define            |
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

## Mando de juegos

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0006E |          2 | umbral del joystick (por defecto 8000)                             |
|  00070 |          8 | gamepad principal: asignaciones de códigos de escaneo del teclado (ver [teclado]) |
|  00078 |          4 | Estado presionado del botón de 4 gamepads (consulte [getpad])      |

Los botones del gamepad son los siguientes:

| Define  | Bitmask   | Descripción                                                        |
|---------|----------:|--------------------------------------------------------------------|
| `BTN_L` |         1 | El botón `◁` o joystick hacia la izquierda                        |
| `BTN_U` |         2 | El botón `△` o joystick hacia arriba                              |
| `BTN_R` |         4 | El botón `▷` o joystick derecha                                   |
| `BTN_D` |         8 | El botón `▽` o joystick hacia abajo                               |
| `BTN_A` |        16 | El botón `Ⓐ`                                                       |
| `BTN_B` |        32 | El botón `Ⓑ`                                                       |
| `BTN_X` |        64 | El botón `Ⓧ`                                                       |
| `BTN_Y` |       128 | El botón `Ⓨ`                                                       |

La secuencia `△△▽▽◁▷◁▷ⒷⒶ` hace que se presione la "tecla" `KEY_CHEAT`.

## Unidad de Procesamiento Gráfico

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0007E |          1 | bits superiores del punto de código UNICODE para mapeo de glifos de fuentes |
|  0007F |          1 | selector de banco de sprites para el mapa                          |
|  00080 |       1024 | paleta, 256 colores, cada entrada 4 bytes, RGBA                    |
|  00480 |          2 | x0, área de recorte X comienza en píxeles (para todas las funciones) |
|  00482 |          2 | x1, área de recorte X final en píxeles                             |
|  00484 |          2 | y0, área de recorte X comienza en píxeles                          |
|  00486 |          2 | y1, área de recorte X final en píxeles                             |
|  00488 |          2 | se muestra el desplazamiento de vram X en píxeles o 0xffff         |
|  0048A |          2 | se muestra el desplazamiento de vram Y en píxeles o 0xffff         |
|  0048C |          1 | corral de tortugas abajo (consulte [up], [down])                   |
|  0048D |          1 | color de tortuga, índice de paleta 0 a 255 (consulte [color])      |
|  0048E |          2 | dirección de tortuga en grados, 0 a 359 (consulte [left], [right]) |
|  00490 |          2 | desplazamiento de tortuga X en píxeles (consulte [move])           |
|  00492 |          2 | desplazamiento de tortuga Y en píxeles                             |
|  00494 |          2 | velocidad al caminar en el laberinto en 1/128 mosaicos (consulte [maze]) |
|  00496 |          2 | velocidad de rotación del laberinto en grados (1 a 90)             |
|  00498 |          1 | color de primer plano de consola, índice de paleta de 0 a 255      |
|  00499 |          1 | color de fondo de consola, índice de paleta 0 a 255 (consulte [printf]) |
|  0049A |          2 | desplazamiento de la consola X en píxeles                          |
|  0049C |          2 | desplazamiento de la consola Y en píxeles                          |
|  0049E |          2 | cámara X desplazada en [espacio 3D] (consulte [tri3d], [tritx], [mesh]) |
|  004A0 |          2 | cámara Y desplazada                                                |
|  004A2 |          2 | cámara Z desplazada                                                |
|  004A4 |          2 | dirección de la cámara, tono (0 arriba, 90 adelante)               |
|  004A6 |          2 | dirección de la cámara, guiñada (0 izquierda, 90 adelante)         |
|  004A8 |          1 | campo de visión de la cámara en ángulos (45, negativo ortográfico) |
|  004AA |          2 | posición de la fuente de luz X offset (consulte [tri3d], [tritx], [mesh]) |
|  004AC |          2 | posición de la fuente de luz Y offset                              |
|  004AE |          2 | posición de la fuente de luz Z offset                              |
|  00600 |      64000 | mapa, índices de sprites de 320 x 200 (consulte [map] y [maze])    |
|  10000 |      65536 | sprites, 256 x 256 índices de paleta, 1024 8 x 8 píxeles (consulte [spr]) |
|  28000 |       2048 | ventana para glifos de fuente 4096 (ver 0007E, [width] y [text])   |

## Procesador de Señal Digital

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  0007C |          1 | selector de banco de formas de onda (1 a 31)                       |
|  0007D |          1 | selector de banco de pistas de música (0 a 7)                      |
|  004BA |          1 | tempo actual (en ticks por fila, solo lectura)                     |
|  004BB |          1 | pista actual que se está reproduciendo (solo lectura)              |
|  004BC |          2 | fila actual que se está reproduciendo (solo lectura)               |
|  004BE |          2 | número total de filas en la pista actual (solo lectura)            |
|  004C0 |         64 | 16 registros de estado de canal, cada uno de 4 bytes (solo lectura) |
|  00500 |        256 | 64 efectos de sonido, cada uno de 4 bytes                          |
|  20000 |      16384 | ventana para muestras de formas de onda (ver 0007C)                |
|  24000 |      16384 | ventana para patrones musicales (ver 0007D)                        |

Todos los registros de estado del DSP son de solo lectura y para cada canal tienen el siguiente aspecto:

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | posición actual en la forma de onda que se está reproduciendo      |
|      2 |          1 | forma de onda actual (1 a 31, 0 si el canal está en silencio)      |
|      3 |          1 | volumen actual (0 significa que el canal está apagado)             |

Los primeros 4 canales son para la música, el resto para los efectos de sonido.

Tenga en cuenta que el índice de forma de onda 0 significa "usar la forma de onda anterior", por lo que el índice 0 no se
puede utilizar en el selector. El formato de cualquier otra forma de onda:

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          2 | número de muestras                                                 |
|      2 |          2 | inicio de bucle                                                    |
|      4 |          2 | longitud del bucle                                                 |
|      6 |          1 | valor de ajuste fino, -8 a 7                                       |
|      7 |          1 | volumen, 0 a 64                                                    |
|      8 |      16376 | muestras mono de 8 bits firmadas                                   |

El formato de los efectos de sonido y las pistas de música son los mismos, la única diferencia es que las pistas de música tienen
4 notas por fila, uno para cada canal y hay 1024 filas; mientras que para los efectos de sonido solo hay una nota y 64 filas.

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|      0 |          1 | número de nota, consulte `NOTE_x` define, 0 a 96                   |
|      1 |          1 | índice de forma de onda, 0 a 31                                    |
|      2 |          1 | tipo de efecto, 0 a 255 (consulte [efectos de sonido])             |
|      3 |          1 | parámetro de efecto                                                |

El conteo de notas es el siguiente: 0 significa que no hay notas colocadas. Seguido de 8 octavas, cada una con 12 notas, por lo
que 1 equivale a C-0, 12 es B-0 (en la octava más baja), 13 es C-1 (una octava más alta) y 14 es C#1 (Do sostenido, semitono
más alto). Por ejemplo, la nota D en la cuarta octava sería 1 + 4\*12 + 2 = 51. La nota B-7 es 96, la nota más alta de la
octava más alta. También tiene definiciones integradas, por ejemplo, C-1 es `NOTE_C_1` y C#1 es `NOTE_Cs1`. Si no desea contar,
puede usarlas también en su programa.

## Efectos de sonido

Para simplificar, MEG-4 utiliza los mismos códigos que el archivo Amiga MOD (de esta manera verás lo mismo en el editor integrado
y en un rastreador de música de terceros), pero no los admite todos. Como se dijo anteriormente, estos códigos están representados
por tres números hexadecimales, siendo el primero el tipo `t` y los dos últimos el parámetro `xy` (o `xx`). Todos los tipos `E1` a
`ED` se almacenan en el byte de tipo, aunque parece que uno de sus nibbles podría pertenecer al parámetro, pero no lo es.

| Efecto | Código | Descripción                                              |
|--------|------|------------------------------------------------------------|
| ...    | 000  | Sin efecto                                                 |
| Arp    | 0xy  | Arpeggio, tocar nota, nota+x semitono y nota+y semitono    |
| Po/    | 1xx  | Portamento arriba, deslizar el punto por x arriba          |
| Po\\   | 2xx  | Portamento abajo, deslizar el punto por x abajo            |
| Ptn    | 3xx  | Tono portamento, período de diapositiva al período x       |
| Vib    | 4xy  | Vibrato, oscilar el tono en y semitonos a x frecuencia     |
| Ctv    | 5xy  | Continuar Portamento de tono + deslizamiento de volumen x arriba o y abajo |
| Cvv    | 6xy  | Continuar Vibrato + deslizar el volumen por x arriba o por y abajo |
| Trm    | 7xy  | Tremolo, oscilar el volumen por amplitud y en x frecuencia |
| Ofs    | 9xx  | Establecer el desplazamiento de muestra en x \* 256        |
| Vls    | Axy  | Desliza el volumen x hacia arriba o y hacia abajo          |
| Jmp    | Bxx  | Salto de posición, establezca la fila en x \* 64           |
| Vol    | Cxx  | Establecer el volumen en x                                 |
| Fp/    | E1x  | Portamento fino hacia arriba, aumentar el período en x     |
| Fp\\   | E2x  | Portamento fino hacia abajo, disminuir el período en x     |
| Svw    | E4x  | Forma de onda de vibrato, 0 sinusoidal, 1 de sierra, 2 cuadrada, 3 de ruido |
| Ftn    | E5x  | Establecer ajuste fino, cambiar el ajuste por x (-8 a 7)   |
| Stw    | E7x  | Forma de onda de tremolo, 0 sinusoidal, 1 de sierra, 2 cuadrada, 3 de ruido |
| Rtg    | E9x  | Volver a activar la nota, activar la muestra actual cada x ticks |
| Fv/    | EAx  | Volumen fino deslizar hacia arriba, aumentar en x          |
| Fv\\   | EBx  | Deslice el volumen fino hacia abajo, disminuya en x        |
| Cut    | ECx  | Cortar nota en x ticks                                     |
| Dly    | EDx  | Nota de retraso en x ticks                                 |
| Tpr    | Fxx  | Establezca el número de ticks por fila en x (predeterminado 6) |

## Memoria de usuario

Las direcciones de memoria de 00000 a 2FFFF pertenecen al MMIO, todo lo anterior (a partir de 30000 o `MEM_USER`) es memoria
de usuario de libre uso.

| Offset | Tamaño     | Descripción                                                        |
|--------|-----------:|--------------------------------------------------------------------|
|  30000 |          4 | (solo BASIC) compensación de DATA                                  |
|  30004 |          4 | (solo BASIC) contador READ actual                                  |
|  30008 |          4 | (solo BASIC) READ máxima, número de DATA                           |

A esto le siguen las variables globales que ha declarado en su programa, seguidas de las constantes, como cadenas literales.
En el caso de BASIC, a esto le siguen los registros de DATA reales.

Las direcciones de memoria por encima de los datos inicializados se pueden asignar y liberar dinámicamente en su programa mediante
las llamadas [malloc] y [free].

Por último, la pila, que está en la parte superior (comenzando desde C0000 o `MEM_LIMIT`) y creciendo *hacia abajo*. Las variables
locales de tu programa (que declaraste dentro de una función) van aquí. El tamaño de la pila siempre cambia dependiendo de qué
función llama a qué otra función en su programa.

Si por casualidad la parte superior de los datos asignados dinámicamente y la parte inferior de la pila se superponen, entonces
MEG-4 arroja un error de "Memoria insuficiente".

## Cadena de formato

Algunas funciones, [printf], [sprintf] y [trace] utilizan una cadena de formato que puede contener caracteres especiales para hacer
referencia a argumentos y describir cómo mostrarlos. Estos son:

| Código | Descripción                                              |
|------|------------------------------------------------------------|
| `%%` | El carácter `%`                                            |
| `%d` | Siguiente parámetro como un número decimal                 |
| `%u` | Siguiente parámetro como un número decimal sin signo       |
| `%x` | Siguiente parámetro como un número hexadecimal             |
| `%o` | Siguiente parámetro como un número octal                   |
| `%b` | Siguiente parámetro como un número binario                 |
| `%f` | Siguiente parámetro como un número de punto flotante       |
| `%s` | Siguiente parámetro como una cadena                        |
| `%c` | Siguiente parámetro como carácter UTF-8                    |
| `%p` | Siguiente parámetro como dirección (puntero)               |
| `\t` | Tab, fija la posición vertical antes de continuar          |
| `\n` | Iniciar una nueva línea para imprimir                      |

Puede agregar relleno especificando la longitud entre `%` y el código. Si comienza con `0`, entonces el valor se completará con ceros;
de lo contrario, con espacios. Por ejemplo, `%4d` rellenará el valor de la derecha con espacios y `%04x` con ceros. La `f` acepta
un número después de un punto, que indica el número de dígitos en la parte fraccionaria (hasta 8), por ejemplo. `%.6f`.

## Espacio 3D

En MEG-4, el espacio tridimensional se maneja según la regla de la mano derecha: +X está a la derecha, +Y está arriba y +Z está
hacia el espectador.

```
  +Y
   |
   |__ +X
  /
+Z
```

Cada punto debe colocarse en el rango -32767 a +32767. La forma en que se proyecta este mundo 3D en su pantalla 2D depende de
cómo configure la cámara (consulte la dirección de [Unidad de Procesamiento Gráfico] 0049E). Eso sí, hay que situar la cámara
en el mundo, con coordenadas X, Y, Z. Luego tienes que saber hacia dónde mira la cámara, usando cabeceo y guiñada. Finalmente
también hay que indicar qué tipo de lente tiene la cámara, especificando el ángulo del campo de visión. Este último normalmente
debería estar entre 30 (muy estrecho) y 180 grados (como peces y pájaros). MEG-4 admite hasta 127 grados, pero hay un truco.
Los valores FOV positivos se proyectarán como perspectiva (cuanto más lejos esté el objeto, más pequeño es), pero los valores
negativos también se manejarán, solo con proyección ortográfica (no importa la distancia, el tamaño del objeto será el mismo).
La perspectiva se utiliza en los juegos FPS, mientras que la proyección ortográfica es la preferida en los juegos de estrategia.

Puede mostrar un conjunto de triángulos (un modelo 3D completo) usando la función [mesh] de manera eficiente. Debido a que los
modelos probablemente tengan coordenadas locales, eso dibujaría todos los modelos uno encima de otro alrededor del origo.
Entonces, si desea mostrar varios modelos en el mundo, primero debe traducirlos (colocarlos) en coordenadas mundiales usando
[trns], y luego usar la nube de vértices traducida con [mesh] (mover y rotar el modelo no cambiar los triángulos, sólo sus
coordenadas de vértice).

## Atajos del editor de código

Atajos de [teclado] adicionales que también puede utilizar al editar el código fuente:

| Tecla | Descripción |
|------------------------------|---------------------------------------------------------------------------------------|
| <kbd>Ctrl</kbd>+<kbd>F</kbd> | Buscar cadena |
| <kbd>Ctrl</kbd>+<kbd>G</kbd> | Buscar de nuevo |
| <kbd>Ctrl</kbd>+<kbd>H</kbd> | Buscar y reemplazar (en el texto seleccionado o, en su defecto, en todo el código fuente) |
| <kbd>Ctrl</kbd>+<kbd>J</kbd> | Ir a la línea |
| <kbd>Ctrl</kbd>+<kbd>D</kbd> | Ir a la definición de función |
| <kbd>Ctrl</kbd>+<kbd>N</kbd> | Lista de marcadores |
| <kbd>Ctrl</kbd>+<kbd>B</kbd> | Activar o desactivar marcador en la línea actual |
| <kbd>Ctrl</kbd>+<kbd>▴</kbd> | Ir al marcador anterior |
| <kbd>Ctrl</kbd>+<kbd>▾</kbd> | Ir al siguiente marcador |
| <kbd>Ctrl</kbd>+<kbd>,</kbd> | Disminuir la sangría de la selección |
| <kbd>Ctrl</kbd>+<kbd>.</kbd> | Aumentar la sangría de la selección |
| <kbd>Inicio</kbd> | Mover el cursor al principio de la línea |
| <kbd>Fin</kbd> | Mueve el cursor al final de la línea |
| <kbd>RePág</kbd> | Mueve el cursor 42 líneas (una página) hacia arriba |
| <kbd>AvPág</kbd> | Mueve el cursor 42 líneas (una página) hacia abajo |
| <kbd>F1</kbd> | Si el cursor está en la lista de argumentos de una API, entonces ve a la página de ayuda integrada de la función |

Consulta también el menú para conocer los métodos de entrada alternativos y sus atajos de teclado.

# Consola

## putc

```c
void putc(uint32_t chr)
```
<dl>
<dt>Descripción</dt><dd>
Imprime un personaje en la consola.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| chr | Carácter UTF-8 |
</dd>
</dl>
<hr>
## printf

```c
void printf(str_t fmt, ...)
```
<dl>
<dt>Descripción</dt><dd>
Imprime texto en la consola.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| fmt | cadena para mostrar, [cadena de formato] |
| ... | argumentos opcionales |
</dd>
</dl>
<hr>
## getc

```c
uint32_t getc(void)
```
<dl>
<dt>Descripción</dt><dd>
Lee un carácter de la consola, bloquea el programa cuando no hay entrada.
</dd>
<dt>Valor de retorno</dt><dd>
Un carácter UTF-8 que la usuario ingresó.
</dd>
<dt>Ver también</dt><dd>
[popkey]
</dd>
</dl>
<hr>
## gets

```c
str_t gets(void)
```
<dl>
<dt>Descripción</dt><dd>
Lee una cadena terminada en nueva línea del usuario (no devuelve la nueva línea).
</dd>
<dt>Valor de retorno</dt><dd>
Los bytes leídos en una cadena.
</dd>
</dl>
<hr>
## trace

```c
void trace(str_t fmt, ...)
```
<dl>
<dt>Descripción</dt><dd>
Seguimiento de la ejecución imprimiendo en stdout. Solo funciona si `meg4` se inició con el indicador detallado `-v`.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| fmt | cadena para mostrar, [cadena de formato] |
| ... | argumentos opcionales |
</dd>
</dl>
<hr>
## delay

```c
void delay(uint16_t msec)
```
<dl>
<dt>Descripción</dt><dd>
Retrasa la ejecución del programa.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| msec | retraso en milisegundos |
</dd>
</dl>
<hr>
## exit

```c
void exit(void)
```
<dl>
<dt>Descripción</dt><dd>
Sale del programa.
</dd>
</dl>

# Audio

## sfx

```c
void sfx(uint8_t sfx, uint8_t channel, uint8_t volume)
```
<dl>
<dt>Descripción</dt><dd>
Reproduce un efecto de sonido.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| sfx | el índice del efecto de sonido, de 0 a 63 |
| channel | canal a utilizar, 0 a 11 |
| volume | volumen a utilizar, 0 a 255, 0 apaga el canal |
</dd>
</dl>
<hr>
## music

```c
void music(uint8_t track, uint16_t row, uint8_t volume)
```
<dl>
<dt>Descripción</dt><dd>
Reproduce una pista de música.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| track | el índice de la pista de música, de 0 a 7 |
| row | fila para comenzar a reproducir, 0 a 1023 (duración máxima de la canción) |
| volume | volumen a utilizar, 0 a 255, 0 apaga la música |
</dd>
</dl>

# GPIO

## gpio_rev

```c
uint32_t gpio_rev(void)
```
<dl>
<dt>Descripción</dt><dd>
Consulta el número de revisión de la placa GPIO. Devuelve 0 si la plataforma no es compatible con GPIO.
</dd>
<dt>Valor de retorno</dt><dd>
Número de revisión de la placa o 0 si no es compatible.
</dd>
</dl>
<hr>
## gpio_get

```c
int gpio_get(uint8_t pin)
```
<dl>
<dt>Descripción</dt><dd>
Lea el valor de un pin GPIO.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| pin | número de pin físico, del 1 al 40 |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve 1 si el pin está alto, 0 si está bajo, -1 en caso de error (el pin GPIO no es compatible).
</dd>
<dt>Ver también</dt><dd>
[gpio_set]
</dd>
</dl>
<hr>
## gpio_set

```c
int gpio_set(uint8_t pin, int value)
```
<dl>
<dt>Descripción</dt><dd>
Escriba el valor en un pin GPIO.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| pin | número de pin físico, del 1 al 40 |
| value | 1 para establecer el pin alto, 0 para bajo |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve 0 en caso de éxito, -1 en caso de error (el pin GPIO no es compatible).
</dd>
<dt>Ver también</dt><dd>
[gpio_get]
</dd>
</dl>

# Gráficos

## cls

```c
void cls(uint8_t palidx)
```
<dl>
<dt>Descripción</dt><dd>
Borra toda la pantalla y restablece las compensaciones de visualización, también establece el color de fondo de la consola.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
</dd>
<dt>Ver también</dt><dd>
[pget], [pset]
</dd>
</dl>
<hr>
## cget

```c
uint32_t cget(uint16_t x, uint16_t y)
```
<dl>
<dt>Descripción</dt><dd>
Obtenga un píxel en una coordenada y devuelva el color RGBA.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| x | Coordenada X en píxeles |
| y | Coordenada Y en píxeles |
</dd>
<dt>Valor de retorno</dt><dd>
Un color empaquetado, con canales RGBA (el rojo está en el byte menos significativo).
</dd>
<dt>Ver también</dt><dd>
[cls], [pget], [pset]
</dd>
</dl>
<hr>
## pget

```c
uint8_t pget(uint16_t x, uint16_t y)
```
<dl>
<dt>Descripción</dt><dd>
Obtenga un píxel en una coordenada y devuelva su índice de paleta.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| x | Coordenada X en píxeles |
| y | Coordenada Y en píxeles |
</dd>
<dt>Valor de retorno</dt><dd>
Color en índice de paleta, 0 a 255.
</dd>
<dt>Ver también</dt><dd>
[cls], [pset], [cget]
</dd>
</dl>
<hr>
## pset

```c
void pset(uint8_t palidx, uint16_t x, uint16_t y)
```
<dl>
<dt>Descripción</dt><dd>
Traza un píxel en una coordenada.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x | Coordenada X en píxeles |
| y | Coordenada Y en píxeles |
</dd>
<dt>Ver también</dt><dd>
[cls], [pget]
</dd>
</dl>
<hr>
## width

```c
uint16_t width(int8_t type, str_t str)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el ancho del texto mostrado en píxeles.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| type | tipo de fuente, -4 a 4 |
| str | cuerda para medir |
</dd>
<dt>Valor de retorno</dt><dd>
Número de píxeles necesarios para mostrar texto.
</dd>
<dt>Ver también</dt><dd>
[text]
</dd>
</dl>
<hr>
## text

```c
void text(uint8_t palidx, int16_t x, int16_t y, int8_t type, uint8_t shidx, uint8_t sha, str_t str)
```
<dl>
<dt>Descripción</dt><dd>
Imprime texto en pantalla.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x | Coordenada X en píxeles |
| y | Coordenada Y en píxeles |
| type | tipo de fuente, -4 a -1 monoespaciado, 1 a 4 proporcional |
| shidx | color de la sombra, índice de paleta 0 a 255 |
| sha | alfa de la sombra, 0 (completamente transparente) a 255 (completamente opaca) |
| str | cadena para mostrar |
</dd>
<dt>Ver también</dt><dd>
[width]
</dd>
</dl>
<hr>
## line

```c
void line(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja una línea antialias.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X inicial en píxeles |
| y0 | coordenada Y inicial en píxeles |
| x1 | coordenada X final en píxeles |
| y1 | coordenada Y final en píxeles |
</dd>
<dt>Ver también</dt><dd>
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
<dt>Descripción</dt><dd>
Dibuja una curva de Bézier cuadrática.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X inicial en píxeles |
| y0 | coordenada Y inicial en píxeles |
| x1 | coordenada X final en píxeles |
| y1 | coordenada Y final en píxeles |
| cx | punto de control coordenada X en píxeles |
| cy | punto de control coordenada Y en píxeles |
</dd>
<dt>Ver también</dt><dd>
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
<dt>Descripción</dt><dd>
Dibuja una curva de Bézier cúbica.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X inicial en píxeles |
| y0 | coordenada Y inicial en píxeles |
| x1 | coordenada X final en píxeles |
| y1 | coordenada Y final en píxeles |
| cx0 | primer punto de control coordenada X en píxeles |
| cy0 | primer punto de control coordenada Y en píxeles |
| cx1 | segundo punto de control coordenada X en píxeles |
| cy1 | segundo punto de control coordenada Y en píxeles |
</dd>
<dt>Ver también</dt><dd>
[line], [qbez]
</dd>
</dl>
<hr>
## tri

```c
void tri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja un triángulo.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X del primer borde en píxeles |
| y0 | coordenada Y del primer borde en píxeles |
| x1 | coordenada X del segundo borde en píxeles |
| y1 | coordenada Y del segundo borde en píxeles |
| x2 | coordenada X del tercer borde en píxeles |
| y2 | coordenada Y del tercer borde en píxeles |
</dd>
<dt>Ver también</dt><dd>
[ftri], [tri2d], [tri3d], [tritx], [mesh], [trns]
</dd>
</dl>
<hr>
## ftri

```c
void ftri(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja un triángulo relleno.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X del primer borde en píxeles |
| y0 | coordenada Y del primer borde en píxeles |
| x1 | coordenada X del segundo borde en píxeles |
| y1 | coordenada Y del segundo borde en píxeles |
| x2 | coordenada X del tercer borde en píxeles |
| y2 | coordenada Y del tercer borde en píxeles |
</dd>
<dt>Ver también</dt><dd>
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
<dt>Descripción</dt><dd>
Dibuja un triángulo relleno con degradados de color.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| pi0 | color del primer borde, índice de paleta 0 a 255 |
| x0 | coordenada X del primer borde en píxeles |
| y0 | coordenada Y del primer borde en píxeles |
| pi1 | color del segundo borde, índice de paleta 0 a 255 |
| x1 | coordenada X del segundo borde en píxeles |
| y1 | coordenada Y del segundo borde en píxeles |
| pi2 | color del tercer borde, índice de paleta 0 a 255 |
| x2 | coordenada X del tercer borde en píxeles |
| y2 | coordenada Y del tercer borde en píxeles |
</dd>
<dt>Ver también</dt><dd>
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
<dt>Descripción</dt><dd>
Dibuja un triángulo relleno con degradados de color en [espacio 3D].
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| pi0 | color del primer borde, índice de paleta 0 a 255 |
| x0 | coordenada X del primer borde en píxeles |
| y0 | coordenada Y del primer borde en píxeles |
| z0 | coordenada Z del primer borde en píxeles |
| pi1 | color del segundo borde, índice de paleta 0 a 255 |
| x1 | coordenada X del segundo borde en píxeles |
| y1 | coordenada Y del segundo borde en píxeles |
| z1 | coordenada Z del segundo borde en píxeles |
| pi2 | color del tercer borde, índice de paleta 0 a 255 |
| x2 | coordenada X del tercer borde en píxeles |
| y2 | coordenada Y del tercer borde en píxeles |
| z2 | coordenada Z del tercer borde en píxeles |
</dd>
<dt>Ver también</dt><dd>
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
<dt>Descripción</dt><dd>
Dibuja un triángulo texturizado en [espacio 3D].
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| u0 | textura del primer borde coordenada X 0 a 255 |
| v0 | textura del primer borde coordenada Y 0 a 255 |
| x0 | coordenada X del primer borde en el espacio |
| y0 | coordenada Y del primer borde en el espacio |
| z0 | coordenada Z del primer borde en el espacio |
| u1 | textura del segundo borde coordenada X 0 a 255 |
| v1 | textura del segundo borde coordenada Y 0 a 255 |
| x1 | coordenada X del segundo borde en el espacio |
| y1 | coordenada Y del segundo borde en el espacio |
| z1 | coordenada Z del segundo borde en el espacio |
| u2 | textura del tercer borde coordenada X 0 a 255 |
| v2 | textura del tercer borde coordenada Y 0 a 255 |
| x2 | coordenada X del tercer borde en el espacio |
| y2 | coordenada Y del tercer borde en el espacio |
| z2 | coordenada Z del tercer borde en el espacio |
</dd>
<dt>Ver también</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [mesh], [trns]
</dd>
</dl>
<hr>
## mesh

```c
void mesh(addr_t verts, addr_t uvs, uint16_t numtri, addr_t tris)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja una malla hecha de triángulos en [espacio 3D], usando índices para vértices y coordenadas de textura (o paleta).
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| verts | dirección de la matriz de vértices, 3 x 2 bytes cada uno, X, Y, Z |
| uvs | dirección de la matriz UV (si es 0, entonces se usa paleta), 2 x 1 bytes cada uno, textura X, Y |
| numtri | numero de triangulos |
| tris | dirección de matriz de triángulos con índices, 6 x 1 bytes cada uno, vi1, ui1/pi1, vi2, ui2/pi2, vi3, ui3/pi3 |
</dd>
<dt>Ver también</dt><dd>
[tri], [ftri], [tri2d], [tri3d], [tritx], [trns]
</dd>
</dl>
<hr>
## rect

```c
void rect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja un rectángulo.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X superior izquierda en píxeles |
| y0 | coordenada Y superior izquierda en píxeles |
| x1 | coordenada X inferior derecha en píxeles |
| y1 | coordenada Y inferior derecha en píxeles |
</dd>
<dt>Ver también</dt><dd>
[frect]
</dd>
</dl>
<hr>
## frect

```c
void frect(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja un rectángulo relleno.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X superior izquierda en píxeles |
| y0 | coordenada Y superior izquierda en píxeles |
| x1 | coordenada X inferior derecha en píxeles |
| y1 | coordenada Y inferior derecha en píxeles |
</dd>
<dt>Ver también</dt><dd>
[rect]
</dd>
</dl>
<hr>
## circ

```c
void circ(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja un círculo.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x | coordenada central X en píxeles |
| y | coordenada central Y en píxeles |
| r | radio en píxeles |
</dd>
<dt>Ver también</dt><dd>
[fcirc], [ellip], [fellip]
</dd>
</dl>
<hr>
## fcirc

```c
void fcirc(uint8_t palidx, int16_t x, int16_t y, uint16_t r)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja un círculo relleno.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x | coordenada central X en píxeles |
| y | coordenada central Y en píxeles |
| r | radio en píxeles |
</dd>
<dt>Ver también</dt><dd>
[circ], [ellip], [fellip]
</dd>
</dl>
<hr>
## ellip

```c
void ellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja una elipse.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X superior izquierda en píxeles |
| y0 | coordenada Y superior izquierda en píxeles |
| x1 | coordenada X inferior derecha en píxeles |
| y1 | coordenada Y inferior derecha en píxeles |
</dd>
<dt>Ver también</dt><dd>
[circ], [fcirc], [fellip]
</dd>
</dl>
<hr>
## fellip

```c
void fellip(uint8_t palidx, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja una elipse rellena.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
| x0 | coordenada X superior izquierda en píxeles |
| y0 | coordenada Y superior izquierda en píxeles |
| x1 | coordenada X inferior derecha en píxeles |
| y1 | coordenada Y inferior derecha en píxeles |
</dd>
<dt>Ver también</dt><dd>
[circ], [fcirc], [ellip]
</dd>
</dl>
<hr>
## move

```c
void move(int16_t x, int16_t y, uint16_t deg)
```
<dl>
<dt>Descripción</dt><dd>
Mueve la tortuga a la posición dada en la pantalla o en el laberinto.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| x | coordenada X en píxeles (o 1/128 mosaicos con [maze]) |
| y | coordenada Y en píxeles |
| deg | dirección en grados, 0 a 359, 0 es hacia arriba en la pantalla, 90 es hacia la derecha |
</dd>
<dt>Ver también</dt><dd>
[left], [right], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## left

```c
void left(uint16_t deg)
```
<dl>
<dt>Descripción</dt><dd>
Gira la tortuga a la izquierda.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| deg | cambio en grados, 0 a 359 |
</dd>
<dt>Ver también</dt><dd>
[move], [right], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## right

```c
void right(uint16_t deg)
```
<dl>
<dt>Descripción</dt><dd>
Gira la tortuga a la derecha.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| deg | cambio en grados, 0 a 359 |
</dd>
<dt>Ver también</dt><dd>
[move], [left], [up], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## up

```c
void up(void)
```
<dl>
<dt>Descripción</dt><dd>
Levanta la cola de la tortuga. La tortuga se moverá sin trazar una línea.
</dd>
<dt>Ver también</dt><dd>
[move], [left], [right], [down], [color], [forw], [back]
</dd>
</dl>
<hr>
## down

```c
void down(void)
```
<dl>
<dt>Descripción</dt><dd>
Baja la cola de la tortuga. La tortuga se moverá dibujando una línea (ver [color]).
</dd>
<dt>Ver también</dt><dd>
[move], [left], [right], [up], [color], [forw], [back]
</dd>
</dl>
<hr>
## color

```c
void color(uint8_t palidx)
```
<dl>
<dt>Descripción</dt><dd>
Establece el color de la pintura de la tortuga.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| palidx | color, índice de paleta 0 a 255 |
</dd>
<dt>Ver también</dt><dd>
[move], [left], [right], [up], [down], [forw], [back]
</dd>
</dl>
<hr>
## forw

```c
void forw(uint16_t cnt)
```
<dl>
<dt>Descripción</dt><dd>
Mueve la tortuga hacia adelante.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| cnt | cantidad en píxeles (o 1/128 mosaicos con [maze]) |
</dd>
<dt>Ver también</dt><dd>
[move], [left], [right], [up], [down], [color], [back]
</dd>
</dl>
<hr>
## back

```c
void back(uint16_t cnt)
```
<dl>
<dt>Descripción</dt><dd>
Mueve la tortuga hacia atrás.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| cnt | cantidad en píxeles (o 1/128 mosaicos con [maze]) |
</dd>
<dt>Ver también</dt><dd>
[move], [left], [right], [up], [down], [color], [forw]
</dd>
</dl>
<hr>
## spr

```c
void spr(int16_t x, int16_t y, uint16_t sprite, uint8_t sw, uint8_t sh, int8_t scale, uint8_t type)
```
<dl>
<dt>Descripción</dt><dd>
Muestra un sprite o varios sprites adyacentes.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| x | coordenada X en píxeles |
| y | coordenada Y en píxeles |
| sprite | ID de sprite, 0 a 1023 |
| sw | número de sprites horizontales |
| sh | número de sprites verticales |
| scale | escala, -3 a 4 |
| type | transformar, 0=normal, 1=girar 90, 2=girar 180, 3=girar 270, 4=voltear verticalmente, 5=voltear+90, 6=voltear horizontalmente, 7=voltear+270 |
</dd>
<dt>Ver también</dt><dd>
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
<dt>Descripción</dt><dd>
Muestra una ventana de diálogo usando sprites.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| x | coordenada X en píxeles |
| y | coordenada Y en píxeles |
| w | ancho del diálogo en píxeles |
| h | altura del diálogo en píxeles |
| scale | escala, -3 a 4 |
| tl | ID de sprite de la esquina superior izquierda |
| tm | ID de sprite medio superior |
| tr | ID de sprite de la esquina superior derecha |
| ml | ID de sprite del lado medio izquierdo |
| bg | ID de sprite de fondo |
| mr | ID de sprite del lado medio derecho |
| bl | ID de sprite de la esquina inferior izquierda |
| bm | ID de sprite inferior medio |
| br | ID de sprite de la esquina inferior derecha |
</dd>
<dt>Ver también</dt><dd>
[spr], [stext]
</dd>
</dl>
<hr>
## stext

```c
void stext(int16_t x, int16_t y, uint16_t fs, uint16_t fu, uint8_t sw, uint8_t sh, int8_t scale, str_t str)
```
<dl>
<dt>Descripción</dt><dd>
Displays text on screen using sprites.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| x | coordenada X en píxeles |
| y | coordenada Y en píxeles |
| fs | primer ID de sprite que se utilizará para mostrar |
| fu | Primer UNICODE (carácter más pequeño) en cadena |
| sw | número de sprites horizontales |
| sh | número de sprites verticales |
| scale | escala, -3 a 4 |
| str | cadena UTF-8 terminada en cero |
</dd>
<dt>Ver también</dt><dd>
[spr], [dlg]
</dd>
</dl>
<hr>
## remap

```c
void remap(addr_t replace)
```
<dl>
<dt>Descripción</dt><dd>
Reemplaza mosaicos en el mapa. Se puede utilizar para animar mosaicos en el mapa.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| replace | una matriz de 256 ID de sprites |
</dd>
<dt>Ver también</dt><dd>
[mget], [mset], [map], [maze]
</dd>
</dl>
<hr>
## mget

```c
uint16_t mget(uint16_t mx, uint16_t my)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve un mosaico en el mapa.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| mx | coordenada X en el mapa en mosaicos |
| my | coordenada Y en el mapa en mosaicos |
</dd>
<dt>Valor de retorno</dt><dd>
La identificación del sprite del mosaico en la coordenada dada.
</dd>
<dt>Ver también</dt><dd>
[remap], [mset], [map], [maze]
</dd>
</dl>
<hr>
## mset

```c
void mset(uint16_t mx, uint16_t my, uint16_t sprite)
```
<dl>
<dt>Descripción</dt><dd>
Establece un mosaico en el mapa.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| mx | coordenada X en el mapa en mosaicos |
| my | coordenada Y en el mapa en mosaicos |
| sprite | ID de sprite, 0 a 1023 |
</dd>
<dt>Ver también</dt><dd>
[remap], [mget], [map], [maze]
</dd>
</dl>
<hr>
## map

```c
void map(int16_t x, int16_t y, uint16_t mx, uint16_t my, uint16_t mw, uint16_t mh, int8_t scale)
```
<dl>
<dt>Descripción</dt><dd>
Dibuja (parte del) mapa.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| x | coordenada X en píxeles |
| y | coordenada Y en píxeles |
| mx | coordenada X en el mapa en mosaicos |
| my | coordenada Y en el mapa en mosaicos |
| mw | número de mosaicos horizontales |
| mh | número de mosaicos verticales |
| scale | escala, -3 a 4 |
</dd>
<dt>Ver también</dt><dd>
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
<dt>Descripción</dt><dd>
Muestra el mapa como un laberinto 3D, usando la posición de la tortuga.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| mx | coordenada X en el mapa en mosaicos |
| my | coordenada Y en el mapa en mosaicos |
| mw | número de mosaicos horizontales |
| mh | número de mosaicos verticales |
| scale | número de sprites por mosaico en potencia de dos, 0 a 3 |
| sky | índice de mosaicos de cielo |
| grd | índice de mosaicos de suelo |
| door | primer índice de azulejos de puerta |
| wall | primer índice de azulejos de pared |
| obj | primer índice de mosaico de objetos |
| numnpc | número de registros NPC |
| npc | una matriz uint32_t de numnpc multiplicado por x, y, índice de mosaico tripletes |
</dd>
<dt>Ver también</dt><dd>
[remap], [mget], [mset], [map]
</dd>
</dl>

# Input

## getpad

```c
int getpad(int pad, int btn)
```
<dl>
<dt>Descripción</dt><dd>
Obtiene el estado actual de un botón del gamepad.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| pad | índice del gamepad, 0 a 3 |
| btn | uno de los botones [mando de juegos], `BTN_` |
</dd>
<dt>Valor de retorno</dt><dd>
Cero si no se presiona, distinto de cero si se presiona.
</dd>
<dt>Ver también</dt><dd>
[prspad], [relpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## prspad

```c
int prspad(int pad, int btn)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve verdadero si se presionó el botón del gamepad desde la última llamada.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| pad | índice del gamepad, 0 a 3 |
| btn | uno de los botones [mando de juegos], `BTN_` |
</dd>
<dt>Valor de retorno</dt><dd>
Cero si no se presiona, distinto de cero si se presiona.
</dd>
<dt>Ver también</dt><dd>
[relpad], [getpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## relpad

```c
int relpad(int pad, int btn)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve verdadero si se soltó el botón del gamepad desde la última llamada.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| pad | índice del gamepad, 0 a 3 |
| btn | uno de los botones [mando de juegos], `BTN_` |
</dd>
<dt>Valor de retorno</dt><dd>
Cero si no se publicó, distinto de cero si se publicó.
</dd>
<dt>Ver también</dt><dd>
[prspad], [getpad], [getbtn], [getclk], [getkey]
</dd>
</dl>
<hr>
## getbtn

```c
int getbtn(int btn)
```
<dl>
<dt>Descripción</dt><dd>
Obtiene el estado del botón del mouse.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| btn | uno de los botones [puntero], `BTN_` o `SCR_` |
</dd>
<dt>Valor de retorno</dt><dd>
Cero si no se presiona, distinto de cero si se presiona.
</dd>
<dt>Ver también</dt><dd>
[prspad], [relpad], [getpad], [getclk], [getkey]
</dd>
</dl>
<hr>
## getclk

```c
int getclk(int btn)
```
<dl>
<dt>Descripción</dt><dd>
Obtiene clic en el botón del mouse.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| btn | uno de los botones [puntero], `BTN_` |
</dd>
<dt>Valor de retorno</dt><dd>
Cero si no se hace clic, distinto de cero si se hace clic.
</dd>
<dt>Ver también</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getkey]
</dd>
</dl>
<hr>
## getkey

```c
int getkey(int sc)
```
<dl>
<dt>Descripción</dt><dd>
Obtiene el estado actual de una clave.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| sc | código de escaneo, 1 a 144, consulte [teclado] |
</dd>
<dt>Valor de retorno</dt><dd>
Cero si no se presiona, distinto de cero si se presiona.
</dd>
<dt>Ver también</dt><dd>
[prspad], [relpad], [getpad], [getbtn], [getclk]
</dd>
</dl>
<hr>
## popkey

```c
uint32_t popkey(void)
```
<dl>
<dt>Descripción</dt><dd>
Extraiga una tecla UTF-8 de la cola del teclado. Consulte [teclado] y para la versión de bloqueo [getc].
</dd>
<dt>Valor de retorno</dt><dd>
La representación UTF-8 de la clave, o 0 si la cola estaba vacía (sin bloqueo).
</dd>
<dt>Ver también</dt><dd>
[pendkey], [lenkey], [speckey], [getc]
</dd>
</dl>
<hr>
## pendkey

```c
int pendkey(void)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve verdadero si hay una clave pendiente en la cola (pero deja la clave en la cola, no la elimina).
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve 1 si hay claves pendientes en la cola.
</dd>
<dt>Ver también</dt><dd>
[popkey], [lenkey], [speckey]
</dd>
</dl>
<hr>
## lenkey

```c
int lenkey(uint32_t key)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve la longitud de una clave UTF-8 en bytes.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| key | la clave, sacada de la cola |
</dd>
<dt>Valor de retorno</dt><dd>
Longitud de la representación UTF-8 en bytes.
</dd>
<dt>Ver también</dt><dd>
[popkey], [pendkey], [speckey]
</dd>
</dl>
<hr>
## speckey

```c
int speckey(uint32_t key)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve verdadera si la clave es una clave especial.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| key | la clave, sacada de la cola |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve 1 si es una clave especial y 0 si es imprimible.
</dd>
<dt>Ver también</dt><dd>
[popkey], [pendkey], [lenkey]
</dd>
</dl>

# Matemáticas

## rand

```c
uint32_t rand(void)
```
<dl>
<dt>Descripción</dt><dd>
Sea aleatorio. Utilice el módulo `%` para hacerlo más pequeño, por ejemplo, `1 + rand() % 6` devuelve aleatoriamente entre 1 y 6,
como un dado.
</dd>
<dt>Valor de retorno</dt><dd>
Un número aleatorio entre 0 y 2^^32^^-1 (4294967295).
</dd>
<dt>Ver también</dt><dd>
[rnd]
</dd>
</dl>
<hr>
## rnd

```c
float rnd(void)
```
<dl>
<dt>Descripción</dt><dd>
Sea aleatorio. Igual que [rand], pero devuelve un número de coma flotante.
</dd>
<dt>Valor de retorno</dt><dd>
Un número aleatorio entre 0.0 y 1.0.
</dd>
<dt>Ver también</dt><dd>
[rand]
</dd>
</dl>
<hr>
## float

```c
float float(int val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el equivalente en coma flotante de un número entero.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
El punto flotante del valor.
</dd>
<dt>Ver también</dt><dd>
[int]
</dd>
</dl>
<hr>
## int

```c
int int(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el equivalente entero de un número de punto flotante.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
El número entero de valor.
</dd>
<dt>Ver también</dt><dd>
[float]
</dd>
</dl>
<hr>
## floor

```c
float floor(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el número entero más grande que no sea mayor que el valor.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
El piso del valor.
</dd>
<dt>Ver también</dt><dd>
[ceil]
</dd>
</dl>
<hr>
## ceil

```c
float ceil(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el número entero más pequeño que no sea menor que el valor.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
El techo del valor.
</dd>
<dt>Ver también</dt><dd>
[floor]
</dd>
</dl>
<hr>
## sgn

```c
float sgn(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el signo del valor.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
Ya sea 1.0 o -1.0.
</dd>
<dt>Ver también</dt><dd>
[abs]
</dd>
</dl>
<hr>
## abs

```c
float abs(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el absoluto del valor.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
Ya sea valor o -valor, siempre positivo.
</dd>
<dt>Ver también</dt><dd>
[sgn]
</dd>
</dl>
<hr>
## exp

```c
float exp(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el exponencial del valor, es decir, la base de logaritmos naturales elevada a la potencia del valor.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve e^^val^^.
</dd>
<dt>Ver también</dt><dd>
[log], [pow]
</dd>
</dl>
<hr>
## log

```c
float log(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el logaritmo natural del valor.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve el logaritmo natural de val.
</dd>
<dt>Ver también</dt><dd>
[exp]
</dd>
</dl>
<hr>
## pow

```c
float pow(float val, float exp)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el valor elevado a la potencia del exponente. Esta es una operación lenta, trate de evitarla.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
| exp | exponente |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve val^^exp^^.
</dd>
<dt>Ver también</dt><dd>
[exp], [sqrt], [rsqrt]
</dd>
</dl>
<hr>
## sqrt

```c
float sqrt(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve la raíz cuadrada del valor. Esta es una operación lenta, trate de evitarla.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
Raíz cuadrada del valor.
</dd>
<dt>Ver también</dt><dd>
[pow], [rsqrt]
</dd>
</dl>
<hr>
## rsqrt

```c
float rsqrt(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el recíproco de la raíz cuadrada del valor (`1 / sqrt(val)`). Utiliza el método rápido de John Carmack.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
</dd>
<dt>Valor de retorno</dt><dd>
Recíproco de la raíz cuadrada del valor.
</dd>
<dt>Ver también</dt><dd>
[pow], [sqrt]
</dd>
</dl>
<hr>
## clamp

```c
float clamp(float val, float minv, float maxv)
```
<dl>
<dt>Descripción</dt><dd>
Fija un valor entre los límites.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor |
| minv | valor mínimo |
| maxv | valor máximo |
</dd>
<dt>Valor de retorno</dt><dd>
Valor fijado.
</dd>
<dt>Ver también</dt><dd>
[clampv2], [clampv3], [clampv4]
</dd>
</dl>
<hr>
## lerp

```c
float lerp(float a, float b, float t)
```
<dl>
<dt>Descripción</dt><dd>
Lineal interpola dos números.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | primer número flotante |
| b | segundo número flotante |
| t | valor de interpolación entre 0.0 y 1.0 |
</dd>
<dt>Ver también</dt><dd>
[lerpv2], [lerpv3], [lerpv4], [lerpq], [slerpq]
</dd>
</dl>
<hr>
## pi

```c
float pi(void)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve π como un número de punto flotante.
</dd>
<dt>Valor de retorno</dt><dd>
El valor 3.14159265358979323846.
</dd>
</dl>
<hr>
## cos

```c
float cos(uint16_t deg)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve coseno.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| deg | grados, 0 a 359, 0 es arriba, 90 a la derecha |
</dd>
<dt>Valor de retorno</dt><dd>
Coseno del grado, entre -1.0 y 1.0.
</dd>
<dt>Ver también</dt><dd>
[sin], [tan], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## sin

```c
float sin(uint16_t deg)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve seno.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| deg | grados, 0 a 359, 0 es arriba, 90 a la derecha |
</dd>
<dt>Valor de retorno</dt><dd>
Seno del grado, entre -1.0 y 1.0.
</dd>
<dt>Ver también</dt><dd>
[cos], [tan], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## tan

```c
float tan(uint16_t deg)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve tangente.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| deg | grados, 0 a 359, 0 es arriba, 90 a la derecha |
</dd>
<dt>Valor de retorno</dt><dd>
Tangente del grado, entre -1.0 y 1.0.
</dd>
<dt>Ver también</dt><dd>
[cos], [sin], [acos], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## acos

```c
uint16_t acos(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el arco coseno.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor, -1.0 a 1.0 |
</dd>
<dt>Valor de retorno</dt><dd>
Arco coseno en grados, 0 a 359, 0 está arriba, 90 a la derecha.
</dd>
<dt>Ver también</dt><dd>
[cos], [sin], [tan], [asin], [atan], [atan2]
</dd>
</dl>
<hr>
## asin

```c
uint16_t asin(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el arco seno.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor, -1.0 a 1.0 |
</dd>
<dt>Valor de retorno</dt><dd>
Arco seno en grados, 0 a 359, 0 está arriba, 90 a la derecha.
</dd>
<dt>Ver también</dt><dd>
[cos], [sin], [tan], [acos], [atan], [atan2]
</dd>
</dl>
<hr>
## atan

```c
uint16_t atan(float val)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el arco tangente.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| val | valor, -1.0 a 1.0 |
</dd>
<dt>Valor de retorno</dt><dd>
Arco tangente en grados, 0 a 359, 0 está arriba, 90 a la derecha.
</dd>
<dt>Ver también</dt><dd>
[cos], [sin], [tan], [acos], [asin], [atan2]
</dd>
</dl>
<hr>
## atan2

```c
uint16_t atan2(float y, float x)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el arco tangente para y/x, utilizando los signos de y, x para determinar el cuadrante.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| y | coordenada Y |
| x | coordenada X |
</dd>
<dt>Valor de retorno</dt><dd>
Arco tangente en grados, 0 a 359, 0 está arriba, 90 a la derecha.
</dd>
<dt>Ver también</dt><dd>
[cos], [sin], [tan], [acos], [asin]
</dd>
</dl>
<hr>
## dotv2

```c
float dotv2(addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Calcula el producto punto de dos vectores con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de dos números flotantes |
| b | dirección de dos números flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
Producto punto de los vectores.
</dd>
<dt>Ver también</dt><dd>
[lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## lenv2

```c
float lenv2(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Calcula la longitud de un vector con dos elementos. Esto es lento, trate de evitarlo (ver [normv2]).
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de dos números flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
Longitud del vector.
</dd>
<dt>Ver también</dt><dd>
[dotv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## scalev2

```c
void scalev2(addr_t a, float s)
```
<dl>
<dt>Descripción</dt><dd>
Escala un vector con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de dos números flotantes |
| s | valor del escalador |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## negv2

```c
void negv2(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Niega un vector con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de dos números flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [scalev2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## addv2

```c
void addv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Suma vectores con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de dos números flotantes, producción |
| a | dirección de dos números flotantes |
| b | dirección de dos números flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## subv2

```c
void subv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Resta vectores con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de dos números flotantes, producción |
| a | dirección de dos números flotantes |
| b | dirección de dos números flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [mulv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## mulv2

```c
void mulv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Multiplica vectores con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de dos números flotantes, producción |
| a | dirección de dos números flotantes |
| b | dirección de dos números flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [divv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## divv2

```c
void divv2(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Divide vectores con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de dos números flotantes, producción |
| a | dirección de dos números flotantes |
| b | dirección de dos números flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [clampv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## clampv2

```c
void clampv2(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Descripción</dt><dd>
Pinza vectores con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de dos números flotantes, producción |
| v | dirección de dos flotadores, entrada |
| minv | dirección de dos flotadores, mínimo |
| maxv | dirección de dos flotadores, máximo |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [lerpv2], [normv2]
</dd>
</dl>
<hr>
## lerpv2

```c
void lerpv2(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Descripción</dt><dd>
Lineal interpola vectores con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de dos números flotantes, producción |
| a | dirección de dos números flotantes |
| b | dirección de dos números flotantes |
| t | valor de interpolación entre 0.0 y 1.0 |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [normv2]
</dd>
</dl>
<hr>
## normv2

```c
void normv2(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Normaliza un vector con dos elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de dos números flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv2], [lenv2], [scalev2], [negv2], [addv2], [subv2], [mulv2], [divv2], [clampv2], [lerpv2]
</dd>
</dl>
<hr>
## dotv3

```c
float dotv3(addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Calcula el producto punto de dos vectores con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de tres flotantes |
| b | dirección de tres flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
Producto punto de los vectores.
</dd>
<dt>Ver también</dt><dd>
[lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## lenv3

```c
float lenv3(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Calcula la longitud de un vector con tres elementos. Esto es lento, trate de evitarlo (ver [normv3]).
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de tres flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
Length of the vector.
</dd>
<dt>Ver también</dt><dd>
[dotv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## scalev3

```c
void scalev3(addr_t a, float s)
```
<dl>
<dt>Descripción</dt><dd>
Escala un vector con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de tres flotantes |
| s | valor del escalador |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## negv3

```c
void negv3(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Niega un vector con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## addv3

```c
void addv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Suma vectores con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| a | dirección de tres flotantes |
| b | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## subv3

```c
void subv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Resta vectores con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| a | dirección de tres flotantes |
| b | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## mulv3

```c
void mulv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Multiplica vectores con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| a | dirección de tres flotantes |
| b | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [divv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## divv3

```c
void divv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Divide vectores con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| a | dirección de tres flotantes |
| b | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [crossv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## crossv3

```c
void crossv3(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Calcula el producto cruzado de vectores con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| a | dirección de tres flotantes |
| b | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [clampv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## clampv3

```c
void clampv3(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Descripción</dt><dd>
Pinza vectores con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| v | dirección de tres flotantes, entrada |
| minv | dirección de tres flotantes, mínimo |
| maxv | dirección de tres flotantes, máximo |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [lerpv3], [normv3]
</dd>
</dl>
<hr>
## lerpv3

```c
void lerpv3(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Descripción</dt><dd>
Lineal interpola vectores con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| a | dirección de tres flotantes |
| b | dirección de tres flotantes |
| t | valor de interpolación entre 0.0 y 1.0 |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [normv3]
</dd>
</dl>
<hr>
## normv3

```c
void normv3(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Normaliza un vector con tres elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv3], [lenv3], [scalev3], [negv3], [addv3], [subv3], [mulv3], [divv3], [crossv3], [clampv3], [lerpv3]
</dd>
</dl>
<hr>
## dotv4

```c
float dotv4(addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Calcula el producto punto de dos vectores con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
Producto punto de los vectores.
</dd>
<dt>Ver también</dt><dd>
[lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## lenv4

```c
float lenv4(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Calcula la longitud de un vector con cuatro elementos. Esto es lento, trate de evitarlo (ver [normv4]).
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
Length of the vector.
</dd>
<dt>Ver también</dt><dd>
[dotv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## scalev4

```c
void scalev4(addr_t a, float s)
```
<dl>
<dt>Descripción</dt><dd>
Escala un vector con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
| s | valor del escalador |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## negv4

```c
void negv4(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Niega un vector con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [scalev4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## addv4

```c
void addv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Suma vectores con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [negv4], [scalev4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## subv4

```c
void subv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Resta vectores con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [mulv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## mulv4

```c
void mulv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Multiplica vectores con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [divv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## divv4

```c
void divv4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Divide vectores con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [clampv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## clampv4

```c
void clampv4(addr_t dst, addr_t v, addr_t minv, addr_t maxv)
```
<dl>
<dt>Descripción</dt><dd>
Pinza vectores con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| v | dirección de cuatro flotantes, entrente |
| minv | dirección de cuatro flotantes, mínimo |
| maxv | dirección de cuatro flotantes, máximo |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [lerpv4], [normv4]
</dd>
</dl>
<hr>
## lerpv4

```c
void lerpv4(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Descripción</dt><dd>
Lineal interpola vectores con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
| t | valor de interpolación entre 0.0 y 1.0 |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [normv4]
</dd>
</dl>
<hr>
## normv4

```c
void normv4(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Normaliza un vector con cuatro elementos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[dotv4], [lenv4], [scalev4], [negv4], [addv4], [subv4], [mulv4], [divv4], [clampv4], [lerpv4]
</dd>
</dl>
<hr>
## idq

```c
void idq(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Carga el cuaternión de identidad.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## eulerq

```c
void eulerq(addr_t dst, uint16_t pitch, uint16_t yaw, uint16_t roll)
```
<dl>
<dt>Descripción</dt><dd>
Carga un cuaternión usando ángulos de Euler.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| pitch | rotación alrededor del eje X en grados, 0 a 359 |
| yaw | rotación alrededor del eje Y en grados, 0 a 359 |
| roll | rotación alrededor del eje Z en grados, 0 a 359 |
</dd>
<dt>Ver también</dt><dd>
[idq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## dotq

```c
float dotq(addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Calcula el producto punto de un cuaternión.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
Producto punto del cuaternión.
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## lenq

```c
float lenq(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Calcula la longitud de un cuaternión.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
Longitud del cuaternión.
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## scaleq

```c
void scaleq(addr_t a, float s)
```
<dl>
<dt>Descripción</dt><dd>
Escala un cuaternión.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
| s | valor del escalador |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## negq

```c
void negq(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Niega un cuaternión.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## addq

```c
void addq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Suma cuaterniones.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [subq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## subq

```c
void subq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Resta cuaterniones.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [mulq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## mulq

```c
void mulq(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Multiplica cuaterniones.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [rotq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## rotq

```c
void rotq(addr_t dst, addr_t q, addr_t v)
```
<dl>
<dt>Descripción</dt><dd>
Gira un vector con tres elementos por un cuaternión.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| q | dirección de cuatro flotantes |
| v | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [lerpq], [slerpq], [normq]
</dd>
</dl>
<hr>
## lerpq

```c
void lerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Descripción</dt><dd>
Lineal interpola dos cuaterniones.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
| t | valor de interpolación entre 0.0 y 1.0 |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [slerpq], [normq]
</dd>
</dl>
<hr>
## slerpq

```c
void slerpq(addr_t dst, addr_t a, addr_t b, float t)
```
<dl>
<dt>Descripción</dt><dd>
Esférica interpola un cuaternión.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| a | dirección de cuatro flotantes |
| b | dirección de cuatro flotantes |
| t | valor de interpolación entre 0.0 y 1.0 |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [normq]
</dd>
</dl>
<hr>
## normq

```c
void normq(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Normaliza un cuaternión.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[idq], [eulerq], [dotq], [lenq], [scaleq], [negq], [addq], [subq], [mulq], [rotq], [lerpq], [slerpq]
</dd>
</dl>
<hr>
## idm4

```c
void idm4(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Carga una matriz de identidad de 4 x 4.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de 16 flotantes |
</dd>
<dt>Ver también</dt><dd>
[trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## trsm4

```c
void trsm4(addr_t dst, addr_t t, addr_t r, addr_t s)
```
<dl>
<dt>Descripción</dt><dd>
Crea una matriz de 4 x 4 con traslación, rotación y escala.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de 16 flotantes, producción matrix |
| t | dirección de tres flotantes, vector de traducción |
| r | dirección de cuatro flotantes, cuaternión de rotación |
| s | dirección de tres flotantes, vector de escala |
</dd>
<dt>Ver también</dt><dd>
[idm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## detm4

```c
float detm4(addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el determinante de la matriz.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| a | dirección de 16 flotantes |
</dd>
<dt>Valor de retorno</dt><dd>
El determinante de la matriz.
</dd>
<dt>Ver también</dt><dd>
[idm4], [trsm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## addm4

```c
void addm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Suma matrices.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de 16 flotantes, producción |
| a | dirección de 16 flotantes |
| b | dirección de 16 flotantes |
</dd>
<dt>Ver también</dt><dd>
[idm4], [trsm4], [detm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## subm4

```c
void subm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Resta matrices.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de 16 flotantes, producción |
| a | dirección de 16 flotantes |
| b | dirección de 16 flotantes |
</dd>
<dt>Ver también</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [mulm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4

```c
void mulm4(addr_t dst, addr_t a, addr_t b)
```
<dl>
<dt>Descripción</dt><dd>
Multiplica matrices.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de 16 flotantes, producción |
| a | dirección de 16 flotantes |
| b | dirección de 16 flotantes |
</dd>
<dt>Ver también</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4v3], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4v3

```c
void mulm4v3(addr_t dst, addr_t m, addr_t v)
```
<dl>
<dt>Descripción</dt><dd>
Multiplica un vector con tres elementos por una matriz.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de tres flotantes, producción |
| m | dirección de 16 flotantes |
| v | dirección de tres flotantes |
</dd>
<dt>Ver también</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v4], [invm4], [trpm4]
</dd>
</dl>
<hr>
## mulm4v4

```c
void mulm4v4(addr_t dst, addr_t m, addr_t v)
```
<dl>
<dt>Descripción</dt><dd>
Multiplica un vector con cuatro elementos por una matriz.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de cuatro flotantes, producción |
| m | dirección de 16 flotantes |
| v | dirección de cuatro flotantes |
</dd>
<dt>Ver también</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [invm4], [trpm4]
</dd>
</dl>
<hr>
## invm4

```c
void invm4(addr_t dst, addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Calcula la matriz inversa.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de 16 flotantes |
| a | dirección de 16 flotantes |
</dd>
<dt>Ver también</dt><dd>
[idm4], [trsm4], [detm4], [addm4], [subm4], [mulm4], [mulm4v3], [mulm4v4], [trpm4]
</dd>
</dl>
<hr>
## trpm4

```c
void trpm4(addr_t dst, addr_t a)
```
<dl>
<dt>Descripción</dt><dd>
Transponer matriz.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de 16 flotantes, producción |
| a | dirección de 16 flotantes |
</dd>
<dt>Ver también</dt><dd>
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
<dt>Descripción</dt><dd>
Traducir una nube de vértices, también conocida como. coloque un modelo 3D en [espacio 3D].
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | matriz de vértices de destino, 3 x 2 bytes cada uno, X, Y, Z |
| src | matriz de vértices de origen, 3 x 2 bytes cada uno, X, Y, Z |
| num | número de tripletes de coordenadas de vértice en la matriz |
| x | Coordenada X mundial, -32767 a 32767 |
| y | Coordenada Y mundial, -32767 a 32767 |
| z | coordenada Z mundial, -32767 a 32767 |
| pitch | rotación alrededor del eje X en grados, 0 a 359 |
| yaw | rotación alrededor del eje Y en grados, 0 a 359 |
| roll | rotación alrededor del eje Z en grados, 0 a 359 |
| scale | escala, use 1.0 para mantener el tamaño original |
</dd>
<dt>Ver también</dt><dd>
[mesh]
</dd>
</dl>

# Memoria

## inb

```c
uint8_t inb(addr_t src)
```
<dl>
<dt>Descripción</dt><dd>
Leer en un byte de la memoria.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| src | dirección, 0x00000 a 0xBFFFF |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve el valor en esa dirección.
</dd>
</dl>
<hr>
## inw

```c
uint16_t inw(addr_t src)
```
<dl>
<dt>Descripción</dt><dd>
Leer una palabra (word, dos bytes) de la memoria.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| src | dirección, 0x00000 a 0xBFFFE |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve el valor en esa dirección.
</dd>
</dl>
<hr>
## ini

```c
uint32_t ini(addr_t src)
```
<dl>
<dt>Descripción</dt><dd>
Leer un número entero (int, cuatro bytes) de la memoria.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| src | dirección, 0x00000 a 0xBFFFC |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve el valor en esa dirección.
</dd>
</dl>
<hr>
## outb

```c
void outb(addr_t dst, uint8_t value)
```
<dl>
<dt>Descripción</dt><dd>
Escribe un byte en la memoria.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección, 0x00000 a 0xBFFFF |
| value | valor a establecer, 0 a 255 |
</dd>
</dl>
<hr>
## outw

```c
void outw(addr_t dst, uint16_t value)
```
<dl>
<dt>Descripción</dt><dd>
Escriba una palabra (word, dos bytes) en la memoria.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección, 0x00000 a 0xBFFFE |
| value | valor a establecer, 0 a 65535 |
</dd>
</dl>
<hr>
## outi

```c
void outi(addr_t dst, uint32_t value)
```
<dl>
<dt>Descripción</dt><dd>
Escriba un número entero (int, cuatro bytes) en la memoria.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección, 0x00000 a 0xBFFFC |
| value | valor a establecer, 0 a 4294967295 |
</dd>
</dl>
<hr>
## memsave

```c
int memsave(uint8_t overlay, addr_t src, uint32_t size)
```
<dl>
<dt>Descripción</dt><dd>
Guarda el área de memoria para superponer.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| overlay | índice de superposición para escribir, 0 a 255 |
| src | dirección de memoria desde la que guardar, 0x00000 a 0xBFFFF |
| size | número de bytes para guardar |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve 1 en caso de éxito, 0 en caso de error.
</dd>
<dt>Ver también</dt><dd>
[memload]
</dd>
</dl>
<hr>
## memload

```c
int memload(addr_t dst, uint8_t overlay, uint32_t maxsize)
```
<dl>
<dt>Descripción</dt><dd>
Carga una superposición en el área de memoria especificada.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de memoria para cargar, 0x00000 a 0xBFFFF |
| overlay | índice de superposición para leer, 0 a 255 |
| maxsize | número máximo de bytes para cargar |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve el número de bytes realmente cargados.
</dd>
<dt>Ver también</dt><dd>
[memsave]
</dd>
</dl>
<hr>
## memcpy

```c
void memcpy(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Descripción</dt><dd>
Copiar regiones de memoria.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de destino, 0x00000 a 0xBFFFF |
| src | dirección de origen, 0x00000 a 0xBFFFF |
| len | número de bytes para copiar |
</dd>
</dl>
<hr>
## memset

```c
void memset(addr_t dst, uint8_t value, uint32_t len)
```
<dl>
<dt>Descripción</dt><dd>
Establezca la región de memoria en un valor determinado.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de destino, 0x00000 a 0xBFFFF |
| value | valor a configurar, 0 a 255 |
| len | número de bytes a configurar |
</dd>
</dl>
<hr>
## memcmp

```c
int memcmp(addr_t addr0, addr_t addr1, uint32_t len)
```
<dl>
<dt>Descripción</dt><dd>
Compara regiones de memoria.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| addr0 | primera dirección, 0x00000 a 0xBFFFF |
| addr1 | segunda dirección, 0x00000 a 0xBFFFF |
| len | número de bytes para comparar |
</dd>
<dt>Valor de retorno</dt><dd>
Devuelve la diferencia, 0 si las dos regiones de memoria coinciden.
</dd>
</dl>
<hr>
## deflate

```c
int deflate(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Descripción</dt><dd>
Comprima un búfer usando RFC1950 deflate (zlib).
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de destino, 0x30000 a 0xBFFFF |
| src | dirección de origen, 0x30000 a 0xBFFFF |
| len | número de bytes para comprimir |
</dd>
<dt>Valor de retorno</dt><dd>
0 o negativo en caso de error; de lo contrario, la longitud del búfer comprimido y los datos comprimidos en dst.
</dd>
<dt>Ver también</dt><dd>
[inflate]
</dd>
</dl>
<hr>
## inflate

```c
int inflate(addr_t dst, addr_t src, uint32_t len)
```
<dl>
<dt>Descripción</dt><dd>
Descomprima un búfer con datos comprimidos RFC1950 deflate (zlib).
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| dst | dirección de destino, 0x30000 a 0xBFFFF |
| src | dirección de origen, 0x30000 a 0xBFFFF |
| len | número de bytes comprimidos |
</dd>
<dt>Valor de retorno</dt><dd>
0 o negativo en caso de error; de lo contrario, la longitud del búfer sin comprimir y los datos sin comprimir en dst.
</dd>
<dt>Ver también</dt><dd>
[deflate]
</dd>
</dl>
<hr>
## time

```c
float time(void)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el número de ticks desde que se enciende.
</dd>
<dt>Valor de retorno</dt><dd>
El tiempo transcurrido en milisegundos desde el encendido.
</dd>
<dt>Ver también</dt><dd>
[now]
</dd>
</dl>
<hr>
## now

```c
uint32_t now(void)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve la marca de tiempo de UNIX. Verifique el byte en la dirección 0000C para ver si se desborda.
</dd>
<dt>Valor de retorno</dt><dd>
El tiempo transcurrido en segundos desde la medianoche del 1 de enero de 1970, hora media de Greenwich.
</dd>
<dt>Ver también</dt><dd>
[time]
</dd>
</dl>
<hr>
## atoi

```c
int atoi(str_t src)
```
<dl>
<dt>Descripción</dt><dd>
Convierte una cadena decimal ASCII en un número entero.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| src | dirección de cadena, 0x00000 a 0xBFFFF |
</dd>
<dt>Valor de retorno</dt><dd>
El valor numérico de la cadena.
</dd>
<dt>Ver también</dt><dd>
[itoa], [str], [val]
</dd>
</dl>
<hr>
## itoa

```c
str_t itoa(int value)
```
<dl>
<dt>Descripción</dt><dd>
Convierte un número entero en una cadena decimal ASCII.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| value | valor, -2147483648 a 2147483647 |
</dd>
<dt>Valor de retorno</dt><dd>
La cadena convertida.
</dd>
<dt>Ver también</dt><dd>
[atoi], [str], [val]
</dd>
</dl>
<hr>
## val

```c
float val(str_t src)
```
<dl>
<dt>Descripción</dt><dd>
Convierte una cadena decimal ASCII en un número de punto flotante.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| src | dirección de cadena, 0x00000 a 0xBFFFF |
</dd>
<dt>Valor de retorno</dt><dd>
El valor numérico de la cadena.
</dd>
<dt>Ver también</dt><dd>
[itoa], [atoi], [str]
</dd>
</dl>
<hr>
## str

```c
str_t str(float value)
```
<dl>
<dt>Descripción</dt><dd>
Convierte un número de punto flotante en una cadena decimal ASCII.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| value | valor |
</dd>
<dt>Valor de retorno</dt><dd>
La cadena convertida.
</dd>
<dt>Ver también</dt><dd>
[atoi], [itoa], [val]
</dd>
</dl>
<hr>
## sprintf

```c
str_t sprintf(str_t fmt, ...)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve una cadena UTF-8 terminada en cero creada utilizando formato y argumentos.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| fmt | cadena para mostrar, [cadena de formato] |
| ... | argumentos opcionales |
</dd>
<dt>Valor de retorno</dt><dd>
Cuerda construida.
</dd>
</dl>
<hr>
## strlen

```c
int strlen(str_t src)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el número de bytes en una cadena (sin el cero final).
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| src | dirección de cadena, 0x00000 a 0xBFFFF |
</dd>
<dt>Valor de retorno</dt><dd>
El número de bytes de la cadena.
</dd>
<dt>Ver también</dt><dd>
[mblen]
</dd>
</dl>
<hr>
## mblen

```c
int mblen(str_t src)
```
<dl>
<dt>Descripción</dt><dd>
Devuelve el número de caracteres multibyte UTF-8 en una cadena (sin el cero final).
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| src | dirección de cadena, 0x00000 a 0xBFFFF |
</dd>
<dt>Valor de retorno</dt><dd>
El número de caracteres de la cadena.
</dd>
<dt>Ver también</dt><dd>
[strlen]
</dd>
</dl>
<hr>
## malloc

```c
addr_t malloc(uint32_t size)
```
<dl>
<dt>Descripción</dt><dd>
Asigna memoria de usuario de forma dinámica.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| size | número de bytes para asignar |
</dd>
<dt>Valor de retorno</dt><dd>
Dirección del nuevo búfer asignado o NULL en caso de error.
</dd>
<dt>Ver también</dt><dd>
[realloc], [free]
</dd>
</dl>
<hr>
## realloc

```c
addr_t realloc(addr_t addr, uint32_t size)
```
<dl>
<dt>Descripción</dt><dd>
Cambie el tamaño de un búfer previamente asignado.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| addr | dirección del buffer asignado |
| size | número de bytes para cambiar el tamaño |
</dd>
<dt>Valor de retorno</dt><dd>
Dirección del nuevo búfer asignado o NULL en caso de error.
</dd>
<dt>Ver también</dt><dd>
[malloc], [free]
</dd>
</dl>
<hr>
## free

```c
int free(addr_t addr)
```
<dl>
<dt>Descripción</dt><dd>
Libera la memoria de usuario asignada dinámicamente.
</dd>
<dt>Parámetros</dt><dd>
| Argumento | Descripción |
| addr | dirección del buffer asignado |
</dd>
<dt>Valor de retorno</dt><dd>
1 en caso de éxito, 0 en caso de error.
</dd>
<dt>Ver también</dt><dd>
[malloc], [realloc]
</dd>
</dl>
