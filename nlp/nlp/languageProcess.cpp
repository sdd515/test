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


bool languageProcess::SentenceSegment(wstring strSentence, Infomations& infomations)
{
	if (strSentence.empty())
	{
		return false;
	}

	wstring strPhoneNo = ExtractPhoneNo(strSentence);//提取电话号码
	wstring strMount = ExtractMount(strSentence);
//	wstring strDate = ExtractDate(strSentence);//
	wstring strType = ExtractType(strSentence, infomations);//
	


	infomations.phone = strPhoneNo;
//	infomations.time = strDate;
	infomations.type = strType;

	//从词典中查取词性
	/*map<wstring, wstring>::iterator it = m_mapDictonary.begin();
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
	}*/

	//按照原语序排序输出
	/*int iCurrentPos = 0;
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
	}*/
	
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
	wregex celPattern(TimeRegex);
	wstring::const_iterator iter = strLine.cbegin();
	wstring::const_iterator iter_end = strLine.cend();
	while (regex_search(iter, iter_end, result, celPattern))
	{
		if (!strDate.empty())
		{
			strDate += L"/";
		}

		strDate += result[0];
		iter = result[0].second;
		str.erase(str.find(result[0]), result[0].length());

		/*if (!strDate.empty())
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
		strDate += strMonth + strDay;*/
	}

	strLine = str;
	return strDate;
}

wstring languageProcess::ExtractType(wstring& strLine, Infomations& info)
{
	wstring str = strLine;
	wstring  strType;

	wsmatch result1;
	wregex pattern1(TypeRegex1);
	bool ismatch1 = regex_match(strLine, result1, pattern1);
	if (ismatch1)
	{
		strType = ForVehicle;
		str.erase(str.find(result1[0]), result1[0].length());

		wsmatch result2;
		wregex celPattern2(TypeRegex2);
		wstring::const_iterator iter = str.cbegin();
		wstring::const_iterator iter_end = str.cend();
		while (regex_search(iter, iter_end, result2, celPattern2))
		{
			if (!strType.empty())
			{
				strType += L"/";
			}

			iter = result2[0].second;
			int ipos = str.find(result2[0]);
			str.erase(str.find(result2[0]), result2[0].length());
			info.origin = result2[1];
			info.destination = result2[2];
		}
	}
	else
	{
		wsmatch result3;
		wregex pattern3(TypeRegex3);
		bool ismatch3 = regex_match(strLine, result3, pattern3);
		if (ismatch3)
		{
			strType = ForVehicle;
			str.erase(str.find(result3[0]), result3[0].length());
			info.origin = result3[1];
			info.destination = result3[2];
		}
		else
		{
			wsmatch result4;
			wregex pattern4(TypeRegex4);
			bool ismatch4 = regex_match(strLine, result4, pattern4);
			if (ismatch4)
			{
				strType = ForPassenger;
				str.erase(str.find(result4[0]), result4[0].length());

				wsmatch result5;
				wregex celPattern5(TypeRegex2);
				wstring::const_iterator iter = str.cbegin();
				wstring::const_iterator iter_end = str.cend();
				while (regex_search(iter, iter_end, result5, celPattern5))
				{
					if (!strType.empty())
					{
						strType += L"/";
					}

					iter = result5[0].second;
					int ipos = str.find(result5[0]);
					str.erase(str.find(result5[0]), result5[0].length());
					info.origin = result5[1];
					info.destination = result5[2];
				}

				info.origin = result4[1];
				info.destination = result4[2];
			}
			else
			{
				strType = ForPassenger;
			}
		}
	}

	strLine = str;
	return strType;
}

wstring languageProcess::ExtractMount(wstring& strLine)
{
	wstring str = strLine;
	wstring  strMount;

	wsmatch result;
	wregex pattern(MountRegex);
	wstring::const_iterator iter = strLine.cbegin();
	wstring::const_iterator iter_end = strLine.cend();
	while (regex_search(iter, iter_end, result, pattern))
	{
		str.erase(str.find(result[0]), result[0].length());

		if (result[1].length() > 0)
		{
			strMount = result[1];
		}
		if (result[2].length() > 0)
		{
			strMount = result[2];
			strMount += L"个大人";
		}
		if (result[2].length() > 0)
		{
			strMount = result[2];
			strMount += L"个小孩";
		}
		iter = result[0].second;
	}
	strLine = str;
	return strMount;
}

wstring languageProcess::ExtractOriAndDest(wstring& strLine)
{
	wstring str = strLine;
	wstring  strMount;

	//TODO
	strLine = str;
	return strMount;
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

