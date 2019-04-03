#ifndef OPERATION_H_INCLUDE
#define OPERATION_H_INCLUDE

/********************************************
*	Function������ջʵ����������
*	Author������yaya
*	Date��2019��3��30��10:03:18
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
	//����Ԫ�����ȼ�
	int Prio(char c);
	//����
	float Computer(float a, float b, char c);
	//^����
	float PowerCom(float a, int b);

};

#endif // !OPERATION_H_INCLUDE

