#include "BTree.h"
//����xΪ����������Ѱ�ҹؼ���Ϊk�Ľ�㣬���ҵ������������y�У��������ǵڼ����ؼ���
int B_Tree::B_Tree_Search(node *x, keyType k, node* &y)
{
	int i = 1;
	//�ҵ���һ���ؼ��ֲ�����k��i
	while(i <= x->n && k > x->key[i])
		i++;
	//��key[i] = k�����ҵ���
	if(i <= x->n && k == x->key[i])
	{
		//���������y��
		y = x;
		//�������ǵڼ����ؼ���
		return i;
	}
	//��û�ҵ����򷵻�0
	else if(x->leaf)
	{
		return 0;
	}
	else//���������������ң���ݹ���ҵ�i������
	return B_Tree_Search(x->child[i], k, y);
}
//����һ�ô������Ŀ���
void B_Tree::B_Tree_Create()
{
	//����һ�������
	//��ʼʱ�������ΪҶ�ӽ�㣬�������û�йؼ���
	root = new node(0, true);
}
//���ѣ���y����Ϊ������㣬ѡ������һ���ؼ��ֲ��뵽x�еĵ�i��λ��
void B_Tree::B_Tree_Split_Child(node *x, int i, node *y)
{
	int j;
	//����һ���½��z
	//Ҫ��y����Ϊy��z�����z��Ҷ��������y��ͬ
	//����ǰy��2t-1���ؼ��֣����Ѻ�ǰt-1������y����t-1������z���м��t������x
	node *z = new node(t-1, y->leaf);
	y->n = t - 1;
	//��t-1���ؼ������θ��Ƹ�z
	for(j = 1; j < t; j++)
		z->key[j] = y->key[j+t];
	//����к��ӣ�����ҲҪ���ƹ�ȥ��ԭ����2t��������ǰt������y����t������z
	if(y->leaf == false)
	{
		for(j = 1; j <= t; j++)
			z->child[j] = y->child[j+t];
	}
	//ʹz��Ϊx�ĵ�i+1������(y�Ѿ���x�ĵ�i������)
	for(j = x->n+1; j > i; j--)
		x->child[j+1] = x->child[j];
	x->child[i+1] = z;
	//��y�е�t���ؼ��ֲ��뵽x�ĵ�i��λ��
	for(j = x->n; j >= i; j--)
		x->key[j+1] = x->key[j];
	x->key[i] = y->key[t];
	//x�Ĺؼ���+1
	x->n++;
}
//���ؼ���k���뵽һ��δ���Ľ��x��
void B_Tree::B_Tree_Insert_Nonfull(node *x, keyType k)
{
	int i = x->n;
	//��x��Ҷ�ӽ��
	if(x->leaf)
	{
		//�ҵ��ò����λ��
		while(i >= 1 && k < x->key[i])
		{
			x->key[i+1] = x->key[i];
			i--;
		}
		//����ؼ���k
		x->key[i+1] = k;
		x->n++;
	}
	//������Ҷ�ӽ��
	else
	{
		//�ҵ��ò����λ��
		while(i >= 1 && k < x->key[i])
			i--;
		i++;
		//��ȡ�亢�ӣ����ؼ��ֲ��뵽���ĺ����У����������
		//��������
		if(x->child[i]->n == 2 * t - 1)
		{
			//�Ժ���ִ�з��Ѳ��������Ѻ󣬺��Ӳ���Ϊ����
			B_Tree_Split_Child(x, i, x->child[i]);
			if(k > x->key[i])
				i++;
		}
		//���Ӳ�����ֱ�ӶԺ��ӽ��в������
		B_Tree_Insert_Nonfull(x->child[i], k);
	}
}
//��T�в���ؼ���k
void B_Tree::B_Tree_Insert(keyType k)
{
	node *r = root;
	//�����������
	if(r->n == 2*t-1)
	{
		//����һ���µĽ��,���µĽ����Ϊ�����
		root = new node(0, false);
		root->child[1] = r;
		//��ԭ��������Ϊ������㣬�ֱ���Ϊs�ĵ�0�����Ӻ͵�1������
		B_Tree_Split_Child(root, 1, r);
		//�ѹؼ���k���뵽������У���ʱ�����һ������
		B_Tree_Insert_Nonfull(root, k);
	}
	//������㲻��
	else
		//ֱ�Ӱѹؼ��ֲ��뵽�������
		B_Tree_Insert_Nonfull(r, k);
}