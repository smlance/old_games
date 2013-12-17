#include "main.h"

Map::Map() { }
Map::~Map()
{
	// delete and free tile pointers
	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j]) delete map[i][j];
			map[i][j] = NULL;
		}
	}
}

Tile *Map::get_tile(int x, int y)
{
	return map[x][y];
}

int Map::get_height()
{
	return map[0].size();
}

int Map::get_width()
{
	return map.size();
}

void Map::build()
{
	init();
	add_maze();
	add_rooms();
	// add_rand needs to be fixed, because it removes corner cells
	add_rand();
	remove_dead_ends();
	add_doors();
	remove_double_doors();
	add_exit();
}

void Map::init()
{
	// screen dimensions
	map.resize(MAP_COLS);
	for (unsigned int i = 0; i < map.size(); i++)
	{
		map[i].resize(MAP_ROWS);
	}

	// fill with default tiles
	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			map[i][j] = new Tile(i, j, WALL_GRAY);
			map[i][j]->set_in_room(false);
		}
	}
}

void Map::add_maze()
{
	int dig_x, dig_y, dug_curr, dug_desired, start_x, start_y;
	dug_curr = 0;
	// arbitrary number of cells to dig (fool around with it)
	dug_desired = get_height()*get_width()*.175;
	// init dig locations
	dig_x = 0;
	dig_y = 0;

	// while either is even
	// (we want to ensure both are odd)
	while (dig_x % 2 == 0 || dig_y % 2 == 0)
	{
		// add 1 to ensure we don't get a cell on the edge (0)
		// subtract 2 so we don't get the size as a result (would
		// segfault, since size only goes up to dimension - 1)
		dig_x = (rand() % (get_width() - 2)) + 1;
		dig_y = (rand() % (get_height() - 2)) + 1;
	}

	start_x = dig_x;
	start_y = dig_y;
	map[dig_x][dig_y]->set_id(GROUND_GRAY);
	dug_curr++;

	bool no_up, no_down, no_left, no_right;
	no_up = false;
	no_down = false;
	no_left = false;
	no_right = false;

	while (dug_curr < dug_desired)
	{
		// choose a direction
		int dir = rand() % 4;

		// left
		if (dir == 0)
		{
			// if we have room to dig and will not go off the map
			if (dig_x-2 >= 1)
			{
				// if the desired digging spot is solid
				if (map[dig_x-2][dig_y]->get_solid())
				{
					// we can dig!
					// "ground" the two adjacent cells in the desired direction 
					map[dig_x-1][dig_y]->set_id(GROUND_GRAY);
					map[dig_x-2][dig_y]->set_id(GROUND_GRAY);
					dig_x -= 2;
					dug_curr++;
					// make all bound-checkers false (we presumably can still move
					// at the new digging location)
					no_up = false;
					no_down = false;
					no_left = false;
					no_right = false;
				}
				// otherwise, if the desired spot is taken by a dug-out spot
				else
				{
					// set bound-checker to true (we cannot move there)
					no_left = true;
				};
			}
			// otherwise, if we cannot dig in the desired spot because it is off the map
			// (really, too close to the edge)
			else
			{
				// we cannot move there
				no_left = true;
			};
		}

		// ... the above repeats for all directions!
		// right
		else if (dir == 1)
		{
			if (dig_x+2 < get_width()-1)
			{
				if (map[dig_x+2][dig_y]->get_solid())
				{
					map[dig_x+1][dig_y]->set_id(GROUND_GRAY);
					map[dig_x+2][dig_y]->set_id(GROUND_GRAY);
					dig_x += 2;
					dug_curr++;
					no_up = false;
					no_down = false;
					no_left = false;
					no_right = false;
				}
				else
				{
					no_right = true;
				};
			}
			else
			{
				no_right = true;
			};
		}

		// up
		else if (dir == 2)
		{
			if (dig_y-2 >= 1)
			{
				if (map[dig_x][dig_y-2]->get_solid())
				{
					map[dig_x][dig_y-1]->set_id(GROUND_GRAY);
					map[dig_x][dig_y-2]->set_id(GROUND_GRAY);
					dig_y -= 2;
					dug_curr++;
					no_up = false;
					no_down = false;
					no_left = false;
					no_right = false;
				}
				else
				{
					no_up = true;
				};
			}
			else
			{
				no_up = true;
			};
		}

		// down
		else if (dir == 3)
		{
			if (dig_y+2 < get_height()-1)
			{
				if (map[dig_x][dig_y+2]->get_solid())
				{
					map[dig_x][dig_y+1]->set_id(GROUND_GRAY);
					map[dig_x][dig_y+2]->set_id(GROUND_GRAY);
					dig_y += 2;
					dug_curr++;
					no_up = false;
					no_down = false;
					no_left = false;
					no_right = false;
				}
				else
				{
					no_down = true;
				};
			}
			else
			{
				no_down = true;
			};
		};
		
		// if we are stuck (can't move in any direction)
		if (no_up && no_down && no_left && no_right)
		{
			int x = 0;
			int y = 0;
			// while our randomly generated new digging locations are even
			while (x % 2 == 0 || y % 2 == 0)
			{
				// randomize them again (we do this to ensure they're odd)
				x = rand() % (get_width()-2) + 1;
				y = rand() % (get_height()-2) + 1;
			}

			// if our new spot is a ground tile
			if (!(map[x][y]->get_solid())
				// and we are an even number of spaces away from our original dig position
				// (#o###n#)
				// o is original, n is new
				// (good dig spot!)
				&& (abs(start_y - y) % 2 == 0) && (abs(start_x - x) % 2 == 0))
			{
				// set dig position to new generated coordinates
				dig_x = x;
				dig_y = y;
				// assume we can move in any direction
				no_up = false;
				no_down = false;
				no_left = false;
				no_right = false;
			}
		}
	}
}

void Map::add_rooms()
{
	int dig_x, dig_y, cur, des, size_x, size_y;
	des = rand() % 3 + 2;
	cur = 0;
	
	while (cur < des)
	{
		dig_x = rand() % (get_width()-2) + 1;
		dig_y = rand() % (get_height()-2) + 1;
		size_x = rand() % 5 + 6;
		size_y = rand() % 5 + 3;
		
		// if our dig coordinates and size are too big for the map
		while (dig_x + size_x >= get_width()-1 || dig_y + size_y >= get_height()-1)
		{
			// make new positions with smaller rooms
			dig_x = rand() % (get_width()-2) + 1;
			dig_y = rand() % (get_height()-2) + 1;
			size_x = rand() % 5 + 4;
			size_y = rand() % 5 + 3;
		};
		
		if (!(map[dig_x][dig_y]->get_solid())
		 && map[dig_x-1][dig_y]->get_solid()
		 && map[dig_x][dig_y-1]->get_solid()
		 && !(map[dig_x+size_x][dig_y+size_y]->get_solid())
		 && map[dig_x+size_x+1][dig_y+size_y]->get_solid()
		 && map[dig_x+size_x][dig_y+size_y+1]->get_solid())
		{
			bool taken = false;
			
			for (int i = dig_x-1; i <= dig_x+size_x+1; i++)
			{
				for (int j = dig_y-1; j <= dig_y+size_y+1; j++)
				{
					if (map[i][j]->get_in_room())
					{
						taken = true;
					}
				}
			}
			if (!taken)
			{
				for (int i = dig_x; i <= dig_x+size_x; i++)
				{
					for (int j = dig_y; j <= dig_y+size_y; j++)
					{
						map[i][j]->set_id(GROUND_GRAY);
						map[i][j]->set_in_room(true);
					}
				}
				cur++;
			}
			
		}
		
	}
}

void Map::add_doors()
{
	// go 1 within bounds on both low and high ends, because those rows/cols
	// will not have floor spaces available (yet)
	for (int i = 1; i < get_width() - 1; i++)
	{
		for (int j = 1; j < get_height() - 1; j++)
		{
			// conditions: tile is not in a room
			if (!map[i][j]->get_in_room()
			// and has exactly two wall tiles UDLR-adjacent
			&& game.num_walls_udlr(i, j) == 2
			// and is UDLR-adjacent to a tile in a room
			&& game.udlr_adj_in_room(i, j)
			// and tile is not a wall
			&& !map[i][j]->get_solid()
			// and a door has not already been made here
			&& !map[i][j]->has_door())
			{
				// ...then add a door to this cell!
				Entity *door = new Entity(i, j, DOOR_CLOSED_GRAY);
				// need to check for size (?XXX?)
				map[i][j]->add_entity(door);
			}
		}
	}
}

void Map::add_rand()
{
	int dig_x, dig_y;
	int cur, des;
	des = rand() % 10 + 20;
	cur = 0;
	
	while (cur < des)
	{
		dig_x = rand() % (get_width()-2) + 1;
		dig_y = rand() % (get_height()-2) + 1;
		int count = 0;
		
		for (int i = -1; i<=1; i++)
		{
			for (int j = -1; j<=1; j++)
			{
				if (j == 0 || i == 0 && !(j == 0 && i == 0))
				{
					if (!map[dig_x+i][dig_y+j]->get_solid())
					{
						count++;
					};
				};
			}
		}
		
		if (count >= 2)
		{
			map[dig_x][dig_y]->set_id(GROUND_GRAY);
			cur++;
		};
		
		count = 0;
	}
}

bool Map::dead_ends_exist()
{
	bool b = false;
	
	for (int i = 0; i < get_width(); i++)
	{
		for (int j = 0; j < get_height(); j++)
		{
			if (!map[i][j]->get_solid())
			{
				int count = 0;
				
				for (int x = -1; x <= 1; x++)
				{
					for (int y = -1; y <= 1; y++)
					{
						if ((y == 0 || x == 0) && !(y == 0 && x == 0)
						 && map[i+x][y+j]->get_solid())
						{
							count++;
						};
					}
				}
				
				if (count == 3)
				{
					b = true;
				};
			}
		}
	}
	
	return b;
}

void Map::remove_dead_ends()
{
	// remove ALL? then player has no dead end to spawn in :(
	while (dead_ends_exist())
	{
	/*performs a top-down and then down-top search to get rid of dead-ends*/
	for (int i = 0; i < get_width(); i++)
	{
		for (int j = 0; j < get_height(); j++)
		{
		
			if (!map[i][j]->get_solid())
			{
				int count = 0;
				
				for (int x = -1; x <= 1; x++)
				{
					for (int y = -1; y <= 1; y++)
					{
						if ((y == 0 || x == 0) && !(y == 0 && x == 0)
						 && map[i+x][y+j]->get_solid())
						{
							count++;
						};
					}
				}
				
				if (count == 3)
				{
					map[i][j]->set_id(WALL_GRAY);
				};
			}; //end if (this tile is ground/door)
			
		}
	}
	
	for (int i = get_width()-1; i >= 0; i--)
	{
		for (int j = get_height()-1; j >= 0; j--)
		{
		
			if (!map[i][j]->get_solid())
			{
				int count = 0;
				
				for (int x = -1; x <= 1; x++)
				{
					for (int y = -1; y <= 1; y++)
					{
						if ((y == 0 || x == 0) && !(y == 0 && x == 0)
						 && map[i+x][y+j]->get_solid())
						{
							count++;
						};
					}
				}
				
				if (count == 3)
				{
					map[i][j]->set_id(WALL_GRAY);
				};
			}; //end if (this tile is ground/door)
			
		}
	}
	}
}

void Map::remove_double_doors()
{
	for (int i = 0; i < get_width(); i++)
	{
		for (int j = 0; j < get_height(); j++)
		{
			// if tile has a door
			if (map[i][j]->has_door()
			// and there are not 2 UDLR-adjacent ground tiles
			&& game.num_grounds_udlr(i, j) != 2)
			{
				// remove the door
				map[i][j]->remove_ent(0);
				// and make the tile a ground tile
				map[i][j]->set_id(WALL_GRAY);
			}
		}
	}
}

void Map::add_exit()
{
	int cur = 0;
	int des = 1;
	int i, j;
	
	while (cur < des)
	{
		i = (rand() % (get_width() - 2)) + 1;
		j = (rand() % (get_height() - 2)) + 1;
		// if tile is in room
		if (map[i][j]->get_in_room()
		// and there are 2 UDLR-adjacent ground tiles
		&& game.num_grounds_udlr(i, j) == 2)
		{
			// (the tile will be a ground tile)
			// put the stairs on top of this cell
			Entity *stairs_down = new Entity(i, j, STAIRS_DOWN_GRAY);
			map[i][j]->add_entity(stairs_down);
			cur++;
		}
	}
}
