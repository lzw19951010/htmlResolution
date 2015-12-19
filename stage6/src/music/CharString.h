#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class CharString
{
public:
	CharString(void);//空初始化
	CharString(const char* input);//初始化为输入的字符串
	CharString(const CharString & S);//复制构造
	~CharString(void);//析构函数


	int length();//返回字符串长度
	bool empty();// 判断字符串是否为空
	void swap(CharString& from);// 交换字符串
	int firstIndexOf(CharString X);  //寻找某一特定字符串
	CharString substr(int index, int length);// 返回子串


	friend ostream& operator << (ostream & OS,const CharString &S);// 重载<<
	friend istream& operator >> (istream & IS,CharString &S);//输入流接受输入并创建对象
	friend  bool operator == (const CharString& S1, const CharString & S2);//判断是否相等
	char& operator[](int);              //operator[]  
	CharString& operator = (const CharString& S);//operator=
	CharString& operator = (const char* input);
	CharString operator + (const CharString &other)const;  //operator+
	CharString& operator = (string input);
	bool operator < (const CharString S);
	bool operator > (const CharString S);
	string fromCharStoString();
	void DeleteString(CharString &X);  //删除字符串中指定字符串

	char* m_string;
	int m_length; //总长度
};

#endif