#ifndef LINKSTACK_H_INCLUDE
#define LINKSTACK_H_INCLUDE

#include "LastYaya.h"
#include <iostream>

template <typename T>
class LinkStack
{
public:
	LinkStack();
	~LinkStack();
	//�ж�ջ�Ƿ�Ϊ��
	bool Empty();
	//�õ�ջ��Ԫ��
	T GetTopElem();
	//���ջ
	void Clear();
	//���ջ�ĳ���
	int GetLength();
	//��ջ
	T PopStack();
	//��ջ
	void PushStakc(T* elem);
private:
	//ջ��ָ��
	LastYaya<T>* top;
	//ջ��Ԫ�ظ���
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
	LastYaya<T>* node = NULL;
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
	LastYaya<T>* node = top->next;
	elem = top->data;
	delete top;
	top = node;
	--length;
	return elem;
}

template<typename T>
inline void LinkStack<T>::PushStakc(T * elem)
{
	LastYaya<T>* node = new LastYaya<T>();
	node->next = top;
	node->data = *elem;
	top = node;
	++length;
}

#endif // !LINKSTACK_H_INCLUDE

