
#include "stdafx.h"
#include "MyFile.h"

MyFile::MyFile()
{
}


MyFile::~MyFile()
{
}


wstring MyFile::UTF8ToUnicode(const string & str)
{
	wstring ret;
	try {
		wstring_convert< codecvt_utf8<wchar_t> > wcv;
		ret = wcv.from_bytes(str);
	}
	catch (const exception & e) 
	{
		cerr << e.what() << endl;
	}
	return ret;
}


wstring MyFile::StringToWString(const string& str)
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	wstring w_str(wide);
	delete[] wide;
	return w_str;
}

string MyFile::WStringToString(const wstring &wstr)
{
	string str;
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');
	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);
	if (nResult == 0)
	{
		return "";
	}
	return str;
}
