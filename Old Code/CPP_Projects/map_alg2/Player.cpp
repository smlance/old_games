#include "main.h"

Player::Player()
{
	this_map = new Map;
	/*pos_x = rand() % sx;
	pos_y = rand() % sy;
	key = 64;
	
	while ((this_map->map[pos_y][pos_x]).type != ground)
	{
		pos_x = rand() % sx;
		pos_y = rand() % sy;
	}
	
	mvaddch(pos_y, pos_x, key);
	
	bool run = true;
	while (run)
	{
		getAndHandleEvent();
	}*/
}

void Player::getAndHandleEvent()
{
	int in = getch();
	
	if (in == KEY_UP)
	{
		if ((this_map->map[pos_y-1][pos_x]).type != wall)
		{
			mvaddch(pos_y, pos_x, (this_map->map[pos_y][pos_x]).type);
			pos_y--;
			mvaddch(pos_y, pos_x, key);
		};
	}
	else if (in == KEY_DOWN)
	{
		if ((this_map->map[pos_y+1][pos_x]).type != wall)
		{
			mvaddch(pos_y, pos_x, (this_map->map[pos_y][pos_x]).type);
			pos_y++;
			mvaddch(pos_y, pos_x, key);
		};
	}
	else if (in == KEY_LEFT)
	{
		if ((this_map->map[pos_y][pos_x-1]).type != wall)
		{
			mvaddch(pos_y, pos_x, (this_map->map[pos_y][pos_x]).type);
			pos_x--;
			mvaddch(pos_y, pos_x, key);
		};
	}
	else if (in == KEY_RIGHT)
	{
		if ((this_map->map[pos_y][pos_x+1]).type != wall)
		{
			mvaddch(pos_y, pos_x, (this_map->map[pos_y][pos_x]).type);
			pos_x++;
			mvaddch(pos_y, pos_x, key);
		};
	};
}

Player::~Player()
{
	delete this_map;
}
