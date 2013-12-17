#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "SDL/SDL.h"

using namespace std;

class Player
{
	private:
	int pos_x, pos_y;
	char key;
	public:
	Player();
	~Player();
	void move(int, int);
};

Player::Player()
{
	pos_x, pos_y = 0, 0;
	key = 64;
}

int main()
{
	
	return 0;
}
