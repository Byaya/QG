#ifndef STACKTREE_H_INCLUDE
#define STACKTREE_H_INCLUDE

/*********************************************
*	Project��QG����δ��鿼��
*	Function��ջ��ʵ��
*	Author������yaya
*	Date��2019��4��20��00:10:59
*	Location������
*********************************************/

#include "yaya.h"
#include "StackElem.h"
#include <iostream>

template<typename T>
class StackTree
{
public:
	StackTree();
	~StackTree();
	//��ջ
	void PushStack(Yaya<T>* elem);
	//��ջ
	Yaya<T>* PopStack(Yaya<T>** elem = nullptr);
	//�ж�ջ�Ƿ�Ϊ��
	bool IsStackEmpty();
	
private:
	//ջ�ĳ���
	int length;
	//ջ��ָ��
	StackElem<T>* top;
};

template <typename T>
StackTree<T>::StackTree()
{
	length = 0;
	top = nullptr;
}

template <typename T>
StackTree<T>::~StackTree()
{

}

/*��ջ*/
template<typename T>
inline void StackTree<T>::PushStack(Yaya<T>* elem)
{
	StackElem<T>* node = new StackElem<T>();
	node->data = *elem;
	node->next = top;
	top = node;
	++length;
}

/*��ջ*/
template<typename T>
inline Yaya<T>* StackTree<T>::PopStack(Yaya<T>** elem)
{
	if (IsStackEmpty())
	{
		std::cout << "��ջΪ�գ�" << std::endl;
		return nullptr;
	}
	if (elem != nullptr)
	{
		**elem = top->data;
	}
	StackElem<T>* temp = top->next;
	delete top;
	top = temp;
	--length;
	return *elem;
}


/*�ж���ջ�Ƿ�Ϊ��*/
template<typename T>
inline bool StackTree<T>::IsStackEmpty()
{
	if (top == nullptr&&length == 0)
	{
		return true;
	}
	return false;
}

#endif // !

