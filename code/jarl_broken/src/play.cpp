#include "main.h"

Player::Player(int x_, int y_, int id_) : Entity(x_, y_, id_)
{
	assert(1);
}
Player::~Player() { }

void Player::update(int time)
{
	check_hit();
	time_a += time;
	if (time_a >= time_m)
	{
		time_a = 0;
		//make_changes();
	}
}

void Player::move(int dir)
{
	switch (dir)
	{
	case MOVE_UP:
		y--;
		break;
	case MOVE_DOWN:
		y++;
		break;
	case MOVE_LEFT:
		x--;
		break;
	case MOVE_RIGHT:
		x++;
		break;
	default:
		break;
	}
}

void Player::rand_spawn()
{
	// TODO: attribute "solidness" to each ID
	Map *area = game.get_area();
	int x_ = (rand() % (area->get_width() - 2)) + 1;
	int y_ = (rand() % (area->get_height() - 2)) + 1;
	// while we are still spawning in a wall
	while (area->get_tile(x_, y_)->get_solid() ||
	        !(game.num_walls_udlr(x_, y_) == 2))
	{
		// generate new random coordinates
		x_ = (rand() % (area->get_width() - 2)) + 1;
		y_ = (rand() % (area->get_height() - 2)) + 1;
	}
	// found right coordinates; assign them to x and y
	x = x_;
	y = y_;
	area = NULL;
}

void Player::check_hit()
{
	Map *area = game.get_area();
	//if area[x][y]->get_tile
}
