#pragma once
#include <map>
#include<string>
#include "MyFile.h"

using namespace std;

#define UnKnown L"\\ unknown";
#define PhoneNo L"\\ PNo"

#define PhoneNoRegex L"[1]+[3,8]+\\d{9}"
//L"((?<month>[0-9]{1,2}|[ʮ]?[һ�����������߰˾�])[��\/.-\\](?<day>[0-3]?[0-9]|[һ����]?[ʮ]?[һ�����������߰˾�ʮ])[����]?|[^0-9](?<sday>[0-9]{1,2}|[һ����]?[ʮ]?[һ�����������߰˾�ʮ])[����]).*((?<hour>[0-2]?[0-9])[:-](?<minute>[0-6]?[0-9]))?"
//#define DateRegex  L"(?<month>[0-9]{1,2}|[ʮ]?[һ�����������߰˾�])[��\/.-](?<day>[0-3]?[0-9]|[һ����]?[ʮ]?[һ�����������߰˾�ʮ])[����]?|[^0-9](?<sday>[0-9]{1,2}|[һ����]?[ʮ]?[һ�����������߰˾�ʮ])[����]"
#define DateRegex  L"([0-9]{1,2}|[ʮ]?[һ�����������߰˾�])[��\/.-]([0-3]?[0-9]|[һ����]?[ʮ]?[һ�����������߰˾�ʮ])[����]?|[^0-9]([0-9]{1,2}|[һ����]?[ʮ]?[һ�����������߰˾�ʮ])[����]"
#define TimeRegex L""
struct MyWord
{
	wstring word;
	wstring proper;
};

enum MyType
{
	ForPassenger = 1,     //������
    ForVehicle            //���ҳ�
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
	bool SentenceSegment(const wstring strSentence,wstring& strProcessed);//�ִ�

private:
	bool LoadDictionary(const string strDictionaryPath);
	wstring ExtractPhoneNo(wstring& strLine);//��ȡ�绰����
	wstring ExtractDate(wstring& strLine);//��ȡ����

public:

private:
	map<wstring,wstring> m_mapDictonary;
};

