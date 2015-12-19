#include "BTree.h"
//从以x为根结点的树中寻找关键字为k的结点，若找到，将结果存入y中，返回其是第几个关键字
int B_Tree::B_Tree_Search(node *x, keyType k, node* &y)
{
	int i = 1;
	//找到第一个关键字不大于k的i
	while(i <= x->n && k > x->key[i])
		i++;
	//若key[i] = k，则找到了
	if(i <= x->n && k == x->key[i])
	{
		//将结果存入y中
		y = x;
		//返回其是第几个关键字
		return i;
	}
	//若没找到，则返回0
	else if(x->leaf)
	{
		return 0;
	}
	else//若还有子树可以找，则递归查找第i个子树
	return B_Tree_Search(x->child[i], k, y);
}
//构造一棵带树结点的空树
void B_Tree::B_Tree_Create()
{
	//生成一个根结点
	//初始时，根结点为叶子结点，根结点中没有关键字
	root = new node(0, true);
}
//分裂，把y分裂为两个结点，选择其中一个关键字插入到x中的第i个位置
void B_Tree::B_Tree_Split_Child(node *x, int i, node *y)
{
	int j;
	//生成一个新结点z
	//要把y分裂为y和z，因此z的叶子属性与y相同
	//分裂前y有2t-1个关键字，分裂后前t-1个属于y，后t-1个属于z，中间第t个属于x
	node *z = new node(t-1, y->leaf);
	y->n = t - 1;
	//后t-1个关键字依次复制给z
	for(j = 1; j < t; j++)
		z->key[j] = y->key[j+t];
	//如果有孩子，孩子也要复制过去，原来有2t个子树，前t个属于y，后t个属于z
	if(y->leaf == false)
	{
		for(j = 1; j <= t; j++)
			z->child[j] = y->child[j+t];
	}
	//使z作为x的第i+1个孩子(y已经是x的第i个孩子)
	for(j = x->n+1; j > i; j--)
		x->child[j+1] = x->child[j];
	x->child[i+1] = z;
	//把y中第t个关键字插入到x的第i个位置
	for(j = x->n; j >= i; j--)
		x->key[j+1] = x->key[j];
	x->key[i] = y->key[t];
	//x的关键字+1
	x->n++;
}
//将关键字k插入到一个未满的结点x中
void B_Tree::B_Tree_Insert_Nonfull(node *x, keyType k)
{
	int i = x->n;
	//若x是叶子结点
	if(x->leaf)
	{
		//找到该插入的位置
		while(i >= 1 && k < x->key[i])
		{
			x->key[i+1] = x->key[i];
			i--;
		}
		//插入关键字k
		x->key[i+1] = k;
		x->n++;
	}
	//若不是叶子结点
	else
	{
		//找到该插入的位置
		while(i >= 1 && k < x->key[i])
			i--;
		i++;
		//读取其孩子，将关键字插入到它的孩子中，分两种情况
		//孩子已满
		if(x->child[i]->n == 2 * t - 1)
		{
			//对孩子执行分裂操作，分裂后，孩子不变为不满
			B_Tree_Split_Child(x, i, x->child[i]);
			if(k > x->key[i])
				i++;
		}
		//孩子不满，直接对孩子进行插入操作
		B_Tree_Insert_Nonfull(x->child[i], k);
	}
}
//向T中插入关键字k
void B_Tree::B_Tree_Insert(keyType k)
{
	node *r = root;
	//若根结点已满
	if(r->n == 2*t-1)
	{
		//申请一个新的结点,将新的结点作为根结点
		root = new node(0, false);
		root->child[1] = r;
		//将原根结点分裂为两个结点，分别作为s的第0个孩子和第1个孩子
		B_Tree_Split_Child(root, 1, r);
		//把关键字k插入到根结点中，此时根结点一定不满
		B_Tree_Insert_Nonfull(root, k);
	}
	//若根结点不满
	else
		//直接把关键字插入到根结点中
		B_Tree_Insert_Nonfull(r, k);
}