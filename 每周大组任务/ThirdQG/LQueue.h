#ifndef LQUEUE_H_INCLUDE
#define LQUEUE_H_INCLUDE

/**********************************************
*	Project:������ʽ����
*	Author������yaya
*	Location������
*	Date��2019��4��6��09:47:02
**********************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Yaya.h"

//��ʼ������
#define InitLQueue(queue)\
queue->front = queue->rear = (Node*)malloc(sizeof(Node));\
queue->front->next = NULL;\
queue->length = 0;

//����
#define DeLQueue(queue, d)\
if (IsEmptyLQueue(queue))\
{\
	printf("����Ϊ�գ�����ʧ�ܣ�");\
	return;\
}\
Node* tp = q->front->next;\
if(queue->length==0)\
{\
	queue->rear = queue->front;\
}\
*d = tp->data;\
queue->front->next = tp->next;\
free(tp);\
queue->length--;\
printf("���ӳɹ���");\

//���
#define EnLQueue(queue, d)\
Node* temp = (Node*)malloc(sizeof(Node));\
if(temp)\
{\
	temp->data = d;\
	temp->next = NULL;\
	q->rear->next = temp;\
	q->rear = temp;\
}\
queue->length++;\
printf("��ӳɹ���");

//��ӡ����
#define DLPrint(data,flag)\
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


//��ʽ���нṹ
typedef struct node
{
	void *data;                   //������ָ��
	struct node *next;            //ָ��ǰ������һ���
} Node;

typedef struct Lqueue
{
	Node *front;					//��ͷ
	Node *rear;						//��β
	size_t length;					//���г���
} LQueue;


//���ٶ���
void DestoryLQueue(LQueue* queue);

//�������Ƿ�Ϊ��
bool IsEmptyLQueue(LQueue* queue);

//�鿴��ͷԪ��
void GetHeadLQueue(LQueue* queue, void** data);

//�鿴���г���
size_t GetLengthLQueue(LQueue* queue);

//��ն���
void ClearLQueue(LQueue* queue);

//������������
void TraverseLQueue(const LQueue* queue, void(*func)(void*, DATATYPE), DATATYPE flag);

//��ӡ����
void LQPrint(LQueue* queue, DATATYPE flag);


#endif // !LQUEUE_H_INCLUDE

