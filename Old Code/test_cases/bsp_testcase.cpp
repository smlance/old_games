#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <math.h>

#define sy 20
#define sx 80

int map[sy][sx];

class BSPRoom
{
	private:
	int size_x, size_y, start_x, start_y, split_loc;
	char id;
	int max_itr;
	bool vertical;
	BSPRoom *left, *right, *parent;
	
	public:
	BSPRoom(BSPRoom*, int, char);
	void genVals(int);
	void makeSplit();
	void printRoom(); //different class...
};

BSPRoom::BSPRoom(BSPRoom *par, int level, char iden)
{
	max_itr = 4;
	id = iden;
	parent = par;
	level++;
	
	if (!parent) /*initial node check*/
	{
		size_x = sx;
		size_y = sy;
		start_x = 0;
		start_y = 0;
	} else {
		genVals(level);
		//printRoom();
	};
	
	makeSplit();
	
	if (level < max_itr)
	{
		//if (rand() % 100 > 35){
			left = new BSPRoom(this, level, 'l');
			right = new BSPRoom(this, level, 'r');//};
		//if (!right && !left){
		//	printRoom();};
	} else {
		printRoom();
	}
}

void BSPRoom::makeSplit()
{
	if (rand() % 2) //vertical
	{
		vertical = TRUE;
		split_loc = size_x/2 + start_x; //+/- uncertainty to add some fun ;)
		if (rand() % 2) {
			split_loc += rand() % 5;
		} else {
			split_loc -= rand() % 5;
		}
	} else {
		vertical = FALSE;
		split_loc = size_y/2 + start_y;
		if (rand() % 2) {
			split_loc += rand() % 3;
		} else {
			split_loc -= rand() % 3;
		}
	};
	/*if (parent) {
		if (parent->vertical) {
			vertical = FALSE;
			split_loc = size_y/2;
		} else { 
			vertical = TRUE;
			split_loc = size_x/2;
		}
	}*/ //test... ensures vertical -> hori -> vertical -> hori...
}

void BSPRoom::printRoom()
{
	for (int i = start_y + 1; i < start_y + size_y - 1; i++) {
		for (int j = start_x + 1; j < start_x + size_x - 1; j++) {
			if (map[i][j] == 46) mvaddstr(22, 80, "Overlap");
			map[i][j] = 46;
			mvaddch(i, j, map[i][j]);
		}
	}
}

std::string intToStr(int integer)
{
	std::string s;
	std::stringstream out;
	out << integer;
	s = out.str();
	return s;
}

void BSPRoom::genVals(int level)
{
	if ((parent->vertical) && id == 'l') { //vert and left
		start_y = parent->start_y;
		start_x = parent->start_x;
		size_y = parent->size_y;
		size_x = parent->split_loc - start_x; //questionable
		if (start_y >= sy) mvaddstr(4, 0, "start_y >= sya");
		mvaddstr(level, 80, intToStr(start_y).c_str());
		mvaddstr(level, 83, intToStr(start_x).c_str());
		mvaddstr(level, 86, intToStr(size_y).c_str());
		mvaddstr(level, 89, intToStr(size_x).c_str());
		if (size_x < 0) mvaddstr(19, 80, "Warning: neg x-val0");
	} else if ((parent->vertical) && id == 'r') { //vert and right
		start_y = parent->start_y;
		start_x = parent->split_loc;
		size_y = parent->size_y;
		size_x = abs(parent->size_x - parent->split_loc);/*
		XXX 123 is the line that creates negs! XXX
		*/
		if (start_y >= sy) mvaddstr(4, 0, "start_y >= syb");
		level += 2;
		mvaddstr(level, 80, intToStr(start_y).c_str());
		mvaddstr(level, 83, intToStr(start_x).c_str());
		mvaddstr(level, 85, intToStr(parent->size_x).c_str());
		mvaddstr(level, 89, intToStr(parent->split_loc).c_str());
		level -= 2;
		if (size_x < 0) mvaddstr(19, 80, "Warning: neg x-val1");
	} else if ((!(parent->vertical)) && id == 'l') { //hor and top
		start_y = parent->start_y;
		start_x = parent->start_x;
		size_y = parent->split_loc - start_y;
		size_x = parent->size_x;
		if (start_y >= sy) mvaddstr(4, 0, "start_y >= syc");
		level += 4;
		mvaddstr(level, 80, intToStr(start_y).c_str());
		mvaddstr(level, 83, intToStr(start_x).c_str());
		mvaddstr(level, 86, intToStr(size_y).c_str());
		mvaddstr(level, 89, intToStr(size_x).c_str());
		level -= 4;
	} else if ((!(parent->vertical)) && id == 'r') {
		start_y = parent->split_loc;
		start_x = parent->start_x;
		size_y = abs(parent->size_y - parent->split_loc);/*
		XXX 148 is the line that creates negs! XXX
		*/
		size_x = parent->size_x;
		if (start_y >= sy) mvaddstr(4, 0, "start_y >= syd");
		level += 6;
		mvaddstr(level, 80, intToStr(start_y).c_str());
		mvaddstr(level, 83, intToStr(start_x).c_str());
		mvaddstr(level, 86, intToStr(size_y).c_str());
		mvaddstr(level, 89, intToStr(size_x).c_str());
		level -= 6;
	};
	mvaddstr(level, 92, intToStr(level).c_str());
	if (start_x < 0) mvaddstr(1, 0, "start_x < 0");
	if (start_y < 0) mvaddstr(2, 0, "start_y < 0");
	if (start_x >= sx) mvaddstr(3, 0, "start_x >= sx");
	if (start_y >= sy) mvaddstr(4, 0, "start_y >= sy");
	//getch();
	if (size_x < 0) mvaddch(20, 80, id);
	if (size_y < 0) mvaddch(20, 80, id);
}

int main()
{
	initscr();
	curs_set(0);
	srand((unsigned)time(0));
	
	for (int i = 0; i<sy; i++) {
		for (int j = 0; j<sx; j++) {
			map[i][j] = 35;
		}
	}
	
	mvaddstr(0, 80, "Init went fine"); getch();
	
	BSPRoom root(NULL, 0, NULL);
	
	/*for (int i = 0; i<sy; i++) {
		for (int j = 0; j<sx; j++) {
			mvaddch(i, j, map[i][j]);
		}
	}*/
	
	getch();
	endwin();
	
	return 0;
}
