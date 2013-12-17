#include <ncurses.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define map_x 78
#define map_y 22

int map[map_y][map_x];
int map2[map_y][map_x];

void transprint(int y, int x){
	if (map[y][x] == 0){
		mvaddch(y, x, 35);
	}
	else if (map[y][x] == 1){
		mvaddch(y, x, 127 | A_ALTCHARSET);
	};
}

void printmap(){
	for (int i=0;i<map_y;i++){
		for (int j=0;j<map_x;j++){
			transprint(i, j);
		}
	}
}

void ca_map(){ //start with 1,1, go thru map, look at nearby cells 
//individually; if they are 1, increment n; etc... do this, then compare
//n and decide. 
	for (int i=1;i<map_y-1;i++){
		for (int j=1;j<map_x-1;j++){
			int n = 0;
			int r2 = 0;
			for (int ii=-1; ii<=1; ii++){
			for (int jj=-1; jj<=1; jj++){
			if (map[i + ii][j + jj] == 0){
				//if (jj != 0 && ii != 0){
				n++;
				//}
			}
			}}
			if (n <= 4){
				map2[i][j] = 1;
			}
//if 3 or fewer adj wall cells, make it open.
			else if (n > 6){
				map2[i][j] = 0;
			}
//if more than 5 wall cells, make it a wall.
			else {
			};
			
			for (int ii=map_y-2; ii<=map_y+2; ii++){
			for (int jj=map_x-2; jj<=map_x+2; jj++){
			
			}
			}
		}
		
	}
	memcpy(map, map2, map_y*map_x*sizeof(int));
}
void playermove();
void initmap(){
	srand((unsigned)time(0));
	
	for (int i=0;i<map_y;i++){
		for (int j=0;j<map_x;j++){
			if (rand() % 100 + 1 >= 40 && (i != 0 && j != 0 && i != map_y -1 && j != map_x -1)){
				map[i][j] = 1;
			}
			else{
				map[i][j] = 0;
			};
		}
	}
	printmap();
	getch();
	ca_map();
	printmap();
	playermove();
}

void playermove(){
	int x = 13;
	int y = 13;
	srand((unsigned)time(0));
	
	
	int k = 64;
	mvaddch(y, x, k);
	bool blap = TRUE;
	while (blap == TRUE){
		if (getch() == KEY_UP){
			mvaddch(y, x, 127 | A_ALTCHARSET);
			y--;
			mvaddch(y, x, k);
			break;
		}
		else if (getch() == KEY_DOWN){
			mvaddch(y, x, 127 | A_ALTCHARSET);
			y++;
			mvaddch(y, x, k);
			break;
		}
		else if (getch() == KEY_LEFT){
			mvaddch(y, x, 127 | A_ALTCHARSET);
			x--;
			mvaddch(y, x, k);
			break;
		}
		else if (getch() == KEY_RIGHT){
			mvaddch(y, x, 127 | A_ALTCHARSET);
			x++;
			mvaddch(y, x, k);
			break;
		}
		else if (getch() == 27){
			blap = FALSE;
			break;
		};
	}
}

int main(){
	initscr();
	noecho();
	curs_set(0);
	initmap();
	getch();
	endwin();
	return 0;
}
