/*
 *	jarl
 *
 *	by stefan lance, 2012
 */

#include "main.h"

struct AppData
{
	Game 	*g;
	Display *d;
};

void init(AppData *ad)
{
	// Enable random number generation
	srand( (unsigned)time(0) );
	
	// Create instances
	Game 	*game = new Game;
	Display *display = new Display;
	
	// Set app data
	ad->g = game;
	ad->d = display;
}

void loop(AppData *ad)
{
	Game 	*game = ad->g;
	Display *display = ad->d;
	
	Clock 	update;
	Clock 	fps;
	Event 	event;
	Handler handler;
	
	bool 	running = true;
	
	update.start();

	while (running)
	{
		fps.start();

		running = handler.handle(event);

		game->update( update.timeElapsed() );
		display->render();
		display->refresh();
		
		// Reset update timer
		update.start();

		// Delay to keep constant time/fps
		/* XXX Should this be put in its own function, i.e., in Clock::? XXX */
		if ( fps.timeElapsed() < (1000/FPS) )
		{
			SDL_Delay( (1000/FPS) - fps.timeElapsed() );
		}
	}
}

void quit(AppData *ad)
{
	// Delete data and then nullify pointers to data
	delete ad->g;
	ad->g = NULL;
	
	delete ad->d;
	ad->d = NULL;
	
	delete ad;
	ad = NULL;
}

int main(int argc, char **argv)
{
	/* This can also be made non-static and just passed by reference to
	 * init, loop, and quit. Is there any advantage?
	 */
	static AppData *app = new AppData;
	
	init(app);
	loop(app);
	quit(app);

	return 0;
}
