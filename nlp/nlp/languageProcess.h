#pragma once
#include <map>
#include<string>
#include "MyFile.h"

using namespace std;

#define UnKnown L"\\ unknown";
#define PhoneNo L"\\ PNo"

struct MYWORD
{
	wstring word;
	wstring property;
};

struct INFOMATIONS
{
	wstring type;
	wstring time;
	wstring origin;
	wstring destination;
	wstring count;
	wstring phone;
};

class languageProcess
{
public:
	languageProcess();
	~languageProcess();

public:
	languageProcess(const string strDictionaryPath);
	bool SentenceSegment(const wstring strSentence,wstring& strProcessed);//分词

private:
	bool LoadDictionary(const string strDictionaryPath);
	wstring ExtractPhoneNo(wstring& strLine);//提取电话号码
	wstring ExtractDate(wstring& strLine);//提取日期

public:

private:
	map<wstring,wstring> m_mapDictonary;
};

