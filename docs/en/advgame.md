Adventure Game Engine
=====================

The [converter](https://gitlab.com/bztsrc/meg4/blob/main/tests/converter) can parse AdvGame JSON source files and convert those
into MEG-4 Adventure Games. These are classic textual games (also known as Interactive Fiction) where the player enters sentences
in order to progress. Each sentence is then parsed into a verb and noun(s), and looked up. If a script is found for that verb and
noun(s) combination, then it is executed.

Limitations:

- verbs: 16 different actions, each 15 bytes, optionally up to 4 synonyms
- nouns: 96 different objects, each 15 bytes
- messages: 16 different strings per room, each 127 bytes
- scripts: 1 global, 63 per on room (1 executes automatically when the player enters the room)
- instructions: 32 mnemonics, simple branch-free design, 61 instructions per scripts
- images: 1 per room by default, but you can add custom implementation
- rooms: 253 in total, connectable in 6 different directions

Game State
----------

The Adventure Game state is an array of 256 bytes. The first byte stores the current room number, all the others are up to you.
You can use these as flags, you can store variables in them, whatever. This state can be saved and loaded in a game save file.

Top Level
---------

The source file must have a `"AdvGame"` structure at the top which is also a magic. Its fields are:

- `sprites`: string, path to a PNG, loads a default 256 x 256 pixels sprite image, the first 32 rows must be empty
- `setup`: array of numbers, initial game state values (up to 256 elements, each between 0 and 255, first number is starting room)
- `verbs`: array of strings, aliases to `verb1`, `verb2`, `verb3` etc. (only used in the JSON)
- `nouns`: array of strings, aliases to nouns (only used in the JSON)
- `vars`: array of strings, aliases to game state indeces (only used in the JSON)
- `colors`: array of 5 integers, intro background, intro text, room background, room text, prompt color
- `textpos`: integer, text position from top in pixels
- `custom`: array of strings, additional code to display user interface (first string intro, second string room)
- `logic`: array of strings, common game logic executed when entering any room
- `config0`: structure, main game configuration
- `config1`: structure, alternative game configuration (to support multi-language)
- numbers: structure, room definitions, room number goes from 1 to 254 (room 0 is the intro page, 255 is the saved game slot)

Normally sprites are assumed to be splitted: top 128 rows are swapped between rooms, bottom 128 rows are fixed (for ui elements,
icons, etc.). If textpos is set, then both on the intro page and in rooms rows 32 to textpos (up to 96 pixels) will be shown. With
the custom ui code you can display whatever and however sprites you'd like.

Configuration
-------------

There's a main and an alternative configuration to support more languages. Its fields are:

- `lang`: string, two letter language code
- `text`: string, intro text (up to 429 bytes)
- `answers`: array of 4 string, messages (up to 63 bytes): unknown verb, can't go there, can't use, game saved
- `save`: array of strings, commands to save game (up to 15 bytes, 4 synonyms)
- `load`: array of strings, commands to load game
- `north`: array of strings, verbs to navigate to North
- `west`: array of strings, verbs to navigate to West
- `east`: array of strings, verbs to navigate to East
- `south`: array of strings, verbs to navigate to South
- `up`: array of strings, verbs to go upstrairs
- `down`: array of strings, verbs to go downstairs
- `verb1`: array of strings, verbs for action 1 (up to 4 variants, each 15 bytes; key can be one of the verbs aliases)
- `verb2`: array of strings, verbs for action 2
- `verb3`: array of strings, verbs for action 3
- `verb16`: array of strings, verbs for action 16
- `nouns`: array of strings, nouns for objects (up to 96 strings)

Rooms
-----

Room numbers are 1 to 254. Its fields are:

- `image`: string, path to a PNG image. Width is up to 256 pixels, height is up to 96 pixels.
- `north`: number, room on the North / array of strings, script to run when player goes North
- `west`: number, room on the West / array of strings, script to run when player goes West
- `east`: number, room on the East / array of strings, script to run when player goes East
- `south`: number, room on the South / array of strings, script to run when player goes North
- `up`: number, room upstairs / array of strings, script to run when player goes upstairs
- `down`: number, room downstairs / array of strings, script to run when player goes downstairs
- `text0`: array of strings, texts for `config0` (up to 16 strings, each 127 bytes)
- `text1`: array of strings, texts for `config1`
- `logic`: array of strings, commands to run when player enters this specific room (there's no alias for this)
- `verbX`: array of strings, commands for a single verb (X goes 1 to 16 or one of the verbs aliases)
- `verbX Y`: array of strings, commands for a verb with a single noun (Y goes 1 to 96)
- `verbX Y Z`: array of strings, commands for a verb with two nouns (Y, Z goes 1 to 96)

Texts can be 127 bytes long, and each room might have 16 texts, which can be displayed with `say` / `sayz` / `saynz`.

If room logic is given, then first game logic runs, then room logic.

With the directions number 0 means invalid direction, otherwise if you pass an array of strings, you can add a script
with custom logic.

Commands
--------

These alter the game's state, display messages, etc., and are listed in `logic` and room's `verb*` fields.

- `end`: end script
- `reset`: wait for a keypress and reset game
- `mus X`: play background music (X goes 0 to 7)
- `sfx X`: play sound effect (X goes 0 to 63)
- `sfxz X Y`: play sound effect X if variable Y is zero
- `sfxnz X Y`: play sound effect X if variable Y is non-zero
- `say X`: says one of the texts (X is from 1 to 16)
- `sayz X Y`: say text X if variable Y is zero
- `saynz X Y`: say text X if variable Y is non-zero
- `inc X`: increases one of the game variables (X goes from 1 to 255)
- `incz X Y`: increases variables X if variable Y is zero
- `incnz X Y`: increases variables X if variable Y is non-zero
- `dec X`: decreases one of the game variables (X goes from 1 to 255)
- `decz X Y`: decreases variables X if variable Y is zero
- `decnz X Y`: decreases variables X if variable Y is non-zero
- `set X Y`: sets variable X to Y (Y can be 0 to 255)
- `setz X Y Z`: sets variable X to Y if variable Z is zero
- `setnz X Y Z`: sets variable X to Y if variable Z is non-zero
- `jmp X`: goes to room X (X goes from 1 to 254)
- `jz X Y`: goes to room X if variable Y is zero
- `jnz X Y`: goes to room X if variable Y is non-zero
- `nz X Y`: set the room to the North to X if variable Y is zero
- `nnz X Y`: set the room to the North to X if variable Y is non-zero
- `wz X Y`: set the room to the West to X if variable Y is zero
- `wnz X Y`: set the room to the West to X if variable Y is non-zero
- `ez X Y`: set the room to the East to X if variable Y is zero
- `enz X Y`: set the room to the East to X if variable Y is non-zero
- `sz X Y`: set the room to the South to X if variable Y is zero
- `snz X Y`: set the room to the South to X if variable Y is non-zero
- `uz X Y`: set the room upstairs to X if variable Y is zero
- `unz X Y`: set the room upstairs to X if variable Y is non-zero
- `dz X Y`: set the room downstairs to X if variable Y is zero
- `dnz X Y`: set the room downstairs to X if variable Y is non-zero

The last 12 instructions can be used to alter the navigation conditionally. For example you store a "has the key" flag in game
state 8, and in room 11 you has a door and you only want to allow to go North to room 12 if the player has that key. In this case
do not set the `north` property for room 11, instead add `nnz 12 8` to its `logic`. This will only enable the North direction to
room 12 if game state 8 is set.

Example Game
------------

An example MEG-4 Adventure Game can be found in the [meg4_idoregesz](https://gitlab.com/bztsrc/meg4_idoregesz) repository.
