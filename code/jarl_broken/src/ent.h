#ifndef ENT_H
#define ENT_H

struct info
		{
			/*
			 * x, y 	-- coords
			 * id, type -- specific and general identifiers
			 * times	-- accumulated and max (for updates)
			 */
			int 	x, y, id, type, time_a, time_m;
			bool 	solid, in_room;
		};

class Entity
{
	protected:
		info ent_info;
		
	public:
	
		Entity(info);
		Entity();
		~Entity() { };
		virtual void update(int);
		virtual void makeChanges();
		virtual void move(int);
		virtual void randSpawn();
		virtual void init(info);
};

class Player : public Entity
{
	private:

	public:
		Player();
		~Player();
		void update(int);
		void move(int);
		void rand_spawn();
		void check_hit();
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

	public:
		Tile();
		~Tile();
		void 	init(info);
		void 	set_solid_by_id();
		void 	set_id(int);
		void 	add_entity(Entity *);
		bool 	has_door();
		Entity *get_ent(int);
		void 	remove_ent(int);
		int 	get_ent_list_size();
		// bool has_items(); (?) (for player checking to pick stuff up)
};
#endif // ENT_H
