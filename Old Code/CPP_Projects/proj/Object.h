#ifndef OBJECTH
#define OBJECTH

class Object
{
	protected:
	int pos_x, pos_y, map_x, map_y;
	bool in_inv;
	Object *list;
	Map *my_map;
	Tile *my_tile;
	SDL_Surface *sprite;
	SDL_Rect box;
	
	public:
	Object(int, int, int, int, Map*, Tile*);
	~Object();
	void loadSprite();
	void applyToMap(); /*display*/
	void doFunc();
	
};

class Sword: public Object
{
	private:
	int atk;
	
	public:
	using Object::loadSprite;
	using Object::doFunc;
	Sword(int, int, int, int, Map*, Tile*);
	void loadSprite();
	void doFunc();
};

class Potion: public Object
{
	private:
	int heal_amt;
	
	public:
	using Object::loadSprite;
	using Object::doFunc;
	Potion(int, int, int, int, Map*, Tile*);
	void loadSprite();
	void doFunc();
};

class Scroll: public Object
{
	private:
	std::string msg;
	
	public:
	using Object::loadSprite;
	using Object::doFunc;
	Scroll(int, int, int, int, Map*, Tile*);
	void loadSprite();
	void doFunc();
	
};

#endif //OBJECTH
