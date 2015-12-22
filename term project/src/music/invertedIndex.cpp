#include "invertedIndex.h"

void createInvertedIndex(B_Tree &T, keyType word, DocLink (&doc)[10000], int DocID, int &TermID, MusicInfo &M)
{
	//y��������B����ѯ���

	node* y;
	int i;
	i = T.B_Tree_Search(T.root,word,y);

	if (i != 0)//����ҵ���word
	{
		y->key[i].Occur++;
		DocNode* dn;
		if(doc[y->key[i].TermID].ListSearch(DocID,dn))
		//�����е��ĵ�����������һ�Σ�����ҵ������ô����µ��ĵ�����ڵ�,��Doc��termID��(֮ǰ��ID)��Ѱ��DOCID
		//�ҵ��˱�ʾ�ڸĴ��Ѿ���DocID�ĵ��г��ֹ���
		{
			dn->Times++;
			//Ѱ��DocID��Ƶ����ߵĵ���
			if (dn->Times > M.frequence)
			{
				M.mostFrequentWord = word.Term;
				M.frequence = dn->Times;
			}
		}
		else//���û�ҵ�����Ҫ�����µ��ĵ�����ڵ�,���ҽ��ڲ�ͬ�ĵ��г��ִ���+1
		{
			doc[y->key[i].TermID].ListInsert(DocID,1);
			y->key[i].DF++;
		}

	}
	else//δ�ҵ�word
	{
		word.TermID = TermID;
		word.Occur = 1;
		word.DF = 1;
		//��ʼ��������B�������word
		T.B_Tree_Insert(word);
		//����Ӧ���ĵ������в���
		doc[TermID].ListInsert(DocID,1);
		//���ʶ�Ӧ��ID+1���Ҳ����ż�һ����ʾ��һ����һ���µĴʣ���֤��ID�뵥��һһ��Ӧ��
		//Ѱ��Ƶ����ߵĵ��ʣ���û�ҵ���ô���ִ����϶�ֻ��һ�Σ��ʽ����е���ߴ���M.frequence��֮�Ƚ�
		if (M.frequence < 1)
		{
			M.mostFrequentWord = word.Term;
			M.frequence = 1;
		}
		TermID++;
	}
}