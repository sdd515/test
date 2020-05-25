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

	map<int, MyWord> mapProccessed;

	//提取电话号码
	wstring strPhoneNo = ExtractPhoneNo(strSentence);

	wstring strDate = ExtractDate(strSentence);

	//从词典中查取词性
	map<wstring, wstring>::iterator it = m_mapDictonary.begin();
	while (it != m_mapDictonary.end())
	{
		wstring strWord = it->first;
		wstring strProperty = it->second;

		int iPos = strSentence.find(strWord);
		if (iPos >= 0)
		{
			MyWord Word;
			Word.word = strWord;
			Word.proper = strProperty;
			mapProccessed.insert(make_pair(iPos, Word));
		}

		it++;
	}

	//按照原语序排序输出
	int iCurrentPos = 0;
	map<int, MyWord>::iterator it1 = mapProccessed.begin();
	while (it1 != mapProccessed.end())
	{
		int iPos = it1->first;
		MyWord  Word = it1->second;

		if (!strProcessed.empty())
		{
			strProcessed += L"\t";
		}

		if (iPos > iCurrentPos)
		{
			strProcessed += strSentence.substr(iCurrentPos, iPos - iCurrentPos) + UnKnown;
			strProcessed += L"\t" + Word.word + Word.proper;
			iCurrentPos = iPos + Word.word.length();
		}
		else
		{
			strProcessed +=  Word.word + Word.proper;
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
	wregex celPattern(PhoneNoRegex);
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
		int ipos = str.find(result[0]);
		str.erase(str.find(result[0]), result[0].length());
	}

	strLine = str;
	return strPhoneNo;
}

wstring languageProcess::ExtractDate(wstring& strLine)
{
	wstring strDate;
	wstring strMonth;
	wstring strDay;

	wstring str = strLine;
	wsmatch result;
	wregex celPattern(DateRegex);
	wstring::const_iterator iter = strLine.cbegin();
	wstring::const_iterator iter_end = strLine.cend();
	while (regex_search(iter, iter_end, result, celPattern))
	{
		if (!strDate.empty())
		{
			strDate += L"/";
		}

		iter = result[0].second;
		str.erase(str.find(result[0]), result[0].length());

		if (result[1].length() > 0)
		{
			strMonth = result[1];
			strMonth += L"月";
		}
		if (result[2].length() > 0)
		{
			strDay = result[2];
			strDay += L"号";
		}
		if (result[3].length() > 0)
		{
			strDay = result[3];
			strDay += L"号";
		}

		if (!strDate.empty())
		{
			strDate += L",";
		}
		strDate += strMonth + strDay;
	}

	strLine = str;
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

