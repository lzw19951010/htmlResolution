#include "gui.h"
#include "recommend.h"
#include <algorithm>
#include "search.h"


bool Sort1( const searchResult &v1, const searchResult &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.numOfDF > v2.numOfDF;//降序排列  
}  
void batchSearchInGui(MusicInfo &M,B_Tree T, DocLink (doc)[10000], string infileName)
{
	cout << "开始对输入内容“"<< infileName<<"”进行搜索！"<< endl;
	vector <searchResult> searchRst;
	searchResult temprst;
	keyType k;
	node* y;//保存搜索B树的结果
	CharString inputstr;
	CharStringLink divideResult;
	CSLnode *csl = NULL;
	int keynum;
	int TermID;
	DocNode* p = NULL;
	int i;
	inputstr = infileName;
	M.divideWordsForinput(inputstr,divideResult);//对输入进行分词
	searchRst.clear();
	csl = divideResult.head;
	while(csl)
	{
		k.Term = csl->data;
		keynum = T.B_Tree_Search(T.root,k,y);

		if (keynum != 0) //找到了关键词k
		{
			TermID = y->key[keynum].TermID;
			p = doc[TermID].head;
			while (p)//遍历文档链表
			{
				int flag = 0;
				for (i = 0; i < searchRst.size(); i++)//遍历已有的查询结果，如果已有则在相应的出现次数中加入
				{
					if (searchRst[i].docID == p->DocID)
					{
						searchRst[i].occurTimes += p->Times;
						searchRst[i].numOfDF++;
						flag = 1;
						break;
					}
				}
				if (flag == 0)//如果已有的查询结果中没有该文档，则新增一个查询结果
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
	sort(searchRst.begin(),searchRst.end(),Sort1);  //按照关键词出现多的在前的方法排序
	if (searchRst.empty())
		//未在数据库中找到结果
	{
		cout << "未在数据库中搜索到结果，十分抱歉！" << endl;
	}
	else
		//找到结果并输出至文件
	{
		cout << "歌曲名-"<<"文档ID"<< "-"<< "关键词在文档中出现次数" << "-"<< "文档中出现的不同关键词个数" <<endl;
		for (i = 0; i < searchRst.size(); i++)
		{
			cout << info[searchRst[i].docID].title <<"-" <<searchRst[i].docID << "-" << searchRst[i].occurTimes<< "-"<< searchRst[i].numOfDF << "\n";
		}
		cout << "\n";
	}

	
	cout << "搜索完毕！"<< endl;
}
bool Sort2( const recommendResult &v1, const recommendResult &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.weigh > v2.weigh;//降序排列  
} 


void recommendBatchInGui(vector <MusicInfo> M,string infilename)
{
	//权值的计算综合了歌手4，作词3，作曲3，专辑5，及出现最多的词2，数字分别为所占权重
	cout << "开始从文件"<< infilename<<"中批量推荐！"<< endl;
	vector <recommendResult> recommends(301);
	recommendResult temprst;
	CharString inputstr;
	DocNode* p = NULL;
	int i,j;
	int isFound;
	vector <MusicInfo> infoFrominput;//由用户输入得到的对应歌曲列表
	inputstr = infilename;
	isFound = 0;
	infoFrominput.clear();

	for (i = 1; i < M.size(); i++)
	{
		if (M[i].title.firstIndexOf(inputstr) >= 0)//首先对歌曲标题进行过滤
		{
			isFound = 1;
			infoFrominput.push_back(M[i]);
		}
	}
	if (isFound)
	{
		cout << "根据您的输入“" << infilename << "”，我们找到" << infoFrominput.size()<<"首对应的歌曲！"<<endl;
		for (i = 0; i < infoFrominput.size(); i++)
		{
			cout <<"歌曲“"<<infoFrominput[i].title<<"”的推荐结果如下："<< endl;
			recommends.resize(301);
			for (j = 1; j < M.size(); j++)
			{
				if (M[j].album == infoFrominput[i].album)
				{
					recommends[j].weigh+=5;//同专辑权重最大
				}
				if (M[j].singer == infoFrominput[i].singer)
				{
					recommends[j].weigh+=4;//同歌手权重其次
				}
				//作词作曲权重一样，次之
				if (M[j].lyricist == infoFrominput[i].lyricist)
				{
					recommends[j].weigh+=3;
				}
				if (M[j].lyrics == infoFrominput[i].lyrics)
				{
					recommends[j].weigh+=3;
				}
				//出现最多的词权重最少，因为样本比较小
				if (M[j].mostFrequentWord == infoFrominput[i].mostFrequentWord)
				{
					recommends[j].weigh+=3;
				}
				recommends[j].DocID = j;
				recommends[j].title = M[j].title;
			}
			//按权值进行排序,取前10首
			sort(recommends.begin()+1,recommends.end(),Sort2);
			for (j = 1; j < 11; j++)
			{
				cout << "文档ID：" <<recommends[j].DocID << ", 歌曲标题：" << recommends[j].title <<endl;
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
		cout << "抱歉，未在曲库中找到“" <<inputstr<< "”对应的歌曲 ！" << endl;
	}

	
	cout << "推荐完毕！"<< endl;
}



void menu()
{
	system("cls");
	cout<<"\n            *******************主菜单*******************\n";
	cout<<"\n                   1.输入关键词，显示关键词信息\n";
	cout<<"\n                   2.输入歌曲名，显示推荐结果，歌曲名中间请不要出现空格！\n";
	cout<<"\n                   0.退出\n";
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
		cout<<"欢 迎 使 用 音 乐 查 询 系 统 !";
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
		cout<<"欢 迎 使 用 音 乐 查 询 系 统  !";
		Sleep(i*10);
		for(j=0;j<34;j++)
			cout<<"\b";
		for(j=0;j<34;j++)
			cout<<" ";
		for(j=0;j<33;j++)
			cout<<"\b";
	}
	cout<<"欢 迎 使 用 音 乐 查 询 系 统 !"<<endl;
	Sleep(100);
}
void End()
{
	int i,j;
	Sleep(300);
	for(i=0;i<28;i++)
	{
		cout<<"谢  谢  使  用  !";
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
		cout<<"谢  谢  使  用  !";
		Sleep(i*10);
		for(j=0;j<17;j++)
			cout<<"\b";
		for(j=0;j<17;j++)
			cout<<" ";
		for(j=0;j<18;j++)
			cout<<"\b";
	}
	cout<<"谢  谢  使  用  !"<<endl;
	Sleep(100);
}

void Close()
{
	int i;
	cout<<"该窗口将在 5 秒后自动关闭";
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
	cout<<"******************查询完毕******************\n";
	system("pause");
	cout<<"\n继续查询请按1，返回主菜单请按0:";
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
		cout<<"\n请选择:";
		instart:cin >> choose;
		getline(cin,sel);//去换行符
		if(choose != "0" && choose != "1" && choose != "2")
		{
			cout<<"\n输入格式错误，请输入0,1,2其中的一个数!\a\n";  
			goto instart;
		}
		switch(choose[0] - '0')
		{
		case 1:
			inx:cout<<"\n请输入要查询的关键词:";

			getline(cin,input1);

			batchSearchInGui(music,T,doc,input1);
			end_round();
			inm:getline(cin,sel);
			if(sel=="1")
				goto inx;
			else if(sel != "0")
			{
				cout<<"\n输入格式错误!\a\n";
				cout<<"\n继续查询请按1，返回主菜单请按0:";           
				goto inm;
			}
			system("pause");
			break;
		case 2:
			iny:cout<<"\n请输入要查询的歌曲:";
			cin >> input2;
			recommendBatchInGui(info,input2);
			end_round();
			getline(cin,sel);//去换行符
			inn:getline(cin,sel);
			if(sel=="1")
				goto iny;
			else if(sel != "0")
			{
				cout<<"\n错误!\a\n";
				cout<<"\n继续查询请按1，返回主菜单请按0:";
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
			cout<<"\n错误的选择!请重选!\a\n";
			system("pause");
			system("pause");
		}
	}
}