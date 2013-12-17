#include "SDL/SDL.h"

int main(int argc, char* argv[])
{
	SDL_Surface* hello = NULL;
	SDL_Surface* screen = NULL;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	hello = SDL_LoadBMP("hello.bmp");
	if (hello == NULL)
	{
		ReportError(SDL_GetError());
	}
	SDL_Rect position;
position.x = 0; //were just putting the picture in the top left corner
position.y = 0;// at position 0,0
	SDL_BlitSurface(hello, NULL, screen, &position);
	SDL_Flip(screen);
	SDL_Delay(2000);
	SDL_FreeSurface(hello);
	SDL_Quit();
	return 0;
}
