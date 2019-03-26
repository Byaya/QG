#include "List.h"

static int nums[5] = { 1,32,23,12,451 };

/*初始化链表*/
List::List()
{
	length = 0;
	//初始化头指针和尾指针
	head = new Node();
	head->data = 0;
	head->prior = nullptr;
	tail = new Node();
	tail->data = 0;
	tail->next = nullptr;
	tail->prior = head;
	head->next = tail;

	//是否创建新结点
	char choice = 's';
	ElemType data = 0;
	int count = length;
	while (1)
	{
		count = length + 1;
		std::cout << "请输入数据域" << std::endl;
		while (!(std::cin >> data))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "不是数字" << std::endl;
			std::cout << "请重新输入数据域" << std::endl;
		}
		insert(count, data);
		std::cout << "是否继续创建新结点（y/n）" << std::endl;
		while (!(std::cin >> data))
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "请输入y/n" << std::endl;
		}
		if (choice == 'n')
		{
			break;
		}
	}
}


List::~List()
{
	if (head != tail)
	{
		Node* node = head;
		head = head->next;
		delete node;
	}
	delete tail;
	tail = nullptr;
	head = nullptr;
}

void List::Print()
{
	if (head->next == tail)
	{
		std::cout << "该链表为空！" << std::endl;
	}
	Node* node = head->next;
	while (1)
	{
		if (node != tail)
		{
			std::cout << node->data << std::endl;
			node = node->next;
			continue;
		}
		break;
	}
}

int & List::front()
{
	// TODO: 在此处插入 return 语句
	std::cout << head->next->data << std::endl;
	return head->next->data;
}

int & List::back()
{
	// TODO: 在此处插入 return 语句
	std::cout << tail->prior->data << std::endl;
	return tail->prior->data;
}

bool List::push_front(ElemType & e)
{
	insert(1, e);
	return false;
}

bool List::pop_front()
{
	erase(1);
	return true;
}

bool List::push_back(ElemType & e)
{
	insert(length + 1, e);
	return true;
}

bool List::pop_back()
{
	erase(length);
	return true;
}

bool List::insert(unsigned int index, ElemType & e)
{
	unsigned int temp = length;
	if (index<1 || index>temp +1)
	{
		std::cout << "下标越界" << std::endl;
		return false;
	}
	Node* node = new Node();
	node->data = e;
	node->next = nullptr;
	node->prior = nullptr;
	Node* last = head;
	Node* next = tail;
	for (unsigned int i = 0; i < index - 1; i++)
	{
		last = last->next;
	}
	next = last->next;
	last->next = node;
	next->prior = node;
	node->next = next;
	node->prior = last;
	length++;
	return true;
}

bool List::erase(unsigned int index)
{

	if (index<1 || index>(unsigned int)length)
	{
		std::cout << "下标越界" << std::endl;
		return false;
	}
	Node* node = head;
	Node* last = head;
	Node* next = tail;
	for (unsigned int i = 0; i < index; i++)
	{
		node = node->next;
	}
	next = node->next;
	last = node->prior;
	next->prior = last;
	last->next = next;
	delete node;
	--length;
	return true;
}

bool List::clear()
{
	int count = length;
	for (int i = 1; i <= count; i++)
	{
		erase(1);
	}
	return true;
}

bool List::contain(ElemType & e)
{
	Node* node = head->next;
	while (node!=tail)
	{
		if (node->data == e)
		{
			return true;
		}
		node = node->next;
	}
	return false;
}

unsigned int List::size()
{
	return length;
}

bool List::traverse(void(*visit)(ElemType &e))
{
	Node* node = head->next;
	while (node != tail)
	{
		visit(node->data);
		node = node->next;
	}
	return false;
}
