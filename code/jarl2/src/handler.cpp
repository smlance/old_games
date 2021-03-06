#include "main.h"

Handler::Handler() { }
Handler::~Handler() { }

void Handler::handle(Event evt)
{
	Key key = evt.key.keysym.sym;

	if (evt.type == SDL_KEYDOWN)
	{
		// if playing
		if (game.getState() == STATE_PLAY)
		{
			// if we get move command
			/* TODO: should we be passing the keys in, or the direction values?
			 * if we pass direction values, we'd have to make a function to convert
			 * key values to direction/"our" key values, which may not be worth it
			 */
			if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_LEFT ||
			        key == SDLK_RIGHT)
			{
				// let game check it
				game.checkPlayerMove(key);
			}
		}
	}
}
