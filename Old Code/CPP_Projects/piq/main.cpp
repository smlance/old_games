#include "main.h"



bool FULLSCREEN;

Display display;
Game game;
SDL_Event event;



void output(std::string input) {
	std::cout << input << std::endl;
}



std::string int_to_str(int num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}



void initialize() {
	display.initialize();

	game.set_display(&display);
	game.init_game_objs();
}



void loop() {
	bool running = true;
	
	Timer FramesPerSec;
	Timer UpdateTimer;
	UpdateTimer.start(); // this is for passing in elapsed times into the Update routine
	
	while (running) {	// one loop completed = one frame of the game completed, so timer needed
		
		FramesPerSec.start(); /* starts timer to record time; this happens every frame! */
	
		while (SDL_PollEvent(&event)) 	/* while input is detected */
		{								/* decide what to do depending on type */
			if (event.type == SDL_QUIT)	/* quit */
			{
				running = false;
			}
			
			else if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
			
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) { 
					game.change_state(0);
				} else {
					game.handle_input(event);
				}
				
			}
			

		}
			if (game.get_state() == -1) {
				running = false;
			}
		
		game.send_updates(UpdateTimer.get_time_elapsed());	// this is where updates occur! 
			// the elapsed time since the last frame is passed in, and then the timer is reset.
		UpdateTimer.start(); // reset
		
		display.refresh();
		
		if (FramesPerSec.get_time_elapsed() < (1000/FPS)) {	/* if this frame finishes early */
			SDL_Delay((1000/FPS) - FramesPerSec.get_time_elapsed());
		}	/* delay by the difference between how much we've done and the number of secs/frame 
		(gives remaining time for frame to complete, which is how much we want to delay by) */
	}
}



void clean_up() {
	//delete &game;
	
	//delete &event;
}



int main(int argc, char **argv) {

	FULLSCREEN = false;

	if (argc > 1 && argc < 5) {
		for (int i = 0; i < argc; i++) {
			//std::cout << argv[i] << std::endl;
		}
		if (std::string(argv[1]) == "full") {
			FULLSCREEN = true;
			//std::cout << "FULL" << std::endl;
		}
	}
	
	initialize();
	loop();
	clean_up();
	
	return 0; 	// well, that was fast!
}
