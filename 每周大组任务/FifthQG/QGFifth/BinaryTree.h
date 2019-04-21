#ifndef BINARYTREE_H_INCLUDE
#define BINARYTREE_H_INCLUDE

/*********************************************
*	Project��QG����δ��鿼��
*	Function�����Ͷ�����
*	Author������yaya
*	Date��2019��4��20��00:10:59
*	Location������
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
	//���������
	bool CreateBinaryTree(Yaya<T>** root);
	//����������ݹ�棩
	void PreOrderTraverse(Yaya<T>* root);
	//����������ǵݹ�棩
	void NewPreOrderTraverse(Yaya<T>* root);
	//����������ݹ�棩
	void InOrderTraverse(Yaya<T>* root);
	//����������ǵݹ�棩
	void NewInOrderTraverse(Yaya<T>* root);
	//����������ݹ�棩
	void PostOrderTraverse(Yaya<T>* root);
	//����������ǵݹ�棩
	void NewPostOrderTraverse(Yaya<T>* root);
	//�������
	void LeverOrderTraverse(Yaya<T>* root);

public:
	//�����
	Yaya<T>* prt_root;
	//�ܽ������
	int length;
	//���
	int depth;
	//ֱ����Ҷ��㵽Ҷ�����·����
	int diameter;
private:
	//������־
	T flag;
	//�ж��Ƿ����������־
	bool isFlag;
};

/*��ʼ����ʽ������*/
template <typename T>
BinaryTree<T>::BinaryTree()
{
	prt_root = nullptr;
	length = 0;
	depth = 0;
	diameter = 0;
	isFlag = false;
}

/*������ʽ������*/
template <typename T>
BinaryTree<T>::~BinaryTree()
{
}


/*������ʽ������*/
template<typename T>
inline bool BinaryTree<T>::CreateBinaryTree(Yaya<T>** root)
{
	//Ϊ���ڵ����ռ�
	*root = new Yaya<T>();
	T input;
	if (!isFlag)
	{
		std::cout << "�����������־���磺#��*������" << std::endl;
		std::cin >> flag;
		isFlag = true;
	}
	std::cout << "������������" << std::endl;
	std::cin >> input;
	if (input == flag)
	{
		return false;
	}
	//������ǰ���
	(*root)->data = input;
	//�ݹ鴴����������������
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

/*��������ݹ��*/
template<typename T>
inline void BinaryTree<T>::PreOrderTraverse(Yaya<T>* root)
{
	//�ȷ��ʸ���㣬Ȼ�������������������
	if (root)
	{
		std::cout << root->data << std::endl;
		PreOrderTraverse(root->left);
		PreOrderTraverse(root->right);
	}
}

/*����������ǵݹ�棩*/
template<typename T>
inline void BinaryTree<T>::NewPreOrderTraverse(Yaya<T>* root)
{
	//������ջ
	StackTree<T> stack;
	//��ǰ�����
	Yaya<T>* currNode = new Yaya<T>();
	//��ʱ�����
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

/*��������ݹ��*/
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

/*����������ǵݹ�棩*/
template<typename T>
inline void BinaryTree<T>::NewInOrderTraverse(Yaya<T>* root)
{
	StackTree<T> stack;
	//��ǰ�����
	Yaya<T>* currNode = new Yaya<T>();
	//��ʱ���
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

/*��������ݹ��*/
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

/*����������ǵݹ�棩*/
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

/*�������*/
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
