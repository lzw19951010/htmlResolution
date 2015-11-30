/*
Developer:
Lawrence Liu
Software engineering
Tsinghua University

ALL RIGHTS RESERVED
*/

#include <iostream>
#include "loadFromHtml.h"
#include <io.h>
#include <vector>
using namespace std;
void getFiles( string path, vector<string>& files ) 
{  
    long   hFile   =   0;    
    struct _finddata_t fileinfo;    
    string p;  
    if   ((hFile   =   _findfirst(p.assign(path).append("/*").c_str(),&fileinfo))   !=   -1)  {    
  
        do  {    
            if   ((fileinfo.attrib   &   _A_SUBDIR)) {    
                if   (strcmp(fileinfo.name,".")   !=   0   &&   strcmp(fileinfo.name,"..")   !=   0)    
                    getFiles(   p.assign(path).append("/").append(fileinfo.name), files   );    
            }  else  {    
                files.push_back(p.assign(fileinfo.name));  
            }    
        }   while   (_findnext(   hFile,   &fileinfo   )   ==   0);    
  
        _findclose(hFile);    
    }  
} 
int main(int argc,char *argv[])
{
	MusicInfo music;
	int i;
	vector <string> files;
	string dicPath, inputPath, outputPath,outputPath1, outputPath2, out1, out2, tempstr, input;
	out1 = ".info";
	out2 = ".txt";

	fstream temp(argv[1]);
	getline(temp,dicPath);
	music.initDictionaryInfo(dicPath);
	inputPath = argv[2];
	outputPath = argv[3];
/*
	inputPath = "D:\\hw\\pages";
	outputPath = "D:\\hw\\output";*/
	getFiles(inputPath, files);
	for (i = 0; i < files.size(); i++)
	{	
		if (files[i].substr(files[i].size() - 5, 5) == ".html")
		{
			input = inputPath + "\\" + files[i];
			tempstr = files[i].erase(files[i].size() - 5, 5);
			outputPath1 = outputPath + "\\" + tempstr + out1;
			outputPath2 = outputPath + "\\" + tempstr + out2;
			
			music.extractMusicInfoFromPage(input, outputPath1);
			music.divideWords(outputPath2);
		}			
	}

	return 0;
}