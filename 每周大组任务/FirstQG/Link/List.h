/***************************************************
*	Function：链表实现
*	Author：风雅yaya
*	Date：2019年3月23日17:02:29
***************************************************/


#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include "QGForwardList.h"


 /*
  * 双向链表
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
	 * 初始化链表
	 */
	List();

	/*
	 * 销毁链表
	 */
	~List();

	/*打印所有的数据*/
	void Print();

	/*
	 * 返回链表中第一个元素的引用
	 */
	ElemType& front();

	/*
	 * 返回链表中最后一个元素的引用
	 */
	ElemType& back();

	/*
	 * 在链表第一个元素前添加元素e
	 */
	bool push_front(ElemType& e);

	/*
	 * 删除链表第一个元素
	 */
	bool pop_front();

	/*
	 * 在链表最后一个元素后添加元素e
	 */
	bool push_back(ElemType& e);

	/*
	 * 删除链表最后一个元素
	 */
	bool pop_back();

	/*
	 * 在链表的第index + 1个元素前插入元素e
	 */
	bool insert(unsigned int index, ElemType& e);

	/*
	 * 删除任意位置元素
	 */
	bool erase(unsigned int index);

	/*
	 * 清空链表
	 */
	bool clear();

	/*
	 * 查找元素是否存在
	 */
	bool contain(ElemType& e);

	/*
	 * 返回链表中元素的数量
	 */
	unsigned int size();
	/*
	 * 遍历链表, 对每个元素调用visit指向的函数
	 */
	bool traverse(void(*visit)(ElemType& e));
};

#endif

