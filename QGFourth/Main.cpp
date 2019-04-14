#include "QgSort.h"
#include <ctime>

constexpr const int N1 = 1000;
constexpr const int N2 = 10000;
constexpr const int N3 = 100000;
constexpr const int MAX = 10000000;

void TextSort();
void TextSortTime();
void ShowResult(int* a, int len);

int main()
{
	int choice = 0;
	std::cout << "请输入你要测试的内容" << std::endl;
	std::cout << "1、排序算法运行时间" << std::endl;
	std::cout << "2、输入数据测试" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		TextSortTime();
		system("cls");
		break;
	case 2:
		TextSort();
		system("cls");
		break;
	default:
		break;
	}
	return 0;
}

void TextSort()
{
	int length = 0;
	char choice = 'a';
	int* arr = new int[100];
	while (1)
	{
		length = 0;
		std::cout << "小组要求测试：" << std::endl;
		while (1)
		{
			std::cout << "请输入元素值：";
			while (!(std::cin >> arr[length++]))
			{
				--length;
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			
			std::cout << "是否继续输入元素值（y/n）?" << std::endl;
			while (!(std::cin >> choice))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "请输入y/n" << std::endl;
			}
			std::cout << std::endl;
			if (choice == 'n' || choice == 'N')
			{
				break;
			}
		}
		ShowResult(arr, length);
		system("pause");
		system("cls");
	}
	delete arr;
}

void TextSortTime()
{
	Sort yaya;
	int arr1[N1]{ 0 };
	int arr2[N2]{ 0 };
	int arr3[N3]{ 0 };
	int temp1[N1]{ 0 };
	int temp2[N2]{ 0 };
	int temp3[N3]{ 0 };
	while(1)
	{
		srand((unsigned)time(NULL));
		for (int i = 0; i < N1; ++i) {
			arr1[i] = rand() % MAX;
		}
		for (int i = 0; i < N2; ++i) {
			arr2[i] = rand() % MAX;
		}
		for (int i = 0; i < N3; ++i) {
			arr3[i] = rand() % MAX;
		}

		clock_t start_time1 = 0;
		clock_t end_time1 = 0;
		clock_t start_time2 = 0;
		clock_t end_time2 = 0;
		clock_t start_time3 = 0;
		clock_t end_time3 = 0;

		int choice = 0;
		std::cout << "请输入你的选择：" << std::endl;
		std::cout << "1、插入排序" << std::endl;
		std::cout << "2、归并排序" << std::endl;
		std::cout << "3、快速排序（递归版）" << std::endl;
		std::cout << "4、快速排序（非递归版）" << std::endl;
		std::cout << "5、计数排序" << std::endl;
		std::cout << "6、基数计数排序" << std::endl;
		std::cout << "7、颜色排序" << std::endl;
		std::cout << "8、自拟排序" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1://插入排序
			std::cout << "1、插入排序：" << std::endl;
			start_time1 = clock();
			{
				yaya.InsertSrot(arr1, N1);
			}
			end_time1 = clock();
			start_time2 = clock();
			{
				yaya.InsertSrot(arr2, N2);
			}
			end_time2 = clock();
			start_time3 = clock();
			{
				yaya.InsertSrot(arr3, N3);
			}
			end_time3 = clock();

			std::cout << "一千级别：";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "一万级别：";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "十万级别：";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			break;
		case 2://归并排序
			std::cout << std::endl;
			std::cout << "2、归并排序：" << std::endl;
			start_time1 = clock();
			{
				yaya.MergeSort(arr1, 0, N1 - 1, temp1);
			}
			end_time1 = clock();
			start_time2 = clock();
			{
				yaya.MergeSort(arr2, 0, N2 - 1, temp2);
			}
			end_time2 = clock();
			start_time3 = clock();
			{
				yaya.MergeSort(arr3, 0, N3 - 1, temp3);
			}
			end_time3 = clock();

			std::cout << "一千级别：";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "一万级别：";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "十万级别：";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 3://快速排序（递归版）
			std::cout << "3、快速排序（递归版）：" << std::endl;
			start_time1 = clock();
			{
				yaya.QuickSort(arr1, 0, N1 - 1);
			}
			end_time1 = clock();
			start_time2 = clock();
			{
				yaya.QuickSort(arr2, 0, N2 - 1);
			}
			end_time2 = clock();
			start_time3 = clock();
			{
				yaya.QuickSort(arr3, 0, N3 - 1);
			}
			end_time3 = clock();

			std::cout << "一千级别：";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "一万级别：";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "十万级别：";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 4://快速排序（非递归版）
			std::cout << "4、快速排序（非递归版）：" << std::endl;
			start_time1 = clock();
			{
				yaya.QuickSort(arr1, N1);
			}
			end_time1 = clock();
			start_time2 = clock();
			{
				yaya.QuickSort(arr2, N2);
			}
			end_time2 = clock();
			start_time3 = clock();
			{
				yaya.QuickSort(arr3, N3);
			}
			end_time3 = clock();

			std::cout << "一千级别：";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "一万级别：";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "十万级别：";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 5://计数排序
			std::cout << std::endl;
			std::cout << "5、计数排序：" << std::endl;
			start_time1 = clock();
			{
				yaya.CountSort(arr1, N1);
			}
			end_time1 = clock();
			start_time2 = clock();
			{
				yaya.CountSort(arr2, N2);
			}
			end_time2 = clock();
			start_time3 = clock();
			{
				yaya.CountSort(arr3, N3);
			}
			end_time3 = clock();

			std::cout << "一千级别：";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "一万级别：";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "十万级别：";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 6://基数计数排序
			std::cout << "6、基数计数排序：" << std::endl;
			start_time1 = clock();
			{
				yaya.RadixCountSort(arr1, N1);
			}
			end_time1 = clock();
			start_time2 = clock();
			{
				yaya.RadixCountSort(arr2, N2);
			}
			end_time2 = clock();
			start_time3 = clock();
			{
				yaya.RadixCountSort(arr3, N3);
			}
			end_time3 = clock();

			std::cout << "一千级别：";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "一万级别：";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "十万级别：";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 7://颜色排序
			std::cout << "7、颜色排序：" << std::endl;
			for (int i = 0; i < N3; i++)
			{
				arr3[i] = rand() % 3;
			}
			start_time3 = clock();
			{
				yaya.RadixCountSort(arr3, N3);
			}
			end_time3 = clock();

			std::cout << "十万级别：";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 8://自拟排序
			std::cout << std::endl;
			std::cout << "7、自拟排序：" << std::endl;
			start_time1 = clock();
			{
				yaya.MySort(arr1, N1);
			}
			end_time1 = clock();
			start_time2 = clock();
			{
				yaya.MySort(arr2, N2);
			}
			end_time2 = clock();
			start_time3 = clock();
			{
				yaya.MySort(arr3, N3);
			}
			end_time3 = clock();

			std::cout << "一千级别：";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "一万级别：";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "十万级别：";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}

void ShowResult(int* a,int len)
{
	Sort yaya;
	int* temp = new int[len];
	for (int i = 0; i < len; i++)
	{
		temp[i] = 0;
	}
	int choice = 0;
	std::cout << "请输入你的选择：" << std::endl;
	std::cout << "1、插入排序" << std::endl;
	std::cout << "2、归并排序" << std::endl;
	std::cout << "3、快速排序（递归版）" << std::endl;
	std::cout << "4、快速排序（非递归版）" << std::endl;
	std::cout << "5、计数排序" << std::endl;
	std::cout << "6、基数计数排序" << std::endl;
	std::cout << "7、颜色排序" << std::endl;
	std::cout << "8、自拟排序" << std::endl;
	std::cin >> choice;
	std::wcout << "排序前：" << std::endl;
	yaya.Print(a, len);
	switch (choice)
	{
	case 1://插入排序
		yaya.InsertSrot(a, len);
		break;
	case 2://归并排序
		yaya.MergeSort(a, 0, len - 1, temp);
		break;
	case 3://快速排序（递归版）
		yaya.QuickSort(a, 0, len - 1);
		break;
	case 4://快速排序（非递归版）
		yaya.QuickSort(a, len);
		break;
	case 5://计数排序
		yaya.CountSort(a, len);
		break;
	case 6://基数计数排序
		yaya.RadixCountSort(a, len);
		break;
	case 7://颜色排序
		yaya.ColorSort(a,len);
		break;
	case 8://自拟排序
		yaya.MySort(a,len);
		break;
	default:
		break;
	}
	std::cout << "排序结果如下" << std::endl;
	yaya.Print(a, len);
	delete temp;
}
