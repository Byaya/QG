#ifndef LINKSTACK_H_INCLUDE
#define LINKSTACK_H_INCLUDE

#include "Yaya.h"
#include <iostream>

template <typename T>
class LinkStack
{
public:
	LinkStack();
	~LinkStack();
	//判断栈是否为空
	bool Empty();
	//得到栈顶元素
	T GetTopElem();
	//清空栈
	void Clear();
	//检测栈的长度
	int GetLength();
	//出栈
	T PopStack();
	//入栈
	void PushStakc(T* elem);
private:
	//栈顶指针
	Yaya<T>* top;
	//栈的元素个数
	int length;
};

template <typename T>
LinkStack<T>::LinkStack()
{
	top = nullptr;
	length = 0;
}

template <typename T>
LinkStack<T>::~LinkStack()
{
	Yaya<T>* node = NULL;
	while (top)
	{
		node = top->next;
		delete top;
		top = node;
	}
	top = nullptr;
}

template<typename T>
inline bool LinkStack<T>::Empty()
{
	if (length == 0 && top == nullptr)
	{
		return true;
	}
	return false;
}

template<typename T>
inline T LinkStack<T>::GetTopElem()
{
	if (Empty())
	{
		return T();
	}
	return top->data;
}

template<typename T>
inline void LinkStack<T>::Clear()
{
	Yaya* node = nullptr;
	while (top)
	{
		node = top;
		top = top->next;
		delete node;
	}
	top = nullptr;
}

template<typename T>
inline int LinkStack<T>::GetLength()
{
	return length;
}

template<typename T>
inline T LinkStack<T>::PopStack()
{
	T elem;
	if (Empty())
	{
		return T();
	}
	Yaya<T>* node = top->next;
	elem = top->data;
	delete top;
	top = node;
	--length;
	return elem;
}

template<typename T>
inline void LinkStack<T>::PushStakc(T * elem)
{
	Yaya<T>* node = new Yaya<T>();
	node->next = top;
	node->data = *elem;
	top = node;
	++length;
}

#endif // !LINKSTACK_H_INCLUDE

