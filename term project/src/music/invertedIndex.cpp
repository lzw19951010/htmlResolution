#include "invertedIndex.h"

void createInvertedIndex(B_Tree &T, keyType word, DocLink (&doc)[10000], int DocID, int &TermID, MusicInfo &M)
{
	//y用来保存B树查询结果

	node* y;
	int i;
	i = T.B_Tree_Search(T.root,word,y);

	if (i != 0)//如果找到了word
	{
		y->key[i].Occur++;
		DocNode* dn;
		if(doc[y->key[i].TermID].ListSearch(DocID,dn))
		//在已有的文档链表中先找一次，如果找到，则不用创建新的文档链表节点,在Doc【termID】(之前的ID)中寻找DOCID
		//找到了表示在改词已经在DocID文档中出现过了
		{
			dn->Times++;
			//寻找DocID中频率最高的单词
			if (dn->Times > M.frequence)
			{
				M.mostFrequentWord = word.Term;
				M.frequence = dn->Times;
			}
		}
		else//如果没找到，需要创建新的文档链表节点,并且将在不同文档中出现次数+1
		{
			doc[y->key[i].TermID].ListInsert(DocID,1);
			y->key[i].DF++;
		}

	}
	else//未找到word
	{
		word.TermID = TermID;
		word.Occur = 1;
		word.DF = 1;
		//初始化，并在B树种添加word
		T.B_Tree_Insert(word);
		//在相应的文档链表中插入
		doc[TermID].ListInsert(DocID,1);
		//单词对应的ID+1（找不到才加一，表示这一定是一个新的词，保证了ID与单词一一对应）
		//寻找频率最高的单词，若没找到那么出现次数肯定只有一次，故将已有的最高次数M.frequence和之比较
		if (M.frequence < 1)
		{
			M.mostFrequentWord = word.Term;
			M.frequence = 1;
		}
		TermID++;
	}
}