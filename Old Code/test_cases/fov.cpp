#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>

/* by odd lobster@takas.lt
** map: 0-passable terrain(los can see), 1-block, 9-player start position(actualy this one isnt used), 5 - los can see, 3-player position
** ;)
*/
int myMap[20][20]=  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
                     1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void drawline_mod(int map[20][20], int x, int y, int x2, int y2) {
    int dx = abs(x - x2);
    int dy = abs(y - y2);
    //std::cout << "\t" << dx << " " << dy << std::endl;
    double s = double(.99/(dx>dy?dx:dy));
    double t = 0.0;
    while(t < 1.0) {
        dx = int((1.0 - t)*x + t*x2);
        dy = int((1.0 - t)*y + t*y2);
        std::cout << dx << " " << dy << " " << std::endl;
        if (map[dy][dx] != 1) {
			map[dy][dx] = 5;
		} else {
			return;
		}
        t += s; 
    }
}

void los(int map[20][20], int range, int plx, int ply) {
	int x, y;
	for (double f = 0; f < 3.14*2; f += 0.05) {
		x = int(range*cos(f)) + plx;
		y = int(range*sin(f)) + ply;
		//std::cout << cos(f) << " " << sin(f) << "\t" << x << " " << y << std::endl;
		drawline_mod(map,plx,ply,x,y);
	}
}

int main()
{
	los(myMap, 5, 10, 10);
	return 0;
}

