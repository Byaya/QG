#include "BinaryTree.h"
#include "CalculateTree.h"

//测试二叉树的遍历
void TextTraverse();
//测试二叉树的前缀表达式计算
void TextCalculate();

int main()
{
	int choice = 0;
	std::cout << "请输入你要测试的选项" << std::endl;
	std::cout << "1、二叉树的ADT" << std::endl;
	std::cout << "2、算术树的测试" << std::endl;
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
	std::cout << "前序遍历：" << std::endl;
	tree.PreOrderTraverse(tree.prt_root);
	std::cout << "前序遍历(非递归版)：" << std::endl;
	tree.NewPreOrderTraverse(tree.prt_root);
	std::cout << "中序遍历：" << std::endl;
	tree.InOrderTraverse(tree.prt_root);
	std::cout << "中序遍历(非递归版)：" << std::endl;
	tree.NewInOrderTraverse(tree.prt_root);
	std::cout << "后序遍历：" << std::endl;
	tree.PostOrderTraverse(tree.prt_root);
	std::cout << "后序遍历（非递归版）：" << std::endl;
	tree.NewPostOrderTraverse(tree.prt_root);
	std::cout << "层序遍历" << std::endl;
	tree.LeverOrderTraverse(tree.prt_root);
}

//2 + ( 4 / 3 ) + 6
void TextCalculate()
{
	CalculateTree tree;
	std::cout << "请输入中缀表达式：" << std::endl;
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