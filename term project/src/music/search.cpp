#include "search.h"
#include <algorithm>
bool SortByM1( const searchResult &v1, const searchResult &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.numOfDF > v2.numOfDF;//降序排列  
}  
void batchSearch(MusicInfo &M,B_Tree T, DocLink (doc)[10000], string infileName, string outfileName)
{
	cout << "开始从文件"<< infileName<<"中批量搜索！"<< endl;
	ifstream infile(infileName);
	ofstream outfile(outfileName);
	string line;//保存每行信息
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
	while (!infile.eof())
	{
		getline(infile, line);
		inputstr = line;
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
		sort(searchRst.begin(),searchRst.end(),SortByM1);  //按照关键词出现多的在前的方法排序
		if (searchRst.empty())
		//未在数据库中找到结果
		{
			outfile << "未在数据库中搜索到结果，十分抱歉！" << endl;
		}
		else
		//找到结果并输出至文件
		{
			for (i = 0; i < searchRst.size(); i++)
			{
				outfile << "("<<searchRst[i].docID << "," << searchRst[i].occurTimes<< ")"<<" ";
			}
			outfile << "\n";
		}
		
	}
	cout << "批量搜索完毕，内容已经输入至" <<outfileName <<"中！"<< endl;
}