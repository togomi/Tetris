// Simple and Fast Multimedia Library
#include <SFML/Graphics.hpp>
#include "shape.cpp"

using namespace std;
using namespace sf;

extern const int Width;
extern const int Height;
extern const int CellSize;

extern int shapes[7][4][4];
extern const Color colors[];

int main()
{
    // a window that can render 2D drawings
    RenderWindow window(VideoMode(Width*CellSize, Height*CellSize), "Tetris");

    // draw a cell in the grid
    RectangleShape cell(Vector2f(CellSize, CellSize));

    // populate a block
    int block;
    int b_x;
    int b_y;

    block = rand()%7;
    b_x = Width / 2;
    b_y = 0;

    while (window.isOpen())
    {
        // Define system event
        Event e;

        while (window.pollEvent(e))
        {
            // close window
            if (e.type == Event::Closed)
                window.close();
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