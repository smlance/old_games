#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#define SI_X 80
#define SI_Y 20

int map[SI_Y][SI_X];

void initMap()
{
	for (int i = 0; i<SI_Y; i++)
	{
		for (int j = 0; j<SI_X; j++)
		{
			map[i][j] = 35;
		}
	}
}

int getRand(int range, int un_range)
{
	int uncert = rand() % un_range + 1;
	
	if (rand() & 1)
	{
		return rand() % range + uncert;
	}
	else
	{
		return -(rand() % range + uncert);
	}
}

int getRPos()
{
	int dir = rand() % 4 + 1;
	return dir;
}

void printMap();

void buildMap()
{
	int dug_tiles = 0;
	int target_dug_tiles = int(SI_X*SI_Y);
	int dig_x = SI_X/2;
	int dig_y = SI_Y/2;
	
	while (dug_tiles < target_dug_tiles)
	{
		if (map[dig_y][dig_x] == 46)
		{
			dig_x = getRand(1, 40) + SI_X/2;
			dig_y = getRand(2, 7) + SI_Y/2;
		};
		
		int move_dir = getRPos();
		
		if (move_dir == 1 && map[dig_y-1][dig_x] != 46) //up
		{
			dig_y--;
		}
		else if (move_dir == 2 && map[dig_y+1][dig_x] != 46) //down
		{
			dig_y++;
		}
		else if (move_dir == 3 && map[dig_y][dig_x-1] != 46) //left
		{
			dig_x--;
		}
		else if (move_dir == 4 && map[dig_y][dig_x+1] != 46) //right
		{
			dig_x++;
		};
		
		if (dig_x < 1 || dig_x > SI_X-2 || dig_y < 1 || dig_y > SI_Y-2) //if the digger went off the map
		{
			dig_x = getRand(1, 40) + SI_X/2;
			dig_y = getRand(1, 7) + SI_Y/2;
			for (int n = -1; n<1; n++)
			{ for (int k = -1; k<1; k++)
			{
			if (!(map[dig_y][dig_x] == '#' && map[dig_y+n][dig_x+k] == '.')){
			dig_x = getRand(1, 40) + SI_X/2;
			dig_y = getRand(1, 7) + SI_Y/2;
			break;
			}
			}
			}
		}
		/*if (dig_x < 1)
		{
			dig_x++;
		}
		else if (dig_x > SI_X-2)
		{
			dig_x--;
		}
		else if (dig_y < 1)
		{
			dig_y++;
		}
		else if (dig_y > SI_Y-2)
		{
			dig_y--;
		}*/
		else
		{
			map[dig_y][dig_x] = 46;
			dug_tiles++;
		};
	}
}

void printMap()
{
	for (int i = 0; i<SI_Y; i++)
	{
		for (int j = 0; j<SI_X; j++)
		{
			mvaddch(i, j, map[i][j]);
		}
	}
}

int main()
{
	srand((unsigned)time(0));
	
	initscr();
	curs_set(0);
	noecho();
	resize_term(22, 82);
	
	initMap();
	buildMap();
	printMap();
	
	getch();
	endwin();
	return 0;
}
