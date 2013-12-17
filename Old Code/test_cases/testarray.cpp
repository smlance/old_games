#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef int IM[2][3];

IM m00 = {
{0, 0, 0},
{1, 1, 1}
};

IM m01 = {
{0, 2, 0},
{1, 5, 1}
};


IM* World[3][3] = {
{&m00, &m01, 0},
{0, 0, 0},
{0, 0, 0}
};

int main(){
	IM Data;
	memcpy(Data, World[0][0], 2*3*sizeof(int));
	for (int i = 0; i<2; i++){
		for (int j = 0; j<3; j++){
			cout << Data[i][j];
		}
		cout << endl;
	}
	memcpy(Data, World[0][1], 2*3*sizeof(int));
	for (int i = 0; i<2; i++){
		for (int j = 0; j<3; j++){
			cout << Data[i][j];
		}
		cout << endl;
	}
	
	return 0;
}
