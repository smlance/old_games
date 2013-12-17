#ifndef MAP_H
#define MAP_H

class Map
{
	private:
		svector < svector<Tile *> > map;

	public:
		Map();
		~Map();
		void init();
		void build();
		// creates the maze
		void add_maze();
		void add_rooms();
		// fills in bits of the maze at random
		void add_rand();
		void add_doors();
		void remove_double_doors();
		void remove_dead_ends();
		bool dead_ends_exist();
		void add_exit();

		Tile *	get_tile(int, int);
		int 	get_height();
		int 	get_width();
};

#endif // MAP_H
