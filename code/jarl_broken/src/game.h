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
		void update(int);
		// Getters
		int getState() { return state; };
		Map *getArea() { return area; };
		// Setters
		// change int to enum??? XXX
		void setState(int s) { state = s; };

		Map *	get_area();
		int 	get_ent_list_size();
		Entity *get_ent(int);

		
		void init_rand_ents();
		void check_player_move(Key);
		// udlr = up, down, left, right (cross)
		int		num_walls_udlr(int, int);
		int		num_grounds_udlr(int, int);
		// udlr-adjacent to a tile in a room
		bool	udlr_adj_in_room(int, int);
		// all = counting all 8 around
		int		num_walls_all(int, int);
};

#endif // GAME_H
