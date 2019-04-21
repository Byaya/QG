#ifndef BINARYTREE_H_INCLUDE
#define BINARYTREE_H_INCLUDE

/*********************************************
*	Project：QG第五次大组考核
*	Function：泛型二叉树
*	Author：风雅yaya
*	Date：2019年4月20日00:10:59
*	Location：广州
*********************************************/

#include "yaya.h"
#include <iostream>
#include <cstring>
#include "StackTree.h"
#include "QueueTree.h"
#include <string>

template<typename T>
class BinaryTree
{
public:
	
	BinaryTree();
	~BinaryTree();
	//构造二叉树
	bool CreateBinaryTree(Yaya<T>** root);
	//先序遍历（递归版）
	void PreOrderTraverse(Yaya<T>* root);
	//先序遍历（非递归版）
	void NewPreOrderTraverse(Yaya<T>* root);
	//中序遍历（递归版）
	void InOrderTraverse(Yaya<T>* root);
	//中序遍历（非递归版）
	void NewInOrderTraverse(Yaya<T>* root);
	//后序遍历（递归版）
	void PostOrderTraverse(Yaya<T>* root);
	//后序遍历（非递归版）
	void NewPostOrderTraverse(Yaya<T>* root);
	//层序遍历
	void LeverOrderTraverse(Yaya<T>* root);

public:
	//根结点
	Yaya<T>* prt_root;
	//总结点数量
	int length;
	//深度
	int depth;
	//直径（叶结点到叶结点的最长路径）
	int diameter;
private:
	//结束标志
	T flag;
	//判断是否输入结束标志
	bool isFlag;
};

/*初始化链式二叉树*/
template <typename T>
BinaryTree<T>::BinaryTree()
{
	prt_root = nullptr;
	length = 0;
	depth = 0;
	diameter = 0;
	isFlag = false;
}

/*销毁链式二叉树*/
template <typename T>
BinaryTree<T>::~BinaryTree()
{
}


/*创建链式二叉树*/
template<typename T>
inline bool BinaryTree<T>::CreateBinaryTree(Yaya<T>** root)
{
	//为根节点分配空间
	*root = new Yaya<T>();
	T input;
	if (!isFlag)
	{
		std::cout << "请输入结束标志（如：#、*……）" << std::endl;
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
	(*root)->left = new Yaya<T>();
	(*root)->right = new Yaya<T>();

	if (!CreateBinaryTree(&((*root)->left)))
	{
		delete (*root)->left;
		(*root)->left = nullptr;
	}
	if (!CreateBinaryTree(&((*root)->right)))
	{
		delete (*root)->right;
		(*root)->right = nullptr;
	}
	return true;
}

/*先序遍历递归版*/
template<typename T>
inline void BinaryTree<T>::PreOrderTraverse(Yaya<T>* root)
{
	//先访问根结点，然后左子树，最后右子树
	if (root)
	{
		std::cout << root->data << std::endl;
		PreOrderTraverse(root->left);
		PreOrderTraverse(root->right);
	}
}

/*先序遍历（非递归版）*/
template<typename T>
inline void BinaryTree<T>::NewPreOrderTraverse(Yaya<T>* root)
{
	//创建链栈
	StackTree<T> stack;
	//当前树结点
	Yaya<T>* currNode = new Yaya<T>();
	//临时树结点
	Yaya<T>* temp = currNode;
	while (root || !stack.IsStackEmpty())
	{
		if (root)
		{
			stack.PushStack(root);
			std::cout << root->data << std::endl;
			root = root->left;
		}
		else
		{
			stack.PopStack(&currNode);
			root = currNode->right;
		}
	}
	delete temp;
}

/*中序遍历递归版*/
template<typename T>
inline void BinaryTree<T>::InOrderTraverse(Yaya<T>* root)
{
	if (root)
	{
		InOrderTraverse(root->left);
		std::cout << root->data << std::endl;
		InOrderTraverse(root->right);
	}
}

/*中序遍历（非递归版）*/
template<typename T>
inline void BinaryTree<T>::NewInOrderTraverse(Yaya<T>* root)
{
	StackTree<T> stack;
	//当前树结点
	Yaya<T>* currNode = new Yaya<T>();
	//临时结点
	Yaya<T>* temp = currNode;
	while (root || !stack.IsStackEmpty())
	{
		if (root)
		{
			stack.PushStack(root);
			root = root->left;
		}
		else
		{
			stack.PopStack(&currNode);
			std::cout << currNode->data << std::endl;
			root = currNode->right;
		}
	}
	delete temp;
}

/*后序遍历递归版*/
template<typename T>
inline void BinaryTree<T>::PostOrderTraverse(Yaya<T>* root)
{
	if (root)
	{
		PostOrderTraverse(root->left);
		PostOrderTraverse(root->right);
		std::cout << root->data << std::endl;
	}
}

/*后序遍历（非递归版）*/
template<typename T>
inline void BinaryTree<T>::NewPostOrderTraverse(Yaya<T>* root)
{
	StackTree<T> stack;
	StackTree<T> tempStack;
	Yaya<T>* currNode = new Yaya<T>();
	Yaya<T>* temp = currNode;
	while (root || !tempStack.IsStackEmpty())
	{
		if (root)
		{
			tempStack.PushStack(root);
			stack.PushStack(root);
			root = root->right;
		}
		else
		{
			tempStack.PopStack(&currNode);
			root = currNode->left;
		}
	}
	while (!stack.IsStackEmpty())
	{
		stack.PopStack(&currNode);
		std::cout << currNode->data << std::endl;
	}
	delete temp;
}

/*层序遍历*/
template<typename T>
inline void BinaryTree<T>::LeverOrderTraverse(Yaya<T>* root)
{
	QueueTree<T> queue;
	Yaya<T>* currNode = new Yaya<T>();
	Yaya<T>* temp = currNode;
	queue.EnQueue(root);
	while (!queue.IsQueueEmpty())
	{
		queue.DeQueue(&currNode);
		std::cout << currNode->data << std::endl;
		if (currNode->left)
		{
			queue.EnQueue(currNode->left);
		}
		if (currNode->right)
		{
			queue.EnQueue(currNode->right);
		}
	}
	delete temp;
}


#endif // !BINARYTREE_H_INCLUDE
