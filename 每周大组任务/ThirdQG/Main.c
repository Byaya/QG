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
	printf("��ѡ����Ҫ���ԵĶ���\n1��ѭ������\n2����ʽ����\n");
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
		printf("\n-------ѭ�����в���-------\n");
		printf("1���鿴��ͷԪ��\n2���鿴���г���\n3�����\n4������\n5����ն���\n6��������������\n7������\n8���˳�");
		printf("\n��������Ҫִ�еĲ�����");
		if ((scanf("%d", &choice)) != 1)
		{
			char c;
			while ((c = getchar() != '\n') && c != EOF);
		}
		switch (choice)
		{
		case 1://�鿴��ͷԪ��
			GetHeadAQueue(q, &temp);
			if (temp)
			{
				DPrint(temp, type);
				temp = NULL;
			}
			break;
		case 2://�鿴���г���
			GetLengthAQueue(q);
			break;
		case 3://���
			printf("��������Ҫ��ӵ�Ԫ�أ�");
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
		case 4://����
			DeAQueue(q,&temp);
			if (temp)
			{
				DPrint(temp, type);
				temp = NULL;
			}
			break;
		case 5://��ն���
			ClearAQueue(q);
			break;
		case 6://������������
			TraverseAQueue(q, Func,type);
			break;
		case 7://����
			AQPrint(q,type);
			break;
		case 8://�˳�
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
		printf("\n-------ѭ�����в���-------\n");
		printf("1���鿴��ͷԪ��\n2���鿴���г���\n3�����\n4������\n5����ն���\n6��������������\n7������\n8���˳�");
		printf("\n��������Ҫִ�еĲ�����");
		if ((scanf("%d", &choice)) != 1)
		{
			char c;
			while ((c = getchar() != '\n') && c != EOF);
		}
		switch (choice)
		{
		case 1://�鿴��ͷԪ��
			GetHeadLQueue(q, &temp);
			if (temp)
			{
				DLPrint(temp, type);
				temp = NULL;
			}
			break;
		case 2://�鿴���г���
			GetLengthLQueue(q);
			break;
		case 3://���
			printf("��������Ҫ��ӵ�Ԫ�أ�");
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
		case 4://����
			DeLQueue(q, &temp);
			if (temp)
			{
				DLPrint(temp, type);
				temp = NULL;
			}
			break;
		case 5://��ն���
			ClearLQueue(q);
			break;
		case 6://������������
			TraverseLQueue(q, Func, type);
			break;
		case 7://����
			LQPrint(q, type);
			break;
		case 8://�˳�
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
	printf("��������Ҫ���Ե����ͣ�\n1��char\n2��float\n3��int\n");
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
