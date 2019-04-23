#pragma once

/*********************************************
*	Project��QG����δ��鿼������
*	Function��������������ʵ��
*	Author������yaya
*	Date��2019��4��21��16:10:21
*********************************************/

#include "yaya.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <algorithm>

class CalculateTree
{
public:
	CalculateTree();
	~CalculateTree();
	//��ǰ׺���ʽת��Ϊ��׺���ʽ
	void Transform(const std::vector<std::string>& infix, std::vector<std::string>& prefix, std::map<std::string, int>& opers);
	//����׺���ʽ�洢��ջ��
	void GetInfix(std::vector<std::string>& infix);
	// ��ʼ��������
	void InitOperators(std::map<std::string, int>& opers);
	//��Ҫ����
	Yaya<std::string>* MainComputer();
	//����
	float ComputerResult(float a, float b, char c);
	//^����
	float PowerCom(float a, int b);
	//�ж��Ƿ�Ϊ������
	bool IsOperator(const std::string& op, const std::map<std::string, int>& opers);
	//��ӡ�ַ���
	void Display(const std::vector<std::string>& fix);
	//���ַ���ת��Ϊ����
	float GetFloat(std::string str);

	//����������
	Yaya<std::string>* CreateTree(const std::vector<std::string>& fix, int& index);
	void CreateTree(const std::vector<std::string>& fix);
	//����������Ĳ���
	int GetLeafCount(Yaya<std::string>* node);
	//��ȡ�����������ڶ�������н��
	void GetLastAllNode(std::vector<Yaya<std::string>*>& nodes, int depth, Yaya<std::string>* root);

	//ǰ�����
	void PreOrderTraverse(Yaya<std::string>* root);
public:
	//�����
	Yaya<std::string>* prt_root;
	//�������
	int prt_size;
	//������
	int prt_level;
	
	//�洢��׺���ʽ��ǰ׺���ʽ��ջ
	std::vector<std::string> infix, prefix;
	//�洢���ʽ�еĲ�����
	std::map<std::string, int> opers;
	//�洢�����������ڶ�������н��
	std::vector<Yaya<std::string>*> lastNodes;
private:

};

