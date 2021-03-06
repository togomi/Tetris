# Essesntial  Functionality

## The Grid
The vast majority of tetromino based game use a playfield 10 cells wide and between 16 and 24 cells tall. I chose 20 cells tall grid.

We can represent this in a multi-dimenstional array, containing 20 sub-arrays of 10 elements.

---
## Block Shapes

``` c++
// Define Shape
int shapes[7][4][4] =
{
    1,0,0,0,
    1,0,0,0,
    1,0,0,0,
    1,0,0,0, // I

    1,0,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0, // Z

    0,1,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0, // S

    1,0,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0, // T

    1,0,0,0,
    1,0,0,0,
    1,1,0,0,
    0,0,0,0, // L

    0,1,0,0,
    0,1,0,0,
    1,1,0,0,
    0,0,0,0, // J

    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0 // O
};
```

---

## Collision Detection (Boundary Check)
If a block hits boudary, should not go outside of the well.

```c++
// Define grid parameters
const int CellSize = 25;
const int Width = 10;
const int Height = 20;

// Define Grid (World)
int GRID[Height][Width] = { 0 };

...

// boundary check for a block
auto check_block_bounary = [&]()
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (shapes[block][y][x] == 0)
                continue;

            // hit Grid boundary
            if (x + b_x < 0 || x + b_x >= Width || y + b_y >= Height)
                return false;

            // collsion with GRID blocks
            if (GRID[y + b_y][x + b_x] == true)
                return false;
        }

    }
    return true;
};
```
---

## Falling and Stacking Blocks
Falling
```c++
// fall down
auto fall_down = [&]()
{
    b_y++;

    // hit bottom
    if (check_block_boundary() == false)
    {
        b_y--;
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (shapes[block][y][x])
                {
                    //+1 for avoiding 0
                    world[b_y + y][b_x + x] = block + 1;
                }

            }
        }

        //start next block
        new_block();

        return false;
    }
    return true;
};
```

Using Timer to Fall down
```c++
Clock clock;

// start clock
static float prev = clock.getElapsedTime().asSeconds();
if (clock.getElapsedTime().asSeconds() - prev >= 0.5)
{
    prev = clock.getElapsedTime().asSeconds();
    fall_down();
}
```

Stacking: Keep track of world record
```c++
// draw world
auto draw_world = [&]()
{
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            if (world[y][x])
            {
                cell.setFillColor(colors[world[y][x] - 1]);
                cell.setPosition(Vector2f(x * CellSize, y * CellSize));
                window.draw(cell);
            }
        }
    }
};
draw_world();
```

---

## Block Rotation
When space bar is pressed, rotate the generated block counter-clock wise (90 degree).
```c++
// rotate shape
auto rotate = [&]()
{
    // check rotation block size
    int len = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (shapes[block][y][x])
            {
                len = max(max(x, y) + 1, len);
            }
        }
    }

    int rotated_block[4][4] = { 0 };

    // rotate conter-clock-wise (90 degree)
    for (int y = 0; y < len; y++)
    {
        for (int x = 0; x < len; x++)
        {
            if (shapes[block][y][x])
            {
                rotated_block[len - 1 - x][y] = 1;
            }
        }
    }

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            shapes[block][y][x] = rotated_block[y][x];
        }
    }
};
```
However, if rotation hits the grid(world) boundary, do not allow to rotate.
```c++
else if (e.key.code == Keyboard::Up)
{
    rotate();

    // if rotation hits boundary, do not allow to rotate
    if (check_block_boundary() == false)
    {
        rotate(), rotate(), rotate();
    }
}
```

---
## Delete filled lines
clear lines when grid(world) width is full.
```c++
// clear lines when grid width is full-filled
auto clear_lines = [&]()
{
    int deleted_line = Height - 1;

    //from bottom line to top line...
    for (int undeleted_line = Height - 1; undeleted_line >= 0; undeleted_line--)
    {
        int count_width = 0;
        for (int x = 0; x < Width; x++)
        {
            if (world[undeleted_line][x])
                count_width++;
        }

        // if current line is not full, copy lines
        // else, the line will be deleted
        if (count_width < Width)
        {
            for (int x = 0; x < Width; x++)
                world[deleted_line][x] = world[undeleted_line][x];

            deleted_line--;
        }

    }
};
```