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

	CharString title;   //音乐名称
	CharString singer;   //歌手名称
	CharString album;   //专辑名称
	CharString publishdate;  //发行时间
	CharString lyricist;   //作词者
	CharString composer;   //作曲者
	CharString lyrics;   //所有歌词
	CharString info;  //信息
	CharString mostFrequentWord; //出现频率最高的单词
	int frequence;//出现频率最高的单词的出现次数
	int lines;  //歌词行数
	hash_map <int, string> m_map;
	hash_map <int, string> useless_map;
	void extractMusicInfoFromPage(string inputname, MusicInfo &outputname);
	void initDictionaryInfo(string inputname);
	void initUselessDictionaryInfo(string inputname);
	void divideWords(CharStringLink &outputname);
	void divideWordsForinput(CharString inputstr,CharStringLink &outputname);//对用户输入进行分词
	void clear();
};
class LoadFromHtml
{
public:
	LoadFromHtml(){};
	~LoadFromHtml();
	CharString tempContext[max_num];  //用于临时存放，以便比较
	CharString infoNeededRaw[max_num];  //用于存储需要解析的部分(含空格)
	CharString infoNeeded[max_num];

	void LoadData(string inputname); //加载html至htmlcontext中
	void FindIndex();  //找到开始提取的标签
	void DeleteSpace();  //删除空格和\t
	void htmlAnalysis();  //用于解析网页
	void outPut(MusicInfo &outputname);  //用于输出得到的信息
	string htmlContext[max_num];  //用于存放html文本
	int strnum;
};


#endif 