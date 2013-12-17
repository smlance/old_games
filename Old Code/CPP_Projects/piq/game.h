#ifndef GAME_H
#define GAME_H

class Game {
	private:
	Display 	*display;
	Entity 		*entity_list[100];	/* size? XXX consider an "Active" entity list */
		// lol just consider putting this in Area, since it's really all handled by Area
	Area 		*present_area;
	Menu 		*menu;
	Editor 		*editor;
	int 		game_state;
	
	public:
	Game();
	~Game();
	
	void set_display(Display *display_in);
	void handle_input(SDL_Event event);
	void init_game_objs();
	
	void update_game_objs(int time_elapsed);
	void render_area();
	
	void send_updates(int time_elapsed);
	void render_to_disp(Entity *en);
	
	void change_state(int);
	int get_state();
	
	void adjust_camera();
};

#endif
