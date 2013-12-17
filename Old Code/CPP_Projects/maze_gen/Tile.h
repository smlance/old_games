#ifndef TILEH
#define TILEH

class Tile
{
	private:
	SDL_Rect box;
	SDL_Surface *sprite;
	int type, visibility;
	Map *my_map;
	
	public:
	Tile(int, int, int, Map*);
	~Tile();
	void applyToMap();
	void loadSprite();
	void loadInitSprite();
	void applyVis();
	void loadObscuredSprite();
	
	friend class Map;
	friend class Player;
	
};

#endif //TILEH
