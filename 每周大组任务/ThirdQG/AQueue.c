#include "AQueue.h"

/*���ٶ���*/
void DestoryAQueue(AQueue * queue)
{
	free(queue);
}

/*�ж϶����Ƿ�����*/
bool IsFullAQueue(AQueue * queue)
{
	if (queue->length == MAX_SIZE)
	{
		printf("����������");
		return true;
	}
	return false;
}

/*�ж϶����Ƿ�Ϊ��*/
bool IsEmptyAQueue(AQueue * queue)
{
	if (queue->length == 0)
	{
		printf("����Ϊ�գ�");
		return true;
	}
	return false;
}

/*���ض�ͷԪ��*/
void GetHeadAQueue(AQueue * queue,void** data)
{
	if (queue->length == 0)
	{
		printf("����Ϊ�գ�");
		return;
	}
	*data = queue->data[queue->front];
	return;
}

/*���ض��г���*/
size_t GetLengthAQueue(AQueue* queue)
{
	printf("���г���Ϊ%d\n", queue->length);
	return queue->length;
}

/*��ն���*/
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

/*�������е��ú���*/
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
