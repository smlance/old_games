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

class MapData
{
	private:
	m_array map;
	
	public:
	friend class Map;
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
	int dig_x, dig_y, rooms_curr, rooms_des, room_size, halls_des, halls_curr;
	rooms_curr = 0;
	rooms_des = 20;
	halls_curr = 0;
	halls_des = 25;
	room_size = rand() % 3 + 3;
	/*generate rooms*/
	while (rooms_curr < rooms_des)
	{
		dig_x = rand() % sx+1;
		dig_y = rand() % sy+1;
		if (map[dig_y][dig_x] != 46)
		{
			int rsx = rand() % room_size + 5;
			int rsy = rand() % room_size + 2;
			if (dig_y + rsy >= sy-2 || dig_x + rsx >= sx-2)
			{
				
			}
			else
			{
				bool has_neighbor = FALSE;
				for (int i = dig_y; i<dig_y+rsy; i++){
				for (int j = dig_x; j<dig_x+rsx; j++){
					if (checkNeighbor(i, j))
					has_neighbor = TRUE;
				}}
				if (!has_neighbor)
				{
				for (int i = dig_y; i<dig_y+rsy; i++){
				for (int j = dig_x; j<dig_x+rsx; j++){
					map[i][j] = 46;
				}}
				rooms_curr++;
				}
			}
		}
	}
	/*generate halls*/
	while (halls_curr < halls_des)
	{
		dig_x = rand() % sx+1;
		dig_y = rand() % sy+1;
		if (dig_y >= sy) dig_y -= 2;
		if (dig_x >= sx) dig_x -= 2;
		
		if (map[dig_y][dig_x] == 46)
		{
			int dir = rand() % 4;
			if (dir == 0) //up
			{
				if (map[dig_y-1][dig_x] == 46)
				{}
				else
				{
				for (int i = dig_y-1; i>0; i--){
					if (map[i][dig_x] == 46 && map[i+1][dig_x-1] != 46 && map[i+1][dig_x+1] != 46){
					/*we've struck gold; make a hall*/
						for (int j = dig_y-1; j>=i; j--)
							{
								map[j][dig_x] = 46;
							}
							//mvaddstr(0, 0, "Hall has been dug UP");
							//getch();
							halls_curr++;
							break;
						}
						//mvaddstr(0, 0, "test0");
							//getch();
					}
							//				mvaddstr(0, 0, "test1");
							//getch();
				}
			}
			else if (dir == 1) //down
			{
				if (map[dig_y+1][dig_x] == 46)
				{}
				else
				{
				for (int i = dig_y+1; i<sy-1; i++){
					if (map[i][dig_x] == 46 && map[i-1][dig_x-1] != 46 && map[i-1][dig_x+1] != 46){
						for (int j = dig_y+1; j<=i; j++)
							{
								map[j][dig_x] = 46;
							}
							//mvaddstr(0, 0, "Hall has been dug DOWN");
							//getch();
							halls_curr++;
							break;
						}
					}
				}
			}
			else if (dir == 2) //left
			{
				if (map[dig_y][dig_x-1] == 46)
				{}
				else
				{
				for (int i = dig_x-1; i>0; i--){
					if (map[dig_y][i] == 46 && map[dig_y-1][i+1] != 46 && map[dig_y+1][i+1] != 46){
					/*we've struck gold; make a hall*/
						for (int j = dig_x-1; j>=i; j--)
							{
								map[dig_y][j] = 46;
							}
							//mvaddstr(0, 0, "Hall has been dug UP");
							//getch();
							halls_curr++;
							break;
						}
						//mvaddstr(0, 0, "test0");
							//getch();
					}
							//				mvaddstr(0, 0, "test1");
							//getch();
				}
			}
			else if (dir == 3) //right
			{
				if (map[dig_y][dig_x+1] == 46)
				{}
				else
				{
				for (int i = dig_x+1; i<sx-1; i++){
					if (map[dig_y][i] == 46 && map[dig_y-1][i-1] != 46 && map[dig_y+1][i-1] != 46){
					/*we've struck gold; make a hall*/
						for (int j = dig_x+1; j<=i; j++)
							{
								map[dig_y][j] = 46;
							}
							//mvaddstr(0, 0, "Hall has been dug UP");
							//getch();
							halls_curr++;
							break;
						}
						//mvaddstr(0, 0, "test0");
							//getch();
					}
							//				mvaddstr(0, 0, "test1");
							//getch();
				}
			}
		//	mvaddstr(0, 0, "End of dirs reached");
		//	getch();
			/*if (dir == 0) //up
			{
				if (map[dig_y-1][dig_x] == 46)
				{break;}
				else
				{
				for (int i = dig_y-1; i>0; i--){
					if (map[i][dig_x] == 46){
						for (int j = dig_y-1; j>=i; j--)
							{
								map[j][dig_x] = 46;
							}
							break;
						}
					}
				}
			}
			if (dir == 0) //up
			{
				if (map[dig_y-1][dig_x] == 46)
				{break;}
				else
				{
				for (int i = dig_y-1; i>0; i--){
					if (map[i][dig_x] == 46){
						for (int j = dig_y-1; j>=i; j--)
							{
								map[j][dig_x] = 46;
							}
							break;
						}
					}
				}
			}*/
		}
	}
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
