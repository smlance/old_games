#ifndef MAIN_H
#define MAIN_H

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include <cmath>
#include <fstream>
//#include <unistd.h> //for display purposes only

#define wall 35
#define ground 32
#define door 45
#define sy 25
#define sx 25

class Map;
class Player;

struct Tile
{
	int type;
	bool in_room;
};

typedef Tile MapArray[sy][sx];

class Map
{
	private:
	MapArray map;
	
	public:
	Map();
	~Map();
	void initMap();
	void buildMap();
	void printMap();
	void addRand();
	void addRooms();
	void addDoors(int, int);
	void removeDoubleDoors(); //XXX optimize XXX
	void removeDeadEnds();
	bool deadEndsExist();
	bool toFile();
	
	friend class Player;
	
};

class Player
{
	private:
	int pos_x, pos_y, key;
	Map *this_map;
	
	public:
	Player();
	~Player();
	void getAndHandleEvent();
	
	friend class Map;
};

#endif
