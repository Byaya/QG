#ifndef YAYA_H_INCLUDE
#define YAYA_H_INCLUDE

/***********************************************
*	Function:����˫����������
*	Author������yaya
*	Date��2019��3��23��19:31:59
***********************************************/

template<typename T>
class Yaya
{
public:
	Yaya();
	Yaya(T data);
	~Yaya();

public:
	//������
	T data;
	//ǰָ��
	Yaya<T>* prior;
	//��ָ��
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


