#ifndef QUEUETREE_H_INCLUDE
#define QUEUETREE_H_INCLUDE

/*********************************************
*	Project��QG����δ��鿼��
*	Function�����е�ʵ��
*	Author������yaya
*	Date��2019��4��20��00:10:59
*	Location������
*********************************************/

#include "QueueElem.h"

template<typename T>
class QueueTree
{
public:
	QueueTree();
	~QueueTree();
	//���
	void EnQueue(Yaya<T>* elem);
	//����
	void DeQueue(Yaya<T>** elem = nullptr);
	//�ж϶����Ƿ�Ϊ��
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

/*���*/
template<typename T>
inline void QueueTree<T>::EnQueue(Yaya<T>* elem)
{
	QueueElem<T>* node = new QueueElem<T>();
	node->data = *elem;
	node->next = nullptr;
	rear->next = node;
	rear = node;
}

/*����*/
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

/*�ж϶����Ƿ�Ϊ��*/
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
