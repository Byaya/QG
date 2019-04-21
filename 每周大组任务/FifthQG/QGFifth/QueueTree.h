#ifndef QUEUETREE_H_INCLUDE
#define QUEUETREE_H_INCLUDE

/*********************************************
*	Project：QG第五次大组考核
*	Function：队列的实现
*	Author：风雅yaya
*	Date：2019年4月20日00:10:59
*	Location：广州
*********************************************/

#include "QueueElem.h"

template<typename T>
class QueueTree
{
public:
	QueueTree();
	~QueueTree();
	//入队
	void EnQueue(Yaya<T>* elem);
	//出队
	void DeQueue(Yaya<T>** elem = nullptr);
	//判断队列是否为空
	bool IsQueueEmpty();
private:
	QueueElem<T>* front;
	QueueElem<T>* rear;
};

template<typename T>
QueueTree<T>::QueueTree()
{
	front = new QueueElem<T>();
	front->next = nullptr;
	rear = front;
}

template<typename T>
QueueTree<T>::~QueueTree()
{

}

/*入队*/
template<typename T>
inline void QueueTree<T>::EnQueue(Yaya<T>* elem)
{
	QueueElem<T>* node = new QueueElem<T>();
	node->data = *elem;
	node->next = nullptr;
	rear->next = node;
	rear = node;
}

/*出队*/
template<typename T>
inline void QueueTree<T>::DeQueue(Yaya<T>** elem)
{
	if (IsQueueEmpty())
	{
		return;
	}
	**elem = front->next->data;
	QueueElem<T>* temp = front->next;
	front->next = temp->next;
	if (rear == temp)
	{
		rear = front;
	}
	delete temp;
}

/*判断队列是否为空*/
template<typename T>
inline bool QueueTree<T>::IsQueueEmpty()
{
	if (front == rear)
	{
		return true;
	}
	return false;
}


#endif // !QUEUETREE_H_INCLUDE
