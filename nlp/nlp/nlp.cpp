// nlp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "languageProcess.h"


int main()
{
	Infomations info;
	languageProcess Message(".//data//dictionary.txt");
	Message.SentenceSegment(L"�������ҳ�ʱ5��6������9����10���������ƺ�޵���վ�յ㶫ݸ��ƽ���پƵ�����1�˵绰13691646535 �Դ����֣��޷��ȣ��޿��ԡ�", info);
    return 0;
}

