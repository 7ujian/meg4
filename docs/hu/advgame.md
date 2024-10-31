Kalandjátékmotor
================

A [converter](https://gitlab.com/bztsrc/meg4/blob/main/tests/converter) eszköz képes AdvGame JSON forrásfájlokat MEG-4
Kalandjátékokká konvertálni. Ezek klasszikus szöveges játékok (hívják őket Interaktív Fikciónak is), ahol a játékos mondatokat
gépel be a játékban történő haladáshoz. Ezeket a mondatokat aztán igére és főnev(ek)re bontja, amikre keres. Ha talál szkriptet
az aktuális ige és főnév kombinációhoz, akkor azt lefuttatja.

Korlátok:

- igék: 16 különböző akció, egyenként 15 bájt, opcionálisan 4 szinonímával
- főnevek: 96 különböző tárgy, egyenként 15 bájt
- üzenetek: 16 különböző sztring szobánként, egyenként 127 bájt
- szkriptek: 1 globális, szobánként pedig 63  (1 automatikusan lefut, amikor a szobába lépnek)
- utasítások: 32 mnemonik, egyszerű elágazásmentes kivitelezés, 61 utasítás szkriptenként
- képek: alapból 1 szobánként, de használható egyéni implementáció
- szobák: 253 összesen, melyek 6 különböző irányban összeköthetők

Játék állapot
-------------

A kalandjáték aktuális állapota egy 256 elemű bájttömben tárolódik. A legelső bájt az aktuális szoba száma, a többi szabadon
felhasználható. Ezek lehetnek jelzőbitek, változók, bármi. Ez az állapot elmenthető és visszatölthető játékmentésként.

Felső szint
-----------

A forrásfájl legfelső szintjén lennie kell egy `"AdvGame"` struktúrának, ami egyben a fájl azonosítója is. A mezői:

- `sprites`: sztring, egy PNG elérési útja, az alapértelmezett 256 x 256 pixeles szprájtképet tölti be, a felső 32 sornak üresnek kell lennie
- `setup`: számtömb, a játék induló állapota (256 elemű, mind 0 és 255 közötti, az első szám az induló szoba)
- `verbs`: sztringtömb, a `verb1`, `verb2`, `verb3` stb. aliaszai (csak a JSON-ben használt)
- `nouns`: sztringtömb, a főnevek aliaszai (csak a JSON-ben használt)
- `vars`: sztringtömb, a játékállapot indexeinek aliaszai (csak a JSON-ben használt)
- `colors`: 5 elemű számtömb, intró háttér-, intró betű-, szoba háttér-, szoba betű- és promptszín
- `textpos`: szám, szöveg pozíciója pixelekben a képernyő tetejétől számítva
- `custom`: sztringtömb, plusz kusztom kód a felhasználói felület megjelenítésére (első az intróé, a második a szobák kódja)
- `logic`: sztringtömb, általános játék logika, ami mindig lefut, ha egy szobába lép a játékos
- `config0`: struktúra, fő játékkonfiguráció
- `config1`: struktúra, alternatív játékkonfiguráció (többnyelvűség támogatás)
- számok: struktúra, szobadefiníciók, a szobák száma 1 és 254 közötti (0-ás szoba az intró, a 255-ös meg a mentett játékállás helye)

Alapesetben feltételezi, hogy a szprájtlap ketté van vágva: a felső 128 sor szobánként cserélődik, az alsó 128 sor állandó
(felhasználói felület elemei, ikonok stb.) Ha a textpos be van állítva, akkor az intrónál és a szobáknál is a 32 és textpos közötti
(96-ig) sorok megjelennek a szöveg fölött. A kusztom kóddal pedig akármennyi és akármilyen szprájt kirakható e helyett.

Konfiguráció
------------

Van egy fő- és egy alternatív konfiguráció a többnyelváség támogatásához. A mezőik:

- `lang`: sztring, kétbetűs nyelvkkód
- `text`: sztring, intró szövege (429 bájtig)
- `answers`: 4 elemű sztringtömb, üzenetek (63 bájtig): ismeretlen parancs, nem lehet arra menni, nem használható, játék elmentve.
- `save`: sztringtömb, játékmentés igéje (15 bájtig, 4 szinoníma)
- `load`: sztringtömb, játékbetöltés igéje
- `north`: sztringtömb, északra navigálás igéje
- `west`: sztringtömb, nyugatra navigálás igéje
- `east`: sztringtömb, keletre navigálás igéje
- `south`: sztringtömb, délre navigálás igéje
- `up`: sztringtömb, emeletre navigálás igéje
- `down`: sztringtömb, alagsorba navigálás igéje
- `verb1`: sztringtömb, 1-es akció igéje (4 variánssal, egyenként 15 bájt; a kulcs lehet valamenyik aliasz)
- `verb2`: sztringtömb, 2-es akció igéje
- `verb3`: sztringtömb, 3-as akció igéje
- `verb16`: sztringtömb, 16-os akció igéje
- `nouns`: sztringtömb, tárgyak főnevei (96 sztringig)

Szobák
------

A szoba száma 1 és 254 közötti. A mezői:

- `image`: sztring, egy PNG elérési útja. Szélessége 256 pixel, magassága legfeljebb 96 pixeles
- `north`: szám, szoba északra (0 jelentése nem járható irány)
- `west`: szám, szoba nyugatra (0 jelentése nem járható irány)
- `east`: szám, szoba keletre (0 jelentése nem járható irány)
- `south`: szám, szoba délre (0 jelentése nem járható irány)
- `up`: szám, szoba felette (0 jelentése nem járható irány)
- `down`: szám, szoba alatta (0 jelentése nem járható irány)
- `text0`: sztringtömb, a `config0`-hoz tartozó szövegek (16 sztringig, egyenként 127 bájt)
- `text1`: sztringtömb, a `config1`-hez tartozó szövegek
- `logic`: sztringtömb, a szobába lépéskor automatikusan lefutó szkript (ehhez nincs aliasz)
- `verbX`: sztringtömb, önálló igés parancs (X értéke 1 és 16 közötti, vagy verbs aliasz)
- `verbX Y`: sztringtömb, egy főnévvel rendelkező parancsok (Y értéke 1 és 96 közötti)
- `verbX Y Z`: sztringtömb, két főnévvel rendelkező parancsok (Y, Z értéke 1 és 96 közötti)

A szövegek 127 bájtosak lehetnek, és minden szobának saját 16 szövege lehet, melyeket a `say` / `sayz` / `saynz` utasításokkal
lehet megjeleníteni.

Ha a szoba logika meg van adva, akkot előbb mindig az általános játéklogika fut le, aztán a szobáé.

Utasítások
----------

Ezek befolyásolják a játék állapotát, szöveget jelenítenek meg, stb. és a `logic` és a szobák `verb*` mezőiben szerepelnek.

- `end`: szkript vége
- `mus X`: háttérzene lejátszása (X értéke 0 és 7 közötti)
- `sfx X`: hangeffekt lejátszása (X értéke 0 és 63 közötti)
- `sfxz X Y`: X hangeffekt lejátszása, ha az Y változó nulla
- `sfxnz X Y`: X hangeffekt lejátszása, ha az Y változó nem nulla
- `say X`: szöveg megjelenítése (X értéke 1 és 16 közötti)
- `sayz X Y`: az X szöveg megjelenítése, ha az Y változó nulla
- `saynz X Y`: az X szöveg megjelenítése, ha az Y változó nem nulla
- `inc X`: egyik változó növelése (X értéke 1 és 255 közötti)
- `incz X Y`: X változó növelése, ha az Y változó nulla
- `incnz X Y`: X változó növelése, ha az Y változó nem nulla
- `dec X`: egyik változó csökkentése (X értéke 1 és 255 közötti)
- `decz X Y`: X változó csökkentése, ha az Y változó nulla
- `decnz X Y`: X változó csökkentése, ha az Y változó nem nulla
- `set X Y`: X változó értékét Y-ra állítja (Y értéke 0 és 255 közötti)
- `setz X Y Z`: X változó értékét Y-ra állítja, ha a Z változó nulla
- `setnz X Y Z`: X változó értékét Y-ra állítja, ha a Z változó nem nulla
- `jmp X`: X szobába lép (X értéke 1 és 254 közötti)
- `jz X Y`: X szobába lép, ha az Y változó nulla
- `jnz X Y`: X szobába lép, ha az Y változó nem nulla
- `nz X Y`: északra lévő szobát X-re állítja, ha az Y változó nulla
- `nnz X Y`: északra lévő szobát X-re állítja, ha az Y változó nem nulla
- `wz X Y`: nyugatra lévő szobát X-re állítja, ha az Y változó nulla
- `wnz X Y`: nyugatra lévő szobát X-re állítja, ha az Y változó nem nulla
- `ez X Y`: keletre lévő szobát X-re állítja, ha az Y változó nulla
- `enz X Y`: keletre lévő szobát X-re állítja, ha az Y változó nem nulla
- `sz X Y`: délre lévő szobát X-re állítja, ha az Y változó nulla
- `snz X Y`: délre lévő szobát X-re állítja, ha az Y változó nem nulla
- `uz X Y`: felette lévő szobát X-re állítja, ha az Y változó nulla
- `unz X Y`: felette lévő szobát X-re állítja, ha az Y változó nem nulla
- `dz X Y`: alatta lévő szobát X-re állítja, ha az Y változó nulla
- `dnz X Y`: alatta lévő szobát X-re állítja, ha az Y változó nem nulla

Az utolsó 12 utasítás a navigáció feltételes szabályozásához használatos. Például ha van egy "kulcs felvéve" jelző a 8-as
állapotban, és a 11-es szobában pedig van egy ajtó az északi irányban a 12-es szoba felé, és azt akarjuk, hogy csak akkor legyen
járható, ha a játékos rendelkezik a kulccsal. Ilyenkor nem a 11-es szoba `north` mezőjét kell állítani, hanem a `logic`-hoz kell
hozzáadni egy `nnz 12 8` utasítást. Ez csak akkor teszi járhatóvá az északi irányt a 12-es szoba felé, ha a 8-as állapot be lett
állítva.

Minta játék
-----------

Minta MEG-4 Kalandjáték a [meg4_idoregesz](https://gitlab.com/bztsrc/meg4_idoregesz) repóban található.
