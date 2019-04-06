#ifndef AQUEUE_H_INCLUDE
#define AQUEUE_H_INCLUDE

/**********************************************
*	Project:����ѭ������
*	Author������yaya
*	Location������
*	Date��2019��4��4��21:22:03
**********************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Yaya.h"

#define MAX_SIZE 30

//��ʼ������
#define InitAQueue(queue)\
queue = (AQueue*)malloc(sizeof(AQueue));\
if (!queue)\
{\
	printf("�����ڴ治���˰���");\
	exit(1);\
}\
queue->front = 0;\
queue->rear = 0;\
queue->length=0;

//����
#define DeAQueue(queue, temp)\
if (IsEmptyAQueue(queue))\
{\
	printf("����Ϊ�գ�����ʧ�ܣ�");\
	return;\
}\
*temp = queue->data[queue->front];\
queue->front = (queue->front + 1) % MAX_SIZE;\
queue->length--;\
printf("���ӳɹ���");\

//���
#define EnAQueue(queue, data)\
if (IsFullAQueue(queue))\
{\
	printf("�������������ʧ�ܣ�");\
	return;\
}\
queue->data[queue->rear] = data;\
queue->length++;\
queue->rear = (queue->rear + 1) % MAX_SIZE;\
printf("��ӳɹ���");

//��ӡ����
#define DPrint(data,flag)\
if(flag == F)\
{\
	printf("%lf\n", *(float*)data);\
}\
if (flag == C)\
{\
	printf("%c\n", *(char*)data);\
}\
if (flag == I)\
{\
	printf("%d\n", *(int*)data);\
}\

typedef struct AQueue
{
	void* data[MAX_SIZE];	//������
	int front;				//��ͷ
	int rear;				//��β
	size_t length;			//����ʵ�ʳ���
}AQueue;


//���ٶ���
void DestoryAQueue(AQueue* queue);

//�������Ƿ�����
bool IsFullAQueue(AQueue* queue);

//�������Ƿ�Ϊ��
bool IsEmptyAQueue(AQueue* queue);

//�鿴��ͷԪ��
void GetHeadAQueue(AQueue* queue,void** data);

//�鿴���г���
size_t GetLengthAQueue(AQueue* queue);

//��ն���
void ClearAQueue(AQueue* queue);

//������������
void TraverseAQueue(const AQueue* queue, void(*func)(void*,DATATYPE),DATATYPE flag);

//��ӡ����
void AQPrint(AQueue* queue,DATATYPE flag);


#endif // !AQUEUE_H_INCLUDE
