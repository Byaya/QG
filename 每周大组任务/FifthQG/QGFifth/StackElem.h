#ifndef STACKELEM_H_INCLUDE
#define STAKCELEM_H_INCLUDE

/************************************************
*	Project：QG大组第五次考核任务
*	Function：链栈元素类
*	Author：风雅yaya
*	Date：2019年4月20日18:14:57
*	Location：广州
************************************************/

#include "yaya.h"

template<typename T>
class StackElem
{
public:
	StackElem();
	~StackElem();

public:
	//数据域
	Yaya<T> data;
	//指针域
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
