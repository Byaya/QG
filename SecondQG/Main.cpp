#include <iostream>
#include "Operation.h"

int main()
{
	std::cout << "QG第二周大组考核" << std::endl;
	Operation text;
	std::cout << "请输入中缀表达式" << std::endl;
	char* temp = new char[255];
	std::cin >> temp;
	text.Transform(temp);
	return 0;
}