#ifndef QUEUEELEM_H_INCLUDE
#define QUEUEELEM_H_INCLUDE

/************************************************
*	Project��QG�������ο�������
*	Function����ջԪ����
*	Author������yaya
*	Date��2019��4��20��18:14:57
*	Location������
************************************************/

#include "yaya.h"

template<typename T>
class QueueElem
{
public:
	QueueElem();
	~QueueElem();

public:
	//������
	Yaya<T> data;
	//ָ����
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
