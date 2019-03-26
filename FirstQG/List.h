/***************************************************
*	Function������ʵ��
*	Author������yaya
*	Date��2019��3��23��17:02:29
***************************************************/


#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include "QGForwardList.h"


 /*
  * ˫������
  */
class List{

public:
	typedef int ElemType;
	int length;

protected:
	struct Node {
		ElemType data;
		struct Node *prior;
		struct Node *next;
	};

	Node* head;
	Node* tail;

public:

	/*
	 * ��ʼ������
	 */
	List();

	/*
	 * ��������
	 */
	~List();

	/*��ӡ���е�����*/
	void Print();

	/*
	 * ���������е�һ��Ԫ�ص�����
	 */
	ElemType& front();

	/*
	 * �������������һ��Ԫ�ص�����
	 */
	ElemType& back();

	/*
	 * �������һ��Ԫ��ǰ���Ԫ��e
	 */
	bool push_front(ElemType& e);

	/*
	 * ɾ�������һ��Ԫ��
	 */
	bool pop_front();

	/*
	 * ���������һ��Ԫ�غ����Ԫ��e
	 */
	bool push_back(ElemType& e);

	/*
	 * ɾ���������һ��Ԫ��
	 */
	bool pop_back();

	/*
	 * ������ĵ�index + 1��Ԫ��ǰ����Ԫ��e
	 */
	bool insert(unsigned int index, ElemType& e);

	/*
	 * ɾ������λ��Ԫ��
	 */
	bool erase(unsigned int index);

	/*
	 * �������
	 */
	bool clear();

	/*
	 * ����Ԫ���Ƿ����
	 */
	bool contain(ElemType& e);

	/*
	 * ����������Ԫ�ص�����
	 */
	unsigned int size();
	/*
	 * ��������, ��ÿ��Ԫ�ص���visitָ��ĺ���
	 */
	bool traverse(void(*visit)(ElemType& e));
};

#endif

