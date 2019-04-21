#ifndef STACKTREE_H_INCLUDE
#define STACKTREE_H_INCLUDE

/*********************************************
*	Project：QG第五次大组考核
*	Function：栈的实现
*	Author：风雅yaya
*	Date：2019年4月20日00:10:59
*	Location：广州
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
	//入栈
	void PushStack(Yaya<T>* elem);
	//出栈
	Yaya<T>* PopStack(Yaya<T>** elem = nullptr);
	//判断栈是否为空
	bool IsStackEmpty();
	
private:
	//栈的长度
	int length;
	//栈顶指针
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

/*入栈*/
template<typename T>
inline void StackTree<T>::PushStack(Yaya<T>* elem)
{
	StackElem<T>* node = new StackElem<T>();
	node->data = *elem;
	node->next = top;
	top = node;
	++length;
}

/*出栈*/
template<typename T>
inline Yaya<T>* StackTree<T>::PopStack(Yaya<T>** elem)
{
	if (IsStackEmpty())
	{
		std::cout << "该栈为空！" << std::endl;
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


/*判断链栈是否为空*/
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

