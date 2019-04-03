#ifndef DOUBLELINK_H_INCLUDE
#define DOUBLELINK_H_INCLUDE

/***********************************************
*	Function:����˫������
*	Author������yaya
*	Date��2019��3��23��19:48:25
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
	//��ͷ
	Yaya<T>* head;
	//��β
	Yaya<T>* tail;
	//������
	int length;
};
/*���캯��*/
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

/*��������*/
template<typename T>
inline DoubleLInk<T>::~DoubleLInk()
{
	if (length == 0)
	{
		std::cout << "����Ϊ�գ�" << std::endl;
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

/*������λ�ò���Ԫ��*/
template<typename T>
void DoubleLInk<T>::Insert(T data, int pos)
{
	if (pos<1 || pos>length + 1)
	{
		std::cout << "�±�Խ��" << std::endl;
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

/*�ڱ�ͷ����Ԫ��*/
template<typename T>
void DoubleLInk<T>::Push_front(T data)
{
	Insert(data, 1);
}

/*�ڱ�β����Ԫ��*/
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

/*ɾ������λ�õ�Ԫ��*/
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
		std::cout << "�±�Խ��" << std::endl;
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

/*ɾ����ͷԪ��*/
template<typename T>
void DoubleLInk<T>::Pop_front()
{
	Erase(1);
}

/*ɾ����βԪ��*/
template<typename T>
void DoubleLInk<T>::Pop_back()
{
	Erase(length);
}

/*�������*/
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

/*��������*/
template<typename T>
void DoubleLInk<T>::FirstSort()
{

}

/*ð������*/
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

/*����������*/
template<typename T>
int DoubleLInk<T>::GetLength()
{
	std::cout << length << std::endl;
	return length;
}

/*��ӡ����Ԫ��*/
template<typename T>
void DoubleLInk<T>::Print()
{
	if (length==0)
	{
		std::cout << "������Ϊ�գ�" << std::endl;
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