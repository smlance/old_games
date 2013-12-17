#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <class type>
type Multiply(type x, type y){
	return x*y;
}

int main(){
	long x = 3;
	long y = 9;
	int a = 2;
	int b = 6;
	long result = Multiply(x,y);
	int result_a = Multiply(a,b);
	cout << x << " " << y << " " << result << endl;
	cout << a << " " << b << " " << result_a << endl;
	return 0;
}
