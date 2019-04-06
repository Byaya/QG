#ifndef AQUEUE_H_INCLUDE
#define AQUEUE_H_INCLUDE

/**********************************************
*	Project:泛型循环队列
*	Author：风雅yaya
*	Location：广州
*	Date：2019年4月4日21:22:03
**********************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Yaya.h"

#define MAX_SIZE 30

//初始化队列
#define InitAQueue(queue)\
queue = (AQueue*)malloc(sizeof(AQueue));\
if (!queue)\
{\
	printf("电脑内存不够了啊！");\
	exit(1);\
}\
queue->front = 0;\
queue->rear = 0;\
queue->length=0;

//出队
#define DeAQueue(queue, temp)\
if (IsEmptyAQueue(queue))\
{\
	printf("队列为空，出队失败！");\
	return;\
}\
*temp = queue->data[queue->front];\
queue->front = (queue->front + 1) % MAX_SIZE;\
queue->length--;\
printf("出队成功！");\

//入队
#define EnAQueue(queue, data)\
if (IsFullAQueue(queue))\
{\
	printf("队列已满，入队失败！");\
	return;\
}\
queue->data[queue->rear] = data;\
queue->length++;\
queue->rear = (queue->rear + 1) % MAX_SIZE;\
printf("入队成功！");

//打印数据
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
	void* data[MAX_SIZE];	//数据域
	int front;				//队头
	int rear;				//队尾
	size_t length;			//队列实际长度
}AQueue;


//销毁队列
void DestoryAQueue(AQueue* queue);

//检查队列是否已满
bool IsFullAQueue(AQueue* queue);

//检查队列是否为空
bool IsEmptyAQueue(AQueue* queue);

//查看队头元素
void GetHeadAQueue(AQueue* queue,void** data);

//查看队列长度
size_t GetLengthAQueue(AQueue* queue);

//清空队列
void ClearAQueue(AQueue* queue);

//遍历函数操作
void TraverseAQueue(const AQueue* queue, void(*func)(void*,DATATYPE),DATATYPE flag);

//打印队列
void AQPrint(AQueue* queue,DATATYPE flag);


#endif // !AQUEUE_H_INCLUDE
