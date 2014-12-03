#include <iostream>
#include "SFML\Graphics.hpp"
#include "ping.h"
using namespace sf;
int main()
{
    // Creates the window to show your game 
    RenderWindow *window;
    window=new RenderWindow(VideoMode(800, 600),"Ping Pong");
    window->setFramerateLimit(20);
    Sprite *background; // a pointer for sprite
    Texture bg; // bgtex to store the texture	
	if(!bg.loadFromFile("C:/Users/intel/Documents/Visual Studio 2010/Projects/pingpong/Debug/Asset/background_pong.png")) // loads image as texture into bgtex
	{
		std::cout<<"\nError loading image";
	}
	else
	{
		background=new Sprite();  // creating sprite object
		background->setTexture(bg);   // you set the texture to the sprite
	}
	// Use setTextureRect() function to set the texture to some of the window
	background->setTextureRect(IntRect(0,0,610,600));  

    //Initialise the game objects
    onCreate();

    // run the program as long as the window is open
    while (window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            //either Window is closed or 'Esc' key is pressed
            if(event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window->close();
        }
		//checks User input
        InputHandler(window);

		//update positions,scores etc.
        GameUpdate();

		//perform ai operations
       	AIOperation();

        //Clears the window every frame to render updated positions
        //Very important step.
		window->clear(sf::Color::White);

	    // draw the background image
		window->draw(*background);

        // draw everything else here...
        Display(window);

		//checks score
		ScoreManager(window);
		
		if(result(window))
		{
			onEnd();
		}
        // end the current frame
        //Display everything on the Window
        window->display();
    }
	
	//free memory
	delete background;
	delete window;
    
    return 0;
}
