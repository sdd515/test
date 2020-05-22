#include "stdafx.h"
#include "languageProcess.h"
#include <fstream>
#include <regex>
#include "MyFile.h"

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


bool languageProcess::SentenceSegment(wstring strSentence, wstring& strProcessed)
{
	if (strSentence.empty())
	{
		return false;
	}

	map<int, MYWORD> mapProccessed;

	//提取电话号码
	wstring strPhoneNo = ExtractPhoneNo(strSentence);

	//从词典中查取词性
	map<wstring, wstring>::iterator it = m_mapDictonary.begin();
	while (it != m_mapDictonary.end())
	{
		wstring strWord = it->first;
		wstring strProperty = it->second;

		int iPos = strSentence.find(strWord);
		if (iPos >= 0)
		{
			MYWORD Word;
			Word.word = strWord;
			Word.property = strProperty;
			mapProccessed.insert(make_pair(iPos, Word));
		}

		it++;
	}

	//按照原语序排序输出
	int iCurrentPos = 0;
	map<int, MYWORD>::iterator it1 = mapProccessed.begin();
	while (it1 != mapProccessed.end())
	{
		int iPos = it1->first;
		MYWORD  Word = it1->second;

		if (!strProcessed.empty())
		{
			strProcessed += L"\t";
		}

		if (iPos > iCurrentPos)
		{
			strProcessed += strSentence.substr(iCurrentPos, iPos - iCurrentPos) + UnKnown;
			strProcessed += L"\t" + Word.word + Word.property;
			iCurrentPos = iPos + Word.word.length();
		}
		else
		{
			strProcessed +=  Word.word + Word.property;
			iCurrentPos += Word.word.length();
		}
		it1++;
	}
	strProcessed += L"\t" + strSentence.substr(iCurrentPos, strSentence.length() - iCurrentPos - 1) + UnKnown;
	if (!strPhoneNo.empty())
	{
		strProcessed += L"\t" + strPhoneNo + PhoneNo;
	}
	
	return true;
}

wstring languageProcess::ExtractPhoneNo(wstring& strLine)
{
	wstring str = strLine;
	wstring strPhoneNo;
	wsmatch result;
	wregex celPattern(L"[1]+[3,8]+\\d{9}");
	wstring::const_iterator iter = strLine.cbegin();
	wstring::const_iterator iter_end = strLine.cend();
	while (regex_search(iter, iter_end, result, celPattern))
	{
		if (!strPhoneNo.empty())
		{
			strPhoneNo += L"/";
		}

		strPhoneNo += result[0];
		iter = result[0].second;
		str.erase(str.find_first_of(result[0]), result[0].length());
	}

	strLine = str;
	return strPhoneNo;
}

wstring languageProcess::ExtractDate(wstring& strLine)
{
	wstring strDate;
	//提取日期
	//TODO
	return strDate;
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
			MyFile myFile;
			wstring strKey = myFile.UTF8ToUnicode(strLine.substr(0,iPos));
			wstring strVale = myFile.UTF8ToUnicode(strLine.substr(iPos + 1, strLine.size() - iPos -2));
			m_mapDictonary.insert(make_pair(strKey,strVale));
		}
	}
	dictionary.close();
	return true;
}

