Hangeffektek
============

<imgt ../img/sound.png> A hangszoró ikonra kattinva (vagy <kbd>F6</kbd>) szerkeszthetők a hangeffektek.

A hangeffekteket a programodból az [sfx] paranccsal tudod megszólaltatni.

<imgc ../img/soundscr.png><fig>Hangeffektek</fig>

Balra található a hanghullám szerkesztő és az eszköztára (<ui2>1</ui2>), jobbra a hangeffekt választó (<ui2>2</ui2>), alattuk
pedig a hangeffekt szerkesztő (<ui2>3</ui2>).

## Effektválasztó

Jobbra látható a hangeffektek listája (<ui2>2</ui2>), mind hangjegyként ábrázolva (technikailag minden hangeffekt egy hangjegy,
konfigurálható hanghullámmal és speciális effekt opciókkal). A kívánt hangeffektre kattintva a listában az szerkeszthetővé válik
(vagy <kbd>▴</kbd> / <kbd>▾</kbd> gombokkal is választható).

## Effektszerkesztő

Alul a zongora (<ui2>3</ui2>), pontosan úgy néz ki, és úgy is műküdik, mint a zenei sávok [hangjegyszerkesztő]je, csak pár opcióval
kevesebb. Bővebb infót és a billentyűzetkosztást ott találod.

INFO: Amikor egy hangeffekt kiválasztódik, az akkori állapota elmentődik az előzményekbe. Erre bármikor vissza lehet állítani a
visszavonás kombináció lenyomásával, amíg az a hangeffekt marad a kiválasztott. Ha volt visszavonás, akkor az újrabeillesztés
is használható mindaddig, amíg nem módosítjuk. (A módosítások nem mentődnek az előzményekbe egyesével, csak az az állapot, amikor
a hangeffekt ki lett választva.)

<h2 sfx_tools>Hanghullám eszköztár</h2>

Alapból a hanghullám (<ui2>1</ui2>) nem módosítható, csak azt mutatja, hogy melyik hullámot használja az aktuális hangeffekt.
Rá kell kattintani a lakat ikonos gombra, hogy szerkeszthetővé váljon (de persze előbb győzödj meg róla, hogy a hangeffektednek
választottál ki hullámmintát).

<imgc ../img/wavescr.png><fig>Hanghullám eszköztára</fig>

Amikor a lakat nyitva, akkor a hangmintára kattintva módosítani lehet azt.

WARN: Ha módosítasz egy hanghullámot, akkor az azonnali hatállyal megváltoztat minden egyes olyan hangeffektet és hangsávot,
ami azt a hanghullámot használja.

INFO: Amikor kilakatolunk egy hanghullámot, az akkori állapota elmentődik az előzményekbe. Erre bármikor vissza lehet állítani az
visszavonás kombináció lenyomásával. (A módsítások nem mentődnek az előzményekbe egyesével, csak a hanghullám abban a pillanatban,
amikor kilakatolásra került.)

Az eszköztárat használva állítható a finomhangolás (-8-tól 7-ig), a hangerő (0-tól 64-ig) és az ismétlés. Az ismétlés gombra
kattintva az lenyomva marad, ilyenkor kijelölhetsz egy "loop" részt a hullámból. Ezután amikor a hanghullám egyszer végig
lejátszódik, utánna a kijelölt rész elejére fog ugrani, és onnan veszi a mintákat a végtelenségig ismételve a kijelölt részt.

A kényelmed kedvéért van még 4 alapértelmezett hanghullám generáló, egy gomb az alapértelmezett hullámminta betöltésére a
soundfontból (amit a [General MIDI] is használ) és mindenféle eszköz a hullám hosszának állításához, forgatásához, növeléséhez,
kicsinyítéséhez, negálásához, tükrözéséhez stb. Az utolsó előtti gomb a végtelenségig játsza a hanghullámot az épp aktuális
beállításaival (akkor is, ha nincs loop megadva).

Végezetül a legutolsó gomb, az <ui1>Export</ui1> kiexportálja a hanghullámot RIFF Wave formátumban. Ezt szerkesztheted egy
külsős programmal, majd a visszatöltéshez csak húzd rá a módosított fájlt a MEG-4 ablakára.
