#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/***********************************************
*	Function��ģ����˳��ջ
*	Author������yaya
*	Date��2019��3��29��22:29:56
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
	//������
	T data[SIZE];
	//ջ��ָ��
	int top;
	//�ж�ջ�Ƿ�Ϊ��
	Status Empyt();
	//�õ�ջ��Ԫ��
	T GetTopStack();
	//���ջ
	Status Clear();
	//���ջ����
	int GetLength();
	//��ջ
	Status PopStack(T* elem);
	//��ջ
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
	//���ջΪ��
	if (top == -1)
	{
		std::cout << "��ջΪ��ջ"std << endl;
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
		std::cout << "��ջΪ��ջ����ջʧ�ܣ�"std::endl;
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
		std::cout << "��ջ������"std::endl;
		return ERROR;
	}
	data[top] = elem;
	++top;
	return OK;
}



#endif // STACK_H_INCLUDED

