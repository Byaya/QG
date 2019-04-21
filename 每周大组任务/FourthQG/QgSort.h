#pragma once

/***************************************
*	Project��QG������Ĵο��ˣ����������㷨��
*	Function�����������㷨ͷ�ļ�
*	Location������
*	Date��2019��4��13��08:56:38
***************************************/

#include <iostream>
#include <stack>

class Sort
{
public:
	 Sort();
	~Sort();
	/*��������*/
	void InsertSrot(int* a,int len);

	/*�鲢���򣨺ϲ����飩*/
	void MergeSort(int* a, int begin, int mid, int end, int* temp);

	/*�鲢����*/
	void MergeSort(int* a, int begin, int end, int* temp);

	/*�������򣨵ݹ�棩*/
	void QuickSort(int* a, int begin, int end);

	/*�������򣨷ǵݹ�棩*/
	void QuickSort(int* a, int len);

	/*�������������ţ�*/
	int Partition(int* a, int begin, int end);

	/*��������*/
	void CountSort(int* a, int len);

	/*������������*/
	void RadixCountSort(int* a, int len);

	/*��ɫ����*/
	void ColorSort(int* a, int len);

	/*��������*/
	void MySort(int* a,int len);

	/*����Ԫ��*/
	void Swap(int* a, int * b);

	/*��ӡ����*/
	void Print(int* a, int len);
private:

};