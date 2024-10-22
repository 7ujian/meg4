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

<hm>int szog;</hm>

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
<hm>  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) szog--;
  if(getkey(KEY_RIGHT)) szog++;
  if(szog < 0) szog = 359;
  if(szog > 359) szog = 0;</hm>
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
adnak, azért ahhoz, hogy 10 pixel hosszú legyen a cső, az eredményt fel kell még szorozni 10-el. Fontos, hogy a [sin] és a [cos]
függvény is lebegőpontos értéket (nem `1` hanem `1.0`) ad vissza.

```c
#!c

int szog;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) szog--;
  if(getkey(KEY_RIGHT)) szog++;
  if(szog < 0) szog = 359;
  if(szog > 359) szog = 0;
  /* Kirajzolás */
  cls(0);
  line(23, 160, 100, 160<hl> + cos(szog)*10</hl>, 100<hl> + sin(szog)*10</hl>);
}
```

Üssük le a <kbd>Ctrl</kbd>+<kbd>R</kbd>-t és látni fogjuk, hogy az ágyúcső szépen forgatható.

Lövedék hozzáadása
------------------

Ahogy azt a [labda pattogás] példából tudjuk, ahhoz, hogy a képernyőn egy mozgó objektumunk legyen, kell két változó, ami a
koordinátáit tárolja, valamint még további kettő, ami meg azt, hogy mennyit kell elmozdulnia. A labdával ellentétben, ami
csak átlósan mozgott, itt most mindenféle tetszőleges szöget akarunk használni, ezért a szép folyamatos mozgáshoz törtpixeleket
kell tárolni, tehát lebegőpontos változókra lesz szükségünk (ezért nem `int` hanem `float`).

```c
#!c

<hm>float x, y, dx, dy;</hm>
int szog;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) szog--;
  if(getkey(KEY_RIGHT)) szog++;
  if(szog < 0) szog = 359;
  if(szog > 359) szog = 0;
<hm>  /* Lövedék mozgatása */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200)
    dx = dy = 0.0;</hm>
  /* Kirajzolás */
  cls(0);
<hm>  pset(8, x, y);</hm>
  line(23, 160, 100, 160 + cos(szog)*10, 100 + sin(szog)*10);
}
```

Pont ahogy a legelső példában is csináltuk, a fő `loop()` függvényben hozzáadjuk a delta értékeket a koordinátákhoz. Továbbá
ellenőrizzük, hogy a lövedék elérte-e valamelyik képernyőszélet, és ha igen, akkor alaphelyzetbe állítjuk, hogy megakadályozzuk a
lövedék további mozgását. Magának a lövedéknek a megjelenítésére pedig kiteszünk egy sárga (8) pixelt a [pset] függvénnyel.

Ágyú elsütése
-------------

Már csak egy dolog maradt hátra, hogy a játékos lőni is tudjon ezzel az ágyúval.

```c
#!c

float x, y, dx, dy;
int szog;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) szog--;
  if(getkey(KEY_RIGHT)) szog++;
  if(szog < 0) szog = 359;
  if(szog > 359) szog = 0;
<hm>  /* Ágyú elsütése */
  if(getkey(KEY_SPACE)) {
    dx = cos(szog);
    dy = sin(szog);
    x = 160 + dx * 9;
    y = 100 + dy * 9;
  }</hm>
  /* Lövedék mozgatása */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200)
    dx = dy = 0.0;
  /* Kirajzolás */
  cls(0);
  pset(8, x, y);
  line(23, 160, 100, 160 + cos(szog)*10, 100 + sin(szog)*10);
}
```

Amikor a játékos leüti a <kbd>Szóköz</kbd> billentyűt, asszerint állítjuk be a dx és dy értékét, hogy a cső aktuális elfordulása
mennyi pixelt is jelent az X és Y tengelyen. Ezen kívül a lövedék koordinátáját a cső végéhez állítjuk be. A delta értékeket
csak 9-el szorozzuk meg itt, mivel mindjárt a következő dolog, amit tenni fogunk az az, hogy a léptetés miatt hozzáadjuk a delta
értékeket a koordinátákhoz, ezért ez így pont olyan, mintha 10-el szoroztunk volna.

Próbáljuk ki! Működik, de van egy kis bökkenő. Ha a játékos lenyomva tartja a <kbd>Szóköz</kbd>-t, akkor semmi sem történik! Ez
amiatt van, mert ilyenkor a [getkey] állandóan igaz lesz, ezért folyamatosan beállítjuk az x, y, dx, dy változókat, így aztán hiába
léptetjük. Javítsuk ki! Kelleni fog egy változó, amiben azt tároljuk, hogy el lett-e már sütve az ágyú.

```c
#!c

float x, y, dx, dy;
int szog<hl>, elsutve</hl>;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) szog--;
  if(getkey(KEY_RIGHT)) szog++;
  if(szog < 0) szog = 359;
  if(szog > 359) szog = 0;
  /* Ágyú elsütése */
  if(getkey(KEY_SPACE)) {
<hm>    if(!elsutve) {
      elsutve = 1;</hm>
      dx = cos(szog);
      dy = sin(szog);
      x = 160 + dx * 9;
      y = 100 + dy * 9;
<hm>    }</hm>
  } <hl> else
    elsutve = 0;</hl>
  /* Lövedék mozgatása */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200)
    dx = dy = 0.0;
  /* Kirajzolás */
  cls(0);
  pset(8, x, y);
  line(23, 160, 100, 160 + cos(szog)*10, 100 + sin(szog)*10);
}
```

Tehát amikor <kbd>Szóköz</kbd> le van nyomva, akkor azt is ellenőrizzük, hogy nincs az `elsutve` változó beállítva, és na nincs,
akkor beállítjuk a többi változóval egyetemben. Így most csak egyszer állítjuk be a változókat. De nem akarjuk, hogy így is
maradjon az `elsutve`, ezért amikor a <kbd>Szóköz</kbd> nincs nyomva, akkor lenullázuk, hogy legközelebb is elsüthessük az ágyút.
És ennyi lenne.

HINT: Egy blokkot raktunk akköré a sorok köré, amik beállítják a változókat. Nem kell ilyenkor egy csomó szóközt becsépelnünk,
hogy beljebb toljuk az utasításokat. Elég csak kijelölni a sorokat, és a <kbd>Ctrl</kbd>+<kbd>.</kbd> leütésével mindet egyszerre
beljebb húzza a szerkesztő.

Több lövedék
------------

A kódunknak még mindig van egy szépséghibája. Ha akkor sütjük el az ágyút, amikor már van egy lövedék kilőve, akkor az eltűnik.
Ez azért van, mert jelenleg csak egyetlen lövedéket tudunk kezelni, mert csak egy x, y, dx, dy négyesünk van. A több lövedékhez
át kell alakítanunk ezeket tömbökké, amik több értéket is képesek tárolni, egy-egy négyest minden lövedékhez.

Elsőre csak csináljunk egy elemű tömböket. Amikor deklarálunk, akkor elemszámot kell megadni a fordítónak, de amikor hivatkozunk
rájuk, akkor az indexük nullától indul, ezért egy N elemű tömb esetén 0 és N - 1 közötti lehet az index.

```c
#!c

<hm>#define N 1</hm>

float x<hl>[N]</hl>, y<hl>[N]</hl>, dx<hl>[N]</hl>, dy<hl>[N]</hl>;
int szog, elsutve;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) szog--;
  if(getkey(KEY_RIGHT)) szog++;
  if(szog < 0) szog = 359;
  if(szog > 359) szog = 0;
  /* Ágyú elsütése */
  if(getkey(KEY_SPACE)) {
    if(!elsutve) {
      elsutve = 1;
      dx<hl>[0]</hl> = cos(szog);
      dy<hl>[0]</hl> = sin(szog);
      x<hl>[0]</hl> = 160 + dx<hl>[0]</hl> * 9;
      y<hl>[0]</hl> = 100 + dy<hl>[0]</hl> * 9;
    }
  } else
    elsutve = 0;
  /* Lövedék mozgatása */
  x<hl>[0]</hl> += dx<hl>[0]</hl>;
  y<hl>[0]</hl> += dy<hl>[0]</hl>;
  if(x<hl>[0]</hl> < 0 || x<hl>[0]</hl> >= 320 || y<hl>[0]</hl> < 0 || y<hl>[0]</hl> >= 200)
    dx<hl>[0]</hl> = dy<hl>[0]</hl> = 0.0;
  /* Kirajzolás */
  cls(0);
  pset(8, x<hl>[0]</hl>, y<hl>[0]</hl>);
  line(23, 160, 100, 160 + cos(szog)*10, 100 + sin(szog)*10);
}
```

Próbáljuk ki! Ha nem rontottuk el, akkor pontosan ugyanúgy fog futni, mint ezidáig.

Hogy továbblépjünk, be kell hoznunk a ciklusokat, amik végigmennek az elemeken. Első nekifutásra alakítsuk át a léptetést és a
kirajzolást.

```c
#!c

#define N 1

float x[N], y[N], dx[N], dy[N];
int szog, elsutve;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  int i;

  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) szog--;
  if(getkey(KEY_RIGHT)) szog++;
  if(szog < 0) szog = 359;
  if(szog > 359) szog = 0;
  /* Ágyú elsütése */
  if(getkey(KEY_SPACE)) {
    if(!elsutve) {
      elsutve = 1;
      dx[0] = cos(szog);
      dy[0] = sin(szog);
      x[0] = 160 + dx[0] * 9;
      y[0] = 100 + dy[0] * 9;
    }
  } else
    elsutve = 0;
  /* Lövedékek mozgatása */
<hm>  for(i = 0; i < N; i++) {</hm>
    x[<hl>i</hl>] += dx[<hl>i</hl>];
    y[<hl>i</hl>] += dy[<hl>i</hl>];
    if(x[<hl>i</hl>] < 0 || x[<hl>i</hl>] >= 320 || y[<hl>i</hl>] < 0 || y[<hl>i</hl>] >= 200)
      dx[<hl>i</hl>] = dy[<hl>i</hl>] = 0.0;
<hm>  }</hm>
  /* Kirajzolás */
  cls(0);
<hm>  for(i = 0; i < N; i++)</hm>
    pset(8, x[<hl>i</hl>], y[<hl>i</hl>]);
  line(23, 160, 100, 160 + cos(szog)*10, 100 + sin(szog)*10);
}
```

Amint látható, nem változtattunk sokat, csak a kifejezések köré raktunk egy ciklust, a konstans `0` indexet meg lecseréltük az `i`
ciklusváltozóra. Ezáltal minden egyes ciklus ismétlődésnél a ciklusmag pontosan egy lövedéket fog léptetni. Hasonlóan jártunk el
a kirajzolásnál is, ott is egy lövedéket rajzolunk ki minden iterációban.

De lőnünk is kell tudni az ágyúval. Ez kicsit trükkösebb, mert itt keresnünk kell egy változó négyest, ami nincs használatban. És
ha találtunk, akkor meg kell állnunk, mert egyszerre csak egy lövedék változóit akarjuk állítani.

```c
#!c

#define N 1

float x[N], y[N], dx[N], dy[N];
int szog, elsutve;

void setup()
{
  /* Induláskor lefuttatandó dolgok */
}

void loop()
{
  int i;

  /* Minden képkockánál lefuttatandó dolgok, 60 FPS */
  /* Gombok lekezelése */
  if(getkey(KEY_LEFT)) szog--;
  if(getkey(KEY_RIGHT)) szog++;
  if(szog < 0) szog = 359;
  if(szog > 359) szog = 0;
  /* Ágyú elsütése */
  if(getkey(KEY_SPACE)) {
    if(!elsutve) {
      elsutve = 1;
<hm>      for(i = 0; i < N; i++)
        if(dx[i] == 0.0 && dy[i] == 0.0) {</hm>
          dx[<hl>i</hl>] = cos(szog);
          dy[<hl>i</hl>] = sin(szog);
          x[<hl>i</hl>] = 160 + dx[<hl>i</hl>] * 9;
          y[<hl>i</hl>] = 100 + dy[<hl>i</hl>] * 9;
<hm>          break;
        }</hm>
    }
  } else
    elsutve = 0;
  /* Lövedékek mozgatása */
  for(i = 0; i < N; i++) {
    x[i] += dx[i];
    y[i] += dy[i];
    if(x[i] < 0 || x[i] >= 320 || y[i] < 0 || y[i] >= 200)
      dx[i] = dy[i] = 0.0;
  }
  /* Kirajzolás */
  cls(0);
  for(i = 0; i < N; i++)
    pset(8, x[i], y[i]);
  line(23, 160, 100, 160 + cos(szog)*10, 100 + sin(szog)*10);
}
```

Ez a ciklus egy feltételes blokkot tartalmaz, ami azt nézi, hogy az adott lövedék elmozdulása nulla-e. Amennyiben igen, úgy
találtunk egy szabad lövedék változó négyest `i`-nél, amit használhatunk. Elvégezzük a korábbi beállításokat ezen az `i`-edik
négyesen, aztán a `break` kulcsszóval megszakítjuk a ciklus további futását.

Futtassuk le! Még mindig semmi változás, pontosan ugyanúgy működik, mint eddig. De hogy rávilágítsunk, miért is dolgoztunk a
tömbösítéssel ilyen keményen, változtassunk meg csak egyetlen egy dolgot:

```c
#define N 100
```

És láss csodát!

Ha lecseréljük az ágyú fix 160-as és 100-as koordinátáit újabb x, y és dx, dy változókra, akkor képesek leszünk mozgatni, és
máris van egy Asteroids űrhajónk!

