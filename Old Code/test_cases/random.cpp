#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

using namespace std;

int main(){
	initscr();
	noecho();
	cbreak();
	srand((unsigned)time(0));
	int map[20][20];
	int itemmap[20][20];
	
	/*for random walls:
		randomly place an A. when that happens, randomly select a direction and number. add that many As in that direction.
	*/
	
	for (int i = 0; i<20; i++){
		for (int j = 0; j<20; j++){
			if (i == 0 || i == 19 || j == 0 || j == 19){
				map[i][j] = 1;
			}
			else {
				map[i][j] = 0;
			};
		}
	}
	
	for (int i = 0; i<20; i++){
		for (int j = 0; j<20; j++){
			int random = rand() % 100 + 1;
			if (random < 99){
				itemmap[i][j] = 0;
			}
			else {
				if (map[i][j] != 0){
					itemmap[i][j] = 0;
				}
				else {
				itemmap[i][j] = 2;
				};
			};
		}
	}
	for (int i = 0; i<20; i++){
		for (int j = 0; j<20; j++){
			if (map[i][j] == 0){
				mvaddch(i, j, 127 | A_ALTCHARSET);
			}
			else{
			mvaddch(i, j, map[i][j] + 64);
			};
		}
	}
	for (int i = 0; i<20; i++){
		for (int j = 0; j<20; j++){
			if (itemmap[i][j] != 0){
				mvaddch(i, j, itemmap[i][j] + 64);
			};
		}
	}
	getch();
	endwin();
	return 0;
}
