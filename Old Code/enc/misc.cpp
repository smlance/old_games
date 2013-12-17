#include "misc.h"

void init(){
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	cbreak();
}

void loop(){
	Player player; //create ptr instead? adv/disadv to doing so?
	//also, put in init?.. how to reference w/ diff scope?
	
	bool game_over = FALSE;
	while (game_over == FALSE)
	{
		if (player.processInput() == 0)
		{
			game_over = TRUE;
		}
	}
}
