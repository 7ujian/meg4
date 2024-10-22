Sound Effects
=============

<imgt ../img/sound.png> Click on the speaker icon (or press <kbd>F6</kbd>) to bring up the sound effects editor.

You can play these sound effects from your program using the [sfx] command.

<imgc ../img/soundscr.png><fig>Sound Effects</fig>

On the left, you'll see the waveform editor and its toolbar (<ui2>1</ui2>), on the right the effect selector (<ui2>2</ui2>), and
below the effect editor (<ui2>3</ui2>).

## Effect Selector

On the right you see the list of effects (<ui2>2</ui2>), each represented by a music note (technically all sound effects are music
notes, with selectable waveforms and special effects option). Clicking on this list (or pressing <kbd>▴</kbd> / <kbd>▾</kbd>) will
edit that effect.

INFO: When you select a sound effect, it's current configuration is saved to history. You can revert to this by pressing undo
until you select another sound effect. If you have pressed undo, then you will be able to do a redo until you don't modify. (The
modifications won't be saved in history one-by-one, only the state when you've selected that sound effect.)

## Effect Editor

The piano at the bottom (<ui2>3</ui2>), looks like and works like the [note editor] on the music tracks, except it has less options
selectable. You can find further info there, including the keyboard layout.

<h2 sfx_tools>Waveform Toolbar</h2>

Normally the waveform (<ui2>1</ui2>) is read-only, and you'll only see what wave the sound effect uses. You'll have to click on
the button with the lock icon to make it editable (but first, make sure your sound effect actually has a waveform choosen).

<imgc ../img/wavescr.png><fig>Waveform Toolbar</fig>

When the toolbar is unlocked, then clicking on the wave will change it.

WARN: If you change a waveform, then effective immediately all sound effects and music tracks will change too that use that
waveform.

INFO: When you unlock a waveform, it's current state is saved in history. You can revert to this by pressing undo. (The
modifications won't be saved in history one-by-one, only the wave at the moment when you've pressed unlock.)

Using the toolbar you can change the finetuning value (-8 to 7), the volume (0 to 64) and the repeat interval. If you click on
the repeat button, then it will remain pressed, and you can select a loop range on the waveform. The wave will be played first
through, then it will jump to the beginning of the selected range, and it will repeat that range infinitely.

For convenience, you have 4 default wave generator buttons, one to load the default pattern (the one that [General MIDI] uses)
from the soundfont for this wave and various tools to set the length, rotate, enlarge, shrink, negate, flip etc. the wave. The
button before the last will continously play it using its current configuration (even if no loop range defined).

Finally the last button, the <ui1>Export</ui1> will export the sample in RIFF Wave format. You can edit this with a third party
tool, and to load it back, just drag'n'drop the modified file to the MEG-4 screen.
