#ifndef ENT_H
#define ENT_H

class Entity
{
protected:
	/*
	 * x, y 	-- coords
	 * id, type -- specific and general identifiers
	 * times	-- accumulated and max (for updates)
	 */
	int 	x, y, id, type, time_a, time_m;
	bool 	solid, in_room, visible;

public:
	Entity(int, int, int);
	~Entity();
	virtual void update(int);
	virtual void move(int);
	virtual void randSpawn();
	virtual void init(bool, bool);
	
	int		hp, atk, def;
	// getters
	int 	getID();
	int 	getX();
	int 	getY();
	/*int		getHP();
	int		getAtk();
	int		getDef();*/
	bool	getSolid();
	bool	getInRoom();
	//bool	getVisible();
	bool	inPlayerLOS();
	
	void	moveEnt(int, int);
	// setters
	virtual void 	setID(int);
	void			setSolid(bool);
	void			setInRoom(bool);
	void			setStatsById(int, int, int);
	/* TODO: make a struct or a class that can grab the stats just by looking at the ID, so you avoid this function... or make g/setting easier */
	//void			setVisible(bool);
};

class Player : public Entity
{
private:

public:
	Player(int, int, int);
	~Player();
	void update(int);
	void move(int);
	void randSpawn();
	void checkHit();
};

// linked list for tiles
struct Tile_Link
{
	Entity * 	entity;
	Tile_Link * next_link;
};

class Tile : public Entity
{
private:
	svector <Entity *> entity_list;
	int projected_ent_occupants;

public:
	Tile(int, int, int);
	~Tile();
	void 	init(bool, bool);
	void 	setSolidById();
	void 	setID(int);
	void 	addEntity(Entity *);
	bool 	hasDoor();
	void 	incrementPEO();
	void	zeroPEO();
	int		getPEO();
	Entity *getEnt(int);
	bool 	hasEnt();
	void 	removeEnt(int);
	void	freeEnt();
	int 	getEntListSize();
	void	setVisible(bool);
	bool	getVisible();
	// bool has_items(); (?) (for player checking to pick stuff up)
};

#endif // ENT_H
