#include <iostream>
#include "CharString.h"
#include "CharStringLink.h"
using namespace std;


void CharStringLink::InitList()  //
{
	this->m_size = 0;
	this->head = NULL;
	this->tail = NULL;
}

bool CharStringLink::isEmpty()
{
	return m_size == 0;
}

/*
CharString ListSearch(CharString element)
{
	
}*/
void CharStringLink::ListInsert(CharString element)
{	

	node *p1;
	p1=new node();
	p1->data = element;
	if(head==NULL)
	{
		head=p1;
		tail=p1;
	}
	else
	{
		tail->next=p1;
		tail=p1;
	}
	tail->next = NULL;
}

void CharStringLink::print_list(node *head, string outputname)
{
	ofstream output(outputname);
	node *p = head;
	while(p)
	{
		output << p->data <<endl;
		p = p->next;
	}
}

