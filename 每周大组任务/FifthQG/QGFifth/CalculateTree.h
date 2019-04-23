#pragma once

/*********************************************
*	Project：QG第五次大组考核任务
*	Function：算术二叉树的实现
*	Author：风雅yaya
*	Date：2019年4月21日16:10:21
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
	//将前缀表达式转换为中缀表达式
	void Transform(const std::vector<std::string>& infix, std::vector<std::string>& prefix, std::map<std::string, int>& opers);
	//将中缀表达式存储到栈中
	void GetInfix(std::vector<std::string>& infix);
	// 初始化操作符
	void InitOperators(std::map<std::string, int>& opers);
	//主要计算
	Yaya<std::string>* MainComputer();
	//计算
	float ComputerResult(float a, float b, char c);
	//^运算
	float PowerCom(float a, int b);
	//判断是否为操作符
	bool IsOperator(const std::string& op, const std::map<std::string, int>& opers);
	//打印字符串
	void Display(const std::vector<std::string>& fix);
	//将字符串转化为数字
	float GetFloat(std::string str);

	//创建二叉树
	Yaya<std::string>* CreateTree(const std::vector<std::string>& fix, int& index);
	void CreateTree(const std::vector<std::string>& fix);
	//计算二叉树的层数
	int GetLeafCount(Yaya<std::string>* node);
	//获取二叉树倒数第二层的所有结点
	void GetLastAllNode(std::vector<Yaya<std::string>*>& nodes, int depth, Yaya<std::string>* root);

	//前序遍历
	void PreOrderTraverse(Yaya<std::string>* root);
public:
	//根结点
	Yaya<std::string>* prt_root;
	//结点总数
	int prt_size;
	//结点层数
	int prt_level;
	
	//存储中缀表达式和前缀表达式的栈
	std::vector<std::string> infix, prefix;
	//存储表达式中的操作数
	std::map<std::string, int> opers;
	//存储二叉树倒数第二层的所有结点
	std::vector<Yaya<std::string>*> lastNodes;
private:

};

