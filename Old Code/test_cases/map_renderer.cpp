#include "main.h"
#include "Tile.h"
#include "Player.h"

SDL_Surface *loadImage(std::string filename)
{
	SDL_Surface* loaded_image = NULL;
	SDL_Surface* optimized_image = NULL;
	loaded_image = SDL_LoadBMP(filename.c_str());
	
	if (loaded_image != NULL)
	{
		optimized_image = SDL_DisplayFormat(loaded_image);
		
		SDL_FreeSurface(loaded_image);
	}
	
	return optimized_image;
}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void handleEvents()
{
	bool quit = false;
	
	while (quit == false)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}

bool loadFiles()
{
	font = TTF_OpenFont("/resources/Ubuntu-B.ttf", 28);
	
	if (font == NULL)
	{
		return false;
	}
	
	return true;
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	if (screen == NULL)
	{
		return false;
	}
	
	if (TTF_Init() == -1)
	{
		return false;
	}
	
	SDL_WM_SetCaption("Brycicles, everywhere", NULL);
	
	return true;
}

void cleanUp()
{
	SDL_FreeSurface(message);
	TTF_CloseFont(font);
	TTF_Quit();
	/*free surfaces*/
	SDL_Quit();
}

void displayText()
{	
	message = TTF_RenderText_Solid(font, "Brycicles. Seriously.",
		text_color);
	if (message == NULL)
	{
		return 1;
	}
	
	applySurface(0, 10, message, screen);
}

int main()
{
	if (init() == false)
	{
		return 1;
	}
	
	if (loadFiles() == false)
	{
		return 1;
	}
	
	displayText();
	
	if (SDL_Flip(screen) == -1)
	{
		return 1;
	}
	
	handleEvents();
	
	cleanUp();
	
	return 0;
}
