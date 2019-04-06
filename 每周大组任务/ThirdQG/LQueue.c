#include "LQueue.h"

void DestoryLQueue(LQueue * queue)
{
	ClearLQueue(queue);
	free(queue->front);
	free(queue->rear);
}

bool IsEmptyLQueue(LQueue * queue)
{
	if (queue->length == 0)
	{
		printf("队列为空！");
		return true;
	}
	return false;
}

void GetHeadLQueue(LQueue * queue, void ** data)
{
	if (queue->length == 0)
	{
		printf("队列为空！");
		return;
	}
	*data = queue->front->next->data;
	return;
}

size_t GetLengthLQueue(LQueue * queue)
{
	printf("队列长度为%d\n", queue->length);
	return queue->length;
}

void ClearLQueue(LQueue * queue)
{
	Node* temp = queue->front->next;
	while (temp)
	{
		Node* tp = temp;
		temp = temp->next;
		free(tp);
	}
	temp = NULL;
	queue->rear = queue->front;
	queue->length = 0;
}

void TraverseLQueue(const LQueue * queue, void(*func)(void *, DATATYPE), DATATYPE flag)
{
	Node* temp = queue->front->next;
	while (temp)
	{
		func(temp->data, flag);
		temp = temp->next;
	}
	temp = NULL;
}

void LQPrint(LQueue * queue, DATATYPE flag)
{
	if (queue->length == 0)
	{
		printf("队列为空\n");
		return;
	}
	Node* temp = queue->front->next;
	while (temp)
	{
		DLPrint(temp->data, flag);
		temp = temp->next;
	}
	temp = NULL;
}
