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
	bool SentenceSegment(const wstring strSentence,wstring& strProcessed);//�ִ�

private:
	bool LoadDictionary(const string strDictionaryPath);
	wstring ExtractPhoneNo(wstring& strLine);//��ȡ�绰����
	wstring ExtractDate(wstring& strLine);//��ȡ����

public:

private:
	map<wstring,wstring> m_mapDictonary;
};

