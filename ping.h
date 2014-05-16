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
char SCP='0'; //Player Score
char SCA='0'; //AI Score
int ballYvel = 0;
int ballXvel = 0;

//Rectangle Shape for Player Slider, AI Slider and Ball respectively
//RectangleShape R1(Vector2f(20,200));
//RectangleShape R2(Vector2f(20,200));
RectangleShape R3(Vector2f(20,20));
RectangleShape UpB(Vector2f(20,20));
RectangleShape DnB(Vector2f(20,20));


//Initialise scores
int SCORE_PLAYER = 0,SCORE_AI = 0;

//Image for AI slider
Sprite *slider;
Texture slider_img;

//Image for Player slider
Sprite *sliderp;
Texture slider_img_p;

void init_game()
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

	Up.left = 690;
	Up.top = 190;
	Up.width = 20;
	Up.height = 20;

	Down.left = 730;
	Down.top = 190;
	Down.width = 20;
	Down.width = 20;

    //Fill Colour to the Rectangle Shapes for Player Slider, AI Slider and Ball respectively
    //R1.setFillColor(Color::Red);
    //R2.setFillColor(Color::Blue);
    R3.setFillColor(Color::Magenta);

	UpB.setFillColor(Color::Cyan);
	DnB.setFillColor(Color::Green);

    //Apply velocity to the Ball
    ballXvel = BALL_VEL;
    ballYvel = BALL_VEL;

	if(!slider_img.loadFromFile("C:/Users/intel/Documents/Visual Studio 2010/Projects/pingpong/Debug/Asset/ai_slider.png")) // loads image as texture into bgtex
	{
		std::cout<<"\nError loading image";
	}
	slider=new Sprite();  // creating sprite object
	slider->setTexture(slider_img);   // you set the texture to the sprite

	if(!slider_img_p.loadFromFile("C:/Users/intel/Documents/Visual Studio 2010/Projects/pingpong/Debug/Asset/player_slider.png")) // loads image as texture into bgtex
	{
		std::cout<<"\nError loading image";
	}
	sliderp=new Sprite();  // creating sprite object
	sliderp->setTexture(slider_img_p);   // you set the texture to the sprite


}

void handle_input(RenderWindow *window)
{
    //If Up arrow is pressed
    //if(Keyboard::isKeyPressed(Keyboard::W))
     // playerYvel = -(SLIDER_VEL);

    //If Down arrow is pressed
   // else if(Keyboard::isKeyPressed(Keyboard::A))
    //  playerYvel = SLIDER_VEL;

    //If no key is pressed
  //  else
     // playerYvel = 0;

	if(Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2i downco;
		downco.x=Down.left;
		downco.y=Down.top;
		Vector2i  position =sf::Mouse::getPosition(*window);
		
		Up.contains(position)?playerYvel = -(SLIDER_VEL) :(Down.contains(position)? playerYvel= SLIDER_VEL : playerYvel = 0) ;

		//if(Down.contains(position))
		//	playerYvel = (SLIDER_VEL);			
		//else if(Up.contains(position))
		//	playerYvel = -(SLIDER_VEL);
		//else 
		//	playerYvel=0;	
		
		 
	}		
	else
		playerYvel = 0;
	


}

void update()
{
    //If ball collides with any of the two sliders
    if(ball.intersects(slider_right) || ball.intersects(slider_left) )
      ballXvel = -(ballXvel);

    //If ball collides with the top and bottom walls
    if(ball.top < 0 || (ball.top+ball.height) > 600)
      ballYvel = -(ballYvel);

    //If ball collides with the left side wall
    if(ball.left < 0)
    {
      SCORE_PLAYER +=1;
      ballXvel      = -(ballXvel);
    }

    //If ball collides with the right side wall
    else if((ball.left+ball.width) > 610)
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

void perform_ai()
{
    //If Ball is above the AI Slider 
    if(ball.top < slider_left.top)
      slider_left.top -= SLIDER_VEL;
  
    //If Ball is below the AI Slider
    else if(ball.top > (slider_left.top + slider_left.height))
      slider_left.top += SLIDER_VEL;
}

void display(RenderWindow *window)
{
    //Displace the Player Slider and draw it on screen
   sliderp->setPosition(slider_right.left,slider_right.top);
    window->draw(*sliderp);

    //Displace the AI Slider and draw it on screen
	slider->setPosition(slider_left.left,slider_left.top);
	window->draw(*slider); //drawing slider on window
 
    //Displace the Ball and draw it on screen
    R3.setPosition(ball.left,ball.top);
    window->draw(R3);
		
	UpB.setPosition(Up.left,Up.top);
	window->draw(UpB);

	DnB.setPosition(Down.left,Down.top);
	window->draw(DnB);
}

void manage_score(RenderWindow *window)
{
	//Updating score

	if(SCP<SCORE_PLAYER+48)
		SCP += 1;
	else if(SCA<SCORE_AI+48)
		SCA +=1;
	else
		{
			SCP+=0;
			SCA+=0;
		}

	//Loading font
	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	 // Initialising Player score
	Text text(SCP, font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	text.setPosition(Vector2f(750,30));

	// Initialising AI score
	Text text1(SCA,font);
	text1.setCharacterSize(30);
	text1.setStyle(sf::Text::Bold);
	text1.setColor(sf::Color::Blue);
	text1.setPosition(Vector2f(700,30));

	
	// Display 
	window->draw(text);

	
	//Display score
	window->draw(text1);
}

bool result(RenderWindow *window)
{
	Font font;
	font.loadFromFile("C:/Windows/Fonts/Verdana.ttf");

	
		if(SCORE_PLAYER==10)
	{
		
		Text text("You WON", font);
		text.setCharacterSize(100);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::White);
		text.setPosition(Vector2f(100,250));
		window->draw(text);
		return true;

	}
		 else if(SCORE_AI==10)
		{
			Text text1("You LOSE", font);
		text1.setCharacterSize(100);
		text1.setStyle(sf::Text::Bold);
		text1.setColor(sf::Color::White);
		text1.setPosition(Vector2f(90,250));
		window->draw(text1);
		return true;
		}
		 else 
			 return false;
}

void endgame()
{
	
	ballXvel=0;
	ballYvel=0;
	BALL_VEL=0;
	SLIDER_VEL=0;

}

