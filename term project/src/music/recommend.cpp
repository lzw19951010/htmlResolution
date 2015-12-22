#include "recommend.h"
#include <algorithm>
bool SortByM1( const recommendResult &v1, const recommendResult &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.weigh > v2.weigh;//��������  
} 

void recommendBatch(vector <MusicInfo> M,string infilename, string outfilename)
{
	//Ȩֵ�ļ����ۺ��˸���4������3������3��ר��5�����������Ĵ�2�����ֱַ�Ϊ��ռȨ��
	cout << "��ʼ���ļ�"<< infilename<<"�������Ƽ���"<< endl;
	ifstream infile(infilename);
	ofstream outfile(outfilename);
	string line;//����ÿ����Ϣ
	vector <recommendResult> recommends(301);
	recommendResult temprst;
	CharString inputstr;
	int TermID;
	DocNode* p = NULL;
	int i,j;
	int isFound;
	vector <MusicInfo> infoFrominput;//���û�����õ��Ķ�Ӧ�����б�

	

	while (!infile.eof())
	{
		getline(infile,line);
		inputstr = line;
		isFound = 0;
		infoFrominput.clear();
		for (i = 1; i < M.size(); i++)
		{
			if (M[i].title.firstIndexOf(inputstr) >= 0)//���ȶԸ���������й���
			{
				isFound = 1;
				infoFrominput.push_back(M[i]);
			}
		}
		if (isFound)
		{
			outfile << "�����������롰" << line << "���������ҵ�" << infoFrominput.size()<<"�׶�Ӧ�ĸ�����"<<endl;
			for (i = 0; i < infoFrominput.size(); i++)
			{
				outfile <<"������"<<infoFrominput[i].title<<"�����Ƽ�������£�"<< endl;
				recommends.resize(301);
				for (j = 1; j < M.size(); j++)
				{
					if (M[j].album == infoFrominput[i].album)
					{
						recommends[j].weigh+=5;//ͬר��Ȩ�����
					}
					if (M[j].singer == infoFrominput[i].singer)
					{
						recommends[j].weigh+=4;//ͬ����Ȩ�����
					}
					//��������Ȩ��һ������֮
					if (M[j].lyricist == infoFrominput[i].lyricist)
					{
						recommends[j].weigh+=3;
					}
					if (M[j].lyrics == infoFrominput[i].lyrics)
					{
						recommends[j].weigh+=3;
					}
					//�������Ĵ�Ȩ�����٣���Ϊ�����Ƚ�С
					if (M[j].mostFrequentWord == infoFrominput[i].mostFrequentWord)
					{
						recommends[j].weigh+=3;
					}
					recommends[j].DocID = j;
					recommends[j].title = M[j].title;
				}
				//��Ȩֵ��������,ȡǰ����
				sort(recommends.begin(),recommends.end(),SortByM1);
				for (j = 1; j < 11; j++)
				{
					outfile << "(" <<recommends[j].DocID << "," << recommends[j].title << ")";
					if (j <= 9)
					{
						outfile << ",";
					}
				}
				outfile <<endl;
				if (i == infoFrominput.size() - 1)
				{
					outfile << endl;
				}
			}
			recommends.clear();
		}
		else
		{
			outfile << "��Ǹ��δ���������ҵ���" <<inputstr<< "����Ӧ�ĸ��� ��" << endl;
		}

	}

	cout << "�����Ƽ���ϣ������Ѿ�������" <<outfilename <<"�У�"<< endl;
}