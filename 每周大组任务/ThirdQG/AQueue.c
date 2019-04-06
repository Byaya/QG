#include "AQueue.h"

/*销毁队列*/
void DestoryAQueue(AQueue * queue)
{
	free(queue);
}

/*判断队列是否已满*/
bool IsFullAQueue(AQueue * queue)
{
	if (queue->length == MAX_SIZE)
	{
		printf("队列已满！");
		return true;
	}
	return false;
}

/*判断队列是否为空*/
bool IsEmptyAQueue(AQueue * queue)
{
	if (queue->length == 0)
	{
		printf("队列为空！");
		return true;
	}
	return false;
}

/*返回队头元素*/
void GetHeadAQueue(AQueue * queue,void** data)
{
	if (queue->length == 0)
	{
		printf("队列为空！");
		return;
	}
	*data = queue->data[queue->front];
	return;
}

/*返回队列长度*/
size_t GetLengthAQueue(AQueue* queue)
{
	printf("队列长度为%d\n", queue->length);
	return queue->length;
}

/*清空队列*/
void ClearAQueue(AQueue * queue)
{
	int count = queue->front;
	while (count!=queue->rear)
	{
		queue->data[count] = 0;
		count++;
	}
	queue->front = 0;
	queue->rear = 0;
	queue->length = 0;
}

/*遍历队列调用函数*/
void TraverseAQueue(const AQueue * queue, void(*func)(void *,DATATYPE),DATATYPE flag)
{
	size_t count = queue->length;
	int curr = queue->front;
	while (count)
	{
		func(queue->data[curr++],flag);
		count--;
	}
}

void AQPrint(AQueue * queue,DATATYPE flag)
{
	int count = queue->length;
	int temp = queue->front;
	while (count)
	{
		DPrint(queue->data[temp], flag);
		temp = (temp + 1) % MAX_SIZE;
		--count;
	}
}
