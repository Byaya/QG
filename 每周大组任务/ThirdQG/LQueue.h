#ifndef LQUEUE_H_INCLUDE
#define LQUEUE_H_INCLUDE

/**********************************************
*	Project:泛型链式队列
*	Author：风雅yaya
*	Location：广州
*	Date：2019年4月6日09:47:02
**********************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Yaya.h"

//初始化队列
#define InitLQueue(queue)\
queue->front = queue->rear = (Node*)malloc(sizeof(Node));\
queue->front->next = NULL;\
queue->length = 0;

//出队
#define DeLQueue(queue, d)\
if (IsEmptyLQueue(queue))\
{\
	printf("队列为空，出队失败！");\
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
printf("出队成功！");\

//入队
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
printf("入队成功！");

//打印数据
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


//链式队列结构
typedef struct node
{
	void *data;                   //数据域指针
	struct node *next;            //指向当前结点的下一结点
} Node;

typedef struct Lqueue
{
	Node *front;					//队头
	Node *rear;						//队尾
	size_t length;					//队列长度
} LQueue;


//销毁队列
void DestoryLQueue(LQueue* queue);

//检查队列是否为空
bool IsEmptyLQueue(LQueue* queue);

//查看队头元素
void GetHeadLQueue(LQueue* queue, void** data);

//查看队列长度
size_t GetLengthLQueue(LQueue* queue);

//清空队列
void ClearLQueue(LQueue* queue);

//遍历函数操作
void TraverseLQueue(const LQueue* queue, void(*func)(void*, DATATYPE), DATATYPE flag);

//打印队列
void LQPrint(LQueue* queue, DATATYPE flag);


#endif // !LQUEUE_H_INCLUDE

