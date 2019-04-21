#ifndef STACKELEM_H_INCLUDE
#define STAKCELEM_H_INCLUDE

/************************************************
*	Project��QG�������ο�������
*	Function����ջԪ����
*	Author������yaya
*	Date��2019��4��20��18:14:57
*	Location������
************************************************/

#include "yaya.h"

template<typename T>
class StackElem
{
public:
	StackElem();
	~StackElem();

public:
	//������
	Yaya<T> data;
	//ָ����
	StackElem* next;
};

template<typename T>
StackElem<T>::StackElem()
{
	next = nullptr;
}

template<typename T>
StackElem<T>::~StackElem()
{
}

#endif // !STACKELEM_H_INCLUDE
