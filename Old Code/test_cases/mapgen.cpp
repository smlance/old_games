#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>

#define size_y 22
#define size_x 80

int map[size_y][size_x];

void printMap(){
	for(int i=0; i<size_y; i++){
		for(int j=0; j<size_x; j++){
			mvaddch(i, j, map[i][j]);
		}
	}
}

void initMap(){
	srand((unsigned)time(0));
	int start_y, start_x;
	
	for(int i=0; i<size_y; i++){
		for(int j=0; j<size_x; j++){
			map[i][j] = 0;
		}
	}
	
	if (rand() % 2 + 1 == 1){
		start_y = (size_y)/2 + (rand() % 5 + 1);
	}
	else if (rand() % 2 + 1 == 2){
		start_y = (size_y)/2 - (rand() % 5 + 1);
	};
	
	if (rand() % 2 + 1 == 1){
		start_x = (size_x)/2 + (rand() % 5 + 1);
	}
	else if (rand() % 2 + 1 == 2){
		start_x = (size_x)/2 - (rand() % 5 + 1);
	};
	
	const int s1_y = rand() % 6 + 6;
	const int s1_x = rand() % 6 + 5;
	mvaddch(s1_y, s1_x, 35);
	for(int i=start_y; i<(s1_y+ start_y); i++){
		for(int j=start_x; i<(s1_x+ start_x); j++){
			mvaddch(i, j, 35);
		}
	}
	
}

int main(){
	initscr();
	noecho();
	curs_set(0);
	initMap();
	//printMap();
	getch();
	endwin();
	return 0;
}
