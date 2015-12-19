#include <iostream>
#include "DocLink.h"
using namespace std;
//析构函数
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
//默认构造函数
DocLink::DocLink()
{
	this->head = NULL;
	this->tail = NULL;
}
//初始化
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

//链表插入节点
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
//链表查找
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

