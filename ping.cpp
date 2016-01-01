#include <iostream>
#include "ping.h"

using namespace sf;

int main()
{
    // Creates the window to show your game
    RenderWindow *window;
    window = new RenderWindow(VideoMode(800, 600),"Ping Pong");
    window->setFramerateLimit (25);

    Sprite *background = new Sprite(); // a pointer for sprite
    Texture bg; // bgtex to store the texture

	if(!bg.loadFromFile("assets/background.png")) // Loads image as texture. Image must at least be 610 x 600
		std::cout<<"\nError loading image";
	else
		background->setTexture (bg);   // you set the texture to the sprite

	// Use setTextureRect() function to set the texture to some of the window
	background->setTextureRect (IntRect (0, 0, 610, 600));

    //Initialize the game objects
    onCreate ();

    // The Game Loop

    while (window->isOpen ())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window->pollEvent (event))
        {
            //Window is closed or 'Esc' key is pressed
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
                window->close ();
        }

		//checks User input
        InputHandler (window);

		//update positions,scores etc.
        GameUpdate ();

		//perform AI operations
       	AIOperation ();

        //Clears the window every frame to render updated positions. MUST DO
        window->clear (sf::Color::White);

	    //Draw the background image
		window->draw (*background);

        //Draw everything else here
        Display (window);

		//Check score
		ScoreManager (window);

		if (ResultManager (window) ) onEnd ();

		//Display everything on the Window
        window->display();
    }

	//free memory
	delete background;
	delete window;

    return 0;
}
