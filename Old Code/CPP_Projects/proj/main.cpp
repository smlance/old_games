/*
 *	jarl might be a good name
 *	(just another roguelike)
 *	but it should be secret ;}
 */

#include "main.h"
#include "etc.h"

SDL_Surface *screen = NULL;

int main(int argc, char **argv)
{
	init();
	loop();
	cleanUp();
	return 0;
}
