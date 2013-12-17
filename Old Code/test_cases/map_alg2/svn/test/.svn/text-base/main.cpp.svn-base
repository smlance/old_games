/*TODO: optimization of certain steps, removal of dead ends, pruning
of a surplus of doors, XXX add start and exit (stairs?) XXX ...*/

#include "main.h"

Map::Map()
{
	initMap();
	buildMap();
	addRand();
	addRooms();
	removeDoubleDoors();
	printMap();
}

void Map::removeDoubleDoors() /*can originally just make maps fix this when
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
			}
		}
	}
}

void Map::printMap()
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
}

void Map::initMap()
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

void Map::addDoors(int y, int x) /*only do for edges*/
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

void Map::addRooms()
{
	int dig_x, dig_y, cur, des, size_x, size_y;
	des = rand() % 4 + 6;
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
						addDoors(i, j);
					}
				}
				cur++;
			}
			
		}
		
	}
}

void Map::addRand()
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

void Map::buildMap()
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
	no_up = FALSE;
	no_down = FALSE;
	no_left = FALSE;
	no_right = FALSE;
	
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
					no_up = FALSE;
	no_down = FALSE;
	no_left = FALSE;
	no_right = FALSE;
				
			}
			else
			{
				no_up = TRUE;
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
					no_up = FALSE;
	no_down = FALSE;
	no_left = FALSE;
	no_right = FALSE;
			}
			else
			{
				no_down = TRUE;
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
					no_up = FALSE;
	no_down = FALSE;
	no_left = FALSE;
	no_right = FALSE;
			}
			else
			{
				no_left = TRUE;
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
					no_up = FALSE;
	no_down = FALSE;
	no_left = FALSE;
	no_right = FALSE;
			}
			else
			{
				no_right = TRUE;
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
				no_up = FALSE;
	no_down = FALSE;
	no_left = FALSE;
	no_right = FALSE;
			}
		}
		//getch();
	}
	
}

int main()
{
	srand((unsigned)time(0));
	initscr();
	curs_set(0);
	noecho();
	keypad(stdscr, true);
	
	Player player;
	
	getch();
	endwin();
	
	return 0;
}
