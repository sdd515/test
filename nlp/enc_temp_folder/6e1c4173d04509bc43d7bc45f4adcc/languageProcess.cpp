#include "stdafx.h"
#include "languageProcess.h"
#include <fstream>
#include <regex>

languageProcess::languageProcess()
{
}


languageProcess::~languageProcess()
{
}

languageProcess::languageProcess(const string strDictionaryPath)
{
	LoadDictionary(strDictionaryPath);
}


bool languageProcess::SentenceSegment(string strSentence, string& strProcessed)
{
	if (strSentence.empty())
	{
		return false;
	}

	map<int, string> mapProccessed;

	//提取电话号码
	string str = strSentence;
	string strPhoneNo;
	smatch result;
	regex celPattern("[1]+[3,8]+\\d{9}");
	string::const_iterator iter = strSentence.cbegin();
	string::const_iterator iter_end = strSentence.cend();
	while (regex_search(iter, iter_end, result, celPattern))
	{
		strPhoneNo += result[0];
		iter = result[0].second;
		str.replace(str.find_first_of(result[0]), result[0].length(), "");
	}

	strSentence = str;

	//从词典中查取词性
	map<string, string>::iterator it = m_mapDictonary.begin();
	while (it != m_mapDictonary.end())
	{
		string strWord = it->first;
		string strProperty = it->second;

		int iPos = strSentence.find(strWord);
		if (iPos >= 0)
		{
			mapProccessed.insert(make_pair(iPos,strWord + strProperty));
		}

		it++;
	}

	//排序输出
	int iCurrentPos = 0;
	map<int, string>::iterator it1 = mapProccessed.begin();
	while (it1 != mapProccessed.end())
	{
		int iPos = it1->first;
		string strWord = it1->second;

		if (iPos > iCurrentPos)
		{
			strProcessed += "\t" + strSentence.substr(iCurrentPos, iCurrentPos - iPos) + "\\ unknown";
		}
		else
		{
			strProcessed += "\t" + strWord;
		}
		strProcessed += "\t" + strPhoneNo + "\\ PNo";
		it1++;
	}
	
	return true;
}

bool languageProcess::LoadDictionary(string strDictionaryPath)
{
	fstream dictionary;
	dictionary.open(strDictionaryPath, ios::in + ios::binary);

	if (!dictionary)
	{
		return false;
	}

	char buff[1024];
	while (dictionary.getline(buff, 1024))
	{
		string strLine(buff);
		int iPos = strLine.find("\t");
		if (iPos > 0)
		{
			string strKey = strLine.substr(0,iPos);
			string strVale = strLine.substr(iPos + 1, strLine.size() - iPos -1);
			m_mapDictonary.insert(make_pair(strKey,strVale));
		}
	}
	dictionary.close();
	return true;
}
