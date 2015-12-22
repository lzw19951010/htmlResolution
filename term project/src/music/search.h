#ifndef SEARCH_H
#define SEARCH_H
#include "loadFromHtml.h"
#include "BTree.h"

struct searchResult 
{
	int docID;
	int occurTimes;
	int numOfDF;//统计每个文档中出现的不同单词个数
	searchResult () {docID = 0;occurTimes = 0;numOfDF = 0;}//默认构造函数
};
void batchSearch(MusicInfo &M,B_Tree T, DocLink (doc)[10000], string infileName, string outfileName);//批量搜索，结果保存至外存中

#endif