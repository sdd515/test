// nlp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "languageProcess.h"


int main()
{
	string str = "����ȥ������";
	int i = str.find("ȥ");

	UNICODE;
	string strResult;
	languageProcess Message(".//data//dictionary.txt");
	Message.SentenceSegment("today���쳤ɳȥ���� 18275668536 ,18275668537", strResult);
    return 0;
}

