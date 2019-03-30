#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/***********************************************
*	Function：模板类顺序栈
*	Author：风雅yaya
*	Date：2019年3月29日22:29:56
***********************************************/

#include <iostream>

constexpr const int SIZE = 20;

typedef enum Status
{
	ERROR = 0,OK=1
}Status;

template <typename T>
class SeqStack
{
public:
	SeqStack();
	~SeqStack();

private:
	//数据域
	T data[SIZE];
	//栈顶指针
	int top;
	//判断栈是否为空
	Status Empyt();
	//得到栈顶元素
	T GetTopStack();
	//清空栈
	Status Clear();
	//检测栈长度
	int GetLength();
	//出栈
	Status PopStack(T* elem);
	//入栈
	Status PushStack(T* elem);
};

template <typename T>
inline SeqStack<T>::SeqStack()
{
	top = -1;
	for (int i = 0; i < SIZE; i++)
	{
		data[i] = 0;
	}
}

template <typename T>
inline SeqStack<T>::~SeqStack()
{

}

template<typename T>
inline Status SeqStack<T>::Empyt()
{
	if (top == -1)
	{
		return OK;
	}
	return ERROR;
}

template<typename T>
inline T SeqStack<T>::GetTopStack()
{
	//如果栈为空
	if (top == -1)
	{
		std::cout << "该栈为空栈"std << endl;
		return;
	}
	return data[top];
}

template<typename T>
inline Status SeqStack<T>::Clear()
{
	if (top == -1)
	{
		return ERROR;
	}
	top = -1;
	return OK;
}

template<typename T>
inline int SeqStack<T>::GetLength()
{
	return top + 1 ;
}

template<typename T>
inline Status SeqStack<T>::PopStack(T* elem)
{
	if (top == -1)
	{
		std::cout << "该栈为空栈，出栈失败！"std::endl;
		return ERROR;
	}
	*elem = data[top];
	--top;
	return OK;
}

template<typename T>
inline Status SeqStack<T>::PushStack(T* elem)
{
	if (top == SIZE - 1)
	{
		std::cout << "该栈已满！"std::endl;
		return ERROR;
	}
	data[top] = elem;
	++top;
	return OK;
}



#endif // STACK_H_INCLUDED

