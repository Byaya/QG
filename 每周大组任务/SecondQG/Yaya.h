#ifndef YAYA_H_INCLUDE
#define YAYA_H_INCLUDE

/************************************************
*	Function：泛型数据元素类
*	Author：风雅yaya
*	Data：2019年3月29日22:17:39
*************************************************/

#include <iostream>

template <typename T>
class Yaya
{
public:
	Yaya();
	~Yaya();
public:
	//数据域
	T data;
	//指针域
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
