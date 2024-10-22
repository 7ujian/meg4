Font Editor
===========

<imgt ../img/font.png> Click on the letter icon (or press <kbd>F5</kbd>) to modify the fonts.

This font will be used by [width] when you measure a string, and also by [text] when you display text from your program.

<imgc ../img/fontscr.png><fig>Font Editor</fig>

This page has a similar arrangement as the [sprite editor], it's just the palette is missing. On the left you can find the glyph
editor area (<ui2>1</ui2>), and on the right the glyph selector (<ui2>2</ui2>). (Glyph is the displayed typeface of a UNICODE
character.)

Glyph Editor
------------

It is as simple as <mbl> left clicking sets typeface (foreground), and <mbr> clears to empty (background).

When the <kbd>Shift</kbd> is hold down, then a line can be drawn from last modified point.

Glyph Selector
--------------

You can search for a UNICODE codepoint, but if you press a key, the glyph selector will jump to its glyph. If your keyboard
layout lacks some keys, you can use one of the special input modes, see [keyboard](#ui_kbd).

<h2 font_tools>Toolbar</h2>

The toolbar here is limited, only shifting, rotating and flipping allowed, there are no selection tools. However copy
(<kbd>Ctrl</kbd>+<kbd>C</kbd>) and paste (<kbd>Ctrl</kbd>+<kbd>V</kbd>) works as usual on the glyph selector table.
