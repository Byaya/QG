#ifndef QUEUEELEM_H_INCLUDE
#define QUEUEELEM_H_INCLUDE

/************************************************
*	Project：QG大组第五次考核任务
*	Function：链栈元素类
*	Author：风雅yaya
*	Date：2019年4月20日18:14:57
*	Location：广州
************************************************/

#include "yaya.h"

template<typename T>
class QueueElem
{
public:
	QueueElem();
	~QueueElem();

public:
	//数据域
	Yaya<T> data;
	//指针域
	QueueElem* next;
};

template<typename T>
QueueElem<T>::QueueElem()
{
	next = nullptr;
}

template<typename T>
QueueElem<T>::~QueueElem()
{
}

#endif // !QUEUEELEM_H_INCLUDE
