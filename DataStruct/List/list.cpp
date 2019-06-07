#include <iostream>
#include <stdlib.h>
#include "list.h"

using namespace std;


List::List()
{
	cout<<"create List head"<<endl;
	
	List::head = new struct node(0);
	List::head->next = NULL;
	List::head->index = 0;
	
	cout<<"create List head"<<&List::head<<endl;
}

List::~List()
{
	cout<<"destructing List head"<<endl;
}

void List::insert(int iVal)
{
	struct node *p;

	p = List::head;

	while(NULL != p->next)
	{
		p = p->next;
	}

	p->next = new struct node(iVal);
	p->next->index = p->index+1;

}

void List::delt(int iVal)
{
	struct node *p;
	struct node *del;
	p = List::head->next;
	del = List::head;

	while(p != NULL)
	{
		
		if(iVal == p->val)
		{
			del->next = p->next;
			delete(p);
			p = del->next;
		}
		else
		{
			del = p;
			p = p->next;
		}
    }
}

void List::deltAll()
{
	struct node *p;
	struct node *del;

	p = List::head->next;
	del = p;

	while(p != NULL)
	{
		del = p;
		p = p->next;
		delete(del);	
	}

}

void List::printList(int start, int end)
{
	struct node *p;

	p = List::head->next;

	while(NULL != p){
		cout<<"["<<p->index<<"]"<<p->val<<" ";
		p = p->next;
	}
	cout<<endl;
}

void List::generateRandList(int len, struct node *ihead)
{
    if(len <= 0)
      return ;//  return NULL;
    
    struct node *p;
    unsigned int index = 0;
    int iRandval;

    p = new struct node(0); // head
    if(p == NULL)
    {
        cout<<"new node error!!!"<<endl;
        exit(0);
    }
    List::head = p;
    p->index = index;


    while(len--)
    {
    /*generate rand value*/
        iRandval = rand()%11;
        
        p->next = new struct node(iRandval);
        p->next->index = ++index;
        p = p->next;
    }

    //return ihead;

}

#if 0
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

#endif
