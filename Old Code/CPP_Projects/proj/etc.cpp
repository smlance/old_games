#include "main.h"
#include "etc.h"
#include "Map.h"
#include "Tile.h"
#include "GenMap.h"
#include "Player.h"
#include "Object.h"

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	srand((unsigned)time(0));
	
	int screen_size_x = SCREEN_WIDTH + 64;
	int screen_size_y = SCREEN_HEIGHT + 64;
	
	SDL_WM_SetIcon(SDL_LoadBMP("./resources/icon.bmp"), NULL);
	screen = SDL_SetVideoMode(screen_size_x, screen_size_y, SCREEN_BPP,
		SDL_SWSURFACE); //XXX this for map?//
	//TTF_Init();
	SDL_WM_SetCaption("C++/SDL PCG Renderer", NULL);
}

void loop()
{
	bool running = true;
	SDL_Event event;
	
	Player test;
	
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			test.handleInput(event);
			
			if (event.type == SDL_QUIT)
			{
				running = false;
			};
		}
		SDL_Flip(screen);
	}
	
}

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

SDL_Surface *loadTransparentImage(std::string filename)
{
	SDL_Surface *loaded_image = NULL;
	SDL_Surface *optimized_image = NULL;
	loaded_image = IMG_Load(filename.c_str());
	
	if (loaded_image)
	{
		optimized_image = SDL_DisplayFormatAlpha(loaded_image);
		SDL_FreeSurface(loaded_image);
		
		/*if (optimized_image)
		{
			SDL_SetColorKey(optimized_image, SDL_SRCCOLORKEY, SDL_MapRGB
				(optimized_image->format, 0, 0xFF, 0xFF)); //replace
		}*/
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
