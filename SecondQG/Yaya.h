#ifndef YAYA_H_INCLUDE
#define YAYA_H_INCLUDE

/************************************************
*	Function����������Ԫ����
*	Author������yaya
*	Data��2019��3��29��22:17:39
*************************************************/

#include <iostream>

template <typename T>
class Yaya
{
public:
	Yaya();
	~Yaya();
public:
	//������
	T data;
	//ָ����
	Yaya<T>* next;
private:

};

template <typename T>
Yaya<T>::Yaya()
{
	next = nullptr;
	data = T();
}

template <typename T>
Yaya<T>::~Yaya()
{
}

#endif // !YAYA_H_INCLUDE
