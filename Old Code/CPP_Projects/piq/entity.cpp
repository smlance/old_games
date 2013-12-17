#include "main.h"

//XXX differentiate moving entities from non-moving ones (organisms vs blocks)

Entity::Entity(/*Display *Disp_in, */int width_in, int height_in, int top_x_in, int top_y_in) {
	width = width_in; height = height_in; top_x = top_x_in; top_y = top_y_in;
	ID = 0;
	move_speed = 1.0f;
	terminal_vel = 5.0f;
	top_right = top_x + width; 	// ?
	top_left = top_x;			// ?
	bot_left = top_y + height;	// ?
	bot_right = 0; 				// ?
	state = 0;
	state_ID = 0;
	
	max_time = 500;		/* arbitrary, for now */
	acc_time = 0;		/* time that has lappsed */
}

int Entity::get_ID() {
	return ID;
}

int Entity::get_width() {
	return width;
}

int Entity::get_height() {
	return height;
}

int Entity::get_top_x() {
	return top_x;
}

int Entity::get_top_y() {
	return top_y;
}

int Entity::get_vel_x() {
	return vel_x;
}

int Entity::get_vel_y() {
	return vel_y;
}

bool Entity::get_solid() {
	//return Solid;
}

int Entity::get_state_ID() {
	return state_ID;
}

int Entity::update_state(int time_elapsed_in) {
	acc_time += time_elapsed_in;
	
	if (acc_time >= max_time) {
		acc_time = 0;
		
		return 1;
	}
	
	return 0;
}



Entity::collision_data Entity::check_collision_down() {	// vertical collision detection
	
	int adjusted_x = ((int)top_x - ((int)top_x % 8)) / 8;
	int adjusted_y = ((int)top_y - ((int)top_y % 8)) / 8;
	
	if (adjusted_y == 0) adjusted_y++; // ?
	if (adjusted_x == 0) adjusted_x++; // ?
	// adjusted_y + 3?
	for (int i = adjusted_y; i < adjusted_y + 2; i++) {	// scan area.	why y and then x? (trying x and then y doesn't work. o_o)
		for (int j = adjusted_x - 1; j < adjusted_x + 3; j++) { // note: adjusted_ *+3* is used, because the char is larger than the tiles... needs to get to adjusted_ + 2 before collision detected ;}
		
			if ( (my_area->get_block(i, j))->get_solid() ) { 						// if a block in the area is solid...
				Entity *temp_en = my_area->get_block(i, j);
				
				if ( (top_y + height + vel_y >= temp_en->get_top_y() && 				// check that we are colliding with block
				top_y + vel_y <= temp_en->get_top_y() + temp_en->get_height()) && 	// is this necessary?
				(top_x + width > temp_en->get_top_x() &&  							// check that we are horizontally in range
				top_x < temp_en->get_top_x() + temp_en->get_width()) ) { 			// then this block is colliding vertically with us!
				
					collision_data cd_true;
					cd_true.target = temp_en; 				// record this collided block
					cd_true.solid = temp_en->get_solid(); 	// i don't even know why i'm doing this >_>
					
					//std::cout << top_y + height << "\t" << temp_en->get_top_y() << std::endl;
					
					return cd_true;
					
				}
			}
		}
	}
	// if collision tests failed, return a "null" block
	collision_data cd_false;
	cd_false.target = NULL;
	cd_false.solid = false;
	
	return cd_false;
}

Entity::collision_data Entity::check_collision_up() {

	int adjusted_x = ((int)top_x - ((int)top_x % 8)) / 8;
	int adjusted_y = ((int)top_y - ((int)top_y % 8)) / 8;
	
	if (adjusted_y == 0) adjusted_y++;
	if (adjusted_x == 0) adjusted_x++;
	
	for (int i = adjusted_y - 1; i < adjusted_y + 3; i++) {	// scan area.	why y and then x? (trying x and then y doesn't work. o_o)
		for (int j = adjusted_x - 1; j < adjusted_x + 3; j++) { // note: adjusted_ *+3* is used, because the char is larger than the tiles... needs to get to adjusted_ + 2 before collision detected ;}
		
			if ( (my_area->get_block(i, j))->get_solid() ) { 						// if a block in the area is solid...
				Entity *temp_en = my_area->get_block(i, j);
				
				if ( (top_y + vel_y <= temp_en->get_top_y() + temp_en->get_height() &&
				top_y + vel_y >= temp_en->get_top_y()) &&
				(top_x + width > temp_en->get_top_x() && // check that we are horizontally in range
				top_x < temp_en->get_top_x() + temp_en->get_width())
				) { 			// then this block is colliding vertically with us!
				
					collision_data cd_true;
					cd_true.target = temp_en; 				// record this collided block
					cd_true.solid = temp_en->get_solid(); 	
					//std::cout << "x" << std::endl;
					return cd_true;
					
				}
			}
		}
	}
	// if collision tests failed, return a "null" block
	collision_data cd_false;
	cd_false.target = NULL;
	cd_false.solid = false;
	
	return cd_false;
}

Entity::collision_data Entity::check_collision_x() {	// horizontal collision detection

	int adjusted_x = ((int)top_x - ((int)top_x % 8)) / 8;
	int adjusted_y = ((int)top_y - ((int)top_y % 8)) / 8;
	
	if (adjusted_y <= 0) adjusted_y = 1;
	if (adjusted_x <= 0) adjusted_x = 1;

	for (int i = adjusted_y - 1; i < adjusted_y + 2; i++) {	// scan area
		for (int j = adjusted_x - 1; j < adjusted_x + 2; j++) {
		
			if ( (my_area->get_block(i, j))->get_solid() ) {					// if a block in the area is solid...
				Entity *temp_en = my_area->get_block(i, j);
			
				if ( (top_x + width  > temp_en->get_top_x() && 			// if we are colliding horizontally
				top_x  < temp_en->get_top_x() + temp_en->get_width()) && //
				(top_y + height > temp_en->get_top_y() && 						// and we are vertically in range of the block
				top_y < temp_en->get_top_y() + temp_en->get_height())
				) {
					collision_data cd_true = {temp_en, temp_en->get_solid()};
					//std::cout << 'x' << std::endl;
					return cd_true;
				}
			}
		}
	}
	
	collision_data cd_false = {NULL, false};
	return cd_false;
}



void Entity::initialize(Area *my_area_in) {
	my_area = my_area_in;
}



Entity::~Entity() {
	if (my_area)
		my_area = NULL;

	//std::cout << "Entity deleted successfully!" << std::endl;
}



Player::Player(int width_in, int height_in, int top_x_in, int top_y_in) : Entity(width_in, height_in, top_x_in, top_y_in) {
	ID = 300;
	vel_x = 0; vel_y = 0;
	on_ground = false;
}



void Entity::handle_collision_up() {
	collision_data temp_cd = check_collision_up();
	
	if (temp_cd.solid/* && !on_ground*/) {
		//top_y -= 1; // XXX
		top_y -= 1*vel_y;
		vel_y = .25*abs(vel_y);
	}
	
	temp_cd.target = NULL;
}

void Entity::handle_collision_down() {
	collision_data temp_cd = check_collision_down();

	if (!(temp_cd.solid) && vel_y < (int)terminal_vel) { 	// if no collision
		vel_y += 0.1f;										// accelerate
		on_ground = false;
	}
	else if (temp_cd.solid/* && !check_collision_up().solid*/) {	// if collision (XXX: the /**/ stuff doesn't do appear to do anything except slow the recoil.
		vel_y = 0;
		top_y += temp_cd.target->get_top_y() - (top_y + height); 
		on_ground = true;
	};
	
	temp_cd.target = NULL;		// be nice ;}
}

void Entity::handle_collision_x() {
	collision_data temp_cd = check_collision_x();
	
	if (temp_cd.solid) {	// if he runs into a wall
		top_x -= vel_x;
	}
	
	if (top_x < 0) { 	// if player is on left side of screen
		top_x++; 		// move him back on
	}
	else if (top_x + width > my_area->get_vec_x() * 8) { // ?
		top_x--;		// similarly, with right side
	}
	
	temp_cd.target = NULL;
}



void Player::move() {

	top_x += 1*vel_x;
	
	handle_collision_x();

	top_y += 1*vel_y;
	
	handle_collision_up();
	handle_collision_down();
}



void Player::handle_input(SDL_Event event) { 
	SDLKey input = event.key.keysym.sym;
	
	if (event.type == SDL_KEYDOWN) {
		
		state = 1; // motion
		
		if (input == SDLK_UP && on_ground == true) { // jump test
			vel_y -= 2;			// velocity points up
			on_ground = false;	// cannot jump
		}
		
		else if (input == SDLK_RIGHT) {
			key_pressed = true;		// just for l/r?
			vel_x += move_speed;
		}
		
		else if (input == SDLK_LEFT) {
			key_pressed = true;		// just for l/r?
			vel_x -= move_speed;
		}
		
		else if (input == SDLK_SPACE) { //respawn
			
			top_x = 16; top_y = 16;
			on_ground = false; vel_y = 0;
		}
		
	}
	
	else if (event.type == SDL_KEYUP) {
		
		state = 0; // idle (do this with enumeration?)
		
		if (input == SDLK_RIGHT) {
			key_pressed = false;
			vel_x -= move_speed; 
		}
		
		else if (input == SDLK_LEFT) {
			key_pressed = false;
			vel_x += move_speed; 
		}
		
		else {
			key_pressed = false; // ew
		}
		
	}
	
	//else { vel_x = 0; } // ? XXX
}



int Player::update_state(int time_elapsed_in) { // as this happens in game loop, he is also printed.
	acc_time += time_elapsed_in;
	
	move();
	
	if (state == 1) 	// moving
		state_ID = 0;
	
	if (acc_time >= max_time) { // lol this code sucks >_>
		acc_time = 0;
		if (state == 0 && !key_pressed && on_ground) { // idle
			state_ID += 1;
			if (state_ID > 2)
				state_ID = 0;
		}
		
		//return 1;
	}
	
	return 1;
} 



Player::~Player() {
	//my_area = NULL;
	
	//std::cout << "I am diff." << std::endl;
}



Block::Block(int width_in, int height_in, int top_x_in, int top_y_in, int ID_in, bool Solid_in) : Entity(width_in, height_in, top_x_in, top_y_in) {
	ID = ID_in; solid = Solid_in;
	// consider using rect coordinates .w and .h for width and height of the objects? :s (could get messy since it violates separation of classes and gfx)
}



Block::~Block() {

}

bool Block::get_solid() {
	return solid;
}



void Area::initialize(Block *BG_in) { // put block map initialization/creation stuff in here!
	area_data.BG = BG_in;
	if (area_data.BG == NULL) { //default/test
		area_data.BG = new Block(320, 240, 0, 0, 0, false);
	}
}



Block *Area::get_BG() {
	return area_data.BG;
}



int Area::get_vec_x() {
	return vec_size_x;
}

int Area::get_vec_y() {
	return vec_size_y;
}


Area::Area(int VS_x_in, int VS_y_in, bool edit) {
	// set size of vector
	vec_size_x = VS_x_in; vec_size_y = VS_y_in;
	
	initialize(NULL); //for setting BG
	
	// TEMPORARY set area data (move this to initialize function with all data (for BG, blockmap, etc.)
	area_data.block_map.resize(vec_size_x);
	for (int i = 0; i < vec_size_x; i++) {
		area_data.block_map[i].resize(vec_size_y); // done setting vector size
		
		for (int j = 0; j < vec_size_y; j++) {
			area_data.block_map[i][j] = 0; // initialize all Block pointers in vector to NULL
		}
	}
	
	area_data.block_list.resize(vec_size_x);
	for (int i = 0; i < vec_size_x; i++) {
		area_data.block_list[i].resize(vec_size_y); // done setting vector size
		
		for (int j = 0; j < vec_size_y; j++) {
			area_data.block_list[i][j] = NULL; // initialize all Block pointers in vector to NULL
		}
	}
	
	// TEMPORARY area data
	if (!edit)
	{
	std::ifstream area_file("./data/temp_level.area");
	
	char area_cell = 'x';
	
	for (int i = 0; i < vec_size_x; i++) {
		for (int j = 0; j < vec_size_y; j++) {
			area_file >> area_cell;
			//std::cout << ((int)area_cell) - 48 << " ";
			area_data.block_map[i][j] = ((int)area_cell) - 48;
		}
		//std::cout << std::endl;
	}
	
	area_data.block_list.resize(vec_size_x);
	for (int i = 0; i < vec_size_x; i++) {
		area_data.block_list[i].resize(vec_size_y); // done setting vector size
		
		for (int j = 0; j < vec_size_y; j++) {
			area_data.block_list[i][j] = NULL; // initialize all Block pointers in vector to NULL
		}
	}
	
	for (int i = 0; i < vec_size_x; i++) {
		for (int j = 0; j < vec_size_y; j++) {
			// TEMPORARY areadata
			
			if (area_data.block_map[i][j] == 1) {
				area_data.block_list[i][j] = new Block(8, 8, j*8, i*8, 101, true); // XXX width first, then height.
			}
			else if (area_data.block_map[i][j] == 2) {
				area_data.block_list[i][j] = new Block(8, 8, j*8, i*8, 102, true);
			}
			else {
				area_data.block_list[i][j] = new Block(8, 8, j*8, i*8, 100, false);
			 // do nothing
			}
			assert(area_data.block_list[i][j]);
		}
	}
	} else {
	for (int i = 0; i < vec_size_x; i++) {
		for (int j = 0; j < vec_size_y; j++) {
			area_data.block_list[i][j] = NULL;
			area_data.block_map[i][j] = 0;
			area_data.block_list[i][j] = new Block(8, 8, j*8, i*8, 100, false);
	}
	}
	}
}



void Area::set_block(int i, int j, int ID, bool solid) {
	area_data.block_map[i][j] = ID-100;
	area_data.block_list[i][j] = new Block(8, 8, j*8, i*8, ID, true);
}



Area::~Area() {
	for (int i = 0; i < vec_size_x; i++) {
		for (int j = 0; j < vec_size_y; j++) {
			delete area_data.block_list[i][j];
			area_data.block_list[i][j] = NULL;
		}
	}
	
	std::cout << "Area deleted successfully!" << std::endl;
}



Block *Area::get_block(int i, int j) {
	return area_data.block_list[i][j];
}
