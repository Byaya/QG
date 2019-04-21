#include "CalculateTree.h"


/*构造函数*/
CalculateTree::CalculateTree()
{
	prt_size = 0;
	prt_root = nullptr;
}

/*析构函数*/
CalculateTree::~CalculateTree()
{

}

void CalculateTree::AddNode(const char & key, int direction)
{
	AddNode(key, direction, prt_root);
	++prt_size;
}

///*在指定位置插入结点*/
//void CalculateTree::InsertNode(char elem)
//{
//	//创建新结点
//	Yaya<char>* node = new Yaya<char>();
//	node->data = elem;
//	if (prt_size == 0)
//	{
//		prt_size = 1;
//		prt_root = node;
//		return;
//	}
//	Yaya<char>* tempNode = prt_root;
//	Yaya<char>* preNode = prt_root;
//	//创建链栈
//	StackTree<char> stack;
//	//当前树结点
//	Yaya<char>* currNode = new Yaya<char>();
//	//临时树结点
//	Yaya<char>* temp = currNode;
//	while (tempNode || !stack.IsStackEmpty())
//	{
//		if (tempNode)
//		{
//			
//			stack.PushStack(tempNode);
//			if (tempNode->left)
//			{
//				preNode = tempNode;
//			}
//			tempNode = tempNode->left;
//			
//		}
//		else
//		{
//			stack.PopStack(&currNode);
//			
//			tempNode = currNode->right;
//			
//		}
//	}
//	if ((preNode)->left && !(preNode)->right)
//	{
//		(preNode)->right = node;
//	}
//	else if(!(preNode)->left)
//	{
//		(preNode)->left = node;
//	}
//	else
//	{
//		tempNode = prt_root;
//		Yaya<char>* tempNode1 = prt_root;
//		int left = 0;
//		int right = 0;
//		int max = 1;
//		int sum = 1;
//		while (tempNode->left)
//		{
//			++left;
//			tempNode = (tempNode)->left;
//		}
//		while (tempNode1->right)
//		{
//			++right;
//			tempNode1 = (tempNode1)->right;
//		}
//		for (int i = 0; i < left; i++)
//		{
//			max *= 2;
//			sum += max;
//		}
//		if (sum - prt_size <= max / 2 && sum != prt_size)
//		{
//			(preNode) = tempNode1;
//			(preNode)->left = node;
//		}
//		else
//		{
//			(preNode) = tempNode;
//			(preNode)->left = node;
//		}
//	}
//	++prt_size;
//	delete temp;
//}

/*根据字符串创建二叉树*/
Yaya<char>* CalculateTree::CreteBinary(Yaya<char>** root)
{
	//为根节点分配空间
	*root = new Yaya<char>();
	char input;
	if (!isFlag)
	{
		std::cout << "请输入结束标志" << std::endl;
		std::cin >> flag;
		isFlag = true;
	}
	std::cout << "请输入结点数据" << std::endl;
	std::cin >> input;
	if (input == flag)
	{
		return false;
	}
	//创建当前结点
	(*root)->data = input;
	//递归创建左子树和右子树
	(*root)->left = new Yaya<char>();
	(*root)->right = new Yaya<char>();

	if (!CreteBinary(&((*root)->left)))
	{
		delete (*root)->left;
		(*root)->left = nullptr;
	}
	if (!CreteBinary(&((*root)->right)))
	{
		delete (*root)->right;
		(*root)->right = nullptr;
	}
}

/*先序遍历*/
void CalculateTree::PreTraverse(Yaya<char>* root)
{
	if (root)
	{
		PreTraverse(root->left);
		std::cout << root->data << std::endl;
		PreTraverse(root->right);
	}
}

char* CalculateTree::Transform(char * middle)
{
	char front[200] = "";
	int i = 0;
	bool kuFlag = false;
	char temp = '\0';
	float num = 0;
	while (middle[i] != '\0')
	{
		//运算数
		if (middle[i] == '-')
		{
			temp = '+';
			while (!stackChar.Empty() && Prio(stackChar.GetTopElem()) >= Prio(temp))
			{
				float temp = Computer(stackNum.PopStack(), stackNum.PopStack(),
					stackChar.PopStack());
				stackNum.PushStakc(&temp);
			}
			stackChar.PushStakc(&temp);
			++i;
			continue;
		}
		if (middle[i] > '0'&&middle[i] <= '9')
		{
			num = 0;
			while (middle[i] >= '0'&&middle[i] <= '9')
			{
				num = num * 10 + middle[i++] - '0';
			}
			//处理小数部分
			if (middle[i] == '.')
			{
				++i;
				float temp = 0;
				int flag = 0;
				while (middle[i] >= '0'&&middle[i] <= '9')
				{
					temp = temp * 10 + middle[i++] - '0';
					++flag;
				}
				temp /= pow(10, flag);
				num += temp;
			}
			stackNum.PushStakc(&num);
			continue;
		}
		//左括号
		if (middle[i] == '(')
		{
			stackChar.PushStakc(middle + i);
			++i;
			kuFlag = true;
			continue;
		}
		//右括号
		if (middle[i] == ')')
		{
			if (kuFlag)
			{
				temp = stackChar.PopStack();
				while (temp != '(')
				{
					num = Computer(stackNum.PopStack(), stackNum.PopStack(), temp);
					stackNum.PushStakc(&num);
					temp = stackChar.PopStack();
				}
				kuFlag = false;
			}
			else
			{
				temp = stackChar.PopStack();
				while (temp != '(')
				{
					num = Computer(stackNum.PopStack(), stackNum.PopStack(), temp);
					stackNum.PushStakc(&num);
					temp = stackChar.PopStack();
				}
			}
			++i;
			continue;
		}
		//普通运算符
		while (!stackChar.Empty() && Prio(stackChar.GetTopElem()) >= Prio(middle[i]))
		{
			float temp = Computer(stackNum.PopStack(), stackNum.PopStack(),
				stackChar.PopStack());
			stackNum.PushStakc(&temp);
		}
		stackChar.PushStakc(middle + i);
		++i;
	}
	while (!stackChar.Empty())
	{
		float temp = 0.0;
		temp = Computer(stackNum.PopStack(), stackNum.PopStack(), stackChar.PopStack());
		stackNum.PushStakc(&temp);
	}
	std::cout << stackNum.GetTopElem() << std::endl;
	return front;
}

float CalculateTree::Computer(float a, float b, char c)
{
	float result = 0;
	switch (c)
	{
	case '+':
		result = a + b;
		break;
	case '-':
		result = a - b;
		break;
	case '/':
		result = a / b;
		break;
	case '*':
		result = a * b;
		break;
	case '^':
		result = PowerCom(a, (int)b);
		break;
	case '%':
		result = (float)((int)a % (int)b);
		break;
	default:
		break;
	}
	return result;
}

float CalculateTree::PowerCom(float a, int b)
{
	float result = a;
	for (int i = 1; i < b; i++)
	{
		result *= a;
	}
	return result;
}

int CalculateTree::Prio(char c)
{
	int result = 0;
	switch (c)
	{
	case '(':
		result = 1;
		break;
	case '+':
	case '-':
		result = 2;
		break;
	case '/':
	case '*':
	case '^':
	case '%':
		result = 3;
		break;
	default:
		break;
	}
	return result;
}

Yaya<char>* CalculateTree::AddNode(const char & key, int direction, Yaya<char>*& root)
{
	if (!root)
	{
		root = new Yaya<char>();
		root->data = key;
	}
	if (direction == 0)//左孩子
	{
		if (root->left == NULL) {//找到对应的叶节点插入
			root->left = new Yaya<char>;
			root->left->data = key;
		}
		else {
			root->left = AddNode(key, direction, root->left);
		}
	}
	else//右孩子
	{
		if (root->right == NULL) {//找到相应的叶节点插入
			root->right = new Yaya<char>;
			root->right->data = key;
		}
		else {
			root->right = AddNode(key, direction, root->right);
		}
	}
	return root;
}
