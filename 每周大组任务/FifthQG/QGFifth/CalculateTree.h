#pragma once

/*********************************************
*	Project��QG����δ��鿼������
*	Function��������������ʵ��
*	Author������yaya
*	Date��2019��4��21��16:10:21
*********************************************/

#include "yaya.h"
#include "LinkStack.h"

class CalculateTree
{
public:
	CalculateTree();
	~CalculateTree();
	void AddNode(const char& key, int direction);
	//�����ַ�������������
	Yaya<char>* CreteBinary(Yaya<char>** root);
	//�������
	void PreTraverse(Yaya<char>* root);
	//��ǰ׺���ʽת��Ϊ��׺���ʽ
	char* Transform(char * middle);
	//����
	float Computer(float a, float b, char c);
	//ָ���˷�
	float PowerCom(float a, int b);
	//������������ȼ�
	int Prio(char c);
public:
	//�����
	Yaya<char>* prt_root;
	//�������
	int prt_size;
	//��ָ��λ�ò�����
	Yaya<char>* AddNode(const char& key, int direction, Yaya<char>*& root);
	LinkStack<float> stackNum;
	LinkStack<char> stackChar;
private:
	//������־
	char flag;
	//�ж��Ƿ����������־
	bool isFlag;

};

