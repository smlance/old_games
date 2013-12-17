#ifndef ENTITY_H
#define ENTITY_H

class Entity {
	protected:
	int 	width, height, top_x, top_y;	/* dimensions */
	float	move_speed;
	int 	max_time, acc_time;				/* max time for update, accumulated time */
	int 	ID;								/* dunno whether this should be used; could be helpful */
	float 	vel_x, vel_y, terminal_vel;
	int		top_left, top_right, bot_left, bot_right; // pixel coordinates
	bool 	key_pressed;
	bool 	on_ground;
	int		state; 							// for animations
	int		state_ID;						// this is really for animations!
	Area 	*my_area;
	
	struct collision_data {
		Entity * 	target;
		bool		solid; // not really necessary if target is not null
	};
	
	public:
	Entity(int width_in, int height_in, int top_x_in, int top_y_in);
	~Entity();
	
	virtual int 	update_state(int time_elapsed_in); 	/* pass in time elapsed, see if anything needs to be done; change return type from void to something else? */
	virtual void 	initialize(Area *my_area_in); //XXX XXX XXX XXX AHHHHH! (make it for other things too)
	virtual bool 	get_solid();	// put this in the block class, not here?
	
	collision_data check_collision_down();
	collision_data check_collision_up();
	collision_data check_collision_x();
	
	void handle_collision_up();
	void handle_collision_down();
	void handle_collision_x();
	
	int get_ID();
	int get_width();
	int get_height();
	int get_top_x();
	int get_top_y();
	int get_vel_x();
	int get_vel_y();
	int get_state_ID(); // why not just have a container for entity_data? ;}
};



class Player : public Entity {
	private:
	
	public:
	Player(int width_in, int height_in, int top_x_in, int top_y_in);
	~Player();
	
	int 	update_state(int time_elapsed_in);
	void 	move();
	void 	handle_input(SDL_Event Event);
};



class Block : public Entity {
	private:
	int Type; // just use ID, you fool! prefix for different types (e.g. blocks get '100' prefixed)
	bool solid; // make this inherent in type or something? XXX
	
	public:
	Block(int width_in, int height_in, int top_x_in, int top_y_in, int Type_in, bool Solid_in); // TFR XXX EXACTLY, SO JUST DO IT IN AN INITIALIZE FCN INSTEAD OF THE FUCKING CTOR. MAKE IT VIRTUAL OR SOME SHIT.
	~Block();
	
	bool get_solid();
};



class Area {
	private:
	
	struct struct_area_data { // this is gold. ;}
		Block *BG;
		std::vector < std::vector<int> > 	block_map; // map of blocks in area
		std::vector< std::vector<Block*> > 	block_list;
	} area_data; // contains all data for area.
	
	int vec_size_x, vec_size_y;
	
	public:
	Area(int VS_x_in, int VS_y_in, bool edit = false);
	~Area();
	
	void 		initialize(Block *BG_in/*, block data (set it somehow from here*/);
	Block *		get_block(int i, int j);
	Block *		get_BG();
	void		set_block(int i, int j, int ID, bool solid);
	int 		get_vec_y();
	int 		get_vec_x(); //getters for sizes of vector
	//struct_area_data *	get_AD();
};

#endif
