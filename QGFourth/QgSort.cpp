#include "QgSort.h"
#include <cstring>

/*构造函数*/
Sort::Sort()
{
}

/*析构函数*/
Sort::~Sort()
{
}

/*插入排序*/
void Sort::InsertSrot(int* a, int len)
{
	int temp = 0;
	for (int i = 1; i < len; i++)
	{
		temp = a[i];
		int j = i - 1;
		for (; j >= 0 && a[j] > temp; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}

/*归并排序（合并数组）*/
void Sort::MergeSort(int * a, int begin, int mid, int end, int * temp)
{
	int i = begin;
	int j = mid + 1;
	int k = begin;
	while (i <= mid && j <= end)
	{
		if (a[i] < a[j])
		{
			temp[k++] = a[i++];
		}
		else
		{
			temp[k++] = a[j++];
		}
	}
	while (i <= mid)
	{
		temp[k++] = a[i++];
	}
	while (j <= end)
	{
		temp[k++] = a[j++];
	}
	memcpy(a + begin, temp + begin, sizeof(int)*(end - begin + 1));
}

/*归并排序*/
void Sort::MergeSort(int * a, int begin, int end, int * temp)
{
	int mid = 0;
	if (end > begin)
	{
		mid = begin + (end - begin) / 2;
		MergeSort(a, begin, mid, temp);
		MergeSort(a, mid + 1, end, temp);
		MergeSort(a, begin, mid, end, temp);
	}
}

/*快速排序（递归版）*/
void Sort::QuickSort(int * a, int begin, int end)
{
	if (end > begin)
	{
		int index = Partition(a, begin, end);
		QuickSort(a, begin, index - 1);
		QuickSort(a, index + 1, end);
	}
}

/*快速排序（非递归版）*/
void Sort::QuickSort(int * a, int len)
{
	if (a == NULL)
	{
		return;
	}
	std::stack<int> temp;
	int i, j, k;
	temp.push(len - 1);
	temp.push(0);
	while (!temp.empty())
	{
		i = temp.top();
		temp.pop();
		j = temp.top();
		temp.pop();
		if (i < j)
		{
			k = Partition(a, i, j);
			if (k > i)
			{
				temp.push(k - 1);
				temp.push(i);
			}
			if (j > k)
			{
				temp.push(j);
				temp.push(k + 1);
			}
		}
	}
}

/*快速排序（枢轴存放）*/
int Sort::Partition(int * a, int begin, int end)
{
	int low = begin + 1;
	int high = end;
	int pivot = a[begin];
	while (high > low)
	{
		while (high >= low && a[low] <= pivot)
		{
			++low;
		}
		while (high >= low && a[high] > pivot)
		{
			--high;
		}
		if (high > low)
		{
			Swap(a + low, a + high);
		}
	}

	while (high > begin && a[high] >= pivot)
	{
		--high;
	}
	if (a[high] < pivot)
	{
		a[begin] = a[high];
		a[high] = pivot;
		return high;
	}
	return begin;
}

/*计数排序*/
void Sort::CountSort(int * a, int len)
{
	int index = 0;
	int min, max;
	min = max = a[0];

	for (int i = 1; i < len; i++)
	{
		min = (a[i] < min) ? a[i] : min;
		max = (a[i] > max) ? a[i] : max;
	}

	int k = max - min + 1;
	int* temp = new int[k];

	for (int i = 0; i < k; i++)
	{
		temp[i] = 0;
	}
	for (int i = 0; i < len; i++)
	{
		temp[a[i] - min]++;
	}
	for (int i = min; i <= max; i++)
	{
		for (int j = 0; j < temp[i - min]; j++)
		{
			a[index++] = i;
		}
	}

	delete temp;
}

/*基数计数排序*/
void Sort::RadixCountSort(int * a, int len)
{
	int max = 0;
	int digitPosition = 1;
	int* bucket = new int[len];
	for (int i = 0; i < len; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
	}

	while (max / digitPosition > 0)
	{
		int digitCount[10] = { 0 };
		for (int i = 0; i < len; i++)
		{
			digitCount[a[i] / digitPosition % 10]++;
		}
		for (int i = 1; i < 10; i++)
		{
			digitCount[i] += digitCount[i - 1];
		}
		for (int i = len - 1; i >= 0; i--)
		{
			bucket[--digitCount[a[i] / digitPosition % 10]] = a[i];
		}
		for (int i = 0; i < len; i++)
		{
			a[i] = bucket[i];
		}
		digitPosition *= 10;
	}
	delete bucket;
}

/*颜色排序*/
void Sort::ColorSort(int * a, int len)
{
	int* zero = a;
	int* two = a + len - 1;
	int* ptr = a  + 1;
	while(1)
	{
		if (*ptr == 0)
		{
			Swap(ptr, zero);
			++zero;
		}
		if (*ptr == 2)
		{
			Swap(ptr, two);
			--two;
		}
		if (ptr == two || ptr > two)
		{
			break;
		}
		if (*ptr == 1 || ptr == zero)
		{
			++ptr;
		}
	}
}

/*自拟排序*/
void Sort::MySort(int * a,int len)
{
	int increment = len;
	int temp{ 0 };
	do {
		increment = increment / 3 + 1;
		for (int i = increment; i < len; ++i)
		{
			if (a[i - increment] > a[i])
			{
				temp = a[i];
				int j = i - increment;
				do {
					a[j + increment] = a[j];
					j -= increment;
				} while (j >= 0 && a[j] > temp);
				a[j + increment] = temp;
			}
		}
	} while (increment > 1);
}

/*交换元素*/
void Sort::Swap(int * a, int * b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*打印数组*/
void Sort::Print(int* a, int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cout << a[i] << '\t';
	}
	std::cout << std::endl;
}
