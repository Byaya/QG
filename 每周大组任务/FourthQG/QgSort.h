#pragma once

/***************************************
*	Project：QG大组第四次考核（各种排序算法）
*	Function：各种排序算法头文件
*	Location：广州
*	Date：2019年4月13日08:56:38
***************************************/

#include <iostream>
#include <stack>

class Sort
{
public:
	 Sort();
	~Sort();
	/*插入排序*/
	void InsertSrot(int* a,int len);

	/*归并排序（合并数组）*/
	void MergeSort(int* a, int begin, int mid, int end, int* temp);

	/*归并排序*/
	void MergeSort(int* a, int begin, int end, int* temp);

	/*快速排序（递归版）*/
	void QuickSort(int* a, int begin, int end);

	/*快速排序（非递归版）*/
	void QuickSort(int* a, int len);

	/*快速排序（枢轴存放）*/
	int Partition(int* a, int begin, int end);

	/*计数排序*/
	void CountSort(int* a, int len);

	/*基数计数排序*/
	void RadixCountSort(int* a, int len);

	/*颜色排序*/
	void ColorSort(int* a, int len);

	/*自拟排序*/
	void MySort(int* a,int len);

	/*交换元素*/
	void Swap(int* a, int * b);

	/*打印数组*/
	void Print(int* a, int len);
private:

};