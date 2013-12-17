#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define max_itr 5

class Split
{
	private:
	public:
	int test_var;
	Split *node1, *node2;
	int test_var2;
	Split(int t)
	{
		test_var = t;
		test_var++;
		if (test_var < max_itr)
		{
			node1 = new Split(test_var);
			node2 = new Split(test_var);
			node1->test_var2 = 1;
			node2->test_var2 = 2;
		}
	}
	int getT(){
		return test_var;
	}
	void printVals()
	{
		cout << this->test_var2 << "my t is: " << this->getT() << endl;
	}
};

void iterate(Split *n)
{ /*solution to superfluous printings: create separate iterate 
funcs for the node1 and node2 iterators/loops*/
	if(n->node1 != NULL){
		n->printVals();
		iterate(n->node1);
		}
	if(n->node2 != NULL){
		n->printVals();
		iterate(n->node2);
		
	}
}

int main()
{
	Split *ptr_to_spl = new Split(0);
	ptr_to_spl->node2->printVals();
	iterate(ptr_to_spl);
	return 0;
}
