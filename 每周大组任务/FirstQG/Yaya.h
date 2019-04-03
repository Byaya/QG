#ifndef YAYA_H_INCLUDE
#define YAYA_H_INCLUDE

/***********************************************
*	Function:泛型双向链表结点类
*	Author：风雅yaya
*	Date：2019年3月23日19:31:59
***********************************************/

template<typename T>
class Yaya
{
public:
	Yaya();
	Yaya(T data);
	~Yaya();

public:
	//数据域
	T data;
	//前指针
	Yaya<T>* prior;
	//后指针
	Yaya<T>* next;
private:

};


template<typename T>
inline Yaya<T>::Yaya()
{
	prior = nullptr;
	next = nullptr;
}

template<typename T>
Yaya<T>::Yaya(T data)
{
	prior = nullptr;
	next = nullptr;
	Yaya::data = data;
}


template<typename T>
Yaya<T>::~Yaya()
{
}
#endif // YAYA_H_INCLUDE


