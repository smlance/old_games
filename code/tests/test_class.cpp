#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

struct ABCInfo
{
	int x, y, z, w, v;
};
/*
 * READ THE REST OF THE CODE BEFORE YOU READ THIS!
 * 
 * The problem can (possibly) be solved by using a struct of all the variables,
 * although each class would need a slightly variant struct if its variables
 * differ from its parents. "Getting" the variables is easy -- just return
 * ABCInfo; -- but "Setting" them would probably actually require making a
 * setter for each variable in the struct.
 */

class A
{
protected:
	int x, y, z;
	
public:
	A(int, int, int);
	~A();
	virtual void print_values();
};

A::A(int X, int Y, int Z)
{
	x = X; y = Y; z = Z;
}

A::~A()
{

}

void A::print_values()
{
	cout << x << "\t" << y << "\t" << z << "\t\n\n";
	/*
	 * PROBLEM: If we want children B and C to also have print_values(),
	 * but, say, with w and v printed BEFORE the endl, how is this possible
	 * without overriding the function entirely?
	 *
	 * This is not such an issue if we know how many variables we are dealing
	 * with, but say we later realize we need to add MANY more variables --
	 * u, t, s, r, q, ... and then later, we decide we only really need r, q,
	 * w, and v. This makes adjusting the code (since the variables appear in
	 * so many places) cumbersome.
	 */
}

class B : public A
{
private:
	int w, v;
	
public:
	B(int, int, int, int, int);
	~B();
	void print_values();
};

B::B(int W, int V, int X, int Y, int Z) : A(X, Y, Z)
{
	w = W; v = V; x++;
	/*
	 * PROBLEM: See line 42, above. We have to keep track not only of all of
	 * B's variables in the ctor, but also all of A's. If we want to add variables
	 * to B later on, we're in trouble -- we have to change the prototype, the ctor,
	 * and the declaration list.
	 */
}

B::~B()
{

}

void B::print_values()
{
	A::print_values();
	cout << w << "\t" << v << "\t\n\n";
	/*
	 * PROBLEM: Again, see line 42.
	 */
}

class C : public A
{
private:
	int a, b;
	
public:
	C(int, int);
	~C();
	void print_values();
};

C::C(int A_, int B) : A(x, y, z)
{
	a = A_; b = B; z += 100;
	/*
	 * PROBLEM: This should not be possible, yet it compiles. No values get passed
	 * in for x, y, and z, because when an instance of C is created, only two
	 * values, a and b, are passed in. x, y, and z thus take on strange values.
	 * See lines 105 and 134.
	 */
}

C::~C()
{

}

void C::print_values()
{
	A::print_values();
}

int main()
{
	cout << "A\n";
	A parent(5, 10, 15);
	parent.print_values();
	
	cout << "B\n";
	B child(0, 1, 3, 4, 5);
	child.print_values();
	
	cout << "C\n";
	C second_child(50, 100);
	second_child.print_values();
	
	return 0;
}
