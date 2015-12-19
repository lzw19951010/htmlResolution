#include <iostream>
#include "CharString.h"
#include "CharStringLink.h"
using namespace std;

CharStringLink::~CharStringLink()
{
	CSLnode *p = head;
	CSLnode *q = head;
	while(p)
	{
		q = p;
		p = p->next;
		delete q;
	}
}
void CharStringLink::InitList()  //
{
	CSLnode *p = head;
	CSLnode *q = head;
	while(p)
	{
		q = p;
		p = p->next;
		delete q;
	}
	this->m_size = 0;
	this->head = NULL;
	this->tail = NULL;
}

bool CharStringLink::isEmpty()
{
	return m_size == 0;
}


void CharStringLink::ListInsert(CharString element)
{	

	CSLnode *p1;
	p1=new CSLnode();
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

void CharStringLink::print_list(CSLnode *head, string outputname)
{
	ofstream output(outputname);
	CSLnode *p = head;
	while(p)
	{
		output << p->data <<endl;
		p = p->next;
	}
}

