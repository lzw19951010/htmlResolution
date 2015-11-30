#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H

#include "CharString.h"
#include <fstream>

class CharStringLink
{
public:
	CharStringLink(){};
	~CharStringLink(){};

	struct node
	{
		CharString data;
		node *next;
	};

	void InitList();
	void ListInsert(CharString element);
	bool isEmpty();
	void print_list(node *head, string outputname);
	CharString ListSearch(CharString element);

	node* head;
	node* tail;
	int m_size; // count
};




#endif