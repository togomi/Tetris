// Simple and Fast Multimedia Library
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Define grid
const int CellSize = 25;
const int Width = 10;
const int Height = 20;

int main()
{
    // a window that can render 2D drawings
    RenderWindow window(VideoMode(Width*CellSize, Height*CellSize), "Tetris");

    // draw a cell in the grid
    RectangleShape cell(Vector2f(CellSize, CellSize));

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

        // draw a cell for test
        cell.setFillColor(Color::Red);
        window.draw(cell);

        // display rendered object on screen
        window.display();
    }

    return 0;
}