#include "main.h"

Entity::Entity(int x_, int y_, int id_)
{
	x 	= 	x_;
	y 	= 	y_;
	id 	= 	id_;
	time_a = 0;
	time_m = 100;
	visible = false;
	solid = true;
	setStatsById(0, 0, 0);
}
Entity::~Entity() { }

// getters
int Entity::getID()
{
	return id;
}
int Entity::getX()
{
	return x;
}
int Entity::getY()
{
	return y;
}
bool Entity::getSolid()
{
	return solid;
}
bool Entity::getInRoom()
{
	return in_room;
}

// setters
void Entity::setID(int i)
{
	id = i;
}

void Entity::setStatsById(int hp_, int atk_, int def_)
{	/* the args do nothing! */
	if (id == RAT)
	{
		hp = 10;
		atk = 2;
		def = 3;
	}
	else if (id == PLAYER)
	{
		hp = 20;
		atk = 5;
		def = 4;
	}
	else if (id == DOOR_CLOSED_GRAY)
	{
	  setSolid(true);
	}
	else
	{
		hp = 999;
		atk = 999;
		def = 999;
	}
}

void Entity::setSolid(bool solid_)
{
	solid = solid_;
}
void Entity::setInRoom(bool in_room_)
{
	in_room = in_room_;
}
/*int		getHP()
{

}
int		getAtk()
{

}
int		getDef()
{

}*/

// initialize main values (used in place of ctor, because adding vars to ctors is a hassle)
void Entity::init(bool solid_, bool in_room_)
{
	solid = solid_;
	in_room = in_room_;
	randSpawn();
}

bool Entity::inPlayerLOS()
{
	/*int play_x = player->getX();
	int play_y = player->getY();*/

	for (;;) {}
}

void Entity::update(int time)
{
	int old_x = x;
	int old_y = y;

	time_a += time;
	if (time_a >= time_m)
	{
		time_a = 0;
		//make_changes();
		move(0);
	}
	// if position has changed
	if (old_x != x || old_y != y)
	{
		game.getArea()->getTile(old_x, old_y)->freeEnt();
		// XXX have a log file -- see what happens if we don't do this
	}
}

bool Entity::solidSpace(int x, int y)
{
  return (game.getArea()->getTile(x, y)->getSolid());
}

bool Entity::openDoor(int x, int y)
{
  return 0;
}

void Entity::move(int dir)
{
	// random movement
	// use direction macros instead?
	int direction = rand() % 4;
	int old_x = x;
	int old_y = y;
	
	if (direction == 0)
		game.getArea()->getTile(x + 1, y)->incrementPEO();
	else if (direction == 1)
		game.getArea()->getTile(x - 1, y)->incrementPEO();
	else if (direction == 2)
		game.getArea()->getTile(x, y + 1)->incrementPEO();
	else if (direction == 3)
		game.getArea()->getTile(x, y - 1)->incrementPEO();

	updatePosition(direction);
	
	if (old_x != x || old_y != y)
	{
	  moveEnt(x, y);
	}
}

void Entity::updatePosition(int dir)
{

  int i = 0, j = 0;

  switch (dir) {
  case 0:
    i = 1;
    break;

  case 1:
    i = -1;
    break;

  case 2:
    j = 1;
    break;

  case 3:
    j = -1;
    break;
  }

  if ( !(solidSpace(x + i, y + j)) // solidSpace is not covered in isWalkable
//       && !(game.getArea()->getTile(x + i, y + j)->hasEnt()) // Covered in isWalkable
       && (game.getArea()->getTile(x + i, y + j)->getPEO() < 2) 
       && (game.getArea()->getTile(x + i, y + j)->isWalkable()) )
  {
    x += i;
    y += j;
  }

  
  
}

void Entity::moveEnt(int new_x, int new_y)
{
	game.getArea()->getTile(new_x, new_y)->addEntity(this);
	/* And remove entity from old tile if we have direction? */
}

void Entity::randSpawn()
{
	// TODO: attribute "solidness" to each ID
	Map *area = game.getArea();
	int x_ = (rand() % (area->getWidth() - 2)) + 1;
	int y_ = (rand() % (area->getHeight() - 2)) + 1;
	// while we are still spawning in a wall
	while (area->getTile(x_, y_)->getSolid()
	        // and we are not in a room
	        || !area->getTile(x_, y_)->getInRoom())
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
