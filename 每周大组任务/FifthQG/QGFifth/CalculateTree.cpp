#include "CalculateTree.h"


/*构造函数*/
CalculateTree::CalculateTree()
{
	infix.clear();
	opers.clear();
	prefix.clear();
	lastNodes.clear();
	prt_size = 0;
	prt_level = 0;
	prt_root = nullptr;
}

/*析构函数*/
CalculateTree::~CalculateTree()
{
	

}

void CalculateTree::Transform(const std::vector<std::string>& infix, std::vector<std::string>& prefix, std::map<std::string, int>& opers)
{
	InitOperators(opers);
	prt_size = infix.size();
	std::string end{"0"};
	std::stack<std::string> stk; // 操作符栈
	for (int i = infix.size() - 1; i >= 0; --i) // 从右到左扫描
	{
		if (!IsOperator(infix[i], opers)) // 如果是操作数
		{
			prefix.push_back(end);
			prefix.push_back(end);
			prefix.push_back(infix[i]);
			
		}
		else // 如果是操作符
		{
			if (infix[i] == ")") // 如果是右括号，则直接入栈
			{
				stk.push(infix[i]);
			}
			else if (infix[i] == "(") // 如果是左括号
			{
				// 依次弹出栈中的操作符，直至遇到右括号
				while (!stk.empty())
				{
					if (stk.top() == ")")
					{
						stk.pop();
						break;
					}
					else
					{
						prefix.push_back(stk.top());
						stk.pop();
					}
				}
			}
			else // 如果是其他操作符
			{
				while (!stk.empty() && stk.top() != ")" && opers[stk.top()] > opers[infix[i]]) // 栈顶操作符优先级大于当前操作符优先级
				{
					prefix.push_back(stk.top());
					stk.pop();
				}
				// 将当前操作符入栈
				stk.push(infix[i]);
			}
		}
	}

	// 检测操作符栈是否为空
	while (!stk.empty())
	{
		prefix.push_back(stk.top());
		stk.pop();
	}
	// 将prefix翻转
	reverse(prefix.begin(), prefix.end());
	return;
}

void CalculateTree::GetInfix(std::vector<std::string>& infix)
{
	infix.clear();
	std::string line;
	std::cout << "每两个字符之间必须要有空格隔开，否则表达式不够漂亮，程序不接受" << std::endl;
	getline(std::cin, line);

	std::istringstream sin(line);
	std::string tmp;
	while (sin >> tmp)
	{
		infix.push_back(tmp);

	}
}

void CalculateTree::InitOperators(std::map<std::string, int>& opers)
{
	opers["("] = 100;
	opers[")"] = 900;
	opers["+"] = 100;
	opers["-"] = 100;
	opers["*"] = 200;
	opers["/"] = 200;
	opers["^"] = 200;
	opers["%"] = 200;
}

Yaya<std::string>* CalculateTree::MainComputer()
{
	InitOperators(opers);
	int num = 0;
	float num1 = 0;
	float num2 = 0;
	float result = 0;
	
	while (prt_level != 1)
	{
		lastNodes.clear();
		GetLastAllNode(lastNodes, 1, prt_root);
		num = lastNodes.size();
		while (num != 0)
		{
			if (IsOperator(lastNodes[num - 1]->data, opers)) // 如果是操作符
			{
				num1 = GetFloat(lastNodes[num - 1]->left->data);
				num2 = GetFloat(lastNodes[num - 1]->right->data);
				result = ComputerResult(num1, num2, lastNodes[num - 1]->data[0]);

				std::stringstream ss;
				ss << result;

				lastNodes[num - 1]->data = ss.str();
				delete lastNodes[num - 1]->left;
				delete lastNodes[num - 1]->right;
				lastNodes[num - 1]->left = nullptr;
				lastNodes[num - 1]->right = nullptr;
			}
			--num;
		}
		--prt_level;
	}
	
	return prt_root;
}

float CalculateTree::ComputerResult(float a, float b, char c)
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


bool CalculateTree::IsOperator(const std::string & op, const std::map<std::string, int>& opers)
{
	auto cit = opers.find(op);
	if (cit != opers.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CalculateTree::Display(const std::vector<std::string>& fix)
{
	lastNodes.clear();
	GetLastAllNode(lastNodes, 1, prt_root);
	std::cout << "上层结点：";
	for (auto i = 0; i != lastNodes.size(); ++i)
	{
		std::cout << lastNodes[i]->data << ' ';
	}
	std::cout << "前缀表达式：";
	for (auto i = 0; i != fix.size(); ++i)
	{
		std::cout << fix[i] << ' ';
	}
	std::cout << std::endl;
}

float CalculateTree::GetFloat(std::string str)
{
	float b = 0;
	float a = 0;
	bool flag = true;
	int num = str.size();
	int temp = 1;
	while (num != 0)
	{
		if (str[num - 1] == '.')
		{
			b /= temp;
			--num;
			flag = false;
			temp = 1;
			continue;
		}
		if (flag)
		{
			b += (int)(str[num - 1] - '0') * temp;
			--num;
			temp *= 10;
		}
		else
		{
			a += (int)(str[num - 1] - '0') * temp;
			--num;
			temp *= 10;
		}
	}
	float result = a + b;
	return result;
}


Yaya<std::string>* CalculateTree::CreateTree(const std::vector<std::string>& fix, int& index)
{
	//若空串或者index超出范围，则返回空指针
	if (fix.size() == 0 || index == fix.size() || fix[index] == "0")
		return nullptr;
	Yaya<std::string>* T = new Yaya<std::string>();
	T->data = fix[index++];
	T->left = CreateTree(fix, index);
	T->right = CreateTree(fix, ++index);
	return T;
	
}

void CalculateTree::CreateTree(const std::vector<std::string>& fix)
{
	int index = 0;
	prt_root = CreateTree(fix,index);
	prt_level = GetLeafCount(prt_root);
}

int CalculateTree::GetLeafCount(Yaya<std::string>* node)
{
	if (nullptr == node)
	{
		return 0;
	}
	if (node->left == nullptr&&node->right == nullptr)
	{
		return 1;
	}
	return GetLeafCount(node->left) + GetLeafCount(node->right);

}

void CalculateTree::GetLastAllNode(std::vector<Yaya<std::string>*>& nodes, int depth, Yaya<std::string>* root)
{
	if (depth == prt_level - 1)
	{
		nodes.push_back(root);
		return;
	}
	if (root->left == nullptr)
	{
		return;
	}
	GetLastAllNode(nodes, ++depth, root->left);
	GetLastAllNode(nodes, depth, root->right);
}


void CalculateTree::PreOrderTraverse(Yaya<std::string>* root)
{
	if (root)
	{
		std::cout << root->data << std::endl;
		PreOrderTraverse(root->left);
		PreOrderTraverse(root->right);
	}
}

