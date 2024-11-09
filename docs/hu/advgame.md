Kalandjáték
===========

A [converter](https://gitlab.com/bztsrc/meg4/blob/main/tests/converter) eszköz képes **AdvGame JSON** forrásfájlokat MEG-4
Kalandjátékokká konvertálni. Ezek klasszikus szöveges játékok (hívják őket Interaktív Fikciónak is), ahol a játékos mondatokat
gépel be a játékban történő haladáshoz. Ezeket a mondatokat aztán igére és főnev(ek)re bontja, amikre keres. Ha talál szkriptet
az aktuális ige és főnév kombinációhoz, akkor azt lefuttatja.

Korlátok:

- igék: 32 különböző akció, egyenként 15 bájt, 8 szinonímával (max. 1536 bájt összesen)
- főnevek: 255 különböző tárgy, egyenként 15 bájt (max. 1536 bájt összesen)
- üzenetek: 32 különböző sztring szobánként, egyenként 255 bájt (max. 2048 bájt nyelvenként)
- szkriptek: 1 globális, 63 közös minden szobában, és 63 különböző szobánként
- utasítások: 21 mnemonik 8 kondícióval, elágazásmentes kivitelezés, 61 utasítás szkriptenként
- képek: alapból 1 szobánként, de használható egyéni implementáció
- szobák: 254 összesen, melyek 6 különböző irányban összeköthetőek

Játék állapot
-------------

A kalandjáték aktuális állapota egy 256 elemű bájttömben tárolódik. A legelső bájt az aktuális szoba száma, az utolsó 32 bájt
a leltárnak van fenntartva, a többi szabadon felhasználható. Ezek lehetnek jelzőbitek, számlálók, bármi. A [szkriptek] ezen a
256 bájtnyi memórián végeznek műveleteket és ez az állapot elmenthető és visszatölthető játékmentésként.

Felső szint
-----------

A forrásfájl legfelső szintjén lennie kell egy `"AdvGame"` JSON struktúrának, ami egyben a fájl azonosítója is. A mezői:

- `sprites`: sztring, 256 x 256 pixeles PNG szprájtlap elérési útja, a felső 32 sora üres
- `music`: sztringtömb, Amiga MOD (.mod) vagy MIDI (.mid) zenefájlok elérési útjai (8 elemű)
- `sounds`: sztringtömb, RIFF WAVE (.wav) formátumú fájlok elérési útjai (31 elemű)
- `setup`: számtömb, a játék induló állapota (256 elemű, mind 0 és 255 közötti, az első szám az induló szoba)
- `status`: számtömb, melyik játékállapotokat írja ki a státusz (2 elemig, többért lásd `custom`)
- `vars`: sztringtömb, a állapot indexek aliaszai, ún. "változók" (csak a JSON-ben használt)
- `rooms`: sztringtömb, a szobaszámok aliaszai (csak a JSON-ben használt)
- `verbs`: sztringtömb, a `verb1`, `verb2`, `verb3` stb. aliaszai (csak a JSON-ben használt)
- `nouns`: sztringtömb, a főnevek aliaszai (csak a JSON-ben használt)
- `colors`: 5 elemű számtömb, intró háttér- és betű-, szoba háttér- és betű-, valamint promptszín
- `textpos`: szám, szöveg pozíciója pixelekben a képernyő tetejétől számítva
- `custom`: sztringtömb, plusz kusztom C kód a felhasználói felület megjelenítésére (első az intróé, a második a szobák kódja)
- `logic`: sztringtömb, általános játék logika szkript, ami mindig minden parancs előtt lefut
- `config0`: struktúra, fő játékkonfiguráció
- `config1`: struktúra, alternatív játékkonfiguráció (többnyelvűség támogatás)
- szám/"rooms" aliasz: struktúra, szobadefiníciók.

Alapesetben feltételezi, hogy a szprájtlap ketté van vágva: a felső 128 sor szobánként cserélődik, az alsó 128 sor állandó
(felhasználói felület elemei, ikonok stb. ez utóbbiak töltődnek be a `sprites`-ról). Ha a textpos be van állítva, akkor az intrónál
és a szobáknál is textpos (de legfeljebb 96) sor a szprájtlap 32. sorától kezdődően megjelenik a szöveg fölött a képernyőn. A
kusztom felület C kóddal pedig akármilyen és akármennyi szprájt kirakható e helyett.

Konfiguráció
------------

Van egy fő- és egy alternatív konfiguráció a többnyelvűség támogatásához. A mezőik:

- `lang`: sztring, kétbetűs nyelvkkód
- `text`: sztring, intró szövege (429 bájtig)
- `answers`: 4 elemű sztringtömb, üzenetek (egyenként 63 bájtig): ismeretlen parancs, nem lehet arra menni, nem használható, játék elmentve.
- `save`: sztringtömb, játékmentés igéi (15 bájtig, 8 szinoníma)
- `load`: sztringtömb, játékbetöltés igéi
- `list`: sztringtömb, leltárlistázás igéi
- `north`: sztringtömb, északra navigálás igéi
- `west`: sztringtömb, nyugatra navigálás igéi
- `east`: sztringtömb, keletre navigálás igéi
- `south`: sztringtömb, délre navigálás igéi
- `up`: sztringtömb, emeletre navigálás igéi
- `down`: sztringtömb, alagsorba navigálás igéi
- `verb1`: sztringtömb, 1-es akció igéi (a kulcs lehet valamenyik "verbs" aliasz is)
- `verb2`: sztringtömb, 2-es akció igéi
- `verb3`: sztringtömb, 3-as akció igéi
- `verb32`: sztringtömb, 32-es akció igéi
- `nouns`: sztringtömb, tárgyak főnevei (255 sztringig)

A parszolás során a három UNICODE karakternél rövidebb szavaknak teljes egészében, egyébként csak a szó elején kell egyeznie. Emiatt
ha például a `verb1`-nek `[ "kinyit" ]`, a `nouns`-nak meg `[ "lád" ]` van megadva, akkor fel fogja ismerni azt is, ha a játékos
`kinyit láda` vagy `kinyitom a ládát` parancsot gépeli be.

Szobák
------

A szobák sorszáma 1 és 254 közötti lehet (a 0-ás szoba az intró illetve reset valamint nem járható irány navigációs parancsoknál,
a 255-ös meg a mentett játékállás helye). Egy szoba struktúra mezői:

- `image`: sztring, egy PNG elérési útja, legfeljebb 256 x 96 pixeles
- `text0`: sztringtömb, a `config0`-hoz tartozó szövegek (32 sztringig, egyenként 255 bájt)
- `text1`: sztringtömb, a `config1`-hez tartozó szövegek
- `north`: szám / sztring / sztringtömb, északi irány szkript
- `west`: szám / sztring / sztringtömb, nyugati irány szkript
- `east`: szám / sztring / sztringtömb, keleti irány szkript
- `south`: szám / sztring / sztringtömb, déli irány szkript
- `up`: szám / sztring / sztringtömb, felfele irány szkript
- `down`: szám / sztring / sztringtömb, lefele irány szkript
- `logic`: szám / sztring / sztringtömb, a szobába lépéskor automatikusan lefutó szkript
- `verbX`: szám / sztring / sztringtömb, önálló igés szkriptek (X értéke 1 és 32 közötti, vagy "verbs" aliasz)
- `verbX Y`: szám / sztring / sztringtömb, egy főnévvel rendelkező szkriptek (Y értéke 1 és 255 közötti, vagy "nouns" aliasz)
- `verbX Y Z`: szám / sztring / sztringtömb, két főnévvel rendelkező szkriptek (Y, Z értéke 1 és 255 közötti, vagy "nouns" aliasz)

A szövegek 255 bájtosak lehetnek, és minden szobának saját 32 szövege lehet, melyeket a `say` / `sayv` / `sayc` utasításokkal
lehet kiiratni.

Az 1-es számú szoba szkriptjei speciálisak abból a szempontból, hogy minden más szobában is elérhetőek. Emiatt ide érdemes egy
"Vége a játéknak" szobát rakni, aminek a logikája csak egy `jmp 0`-ás resetet tartalmaz, így nincs benne további parancsbekérés.

Szkriptek
---------

Bármelyik navigációs vagy igés parancs utánni JSON érték lehet egy nem nulla szám, ami egy szobaszám:

```
"north": 12,
```

Vagy lehet sztring, ami egy "rooms" aliasz:

```
"north": "padlás",
```

De ha egy sztringtömb, akkor az egy utasításokat tartalmazó szkript:

```
"north": [ "jmp 12" ],
```

Ezek befolyásolják a játék állapotát, szöveget jelenítenek meg, stb. Az utasítások paraméterei számok, de a megfelelő helyeken
"rooms", "vars", stb. aliaszok használhatók.

A rendelkezésre álló utasítások:

- `end`: szkript vége
- `and`: az utótagja a következő utasítás feltételéhez adódik logikai ÉS kapcsolattal
- `or`: az utótagja a következő utasítás feltételéhez adódik logikai VAGY kapcsolattal
- `bgm X`: háttérzene lejátszása (X értéke 0 és 7 közötti)
- `sfx X`: hangeffekt lejátszása (X értéke 0 és 63 közötti)
- `jmp X`: X szobába lép (X értéke 0 és 254 közötti)
- `jmpv (X)`: mint a `jmp`, de a szobát az X változóból veszi
- `call X`: meghívja az 1-es szoba X szkriptjét (X értéke 1 és 64 közötti)
- `callv (X)`: mint a `call`, de a szkript számát az X változóból veszi
- `give X`: hozzáadja az X főnevet a leltárhoz (X értéke 1 és 254 közötti)
- `take X`: kiveszi az X főnevet a leltárból
- `say X`: az X szöveg megjelenítése (X értéke 1 és 32 közötti)
- `sayv (X) Y`: az X változó értéke + Y szöveg megjelenítése
- `sayc X Y`: vagy az X (hamis), vagy az Y (igaz) szöveg megjelenítése kondíciótól függően
- `add (X) Y`: az X változó növelése Y-al (X és Y értéke 1 és 255 közötti)
- `addv (X) (Y)`: az X változó növelése Y változó értékével
- `sub (X) Y`: az X változó csökkentése Y-al (X és Y értéke 1 és 255 közötti)
- `subv (X) (Y)`: az X változó csökkentése Y változó értékével
- `set (X) Y`: az X változó értékét Y-ra állítja (Y értéke 0 és 255 közötti)
- `rnd (X) Y`: mint a `set`, de egy 0 és Y közötti véletlenszámot rak X-be
- `mov (X) (Y)`: az Y változó értékét X változóba másolja

Ezek az utasítások mind elláthatók a következő utótagok egyikével:

- nincs utótag: feltétel nélkül végrehajtódik
- `if (V) = N`: csak ha a V változó értéke N
- `if (V) != N`: csak ha a V változó értéke nem N
- `if (V) <= N`: csak ha a V változó értéke kissebb vagy egyenlő, mint N
- `if (V) < N`: csak ha a V változó értéke kissebb, mint N
- `if (V) > N`: csak ha a V változó értéke nagyobb, mint N
- `has N`: csak ha az N főnév a leltárban van
- `not N`: csak ha az N főnév nincs a leltárban

A 0-ás szobára ugrás vár egy billentyűleütésre, majd újraindítja a játékot és a 0-ás helyett a megadott induló szobára ugrik (ez
csak kifejezetten `jmp` utasításnak adható meg, mert a 0 szám nem használható, mint cél szobaszám).

Alapesetben egy szobaösszeköttetéshez szobaszámot (vagy "rooms" aliaszt) adunk meg, de ez feltétel nélkül átengedi a játékost az
egyik szobából a másikba. Például ha van egy "kulcs felvéve" jelző a 7-es állapotban, és a 11-es szobában pedig van egy ajtó az
északi irányban a 12-es szoba felé, és azt akarjuk, hogy csak akkor legyen járható, ha a játékos rendelkezik a kulccsal, akkor
szkriptelt navigációra van szükség.

```
"11": {
  "text0": [ "Az ajtó zárva." ],
  "north": [ "jmp 12 if (7) = 1", "say 1" ]
}
```

Ilyenkor a `north` mezőben szám helyett egy sztringtömben a `jmp 12 if (7) = 1` utasítást adunk meg. Ez csak abban az esetben
ugrik a 12-es szobába, ha a 7-es állapot értéke 1, egyébként marad a 11-esben. Ilyenkor mondhatjuk azt is, hogy "Az ajtó zárva"
a `say 1` utasítással (ha korábban a 12-es szobára ugrottunk, akkor ez már nem hajtódik végre). A szobaszám helyett használható
"rooms" aliasz, az állapot index (változó) helyén pedig "vars" aliasz, például `jmp padlás if kulcs = 1`. Bonyolultabb összefüggés
is megadható az `and` / `or` utasításokkal, amennyiben a befolyásolandó utasítás *elé* tesszük őket. Például hogy csak éjjel
lehessen átmenni, és csak ha lámpája is van a játékosnak, az `[ "and if éjjel = 1", "and has lámpa", "jmp padlás if kulcs = 1" ]`.

Egy másik példa, ami véletlenszerűen ugrik a 100 és 109 közötti szoba valamelyikére:

```
[ "rnd (1) 10",   /* 0 és 9 közötti véletlenszám az 1-es állapotba */
  "add (1) 100",  /* hozzáadunk 100-at így az most 100 és 109 közötti */
  "jmpv (1)" ]    /* az állapotban tárolt szobaszámra ugrás */
```

A kiírás is jöhet változóból, például ha a halál okát a 9-es állapotban tároljuk, ami 0 és 2 közötti, akkor:

```
"text0": [
  "Meghaltál, ennek oka:",  /* 1-es szöveg */
  "megfulladtál",           /* 2-es szöveg */
  "éhenhaltál",             /* 3-as szöveg */
  "bedarált a hegyirém"     /* 4-es szöveg */
],
"logic": [ "say 1", "sayv (9) 2" ]
```

Itt a `say` előbb kiírja az 1-es szöveget, majd a `sayv` veszi a 9-es állapot értékét, hozzáad 2-őt, és az annyadik szöveget írja
ki a 2-es és 4-es szövegek közül.

Ugyancsak hasznos a feltételes szövegkiírás, ami a kondíciótól függően vagy egy hamis, vagy egy igaz szöveget ír ki. Például:

```
"text0": [
  "Nincs nálad kulcs.",     /* 1-es szöveg */
  "Kinyitottad a ládát."    /* 2-es szöveg */
],
"nyit láda": [ "sayc 1 2 has kulcs", "set (10) 1 has kulcs" ]
```

Amennyiben a játékosnál nincs kulcs, úgy a `sayc` az 1-es, ha van, akkor meg a 2-es szöveget írja ki. Aztán beállítunk egy "láda
nyitva" jelzőt a `set`-el, de csak akkor, ha volt kulcs a játékosnál. (Hogy a parancs így megadható legyen, ahhoz kell egy `nyit`
"verbs" aliasz és egy `láda` "nouns" aliasz is. Mégegyszer, az aliaszok csak a JSON-ben használatosak és függetlenek a lefordítható
szavaktól, amit a játékosok a játék közben gépelnek be.)

Minta játékok
-------------

Minta MEG-4 Kalandjátékok a [meg4_advgame](https://gitlab.com/bztsrc/meg4_advgame) repóban találhatók.
