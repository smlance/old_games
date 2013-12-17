#include "main.h"

Game::Game()
{
	// initially at menu
	state = STATE_PLAY;

	// set arbitrary max number of ents
	ent_list.resize(100);

	// nullify entities
	for (unsigned int i = 0; i < ent_list.size(); i++)
	{
		ent_list[i] = NULL;
	}

	// generate map
	//area = new Map;
	//area->build();

	// make and spawn player and entities
	//ent_list[0] = new Player(0, 0, PLAYER);
	//ent_list[0]->rand_spawn();
	////init_rand_ents();
}

Game::~Game()
{
	for (unsigned int i = 0; i < ent_list.size(); i++)
	{
		//if (ent_list[i]) delete ent_list[i];
		ent_list[i] = NULL;
	}
}

void Game::update(int time)
{
	for (unsigned int i = 0; i < ent_list.size(); i++)
	{
		if (ent_list[i]) ent_list[i]->update(time);
	}
}

Map *	Game::get_area()
{
	return area;
}
int 	Game::get_ent_list_size()
{
	return ent_list.size();
}
Entity *Game::get_ent(int i)
{
	return ent_list[i];
}
int		Game::get_state()
{
	return state;
}
void	Game::set_state(int s)
{
	state = s;
}

void Game::init()
{
	// initially at menu
	state = STATE_PLAY;

	// set arbitrary max number of ents
	ent_list.resize(100);

	// nullify entities
	for (unsigned int i = 0; i < ent_list.size(); i++)
	{
		ent_list[i] = NULL;
	}

	// generate map
	area = new Map;
	area->build();

	// make and spawn player and entities
	ent_list[0] = new Player(0, 0, PLAYER);
	ent_list[0]->rand_spawn();
	init_rand_ents();
}

void Game::update(int time)
{
	// send time elapsed to every entity
	for (unsigned int i = 0; i < ent_list.size(); i++)
	{
		if (ent_list[i]) ent_list[i]->update(time);
	}
}

void Game::init_rand_ents()
{
	int num_ents = (rand() % 5) + 5;
	int ents_made = 0;

		// loop through the entities in the list
		for (int i = 0; i < ent_list.size(); i++)
		{
			// if we get to a position without an entity
			if (!ent_list[i] && ents_made < num_ents)
			{
				// make one
				ent_list[i] = new Entity(0, 0, RAT);
				// initialize it (spawn it randomly)
				ent_list[i]->init(true, true);
				ents_made++;
			}
		}
	
}

void Game::check_player_move(Key key)
{
	int x = ent_list[0]->ent_info.x;
	int y = ent_list[0]->ent_info.y;

	/*
	 * switch based on direction
	 * check to see that player CAN move (non-solid space requested); if so,
	 * move him
	 */
	switch (key)
	{
	case SDLK_UP:
		if (!(area->get_tile(x, y - 1)->get_solid()))
			ent_list[0]->move(MOVE_UP);
		break;

	case SDLK_DOWN:
		if (!(area->get_tile(x, y + 1)->get_solid()))
			ent_list[0]->move(MOVE_DOWN);
		break;

	case SDLK_LEFT:
		if (!(area->get_tile(x - 1, y)->get_solid()))
			ent_list[0]->move(MOVE_LEFT);
		break;

	case SDLK_RIGHT:
		if (!(area->get_tile(x + 1, y)->get_solid()))
			ent_list[0]->move(MOVE_RIGHT);
		break;

	default:
		break;
	}
}

int Game::num_walls_udlr(int x, int y)
{
	/*
	 * find number of walls in up, down, left, and right positions:
	 * #-U-#
	 * L-P-R
	 * #-D-#
	 * (P = player)
	 * (ignore corners, #s)
	 */
	int walls = 0;

	if (area->get_tile(x + 1, y))
	{
		if (area->get_tile(x + 1, y)->get_solid())
			walls++;
	}

	if (area->get_tile(x - 1, y))
	{
		if (area->get_tile(x - 1, y)->get_solid())
			walls++;
	}

	if (area->get_tile(x, y + 1))
	{
		if (area->get_tile(x, y + 1)->get_solid())
			walls++;
	}

	if (area->get_tile(x, y - 1))
	{
		if (area->get_tile(x, y - 1)->get_solid())
			walls++;
	}

	return walls;
}

int Game::num_grounds_udlr(int x, int y)
{
	int grounds = 0;

	if (area->get_tile(x + 1, y))
	{
		if (!area->get_tile(x + 1, y)->get_solid())
			grounds++;
	}

	if (area->get_tile(x - 1, y))
	{
		if (!area->get_tile(x - 1, y)->get_solid())
			grounds++;
	}

	if (area->get_tile(x, y + 1))
	{
		if (!area->get_tile(x, y + 1)->get_solid())
			grounds++;
	}

	if (area->get_tile(x, y - 1))
	{
		if (!area->get_tile(x, y - 1)->get_solid())
			grounds++;
	}

	return grounds;
}

bool Game::udlr_adj_in_room(int x, int y)
{
	if (area->get_tile(x + 1, y))
	{
		if (area->get_tile(x + 1, y)->get_in_room())
			return true;
	}

	if (area->get_tile(x - 1, y))
	{
		if (area->get_tile(x - 1, y)->get_in_room())
			return true;
	}

	if (area->get_tile(x, y + 1))
	{
		if (area->get_tile(x, y + 1)->get_in_room())
			return true;
	}

	if (area->get_tile(x, y - 1))
	{
		if (area->get_tile(x, y - 1)->get_in_room())
			return true;
	}
	
	return false;

}
