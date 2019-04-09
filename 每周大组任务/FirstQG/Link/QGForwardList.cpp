#include "QGForwardList.h"



QGForwardList::QGForwardList()
{
	length = 0;
	//初始化头指针和尾指针
	head = new Node();
	head->data = 0;
	tail = new Node();
	tail->data = 0;
	tail->next = nullptr;
	head->next = tail;

	//是否创建新结点
	char choice = 's';
	ElemType data;
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
		while (!(std::cin >> choice))
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

void QGForwardList::Print()
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


QGForwardList::~QGForwardList()
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

int & QGForwardList::front()
{
	// TODO: 在此处插入 return 语句
	std::cout << head->next->data << std::endl;
	return head->next->data;
}

int & QGForwardList::back()
{
	Node* node = head;
	while (node->next!=tail)
	{
		node = node->next;
	}
	std::cout << node->data << std::endl;
	return node->data;
}

bool QGForwardList::push_front(ElemType & e)
{
	insert(1, e);
	return false;
}

bool QGForwardList::pop_front()
{
	erase(1);
	return true;
}

bool QGForwardList::push_back(ElemType & e)
{
	insert(length + 1,e);
	return false;
}

bool QGForwardList::pop_back()
{
	erase(length);
	return false;
}

bool QGForwardList::insert(unsigned int index, ElemType & e)
{
	if (index<1 || index>(unsigned int)length + 1)
	{
		std::cout << "下标越界" << std::endl;
		return false;
	}
	Node* node = new Node();
	node->data = e;
	node->next = nullptr;
	Node* last = head;
	Node* next = tail;
	for (unsigned int i = 0; i < index - 1; i++)
	{
		last = last->next;
	}
	next = last->next;
	last->next = node;
	node->next = next;
	++length;
	return true;
}

bool QGForwardList::erase(unsigned int index)
{
	if (index<1 || index>(unsigned int)length)
	{
		std::cout << "下标越界" << std::endl;
		return false;
	}
	Node* node = head;
	Node* last = head;
	Node* next = tail;
	for (unsigned int i = 0; i < index - 1; i++)
	{
		last = last->next;
	}
	node = last->next;
	next = node->next;
	last->next = next;
	delete node;
	--length;
	return true;
}

bool QGForwardList::clear()
{
	int count = length;
	for (int i = 1; i <= count; i++)
	{
		erase(1);
	}
	return true;
}

bool QGForwardList::contain(ElemType & e)
{
	Node* node = head->next;
	while (node != tail)
	{
		if (node->data == e)
		{
			return true;
		}
		node = node->next;
	}
	return false;
}

unsigned int QGForwardList::size()
{
	std::cout << length << std::endl;
	return length;
}

bool QGForwardList::traverse(void(*visit)(ElemType &e))
{
	Node* node = head->next;
	while (node != tail)
	{
		visit(node->data);
		node = node->next;
	}
	return false;
}

bool QGForwardList::reverse()
{
	Node* node = head->next;
	Node* last = head;
	Node* next = tail;
	while (node!=tail)
	{
		next = node->next;
		node->next = last;
		last = node;
		node = next;
	}
	node->next = last;
	Node* temp = head;
	head = tail;
	tail = temp;
	return true;
}

bool QGForwardList::isLoop()
{
	Node* fast = head;
	Node* slow = head;
	while (slow!=nullptr&&fast->next!=nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)
		{
			return false;
		}
	}
	return true;
}

bool QGForwardList::reverseEven()
{
	Node* node = head->next;
	Node* last = head;
	Node* next = tail;
	while (node != tail&&node->next!=tail)
	{
		next = node->next;
		last->next = next;
		node->next = next->next;
		next->next = node;
		last = node;
		node = last->next;
	}
	//node->next = last;
	return true;
}

int & QGForwardList::middleElem()
{
	if (head == tail)
	{
		std::cout << head->data << std::endl;
		return head->data;
	}
	if (length == 1)
	{
		std::cout << head->next->data << std::endl;
		return head->next->data;
	}
	Node* slow, *fast;
	if (length % 2 == 0)
	{
		slow = fast = head;
	}
	else
	{
		slow = fast = head->next;
	}
	while (slow != tail&&fast->next!=tail)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	std::cout << slow->data << std::endl;
	return slow->data;
}
