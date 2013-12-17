#ifndef GAME_H
#define GAME_H

class Game
{
private:
	int 				state;
	svector <Entity *> 	ent_list;
	Map *				area;

public:
	Game();
	~Game();
	void init();
	void update(int);
	// getters
	int getState();
	// setters
	void setState(int);

	Map *	getArea();
	int 	getEntListSize();
	Entity *getEnt(int);

	void 	initRandEnts();
	void 	checkPlayerMove(Key);
	int		numWallsUDLR(int, int); 	// udlr = up, down, left, right (cross)
	int		numGroundsUDLR(int, int);
	bool	numUDLRAdjInRoom(int, int); // udlr-adjacent to a tile in a room
	int		numWallsAll(int, int); 	// all = counting all 8 around
	void 	generatePlayerLOS();

};

#endif // GAME_H
