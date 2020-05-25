// nlp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "languageProcess.h"


int main()
{
	wstring strResult;
	languageProcess Message(".//data//dictionary.txt");
	Message.SentenceSegment(L"今天 12月3号 长沙去深圳 18275668536 ,18275668537", strResult);
    return 0;
}

