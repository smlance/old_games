#ifndef TIMER_H
#define TIMER_H

class Timer {
	private:
	int time_i; /* initial time recorded */
	
	public:
	Timer();
	~Timer();
	
	void start();
	int get_time_elapsed();
};

#endif
