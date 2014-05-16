#include <iostream>
#include "SFML\Graphics.hpp"
#include "ping.h"
using namespace sf;
int main()
{
    // create the window to show your game 
    RenderWindow *window;
	bool a;
    window=new RenderWindow(VideoMode(800, 600),"Ping Pong");
    window->setFramerateLimit(20);
    Sprite *background; // a pointer for sprite
	Texture bg; // bgtex to store the texture

	if(!bg.loadFromFile("C:/Users/intel/Documents/Visual Studio 2010/Projects/pingpong/Debug/Asset/background_pong.png")) // loads image as texture into bgtex
	{
		std::cout<<"\nError loading image";
	}
	background=new Sprite();  // creating sprite object
	background->setTexture(bg);   // you set the texture to the sprite

// if you wanna clip a particular area from the texture and put into the sprite you can // use the following setTextureRect() function

	background->setTextureRect(Rect<int>(0,0,610,600));  

	 
    //Initialise the game objects
    init_game();

    // run the program as long as the window is open
    while (window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;

        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window->close();
        }

		//check user input
        handle_input(window);

		//update positions,scores etc.
        update();

		//perform ai operations
        perform_ai();

        // clear the window 
		window->clear(sf::Color::White);

	    // draw the background image

		window->draw(*background);

        // draw everything else here...

        display(window);

		//check score

		manage_score(window);

		//check result

		a=result(window);
		
		if(a)
		{
			endgame();
		}
        // end the current frame
        window->display();
    }

    return 0;
}
