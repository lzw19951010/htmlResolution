#ifndef  BTREE_H
#define  BTREE_H
#include "loadFromHtml.h"
#include <iostream>
using namespace std;

const int t = 3; //��С����
const int N = 6;
typedef struct keyType
{
	CharString Term;
	int TermID;
	int DF;
	int Occur;
	keyType& operator=(keyType& value)
	{
		Term = value.Term;
		TermID = value.TermID;
		DF = value.DF;
		Occur = value.Occur;
		return *this;
	}
	bool operator==(keyType& rhs)
	{
		return (Term == rhs.Term);
	}
	bool operator<(keyType& rhs)
	{
		return (Term < rhs.Term);
	}
	bool operator>(keyType& rhs)
	{
		return (Term > rhs.Term);
	}
	//���캯��
	keyType(){Term = "";TermID = 0; DF = 0; Occur = 0;}
	keyType(CharString _Term, int _TermID, int _DF, int _Occur):Term(_Term),TermID(_TermID),DF(_DF),Occur(_Occur){}
}keyType; 

//B�����ṹ
struct node
{
	int n;//�洢�ڽ��x�еĹؼ�����
	keyType key[N];//�ؼ��֣��Էǽ�����
	bool leaf;//TRUE:x��Ҷ�ӣ�FALSE:x���ڽ��
	node *child[N+1];//ָ����n+1�����ӵ�ָ��
	//���캯��
	node(){};
	node(int num, bool IsLeaf):n(num),leaf(IsLeaf){}
};
//B���ṹ
class B_Tree
{
public:
	//ָ������
	node *root;
	B_Tree():root(NULL){}

	//����xΪ����������Ѱ�ҹؼ���Ϊk�Ľ�㣬���ҵ������������y�У��������ǵڼ����ؼ���
	int B_Tree_Search(node *x, keyType k, node* &y);

	//����һ�ô������Ŀ���
	void B_Tree_Create();

	//���ѣ���y����Ϊ������㣬ѡ������һ���ؼ��ֲ��뵽x�еĵ�i��λ��
	void B_Tree_Split_Child(node *x, int i, node *y);

	//���ؼ���k���뵽һ��δ���Ľ��x��
	void B_Tree_Insert_Nonfull(node *x, keyType k);

	//��T�в���ؼ���k
	void B_Tree_Insert(keyType k);
};



#endif
