#ifndef __LISH_W_H__
#define __LIST_W_H__

class List{
public:	
	struct node{
		int val;
		unsigned int index; //支持0-4294967295
		struct node *next; 
		node(int x) : val(x), next(NULL){}
	};
	
	struct node *head;
	

	/*构造create List*/
	
	List();
	~List();
	/*插入链表*/
	void insert(int iVal);
	/*删除某个值*/
	void delt(int iVal);

	void deltAll();
	/*打印链表*/
	void printList(int start, int end);
	
};


#endif
