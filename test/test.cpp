#include <iostream>
#include "class_test.h"
#include "class2_test.h"

#include "H_2_test.h"
#include "H_1_test.h"


using namespace std;
A* cl_a[1];
change ch;
int main()
{
	cl_a[0] = new B;
	Foo(*cl_a, &ch);
	return 0;
}
