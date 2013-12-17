#include "main.h"

Timer::Timer() {
	time_i = 0;
}

void Timer::start() {
	time_i = SDL_GetTicks();
}

int Timer::get_time_elapsed() {
	return SDL_GetTicks() - time_i;
}

Timer::~Timer() {

}
