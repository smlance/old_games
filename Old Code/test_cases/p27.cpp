#include <cstdio>
#include <cstdlib>
#include <iostream>

/*int quad(int n, int a, int b)
{
	return ((n*n) + (a*n) + (b));
}*/

int main(int argv, char** argc)
{
	//int a, b;
	std::cout << "hi";
	
	
	int primes[1000];
	//get list of primes
	int index = 0;
	std::cout << index;
	for(int i = 0; i<1000; i++)
	{
		//int total = 0; //num of divisors
		
		for(int j = 0; j<i; j++)
		{
			if (i%j == 0)
			{
				break;
			}
		}
		primes[index] = i;
		index++;
	}
	
	for(int n=0; n<index; n++)
	{
		std::cout << primes[n] << std::endl;
	}
	
	//for(b

	return 0;
}
