#ifndef SEARCH_H
#define SEARCH_H
#include "loadFromHtml.h"
#include "BTree.h"

struct searchResult 
{
	int docID;
	int occurTimes;
	int numOfDF;//ͳ��ÿ���ĵ��г��ֵĲ�ͬ���ʸ���
	searchResult () {docID = 0;occurTimes = 0;numOfDF = 0;}//Ĭ�Ϲ��캯��
};
void batchSearch(MusicInfo &M,B_Tree T, DocLink (doc)[10000], string infileName, string outfileName);//������������������������

#endif