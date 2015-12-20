#include "recommend.h"
#include <algorithm>
bool SortByM1( const recommendResult &v1, const recommendResult &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.weigh > v2.weigh;//降序排列  
} 

void recommendBatch(vector <MusicInfo> M,string infilename, string outfilename)
{
	//权值的计算综合了歌手4，作词3，作曲3，专辑5，及出现最多的词2，数字分别为所占权重
	cout << "开始从文件"<< infilename<<"中批量推荐！"<< endl;
	ifstream infile(infilename);
	ofstream outfile(outfilename);
	string line;//保存每行信息
	vector <recommendResult> recommends(301);
	recommendResult temprst;
	CharString inputstr;
	int TermID;
	DocNode* p = NULL;
	int i,j;
	int isFound;
	vector <MusicInfo> infoFrominput;//由用户输入得到的对应歌曲列表

	

	while (!infile.eof())
	{
		getline(infile,line);
		inputstr = line;
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
			outfile << "根据您的输入“" << line << "”，我们找到" << infoFrominput.size()<<"首对应的歌曲！"<<endl;
			for (i = 0; i < infoFrominput.size(); i++)
			{
				outfile <<"歌曲“"<<infoFrominput[i].title<<"”的推荐结果如下："<< endl;
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
				//按权值进行排序,取前三首
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
			outfile << "抱歉，未在曲库中找到“" <<inputstr<< "”对应的歌曲 ！" << endl;
		}

	}

	cout << "批量推荐完毕，内容已经输入至" <<outfilename <<"中！"<< endl;
}