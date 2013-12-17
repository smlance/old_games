/*
Roguelike programmed entirely by Stefan Lance in January-February 2011
(Thanks to Bryce for the graphics!)
*/

#include "main.h"
#include "etc.h"

SDL_Surface *screen = NULL;

int main()
{
	init();
	loop();
	cleanUp();
	return 0;
}
