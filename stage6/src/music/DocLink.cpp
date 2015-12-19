#include <iostream>
#include "DocLink.h"
using namespace std;
//��������
DocLink::~DocLink()
{
	DocNode *p = head;
	DocNode *q = head;
	while(p)
	{
		q = p;
		p = p->next;
		delete q;
	}
}
//Ĭ�Ϲ��캯��
DocLink::DocLink()
{
	this->head = NULL;
	this->tail = NULL;
}
//��ʼ��
void DocLink::InitList()  //
{
	DocNode *p = head;
	DocNode *q = head;
	while(p)
	{
		q = p;
		p = p->next;
		delete q;
	}
	this->head = NULL;
	this->tail = NULL;
}

//�������ڵ�
void DocLink::ListInsert(int docID, int times)
{	

	DocNode *p1;
	p1=new DocNode();
	p1->DocID = docID;
	p1->Times = times;
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
//�������
int DocLink::ListSearch(int _docID, DocNode* &p)
{
	if (head == NULL)
	{
		return 0;
	}
	p = head;
	while(p)
	{
		if (p->DocID == _docID)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

