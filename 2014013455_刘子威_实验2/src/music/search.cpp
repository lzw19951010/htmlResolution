#include "search.h"
#include <algorithm>
bool SortByM1( const searchResult &v1, const searchResult &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.numOfDF > v2.numOfDF;//��������  
}  
void batchSearch(MusicInfo &M,B_Tree T, DocLink (doc)[10000], string infileName, string outfileName)
{
	cout << "��ʼ���ļ�"<< infileName<<"������������"<< endl;
	ifstream infile(infileName);
	ofstream outfile(outfileName);
	string line;//����ÿ����Ϣ
	vector <searchResult> searchRst;
	searchResult temprst;
	keyType k;
	node* y;//��������B���Ľ��
	CharString inputstr;
	CharStringLink divideResult;
	CSLnode *csl = NULL;
	int keynum;
	int TermID;
	DocNode* p = NULL;
	int i;
	while (!infile.eof())
	{
		getline(infile, line);
		inputstr = line;
		M.divideWordsForinput(inputstr,divideResult);//��������зִ�
		searchRst.clear();
		csl = divideResult.head;
		while(csl)
		{
			k.Term = csl->data;
			keynum = T.B_Tree_Search(T.root,k,y);

			if (keynum != 0) //�ҵ��˹ؼ���k
			{
				TermID = y->key[keynum].TermID;
				p = doc[TermID].head;
				while (p)//�����ĵ�����
				{
					int flag = 0;
					for (i = 0; i < searchRst.size(); i++)//�������еĲ�ѯ������������������Ӧ�ĳ��ִ����м���
					{
						if (searchRst[i].docID == p->DocID)
						{
							searchRst[i].occurTimes += p->Times;
							searchRst[i].numOfDF++;
							flag = 1;
							break;
						}
					}
					if (flag == 0)//������еĲ�ѯ�����û�и��ĵ���������һ����ѯ���
					{
						temprst.docID = p->DocID;
						temprst.occurTimes = p->Times;
						temprst.numOfDF = 1;
						searchRst.push_back(temprst);
					}
					
					p = p->next;
				}
			}
			csl = csl->next;
		}
		sort(searchRst.begin(),searchRst.end(),SortByM1);  //���չؼ��ʳ��ֶ����ǰ�ķ�������
		if (searchRst.empty())
		//δ�����ݿ����ҵ����
		{
			outfile << "δ�����ݿ��������������ʮ�ֱ�Ǹ��" << endl;
		}
		else
		//�ҵ������������ļ�
		{
			for (i = 0; i < searchRst.size(); i++)
			{
				outfile << "("<<searchRst[i].docID << "," << searchRst[i].occurTimes<< ")"<<" ";
			}
			outfile << "\n";
		}
		
	}
	cout << "����������ϣ������Ѿ�������" <<outfileName <<"�У�"<< endl;
}