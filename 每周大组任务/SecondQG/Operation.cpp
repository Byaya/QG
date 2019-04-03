#include "Operation.h"

Operation::Operation()
{
	
}

Operation::~Operation()
{
	
}

void Operation::Transform(char * middle)
{
	int i = 0;
	bool numFlag = false;
	bool kuFlag = false;
	char temp = '\0';
	float num = 0;
	while (middle[i]!='\0')
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
			numFlag = true;
			continue;
		}
		if (middle[i] > '0'&&middle[i] <= '9')
		{
			num = 0;
			while (middle[i]>='0'&&middle[i]<='9')
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
			if (numFlag)
			{
				num = -num;
				numFlag = false;
			}
			stackNum.PushStakc(&num);
			continue;
		}
		//左括号
		if (middle[i] == '(')
		{
			stackChar.PushStakc(middle + i);
			++i;
			numFlag = false;
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
					num = Computer(-stackNum.PopStack(), -stackNum.PopStack(), temp);
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
		while (!stackChar.Empty()&&Prio(stackChar.GetTopElem())>=Prio(middle[i]))
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
}

/*返回元素优先级*/
int Operation::Prio(char c)
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

float Operation::Computer(float a, float b, char c)
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
		result = PowerCom(a,(int)b);
		break;
	case '%':
		result = (float)((int)a % (int)b);
		break;
	default:
		break;
	}
	return result;
}

float Operation::PowerCom(float a, int b)
{
	float result = a;
	for (int i = 1; i < b; i++)
	{
		result *= a;
	}
	return result;
}

