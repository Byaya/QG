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
	std::cout << "��������Ҫ���Ե�����" << std::endl;
	std::cout << "1�������㷨����ʱ��" << std::endl;
	std::cout << "2���������ݲ���" << std::endl;
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
		std::cout << "С��Ҫ����ԣ�" << std::endl;
		while (1)
		{
			std::cout << "������Ԫ��ֵ��";
			while (!(std::cin >> arr[length++]))
			{
				--length;
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			
			std::cout << "�Ƿ��������Ԫ��ֵ��y/n��?" << std::endl;
			while (!(std::cin >> choice))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "������y/n" << std::endl;
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
		std::cout << "���������ѡ��" << std::endl;
		std::cout << "1����������" << std::endl;
		std::cout << "2���鲢����" << std::endl;
		std::cout << "3���������򣨵ݹ�棩" << std::endl;
		std::cout << "4���������򣨷ǵݹ�棩" << std::endl;
		std::cout << "5����������" << std::endl;
		std::cout << "6��������������" << std::endl;
		std::cout << "7����ɫ����" << std::endl;
		std::cout << "8����������" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1://��������
			std::cout << "1����������" << std::endl;
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

			std::cout << "һǧ����";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "һ�򼶱�";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "ʮ�򼶱�";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			break;
		case 2://�鲢����
			std::cout << std::endl;
			std::cout << "2���鲢����" << std::endl;
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

			std::cout << "һǧ����";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "һ�򼶱�";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "ʮ�򼶱�";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 3://�������򣨵ݹ�棩
			std::cout << "3���������򣨵ݹ�棩��" << std::endl;
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

			std::cout << "һǧ����";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "һ�򼶱�";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "ʮ�򼶱�";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 4://�������򣨷ǵݹ�棩
			std::cout << "4���������򣨷ǵݹ�棩��" << std::endl;
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

			std::cout << "һǧ����";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "һ�򼶱�";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "ʮ�򼶱�";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 5://��������
			std::cout << std::endl;
			std::cout << "5����������" << std::endl;
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

			std::cout << "һǧ����";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "һ�򼶱�";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "ʮ�򼶱�";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 6://������������
			std::cout << "6��������������" << std::endl;
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

			std::cout << "һǧ����";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "һ�򼶱�";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "ʮ�򼶱�";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 7://��ɫ����
			std::cout << "7����ɫ����" << std::endl;
			for (int i = 0; i < N3; i++)
			{
				arr3[i] = rand() % 3;
			}
			start_time3 = clock();
			{
				yaya.RadixCountSort(arr3, N3);
			}
			end_time3 = clock();

			std::cout << "ʮ�򼶱�";
			std::cout << static_cast<double>(end_time3 - start_time3) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

			break;
		case 8://��������
			std::cout << std::endl;
			std::cout << "7����������" << std::endl;
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

			std::cout << "һǧ����";
			std::cout << static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "һ�򼶱�";
			std::cout << static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
			std::cout << "ʮ�򼶱�";
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
	std::cout << "���������ѡ��" << std::endl;
	std::cout << "1����������" << std::endl;
	std::cout << "2���鲢����" << std::endl;
	std::cout << "3���������򣨵ݹ�棩" << std::endl;
	std::cout << "4���������򣨷ǵݹ�棩" << std::endl;
	std::cout << "5����������" << std::endl;
	std::cout << "6��������������" << std::endl;
	std::cout << "7����ɫ����" << std::endl;
	std::cout << "8����������" << std::endl;
	std::cin >> choice;
	std::wcout << "����ǰ��" << std::endl;
	yaya.Print(a, len);
	switch (choice)
	{
	case 1://��������
		yaya.InsertSrot(a, len);
		break;
	case 2://�鲢����
		yaya.MergeSort(a, 0, len - 1, temp);
		break;
	case 3://�������򣨵ݹ�棩
		yaya.QuickSort(a, 0, len - 1);
		break;
	case 4://�������򣨷ǵݹ�棩
		yaya.QuickSort(a, len);
		break;
	case 5://��������
		yaya.CountSort(a, len);
		break;
	case 6://������������
		yaya.RadixCountSort(a, len);
		break;
	case 7://��ɫ����
		yaya.ColorSort(a,len);
		break;
	case 8://��������
		yaya.MySort(a,len);
		break;
	default:
		break;
	}
	std::cout << "����������" << std::endl;
	yaya.Print(a, len);
	delete temp;
}
