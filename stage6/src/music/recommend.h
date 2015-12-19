#ifndef RECOMMEND_H
#define RECOMMEND_H
#include "loadFromHtml.h"
#include "BTree.h"
struct recommendResult
{
	int weigh;//比较权重
	CharString title;//推荐歌曲名
	int DocID;//歌曲序号
	recommendResult(){weigh = 0;DocID = 0; title = "";}
};
void recommendBatch(vector <MusicInfo> M, string infilename, string outfilename);

#endif