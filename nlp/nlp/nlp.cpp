// nlp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "languageProcess.h"


int main()
{
	string str = "今天去哈哈哈";
	int i = str.find("去");

	UNICODE;
	string strResult;
	languageProcess Message(".//data//dictionary.txt");
	Message.SentenceSegment("today今天长沙去深圳 18275668536 ,18275668537", strResult);
    return 0;
}

