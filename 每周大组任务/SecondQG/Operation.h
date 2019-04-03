#ifndef OPERATION_H_INCLUDE
#define OPERATION_H_INCLUDE

/********************************************
*	Function：用链栈实现四则运算
*	Author：风雅yaya
*	Date：2019年3月30日10:03:18
********************************************/

#include "LinkStack.h"

class Operation
{
public:
	Operation();
	~Operation();
	void Transform(char* middle);
private:
	LinkStack<float> stackNum;
	LinkStack<char> stackChar;
	//返回元素优先级
	int Prio(char c);
	//计算
	float Computer(float a, float b, char c);
	//^运算
	float PowerCom(float a, int b);

};

#endif // !OPERATION_H_INCLUDE

