#include "main.h"



Game::Game() {
	game_state = 0;		// menu

	for (int i = 0; i < 100; i++) {
		entity_list[i] = NULL;
	}
}



Game::~Game() {
	for (int i = 0; i < 100; i++) { // removing these gets rid of segfault upon closing. intriguing!
		if (entity_list[i]) {
			delete entity_list[i];
			entity_list[i] = NULL;
		}
	}
	
	display 		= 	NULL;
	
	delete present_area;
	present_area 	= 	NULL;
	
	delete menu;
	menu			=	NULL;
	
	if (editor)
		delete editor;
	editor = NULL;
	
	std::cout << "Game deleted successfully!" << std::endl;
}



void Game::send_updates(int time_elapsed) {	// go through all update routines, passing in pertinent vars
	update_game_objs(time_elapsed);
}



void Game::render_to_disp(Entity *en) { //make this for other crap too, not just Entities :(
	if (en) {
		display->apply_surface(en->get_top_x() - display->get_cam()->get_viewer()->x, 
			en->get_top_y() - display->get_cam()->get_viewer()->y, 
			display->load_image_from_ID(en->get_ID(), en->get_state_ID()), 
			NULL/*display->get_cam()->get_viewer()*/);
	}
		
	else if (!en) {
		static int num = 300;
		display->apply_surface(0, 0, display->load_image_from_ID(num, 0), NULL);
		//num++;
		//if (num > 302) num = 300;
	}
	
	en = NULL;
}



void Game::init_game_objs() {

	menu = new Menu;
	menu->initialize("untitled game", 3, "play", "level editor", "exit");
	//assert(0);
	
	present_area = new Area(SCREEN_HEIGHT/8*2, SCREEN_WIDTH/8*2); // XXX careful with order. height then width. >_> (since you did ys first then xs...?)
	entity_list[0] = new Player(8, 8, 16, 16);
	entity_list[0]->initialize(present_area);
	
	editor = NULL;
	
}



void Game::adjust_camera() {
	SDL_Rect *viewer = display->get_cam()->get_viewer();

	viewer->x = (entity_list[0]->get_top_x() + entity_list[0]->get_width() / 2)
		- SCREEN_WIDTH / 2;
	viewer->y = (entity_list[0]->get_top_y() + entity_list[0]->get_height() / 2)
		- SCREEN_HEIGHT / 2;
		
	if (viewer->x < 0) {
		viewer->x = 0;
	}
	
	if (viewer->y < 0) {
		viewer->y = 0;
	}
	
	if (viewer->x > present_area->get_vec_x() * 8 - viewer->w) {
		viewer->x = present_area->get_vec_x() * 8 - viewer->w;
	}
	
	if (viewer->y > present_area->get_vec_y() * 8 - viewer->h) {
		viewer->y = present_area->get_vec_y() * 8 - viewer->h;
	}
}



void Game::render_area() {
	/*if (game_state != 0) {*/	// game
		render_to_disp(present_area->get_BG()); // render background
		
		// ********************************************************************* //
		// ********************************************************************* //
		// XXX MAYBE JUST CHANGE IT TO HAVE render_to_disp ACCEPT IMAGE IDS!!! XXX //
		// ********************************************************************* //
		// ********************************************************************* //
		// or at least make it general for images; i.e. errr.
		
		for (int i = 0; i < present_area->get_vec_x(); i++) {
			for (int j = 0; j < present_area->get_vec_y(); j++) {
				if (present_area->get_block(i, j))
					render_to_disp(present_area->get_block(i, j));
			}
		}
		
		//render_to_disp(NULL);
		
	/*} else {			// menu
		//menu->display();
	} */
	
}



void Game::update_game_objs(int time_elapsed) { // XXX need to do first isolate to just current area
	// and then to just on-screen data (FOR RENDERING/DISPING. MAYBE SEPARATE THESE (name
	// of current func is confusing.)
	
	if (game_state == 1) {
		
		adjust_camera();
		
		render_area();
		
		// update/render entities
		for (int i = 0; i < 100; i++) {
			if (entity_list[i]) {	// entity list gets updated here. All entities are happy!
				entity_list[i]->update_state(time_elapsed);
				render_to_disp(entity_list[i]);
			}
		}
		
	} else if (game_state == 0) {
		//menu stuff
		menu->show_back();
		menu->print();
	} else if (game_state == 2) {
		if (editor->update()) { // area has been made
			present_area = editor->get_area();
		}
		editor->show_back();
		editor->print();
	}
}



void Game::handle_input(SDL_Event event) {
	if (game_state == 1) { 	// if we are playing
		((Player*)(entity_list[0]))->handle_input(event); // give event to player
	} else if (game_state == 0) {				// menu
		menu->handle_input(event);
		//std::cout << "hi" << std::endl;
	} else if (game_state == 2) {
		editor->read_input();
	}
}



void Game::change_state(int state_in) {
	game_state = state_in;
	
	if (game_state == 2) {
		//delete menu;
		//menu = NULL;
		//output("t");
		editor = new Editor;
	}
}



int Game::get_state() {
	return game_state;
}



void Game::set_display(Display *display_in) {
	display = display_in;	// useless since display is out of game >_>
}
