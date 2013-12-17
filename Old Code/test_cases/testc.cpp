#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const int sx = 80;
const int sy = 20;

struct coordinates
{
	int x;
	int y;
};

coordinates someFunc()
{
	int dig_x, dig_y;
	dig_x = rand() % sx;
	dig_y = rand() % sy;
	coordinates coords;
	coords.x = dig_x;
	coords.y = dig_y;
	if (coords.y > 10) {
	return coords;
	} else {
	return someFunc(); };
}

int main()
{
	srand((unsigned)time(0));
	cout << someFunc().x << " " << someFunc().y << endl;
	return 0;
}
