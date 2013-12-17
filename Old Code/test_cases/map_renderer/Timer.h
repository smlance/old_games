#ifndef TIMERH
#define TIMERH

class Timer
{
	private:
	int start_ticks;
	int paused_ticks;
	bool paused, started;
	SDL_Surface *start_stop, *pause_message;
	
	public:
	Timer();
	~Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	int getTicks();
	bool isStarted();
	bool isPaused();
	SDL_Surface *getSS();
	SDL_Surface *getPM();
};

#endif
