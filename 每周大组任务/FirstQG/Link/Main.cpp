#include "List.h"
#include "QGForwardList.h"
#include "DoubleLInk.h"

void func(int& i);

void TextList();
void TextQGForwardList();
void TextDoubleList();


int main()
{
	std::cout << "��������Ҫ���Ե���������" << std::endl;
	std::cout << "1��������" << std::endl;
	std::cout << "2��˫������" << std::endl;
	std::cout << "3��ģ����˫������" << std::endl;
	int choice;
	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << "��������" << std::endl;
		std::cout << "����������" << std::endl;
	}
	switch (choice)
	{
	case 1://������
		TextQGForwardList();
		break;
	case 2://˫������
		TextList();
		break;
	case 3://ģ����˫������
		TextDoubleList();
		break;
	default:
		break;
	}
	return 0;
}

void func(int& i)
{
	i *= 2;
}

void TextList()
{
	List list;
	while (true)
	{
		int data;
		int pos;
		std::cout << "��������ϣ���ѡ����Ҫ���еĲ���" << std::endl;
		std::cout << "1����ӡ���е�����" << std::endl;
		std::cout << "2�����������е�һ��Ԫ�ص�����e" << std::endl;
		std::cout << "3���������������һ��Ԫ�ص�����" << std::endl;
		std::cout << "4���������һ��Ԫ��ǰ���Ԫ��e" << std::endl;
		std::cout << "5��ɾ�������һ��Ԫ��" << std::endl;
		std::cout << "6�����������һ��Ԫ�غ����Ԫ��e" << std::endl;
		std::cout << "7��ɾ���������һ��Ԫ��" << std::endl;
		std::cout << "8��ɾ������λ��Ԫ��" << std::endl;
		std::cout << "9���������" << std::endl;
		std::cout << "10������Ԫ���Ƿ����" << std::endl;
		std::cout << "11������������Ԫ�ص�����" << std::endl;
		std::cout << "12����������, ��ÿ��Ԫ�ص���visitָ��ĺ���" << std::endl;
		int choice;
		while (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "��������" << std::endl;
			std::cout << "����������" << std::endl;
		}
		switch (choice)
		{
		case 1://��ӡ���е�����
			list.Print();
			break;
		case 2://���������е�һ��Ԫ�ص�����
			list.front();
			break;
		case 3://�������������һ��Ԫ�ص�����
			list.back();
			break;
		case 4://�������һ��Ԫ��ǰ���Ԫ��
			std::cout << "��������Ҫ�����Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.push_front(data);
			list.Print();
			break;
		case 5://ɾ�������һ��Ԫ��
			list.pop_front();
			list.Print();
			break;
		case 6://���������һ��Ԫ�غ����Ԫ��e
			std::cout << "��������Ҫ�����Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.push_back(data);
			list.Print();
			break;
		case 7://ɾ���������һ��Ԫ��
			list.pop_back();
			list.Print();
			break;
		case 8://ɾ������λ��Ԫ��
			std::cout << "��������Ҫɾ����Ԫ��λ��" << std::endl;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.erase(pos);
			list.Print();
			break;
		case 9://�������
			list.clear();
			break;
		case 10://����Ԫ���Ƿ����
			std::cout << "��������Ҫ���ҵ�Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			if (list.contain(data))
			{
				std::cout << "��Ԫ�ش���" << std::endl;
			}
			else
			{
				std::cout << "��Ԫ�ز�����" << std::endl;
			}
			break;
		case 11://����������Ԫ�ص�����
			list.size();
			break;
		case 12://��������, ��ÿ��Ԫ�ص���visitָ��ĺ���
			list.traverse(func);
			list.Print();
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}

void TextQGForwardList()
{
	QGForwardList list;
	while (true)
	{
		std::cout << "��������ϣ���ѡ����Ҫ���еĲ���" << std::endl;
		std::cout << "1�����������е�һ��Ԫ�ص�����" << std::endl;
		std::cout << "2���������һ��Ԫ��ǰ���Ԫ��e" << std::endl;
		std::cout << "3��ɾ�������һ��Ԫ��" << std::endl;
		std::cout << "4�����������һ��Ԫ�غ����Ԫ��e" << std::endl;
		std::cout << "5��ɾ���������һ��Ԫ��" << std::endl;
		std::cout << "6��������ĵ�index + 1��Ԫ��ǰ����Ԫ��e" << std::endl;
		std::cout << "7��ɾ������λ��Ԫ��" << std::endl;
		std::cout << "8���������" << std::endl;
		std::cout << "9������Ԫ���Ƿ����" << std::endl;
		std::cout << "10����������, ��ÿ��Ԫ�ص���visitָ��ĺ���" << std::endl;
		std::cout << "11����ת����1234��ת����4321" << std::endl;
		std::cout << "12�������л�" << std::endl;
		std::cout << "13��ż�ڵ㷴ת��1234��ת����2143" << std::endl;
		std::cout << "14�������м�ڵ�" << std::endl;
		std::cout << "15����ӡ����" << std::endl;
		int choice;
		while (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "��������" << std::endl;
			std::cout << "����������" << std::endl;
		}
		switch (choice)
		{
		case 1:
			list.front();
			break;
		case 2:
			std::cout << "��������Ҫ�����Ԫ��ֵ" << std::endl;
			int data;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.push_front(data);
			list.Print();
			break;
		case 3://ɾ������ĵ�һ��Ԫ��
			list.pop_front();
			list.Print();
			break;
		case 4://���������һ��Ԫ�غ����Ԫ��
			std::cout << "��������Ҫ�����Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.push_back(data);
			list.Print();
			break;
		case 5://ɾ���������һ��Ԫ��
			list.pop_back();
			list.Print();
			break;
		case 6://������ĵ�index + 1��Ԫ��ǰ����Ԫ��e
			std::cout << "��������Ҫ�����Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			std::cout << "��������Ҫ�����λ��" << std::endl;
			int pos;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.insert(pos, data);
			list.Print();
			break;
		case 7://ɾ������λ��Ԫ��
			std::cout << "��������Ҫɾ����Ԫ�ص�λ��" << std::endl;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.erase(pos);
			list.Print();
			break;
		case 8://�������
			list.clear();
			break;
		case 9://����Ԫ���Ƿ����
			std::cout << "��������Ҫ���ҵ�Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			if (list.contain(data))
			{
				std::cout << "��Ԫ�ش���" << std::endl;
			}
			else
			{
				std::cout << "��Ԫ�ز�����" << std::endl;
			}
			break;
		case 10://��������, ��ÿ��Ԫ�ص���visitָ��ĺ���
			list.traverse(func);
			list.Print();
			break;
		case 11://��ת����1234��ת����4321
			list.reverse();
			list.Print();
			break;
		case 12://�����л�
			if (list.isLoop())
			{
				std::cout << "�л�" << std::endl;
			}
			else
			{
				std::cout << "�޻�" << std::endl;
			}
			break;
		case 13://ż�ڵ㷴ת��1234��ת����2143
			list.reverseEven();
			list.Print();
			break;
		case 14://�����м�ڵ�
			list.middleElem();
			break;
		case 15://��ӡ����
			list.Print();
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}

void TextDoubleList()
{
	DoubleLInk<int> list;
	while (true)
	{
		int data;
		int pos;
		std::cout << "��������ϣ���ѡ����Ҫ���еĲ���" << std::endl;
		std::cout << "1��������λ�ò���Ԫ��" << std::endl;
		std::cout << "2���ڱ�ͷ����Ԫ��" << std::endl;
		std::cout << "3���ڱ�β����Ԫ��" << std::endl;
		std::cout << "4��ɾ������λ�õ�Ԫ��" << std::endl;
		std::cout << "5��ɾ����ͷԪ��" << std::endl;
		std::cout << "6��ɾ����βԪ��" << std::endl;
		std::cout << "7���������" << std::endl;
		std::cout << "8��ð������" << std::endl;
		std::cout << "9������������" << std::endl;
		std::cout << "10����ӡ����Ԫ��" << std::endl;

		int choice;
		while (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "��������" << std::endl;
			std::cout << "����������" << std::endl;
		}
		switch (choice)
		{
		case 1://������λ�ò���Ԫ��
			std::cout << "��������Ҫ�����Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			std::cout << "��������Ҫ�����λ��" << std::endl;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.Insert(data, pos);
			list.Print();
			break;
		case 2://�ڱ�ͷ����Ԫ��
			std::cout << "��������Ҫ�����Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.Push_front(data);
			list.Print();
			break;
		case 3://�ڱ�β����Ԫ��
			std::cout << "��������Ҫ�����Ԫ��ֵ" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.Push_back(data);
			list.Print();
			break;
		case 4://ɾ������λ�õ�Ԫ��
			std::cout << "��������Ҫɾ����Ԫ�ص�λ��" << std::endl;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "��������" << std::endl;
				std::cout << "����������" << std::endl;
			}
			list.Erase(pos);
			list.Print();
			break;
		case 5://ɾ����ͷԪ��
			list.Pop_front();
			list.Print();
			break;
		case 6://ɾ����βԪ��
			list.Pop_back();
			list.Print();
			break;
		case 7://�������
			list.Clear();
			break;
		case 8://ð������
			list.SecondSort();
			list.Print();
			break;
		case 9://����������
			list.GetLength();
			break;
		case 10://��ӡ����Ԫ��
			list.Print();
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}
