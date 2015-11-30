#include "CharString.h"
# include <iostream>
using namespace std;

CharString::CharString()
{
	m_length = 1;
	m_string = new char[m_length];
	m_string[m_length-1] = '\0';
}

CharString::CharString(const char *input)
{
	m_length = strlen(input)+1 ;
	m_string = new char[m_length];
	for(int i = 0; i < (m_length - 1); i++)
	{
		m_string[i] = input[i];
	}
	m_string[(m_length-1)] = '\0';
}

CharString::CharString(const CharString& S)
{
	m_length = S.m_length;
	m_string = new char[m_length];
	for(int i = 0; i < (m_length - 1); i++)
	{
		m_string[i] = S.m_string[i];
	}

	if(m_string[m_length - 1] != '\0'){m_string[m_length -1] = '\0';}
}

CharString::~CharString()
{
	delete[] m_string;
}

int CharString::length()
{
	int i = 0;
	while(m_string[i] != '\0')
	{
		i++;
	}
	return i;
}

bool CharString::empty()
{
	if(m_string[0] == NULL && m_length == 1)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void CharString::swap(CharString &from)
{
	int lena = m_length;
	int lenb = from.m_length;
	char *temp1 = new char[lena];
	char *temp2 = new char[lenb];

	for(int i = 0; i < (lena- 1); i++)
	{
		temp1[i] = m_string[i];
	}
	if(temp1[lena - 1] != '\0')
	{
		temp1[lena -1] = '\0';
	}

	for(int j = 0; j < (lenb- 1); j++)
	{
		temp2[j] = from.m_string[j];
	}
	if(temp2[lenb - 1] != '\0'){temp2[lenb -1] = '\0';}

	delete[] m_string;
	delete[]from.m_string;

	m_string = new char[lenb];
	m_length = lenb;
	from.m_string = new char[lena];
	from.m_length = lena;

	for(int k = 0; k < (lenb - 1); k++)
	{
		m_string[k] = temp2[k];
	}
	if(m_string[lenb -1] != '\0'){m_string[lenb - 1] = '\0';}

	for(int l = 0; l < (lena - 1); l++)
	{
		from.m_string[l] = temp1[l];
	}
	if(from.m_string[lena -1] != '\0'){from.m_string[lena-1] = '\0';}

	delete[]temp1; 
	delete[]temp2;
}

CharString CharString::substr(int index, int length)
{
	int size = length+1;
	char* temp = new char[size];
	int j = 0;
	for(int i = index, j = 0; i <  size + index; i++, j++)
	{
		temp[j] = m_string[i];
	}
	if(temp[size -1 ] != '\0')
	{
		temp[size -1] = '\0';
	}


	CharString RET;
	RET.m_length = size;
	delete[]RET.m_string;
	RET.m_string = new char[size];
	for(int m = 0; m < (size - 1);m++)
	{
		RET.m_string[m] = temp[m];
	}

	if(RET.m_string[size-1] != '\0'){RET.m_string[size-1] = '\0';}
	return RET; 
	delete[]temp;
}

bool operator == (const CharString & S1, const CharString & S2)
{
	if(S1.m_length == S2.m_length)
	{
		int counter = S1.m_length;
		int flag = 0;
		int i = 0;
		while(i != counter)
		{
			if(S1.m_string[i] != S2.m_string[i])
			{
				flag = 1;
				break;
			}
			i++;
		}
		if(flag != 0) 
		{
			return false;
		}
		else
		{
			return true;
		}		
	}
	else 
	{
		return false;
	}

}

ostream& operator <<(ostream & OS, const CharString& S)
{
	OS << S.m_string;
	return OS;
}

istream& operator >>(istream & IS, CharString& S)
{
	char temp[255]; //用于存储输入流  
	IS >> temp;  
	S = temp; //使用赋值运算符  
	return IS; //使用return可以支持连续使用>>运算符 
}

CharString& CharString::operator = (const CharString &S)
{
	m_length = S.m_length;
	delete[] m_string;
	m_string = new char[m_length];
	for(int i = 0 ; i < (m_length -1);i++)
	{
		m_string[i] = S.m_string[i];
	}
	m_string[(m_length -1)] = '\0';
	return *this;
}
CharString& CharString::operator = (const char* input)
{
	m_length = strlen(input)+1 ;
	m_string = new char[m_length];
	for(int i = 0; i < (m_length - 1); i++)
	{
		m_string[i] = input[i];
	}
	m_string[(m_length-1)] = '\0';
	return *this;
}
CharString CharString::operator +(const CharString&other)const  
{  
	CharString newString;  
	if(!other.m_string)  
		newString = *this;  
	else if(!m_string)  
		newString = other;  
	else  
	{  
		newString.m_length = m_length + other.m_length - 1;
		newString.m_string = new char[newString.m_length];  
		for(int i = 0 ; i < m_length - 1;i++)
		{
			newString.m_string[i] = m_string[i];
		}
		for(int i = m_length - 1 ; i < newString.m_length - 1; i++)
		{
			newString.m_string[i] = other.m_string[i + 1 - m_length];
		}
		newString.m_string[newString.m_length - 1] = '/0';
	}  
	return newString;  
} 

char& CharString::operator[](int e)  
{  
	if (e>=0 && e<m_length)
		return m_string[e];  
}  

int CharString::firstIndexOf(CharString X)
{

		int lenA = this->length();
		int lenB = X.length();
		int i = 0, j = 0;
		while(i < lenA && j < lenB)
		{
			if (m_string[i] == X.m_string[j])
			{
				i++;
				j++;
			}
			else
			{
				i = i - j + 1;
				j = 0;
			}
		}
		if (j >= lenB)
			return i - lenB;
		else
			return -1; //匹配不成功
}
void CharString::DeleteString(CharString &X)
{
	int start = this->firstIndexOf(X);
	if (start == -1)
	{
		return;
	}
	int i;
	for (i = start; i <= this->length() - X.length(); i++)
	{
		m_string[i] = m_string[i + X.length()];
	}
	m_string[i] = '\0';
}

string CharString::fromCharStoString()
{
	string str = "";
	int i = 0;
	while(m_string[i] != '\0')
	{
		str = str + m_string[i];
		i++;
	}
	return str;
}