#ifndef  BTREE_H
#define  BTREE_H
#include "loadFromHtml.h"
#include <iostream>
using namespace std;

const int t = 3; //最小度数
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
	//构造函数
	keyType(){Term = "";TermID = 0; DF = 0; Occur = 0;}
	keyType(CharString _Term, int _TermID, int _DF, int _Occur):Term(_Term),TermID(_TermID),DF(_DF),Occur(_Occur){}
}keyType; 

//B树结点结构
struct node
{
	int n;//存储在结点x中的关键字数
	keyType key[N];//关键字，以非降序存放
	bool leaf;//TRUE:x是叶子；FALSE:x是内结点
	node *child[N+1];//指向其n+1个孩子的指针
	//构造函数
	node(){};
	node(int num, bool IsLeaf):n(num),leaf(IsLeaf){}
};
//B树结构
class B_Tree
{
public:
	//指向根结点
	node *root;
	B_Tree():root(NULL){}

	//从以x为根结点的树中寻找关键字为k的结点，若找到，将结果存入y中，返回其是第几个关键字
	int B_Tree_Search(node *x, keyType k, node* &y);

	//构造一棵带树结点的空树
	void B_Tree_Create();

	//分裂，把y分裂为两个结点，选择其中一个关键字插入到x中的第i个位置
	void B_Tree_Split_Child(node *x, int i, node *y);

	//将关键字k插入到一个未满的结点x中
	void B_Tree_Insert_Nonfull(node *x, keyType k);

	//向T中插入关键字k
	void B_Tree_Insert(keyType k);
};



#endif
