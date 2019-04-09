/**
 * 创建时间: 2019年3月23日12:22:21
 * 作者:风雅yaya
 **/


#ifndef __QGFORWARD_LIST_H__
#define __QGFORWARD_LIST_H__

#include <iostream>
#include <cstdlib>
#include <cstdio>

 /*
  * 单向链表
  */
class QGForwardList{

public:
	typedef int ElemType;
	int length;

protected:
	struct Node {
		ElemType data;
		struct Node *next;
	};


	Node* head;
	Node* tail;

public:

	/*
	 * 初始化链表
	 */
	QGForwardList();

	void Print();

	/*
	 * 销毁链表
	 */
	~QGForwardList();

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

	/*
	 * 反转链表，1234反转后变成4321
	 */
	bool reverse();

	/*
	 * 链表判环
	 */
	bool isLoop();

	/*
	 * 偶节点反转，1234反转后变成2143
	 */
	bool reverseEven();

	/*
	 * 返回中间节点
	 */
	ElemType& middleElem();
};

#endif

