#ifndef DOUBLELINK_H_INCLUDE
#define DOUBLELINK_H_INCLUDE

/***********************************************
*	Function:泛型双向链表
*	Author：风雅yaya
*	Date：2019年3月23日19:48:25
***********************************************/

#include "Yaya.h"
#include <iostream>

template<typename T>
class DoubleLInk
{
public:
	DoubleLInk();
	~DoubleLInk();
public:
	void Insert(T data, int pos);
	void Push_front(T data);
	void Push_back(T data);
	void Erase(int pos);
	void Pop_front();
	void Pop_back();
	void Clear();
	void FirstSort();
	void SecondSort();
	int GetLength();
	void Print();

private:
	//表头
	Yaya<T>* head;
	//表尾
	Yaya<T>* tail;
	//链表长度
	int length;
};
/*构造函数*/
template<typename T>
inline DoubleLInk<T>::DoubleLInk()
{
	head = new Yaya<T>();
	head->data = 0;
	head->prior = nullptr;
	head->next = nullptr;
	tail = head;
	length = 0;
}

/*析构函数*/
template<typename T>
inline DoubleLInk<T>::~DoubleLInk()
{
	if (length == 0)
	{
		std::cout << "链表为空！" << std::endl;
		return;
	}
	Yaya<T>* yaya = head;
	Yaya<T>* temp = head;
	while (yaya)
	{
		temp = yaya;
		yaya = yaya->next;
		delete temp;
	}
}

/*在任意位置插入元素*/
template<typename T>
void DoubleLInk<T>::Insert(T data, int pos)
{
	if (pos<1 || pos>length + 1)
	{
		std::cout << "下标越界" << std::endl;
		return;
	}
	if (pos == length + 1)
	{
		Push_back(data);
		return;
	}
	Yaya<T>* last = head;
	Yaya<T>* next = head;
	for (int i = 0; i < pos - 1; i++)
	{
		last = last->next;
	}
	next = last->next;
	Yaya<T>* yaya = new Yaya<T>();
	yaya->next = next;
	yaya->prior = last;
	yaya->data = data;
	last->next = yaya;
	next->prior = yaya;
	length++;
}

/*在表头插入元素*/
template<typename T>
void DoubleLInk<T>::Push_front(T data)
{
	Insert(data, 1);
}

/*在表尾插入元素*/
template<typename T>
void DoubleLInk<T>::Push_back(T data)
{
	Yaya<T>* yaya = new Yaya<T>();
	yaya->data = data;
	yaya->prior = tail;
	yaya->next = nullptr;
	tail->next = yaya;
	tail = yaya;
	length++;
}

/*删除任意位置的元素*/
template<typename T>
void DoubleLInk<T>::Erase(int pos)
{
	if (length == 1)
	{
		delete head->next;
		tail = head;
		--length;
		return;
	}
	if (pos<1 || pos>length)
	{
		std::cout << "下标越界" << std::endl;
	}
	Yaya<T>* last = head;
	Yaya<T>* yaya = head;
	Yaya<T>* next = head;
	for (int i = 0; i < pos; i++)
	{
		yaya = yaya->next;
	}
	last = yaya->prior;
	next = yaya->next;
	last->next = next;
	if (next)
	{
		next->prior = last;
	}
	if (pos == length)
	{
		tail = last;
	}
	delete yaya;
	--length;
}

/*删除表头元素*/
template<typename T>
void DoubleLInk<T>::Pop_front()
{
	Erase(1);
}

/*删除表尾元素*/
template<typename T>
void DoubleLInk<T>::Pop_back()
{
	Erase(length);
}

/*清空链表*/
template<typename T>
void DoubleLInk<T>::Clear()
{
	if (!length)
	{
		return;
	}
	Yaya<T>* temp = head;
	Yaya<T>* yaya = head->next;
	while (head != tail)
	{
		temp = yaya;
		yaya = yaya->next;
		delete temp;
	}
	length = 0;
}

/*快速排序*/
template<typename T>
void DoubleLInk<T>::FirstSort()
{

}

/*冒泡排序*/
template<typename T>
void DoubleLInk<T>::SecondSort()
{
	Yaya<T>* top = head->next;
	Yaya<T>* last = head;
	Yaya<T>* yaya = top;
	Yaya<T>* next = top->next;
	for (int i = 0; i < length - 1; i++)
	{
		last = top->prior;
		yaya = top;
		next = yaya->next;
		while(1)
		{
			if (!next)
			{
				break;
			}
			if (yaya->data > next->data)
			{
				yaya->prior = next;
				yaya->next = next->next;
				next->next = yaya;
				next->prior = last;
				last->next = next;
			}
			
			yaya = last->next->next;
			next = yaya->next;
			last = last->next;
		}
		top = top->next;
	}
}

/*返回链表长度*/
template<typename T>
int DoubleLInk<T>::GetLength()
{
	std::cout << length << std::endl;
	return length;
}

/*打印所有元素*/
template<typename T>
void DoubleLInk<T>::Print()
{
	if (length==0)
	{
		std::cout << "该链表为空！" << std::endl;
		return;
	}
	Yaya<T>* node = head->next;
	int count = length;
	while (1)
	{
		if (count)
		{
			std::cout << node->data << std::endl;
			node = node->next;
			--count;
			continue;
		}
		break;
	}
}


#endif // !DOUBLELINK_H_INCLUDE