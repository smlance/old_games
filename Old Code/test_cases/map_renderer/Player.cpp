#include "main.h"
#include "Player.h"

Player::Player()
{
	x = 0;
	y = 0;
	xVel = 0;
	yVel = 0;
	
	sprite = loadImage("./resources/guy.bmp");
}

SDL_Surface* Player::getSprite()
{
	return sprite;
}

/*void Player::handleInput()
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			
		}
	}
}*/

Player::~Player()
{
	SDL_FreeSurface(sprite);
}
