#ifndef PLAYERH
#define PLAYERH

class Player
{
	private:
	int pos_x, pos_y, dir/*, map_x, map_y*/;
	Map *map_curr; /*TEMPORARY*/
	SDL_Surface *sprite;
	
	public:
	Player();
	~Player();
	void handleInput(SDL_Event &);
	void display();
	
	friend class Map;
	friend class Tile;
};

#endif //PLAYERH
