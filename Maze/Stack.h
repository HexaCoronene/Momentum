#ifndef STACK_H
#define STACK_H
#include <ostream>

template <class T>
class Stack {
private:
	int maxsize;
	T *stck;
	int top;
	void stackFull();
public:
	Stack() :Stack(50) {}
	Stack(int sz);
	~Stack() { delete stck; };
	bool Pop(T &x);
	void Push(T x);
	bool IsFull();
	bool IsEmpty();
	int getSize();
	friend std::ostream &operator<<(std::ostream &os, Stack<T> s)
	{
		T x;
		for( int i = s.top; i >= 0; i-- )
		{
			s.Pop(x);
			os << i << ":" << x << std::endl;
		}
		return os;
	}
};

template<class T>
inline bool Stack<T>::IsFull()
{
	return (top == maxsize - 1) ? true : false;
}

template<class T>
inline bool Stack<T>::IsEmpty()
{
	return (top == -1) ? true : false;
}

template<class T>
inline int Stack<T>::getSize()
{
	return top + 1;
}

template<class T>
void Stack<T>::stackFull()
{
	T *newStck = new T[maxsize * 2];
	if( newStck == nullptr )
	{
		std::cerr << "´æ´¢·ÖÅäÊ§°Ü£¡" << std::endl;
	}
	for( int i = 0; i < maxsize; i++ )
	{
		newStck[i] = stck[i];
	}
	maxsize *= 2;
	delete[]stck;
	stck = newStck;
}

template <class T>
Stack<T>::Stack(int sz) :top(-1), maxsize(sz)
{
	stck = new T[maxsize];
	if( stck == nullptr )
	{
		std::cerr << "´æ´¢·ÖÅäÊ§°Ü£¡" << std::endl;
	}
};

template <class T>
bool Stack<T>::Pop(T &x)
{
	if( IsEmpty() == true )
	{
		return false;
	}
	x = stck[top--];
	return true;
};

template <class T>
void Stack<T>::Push(T x)
{
	if( IsFull() == true )
	{
		stackFull();
	}
	stck[++top] = x;
};

#endif // !STACK_H
