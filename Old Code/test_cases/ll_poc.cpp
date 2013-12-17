#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class A{
	public:
	int key;
	A* next;
	A();
};

A::A(){
	key = 5;
}

using namespace std;

int main(){
	A *a1 = new A;
	A *head = new A;
	A *a2 = new A;
	A* z = new A;
	head->next = a1;
	a1->next = a2;
	a2->next = z;
	z->next = z;
	a1->key = 3;
	cout << (a2->next)->key << endl;
	cout << a1->key << endl;
	
	return 0;
}
