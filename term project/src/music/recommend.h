#ifndef RECOMMEND_H
#define RECOMMEND_H
#include "loadFromHtml.h"
#include "BTree.h"
struct recommendResult
{
	int weigh;//�Ƚ�Ȩ��
	CharString title;//�Ƽ�������
	int DocID;//�������
	recommendResult(){weigh = 0;DocID = 0; title = "";}
};
void recommendBatch(vector <MusicInfo> M, string infilename, string outfilename);

#endif