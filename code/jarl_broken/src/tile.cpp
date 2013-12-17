#include "main.h"

Tile::Tile()
{
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

void Tile::init(bool solid_, bool in_room_) {
	solid = solid_;
	in_room = in_room_;
	
	// arbitrary size for entity list
	entity_list.resize(5);
	// init entity list
	for (unsigned int i = 0; i < entity_list.size(); i++)
	{
		entity_list[i] = NULL;
	}
	
	// look at id and determine whether solid
	set_solid_by_id();
}

void Tile::set_id(int id_)
{
	Entity::set_id(id_);
	set_solid_by_id();
}

void Tile::set_solid_by_id() {
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

Entity *Tile::get_ent(int pos)
{
	return entity_list[pos];
}

int Tile::get_ent_list_size()
{
	return entity_list.size();
}

void Tile::add_entity(Entity *ent)
{
	for (unsigned int i = 0; i < entity_list.size(); i++)
	{
		// if we come to a cell without an entity
		if (!(entity_list[i]))
			entity_list[i] = ent;
			// break loop
			i = entity_list.size();
	}
}

void Tile::remove_ent(int pos)
{
	if (entity_list[pos])
	{
		delete entity_list[pos];
		entity_list[pos] = NULL;
	}
}

void Tile::free_ent()
{
	
}

bool Tile::has_door()
{
	if (entity_list[0])
	{
		// TODO: make id sets/types (DOOR, SWORD, SHIELD, POT, etc.)
		// and use them instead of id's for these kinds of checks
		if (entity_list[0]->get_id() == DOOR_CLOSED_GRAY)
			return true;
		else
			return false;
	}
	else
		return false;
}
