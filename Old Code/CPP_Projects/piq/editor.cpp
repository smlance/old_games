#include "main.h"

Editor::Editor() {
	area = NULL;
	size.x = 0;
	size.y = 0;
	current_text.resize(2);
	SDL_EnableUNICODE(1);
	current_text[0] = "enter width";
	current_text[1] = "enter height";
	active_block_ID = 101;
	active_block_x = SCREEN_WIDTH-8;
	active_block_y = 8;
}



Editor::x_y Editor::prompt_size() {
	int x = 0;
	int y = 0;
	
	SDL_EnableUNICODE(1);
}



int Editor::read_input() {
	if (event.type == SDL_KEYDOWN) {
		if (size.x == 0) { // size not yet recorded
			
				if (event.key.keysym.sym >= 48 && event.key.keysym.sym <= 57) {
					size.x_string += (event.key.keysym.sym);
					//output((char*)event.key.keysym.sym);
					//output("HI");
				}
				else if (event.key.keysym.sym == SDLK_RETURN && size.x_string.length() > 0)
				{
					int out;
					std::istringstream(size.x_string) >> out;
					if (out % 8 != 0) {
						output("must be divisible by 8");
					} 
					if (out > 2048) {
						output("must be 2048 or lower");
					}
					if (!(out % 8 != 0 && out > 2048)) {
						size.x = out;
						output("width set");
						output(int_to_str(out));
					}
				}
			}
		if (size.x != 0 && size.y == 0) {
			if (event.key.keysym.sym >= 48 && event.key.keysym.sym <= 57) {
					size.y_string += (event.key.keysym.sym);
					//output((char*)event.key.keysym.sym);
					//output("HI");
				}
				else if (event.key.keysym.sym == SDLK_RETURN && size.y_string.length() > 0)
				{
					int out;
					std::istringstream(size.y_string) >> out;
					//output(int_to_str(out));
					if (out % 8 != 0) {
						output("must be divisible by 8");
					} 
					if (out > 2048) {
						output("must be 2048 or lower");
					}
					if (!(out % 8 != 0 && out > 2048)) {
						size.y = out;
						output("height set");
						output(int_to_str(out));
					}
				}
			}
		}
		//output("hi");
		//
		else if (event.type == SDL_MOUSEBUTTONDOWN) {	
			assert(0);
			output("h");
			int x; int y;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
				y = event.button.y;
				int adjusted_x = (x - (x % 8)) / 8;
				int adjusted_y = (y - (y % 8)) / 8;
				
				output("Hello");
				
				delete area->get_block(adjusted_x, adjusted_y);
				area->set_block(adjusted_x, adjusted_y, active_block_ID, true);
			}
		}
	return 0;
}



void Editor::init(int x, int y) {
	area = new Area(x, y, true);
}



int Editor::update() {
	if (size.x != 0 && size.y != 0 && area == NULL) {
		init(size.x, size.y);
		return 1;
	}
	return 0;
}



void Editor::show_back() {
	if (area == NULL)
		display.apply_surface(0, 0, display.load_image_from_ID(0, 0), NULL);
}



void Editor::print() {
	if (area == NULL) {
		for (int i = 0; i < current_text.size(); i++) {
			display.apply_text(16, 16 * (i + 1), current_text[i]);
		}
	} else {
		game.render_area();
		display.apply_surface(active_block_x, active_block_y, 
			display.load_image_from_ID(active_block_ID, 0), NULL);
	}
}



Area *Editor::get_area() {
	return area;
}



Editor::~Editor() {

}
