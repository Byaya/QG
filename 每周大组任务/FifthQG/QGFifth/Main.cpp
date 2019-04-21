#include "BinaryTree.h"
#include "CalculateTree.h"

//���Զ������ı���
void TextTraverse();
//���Զ�������ǰ׺���ʽ����
void TextCalculate();

int main()
{
	int choice = 0;
	std::cout << "��������Ҫ���Ե�ѡ��" << std::endl;
	std::cout << "1����������ADT" << std::endl;
	std::cout << "1���������Ĳ���" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		TextTraverse();
		break;
	case 2:
		TextCalculate();
		break;
	default:
		break;
	}
	return 0;
}

void TextTraverse()
{
	BinaryTree<std::string> tree;
	tree.CreateBinaryTree(&(tree.prt_root));
	std::cout << "ǰ�������" << std::endl;
	tree.PreOrderTraverse(tree.prt_root);
	std::cout << "ǰ�����(�ǵݹ��)��" << std::endl;
	tree.NewPreOrderTraverse(tree.prt_root);
	std::cout << "���������" << std::endl;
	tree.InOrderTraverse(tree.prt_root);
	std::cout << "�������(�ǵݹ��)��" << std::endl;
	tree.NewInOrderTraverse(tree.prt_root);
	std::cout << "���������" << std::endl;
	tree.PostOrderTraverse(tree.prt_root);
	std::cout << "����������ǵݹ�棩��" << std::endl;
	tree.NewPostOrderTraverse(tree.prt_root);
	std::cout << "�������" << std::endl;
	tree.LeverOrderTraverse(tree.prt_root);
}

void TextCalculate()
{
	CalculateTree tree;
	std::cout << "��������׺���ʽ" << std::endl;
	char* temp = new char[255];
	std::cin >> temp;
	tree.Transform(temp);
}