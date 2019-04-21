#pragma once

/*********************************************
*	Project：QG第五次大组考核任务
*	Function：算术二叉树的实现
*	Author：风雅yaya
*	Date：2019年4月21日16:10:21
*********************************************/

#include "yaya.h"
#include "LinkStack.h"

class CalculateTree
{
public:
	CalculateTree();
	~CalculateTree();
	void AddNode(const char& key, int direction);
	//根据字符串创建二叉树
	Yaya<char>* CreteBinary(Yaya<char>** root);
	//先序遍历
	void PreTraverse(Yaya<char>* root);
	//将前缀表达式转换为中缀表达式
	char* Transform(char * middle);
	//计算
	float Computer(float a, float b, char c);
	//指数乘法
	float PowerCom(float a, int b);
	//返回运算符优先级
	int Prio(char c);
public:
	//根结点
	Yaya<char>* prt_root;
	//结点总数
	int prt_size;
	//在指定位置插入结点
	Yaya<char>* AddNode(const char& key, int direction, Yaya<char>*& root);
	LinkStack<float> stackNum;
	LinkStack<char> stackChar;
private:
	//结束标志
	char flag;
	//判断是否输入结束标志
	bool isFlag;

};

