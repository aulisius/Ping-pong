#include "SFML\Graphics.hpp"
#include <iostream>
using namespace sf;

//Rectangle for Player Slider
Rect<int> slider_right;

//Rectangle for AI Slider
Rect<int> slider_left;

//Rectangle for Ball
Rect<int> ball;

//Rectangle for buttons
Rect<int> Up;
Rect<int> Down;

//Velocity Values for Ball and Slider
int BALL_VEL   = 10;
int SLIDER_VEL = 10;

//Velocity variables for Player and Ball
int playerYvel = 0;
int ballYvel = 0;
int ballXvel = 0;

char SCP = '0'; //Player Score
char SCA = '0'; //AI Score

//Rectangle Shape for Ball and the Buttons respectively
RectangleShape R3 (Vector2f (20, 20));
RectangleShape UpB (Vector2f (20, 20));
RectangleShape DnB (Vector2f (20, 20));

//Initialize scores
int SCORE_PLAYER = 0;
int SCORE_AI = 0;

//Image for AI slider
Sprite *slider;
Texture slider_img;

//Image for Player slider
Sprite *sliderp;
Texture slider_img_p;

void onCreate()
{
    //Assign values to Ball Rectangle
    ball.left   = 30;
    ball.top    = 30;
    ball.width  = 20;
    ball.height = 20;

    //Assign values to Player Slider Rectangle
    slider_right.left   = 550;
    slider_right.top    = 200;
    slider_right.width  = 20;
    slider_right.height = 240;

    //Assign values to AI Slider Rectangle
    slider_left.left   = 30;
    slider_left.top    = 200;
    slider_left.width  = 20;
    slider_left.height = 250;

    //Assign values to Up button
    Up.left = 690;
    Up.top = 190;
    Up.width = 20;
    Up.height = 20;

    //Assign values to Down button
    Down.left = 730;
    Down.top = 190;
    Down.width = 20;
    Down.height = 20;

    //Fill Color to the Rectangle Shape for Ball,Up and Down respectively
    R3.setFillColor (Color::Magenta);
    UpB.setFillColor (Color::Cyan);
    DnB.setFillColor (Color::Green);

    //Apply velocity to the Ball
    ballXvel = BALL_VEL;
    ballYvel = BALL_VEL;

    //Loading and Applying Slider images
	if(!slider_img.loadFromFile("assets/pong.png")) // loads image as texture into bgtex
		std::cout<<"\nError loading image";
	else
	{
		slider = new Sprite();  // creating sprite object
		sliderp = new Sprite();  // creating sprite object

		slider->setTexture(slider_img);   // you set the texture to the sprite
		sliderp->setTexture(slider_img);   // you set the texture to the sprite
	}
}

void InputHandler (RenderWindow *window)
{
    //Handling inputs with Buttons and sf::Mouse events
	if (Mouse::isButtonPressed (Mouse::Left))
	{
		Vector2i  position = sf::Mouse::getPosition (*window);
		if (Down.contains (position))
			playerYvel = SLIDER_VEL;
		else if(Up.contains(position))
			playerYvel = -(SLIDER_VEL);
		else
			playerYvel = 0;
	}
	else
		playerYvel = 0;
}

void GameUpdate()
{
    //If ball collides with any of the two sliders
    if (ball.intersects (slider_right) || ball.intersects (slider_left) )
      ballXvel = -(ballXvel);

    //If ball collides with the top and bottom walls
    if (ball.top < 0 || (ball.top+ball.height) > 600)
      ballYvel = -(ballYvel);

    //If ball collides with the left side wall
    if (ball.left < 0)
    {
      SCORE_PLAYER +=1;
      ballXvel      = -(ballXvel);
    }

    //If ball collides with the right side wall
    else if ( (ball.left+ball.width) > 610)
    {
      SCORE_AI += 1;
      ballXvel  = -(ballXvel);
    }

    //Change ball's position with respect to velocity
    ball.left += ballXvel;
    ball.top  += ballYvel;

    //Change Player Slider's position with respect to velocity
    slider_right.top += playerYvel;

}

void AIOperation()
{
    //If Ball is above the AI Slider
    if (ball.top < slider_left.top)
      slider_left.top -= SLIDER_VEL;

    //If Ball is below the AI Slider
    else if (ball.top > (slider_left.top + slider_left.height))
      slider_left.top += SLIDER_VEL;
}

void Display (RenderWindow *window)
{
    //Displace the Player Slider and draw it on screen
    sliderp->setPosition (slider_right.left,slider_right.top);
    window->draw (*sliderp);

    //Displace the AI Slider and draw it on screen
	slider->setPosition (slider_left.left,slider_left.top);
	window->draw (*slider); //drawing slider on window

    //Displace the Ball and draw it on screen
    R3.setPosition (ball.left,ball.top);
    window->draw (R3);

    //Draw Up and Down button
    UpB.setPosition (Up.left,Up.top);
    window->draw (UpB);

    DnB.setPosition (Down.left,Down.top);
    window->draw (DnB);
}

void ScoreManager (RenderWindow *window)
{

	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	//Updating score
	if (SCP < SCORE_PLAYER + 48) SCP += 1;

	if ( SCA < SCORE_AI + 48) SCA +=1;

	Text text(SCP, font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	text.setPosition(Vector2f(750,30));

	// Initializing AI score
	Text text1(SCA,font);
	text1.setCharacterSize(30);
	text1.setStyle(sf::Text::Bold);
	text1.setColor(sf::Color::Blue);
	text1.setPosition(Vector2f(700,30));

	// Display score for player
	window->draw(text);

	//Display score for AI
	window->draw(text1);
}

bool ResultManager(RenderWindow *window)
{
    Font font1;
    font1.loadFromFile("C:/Windows/Fonts/Verdana.ttf");

    Text text ("You WON", font1);
	text.setCharacterSize (100);
	text.setStyle (sf::Text::Bold);
	text.setColor (sf::Color::White);
	text.setPosition (Vector2f(100,250));

	Text text1 ("You LOSE", font1);
	text1.setCharacterSize (100);
	text1.setStyle (sf::Text::Bold);
	text1.setColor (sf::Color::White);
	text1.setPosition (Vector2f(90,250));
	//Checks who wins the game (reaches 10 points first)

	if (SCORE_PLAYER == 10)
	{
		window->draw (text);
		return true;
	}
	else if (SCORE_AI == 10)
	{
		window->draw (text1);
		return true;
	}
	else
		 return false;
}

void onEnd()
{
  	//Ends the game by freezing all elements
	ballXvel=0;
	ballYvel=0;
	BALL_VEL=0;
	SLIDER_VEL=0;
}
