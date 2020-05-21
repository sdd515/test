#pragma once
#include "stdafx.h"
#include <map>

using namespace std;

class languageProcess
{
public:
	languageProcess();
	~languageProcess();

public:
	languageProcess(const string strDictionaryPath);
	bool SentenceSegment(const string strSentence,string& strProcessed);

private:
	bool LoadDictionary(const string strDictionaryPath);

public:

private:
	map<string,string> m_mapDictonary;
};

