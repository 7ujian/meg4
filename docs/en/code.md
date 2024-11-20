Code Editor
===========

<imgt ../img/code.png> Click on the pencil icon (or press <kbd>F2</kbd>) to write your program's source code.

Code has three sub-pages, one where you can write the source code (this one), the [Visual Editor], where you can do the same
using structograms, and your program's machine code can be seen in the [debugger].

<imgc ../img/codescr.png><fig>Code Editor</fig>

Here the entire area (<ui2>1</ui2>) is one big input field for the source code. At the bottom (<ui2>2</ui2>), you can see the
status bar, with the current row and coloumn, the UNICODE codepoint of the character under the cursor, and if you're standing
in an API's argument list, a quick help on that API function's parameters (suitable for all programming languages).

Programming Language
--------------------

The program must start with a special line, with the characters `#!` followed by the language you want to use. By default,
it uses [MEG-4 C](#c) (a subset of ANSI C), but you can choose others as well. See the list under "Programming" in the table of
contents on the left.

User Provided Functions
-----------------------

Regardless to the scripting language you choose, there are two functions that you should implement. They have no arguments and
they return no value.

- `setup` function is optional and runs only once when your program gets loaded.
- `loop` function is mandatory, and runs every time a frame is generated. At 60 FPS this means a 16.6 msecs timeframe, but the
  MEG-4 "hardware" itself takes about 2-3 msecs, which leaves you a 12-13 msecs for your function to fill. You can query this
  value from the performance counter MMIO register, see [memory map]. If it takes longer to run the `loop` function, then the
  screen might became laggy, and the emulator will be less responsive than usual.

Additional Shortcuts
--------------------

In addition to [standard keyboard shortcuts](#ui_kbd) and input methods, the code editor has lot more text editing related
[shortcuts](#code_editor_shortcuts).

From the menu, you can also access Find, Replace, Go to, Undo, Redo as well as the list of bookmarks and the defined functions.
