/*
bsptest.cpp - try to get an iterative BSP working to implement for map generation algorithm
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Split
{
	public:
	int test_var;
	Split *node1, *node2;
	
	private:
	Split(int t)
	{
		test_var = t;
		test_var++;
		if (test_var < 3)
		{
			node1 = new Split(test_var);
			node2 = new Split(test_var);
		}
	}
};

int main()
{
	
	return 0;
}
