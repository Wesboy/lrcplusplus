#include <iostream>
#include "list.h"

using namespace std;

int main()
{
    List lt;

    lt.generateRandList(100, lt.head); 

	lt.printList(0,0);	


	lt.deltAll();
	
	return 0;
}
