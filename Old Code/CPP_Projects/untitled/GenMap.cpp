#include "main.h"
#include "GenMap.h"

/*TODO: if ground cell surounded by seven walls, prune it*/
/*ACTUALLY, only do it if it's caticorner to another ground.*/

GenMap::GenMap()
{
	initMap();
	buildMap();
	addRand();
	addRooms();
	removeDoubleDoors();
	while (deadEndsExist())
	{
		removeDeadEnds();
	}
	toFile();
}

bool GenMap::toFile()
{
	std::ofstream map_file ("./resources/map.txt");
	//map_file.open("./resources/map.txt");
	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx; j++)
		{
			//stringstream
			if (map[i][j].type == wall)
			{
				map_file << '0' << " ";
			}
			else if (map[i][j].type == ground)
			{
				map_file << '1' << " ";
			}
			else if (map[i][j].type == door)
			{
				map_file << '2' << " ";
			}
		}
		map_file << "\n";
	}
	map_file.close();
	return true;
}

bool GenMap::deadEndsExist()
{
	bool b = false;
	
	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx; j++)
		{
			if (map[i][j].type != wall)
			{
				int count = 0;
				
				for (int y = -1; y <= 1; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						if ((y == 0 || x == 0) && !(y == 0 && x == 0)
						 && map[i+y][x+j].type == wall)
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

void GenMap::removeDeadEnds()
{
	/*performs a top-down and then down-top search to get rid of dead-ends*/
	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx; j++)
		{
		
			if (map[i][j].type != wall)
			{
				int count = 0;
				
				for (int y = -1; y <= 1; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						if ((y == 0 || x == 0) && !(y == 0 && x == 0)
						 && map[i+y][x+j].type == wall)
						{
							count++;
						};
					}
				}
				
				if (count == 3)
				{
					//mvaddch(i, j, '*' | A_STANDOUT);
					map[i][j].type = wall;
					//printMap(); slowLoop(); refresh();
				};
			}; //end if (this tile is ground/door)
			
		}
	}
	
		for (int i = sy-1; i >= 0; i--)
		{
		for (int j = sx-1; j >= 0; j--)
		{
		
			if (map[i][j].type != wall)
			{
				int count = 0;
				
				for (int y = -1; y <= 1; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						if ((y == 0 || x == 0) && !(y == 0 && x == 0)
						 && map[i+y][x+j].type == wall)
						{
							count++;
						};
					}
				}
				
				if (count == 3)
				{
					//mvaddch(i, j, '*' | A_STANDOUT);
					//getch();
					map[i][j].type = wall;
					//printMap(); slowLoop(); refresh();
				};
			}; //end if (this tile is ground/door)
			
		}
	}
}

void GenMap::removeDoubleDoors() /*can originally just make maps fix this when
they are made by noticing if two non-in_room grounds are next to each
other and filling one*/
{
	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx; j++)
		{
			if (map[i][j].type == door && (map[i+1][j].type == door
			|| map[i-1][j].type == door || map[i][j+1].type == door
			|| map[i][j-1].type == door))
			{
				map[i][j].type = wall;
				//printMap(); slowLoop(); refresh();
			}
		}
	}
}

/*void GenMap::printMap()
{
	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx; j++)
		{
			if (map[i][j].type == door)
			{
				attron(A_BOLD);
				mvaddch(i, j, map[i][j].type);
				attroff(A_BOLD);
			}
			else
			{
			mvaddch(i, j, map[i][j].type);
			}
		}
	}
}*/

void GenMap::initMap()
{
	for (int i = 0; i < sy; i++)
	{
		for (int j = 0; j < sx; j++)
		{
			map[i][j].type = wall;
			map[i][j].in_room = false;
		}
	}
}

void GenMap::addDoors(int y, int x) /*only do for edges*/
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((i == 0 || j == 0) && !(i == 0 && j == 0)
			 && (map[y][x].in_room)
			 && (map[y+i][x+j].type == ground
			 && map[y+i][x+j].in_room == false)
			 && (map[y+i][x+j].type != door))
			{
				map[y+i][x+j].type = door;
			}
		}
	}
}

void GenMap::addRooms()
{
	int dig_x, dig_y, cur, des, size_x, size_y;
	des = rand() % 3 + 2;
	cur = 0;
	
	while (cur < des)
	{
		dig_x = rand() % (sx-2) + 1;
		dig_y = rand() % (sy-2) + 1;
		size_x = rand() % 5 + 6;
		size_y = rand() % 5 + 3;
		
		while (dig_x + size_x >= sx-1 || dig_y + size_y >= sy-1)
		{
			dig_x = rand() % (sx-2) + 1;
			dig_y = rand() % (sy-2) + 1;
			size_x = rand() % 5 + 4;
			size_y = rand() % 5 + 3;
		};
		
		if (map[dig_y][dig_x].type == ground
		 && map[dig_y-1][dig_x].type == wall
		 && map[dig_y][dig_x-1].type == wall
		 && map[dig_y+size_y][dig_x+size_x].type == ground
		 && map[dig_y+size_y+1][dig_x+size_x].type == wall
		 && map[dig_y+size_y][dig_x+size_x+1].type == wall)
		{
			bool taken = false;
			
			for (int i = dig_y-1; i <= dig_y+size_y+1; i++)
			{
				for (int j = dig_x-1; j <= dig_x+size_x+1; j++)
				{
					if (map[i][j].in_room == true)
					{
						taken = true;
					}
				}
			}
			if (!taken)
			{
				for (int i = dig_y; i <= dig_y+size_y; i++)
				{
					for (int j = dig_x; j <= dig_x+size_x; j++)
					{
						map[i][j].type = ground;
						map[i][j].in_room = true;
						//printMap(); slowLoop(); refresh();
						addDoors(i, j);
					}
				}
				cur++;
			}
			
		}
		
	}
}

void GenMap::addRand()
{
	int dig_x, dig_y;
	int cur, des;
	des = rand() % 10 + 20;
	cur = 0;
	
	while (cur < des)
	{
		dig_x = rand() % (sx-2) + 1;
		dig_y = rand() % (sy-2) + 1;
		int count = 0;
		
		for (int i = -1; i<=1; i++)
		{
			for (int j = -1; j<=1; j++)
			{
				if (j == 0 || i == 0 && !(j == 0 && i == 0))
				{
					if (map[dig_y+i][dig_x+j].type == ground)
					{
						count++;
						//printMap(); slowLoop(); refresh();
					};
				};
			}
		}
		
		if (count >= 2)
		{
			map[dig_y][dig_x].type = ground;
			cur++;
		};
		
		count = 0;
	}
}

void slowLoop()
{
	for (float i = 0.0; i < 10000.0; i += 1.0)
	{
		for (float j = 0.0; j < 1000.0; j += 1.0)
		{
		
		}
	}
}

void GenMap::buildMap()
{
	int dig_x, dig_y, dug_curr, dug_desired, start_x, start_y;
	dug_curr = 0;
	dug_desired = sy*sx*.205;
	dig_x = rand() % (sx-2) + 1;
	dig_y = rand() % (sy-2) + 1;
	start_x = dig_x;
	start_y = dig_y;
	map[dig_y][dig_x].type = ground;
	dug_curr++;
	
	bool no_up, no_down, no_left, no_right;
	no_up = false;
	no_down = false;
	no_left = false;
	no_right = false;
	
	while (dug_curr < dug_desired)
	{	
		int dir = rand() % 4;
		
		if (dir == 0) //up
		{
			if (map[dig_y-2][dig_x].type == wall && dig_y-2 >= 1)
			{
				map[dig_y-1][dig_x].type = ground;
				map[dig_y-2][dig_x].type = ground;
				dig_y -= 2;
				dug_curr++;
				//printMap(); slowLoop(); refresh();
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
		
		else if (dir == 1) //down
		{
			if (map[dig_y+2][dig_x].type == wall && dig_y+2 < sy-1)
			{
				map[dig_y+1][dig_x].type = ground;
				map[dig_y+2][dig_x].type = ground;
				dig_y += 2;
				dug_curr++;
				//printMap(); slowLoop(); refresh();
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
		
		else if (dir == 2) //left
		{
			if (map[dig_y][dig_x-2].type == wall && dig_x-2 >= 1)
			{
				map[dig_y][dig_x-1].type = ground;
				map[dig_y][dig_x-2].type = ground;
				dig_x -= 2;
				dug_curr++;
				//printMap(); slowLoop(); refresh();
					no_up = false;
	no_down = false;
	no_left = false;
	no_right = false;
			}
			else
			{
				no_left = true;
			};
		}
		
		else if (dir == 3) //right
		{
			if (map[dig_y][dig_x+2].type == wall && dig_x+2 < sx-1)
			{
				map[dig_y][dig_x+1].type = ground;
				map[dig_y][dig_x+2].type = ground;
				dig_x += 2;
				dug_curr++;
				//printMap(); slowLoop(); refresh();
					no_up = false;
	no_down = false;
	no_left = false;
	no_right = false;
			}
			else
			{
				no_right = true;
			};
		};
		if (no_up && no_down && no_left && no_right)
		{
			int x = rand() % (sx-2) + 1;
			int y = rand() % (sy-2) + 1;
			
			if (map[y][x].type == ground && (abs(start_y - y) % 2 == 0) && (abs(start_x - x) % 2 == 0))
			{
			//mvaddstr(0, 81, "Hello");
				dig_x = x;
				dig_y = y;
				no_up = false;
	no_down = false;
	no_left = false;
	no_right = false;
			}
		}
		//getch();
	}
	
}

GenMap::~GenMap()
{
	//delete map;
}
