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
//0λ������,10000������һ��magic number����ͳ�ƹ��Ժ�Ŷ��µ��ĵ������С
//�ĵ������Ե��ʵ�TermIDΪ�±꣬����
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
	cout << "����html�ļ���..." << endl;
	for (i = 0; i < files.size(); i++)
	{	
		//�����ļ����������ļ�
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
			//link��ÿһ��html�ļ��ķִʽ����info�Ǹ�����Ϣ
			//��ʼ���������ĵ�

			while (link.head)
			{
				keyType word(link.head->data,0,0,0);
				createInvertedIndex(T,word,doc,i+1,j,info[i+1]);
				link.head = link.head->next;
			}
		}	

	}
	cout << endl <<"������ϣ�" << endl;
	int taskId = 2; 
	switch (taskId){ 
	case 1: 
		batchSearch(music,T,doc,"query1.txt","result1.txt"); // �������� 
		break; 
	case 2: 
		recommendBatch(info,"query2.txt", "result2.txt");
		// �����Ƽ� 
		break; 
	case 3: 
		runGui();
		// �������� 
		break; 
	default: 
		break; 
	} 
	


	return 0;
}