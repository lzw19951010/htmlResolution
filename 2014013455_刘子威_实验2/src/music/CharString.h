#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class CharString
{
public:
	CharString(void);//�ճ�ʼ��
	CharString(const char* input);//��ʼ��Ϊ������ַ���
	CharString(const CharString & S);//���ƹ���
	~CharString(void);//��������


	int length();//�����ַ�������
	bool empty();// �ж��ַ����Ƿ�Ϊ��
	void swap(CharString& from);// �����ַ���
	int firstIndexOf(CharString X);  //Ѱ��ĳһ�ض��ַ���
	CharString substr(int index, int length);// �����Ӵ�


	friend ostream& operator << (ostream & OS,const CharString &S);// ����<<
	friend istream& operator >> (istream & IS,CharString &S);//�������������벢��������
	friend  bool operator == (const CharString& S1, const CharString & S2);//�ж��Ƿ����
	char& operator[](int);              //operator[]  
	CharString& operator = (const CharString& S);//operator=
	CharString& operator = (const char* input);
	CharString operator + (const CharString &other)const;  //operator+
	CharString& operator = (string input);
	bool operator < (const CharString S);
	bool operator > (const CharString S);
	string fromCharStoString();
	void DeleteString(CharString &X);  //ɾ���ַ�����ָ���ַ���

	char* m_string;
	int m_length; //�ܳ���
};

#endif