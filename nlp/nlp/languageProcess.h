#pragma once
#include <map>
#include<string>
#include "MyFile.h"

using namespace std;

#define UnKnown L"\\ unknown";
#define PhoneNo L"\\ PNo"

#define PhoneNoRegex L"[1]+[3,8]+\\d{9}"
//L"((?<month>[0-9]{1,2}|[十]?[一二三四五六七八九])[月\/.-\\](?<day>[0-3]?[0-9]|[一二三]?[十]?[一二三四五六七八九十])[号日]?|[^0-9](?<sday>[0-9]{1,2}|[一二三]?[十]?[一二三四五六七八九十])[号日]).*((?<hour>[0-2]?[0-9])[:-](?<minute>[0-6]?[0-9]))?"
//#define DateRegex  L"(?<month>[0-9]{1,2}|[十]?[一二三四五六七八九])[月\/.-](?<day>[0-3]?[0-9]|[一二三]?[十]?[一二三四五六七八九十])[号日]?|[^0-9](?<sday>[0-9]{1,2}|[一二三]?[十]?[一二三四五六七八九十])[号日]"
#define DateRegex  L"([0-9]{1,2}|[十]?[一二三四五六七八九])[月\/.-]([0-3]?[0-9]|[一二三]?[十]?[一二三四五六七八九十])[号日]?|[^0-9]([0-9]{1,2}|[一二三]?[十]?[一二三四五六七八九十])[号日]"
#define TimeRegex L""
struct MyWord
{
	wstring word;
	wstring proper;
};

enum MyType
{
	ForPassenger = 1,     //车找人
    ForVehicle            //人找车
};

struct Infomations
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

