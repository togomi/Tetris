// Simple and Fast Multimedia Library
#include <SFML/Graphics.hpp>
#include "shape.cpp"

using namespace std;
using namespace sf;

// Define world parameters
const int CellSize = 25;
const int Width = 10;
const int Height = 20;

// Define world
int world[Height][Width] = { 0 };

extern int shapes[7][4][4];
extern const Color colors[];

int main()
{
    // a window that can render 2D drawings
    RenderWindow window(VideoMode(Width * CellSize, Height * CellSize), "Tetris");

    // draw a cell in the world
    RectangleShape cell(Vector2f(CellSize, CellSize));

    // populate a block
    int block;
    int b_x;
    int b_y;

    auto new_block = [&]()
    {
        block = rand() % 7;
        b_x = Width / 2;
        b_y = 0;
    };

    new_block();

    // boundary check for a block
    auto check_block_boundary = [&]()
    {
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                if (shapes[block][y][x] == 0)
                    continue;

                // hit world boundary
                if (x + b_x < 0 || x + b_x >= Width || y + b_y >= Height)
                    return false;

                // collsion with world blocks
                if (world[y + b_y][x + b_x] )
                    return false;
            }

        }
        return true;
    };

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
                        // +1 for avoiding 0
                        world[b_y + y][b_x + x] = block + 1;
                    }

                }
            }
            // delete lines
            clear_lines();

            // start next block
            new_block();

            return false;
        }
        return true;
    };

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

    Clock clock;

    while (window.isOpen())
    {
        // start clock
        static float prev = clock.getElapsedTime().asSeconds();
        if (clock.getElapsedTime().asSeconds() - prev >= 0.5)
        {
            prev = clock.getElapsedTime().asSeconds();
            fall_down();
        }

        // Define system event
        Event e;

        // polling event (eg. key pressed)
        while (window.pollEvent(e))
        {
            // close window
            if (e.type == Event::Closed)
                window.close();

            // keyboard interrupt
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Left) {
                    b_x--;
                    if (check_block_boundary() == false) b_x++;
                }
                else if (e.key.code == Keyboard::Right)
                {
                    b_x++;
                    if (check_block_boundary() == false) b_x--;
                }
                else if (e.key.code == Keyboard::Down)
                {
                    fall_down();
                }
                else if (e.key.code == Keyboard::Space)
                {
                    // fall down until reaches the bottom
                    while (fall_down() == true);
                }
                else if (e.key.code == Keyboard::Up)
                {
                    rotate();

                    // if rotation hits boundary, do not allow to rotate
                    if (check_block_boundary() == false)
                    {
                        rotate(), rotate(), rotate();
                    }
                }
            }
        }

        // clear window every frame
        window.clear();

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

        // define C++11 lambda function
        // this function can use all the outside variables, such as block
        auto draw_block = [&]()
        {
            cell.setFillColor(colors[block]);
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    if (shapes[block][y][x])
                    {
                        cell.setPosition(Vector2f((b_x + x) * CellSize, (b_y + y) * CellSize));
                        window.draw(cell);
                    }
                }
            }
        };

        // call the above lambda function
        draw_block();

        // display rendered object on screen
        window.display();
    }

    return 0;
}