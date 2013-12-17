#include "main.h"
#include "Timer.h"

Timer::Timer()
{
	start_ticks = 0;
	paused_ticks = 0;
	paused = false;
	started = false;
	
	start_stop = TTF_RenderText_Solid(font, "Press S to start or stop the timer", text_color);
	pause_message = TTF_RenderText_Solid(font, "Press P to pause or unpause the timer", text_color);
	
	start();
}

void Timer::start()
{
	started = true;
	paused = false;
	start_ticks = SDL_GetTicks();
	std::cout << "Started";
}

void Timer::stop()
{
	started = false;
	paused = false;
	std::cout << "Stopped";
}

int Timer::getTicks()
{
	if (started == true)
	{
		if (paused == true)
		{
			return paused_ticks;
		}
		else
		{
			return SDL_GetTicks() - start_ticks;
		}
	}
	else
	{
		return 0;
	}
}

void Timer::pause()
{
	if ((started == true) && (paused == false))
	{
		paused = true;
		paused_ticks = SDL_GetTicks() - start_ticks;
	}
}

void Timer::unpause()
{
	if (paused == true)
	{
		paused = false;
		start_ticks = SDL_GetTicks() - paused_ticks;
		paused_ticks = 0;
	}
}

bool Timer::isStarted()
{
	return started;
}

bool Timer::isPaused()
{
	return paused;
}

SDL_Surface *Timer::getSS()
{
	return start_stop;
}

SDL_Surface *Timer::getPM()
{
	return pause_message;
}

Timer::~Timer()
{
	SDL_FreeSurface(start_stop);
	SDL_FreeSurface(pause_message);
}
