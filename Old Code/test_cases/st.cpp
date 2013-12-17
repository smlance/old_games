#include "SDL/SDL.h"

SDL_Surface *screen = NULL;

void initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(320, 240, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("bstc", NULL);
}

void prog_loop()
{
	bool running = true;
	
	SDL_Event event;
	
	//Player test;
	
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

int main(int argc, char* argv[])
{
	initialize();
	prog_loop();
	SDL_Quit();
	return 0;
}
