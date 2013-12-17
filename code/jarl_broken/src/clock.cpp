#include "main.h"

Clock::Clock()
{
	time_init = 0;
}

void Clock::start()
{
	time_init = SDL_GetTicks();
}

int Clock::timeElapsed()
{
	return SDL_GetTicks() - time_init;
}
