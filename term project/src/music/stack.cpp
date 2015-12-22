#include "stack.h"

stack::stack() 
{
	// init
	this->m_size = 0;
	this->head = NULL;
}

void stack::init()  //
{
	this->m_size = 0;
	this->head = NULL;
}
void stack::clear()
{
	node *p;
	while (this->head)
	{
		p = this->head;
		this->head = p->next;
		free(p);
		--m_size;
	}
}
void stack::push(const CharString& element)
{
	node *oldHead = this->head;
	this->head = new node();
	this->head->val = new CharString(element);
	this->head->next = oldHead;
	++m_size;
}

CharString stack::pop() 
{
	if (this->isEmpty()) 
	{
		throw "empty stack";
	}

	const CharString *retPtr = this->head->val;
	node *newHead = this->head->next;
	delete this->head;
	this->head = newHead;
	--m_size;
	return *retPtr;
}

CharString stack::top() 
{
	if (this->isEmpty()) {
		throw "empty stack";
	}

	const CharString *retPtr = this->head->val;
	return *retPtr;
}


bool stack::isEmpty() 
{
	return m_size == 0;
}

int stack::size() 
{
	return m_size;
}

