#include "AQueue.h"
#include "LQueue.h"
#include <Windows.h>

#define MyScanf(data,type)\
char c = '0';\
while ((c=getchar())!='\n'&&c!=EOF);\
if (type == I)\
{\
	scanf("%d", data);\
}\
if (type == C)\
{\
	scanf("%c", data);\
}\
if (type == F)\
{\
	scanf("%f", data);\
}\
getchar();\

void TextAQueue();
void TextLQueue();
void Func(void* a,DATATYPE type);
DATATYPE ChoiceType();


int main()
{
	printf("请选择你要测试的队列\n1、循环队列\n2、链式队列\n");
	int choice = 0;
	scanf("%d", &choice);
	if (choice == 1)
	{
		TextAQueue();
	}
	if(choice == 2)
	{
		TextLQueue();
	}
	return 0;
	
}

void TextAQueue()
{
	int* dataInt = (int*)malloc(sizeof(int)*30);
	char dataChar[31] = "a";
	float* dataFloat = (float*)malloc(sizeof(float)*30);
	int count = 0;
	int choice = 0;
	DATATYPE type = ChoiceType();
	void* data = NULL;
	void* temp = NULL;
	if (type == I)
	{
		data = dataInt;
	}
	if (type == C)
	{
		data = dataChar;
	}
	if (type == F)
	{
		data = dataFloat;
	}
	AQueue* q = NULL;
	InitAQueue(q);
	while (1)
	{
		printf("\n-------循环队列操作-------\n");
		printf("1、查看队头元素\n2、查看队列长度\n3、入队\n4、出队\n5、清空队列\n6、遍历函数操作\n7、遍历\n8、退出");
		printf("\n请输入你要执行的操作：");
		if ((scanf("%d", &choice)) != 1)
		{
			char c;
			while ((c = getchar() != '\n') && c != EOF);
		}
		switch (choice)
		{
		case 1://查看队头元素
			GetHeadAQueue(q, &temp);
			if (temp)
			{
				DPrint(temp, type);
				temp = NULL;
			}
			break;
		case 2://查看队列长度
			GetLengthAQueue(q);
			break;
		case 3://入队
			printf("请输入你要入队的元素！");
			if (type == I)
			{
				MyScanf(dataInt + count, type);
			}
			if (type == C)
			{
				MyScanf(dataChar + count, type);
			}
			if (type == F)
			{
				MyScanf(dataFloat + count, type);
			}
			EnAQueue(q,data);
			++count;
			if (type == I)
			{
				data = dataInt + count;
			}
			if (type == C)
			{
				data = dataChar + count;
			}
			if (type == F)
			{
				data = dataFloat + count;
			}
			break;
		case 4://出队
			DeAQueue(q,&temp);
			if (temp)
			{
				DPrint(temp, type);
				temp = NULL;
			}
			break;
		case 5://清空队列
			ClearAQueue(q);
			break;
		case 6://遍历函数操作
			TraverseAQueue(q, Func,type);
			break;
		case 7://遍历
			AQPrint(q,type);
			break;
		case 8://退出
			exit(0);
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
	free(dataInt);
	free(dataFloat);
}

void TextLQueue()
{
	int* dataInt = (int*)malloc(sizeof(int) * 30);
	char dataChar[31] = "a";
	float* dataFloat = (float*)malloc(sizeof(float) * 30);
	int count = 0;
	int choice = 0;
	DATATYPE type = ChoiceType();
	void* data = NULL;
	void* temp = NULL;
	if (type == I)
	{
		data = dataInt;
	}
	if (type == C)
	{
		data = dataChar;
	}
	if (type == F)
	{
		data = dataFloat;
	}
	LQueue* q = (LQueue*)malloc(sizeof(LQueue));
	InitLQueue(q);
	while (1)
	{
		printf("\n-------循环队列操作-------\n");
		printf("1、查看队头元素\n2、查看队列长度\n3、入队\n4、出队\n5、清空队列\n6、遍历函数操作\n7、遍历\n8、退出");
		printf("\n请输入你要执行的操作：");
		if ((scanf("%d", &choice)) != 1)
		{
			char c;
			while ((c = getchar() != '\n') && c != EOF);
		}
		switch (choice)
		{
		case 1://查看队头元素
			GetHeadLQueue(q, &temp);
			if (temp)
			{
				DLPrint(temp, type);
				temp = NULL;
			}
			break;
		case 2://查看队列长度
			GetLengthLQueue(q);
			break;
		case 3://入队
			printf("请输入你要入队的元素！");
			if (type == I)
			{
				MyScanf(dataInt + count, type);
			}
			if (type == C)
			{
				MyScanf(dataChar + count, type);
			}
			if (type == F)
			{
				MyScanf(dataFloat + count, type);
			}
			EnLQueue(q, data);
			++count;
			if (type == I)
			{
				data = dataInt + count;
			}
			if (type == C)
			{
				data = dataChar + count;
			}
			if (type == F)
			{
				data = dataFloat + count;
			}
			break;
		case 4://出队
			DeLQueue(q, &temp);
			if (temp)
			{
				DLPrint(temp, type);
				temp = NULL;
			}
			break;
		case 5://清空队列
			ClearLQueue(q);
			break;
		case 6://遍历函数操作
			TraverseLQueue(q, Func, type);
			break;
		case 7://遍历
			LQPrint(q, type);
			break;
		case 8://退出
			exit(0);
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
	free(dataInt);
	free(dataFloat);
	free(q);
}

void Func(void * a,DATATYPE type)
{
	if (type == I)
	{
		int* temp = (int*)malloc(sizeof(int));
		*temp = 520;
		memcpy(a, temp, sizeof(int));
	}
	if (type == C)
	{
		char* temp = (char*)malloc(sizeof(char));
		*temp = 'a';
		memcpy(a, temp, sizeof(char));
	}
	if (type == F)
	{
		float* temp = (float*)malloc(sizeof(float));
		*temp = 52.0;
		memcpy(a, temp, sizeof(float));
	}
}

DATATYPE ChoiceType()
{
	printf("请输入你要测试的类型：\n1、char\n2、float\n3、int\n");
	int choice = 0;
	DATATYPE result = I;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1://char
		result = C;
		break;
	case 2://char
		result = F;
		break;
	case 3://int
		break;
	default:
		break;
	}
	return result;
}
