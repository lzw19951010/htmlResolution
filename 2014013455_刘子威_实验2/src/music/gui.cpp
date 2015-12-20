#include "gui.h"
#include "recommend.h"
#include <algorithm>
#include "search.h"


bool Sort1( const searchResult &v1, const searchResult &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.numOfDF > v2.numOfDF;//��������  
}  
void batchSearchInGui(MusicInfo &M,B_Tree T, DocLink (doc)[10000], string infileName)
{
	cout << "��ʼ���������ݡ�"<< infileName<<"������������"<< endl;
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
	inputstr = infileName;
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
	sort(searchRst.begin(),searchRst.end(),Sort1);  //���չؼ��ʳ��ֶ����ǰ�ķ�������
	if (searchRst.empty())
		//δ�����ݿ����ҵ����
	{
		cout << "δ�����ݿ��������������ʮ�ֱ�Ǹ��" << endl;
	}
	else
		//�ҵ������������ļ�
	{
		cout << "������-"<<"�ĵ�ID"<< "-"<< "�ؼ������ĵ��г��ִ���" << "-"<< "�ĵ��г��ֵĲ�ͬ�ؼ��ʸ���" <<endl;
		for (i = 0; i < searchRst.size(); i++)
		{
			cout << info[searchRst[i].docID].title <<"-" <<searchRst[i].docID << "-" << searchRst[i].occurTimes<< "-"<< searchRst[i].numOfDF << "\n";
		}
		cout << "\n";
	}

	
	cout << "������ϣ�"<< endl;
}
bool Sort2( const recommendResult &v1, const recommendResult &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.weigh > v2.weigh;//��������  
} 


void recommendBatchInGui(vector <MusicInfo> M,string infilename)
{
	//Ȩֵ�ļ����ۺ��˸���4������3������3��ר��5�����������Ĵ�2�����ֱַ�Ϊ��ռȨ��
	cout << "��ʼ���ļ�"<< infilename<<"�������Ƽ���"<< endl;
	vector <recommendResult> recommends(301);
	recommendResult temprst;
	CharString inputstr;
	DocNode* p = NULL;
	int i,j;
	int isFound;
	vector <MusicInfo> infoFrominput;//���û�����õ��Ķ�Ӧ�����б�
	inputstr = infilename;
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
		cout << "�����������롰" << infilename << "���������ҵ�" << infoFrominput.size()<<"�׶�Ӧ�ĸ�����"<<endl;
		for (i = 0; i < infoFrominput.size(); i++)
		{
			cout <<"������"<<infoFrominput[i].title<<"�����Ƽ�������£�"<< endl;
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
			//��Ȩֵ��������,ȡǰ10��
			sort(recommends.begin()+1,recommends.end(),Sort2);
			for (j = 1; j < 11; j++)
			{
				cout << "�ĵ�ID��" <<recommends[j].DocID << ", �������⣺" << recommends[j].title <<endl;
			}
			cout <<endl;
			if (i == infoFrominput.size() - 1)
			{
				cout << endl;
			}
		}
		recommends.clear();
	}
	else
	{
		cout << "��Ǹ��δ���������ҵ���" <<inputstr<< "����Ӧ�ĸ��� ��" << endl;
	}

	
	cout << "�Ƽ���ϣ�"<< endl;
}



void menu()
{
	system("cls");
	cout<<"\n            *******************���˵�*******************\n";
	cout<<"\n                   1.����ؼ��ʣ���ʾ�ؼ�����Ϣ\n";
	cout<<"\n                   2.�������������ʾ�Ƽ�������������м��벻Ҫ���ֿո�\n";
	cout<<"\n                   0.�˳�\n";
}
void Welcome()
{
	int i,j;
	cout<<"\n\n\n\n\n";
	for(i=0;i<45;i++)
		cout<<" ";
	Sleep(300);
	for(i=0;i<25;i++)
	{
		cout<<"�� ӭ ʹ �� �� �� �� ѯ ϵ ͳ !";
		Sleep(40-i);
		for(j=0;j<34;j++)
			cout<<"\b";
		for(j=0;j<34;j++)
			cout<<" ";
		for(j=0;j<35;j++)
			cout<<"\b";	
	}
	Sleep(10);
	for(i=0;i<2;i++)
	{
		cout<<"�� ӭ ʹ �� �� �� �� ѯ ϵ ͳ  !";
		Sleep(i*10);
		for(j=0;j<34;j++)
			cout<<"\b";
		for(j=0;j<34;j++)
			cout<<" ";
		for(j=0;j<33;j++)
			cout<<"\b";
	}
	cout<<"�� ӭ ʹ �� �� �� �� ѯ ϵ ͳ !"<<endl;
	Sleep(100);
}
void End()
{
	int i,j;
	Sleep(300);
	for(i=0;i<28;i++)
	{
		cout<<"л  л  ʹ  ��  !";
		Sleep(28-i);
		for(j=0;j<17;j++)
			cout<<"\b";
		for(j=0;j<17;j++)
			cout<<" ";
		for(j=0;j<16;j++)
			cout<<"\b";	
	}
	Sleep(5);
	for(i=0;i<2;i++)
	{
		cout<<"л  л  ʹ  ��  !";
		Sleep(i*10);
		for(j=0;j<17;j++)
			cout<<"\b";
		for(j=0;j<17;j++)
			cout<<" ";
		for(j=0;j<18;j++)
			cout<<"\b";
	}
	cout<<"л  л  ʹ  ��  !"<<endl;
	Sleep(100);
}

void Close()
{
	int i;
	cout<<"�ô��ڽ��� 5 ����Զ��ر�";
	for(i=0;i<13;i++)
		cout<<"\b";
	for(i=4;i>=0;i--)
	{
		cout<<"\b";
		Sleep(1000);
		cout<<i;
	}
	cout<<endl;
}   

void end_round()
{
	cout<<"******************��ѯ���******************\n";
	system("pause");
	cout<<"\n������ѯ�밴1���������˵��밴0:";
}

void runGui()
{
	int flag=1;
	string choose;
	string sel;
	string input1;
	string input2;
	Welcome();
	system("pause");
	while(flag)
	{
		menu();
		cout<<"\n��ѡ��:";
		instart:cin >> choose;
		getline(cin,sel);//ȥ���з�
		if(choose != "0" && choose != "1" && choose != "2")
		{
			cout<<"\n�����ʽ����������0,1,2���е�һ����!\a\n";  
			goto instart;
		}
		switch(choose[0] - '0')
		{
		case 1:
			inx:cout<<"\n������Ҫ��ѯ�Ĺؼ���:";

			getline(cin,input1);

			batchSearchInGui(music,T,doc,input1);
			end_round();
			inm:getline(cin,sel);
			if(sel=="1")
				goto inx;
			else if(sel != "0")
			{
				cout<<"\n�����ʽ����!\a\n";
				cout<<"\n������ѯ�밴1���������˵��밴0:";           
				goto inm;
			}
			system("pause");
			break;
		case 2:
			iny:cout<<"\n������Ҫ��ѯ�ĸ���:";
			cin >> input2;
			recommendBatchInGui(info,input2);
			end_round();
			getline(cin,sel);//ȥ���з�
			inn:getline(cin,sel);
			if(sel=="1")
				goto iny;
			else if(sel != "0")
			{
				cout<<"\n����!\a\n";
				cout<<"\n������ѯ�밴1���������˵��밴0:";
				goto inn;
			}
			system("pause");
			break;
		case 0:
			flag=0;
			End();
			Close();
			break;
		default:
			cout<<"\n�����ѡ��!����ѡ!\a\n";
			system("pause");
			system("pause");
		}
	}
}