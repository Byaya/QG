#include "CalculateTree.h"


/*���캯��*/
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

/*��������*/
CalculateTree::~CalculateTree()
{
	

}

void CalculateTree::Transform(const std::vector<std::string>& infix, std::vector<std::string>& prefix, std::map<std::string, int>& opers)
{
	InitOperators(opers);
	prt_size = infix.size();
	std::string end{"0"};
	std::stack<std::string> stk; // ������ջ
	for (int i = infix.size() - 1; i >= 0; --i) // ���ҵ���ɨ��
	{
		if (!IsOperator(infix[i], opers)) // ����ǲ�����
		{
			prefix.push_back(end);
			prefix.push_back(end);
			prefix.push_back(infix[i]);
			
		}
		else // ����ǲ�����
		{
			if (infix[i] == ")") // ����������ţ���ֱ����ջ
			{
				stk.push(infix[i]);
			}
			else if (infix[i] == "(") // �����������
			{
				// ���ε���ջ�еĲ�������ֱ������������
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
			else // ���������������
			{
				while (!stk.empty() && stk.top() != ")" && opers[stk.top()] > opers[infix[i]]) // ջ�����������ȼ����ڵ�ǰ���������ȼ�
				{
					prefix.push_back(stk.top());
					stk.pop();
				}
				// ����ǰ��������ջ
				stk.push(infix[i]);
			}
		}
	}

	// ��������ջ�Ƿ�Ϊ��
	while (!stk.empty())
	{
		prefix.push_back(stk.top());
		stk.pop();
	}
	// ��prefix��ת
	reverse(prefix.begin(), prefix.end());
	return;
}

void CalculateTree::GetInfix(std::vector<std::string>& infix)
{
	infix.clear();
	std::string line;
	std::cout << "ÿ�����ַ�֮�����Ҫ�пո������������ʽ����Ư�������򲻽���" << std::endl;
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
			if (IsOperator(lastNodes[num - 1]->data, opers)) // ����ǲ�����
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
	std::cout << "�ϲ��㣺";
	for (auto i = 0; i != lastNodes.size(); ++i)
	{
		std::cout << lastNodes[i]->data << ' ';
	}
	std::cout << "ǰ׺���ʽ��";
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
	//���մ�����index������Χ���򷵻ؿ�ָ��
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

