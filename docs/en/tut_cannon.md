Cannon
======

In this tutorial we'll create a cannon. This contains all the basics for an Asteroids game.

Display the Turret
------------------

We start with the usual skeleton. We know from the previous tutorial that we'll have to clear the screen and we'll use [line] to
draw a very simple turret.

```c
#!c

void setup()
{
  /* Things to do on startup */
}

void loop()
{
  /* Things to run for every frame, at 60 FPS */
<hm>  /* Display */
  cls(0);
  line(23, 160, 100, 160, 100 - 10);</hm>
}
```

The centre of the screen is at 160, 100 and we draw a 10 pixels long turret pointing upwards by subtracting 10 pixels from the
end Y coordinate. We also gave it a grayish color (23).

Rotating the Turret
-------------------

In order to make the player able to rotate this, we'll need a variable to keep track of the current degree where the turret
should point to.

```c
#!c

<hm>int deg;</hm>

void setup()
{
  /* Things to do on startup */
}

void loop()
{
  /* Things to run for every frame, at 60 FPS */
<hm>  /* User input */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;</hm>
  /* Display */
  cls(0);
  line(23, 160, 100, 160, 100 - 10);
}
```

We query if the player has pressed left or right arrow keys, and we change the degree accordingly. We are not ready yet, because
we must also clip the degree and make it so that when we reach the lower limit we set the highest value, and when we reach the
higher limit we set the lowest value. This will result in a nicely rotating around the clock turret.

Now to display the turret rotated at this degree, we'll need to know how much that degree means in pixels on the X and Y axis.
One might remember from school math class that this is exactly what sinus and cosinus functions do. Of course they return a
unit value, so if we want our turret to be 10 pixels long, we have to multiply that by 10. It is important that [sin] and [cos]
returns a floating point number (so not `1` but `1.0`).

```c
#!c

int deg;

void setup()
{
  /* Things to do on startup */
}

void loop()
{
  /* Things to run for every frame, at 60 FPS */
  /* User input */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Display */
  cls(0);
  line(23, 160, 100, 160<hl> + cos(deg)*10</hl>, 100<hl> + sin(deg)*10</hl>);
}
```

Press <kbd>Ctrl</kbd>+<kbd>R</kbd>, and you'll see that the turret is nicely rotating!

Adding a Bullet
---------------

As we know from [bouncing the ball], to display a moving object we'll need two variables to store its coordinate and another
two storing how much it should move. Unlike that ball, which only moved in diagonal, here we want to handle any arbitrary degree,
so for a smooth movement we need to store sub-pixels, therefore we'll use floating point numbers for these variables (not `int`
but `float`).

```c
#!c

<hm>float x, y, dx, dy;</hm>
int deg;

void setup()
{
  /* Things to do on startup */
}

void loop()
{
  /* Things to run for every frame, at 60 FPS */
  /* User input */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
<hm>  /* Move the bullet */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200)
    dx = dy = 0.0;</hm>
  /* Display */
  cls(0);
<hm>  pset(8, x, y);</hm>
  line(23, 160, 100, 160 + cos(deg)*10, 100 + sin(deg)*10);
}
```

Just like we did in the first tutorial, in the main `loop()` we add the delta values to the current coordinates. We also check if
the bullet has reached the edge of the screen, and if so then we reset to stop the bullet's further movement. To display the bullet,
we just simply set a yellow (8) pixel with [pset].

Firing the Cannon
-----------------

One last thing left is to make the player able to fire this cannon.

```c
#!c

float x, y, dx, dy;
int deg;

void setup()
{
  /* Things to do on startup */
}

void loop()
{
  /* Things to run for every frame, at 60 FPS */
  /* User input */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
<hm>  /* Fire the cannon */
  if(getkey(KEY_SPACE)) {
    dx = cos(deg);
    dy = sin(deg);
    x = 160 + dx * 9;
    y = 100 + dy * 9;
  }</hm>
  /* Move the bullet */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200)
    dx = dy = 0.0;
  /* Display */
  cls(0);
  pset(8, x, y);
  line(23, 160, 100, 160 + cos(deg)*10, 100 + sin(deg)*10);
}
```

When the player presses the <kbd>Space</kbd>, we set the dx and dy values depending how much pixels the current degree means
on the X and Y axis. We also set the x and y variables to point at the end of the turret. We multiply the delta values by 9
for this, because the very next thing we are about to do is adding the delta values to the current coordinates, thus resulting
in multiplying by 10.

Try it out! It works, but has a drawback though. If the player holds down the <kbd>Space</kbd>, then nothing happens. This is
because [getkey] will return constantly true, so we keep setting the x, y, dx, dy variables to the same values, and movement
can't happen. Let's fix this! We need a variable to keep track if we have already fired the cannon.

```c
#!c

float x, y, dx, dy;
int deg<hl>, fired</hl>;

void setup()
{
  /* Things to do on startup */
}

void loop()
{
  /* Things to run for every frame, at 60 FPS */
  /* User input */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Fire the cannon */
  if(getkey(KEY_SPACE)) {
<hm>    if(!fired) {
      fired = 1;</hm>
      dx = cos(deg);
      dy = sin(deg);
      x = 160 + dx * 9;
      y = 100 + dy * 9;
<hm>    }</hm>
  } <hl> else
    fired = 0;</hl>
  /* Move the bullet */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200)
    dx = dy = 0.0;
  /* Display */
  cls(0);
  pset(8, x, y);
  line(23, 160, 100, 160 + cos(deg)*10, 100 + sin(deg)*10);
}
```

So when <kbd>Space</kbd> is pressed, we also check if `fired` variable is not set, and if it isn't, then we set it along with the
other variables. This way we'll only set the other variables once. But we don't want to keep `fired` that way, therefore when
<kbd>Space</kbd> is not pressed, we clear that flag so that we could fire the cannon again. And that's all about it.

HINT: We have added a block around the lines which set those variables. No need to type so many spaces to indent all those lines,
you can select the lines and press <kbd>Ctrl</kbd>+<kbd>.</kbd> to make the editor increase indentation at once.

Multiple Bullets
----------------

Our code still has an issue. If we fire the cannon when a bullet is already fired, then the first bullet disappears. This is
because we can only handle one bullet at a time, we have only one x, y, dx, dy quadlet. To support more bullets, we need to convert
these to arrays which can hold multiple values, one quadlet for each bullet.

At first, just create arrays with one element. When we declare them, we need to tell the compiler the number of elements, but when
we reference them, we use an index starting from zero, therefore the indeces of an array with N elements goes 0 to N - 1.

```c
#!c

<hm>#define N 1</hm>

float x<hl>[N]</hl>, y<hl>[N]</hl>, dx<hl>[N]</hl>, dy<hl>[N]</hl>;
int deg, fired;

void setup()
{
  /* Things to do on startup */
}

void loop()
{
  /* Things to run for every frame, at 60 FPS */
  /* User input */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Fire the cannon */
  if(getkey(KEY_SPACE)) {
    if(!fired) {
      fired = 1;
      dx<hl>[0]</hl> = cos(deg);
      dy<hl>[0]</hl> = sin(deg);
      x<hl>[0]</hl> = 160 + dx<hl>[0]</hl> * 9;
      y<hl>[0]</hl> = 100 + dy<hl>[0]</hl> * 9;
    }
  } else
    fired = 0;
  /* Move the bullet */
  x<hl>[0]</hl> += dx<hl>[0]</hl>;
  y<hl>[0]</hl> += dy<hl>[0]</hl>;
  if(x<hl>[0]</hl> < 0 || x<hl>[0]</hl> >= 320 || y<hl>[0]</hl> < 0 || y<hl>[0]</hl> >= 200)
    dx<hl>[0]</hl> = dy<hl>[0]</hl> = 0.0;
  /* Display */
  cls(0);
  pset(8, x<hl>[0]</hl>, y<hl>[0]</hl>);
  line(23, 160, 100, 160 + cos(deg)*10, 100 + sin(deg)*10);
}
```

Try this out! It should work exactly as before.

Now moving on, we introduce loops, which iterates on all elements. First, let's do this with the movement and the display.

```c
#!c

#define N 1

float x[N], y[N], dx[N], dy[N];
int deg, fired;

void setup()
{
  /* Things to do on startup */
}

void loop()
{
<hm>  int i;</hm>

  /* Things to run for every frame, at 60 FPS */
  /* User input */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Fire the cannon */
  if(getkey(KEY_SPACE)) {
    if(!fired) {
      fired = 1;
      dx[0] = cos(deg);
      dy[0] = sin(deg);
      x[0] = 160 + dx[0] * 9;
      y[0] = 100 + dy[0] * 9;
    }
  } else
    fired = 0;
  /* Move the bullets */
<hm>  for(i = 0; i < N; i++) {</hm>
    x[<hl>i</hl>] += dx[<hl>i</hl>];
    y[<hl>i</hl>] += dy[<hl>i</hl>];
    if(x[<hl>i</hl>] < 0 || x[<hl>i</hl>] >= 320 || y[<hl>i</hl>] < 0 || y[<hl>i</hl>] >= 200)
      dx[<hl>i</hl>] = dy[<hl>i</hl>] = 0.0;
<hm>  }</hm>
  /* Display */
  cls(0);
<hm>  for(i = 0; i < N; i++)</hm>
    pset(8, x[<hl>i</hl>], y[<hl>i</hl>]);
  line(23, 160, 100, 160 + cos(deg)*10, 100 + sin(deg)*10);
}
```

As you can see, we didn't change much, we just put a loop around the expressions, and we have replaced the constant `0` index with
the loop variable `i`. This way on each iteration the loop body moves one bullet. Same way, we use another loop to display one
bullet in each iteration.

We also have to make the cannon fire a bullet. This is a bit trickier, as we'll have to find a quadlet of variables which is not
being used. And once we find one, we need to stop, because we only want to set one bullet's variables.

```c
#!c

#define N 1

float x[N], y[N], dx[N], dy[N];
int deg, fired;

void setup()
{
  /* Things to do on startup */
}

void loop()
{
  int i;

  /* Things to run for every frame, at 60 FPS */
  /* User input */
  if(getkey(KEY_LEFT)) deg--;
  if(getkey(KEY_RIGHT)) deg++;
  if(deg < 0) deg = 359;
  if(deg > 359) deg = 0;
  /* Fire the cannon */
  if(getkey(KEY_SPACE)) {
    if(!fired) {
      fired = 1;
<hm>      for(i = 0; i < N; i++)
        if(dx[i] == 0.0 && dy[i] == 0.0) {</hm>
          dx[<hl>i</hl>] = cos(deg);
          dy[<hl>i</hl>] = sin(deg);
          x[<hl>i</hl>] = 160 + dx[<hl>i</hl>] * 9;
          y[<hl>i</hl>] = 100 + dy[<hl>i</hl>] * 9;
<hm>          break;
        }</hm>
    }
  } else
    fired = 0;
  /* Move the bullets */
  for(i = 0; i < N; i++) {
    x[i] += dx[i];
    y[i] += dy[i];
    if(x[i] < 0 || x[i] >= 320 || y[i] < 0 || y[i] >= 200)
      dx[i] = dy[i] = 0.0;
  }
  /* Display */
  cls(0);
  for(i = 0; i < N; i++)
    pset(8, x[i], y[i]);
  line(23, 160, 100, 160 + cos(deg)*10, 100 + sin(deg)*10);
}
```

So this loop contains a conditional, which checks if a certain bullet's movement is zero. If so, then we have found an empty bullet
slot at `i` that we can use. We do the same setup as before on the `i`th quadlet, and then the `break` keyword quits the loop.

Let's run this! Still no change, works exactly as before. To put into perspective why we have worked so hard with these arrays,
change only one thing:

```c
#define N 100
```

And presto!

By replacing the fixed 160 and 100 coordinates of the cannon with another x, y and dx, dy variables, you'll be able to move it,
and you'll get an Asteroids spaceship!

