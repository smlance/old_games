#include "Player.h"

Player::Player()
{
	pos_x = 2;
	pos_y = 2;
	key = 64;
	map_x = 0;
	map_y = 0;
	health = 20;
	max_health = 20;
	lvl = 1;
	str = 5;
	dir = 0;
}
/*
Map& Player::getMap(){
	return *world_map[map_y][map_x];
}*/

int Player::returnxMap()
{
	return map_x;
}

int Player::returnyMap()
{
	return map_y;
}

void Player::updatePlayerAndWorld(/*params?*/)
{
	mvaddch(pos_y, pos_x, key);
	/*stuff to add: update previous cell (based on dir),
	i.e. with tile or item*/
}

/*bool Player::isSpotTaken(){
	uses map data and dir to see if move is possible
	(returns TRUE if spot is taken, false if not)
}*/

void Player::move(int d)
{
	dir = d;
	
	switch(d)
	{
	case 90:
		if (pos_y == 0)
		{
			map_y--;
			pos_y = (MAP_SIZE_Y-1);
			//print map
			updatePlayerAndWorld();
		}
		/*else if (isSpotTaken*/
		else
		{
			pos_y--;
			updatePlayerAndWorld(); /*any way
			to do this at the END (after all
			cases), but skip it if an isSpotTaken
			is set to TRUE?*/
		};
		break;
	case 270:
		if (pos_y == (MAP_SIZE_Y-1))
		{
			map_y++;
			pos_y = 0;
			//print map
			updatePlayerAndWorld();
		}
		/*else if (isSpotTaken*/
		else
		{
			pos_y++;
			updatePlayerAndWorld(); /*any way
			to do this at the END (after all
			cases), but skip it if an isSpotTaken
			is set to TRUE?*/
		};
		break;
	case 180:
		if (pos_x == 0)
		{
			map_x--;
			pos_x = (MAP_SIZE_X-1);
			//print map
			updatePlayerAndWorld();
		}
		/*else if (isSpotTaken*/
		else
		{
			pos_x--;
			updatePlayerAndWorld(); /*any way
			to do this at the END (after all
			cases), but skip it if an isSpotTaken
			is set to TRUE?*/
		};
		break;
	case 360:
		if (pos_x == (MAP_SIZE_X-1))
		{
			map_x++;
			pos_x = 0;
			//print map
			updatePlayerAndWorld();
		}
		/*else if (isSpotTaken*/
		else
		{
			pos_x++;
			updatePlayerAndWorld(); /*any way
			to do this at the END (after all
			cases), but skip it if an isSpotTaken
			is set to TRUE?*/
		};
		break;
	}
}

int Player::processInput(){
	/*This has to be optimized; how can I make functions that
	act similarly (as if made by enum) in regards to movement? 
	How to handle events here? ex. make bool check_for_item
	or check_for_possible_move funcs?
	*/
	int input = getch();
	switch(input)
	{
		case KEY_UP:
			move(90);
			return 1;
			break;
		case KEY_DOWN:
			move(270);
			return 1;
			break;
		case KEY_LEFT:
			move(180);
			return 1;
			break;
		case KEY_RIGHT:
			move(360);
			return 1;
			break;
		case 27:
			return 0;
			break;
			/*TODO: fix return/escape thingy: work
			in just one esc keystroke and display 
			quit-confirmation msg*/
	}
}

Player::~Player(){
	delete &pos_x, &pos_y, &key, &map_x, &map_y, &health, &max_health, &lvl, &str, &dir /*stat_bar*/;
}
