#ifndef LOADFROMHTML_H
#define LOADFROMHTML_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "stack.h"
#include <hash_map>
#include "CharString.h"
#include "CharStringLink.h"
#include "DocLink.h"
const int max_num = 500;
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
	CharString mostFrequentWord; //����Ƶ����ߵĵ���
	int frequence;//����Ƶ����ߵĵ��ʵĳ��ִ���
	int lines;  //�������
	hash_map <int, string> m_map;
	hash_map <int, string> useless_map;
	void extractMusicInfoFromPage(string inputname, MusicInfo &outputname);
	void initDictionaryInfo(string inputname);
	void initUselessDictionaryInfo(string inputname);
	void divideWords(CharStringLink &outputname);
	void divideWordsForinput(CharString inputstr,CharStringLink &outputname);//���û�������зִ�
	void clear();
};
class LoadFromHtml
{
public:
	LoadFromHtml(){};
	~LoadFromHtml();
	CharString tempContext[max_num];  //������ʱ��ţ��Ա�Ƚ�
	CharString infoNeededRaw[max_num];  //���ڴ洢��Ҫ�����Ĳ���(���ո�)
	CharString infoNeeded[max_num];

	void LoadData(string inputname); //����html��htmlcontext��
	void FindIndex();  //�ҵ���ʼ��ȡ�ı�ǩ
	void DeleteSpace();  //ɾ���ո��\t
	void htmlAnalysis();  //���ڽ�����ҳ
	void outPut(MusicInfo &outputname);  //��������õ�����Ϣ
	string htmlContext[max_num];  //���ڴ��html�ı�
	int strnum;
};


#endif 