#ifndef TILEH
#define TILEH

class Tile
{
	private:
	SDL_Rect 	box;
	int 		type;
	
	public:
	Tile(int x, int y, int tile_type);
	void show();
	int get_type();
	SDL_Rect get_box();
	
};

#endif
