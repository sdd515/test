// nlp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "languageProcess.h"


int main()
{
	Infomations info;
	languageProcess Message(".//data//dictionary.txt");
	Message.SentenceSegment(L"类型人找车时5月6日上午9点至10点起点深圳坪洲地铁站终点东莞常平君临酒店人数1人电话13691646535 自带口罩，无发热，无咳嗽。", info);
    return 0;
}

