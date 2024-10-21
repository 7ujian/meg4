Ágyú
====

Ebben a példában egy ágyút fognunk csinálni. Minden benne van, ami az Asteroids játék alapját képezi.

Ágyúcső kirajzolása
-------------------

A szokásos vázzal indítunk. Az előző példából tudjuk, hogy le kell törölnünk a képernyőt, aztán egy [line] hívással egy egyszerű
vonal ágyút rajzolunk.

```c
#!c

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
<hm>  /* Kirajzolás */
  cls(0);
  line(23, 160, 100, 160, 100 - 10);</hm>
}
```

A képernyő közepe 160, 100-nál van, innen egy 10 pixeles csövet húzunk felfelé azáltal, hogy a vége Y koordinátából kivonunk 10-et.
Továbbá a csőhöz szürkés színt használunk (23).

Ágyúcső forgatása
-----------------

Hogy a játékos ezt forgatni tudja, szükségünk lesz egy változóra, ami az aktuális szöget tárolja, hogy merre mutat a cső.

```c
#!c

<hm>int deg;</hm>

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
<hm>  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;</hm>
  /* Kirajzolás */
  cls(0);
  line(23, 160, 100, 160, 100 - 10);
}
```

Lekérdezzük, hogy a játékos leütötte-e a jobbra vagy balra nyilakat és ennek megfelelően változtatjuk a szöget. De még nem vagyunk
készen, mert a szöget vágni is kell, méghozzá úgy, hogyha eléri az alsó értéket, akkor a legnagyobb legyen, míg ha a felső értéket,
akkor meg a legkissebb. Ennek eredményeként egy szépen körbe-körbe forgatható ágyúcsövet kapunk.

Namost hogy az ágyúcsövet ebben a szögben tudjuk kirajzolni, ahhoz tudnunk kell, hogy egy adott szög mit jelent pixelekben az
X és Y tengelyen. Talán rémlik iskolás matekóráról, hogy a szinusz és koszinusz függvények pontosan ezt adják meg. Persze egységet
adnak, azért ahhoz, hogy 10 pixel hosszú legyen a cső, az eredményt fel kell még szorozni 10-el. Lássuk!

```c
#!c

int deg;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Kirajzolás */
  cls(0);
  line(23, 160, 100, 160<hl> + cos(deg)*10</hl>, 100<hl> + sin(deg)*10</hl>);
}
```

Próbáljuk ki! Jajj, ne, nem működik, az ágyúcső megőrült! Mi történt? Ennek az oka az, hogy a [line] egész számokban várja a
koordinátákat, azonban a [sin] és [cos] lebegőpontos számot ad vissza (tehát nem `0`, hanem `0.0`). Hogy egy egész számot kapjunk
egy lebegőpontosból, konvertálnunk kell. Ezt C alatt kasztolásnak hívják, ami annyit tesz, hogy a kívánt típust zárójelek között
a kifejezés elé írjuk. Tegyük ezt.

```c
#!c

int deg;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Kirajzolás */
  cls(0);
  line(23, 160, 100, 160 + <hl>(int)</hl>cos(deg)*10, 100 + <hl>(int)</hl>sin(deg)*10);
}
```

Rendben, a cső most már 10 pixel hosszú, de nem tudjuk szabadon mozgatni, a tengelyekre tapad! Ez azért történik, mert a [sin] és
[cos] egy -1.0 és 1.0 közötti számot ad vissza, amit ha egész számmá kasztolunk, akkor össz-vissz csak három lehetséges értéket
kapunk: -1, 0 és 1. Amire nekünk itt szükségünk van, az az, hogy lebegőpontosként végezzük el az egész számolást, és majd csak
a legvégén, a végeredményt kasztoljuk.

```c
#!c

int deg;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Kirajzolás */
  cls(0);
  line(23, 160, 100, <hl>(int)(</hl>160 + cos(deg)*10<hl>)</hl>, <hl>(int)(</hl>100 + sin(deg)*10<hl>)</hl>);
}
```

Üssük le a <kbd>Ctrl</kbd>+<kbd>R</kbd>-t és látni fogjuk, hogy ezúttal pontosan úgy működik minden, ahogy szeretnénk.

Lövedék hozzáadása
------------------

Ahogy azt a [labda pattogás] példából tudjuk, ahhoz, hogy a képernyőn egy mozgó objektumunk legyen, kell két változó, ami a
koordinátáit tárolja, valamint még további kettő, ami meg azt, hogy mennyit kell elmozdulnia. Az előbbi baklövésből azt is
tudjuk, hogy a szép folyamatos mozgás érdekében lebegőpontosan kell tárolnunk ezeket a változókat.

```c
#!c

<hm>float x, y, dx, dy;</hm>
int deg;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
<hm>  x = 160.0;
  y = 100.0;
  dx = dy = 0.0;</hm>
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
<hm>  /* Lövedék mozgatása */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200) setup();</hm>
  /* Kirajzolás */
  cls(0);
<hm>  pset(8, (int)x, (int)y);</hm>
  line(23, 160, 100, (int)(160 + cos(deg)*10), (int)(100 + sin(deg)*10));
}
```

Pont ahogy a legelső példában is csináltuk, a `setup()` függvényben alaphelyzetbe állítjuk ezeket, majd a fő `loop()` függvényben
hozzáadjuk a delta értékeket a koordinátákhoz. Továbbá ellenőrizzük, hogy a lövedék elérte-e valamelyik képernyőszélet, és ha
igen, akkor meghívjuk ismét a `setup()`-ot, hogy alaphelyzetbe állítsuk a lövedék koordinátáit és elmozdulását. Magának a
lövedéknek a megjelenítésére kiteszünk egy sárga (8) pixelt a [pset] függvénnyel. Mivel ez szintén egész számban várja a
koordinátákat, ezért itt is kasztolunk.

Ágyú elsütése
-------------

Már csak egy dolog maradt hátra, hogy a játékos lőni is tudjon ezzel az ágyúval.

```c
#!c

float x, y, dx, dy;
int deg;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
  x = 160.0;
  y = 100.0;
  dx = dy = 0.0;
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
<hm>  /* Ágyú elsütése */
  if(getkey(KEY_SPACE)) {
    dx = cos(deg);
    dy = sin(deg);
    x = 160 + dx * 9;
    y = 100 + dy * 9;
  }</hm>
  /* Lövedék mozgatása */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200) setup();
  /* Kirajzolás */
  cls(0);
  pset(8, (int)x, (int)y);
  line(23, 160, 100, (int)(160 + cos(deg)*10), (int)(100 + sin(deg)*10));
}
```

Amikor a játékos leüti a <kbd>Szóköz</kbd> billentyűt, asszerint állítjuk be a dx és dy értékét, hogy a cső aktuális elfordulása
mennyi pixelt is jelent az X és Y tengelyen. Ezen kívül a lövedék koordinátáját a cső végéhez állítjuk be. A delta értékeket
csak 9-el szorozzuk meg itt, mivel mindjárt a következő dolog, amit tenni fogunk az az, hogy a léptetés miatt hozzáadjuk a delta
értékeket a koordinátákhoz, ezért ez így pont olyan, mintha 10-el szoroztunk volna.

Próbáljuk ki! Működik, de van egy kis bökkenő. Ha a lövedék már ki lett lőve, amikor a játékos <kbd>Szóköz</kbd>-t üt, akkor
a lövedék képes irányt váltani! Hogy ezt megakadályozzuk, ellenőriznünk kell, hogy ki van-e már a lövedék lőve.

```c
#!c

float x, y, dx, dy;
int deg;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
  x = 160.0;
  y = 100.0;
  dx = dy = 0.0;
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Ágyú elsütése */
  if(getkey(KEY_SPACE) <hl>&& dx == 0.0 && dy == 0.0</hl>) {
    dx = cos(deg);
    dy = sin(deg);
    x = 160 + dx * 9;
    y = 100 + dy * 9;
  }
  /* Lövedék mozgatása */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200) setup();
  /* Kirajzolás */
  cls(0);
  pset(8, (int)x, (int)y);
  line(23, 160, 100, (int)(160 + cos(deg)*10), (int)(100 + sin(deg)*10));
}
```

És ennyi lenne.

Ha lecseréljük az ágyú fix 160-as és 100-as koordinátáit újabb x, y és dx, dy változókra, akkor képesek leszünk mozgatni, és
máris van egy Asteroids űrhajónk!
