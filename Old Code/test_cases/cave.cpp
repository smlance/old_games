#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

//use assertions

const int dim = 32;

int cave[dim][dim];

using namespace std;

int return_rand()
{
	return rand() % 2;
}

void create_cave()
{
	for (int i = 0; i<dim; i++)
	{
		for (int j = 0; j<dim; j++)
		{
			cave[i][j] = 1;
		}
	}
}

void print_cave()
{
	for (int i = 0; i<dim; i++)
	{
		for (int j = 0; j<dim; j++)
		{
			cout << cave[i][j];
		}
		
		cout << endl;
	}
}

int main()
{
	srand((unsigned)time(0));
	create_cave();
	print_cave();
	return 0;
}
