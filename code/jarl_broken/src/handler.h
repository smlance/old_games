#ifndef HANDLER_H
#define HANDLER_H

class Handler
{
	public:
		Handler() 	{ };
		~Handler() 	{ };
		bool handle(Event);
		void handlePlaying(Event);
};

#endif // HANDLER_H
