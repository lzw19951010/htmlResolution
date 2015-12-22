#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H

#include "CharString.h"
#include <fstream>
struct CSLnode
{
	CharString data;
	CSLnode *next;
};
class CharStringLink
{
public:
	CharStringLink(){}; //���캯��
	~CharStringLink();  //��������



	void InitList();
	void ListInsert(CharString element);
	bool isEmpty();
	void print_list(CSLnode *head, string outputname);

	CSLnode* head;
	CSLnode* tail;
	int m_size; // count
};




#endif