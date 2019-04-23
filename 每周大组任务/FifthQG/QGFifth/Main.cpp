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
	std::cout << "2���������Ĳ���" << std::endl;
	std::cin >> choice;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
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

//2 + ( 4 / 3 ) + 6
void TextCalculate()
{
	CalculateTree tree;
	std::cout << "��������׺���ʽ��" << std::endl;
	tree.GetInfix(tree.infix);

	std::vector<std::string> temp{};
	temp.clear();
	tree.Transform(tree.infix, tree.prefix, tree.opers);
	for (size_t i = 0; i < tree.prefix.size(); i++)
	{
		temp.push_back (tree.prefix[i]);
	}
	
	tree.CreateTree(temp);
	tree.MainComputer();
	tree.PreOrderTraverse(tree.prt_root);
}