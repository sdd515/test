#pragma once
#include <map>
#include<string>
#include "MyFile.h"

using namespace std;

#define UnKnown L"\\ unknown";
#define PhoneNo L"\\ PNo"

#define PhoneNoRegex L"([1][345678][0-9]{9})"//
#define MountRegex L"(?:([0-9]|[一二三四五六七八九十两])[个]?人|位)|(?:([0-9]|[一二三四五六七八九十两])[个]?大人)|(?:([0-9]|[一二三四五六七八九十两])[个]?小孩)"
//#define MountRegex L"(?:([0-9]|[一二三四五六七八九十两])[个]?人|位)|(([0-9]|[一二三四五六七八九十两])[个]?大人)|(([0-9]|[一二三四五六七八九十两])[个]?小孩)"
//#define TimeRegex L"(?:([0-9]{1,2}|(?:[十]?[一二三四五六七八九]))?[月//.-]?([0-3]?[0-9]|[一二三]?[十]?[一二三四五六七八九十])[号日]|(?:([0-9]{1,2}|[一二三]?[十]?[一二三四五六七八九十])[号日]))?((?:早上|上午|中午|下午|傍晚|晚上|凌晨|清晨|现在|马上|全天|一天|整天|今天|明天|后天|今晚|明晚|今早|明早|今明|今明两天?)[或和、//]?(?:早上|上午|中午|下午|傍晚|晚上|凌晨|清晨|现在|马上|全天|一天|整天|今天|明天|后天|今晚|明晚|今早|明早)?)?((+|(?:[十]?[一二三四五六七[0-9]八九]+))[点时](?:([0-9]+|(?:[十]?[一二三四五六七八九]+[^\u4e00-\u9fff]))[分刻])?|(?:([0-9]+)[:：]([0-9]+)))?([至到或]([0-9]+|(?:[十]?[一二三四五六七八九]+))[点时](?:([0-9]+|(?:[十]?[一二三四五六七八九]+[^\u4e00-\u9fff]))[分刻]?)?|(?:([0-9]+)[:：]([0-9]+)))?"
//#define TimeRegex L"(?:([0-9]{1,2}|(?:[十]?[一二三四五六七八九]))?[月.-]?([0-3]?[0-9]|[一二三]?[十]?[一二三四五六七八九十])[号日]|(?:([0-9]{1,2}|[一二三]?[十]?[一二三四五六七八九十])[号日]))?((?:早上|上午|中午|下午|傍晚|晚上|凌晨|清晨|现在|马上|全天|一天|整天|今天|明天|后天|今晚|明晚|今早|明早|今明|今明两天?)[或和、]?(?:早上|上午|中午|下午|傍晚|晚上|凌晨|清晨|现在|马上|全天|一天|整天|今天|明天|后天|今晚|明晚|今早|明早)?)?((+|(?:[十]?[一二三四五六七[0-9]八九]+))[点时](?:([0-9]+|(?:[十]?[一二三四五六七八九]+[^\u4e00-\u9fff]))[分刻])?|(?:([0-9]+)[;：]([0-9]+)))?([至到或和\、-]([0-9]+|(?:[十]?[一二三四五六七八九]+))[点时](?:([0-9]+|(?:[十]?[一二三四五六七八九]+[^\u4e00-\u9fff]))[分刻]?)?|(?:([0-9]+)[:：]([0-9]+)))?"
#define TimeRegex L"(?:([0-9]{1,2}|(?:[十]?[一二三四五六七八九]))?[月.-]?([0-3]?[0-9]|[一二三]?[十]?[一二三四五六七八九十])[号日]|(?:([0-9]{1,2}|[一二三]?[十]?[一二三四五六七八九十])[号日]))?((?:早上|上午|中午|下午|傍晚|晚上|凌晨|清晨|现在|马上|全天|一天|整天|今天|明天|后天|今晚|明晚|今早|明早|今明|今明两天?))?(([0-9]+|(?:[十]?[一二三四五六七八九]+))[点时](?:([0-9]+|(?:[十]?[一二三四五六七八九]+[^\u4e00-\u9fff]))[分刻])?|(?:([0-9]+)[:：/]([0-9]+)))?"
#define TypeRegex1 L"人找车|人寻车|找车|寻车|寻顺风车|找顺风车|寻顺丰车|找顺丰车|有顺风车[吗么啊没]?|有没有"
#define TypeRegex2 L"(?:(?:起点|[出|始]发地)(?:[^\u4E00-\u9FFF]*)([\u4E00-\u9FFF]*))|(?:(?:终点|目的地)(?:[^\u4E00-\u9FFF]*)([\u4E00-\u9FFF]*))|(?:([\u4E00-\u9FFF]*)[-去上下至到在回来达出翻][^\u4E00-\u9FFF]*([\u4E00-\u9FFF]*))"
#define TypeRegex3 L"(?:有没有|有无|有)[车]?[从]?([\u4E00-\u9FFF]*)(?:直达|[-去上下至到在回来达出翻])([\u4E00-\u9FFF]*)的顺?风?|车?[啊呀么没吗]?"
#define TypeRegex4 L"车找人|车寻人|找人|寻人|有车|有位置"

/*
struct MyWord
{
	wstring word;
	wstring proper;
};*/

enum MyType
{
	ForVehicle = 1,     //人找车
	ForPassenger        //车找人
};

struct Infomations
{
	wstring type;              //类型
	wstring time;              //时间
	wstring origin;            //始发地
	wstring destination;       //目的地
	wstring mount;             //人数
	wstring phone;             //电话号码
};

class languageProcess
{
public:
	languageProcess();
	~languageProcess();

public:
	languageProcess(const string strDictionaryPath);
	bool SentenceSegment(const wstring strSentence, Infomations& infomations);//

private:
	bool LoadDictionary(const string strDictionaryPath);
	wstring ExtractPhoneNo(wstring& strLine);                       //提取电话号码
	wstring ExtractDate(wstring& strLine);                          //提取日期
	wstring ExtractType(wstring& strLine, Infomations& info);       //提取类型、始发地、目的地
	wstring ExtractMount(wstring& strLine);                         //提取人数
	wstring ExtractOriAndDest(wstring& strLine);                    //提取地址

public:

private:
	map<wstring,wstring> m_mapDictonary;
};

