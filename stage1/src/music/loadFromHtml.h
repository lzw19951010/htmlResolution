#ifndef LOADFROMHTML_H
#define LOADFROMHTML_H
#include <string>
#include <iostream>
#include <fstream>
#include "stack.h"
#include <hash_map>
#include "CharString.h"
#include "CharStringLink.h"
const int max_num = 500;

class LoadFromHtml
{
public:
	LoadFromHtml(){};
	~LoadFromHtml(){};
	CharString tempContext[max_num];  //������ʱ��ţ��Ա�Ƚ�
	CharString infoNeededRaw[max_num];  //���ڴ洢��Ҫ�����Ĳ���(���ո�)
	CharString infoNeeded[max_num];

	void LoadData(string inputname); //����html��htmlcontext��
	void FindIndex();  //�ҵ���ʼ��ȡ�ı�ǩ
	void DeleteSpace();  //ɾ���ո��\t
	void htmlAnalysis();  //���ڽ�����ҳ
	void outPut(string outputname);  //��������õ�����Ϣ
	char* htmlContext[max_num];  //���ڴ��html�ı�
	int strnum;
};

class MusicInfo
{
public:
	MusicInfo(){};
	~MusicInfo(){};

	CharString title;   //��������
	CharString singer;   //��������
	CharString album;   //ר������
	CharString publishdate;  //����ʱ��
	CharString lyricist;   //������
	CharString composer;   //������
	CharString lyrics;   //���и��
	CharString info;  //��Ϣ
	int lines;  //�������
	hash_map <int, string> m_map;
	void extractMusicInfoFromPage(string inputname, string outputname);
	void initDictionaryInfo(string inputname);
	void divideWords(string outputname);
	void clear();
};
#endif 