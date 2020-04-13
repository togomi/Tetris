## Environment Setup
1. Download SFML library from https://www.sfml-dev.org/download/sfml/2.5.1/
- Visual C++ 15 (2017) - 32-bit
- Unzip and save it to desired directory (eg. C:\SFML-2.5.1.\)

2. Create an empty Visual Studio Project

3. Goto Project Property Page and Select All Configurations
	a. C/C++ > Additional Include Directories
	- Additional Include Directories: C:\SFML-2.5.1.\include
	- Tell Compiler where to find .hpp header files

	b. Linker > General
	- Additional Library Directories: C:\SFML-2.5.1.\lib
	- Tell Linker how to find SFML library files

	c. Linkder > Input
	- Add 5 modules(sfml-graphics.lib; sfml-window.lib; sfml-audio.lib; sfml-network-s.lib; sfml-system-s.lib) in Additional Dependencies
	- Can be found in https://www.sfml-dev.org/tutorials/2.5/start-vc.php
	- For Debug Configuration, add debug libraries by adding "-d" to library names
	- This is [Dynamic Linking], which means we have to copy .dll from /bin to project folder
	
	- For [Static Linking], integrate SFML libaries to executables
	- Change module name to static as well as dependencies listed in above link
	- Ex. sfml-graphics.lib -> sfml-graphics-s.lib, and winmm.lib; opengl32.lib; freetype.lib
	- Define SFML_STATIC in C/C++ > Preprocessor > Preprocessor Definitions

4. Check if following code can be compiled&executed.
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Title");

    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
    return 0;
}