#ifndef PLAYER_H
#define PLAYER_H

#include "misc.h"

class Player{
	private:
	int pos_x, pos_y, key, dir, map_x, map_y, health, max_health, lvl, str;
	//StatusBar* stat_bar;
	
	public:
	Player();
	~Player();
	int processInput();
	int returnxMap();
	int returnyMap();
	void move(int);
	void updatePlayerAndWorld();
	/*bool isSpotTaken();*/
	/* updatePlayerAndWorld: prints player, makes any
	updates to world (i.e. prints item or map tile)*/
	//Map& getMap();
	
	/*friend class Map;
	friend class Object;
	friend class StatusBar;*/
	
};

#endif
