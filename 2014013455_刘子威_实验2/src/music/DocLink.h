#ifndef DOCLINK_H
#define DOCLINK_H

struct DocNode
{
	int  DocID;             // �ĵ�ID
	int  Times;				// �����ڸ��ĵ��г��ֵĴ���
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
}; // ��DocLink�������



#endif