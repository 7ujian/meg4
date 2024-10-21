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
unit value, so if we want our turret to be 10 pixels long, we have to multiply that by 10. Let's give it a try.

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

Try it out! Oh no, it does not work, the turret went havoc! What had happened? The reason is, [line] expects the coordinates
in integer numbers, however [sin] and [cos] returns a floating point number (it is not `0`, rather `0.0`). To get an integer
out of a float, we'll need to convert. This is done in C by casting, which is adding the desired type in parenthesis before
the expression. Let's do this.

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
  line(23, 160, 100, 160 + <hl>(int)</hl>cos(deg)*10, 100 + <hl>(int)</hl>sin(deg)*10);
}
```

Alright, the turret is now 10 pixels long, but we can't move it freely, it sticks to the axis! This happens because [sin] and
[cos] returns a value between -1.0 and 1.0, and if we cast that to an integer, we will only get three possible values: -1, 0 and 1.
What we need instead is calculating the entire expression as a floating point, and only cast the final result.

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
  line(23, 160, 100, <hl>(int)(</hl>160 + cos(deg)*10<hl>)</hl>, <hl>(int)(</hl>100 + sin(deg)*10<hl>)</hl>);
}
```

Press <kbd>Ctrl</kbd>+<kbd>R</kbd>, and you'll see that this time around it works exactly as we wanted!

Adding a Bullet
---------------

As we know from [bouncing the ball], to display a moving object we'll need two variables to store its coordinate and another
two storing how much it should move. From our previous mess up, we also know that in order to move smoothly, we'll need to
store these variables as floating point numbers.

```c
#!c

<hm>float x, y, dx, dy;</hm>
int deg;

void setup()
{
  /* Things to do on startup */
<hm>  x = 160.0;
  y = 100.0;
  dx = dy = 0.0;</hm>
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
  if(x < 0 || x >= 320 || y < 0 || y >= 200) setup();</hm>
  /* Display */
  cls(0);
<hm>  pset(8, (int)x, (int)y);</hm>
  line(23, 160, 100, (int)(160 + cos(deg)*10), (int)(100 + sin(deg)*10));
}
```

Just like we did in the first tutorial, we reset the values in `setup()`, and in the main `loop()` we add the delta values to the
current coordinates. We also check if the bullet has reached the edge of the screen, and if so then we call `setup()` again to
reset the bullet's position and movement. To display the bullet, we just set a yellow (8) pixel with [pset]. This also expects
integer arguments, so we use casting here as well.

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
  x = 160.0;
  y = 100.0;
  dx = dy = 0.0;
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
  if(x < 0 || x >= 320 || y < 0 || y >= 200) setup();
  /* Display */
  cls(0);
  pset(8, (int)x, (int)y);
  line(23, 160, 100, (int)(160 + cos(deg)*10), (int)(100 + sin(deg)*10));
}
```

When the player presses the <kbd>Space</kbd>, we set the dx and dy values depending how much pixels the current degree means
on the X and Y axis. We also set the x and y variables to point at the end of the turret. We multiply the delta values by 9
for this, because the very next thing we are about to do is adding the delta values to the current coordinates, thus resulting
in multiplying by 10.

Try it out! It works, but has a drawback though. If the bullet is already fired when the player presses <kbd>Space</kbd>, then
the bullet will change its course! To avoid this, we must check if the bullet isn't already fired.

```c
#!c

float x, y, dx, dy;
int deg;

void setup()
{
  /* Things to do on startup */
  x = 160.0;
  y = 100.0;
  dx = dy = 0.0;
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
  if(getkey(KEY_SPACE) <hl>&& dx == 0.0 && dy == 0.0</hl>) {
    dx = cos(deg);
    dy = sin(deg);
    x = 160 + dx * 9;
    y = 100 + dy * 9;
  }
  /* Move the bullet */
  x += dx;
  y += dy;
  if(x < 0 || x >= 320 || y < 0 || y >= 200) setup();
  /* Display */
  cls(0);
  pset(8, (int)x, (int)y);
  line(23, 160, 100, (int)(160 + cos(deg)*10), (int)(100 + sin(deg)*10));
}
```

And that's all about it.

By replacing the fixed 160 and 100 coordinates of the cannon with another x, y and dx, dy variables, you'll be able to move it,
and you'll get an Asteroids spaceship!
