#include <iostream>
#include "list.h"

using namespace std;

int main()
{
	List lt;
	
	lt.insert(4);
	lt.insert(45);
	lt.insert(45);
	lt.insert(3);
	lt.insert(5);
	lt.insert(6);
	lt.insert(47);
	lt.insert(48);
	lt.insert(23);
	lt.insert(43);
	lt.printList(0,0);	

	lt.delt(45);
	lt.printList(0,0);	


	lt.deltAll();
	
	return 0;
}
