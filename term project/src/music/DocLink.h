#ifndef DOCLINK_H
#define DOCLINK_H

struct DocNode
{
	int  DocID;             // 文档ID
	int  Times;				// 单词在该文档中出现的次数
	DocNode *next;
};
class DocLink
{
	
public:


	DocNode* head;
	DocNode* tail;

	DocLink( );
	~DocLink( );

	void InitList();
	void ListInsert(int docID, int times);
	int ListSearch(int _docID, DocNode* &p);
}; // 类DocLink定义结束



#endif