#include <iostream>
#include <sstream>
#include <ncurses.h>

using namespace std;

std::string IntToString(int i){
	std::stringstream ss;
	std::string s;
	ss << i;
	s = ss.str();
	return s;
}

int main(){
	initscr();
	for (int i = 0; i<160; i++){
		addstr(IntToString(i).c_str());
		addch(i);
		addch(9);
	}
	for (int i = 160; i<256; i++){
		addstr(IntToString(i).c_str());
		addch(i | A_ALTCHARSET);
		addch(9);
	}
	getch();
	endwin();
	return 0;
}
