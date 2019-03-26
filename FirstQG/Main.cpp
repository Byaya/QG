#include "List.h"
#include "QGForwardList.h"
#include "DoubleLInk.h"

void func(int& i);

void TextList();
void TextQGForwardList();
void TextDoubleList();


int main()
{
	std::cout << "请输入你要测试的链表类型" << std::endl;
	std::cout << "1、单链表" << std::endl;
	std::cout << "2、双向链表" << std::endl;
	std::cout << "3、模板类双向链表" << std::endl;
	int choice;
	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << "不是数字" << std::endl;
		std::cout << "请重新输入" << std::endl;
	}
	switch (choice)
	{
	case 1://单链表
		TextQGForwardList();
		break;
	case 2://双向链表
		TextList();
		break;
	case 3://模板类双向链表
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
		std::cout << "链表创建完毕！请选择你要进行的操作" << std::endl;
		std::cout << "1、打印所有的数据" << std::endl;
		std::cout << "2、返回链表中第一个元素的引用e" << std::endl;
		std::cout << "3、返回链表中最后一个元素的引用" << std::endl;
		std::cout << "4、在链表第一个元素前添加元素e" << std::endl;
		std::cout << "5、删除链表第一个元素" << std::endl;
		std::cout << "6、在链表最后一个元素后添加元素e" << std::endl;
		std::cout << "7、删除链表最后一个元素" << std::endl;
		std::cout << "8、删除任意位置元素" << std::endl;
		std::cout << "9、清空链表" << std::endl;
		std::cout << "10、查找元素是否存在" << std::endl;
		std::cout << "11、返回链表中元素的数量" << std::endl;
		std::cout << "12、遍历链表, 对每个元素调用visit指向的函数" << std::endl;
		int choice;
		while (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "不是数字" << std::endl;
			std::cout << "请重新输入" << std::endl;
		}
		switch (choice)
		{
		case 1://打印所有的数据
			list.Print();
			break;
		case 2://返回链表中第一个元素的引用
			list.front();
			break;
		case 3://返回链表中最后一个元素的引用
			list.back();
			break;
		case 4://在链表第一个元素前添加元素
			std::cout << "请输入你要输入的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.push_front(data);
			list.Print();
			break;
		case 5://删除链表第一个元素
			list.pop_front();
			list.Print();
			break;
		case 6://在链表最后一个元素后添加元素e
			std::cout << "请输入你要输入的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.push_back(data);
			list.Print();
			break;
		case 7://删除链表最后一个元素
			list.pop_back();
			list.Print();
			break;
		case 8://删除任意位置元素
			std::cout << "请输入你要删除的元素位置" << std::endl;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.erase(pos);
			list.Print();
			break;
		case 9://清空链表
			list.clear();
			break;
		case 10://查找元素是否存在
			std::cout << "请输入你要查找的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			if (list.contain(data))
			{
				std::cout << "该元素存在" << std::endl;
			}
			else
			{
				std::cout << "该元素不存在" << std::endl;
			}
			break;
		case 11://返回链表中元素的数量
			list.size();
			break;
		case 12://遍历链表, 对每个元素调用visit指向的函数
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
		std::cout << "链表创建完毕！请选择你要进行的操作" << std::endl;
		std::cout << "1、返回链表中第一个元素的引用" << std::endl;
		std::cout << "2、在链表第一个元素前添加元素e" << std::endl;
		std::cout << "3、删除链表第一个元素" << std::endl;
		std::cout << "4、在链表最后一个元素后添加元素e" << std::endl;
		std::cout << "5、删除链表最后一个元素" << std::endl;
		std::cout << "6、在链表的第index + 1个元素前插入元素e" << std::endl;
		std::cout << "7、删除任意位置元素" << std::endl;
		std::cout << "8、清空链表" << std::endl;
		std::cout << "9、查找元素是否存在" << std::endl;
		std::cout << "10、遍历链表, 对每个元素调用visit指向的函数" << std::endl;
		std::cout << "11、反转链表，1234反转后变成4321" << std::endl;
		std::cout << "12、链表判环" << std::endl;
		std::cout << "13、偶节点反转，1234反转后变成2143" << std::endl;
		std::cout << "14、返回中间节点" << std::endl;
		std::cout << "15、打印链表" << std::endl;
		int choice;
		while (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "不是数字" << std::endl;
			std::cout << "请重新输入" << std::endl;
		}
		switch (choice)
		{
		case 1:
			list.front();
			break;
		case 2:
			std::cout << "请输入你要输入的元素值" << std::endl;
			int data;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.push_front(data);
			list.Print();
			break;
		case 3://删除链表的第一个元素
			list.pop_front();
			list.Print();
			break;
		case 4://在链表最后一个元素后添加元素
			std::cout << "请输入你要输入的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.push_back(data);
			list.Print();
			break;
		case 5://删除链表最后一个元素
			list.pop_back();
			list.Print();
			break;
		case 6://在链表的第index + 1个元素前插入元素e
			std::cout << "请输入你要输入的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			std::cout << "请输入你要插入的位置" << std::endl;
			int pos;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.insert(pos, data);
			list.Print();
			break;
		case 7://删除任意位置元素
			std::cout << "请输入你要删除的元素的位置" << std::endl;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.erase(pos);
			list.Print();
			break;
		case 8://清空链表
			list.clear();
			break;
		case 9://查找元素是否存在
			std::cout << "请输入你要查找的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			if (list.contain(data))
			{
				std::cout << "该元素存在" << std::endl;
			}
			else
			{
				std::cout << "该元素不存在" << std::endl;
			}
			break;
		case 10://遍历链表, 对每个元素调用visit指向的函数
			list.traverse(func);
			list.Print();
			break;
		case 11://反转链表，1234反转后变成4321
			list.reverse();
			list.Print();
			break;
		case 12://链表判环
			if (list.isLoop())
			{
				std::cout << "有环" << std::endl;
			}
			else
			{
				std::cout << "无环" << std::endl;
			}
			break;
		case 13://偶节点反转，1234反转后变成2143
			list.reverseEven();
			list.Print();
			break;
		case 14://返回中间节点
			list.middleElem();
			break;
		case 15://打印链表
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
		std::cout << "链表创建完毕！请选择你要进行的操作" << std::endl;
		std::cout << "1、在任意位置插入元素" << std::endl;
		std::cout << "2、在表头插入元素" << std::endl;
		std::cout << "3、在表尾插入元素" << std::endl;
		std::cout << "4、删除任意位置的元素" << std::endl;
		std::cout << "5、删除表头元素" << std::endl;
		std::cout << "6、删除表尾元素" << std::endl;
		std::cout << "7、清空链表" << std::endl;
		std::cout << "8、冒泡排序" << std::endl;
		std::cout << "9、返回链表长度" << std::endl;
		std::cout << "10、打印所有元素" << std::endl;

		int choice;
		while (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "不是数字" << std::endl;
			std::cout << "请重新输入" << std::endl;
		}
		switch (choice)
		{
		case 1://在任意位置插入元素
			std::cout << "请输入你要输入的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			std::cout << "请输入你要插入的位置" << std::endl;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.Insert(data, pos);
			list.Print();
			break;
		case 2://在表头插入元素
			std::cout << "请输入你要输入的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.Push_front(data);
			list.Print();
			break;
		case 3://在表尾插入元素
			std::cout << "请输入你要输入的元素值" << std::endl;
			while (!(std::cin >> data))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.Push_back(data);
			list.Print();
			break;
		case 4://删除任意位置的元素
			std::cout << "请输入你要删除的元素的位置" << std::endl;
			while (!(std::cin >> pos))
			{
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cout << "不是数字" << std::endl;
				std::cout << "请重新输入" << std::endl;
			}
			list.Erase(pos);
			list.Print();
			break;
		case 5://删除表头元素
			list.Pop_front();
			list.Print();
			break;
		case 6://删除表尾元素
			list.Pop_back();
			list.Print();
			break;
		case 7://清空链表
			list.Clear();
			break;
		case 8://冒泡排序
			list.SecondSort();
			list.Print();
			break;
		case 9://返回链表长度
			list.GetLength();
			break;
		case 10://打印所有元素
			list.Print();
			break;
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}
