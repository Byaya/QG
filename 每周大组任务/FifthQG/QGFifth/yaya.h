#ifndef YAYA_H_INCLUDE
#define YAYA_H_INCLUDE

/*********************************************
*	Project：QG第五次大组考核
*	Function：二叉树树结点
*	Author：风雅yaya
*	Date：2019年4月20日00:10:59
*	Location：广州
*********************************************/

template <typename T>
class Yaya
{
public:
	Yaya();
	~Yaya();

public:
	//数据域
	T data;
	//左孩子
	Yaya<T>* left;
	//右孩子
	Yaya<T>* right;
};

template <typename T>
inline Yaya<T>::Yaya()
{
	left = nullptr;
	right = nullptr;
}

template <typename T>
inline Yaya<T>::~Yaya()
{
}

#endif // !YAYA_H_INCLUDE
