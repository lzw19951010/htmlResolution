/*
Developer:
Lawrence Liu
Software engineering
Tsinghua University

ALL RIGHTS RESERVED
*/

#include <iostream>
#include "loadFromHtml.h"
#include <io.h>
#include <vector>
#include "BTree.h"
#include "invertedIndex.h"
#include "DocLink.h"
#include "search.h"
#include "recommend.h"
#include "gui.h"
using namespace std;
MusicInfo music;
DocLink doc[10000];
//0位置闲置,10000并不是一个magic number，是统计过以后才定下的文档链表大小
//文档链表以单词的TermID为下标，储存
B_Tree T;
vector<MusicInfo> info(301);
void getFiles( string path, vector<string>& files ) 
{  
    long   hFile   =   0;    
    struct _finddata_t fileinfo;    
    string p;  
    if   ((hFile   =   _findfirst(p.assign(path).append("/*").c_str(),&fileinfo))   !=   -1)  {    
  
        do  {    
            if   ((fileinfo.attrib   &   _A_SUBDIR)) {    
                if   (strcmp(fileinfo.name,".")   !=   0   &&   strcmp(fileinfo.name,"..")   !=   0)    
                    getFiles(   p.assign(path).append("/").append(fileinfo.name), files   );    
            }  else  {    
                files.push_back(p.assign(fileinfo.name));  
            }    
        }   while   (_findnext(   hFile,   &fileinfo   )   ==   0);    
  
        _findclose(hFile);    
    }  
} 
int main()
{	
	int i;
	vector <string> files;
	string dicPath, inputPath, outputPath,outputPath1, outputPath2, out1, out2, tempstr, input;
	string uselessdicPath;
	out1 = ".info";
	out2 = ".txt";
	
	dicPath = ".\\dic\\dictionary.dic";
	uselessdicPath = ".\\dic\\useless.dic";
	music.initDictionaryInfo(dicPath);
	music.initUselessDictionaryInfo(uselessdicPath);
	inputPath = ".\\pages_300";
	outputPath = ".\\output";
	getFiles(inputPath, files);
	CharStringLink link;
	CharString title[301];
	T.B_Tree_Create();

	int j = 1;
	cout << "解析html文件中..." << endl;
	for (i = 0; i < files.size(); i++)
	{	
		//遍历文件夹内所有文件
		if (files[i].substr(files[i].size() - 5, 5) == ".html")
		{
			input = inputPath + "\\" + files[i];
			tempstr = files[i].erase(files[i].size() - 5, 5);
			outputPath1 = outputPath + "\\" + tempstr + out1;
			outputPath2 = outputPath + "\\" + tempstr + out2;
			
			music.extractMusicInfoFromPage(input, info[i+1]);
			if (i+1 < 10)
				cout << "\b\b";
			else 
				cout << "\b\b\b";
			cout << (i+1)/3 << "%";
			info[i+1].frequence = 0;
			music.divideWords(link);
			//link是每一个html文件的分词结果，info是歌曲信息
			//开始构建倒排文档

			while (link.head)
			{
				keyType word(link.head->data,0,0,0);
				createInvertedIndex(T,word,doc,i+1,j,info[i+1]);
				link.head = link.head->next;
			}
		}	

	}
	cout << endl <<"解析完毕！" << endl;
	int taskId = 2; 
	switch (taskId){ 
	case 1: 
		batchSearch(music,T,doc,"query1.txt","result1.txt"); // 批量搜索 
		break; 
	case 2: 
		recommendBatch(info,"query2.txt", "result2.txt");
		// 批量推荐 
		break; 
	case 3: 
		runGui();
		// 交互界面 
		break; 
	default: 
		break; 
	} 
	


	return 0;
}