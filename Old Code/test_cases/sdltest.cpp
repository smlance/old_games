


//-------------------------includes and constant stuff-------------------------//


#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <string>
#include <sstream>
#include <fstream>

const int win_width = 320;
const int win_height = 240;
SDL_Surface *screen;
SDL_Surface *loadImage(std::string);
void applySurface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect * = NULL);


//-------------------------SDL stuff-------------------------//


void cleanUp()
{
	//TTF_Quit();
	SDL_Quit();
}

SDL_Surface *loadImage(std::string filename)
{
	SDL_Surface *loaded_image = NULL;
	SDL_Surface *optimized_image = NULL;
	loaded_image = IMG_Load(filename.c_str());
	
	if (loaded_image)
	{
		optimized_image = SDL_DisplayFormat(loaded_image);
		SDL_FreeSurface(loaded_image);
		
		if (optimized_image)
		{
			SDL_SetColorKey(optimized_image, SDL_SRCCOLORKEY, SDL_MapRGB
				(optimized_image->format, 0, 0xFF, 0xFF)); //replace
		}
	}
	
	return optimized_image;
}

void applySurface(int x, int y, SDL_Surface *source, SDL_Surface *dest,
	SDL_Rect *clp)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clp, dest, &offset);
}


//-------------------------class stuff-------------------------//


class Player
{
private:
	int pos_x, pos_y;
	SDL_Surface *sprite; //not going to use SDL right now

public:
	Player();
	//~Player();
	void handle_input();
	void display_sprite();
	
};

Player::Player()
{
	sprite = loadImage("./what.bmp");
	
	display_sprite();
}

void Player::display_sprite()
{
	applySurface((320/2), (240/2), sprite, screen);
}

//-------------------------game, main, and loop stuff-------------------------//

void loop()
{
	bool running = true;
	
	SDL_Event event;
	
	Player test;
	
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			//test.handleInput(event);
			
			if (event.type == SDL_QUIT)
			{
				running = false;
			};
		}
		
		SDL_Flip(screen);
	}
	
}

void initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(win_width, win_height, 32,
		SDL_SWSURFACE);
	SDL_WM_SetCaption("not an inside joke", NULL);
	
	SDL_Surface *bg;
	bg = loadImage("./bgtest.bmp");
	applySurface(0, 0, bg, screen);
}

/*
void game()
{
	
}
*/

int main()
{
	initialize();
	loop();
	
	return 0;
}
