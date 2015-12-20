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
	CharStringLink(){}; //构造函数
	~CharStringLink();  //析构函数



	void InitList();
	void ListInsert(CharString element);
	bool isEmpty();
	void print_list(CSLnode *head, string outputname);

	CSLnode* head;
	CSLnode* tail;
	int m_size; // count
};




#endif