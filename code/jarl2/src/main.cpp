/*
 *	jarl
 *
 *	copyright (c) stef1a
 *	some code adapted from LazyFoo's C++ & SDL tutorials
 *
 */

#include "main.h"

Display display;
Camera	camera;
Game 	game;
Handler handler;
Event 	event;
Clock	fps;
Clock	update;

void init()
{
	// initialize randomizer seed
	srand((unsigned)time(0));
	game.init();
	display.init();
	camera.init();
}

void loop()
{
	bool running = true;
	update.start();

	while (running)
	{
		fps.start();

		// detect and handle events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) running = false;
			else 						handler.handle(event);
		}
		game.update(update.getTimeElapsed());
		display.render();

		// reset update timer
		update.start();
		display.refresh();

		// delay to keep constant time/fps
		if (fps.getTimeElapsed() < (1000/FPS))
		{
			SDL_Delay((1000/FPS) - fps.getTimeElapsed());
		}
	}
}

void quit()
{

}

int main(int argc, char *argv[])
{
	init();
	loop();
	quit();

	return 0;
}
