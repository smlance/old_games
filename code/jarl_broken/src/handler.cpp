#include "main.h"

// handle: For non-specific events
bool Handler::handle(Event event)
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) return false;
		else 						handlePlaying(event);
	}
	
	return true;
}

// handlePlaying: for non-quit events
void Handler::handlePlaying(Event event)
{
	Key key = event.key.keysym.sym;

	if (event.type == SDL_KEYDOWN)
	{
		// if playing
		if (game.get_state() == STATE_PLAY)
		{
			// if we get move command
			if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_LEFT ||
			        key == SDLK_RIGHT)
			{
				// let game check it
				//game.check_player_move(key);
			}
		}
	}
}
