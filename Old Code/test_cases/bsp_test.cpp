#include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define sx 80
#define sy 20

using namespace std;

class Cell;

typedef int m_array [sy][sx];

class MapData;
class Player;

class Cell
{
private:
int visibility, tile;
/*visibility: 0=hidden, 1=visible, 2=active*/
public:
friend class Map;
};

void clearMap()
{
	for (int i = 0; i<sy; i++)
	{ for (int j = 0; j<sx; j++)
	{ mvaddch(i, j, 127 | A_ALTCHARSET);}}
}

class Map
{
	private:
	MapData *data;
	m_array *map_data;
	
	public:
	friend class MapData;
	Map();
	void printMap();
	void setData();
	int getSpace(int, int);
};

class BSPRoom
{
	private:
	int size_x, size_y, start_x, start_y;
	static int max_itr;
	BSPRoom *left, *right, *parent;
	
	public:
	friend class MapData;
	BSPRoom(BSPRoom*, int);
};

class MapData
{
	private:
	m_array map;
	
	public:
	friend class Map;
	friend class BSPRoom;
	MapData();
	void initMap();
	void fillMap();
	void printMap();
	bool checkNeighbor(int, int);
	
};

class Player
{
	private:
	int pos_x, pos_y, key, rad;
	Map *map;
	
	public:
	Player();
	void placePlayer();
	void printInLOS(float, float);
	void getLOS(bool);
};

/*---------------------------------------------------*/

BSPRoom::BSPRoom(BSPRoom *par, int level)
{
	parent = par;
	
}

Player::Player()
{
	map = new Map;
	key = 64;
	rad = 10;
	
	
	placePlayer();
	getLOS(TRUE);
	mvaddch(pos_y, pos_x, key);
	bool yes = TRUE;
	while (yes)
	{
		getLOS(TRUE);
		mvaddch(pos_y, pos_x, key);
		int dir = getch();
		if (dir == 'a')
		{
			if (map->getSpace(pos_y, pos_x-1) != 35)
			{getLOS(FALSE);
				pos_x--;
			}
		}
		else if (dir == 'd')
		{
			if (map->getSpace(pos_y, pos_x+1) != 35)
			{getLOS(FALSE);
				pos_x++;
			}
		}
		else if (dir == 'w')
		{
			if (map->getSpace(pos_y-1, pos_x) != 35)
			{getLOS(FALSE);
				pos_y--;
			}
		}
		else if (dir == 's')
		{
			if (map->getSpace(pos_y+1, pos_x) != 35)
			{getLOS(FALSE);
				pos_y++;
			}
		}
		else if (dir == 27)
		{
			yes = FALSE;
		}
	}
}

void Player::getLOS(bool clear)
{
	float x, y;
	int i;
	for (i = 0; i < 360; i++)
	{
		x = cos((float)i*0.01745f);
		y = sin((float)i*0.01745f);
		if (!clear)
		{
			attron(COLOR_PAIR(1));
			printInLOS(x, y);
			attroff(COLOR_PAIR(1));
		}
		else
		{
			attron(A_BOLD);
			printInLOS(x, y);
			attroff(A_BOLD);
		};
	}
}

void Player::printInLOS(float x, float y)
{
	int i;
	float ox, oy;
	ox = (float)pos_x+0.5f;
	oy = (float)pos_y+0.5f;
	for (i=0; i<rad; i++)
	{
		mvaddch((int)oy, (int)ox, map->getSpace((int)oy, (int)ox));
		if (map->getSpace((int)oy, (int)ox) == 35)
			return;
		ox+=x;
		oy+=y;
	}
}

void Player::placePlayer()
{
	int rand_x = rand() % sx;
	int rand_y = rand() % sy;
	
	if (map->getSpace(rand_y, rand_x) != 35)
	{
		pos_x = rand_x;
		pos_y = rand_y;
		mvaddch(pos_y, pos_x, key);
	}
	else
	{
		placePlayer();
	}
}

MapData::MapData()
{
	initMap();
	fillMap();
}
void MapData::printMap()
{
		for (int i = 0; i<sy; i++)
	{
		for (int j = 0; j<sx; j++)
		{
			cout << map[i][j];
		}
	}
}
void MapData::initMap()
{
	for (int i = 0; i<sy; i++)
	{
		for (int j = 0; j<sx; j++)
		{
			map[i][j] = 35;
		}
	}
}

bool MapData::checkNeighbor(int y, int x)
{
	bool b = FALSE;
	for (int j = -1; j<=1; j++)
	{
		for (int k = -1; k<=1; k++)
		{
			if (map[j+y][k+x] == 46) b = TRUE;
		}
	}
	return b;
}
void MapData::fillMap()
{
}

	Map::Map()
	{
		setData();
		//printMap();
	}
	void Map::printMap()
	{
		for (int i = 0; i<sy; i++)
		{
			for (int j = 0; j<sx; j++)
			{
				mvaddch(i, j, (*map_data)[i][j]);
			}
		}
	}
	void Map::setData()
	{
		data = new MapData;
		map_data = &(data->map);
	}
	int Map::getSpace(int y, int x)
	{
		return (*map_data)[y][x];
	}


int main()
{
	srand((unsigned)time(0));
	initscr();
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	
	/*MapData test;
	test.printMap();*/
	
	Player player;
	endwin();
	
	return 0;
}
