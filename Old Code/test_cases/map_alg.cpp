#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <sstream>

#define sy 20
#define sx 80
#define wall 35
#define ground 46

std::string intToStr(int integer)
{
	std::string s;
	std::stringstream out;
	out << integer;
	s = out.str();
	return s;
}

class Room;
class Hall;
class Map;
struct Cell;
struct Coordinates;

struct Coordinates
{
	int x;
	int y;
	bool up, down, left, right;
};

struct Cell
{
	Map *myMap;
	Room *myRoom;
	Hall *myHall;
	std::string belong_to;
	int disp;
	bool active;
};

class Hall
{
	private:
	int hall_len;
	Coordinates coords;
	Map* my_screen;
	bool connected;
	
	public:
	Hall(Coordinates, int, Map*);
	void buildHall();
	friend class Map;
	friend class Room;
};

class Map
{
	private:
	int rooms_curr, rooms_des, halls_curr, halls_des;
	Cell map[sy][sx];
	
	public:
	Map();
	void buildMap(int);
	void initMap();
	bool checkForGround(int, int);
	void printMap();
	void makeInitialRoom();
	void connectRooms();
	Coordinates chooseRandEdge();
	void chooseFeature(Coordinates);
	void genHall(Coordinates, int);
	int checkHall(Coordinates);
	friend class Room;
	friend class Hall;
};

class Room
{
	private:
	int size_x, size_y, start_x, start_y;
	Map *my_screen;
	bool connected;
	
	public:
	Room(int, int, int, int, Map*);
	void buildRoom();
	friend class Map;
	friend class Hall;
};

Map::Map()
{
	rooms_curr = 0;
	halls_curr = 0;
	rooms_des = rand() % 3 + 5;
	halls_des = 5;
	
	initMap();
	buildMap(1);
	printMap();
}

void Map::initMap()
{
	for (int i = 0; i < sy; i++) {
		for (int j = 0; j < sx; j++) {
			(map[i][j]).disp = wall;
			(map[i][j]).active = FALSE;
		}
	}
}

bool Map::checkForGround(int y, int x)
{
	bool b = FALSE;
	for (int j = -2; j<=2; j++)
	{
		for (int k = -2; k<=2; k++)
		{
			if (map[j+y][k+x].disp == ground) b = TRUE;
		}
	}
	return b;
}

void Map::makeInitialRoom()
{
	while (rooms_curr == 0)
	{
		int dig_x, dig_y, room_size;
		dig_x = rand() % sx + 1;
		dig_y = rand() % sy + 1;
		room_size = rand() % 5 + 1;
		/*select random dig locations and room size*/
		
		/*if position isn't taken...*/
		int rsx = rand() % room_size + 5;
		int rsy = rand() % room_size + 2;
		/*generate room sizes*/
		
		if (dig_y + rsy >= sy-2 || dig_x + rsx >= sx-2)
		{/*if the room will exceed the map size, restart*/}
		else /*otherwise... check to see if has_neighbor*/
		{
			new Room(rsx, rsy, dig_x, dig_y, this);
			rooms_curr++; //tell screen that we have one more room
		}
		}
}

void Map::buildMap(int feat)
{
	int f = 0;
	
	makeInitialRoom();
	while (f < feat) {
		chooseFeature(chooseRandEdge());
		f++;
		}
}

int Map::checkHall(Coordinates coords)
{
	int hall_len;
	
	if (coords.up) {
		hall_len = rand() % (sy/3) + 3;
		if (coords.y - hall_len < 1)
		{
			return checkHall(coords);
		};
	}
	else if (coords.down) {
		hall_len = rand() % (sy/3) + 3;
		if (coords.y + hall_len > (sy-2))
		{
			return checkHall(coords);
		};
	}
	else if (coords.left) {
		hall_len = rand() % (sx/10) + 3;
		mvaddstr(0, 0, "left");
		getch();
		if (coords.x - hall_len < 1)
		{
			return checkHall(coords);
		};
	}
	else if (coords.right) {
		hall_len = rand() % (sx/10) + 3;
		mvaddstr(0, 0, "right");
		getch();
		if (coords.x + hall_len > (sx-2))
		{
			return checkHall(coords);
		};
	};
	
	bool hit = FALSE;
	
	mvaddstr(0, 20, "Checking hall...");
	//getch();
	
	if (coords.up)
	{
	mvaddstr(0, 0, "run through map");
			//getch();
		for (int i = -1; i<=1; i++)
		{
			for (int j = coords.y; j > coords.y - hall_len; j--)
			{
				if (map[j][coords.x+i].disp == ground)
				{
					hit = TRUE;
					//break;
				}
			}
		}
	}
	
	else if (coords.down)
	{
		for (int i = -1; i<=1; i++)
		{
			for (int j = coords.y; j < coords.y + hall_len; j++)
			{
				if (map[j][coords.x+i].disp == ground)
				{
					hit = TRUE;
					//break;
				}
			}
		}
	}
	
	else if (coords.left)
	{
		for (int i = -1; i<=1; i++)
		{
			for (int j = coords.x; j > coords.x - hall_len; j--)
			{
				if (map[coords.y+i][j-1].disp == ground)
				{
					hit = TRUE;
					//break;
				}
			}
		}
	}
	
	else if (coords.right)
	{
		for (int i = -1; i<=1; i++)
		{
			for (int j = coords.x; j < coords.x + hall_len; j++)
			{
				if (map[coords.y+i][j+1].disp == ground)
				{
					hit = TRUE;
					//break;
				}
			}
		}
	}
	
	if (hit)
	{
		return checkHall(coords);
	}
	else
	{
		return hall_len;
	};
}

void Map::genHall(Coordinates coords, int hall_len)
{
	mvaddstr(0, 20, "About to generate hall...");
	getch();
	new Hall(coords, hall_len, this);
}

Hall::Hall(Coordinates cords, int hal_len, Map *myscr)
{
	my_screen = myscr;
	coords = cords;
	hall_len = hal_len;
	mvaddstr(0, 0, "About to build hall");
	getch();
	
	buildHall();
}

void Hall::buildHall()
{
	mvaddstr(0, 20, "Building hall...");
	getch();
	if (coords.up)
	{
		for (int i = 0; i<hall_len; i++)
		{
			(my_screen->map[coords.y-i][coords.x]).disp = ground;
			(my_screen->map[coords.y-i][coords.x]).myHall = this;
			(my_screen->map[coords.y-i][coords.x]).belong_to = "hall";
		}
	}
	
	else if (coords.down)
	{
		for (int i = 0; i<hall_len; i++)
		{
			(my_screen->map[coords.y+i][coords.x]).disp = ground;
			(my_screen->map[coords.y+i][coords.x]).myHall = this;
			(my_screen->map[coords.y+i][coords.x]).belong_to = "hall";
		}
	}
	
	else if (coords.left)
	{
		for (int i = 0; i<hall_len; i++)
		{
			(my_screen->map[coords.y][coords.x-i]).disp = ground;
			(my_screen->map[coords.y][coords.x-i]).myHall = this;
			(my_screen->map[coords.y][coords.x-i]).belong_to = "hall";
		}
	}
	
	else if (coords.right)
	{
		for (int i = 0; i<hall_len; i++)
		{
			(my_screen->map[coords.y][coords.x+i]).disp = ground;
			(my_screen->map[coords.y][coords.x+i]).myHall = this;
			(my_screen->map[coords.y][coords.x+i]).belong_to = "hall";
		}
	};
}

/*void Map::chooseDir(Coordinates coords)
{
	int n;
	if (coords.up)
}*/

void Map::chooseFeature(Coordinates coords)
{
		
		/*before generating stuff, choose a direction and make sure stuff can be made (make another function for checking for different features?*/
		//if (map[coords.y][coords.x].belong_to == "room") {
			genHall(coords, checkHall(coords));
		//}
}

void Map::printMap()
{
	for (int i = 0; i < sy; i++) {
		for (int j = 0; j < sx; j++) {
			mvaddch(i, j, map[i][j].disp);
		}
	}
}

Coordinates Map::chooseRandEdge()
{
	int dig_x, dig_y;
	dig_x = rand() % (sx-1) + 1;
	dig_y = rand() % (sy-1) + 1;
	/*this shouldn't seg-fault because rooms can't be made on the edge of the screen*/
	if (map[dig_y][dig_x].disp == wall)
	{
		bool adj = FALSE;
		
		for (int i = -1; i<=1; i++)
		{
			for(int j = -1; j<=1; j++)
			{
				if (map[dig_y+i][dig_x+j].disp == ground && ((i==-1&&j==0)||(i==1&&j==0)||(i==0&&j==-1)||(i==0&&j==1)))
				{
					adj = TRUE;
				}
			}
		}
		if (adj) {
			Coordinates coords;
			if (map[dig_y-1][dig_x].disp == ground){
				coords.down = TRUE;};
			if (map[dig_y+1][dig_x].disp == ground){
				coords.up = TRUE;};
			if (map[dig_y][dig_x-1].disp == ground){
				mvaddstr(0, 0, "right");
				getch();
				coords.right = TRUE;};
			if (map[dig_y][dig_x+1].disp == ground){
							mvaddstr(0, 0, "rleft");
				getch();
				coords.left = TRUE;};
			//if ((coords.up && coords.left) || (coords.up && coords.right) || (coords.down && coords.left) || (coords.down && coords.right))
			//{ return chooseRandEdge(); }
			//else
			//{
			coords.x = dig_x;
			coords.y = dig_y;
			mvaddch(dig_y, dig_x, 64);
			getch();
			return coords;
			//}
			}
		 else {
			return chooseRandEdge();
		};
	} else {
		return chooseRandEdge();
	};
}

Room::Room(int six, int siy, int stx, int sty, Map *mysc)
{
	start_x = stx;
	start_y = sty;
	size_x = six;
	size_y = siy;
	my_screen = mysc;
	connected = FALSE;
	
	buildRoom();
}

void Room::buildRoom()
{
	for (int i = start_y; i<(start_y+size_y); i++) {
		for (int j = start_x; j<(start_x+size_x); j++) {
			(my_screen->map[i][j]).myRoom = this;
			(my_screen->map[i][j]).disp = ground;
			(my_screen->map[i][j]).belong_to = "room";
		}
	}
}

int main()
{
	srand((unsigned)time(0));
	initscr();
	curs_set(0);
	noecho();
	
	Map testmap;
	getch();
	endwin();
	
	return 0;
}
