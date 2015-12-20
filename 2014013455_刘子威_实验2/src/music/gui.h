#ifndef GUI_H
#define GUI_H
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<windows.h>
using namespace std;
#include "loadFromHtml.h"
#include "BTree.h"

extern MusicInfo music;
extern DocLink doc[10000];
extern vector <MusicInfo> info;
extern B_Tree T;

void recommendBatchInGui(vector <MusicInfo> M, string infilename);

void batchSearchInGui(MusicInfo &M,B_Tree T, DocLink (doc)[10000], string infileName);//批量搜索，结果保存至外存中

void Welcome();
void menu();
void End();
void Close();
void end_round();
void runGui();

#endif