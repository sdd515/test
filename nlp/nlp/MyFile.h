#pragma once

#include<string>
#include <windows.h>
#include <codecvt>
#include <iostream>

using namespace std;

class MyFile
{
public:
	MyFile();
	~MyFile();

public:
	wstring UTF8ToUnicode(const string & str);
	wstring StringToWString(const string& str);
	string WStringToString(const wstring &wstr);

private:

};

