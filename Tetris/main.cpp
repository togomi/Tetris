// Simple and Fast Multimedia Library
#include <SFML/Graphics.hpp>
#include "shape.cpp"

using namespace std;
using namespace sf;

// Define grid parameters
const int CellSize = 25;
const int Width = 10;
const int Height = 20;

// Define Grid (World)
int GRID[Height][Width] = { 0 };

extern int shapes[7][4][4];
extern const Color colors[];

int main()
{
    // a window that can render 2D drawings
    RenderWindow window(VideoMode(Width * CellSize, Height * CellSize), "Tetris");

    // draw a cell in the grid
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

    while (window.isOpen())
    {
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
                    if (check_block_bounary() == false) b_x++;
                }
                else if (e.key.code == Keyboard::Right)
                {
                    b_x++;
                    if (check_block_bounary() == false) b_x--;
                }
                else if (e.key.code == Keyboard::Down)
                {
                    b_y++;
                    if (check_block_bounary() == false) b_y--;
                }
            }
        }

        // clear window every frame
        window.clear();

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