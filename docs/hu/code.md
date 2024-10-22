Kód Szerkesztő
==============

<imgt ../img/code.png> Kattints a ceruza ikonra (vagy <kbd>F2</kbd>) a program forráskódjának írásához.

A kód három alrészből áll, az egyiken szövegesen tudod a forráskódot szerkeszteni (ez), a [Vizuális Szerkesztő]ben ugyanezt
struktrogrammokkal teheted meg, a programod gépi kódú megfelelőjét pedig a [debuggoló]ban láthatod.

<imgc ../img/codescr.png><fig>Kód Szerkesztő</fig>

Itt az egész felület egy nagy forráskód szerkesztő (<ui2>1</ui2>). Alul látható a státuszsor (<ui2>2</ui2>), az aktuális sor és
oszlop értékekkel, valamint a kurzor alatti karakter UNICODE kódpontjával, továbbá ha épp egy API funkció paraméterei között áll
a kurzor, akkor egy gyorssúgóval a paraméterek listájáról (ami érvényes minden programozási nyelv esetén).

Programozási nyelv
------------------

A programnak egy speciális sorral kell kezdődnie, az első két karakter `#!`, amit a használni kívánt nyelv kódja zár. Az
alapértelmezett a [MEG-4 C](#c) (az ANSI C egyszerűsített változata), de több nyelv is a rendelkezésedre áll. A teljes listát
balra, a tartalomjegyzékben a "Programozás" címszó alatt találod.

Felhasználói funkciók
---------------------

A választott nyelvtől függetlenül van két funkció, amit neked kell implementálni. Nincs paraméterük, sem visszatérési értékük.

- `setup` funkció elhagyható, és csak egyszer fut le, amikor a programod betöltődik.
- `loop` funkció kötelező, és mindig lefut, amikor egy képkocka generálódik. 60 FPS (képkocka per másodperc) mellett ez azt
  jelenti, hogy a futására 16.6 milliszekundum áll rendelkezésre, de ebből a MEG-4 "hardver" elvesz 2-3 milliszekundumot, így
  12-13 ezredmásodperced marad, amit a függvényed kitölthet. Ezt lekérdezheted a performancia számláló MMIO regiszterből, lásd
  [memóriatérkép]. Ha ennél tovább tart a `loop` funkció futása, akkor a képernyő töredezni fog, és az emulátor kevésbé lesz
  reszponzív, mint lenni szokott.

Plusz billentyűkombók
---------------------

A normál [billentyűkön és beviteli módokon](#ui_kbd) túl, kódszerkesztéskor még számos más, szövegszerkesztés orientált
[gyorsbillentyű](#kod_szerkeszto_gyorsbillentyuk) is elérhető.

A menüből ugyancsak eléhető a keresés, következő, sorraugrás, visszavonás, újrabeillesztés, valamint a könyvjelzők és funkciók
definíciójának listája is.
