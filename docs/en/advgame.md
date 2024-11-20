Adventure Game
==============

The [advcomp](https://gitlab.com/bztsrc/meg4_advgame) compiler can parse **AdvGame JSON** source files and convert those into
MEG-4 Adventure Games. These are classic textual games (also known as Interactive Fiction) where the player enters sentences
in order to progress in the game. Each sentence is then parsed into a verb and noun(s), and looked up. If a script is found for
that verb and noun(s) combination, then it is executed. (The `advcomp` tool can also generate point'n'click adventure games from
the very same JSON files which are playable using `advgame`, but not by MEG-4.)

Limitations:

- verbs: 32 different actions, each 15 bytes, up to 8 synonyms (max. 1536 bytes in total)
- nouns: 255 different objects, each 15 bytes (max. 1536 bytes in total)
- messages: 32 different strings per room, each 255 bytes (max. 2048 bytes per language)
- scripts: 1 global, 63 shared by all rooms, and 63 different per on room
- instructions: 21 mnemonics with 8 conditions, branch-free design, 61 instructions per scripts
- images: 1 per room by default, but you can add custom implementation
- rooms: 254 in total, connectable in 6 different directions

Game State
----------

The Adventure Game state is an array of 256 bytes. The first byte stores the current room number, the last 32 bytes are reserved
for the inventory, all the others are up to you. You can use these as flags, you can store counters in them, whatever. [Scripts]
operate on this 256 bytes of memory, and this state can be saved and loaded in a game save file.

Top Level
---------

The source file must have an `"AdvGame"` JSON structure at the top which is also a magic. Its fields are:

- `sprites`: string, path to a 256 x 256 pixels sprite sheet PNG, the first 32 rows must be empty
- `music`: array of strings, path to Amiga MOD (.mod) or MIDI (.mid) files (up to 8 files)
- `sounds`: array of strings, path to RIFF WAVE (.wav) files (up to 31 elements)
- `setup`: array of numbers, initial game state values (up to 256 elements, each between 0 and 255, first number is starting room)
- `status`: array of numbers, game states to be shown on status (up to 2, see `custom` for more)
- `vars`: array of strings, aliases to game state indeces, aka "variables" (only used in the JSON)
- `rooms`: array of strings, aliases to room numbers (only used in the JSON)
- `verbs`: array of strings, aliases to `verb1`, `verb2`, `verb3` etc. (only used in the JSON)
- `nouns`: array of strings, aliases to nouns (only used in the JSON)
- `colors`: array of 5 numbers, intro and room background and text, and prompt color
- `pos`: number, text position from top in pixels
- `custom`: array of strings, additional C code to display user interface (first intro code, second room code)
- `logic`: array of strings, common game logic script executed before each and every command
- `config0`: structure, main game configuration
- `config1`: structure, alternative game configuration (to support multi-language)
- numbers/"rooms" alias: structure, room definitions.

Normally sprites are assumed to be splitted: top 128 rows are swapped between rooms, bottom 128 rows are constant (for ui elements,
icons, etc. this latter is loaded from `sprites`). If textpos is set, then both on the intro page and in rooms textpos rows (up
to 96 pixels) starting from the sprite sheet's row 32 will be shown on screen. With the custom user interface C code you can display
whatever and howmany sprites you'd like.

Configuration
-------------

There's a main and an alternative configuration to support more languages. Their fields are:

- `lang`: string, two letter language code
- `text`: string, intro text (up to 429 bytes)
- `answers`: array of 4 strings, messages (up to 63 bytes each): unknown verb, can't go there, can't use, game saved
- `save`: array of strings, verbs to save game (up to 15 bytes, 8 synonyms)
- `load`: array of strings, verbs to load game
- `list`: array of strings, verbs to list inventory
- `north`: array of strings, verbs to navigate to North
- `west`: array of strings, verbs to navigate to West
- `east`: array of strings, verbs to navigate to East
- `south`: array of strings, verbs to navigate to South
- `up`: array of strings, verbs to go upstrairs
- `down`: array of strings, verbs to go downstairs
- `verb1`: array of strings, verbs for action 1 (key can be one of the "verbs" aliases)
- `verb2`: array of strings, verbs for action 2
- `verb3`: array of strings, verbs for action 3
- `verb32`: array of strings, verbs for action 32
- `nouns`: array of strings, nouns for objects (up to 255 strings)

During parsing, words shorter than three UNICODE characters must match exactly, otherwise it is enough if the words starts with that.
This is needed for inflecting languages, not for English (an example could be maybe `nouns` being `[ "brit" ]` that would match both
if player typed either `briton` or `british`).

Rooms
-----

Room number goes from 1 to 254 (room 0 is the intro or reset or no direction for navigation verbs, 255 is the saved game slot).
Each room structure's fields are:

- `image`: string, path to a PNG image, up to 256 x 96 pixels
- `text0`: array of strings, texts for `config0` (up to 32 strings, each 255 bytes)
- `text1`: array of strings, texts for `config1`
- `north`: number / string / array of strings, go to North script
- `west`: number / string / array of strings, go to West script
- `east`: number / string / array of strings, go to East script
- `south`: number / string / array of strings, go to South script
- `up`: number / string / array of strings, go upstairs script
- `down`: number / string / array of strings, go downstairs script
- `logic`: number / string / array of strings, script to run when player enters this specific room
- `verbX`: number / string / array of strings, scripts with a single verb (X goes 1 to 32 or a "verbs" alias)
- `verbX Y`: number / string / array of strings, scripts with a verb and a single noun (Y goes 1 to 255, or a "nouns" alias)
- `verbX Y Z`: number / string / array of strings, scripts with a verb and two nouns (Y, Z goes 1 to 255, or a "nouns" alias)

Texts can be 255 bytes long, and each room might have 32 texts, can be displayed with the `say` / `sayv` / `sayc` instructions.

The scripts in room 1 are special in a way that they can be accessed from every other room too. Therefore it is recommended to put
a "Game over" room here, which has only a `jmp 0` reset in its logic, so that there's no further command parsing in this room.

Scripts
-------

Every JSON value after a navigation or a verb command can be a non-zero number, which is a room number:

```
"north": 12,
```

Or it can be a string, which is a "rooms" alias:

```
"north": "attic",
```

But if it is an array of strings, then it is a script with instructions:

```
"north": [ "jmp 12" ],
```

These alter the game's state, display messages, etc., Instruction arguments are numbers, but in the appropriate places "rooms",
"vars", etc. aliases can be used.

Available instructions:

- `end`: end script
- `and`: it's suffix is added to next instruction's condition with a logical AND
- `or`: it's suffix is added to next instruction's condition with a logical OR
- `bgm X`: play background music (X goes 0 to 7)
- `sfx X`: play sound effect (X goes 0 to 63)
- `jmp X`: goes to room X (X goes from 0 to 254)
- `jmpv (X)`: like `jmp`, but reads the room number from variable X
- `call X`: call script X in room 1 (X goes 1 to 64)
- `callv (X)`: like `call`, but reads the script number from variable X
- `give X`: add noun X to inventory (X goes 1 to 255)
- `take X`: remove noun X from inventory
- `say X`: says text X (X is from 1 to 32)
- `sayv (X) Y`: say text value of variable X + Y
- `sayc X Y`: either say text X (false) or Y (true) depending on condition
- `add (X) Y`: increase game state variable X by Y (X and Y goes from 1 to 255)
- `addv (X) (Y)`: increase game state variable X by value of variable Y
- `sub (X) Y`: decrease game state variable X by Y (X and Y goes from 1 to 255)
- `subv (X) (Y)`: decrease game state variable X by value of variable Y
- `set (X) Y`: set variable X to Y (Y can be 0 to 255)
- `rnd (X) Y`: like `set`, but puts a random number between 0 and Y into X
- `mov (X) (Y)`: move value of variable Y into variable X

All of these instructions can be expanded with exactly one of these suffixes:

- no suffix: unconditionally execute
- `if (V) = N`: only do if variable V equals N
- `if (V) != N`: only do if variable V isn't N
- `if (V) <= N`: only do if variable V less than or equal to N
- `if (V) < N`: only do if variable V less than N
- `if (V) > N`: only do if variable V greater than N
- `has N`: only do if noun N is in the inventory
- `not N`: only do if noun N is not in the inventory

A special case when `(V)` is 250 or above, these use the navigation drirections: 250 (or `north`), 251 (or `west`), 252 (or `east`),
253 (or `south`), 254 (or `up`), 255 (or `down`). For example to check if the room is passable to the North, that's `if north != 0`.
These state indeces are storing the inventory's bitmask, which must be accessed using the `has` and `not` conditions, so there's no
conflict.

Jumping to room 0 will wait for a keypress, then resets the game and instead of 0, jumps to the given starting room (this needs
an explicit `jmp` command as number 0 cannot be used as destination room number).

Normally to connect rooms one would specify a room number (or "rooms" alias), but this allows passing from one room to another
unconditionally. For example if you store a "has the key" flag in game state 7, and in room 11 you have a door and you only
want to allow to go North to room 12 if the player has that key, then you'll need a scripted navigation.

```
"11": {
  "text0": [ "The door is closed." ],
  "north": [ "jmp 12 if (7) = 1", "say 1" ]
}
```

Instead of a number now we have an array of strings, with a `jmp 12 if (7) = 1` instruction in the `north` property. This would
only jump to room 12 if state 7 is 1, otherwise it remains in room 11. In this case we can also say "The door is closed" with a
`say 1` instruction (if we jumped to room 12 then this won't be executed). You can use a "rooms" alias in place of a room number,
and a "vars" alias instead of a game state index (variable), for example `jmp attic if key = 1`. You can also use more complex
conditions with the `and` / `or` instructions, if you add them *before* the instruction they should affect. For example to only
allow passing when it's night and the player has a lamp too, then `[ "and if night = 1", "and has lamp", "jmp attic if key = 1" ]`.

Another example, which randomly picks a room between 100 and 109:

```
[ "rnd (1) 10",   /* random between 0 and 9 into game state 1 */
  "add (1) 100",  /* add 100 so state 1 is now between 100 and 109 */
  "jmpv (1)" ]    /* jump to the room stored in a game state */
```

Texts can be choosen depending on variables too, for example if you store the cause of death 0 to 2 in variable 9, then:

```
"text0": [
  "You're dead, because:",  /* 1st text */
  "you drown",              /* 2nd text */
  "you starved",            /* 3rd text */
  "monster eat you"         /* 4th text */
],
"logic": [ "say 1", "sayv (9) 2" ]
```

This will first display the 1st text with `say`, then `sayv` takes the value from game state 9, adds 2 to it and displays one
of the texts from 2nd to 4th.

The conditional text is also useful, which can display either a false or a true text depending on its suffix. For example:

```
"text0": [
  "You don't have a key.",  /* 1st text */
  "The chest is now open."  /* 2nd text */
],
"open chest": [ "sayc 1 2 has key", "set (10) 1 has key" ]
```

If the player does not have the key, then `sayc` will display the first, otherwise the second text. Then we set a "chest open"
flag with `set`, but only if the player has the key. (To specify the command like this, you'll need a "verbs" alias `open` and a
"nouns" alias `chest` as well. Again, aliases are only used in the JSON and they are independent to the translated words players
can type in the game.)

Example Games
-------------

Example MEG-4 Adventure Games can be found in the [meg4_advgame](https://gitlab.com/bztsrc/meg4_advgame) repository.
