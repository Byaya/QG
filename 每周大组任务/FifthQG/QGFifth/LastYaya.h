#ifndef LASTYAYA_H_INCLUDE
#define LASTYAYA_H_INCLUDE

/************************************************
*	Function：泛型数据元素类
*	Author：风雅yaya
*	Data：2019年3月29日22:17:39
*************************************************/

#include <iostream>

template <typename T>
class LastYaya
{
public:
	LastYaya();
	~LastYaya();
public:
	//数据域
	T data;
	//指针域
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
