#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

using namespace std;

#define SIZE_Y 20
#define SIZE_X 80

class SplitSec{
	/*each splitsec can look at its parent's first 4 int parameters
	(start_x,y, size_y,x) to determine where it splits
	XXX initial parent needs these vals fed into it XXX
	*/
	private:
	/*XXX "sister" ptr needs to be fed to each one and two later on;
	is it necessary to make another one..?*/
	int start_y, start_x, size_y, size_x, incision_location;
	int hor_or_ver;
	int control_iter;
	SplitSec *one, *two, *parent;
	public:
	SplitSec(){
		if (parent == NULL){
			start_x = 0;
			start_y = 0;
			size_x = SIZE_X;
			size_y = SIZE_Y;
			control_iter = 0;
		};
	}
	~SplitSec(){
		//delete /*one, two, parent,*/ &start_y, &start_x, &size_x, &size_y, &incision_location, &hor_or_ver;
	}
	
	int getStartY(){
		return start_y;
	}
	int getStartX(){
		return start_x;
	}
	int getSizeY(){
		return size_y;
	}
	int getSizeX(){
		return size_x;
	}
	int getIncLoc(){
		return incision_location;
	}
	void setContIter(int CI){
		control_iter = CI;
	}
	
	void makeSplit(){
		srand((unsigned)time(0));
		int uncert = rand() % 5 + 1;
		
		if (rand() % 2 + 1 == 1) {hor_or_ver = 1; /*incision is VERTICAL*/
			if (rand() % 2 + 1 == 1){
			incision_location = (parent->getSizeY()/2 + (uncert));
			}
			else {
			incision_location = (parent->getSizeY()/2 - (uncert));
			};/*problem here is that if size gets less than 5, the incision could go off map*/
		}
		else {hor_or_ver = 2; /*incision is HORIZONTAL*/
			if (rand() % 2 + 1 == 1){
			incision_location = (parent->getSizeX()/2 + (uncert));
			}
			else{
			incision_location = (parent->getSizeX()/2 - (uncert));
			}; /*problem here is that if size gets less than 5, the incision could go off map*/
			};
		one->parent = this;
		two->parent = this;
		if (hor_or_ver == 1){
			one->start_y = start_y;
			one->start_x = start_x;
			one->size_y = size_y;
			one->size_x = (incision_location - one->start_x);
			
			two->start_y = start_y;
			two->start_x = incision_location;
			two->size_y = size_y;
			two->size_x = (size_x - incision_location);
		}
		else if (hor_or_ver == 2){
			one->start_y = start_y;
			one->start_x = incision_location;
			one->size_y = (incision_location - one->start_y);
			one->size_x = size_x;
			
			two->start_y = incision_location;
			two->start_x = start_x;
			two->size_y = (size_y - incision_location); /*same as above?*/
			two->size_x = size_x;
		};
	}
};

void splitMap(int number){
	SplitSec initial;
	for (int i=0;i<number;i++){
		
	}
}

int main(){

	
	char map[20][80];
	
	for (int i=0;i<20;i++){
		for (int j=0;j<80;j++){
			map[i][j] = '.';
		}
	}
	srand((unsigned)time(0));
	int num_rooms = 10;
	for (int i = 0; i<num_rooms; i++){
	int rand_const = rand() % 7 + 4;
	int rand_const2 = rand() % 7 + 4;
	
	int sp_y = rand() % 20/2 + 1;
	int sp_x = rand() % 80/2 + 20;
	for (int i=sp_y; i<(sp_y+rand_const); i++){
		for (int j=sp_x; j<(sp_x+rand_const2); j++){
			//cout << i <<" "<< j << endl;
			if (map[i][j] == '#' || map[i][j] == 'o'){
				i = sp_y + rand_const;
				j = sp_x + rand_const2;
			}
			else if ((i == sp_y) || (i == sp_y+rand_const-1) || (j == sp_x) || (j == sp_x+rand_const2-1)){
			map[i][j] = 'o';
			}
			else{
			map[i][j] = 'o';
			};
			for (int x= -1; x<=1; x++){
				for (int y= -1; y<=1; y++){
					if ((x != 0 && y != 0) && (map[i][j] == 'o') && (map[i+x][j+y] != '#')){
						map[i+x][j+y] = '#';
					}
				}
			}
	}
	}
	}
	for (int i=0;i<20;i++){
		for (int j=0;j<80;j++){
			cout << map[i][j];
		}
		cout << endl;
	}
	SplitSec test;
	SplitSec *a = new SplitSec;
	SplitSec *b = new SplitSec;
	
	return 0;
}
