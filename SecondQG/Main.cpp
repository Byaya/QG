#include <iostream>
#include "Operation.h"

int main()
{
	std::cout << "QG�ڶ��ܴ��鿼��" << std::endl;
	Operation text;
	std::cout << "��������׺���ʽ" << std::endl;
	char* temp = new char[255];
	std::cin >> temp;
	text.Transform(temp);
	return 0;
}