#ifndef YAYA_H_INCLUDE
#define YAYA_H_INCLUDE

/*********************************************
*	Project��QG����δ��鿼��
*	Function�������������
*	Author������yaya
*	Date��2019��4��20��00:10:59
*	Location������
*********************************************/

template <typename T>
class Yaya
{
public:
	Yaya();
	~Yaya();

public:
	//������
	T data;
	//����
	Yaya<T>* left;
	//�Һ���
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
