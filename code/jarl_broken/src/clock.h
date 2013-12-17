#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
	private:
		int time_init;

	public:
		Clock();
		~Clock() { };
		void start();
		int timeElapsed();
};

#endif // CLOCK_H
