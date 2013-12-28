#include "main.h"

Game::Game() { }
Game::~Game()
{
	for (unsigned int i = 0; i < ent_list.size(); i++)
	{
		if (ent_list[i]) delete ent_list[i];
		ent_list[i] = NULL;
	}
}

Map *	Game::getArea()
{
	return area;
}
int 	Game::getEntListSize()
{
	return ent_list.size();
}
Entity *Game::getEnt(int i)
{
	return ent_list[i];
}
int		Game::getState()
{
	return state;
}
void	Game::setState(int s)
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
	ent_list[0]->randSpawn();

	generatePlayerLOS();
	initRandEnts();
}

void Game::update(int time)
{
	// clear number of projected entities in each tile
	for (unsigned int i = 0; i < area->getWidth(); i++)
	{
		for (unsigned int j = 0; j < area->getHeight(); j++)
		{
			if ( !(area->getTile(i, j)->getSolid()) )
			{
				area->getTile(i, j)->zeroPEO();
			}
		}
	}
	// send time elapsed to every entity
	for (unsigned int i = 0; i < ent_list.size(); i++)
	{
		if (ent_list[i]) ent_list[i]->update(time);
	}

}

void Game::initRandEnts()
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

void Game::checkPlayerMove(Key key)
{
	int x = ent_list[0]->getX();
	int y = ent_list[0]->getY();

	/*
	 * switch based on direction
	 * check to see that player CAN move (non-solid space requested); if so,
	 * move him
	 */
	switch (key)
	{

	  /* All of these conditionals should be placed in one method that
	     accepts (int x, int y) as args... ideally, the player and the other
	     entities should use similar if not the same methods for movement */
	case SDLK_UP:
	  if (!(area->getTile(x, y - 1)->getSolid())
	      && !(game.getArea()->getTile(x, y - 1)->hasEnt()) 
	       && !(game.getArea()->getTile(x, y - 1)->getWalkable()) )
	    /* For making sure an entity doesn't walk into a door; same below */
	    ent_list[0]->move(MOVE_UP);
	  break;

	case SDLK_DOWN:
	  if (!(area->getTile(x, y + 1)->getSolid())
	      && !(game.getArea()->getTile(x, y + 1)->hasEnt()) 
	      && !(game.getArea()->getTile(x, y + 1)->getWalkable()) )
	    ent_list[0]->move(MOVE_DOWN);
	  break;

	case SDLK_LEFT:
	  if (!(area->getTile(x - 1, y)->getSolid())
	      && !(game.getArea()->getTile(x - 1, y)->hasEnt()) 
	      && !(game.getArea()->getTile(x - 1, y)->getWalkable()) )
	    ent_list[0]->move(MOVE_LEFT);
	  break;

	case SDLK_RIGHT:
	  if (!(area->getTile(x + 1, y)->getSolid())
	      && !(game.getArea()->getTile(x + 1, y)->hasEnt()) 
	      && !(game.getArea()->getTile(x + 1, y)->getWalkable()) )
	    ent_list[0]->move(MOVE_RIGHT);
	  break;

	default:
	  break;
	}

	generatePlayerLOS();

}

int Game::numWallsUDLR(int x, int y)
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

	if (area->getTile(x + 1, y))
	{
		if (area->getTile(x + 1, y)->getSolid())
			walls++;
	}

	if (area->getTile(x - 1, y))
	{
		if (area->getTile(x - 1, y)->getSolid())
			walls++;
	}

	if (area->getTile(x, y + 1))
	{
		if (area->getTile(x, y + 1)->getSolid())
			walls++;
	}

	if (area->getTile(x, y - 1))
	{
		if (area->getTile(x, y - 1)->getSolid())
			walls++;
	}

	return walls;
}

int Game::numGroundsUDLR(int x, int y)
{
	int grounds = 0;

	if (area->getTile(x + 1, y))
	{
		if (!area->getTile(x + 1, y)->getSolid())
			grounds++;
	}

	if (area->getTile(x - 1, y))
	{
		if (!area->getTile(x - 1, y)->getSolid())
			grounds++;
	}

	if (area->getTile(x, y + 1))
	{
		if (!area->getTile(x, y + 1)->getSolid())
			grounds++;
	}

	if (area->getTile(x, y - 1))
	{
		if (!area->getTile(x, y - 1)->getSolid())
			grounds++;
	}

	return grounds;
}

bool Game::numUDLRAdjInRoom(int x, int y)
{
	if (area->getTile(x + 1, y))
	{
		if (area->getTile(x + 1, y)->getInRoom())
			return true;
	}

	if (area->getTile(x - 1, y))
	{
		if (area->getTile(x - 1, y)->getInRoom())
			return true;
	}

	if (area->getTile(x, y + 1))
	{
		if (area->getTile(x, y + 1)->getInRoom())
			return true;
	}

	if (area->getTile(x, y - 1))
	{
		if (area->getTile(x, y - 1)->getInRoom())
			return true;
	}

	return false;
}

void Game::generatePlayerLOS()
{
	float x, y;
	int i;
	int LOS_radius = 5;

	for (i = 0; i < 360; i+=15)
	{
		x = cos((float)i*0.01745f);
		y = sin((float)i*0.01745f);

		int j;
		float ox, oy;
		ox = (float)(ent_list[0]->getY())+0.5f;//TILE_WIDTH)+0.5f;
		oy = (float)(ent_list[0]->getX())+0.5f;//TILE_HEIGHT)+0.5f;
		for (j = 0; j < LOS_radius; j++)
		{
			int ioy = (int)oy;
			int iox = (int)ox;
			// check bounds before determining LOS
			if (ioy >= 0 && iox >= 0
			        && ioy < area->getWidth() && iox < area->getHeight())
			{
				if (!(area->getTile(ioy, iox)->getVisible()))
				{
					area->getTile(ioy, iox)->setVisible(true);
				}
				ox+=x;
				oy+=y;
				// if we encounter a wall, make it visible, but nothing beyond it
				if (area->getTile(ioy, iox)->getSolid())
				{
					j = LOS_radius; // "reset" AKA stop looking past this point
				}
			}
		}
	}
}
