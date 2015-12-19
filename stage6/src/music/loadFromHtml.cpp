#include "loadFromHtml.h"

using namespace std;

MusicInfo M;
LoadFromHtml::~LoadFromHtml()
{

}

void MusicInfo::clear()
{
	CharString init("");
	title = init;   //��������
	singer = init;   //��������
	album = init;   //ר������
	publishdate = init;  //����ʱ��
	lyricist = init;   //������
	composer = init;   //������
	lyrics  = init;   //���и��
	info = init;  //��Ϣ
	lines = 0;  //�������
}

void LoadFromHtml::LoadData(string inputname)
{
	int i = 0;
	ifstream infile(inputname, ios::in);
	string space;
	getline(infile, space);
	while (!infile.eof())
	{
		getline(infile,htmlContext[i]);
		i++;
	}

}

void LoadFromHtml::FindIndex()
{
	int i = 0,j = 0;
	int begin;  //ջ��������ʼλ��
	int end;  //��ֹλ��
	int flag = 0;  //��Ҫ�Ĳ���
	CharString temp_start("<div class=\"song_info_area\">"), temp_end("<div class=\"music_list_area\">"),eoh("<!--tiny-->");
	tempContext[0] = htmlContext[0];  //�ȶ�ȡ��һ��

	while (!(tempContext[i] == eoh) || tempContext[i].length() == 0)
	{
		tempContext[i+1] = htmlContext[i+1];
		begin = tempContext[i].firstIndexOf(temp_start);
		end = tempContext[i+1].firstIndexOf(temp_end);
		if (begin != -1)
		{
			flag = 1;
		}
		if (end != -1)
		{
			flag = 0;
		}
		if (flag == 1)
		{
			infoNeededRaw[j] = tempContext[i + 1];
			j++;
		}
		i++;
	}
	strnum = j;
	tempContext[i] = htmlContext[i];
}

void LoadFromHtml::DeleteSpace()
{
	int i = 0,j = 0;
	int t = 0;
	while (i < strnum)
	{
		for (j = 0; j < infoNeededRaw[i].length(); j++)
		{
			if (infoNeededRaw[i].m_string[j] == '\t')
			{
				t++;
			}
			infoNeeded[i] = infoNeededRaw[i].substr(t, infoNeededRaw[i].length());
		}
		t = 0;
		i++;
	}
}

void LoadFromHtml::htmlAnalysis()
{
	int i = 0,j = 0;
	int num = 0;  //����<��>����
	int times = 0;
	M.lines = 0;//�������init
	int t;
	int k;
	CharString n;//�м���
	stack m_stack;
	/*����Ϊ�˽����ַ����жϣ�������һЩ�ؼ���Ϣ���ַ�������������ע��Ӣ�ĺ����ĵ�����*/
	CharString isSinger("in_song_tiny_singer"); 
	CharString isAlbum("in_song_tiny_album");  
	CharString isPublishdate("����ʱ��"); 
	CharString isLyricist("�ʣ�"); 
	CharString isLyricist1("��:"); 
	CharString isComposer("����"); 
	CharString isComposer1("��:");  
	CharString isComposer2("������");  
	CharString isLyrics("��");  
	CharString isLyrics1(":"); 
	CharString line_break("\n"); 
	//һ���з���,i��ʾ����
	while (i < strnum)
	{
		if (infoNeeded[i].m_string[j] == '<' && infoNeeded[i].m_string[j + 1] == 'i' && infoNeeded[i].m_string[j + 2] == 'm')  // biaoqian
		{
			i++;
		}
		if (infoNeeded[i].m_string[j] == '<' && infoNeeded[i].m_string[j + 1] != '/'  && infoNeeded[i].m_string[j + 2] != 'm')  
		{
			if (infoNeeded[i].m_string[1] == 'l')
			{
				for (j = 1;; j++)
				{
					if (infoNeeded[i].m_string[j] == '<')
					{
						t = j;
						break;
					}
				}
				for (j = t; j < infoNeeded[i].length(); j++)
				{
					if (infoNeeded[i].m_string[j] != '>')
						num++;
					else
						break;
				}
				n = infoNeeded[i].substr(t, num + 1);
				m_stack.push(n);//��ջ
				for (k = num + t; ; k++)
				{
					if (infoNeeded[i].m_string[k] == '<' && infoNeeded[i].m_string[k + 1] == '/' && (infoNeeded[i].m_string[k + 2] == 'a' || infoNeeded[i].m_string[k + 2] == 's'))
					{
						if (!m_stack.isEmpty())
						{
							m_stack.pop();                  //��ջ
						}
						break;
					}
				}
				if (infoNeeded[i].firstIndexOf(isSinger) != -1)
					M.singer = infoNeeded[i].substr(num + t + 1, k - num - t -1);
				if (infoNeeded[i].firstIndexOf(isAlbum) != -1)
					M.album = infoNeeded[i].substr(num + t + 1, k - num - t -1); 
				if (infoNeeded[i].firstIndexOf(isPublishdate) != -1)
					M.publishdate = infoNeeded[i].substr(num + t + 1, k - num - t -1); 
			}
			else
			{
				for (j = 0; j < infoNeeded[i].length(); j++)
				{
					if (infoNeeded[i].m_string[j] != '>')
						num++;
					else
						break;
				}
				n = infoNeeded[i].substr(0, num + 1);
				m_stack.push(n);
				for (t = num + 1; t < infoNeeded[i].length(); t++)
				{
					if (infoNeeded[i].m_string[t] == '<')
					{
						if (infoNeeded[i].m_string[t+1] == '/')
						{
							if (!m_stack.isEmpty())
							{
								m_stack.pop();
							}
							break;
						}
					}
				}
				if (infoNeeded[i].m_string[1] == 'h')
				{
					int temp = infoNeeded[i].firstIndexOf("title=") + 7;
					M.title = infoNeeded[i].substr(temp, num - 1 - temp);
				}
			}
			i++;
			j = 0;
			k = 0;
		}
		if (infoNeeded[i].m_string[j] == '<' && infoNeeded[i].m_string[j + 1] == '/')  
		{
			if (!m_stack.isEmpty())
			{
				m_stack.pop();  //��ջ
			}
			i++;
		}
		if (infoNeeded[i].m_string[j] == '\t' || infoNeeded[i].m_string[j] == ' ')
			i++;
		if (infoNeeded[i].m_string[j] != '\t' && infoNeeded[i].m_string[j] != '<')  
		{
			if (infoNeeded[i].firstIndexOf(isLyricist) != -1 ||infoNeeded[i].firstIndexOf(isLyricist1) != -1)
			{
				if (infoNeeded[i].firstIndexOf(isLyrics) != -1)
					M.lyricist = infoNeeded[i].substr(4, infoNeeded[i].length() - 4); 
				else
				{
					M.lyricist = infoNeeded[i].substr(3, infoNeeded[i].length() - 3);   //Ӣ��ð��
					i++;
				}
			}
			if ((infoNeeded[i].firstIndexOf(isComposer) != -1 || infoNeeded[i].firstIndexOf(isComposer1) != -1) && infoNeeded[i].firstIndexOf(isComposer2) == -1)
			{
				if (infoNeeded[i].firstIndexOf(isLyrics) != -1)
					M.composer = infoNeeded[i].substr(4,infoNeeded[i].length() - 4);
				else
				{
					M.composer = infoNeeded[i].substr(3,infoNeeded[i].length() - 3);
					i++;
				}
			}
			if ((infoNeeded[i].firstIndexOf(isLyricist) == -1 || infoNeeded[i].firstIndexOf(isLyricist1) != -1) && 
				(infoNeeded[i].firstIndexOf(isComposer) == -1 || infoNeeded[i].firstIndexOf(isComposer1) != -1) ) 
				//��ʼ�Ҹ��
			{
				if (infoNeeded[i].m_string[0] != '\0')
				{
					M.lyrics = M.lyrics + infoNeeded[i] + "\n";
					M.lines++;
				}
			}
			i++;
		}
		if (infoNeeded[i].m_string[0] == '<' && infoNeeded[i].m_string[1] == '/' && infoNeeded[i].m_string[2] == 't') 
			break;
		//����������
		j = 0;
		num = 0;
	}
	m_stack.clear();
	return;
}

void LoadFromHtml::outPut(MusicInfo &output)
{
	output.title = M.title;
	output.singer = M.singer;
	output.album = M.album;
	output.publishdate = M.publishdate;
	output.lyricist = M.lyricist;
	output.composer = M.composer;
	output.lyrics = M.lyrics;
	return;
}

void MusicInfo::extractMusicInfoFromPage(string inputname, MusicInfo &outputname)
{
	M.clear();
	LoadFromHtml load;
	load.LoadData(inputname);
	load.FindIndex();
	load.DeleteSpace();
	load.htmlAnalysis();
	load.outPut(outputname);
	cout << "�����ɹ�������"<< inputname <<"�Ѿ�������ϣ�"<<endl;
}

void MusicInfo::initDictionaryInfo(string inputname)
{
	cout <<"���ڼ��شʿ⣡"<<endl;
	hash <string> hm;
	ifstream infile(inputname);
	string words;
	while (infile)
	{
		getline(infile,words);
		m_map[hm(words)] = words;
	}
	cout <<"�ʿ������ϣ�"<<endl;
}

void MusicInfo::initUselessDictionaryInfo(string inputname)
{
	cout <<"���ڼ���ͣ�ôʿ⣡"<<endl;
	hash <string> hm;
	ifstream infile(inputname);
	string words;

	while (infile)
	{
		getline(infile,words);
		useless_map[hm(words)] = words;

	}
	cout <<"ͣ�ôʿ������ϣ�"<<endl;
}
void MusicInfo::divideWords(CharStringLink &outputname)
{
	int begin = 0, lenth;
	const int maxNumOfWord = 12;
	hash <string> hm;
	string lyricsInstring;
	CharString linkNode;
	outputname.InitList();
	while(M.lyrics.m_string[begin] != '\0')
	{
		lenth = maxNumOfWord;
		while(lenth >= 1)
		{		

			linkNode = M.lyrics.substr(begin, lenth);
			lyricsInstring = linkNode.fromCharStoString();
			if (lyricsInstring[0] >= 0)
			{
				if (lyricsInstring[0] < 'A'
					|| lyricsInstring[0] > 'Z' && lyricsInstring[0] < 'a' 
					|| lyricsInstring[0] > 'z')
				{
					begin++;
					break;
				}
			}

			if (lyricsInstring[0] >= 'A'  && lyricsInstring[0] <= 'z')
			{
				if (lyricsInstring.find(' ') < lenth)
				{
					lenth = lyricsInstring.find(' ');
					linkNode = M.lyrics.substr(begin, lenth);
					outputname.ListInsert(linkNode);
					begin += lenth;
					break;

				}
				else if (lyricsInstring.find('\n') < lenth)
				{
					lenth = lyricsInstring.find('\n');
					linkNode = M.lyrics.substr(begin, lenth);
					outputname.ListInsert(linkNode);
					begin += lenth;
					break;
				}
			}
			if (useless_map.find(hm(lyricsInstring)) != useless_map.end())
			{
				begin += 2;
				break;
			}
			if (lenth <= 2 || m_map.find(hm(lyricsInstring)) != m_map.end())
			{
				outputname.ListInsert(linkNode);
				begin+=lenth;
				break;
			}
			else
			{
				lenth--;
			}
		}
	}
}

void MusicInfo::divideWordsForinput(CharString inputstr,CharStringLink &outputname)
{
	int begin = 0, lenth;
	const int maxNumOfWord = 12;
	hash <string> hm;
	string lyricsInstring;
	CharString linkNode;
	outputname.InitList();
	while(begin < inputstr.m_length - 1)
	{
		lenth = maxNumOfWord;
		if (lenth >= inputstr.m_length - begin) //����ʵĳ���С�ڵ���һ�ν�ȡ�ĳ���
		{
			lenth = inputstr.m_length - 1 - begin;
		}
		while(lenth >= 1)
		{		
			linkNode = inputstr.substr(begin, lenth);
			lyricsInstring = linkNode.fromCharStoString();
			if (lyricsInstring[0] >= 0)
			{
				if (lyricsInstring[0] < 'A'
					|| lyricsInstring[0] > 'Z' && lyricsInstring[0] < 'a' 
					|| lyricsInstring[0] > 'z')
				{
					begin++;
					break;
				}
			}

			if (lyricsInstring[0] >= 'A'  && lyricsInstring[0] <= 'z')
			{
				if (lyricsInstring.find(' ') < lenth)
				{
					lenth = lyricsInstring.find(' ');
					linkNode = inputstr.substr(begin, lenth);
					outputname.ListInsert(linkNode);
					begin += lenth;
					break;

				}
				else if (lyricsInstring.find('\n') < lenth)
				{
					lenth = lyricsInstring.find('\n');
					linkNode = inputstr.substr(begin, lenth);
					outputname.ListInsert(linkNode);
					begin += lenth;
					break;
				}
			}
			if (useless_map.find(hm(lyricsInstring)) != useless_map.end())
			{
				begin += 2;
				break;
			}
			if (lenth <= 2 || m_map.find(hm(lyricsInstring)) != m_map.end())
			{
				outputname.ListInsert(linkNode);
				begin+=lenth;
				break;
			}
			else
			{
				lenth--;
			}
		}
	}
}