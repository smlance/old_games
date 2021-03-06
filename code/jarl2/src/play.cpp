#include "main.h"

Player::Player(int x_, int y_, int id_) : Entity(x_, y_, id_)
{
	assert(1);
}

Player::~Player()
{

}

void Player::update(int time)
{
	//int old_x = x;
	//int old_y = y;
	checkHit();
	time_a += time;
	if (time_a >= time_m)
	{
		time_a = 0;
		//make_changes();
	}
	//if (old_x != x || old_y != y)
	//{
		//game.getArea()->getTile(old_x, old_y)->freeEnt();
		// XXX have a log file -- see what happens if we don't do this
		// XXX DO NOT FREE THE ENT HERE, BECAUSE MOVE HAPPENS REGARDLESS OF TIME UPDATES?
	//}
}

void Player::move(int direction)
{
  /* This method assumes no tile is hindering our movement. */
	int old_x = x;
	int old_y = y;
	/* put these move function checks into a single function for all entities */
	if (direction == MOVE_RIGHT)
		game.getArea()->getTile(x + 1, y)->incrementPEO();
	else if (direction == MOVE_LEFT)
		game.getArea()->getTile(x - 1, y)->incrementPEO();
		/* REMEMBER XXX: y UP is -; y DOWN is + XXX */
	else if (direction == MOVE_UP)
		game.getArea()->getTile(x, y - 1)->incrementPEO();
	else if (direction == MOVE_DOWN)
		game.getArea()->getTile(x, y + 1)->incrementPEO();
		
	switch (direction)
	{
	case MOVE_UP:
		if ( !(game.getArea()->getTile(x, y - 1)->hasEnt())
		&& (game.getArea()->getTile(x, y - 1)->getPEO() < 2) )
			y--;
		break;
	case MOVE_DOWN:
		if ( !(game.getArea()->getTile(x, y + 1)->hasEnt())
		&& (game.getArea()->getTile(x, y + 1)->getPEO() < 2) )
			y++;
		break;
	case MOVE_LEFT:
		if ( !(game.getArea()->getTile(x - 1, y)->hasEnt())
		&& (game.getArea()->getTile(x - 1, y)->getPEO() < 2) )
			x--;
		break;
	case MOVE_RIGHT:
		if ( !(game.getArea()->getTile(x + 1, y)->hasEnt())
		&& (game.getArea()->getTile(x + 1, y)->getPEO() < 2) )
			x++;
		break;
	default:
		break;
	}
	
	if (old_x != x || old_y != y)
		moveEnt(x, y);
		game.getArea()->getTile(old_x, old_y)->freeEnt();
}

void Player::randSpawn()
{
	// TODO: attribute "solidness" to each ID
	Map *area = game.getArea();
	int x_ = (rand() % (area->getWidth() - 2)) + 1;
	int y_ = (rand() % (area->getHeight() - 2)) + 1;
	// while we are still spawning in a wall
	while (area->getTile(x_, y_)->getSolid() ||
	        !(game.numWallsUDLR(x_, y_) == 2))
	{
		// generate new random coordinates
		x_ = (rand() % (area->getWidth() - 2)) + 1;
		y_ = (rand() % (area->getHeight() - 2)) + 1;
	}
	// found right coordinates; assign them to x and y
	x = x_;
	y = y_;
	area = NULL;
}

void Player::checkHit()
{
	Map *area = game.getArea();
	//if area[x][y]->getTile
}
