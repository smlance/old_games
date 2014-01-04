#include "main.h"

Tile::Tile(int x_, int y_, int id_) : Entity(x_, y_, id_)
{
	// arbitrary size for entity list
	entity_list.resize(5);
	// init entity list
	for (unsigned int i = 0; i < entity_list.size(); i++)
	{
		entity_list[i] = NULL;
	}

	// look at id and determine whether solid
	setSolidById();
	
	projected_ent_occupants = 0;
}

Tile::~Tile()
{
	// free objects, if any, in list
	for (unsigned int i = 0; i < entity_list.size(); i++)
	{
		if (entity_list[i])
			delete entity_list[i];
		entity_list[i] = NULL;
	}
}

bool Tile::getVisible()
{
	return visible;
}

void Tile::setVisible(bool visible_)
{
	visible = visible_;
}

void Tile::init(bool solid_, bool in_room_)
{
	solid = solid_;
	in_room = in_room_;
}

void Tile::incrementPEO()
{
	projected_ent_occupants++;
}

void Tile::zeroPEO()
{
	projected_ent_occupants = 0;
}

int Tile::getPEO()
{
	return projected_ent_occupants;
}

void Tile::setID(int id_)
{
	Entity::setID(id_);
	setSolidById();
}

void Tile::setSolidById() /* ??? */
{
	switch (id)
	{
		// ground tiles
	case GROUND_GRAY:
		// case ...:
		solid = false;
		break;

		// wall tiles
	case WALL_GRAY:
		// case ...:
		solid = true;
		break;
		
	default:
		break;
	}
}

/*
  getSolid is used while the map is being made. Some other "getSolid" (maybe
  isWalkable?) needs to be made specifically for gameplay.

  isWalkable needs to be called when the Game object is determining whether 
  the player can move to the cell to which he wants to move. (look in game.cpp)
 */
// bool Tile::getSolid()
// {
//   return solid;
// }

bool Tile::isWalkable()
{

  /*
    Should we also cover the solidSpace() check here? (We can't walk on solid
    spaces, after all...)
   */

  for (int i = 0; i < entity_list.size(); i++)
  {
    if (entity_list[i])
    {
      if (entity_list[i]->getSolid() == true) return false;
    }
  }

  return true;
}

Entity *Tile::getEnt(int pos)
{
	return entity_list[pos];
}

bool Tile::hasEnt()
{
	for (int i = 0; i < getEntListSize(); i++)
	{
		if (getEnt(i))
		{
			if  (getEnt(i)->getID() == RAT ||
				getEnt(i)->getID() == PLAYER)// || hasDoor() )
				//std::cout << "!" << std::endl;
				return true;
				//std::cout << getEnt(i)->getX() << " " << getEnt(i)->getY() << std::endl;
		}
	}
	
	return false;
}

int Tile::getEntListSize()
{
	return entity_list.size();
}

void Tile::addEntity(Entity *ent)
{
	for (unsigned int i = 0; i < entity_list.size(); i++)
	{
		// if we come to a cell without an entity
		if (!(entity_list[i]))
		{
			entity_list[i] = ent;
			i = entity_list.size();
		}
	}
}

void Tile::removeEnt(int pos)
{
	if (entity_list[pos])
	{
		delete entity_list[pos];
		entity_list[pos] = NULL;
	}
}

void Tile::freeEnt()
{
	//entity_list[0] = NULL;
	//solid = false; // this could change, depending on whether entities can be on solid spaces
	// XXX need to make this more specific to entities later (pass in address / the specific entity we want to get rid of) and make it general
	for (int i = 0; i < getEntListSize(); i++)
	{
		if (entity_list[i])
		{
			if (entity_list[i]->getID() == RAT ||
				getEnt(i)->getID() == PLAYER)
				entity_list[i] = NULL;
		}
	}
}

bool Tile::hasDoor()
{
	if (entity_list[0])
	{
		// TODO: make id sets/types (DOOR, SWORD, SHIELD, POT, etc.)
		// and use them instead of id's for these kinds of checks
		if (entity_list[0]->getID() == DOOR_CLOSED_GRAY)
			return true;
		else
			return false;
	}
	else
		return false;
}
