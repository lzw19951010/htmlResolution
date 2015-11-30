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
	CharString tempContext[max_num];  //用于临时存放，以便比较
	CharString infoNeededRaw[max_num];  //用于存储需要解析的部分(含空格)
	CharString infoNeeded[max_num];

	void LoadData(string inputname); //加载html至htmlcontext中
	void FindIndex();  //找到开始提取的标签
	void DeleteSpace();  //删除空格和\t
	void htmlAnalysis();  //用于解析网页
	void outPut(string outputname);  //用于输出得到的信息
	char* htmlContext[max_num];  //用于存放html文本
	int strnum;
};

class MusicInfo
{
public:
	MusicInfo(){};
	~MusicInfo(){};

	CharString title;   //音乐名称
	CharString singer;   //歌手名称
	CharString album;   //专辑名称
	CharString publishdate;  //发行时间
	CharString lyricist;   //作词者
	CharString composer;   //作曲者
	CharString lyrics;   //所有歌词
	CharString info;  //信息
	int lines;  //歌词行数
	hash_map <int, string> m_map;
	void extractMusicInfoFromPage(string inputname, string outputname);
	void initDictionaryInfo(string inputname);
	void divideWords(string outputname);
	void clear();
};
#endif 