#ifndef LASTYAYA_H_INCLUDE
#define LASTYAYA_H_INCLUDE

/************************************************
*	Function����������Ԫ����
*	Author������yaya
*	Data��2019��3��29��22:17:39
*************************************************/

#include <iostream>

template <typename T>
class LastYaya
{
public:
	LastYaya();
	~LastYaya();
public:
	//������
	T data;
	//ָ����
	LastYaya<T>* next;
private:

};

template <typename T>
LastYaya<T>::LastYaya()
{
	next = nullptr;
	data = T();
}

template <typename T>
LastYaya<T>::~LastYaya()
{
}

#endif // !LASTYAYA_H_INCLUDE
