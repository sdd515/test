// nlp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "languageProcess.h"


int main()
{
	wstring strResult;
	languageProcess Message(".//data//dictionary.txt");
	Message.SentenceSegment(L"���� 12��3�� ��ɳȥ���� 18275668536 ,18275668537", strResult);
    return 0;
}

