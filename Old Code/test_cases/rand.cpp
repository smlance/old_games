#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	srand((unsigned)time(0));
	int i = 0;
	while (1){
		i += rand() % 2;
	}
	
	return 0;
}
