#include "main.h"

// Specific constructor
Entity::Entity(info info_)
{
	// Negative values correspond to, "set me to default value!"
	if (info_.x < 0) 	ent_info.x = 0;
	else				ent_info.x = info_.x;
	
	if (info_.y < 0)	ent_info.y = 0;
	else				ent_info.y = info_.y;
	
	if (info_.id < 0)	ent_info.id = 0;
	else				ent_info.id = info_.id;
	
	if (info_.type < 0)	ent_info.type = 0;
	else				ent_info.type = info_.type;
	
	if (info_.time_a < 0) 	ent_info.time_a = 0;
	else					ent_info.time_a = info_.time_a;
	
	/* XXX Value of 1000 for time_m is arbitrary; set as const elsewhere? XXX */
	if (info_.time_m < 0)	ent_info.time_m = 1000;
	else					ent_info.time_m = info_.time_m;
}

// Default constructor (when the creator has no idea what values to pass)
Entity::Entity()
{
	ent_info.x 		= 0;
	ent_info.y 		= 0;
	ent_info.id 	= 0;
	ent_info.type 	= 0;
	ent_info.time_a = 0;
	ent_info.time_m = 1000;
	
	// randSpawn();
}

void Entity::update(int time)
{
	ent_info.time_a += time;
	if (ent_info.time_a >= ent_info.time_m)
	{
		ent_info.time_a = 0;
		makeChanges();
	}
}

void Entity::makeChanges()
{
	// Store old values
	int old_x = ent_info.x;
	int old_y = ent_info.y;
	
	// If position has changed
	if (old_x != ent_info.x || old_y != ent_info.y)
	{
		//map.get_area()->get_tile(old_x, old_y)->free_ent
	}
}

void Entity::move(int dir) { }

void Entity::randSpawn()
{
	Map *area = game.get_area();
	int x_ = (rand() % (area->get_width() - 2)) + 1;
	int y_ = (rand() % (area->get_height() - 2)) + 1;
	// while we are still spawning in a wall
	while (area->get_tile(x_, y_)->ent_info.solid
		// and we are not in a room
		|| !area->get_tile(x_, y_)->ent_info.in_room)
	{
		// generate new random coordinates
		x_ = (rand() % (area->get_width() - 2)) + 1;
		y_ = (rand() % (area->get_height() - 2)) + 1;
	}
	// found right coordinates; assign them to x and y
	ent_info.x = x_;
	ent_info.y = y_;
	area = NULL;
}
