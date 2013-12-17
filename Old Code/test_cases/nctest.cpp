#include <ncurses.h>

int main()
{
	initscr();
	curs_set(0);
	mvaddch(0, 0, 64);
	getch();
	endwin();
	return 0;
}
