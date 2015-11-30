#ifndef STACK_H
#define STACK_H

#include "CharString.h"

class stack 
{
public:

	struct node 
	{
		const CharString * val; // the value of this node
		node *next;    //
	};


	stack();
	void init();
	void clear();
	void push(const CharString& element); // push an element to this stack
	CharString pop(); 
	CharString top(); // get the top element
	int size(); 
	bool isEmpty(); 

	//
	node* head;
	int m_size; // count
};
#endif 
