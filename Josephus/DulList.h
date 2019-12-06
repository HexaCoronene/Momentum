#include <string>
#ifndef DULLIST_H
#define DULLIST_H

template <class T>
struct DulNode {
	T data;
	DulNode<T> *prior = nullptr;
	DulNode<T> *next = nullptr;
	DulNode() = default;
	DulNode(const T item, DulNode<T> *prt = nullptr)
	{
		data = item; prior = next = prt;
	}
};

//类模板无法实现分离式编译，故声明与定义置于同一头文件
template <class T>
class DulList {
protected:
	DulNode<T> *first;
public:
	DulList();
	~DulList();
	void makeEmpty(void);
	void inputR(T x);
	DulNode<T> *GetHead();
	DulNode<T> *Search(const T x, int &i);
	DulNode<T> *Locate(int i, std::string s);
	//DulNode<T> *NoStLocate(const int begin, const int inter, std::string);
	bool Insert(int i, T &x, std::string s);
	bool Remove(int i, T &x);
	bool Delete(T x);
	void Print();
	void EspePrint(const int i);
	int Length()const;
};

template <class T>
DulList<T>::DulList()
{
	first = new DulNode<T>(0);
	if( first == nullptr )
	{
		std::cerr << "存储分配出错！" << std::endl;
		exit(1);
	}
	first->next = first;
	first->prior = first;
}

template <class T>
DulList<T>::~DulList()
{
	makeEmpty();
	delete first;
}

template <class T>
void DulList<T>::makeEmpty()
{
	DulNode<T> *q;
	while( first->next != first )
	{
		q = first->next;
		first->next = q->next;
		delete q;
	}
}

template<class T>
void DulList<T>::inputR(T x)
{
	DulNode<T> *newNode = new DulNode<T>(x);
	if( newNode == nullptr )
	{
		std::cerr << "存储分配错误！" << std::endl;
		exit(1);
	}
	newNode->prior = first->prior;
	first->prior->next = newNode;
	newNode->next = first;
	first->prior = newNode;
}

template<class T>
inline DulNode<T> *DulList<T>::GetHead()
{
	return first;
}

template <class T>
DulNode<T> *DulList<T>::Locate(int i, std::string s)
{
	if( first->next == first || i == 0 )
	{
		return first;
	}

	DulNode<T> *current = nullptr;
	if( s == std::string("l") )
	{
		current = first->prior;
	}
	else
	{
		current = first->next;
	}
	for( int j = 1; j < i; j++ )
	{
		if( current == first )
		{
			break;
		}
		else if( s == std::string("l") )
		{
			current = current->prior;
		}
		else
		{
			current = current->next;
		}
	}
	if( current != first )
	{
		return current;
	}
	else
	{
		return nullptr;
	}
}

//template<class T>
//DulNode<T> *DulList<T>::NoStLocate(const int begin, const int inter, std::string s)
//{
//	DulNode<T> *current = first;
//	std::string flag = "l";
//
//	for( int j = 0; j < begin; j++ )
//	{
//		current = current->next;
//	}
//
//	for( int j = 0; j < inter; j++ )
//	{
//		if( s == flag )
//		{
//			current = current->prior;
//			if( current == first )
//			{
//				current = current->prior;
//			}
//		}
//		else
//		{
//			current = current->next;
//			if( current == first )
//			{
//				current = current->next;
//			}
//		}
//	}
//	return current;
//}

template <class T>
DulNode<T> *DulList<T>::Search(T x, int &i)
{
	i = 1;
	DulNode<T> *current = first->next;
	while( current != first && current->data != x )
	{
		current = current->next;
		i++;
	}
	if( current != first )
	{
		return current;
	}
	else
	{
		return nullptr;
		i = -1;
	}
}

//未完成
template <class T>
bool DulList<T>::Insert(int i, T &x, std::string s)
{
	DulNode<T> *current = Locate(i);
	if( current == nullptr )
	{
		return false;
	}
	DulNode<T> *newNode = new DulNode<T>(x);
	if( newNode == nullptr )
	{
		std::cerr << "存储分配错误！" << std::endl;
		exit(1);
	}
	newNode->next = current->next;
	current->next = newNode;
	return true;
}

//未完成
template <class T>
bool DulList<T>::Remove(int i, T &x)
{
	DulNode <T> *current = Locate(i - 1);
	if( current == nullptr || current->next == nullptr )
	{
		return false;
	}
	DulNode<T> *del = current->next;
	del->next = current->next;
	x = del->data;
	delete del;
	return true;
}

template<class T>
bool DulList<T>::Delete(T x)
{
	DulNode<T> *p = first->next;
	DulNode<T> *q = first;
	while( p != first )
	{
		if( p->data == x )
		{
			q->next = p->next;
			p->next->prior = q;
			delete p;
			return true;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	return false;
}

template <class T>
void DulList<T>::Print()
{
	DulNode<T> *current = first->next;
	while( current != first )
	{
		std::cout << current->data << std::endl;
		current = current->next;
	}
}

template<class T>
inline void DulList<T>::EspePrint(const int i)
{
	DulNode<T> *current = first->next;
	int j = 1;
	while( current != first )
	{

		if( j == i )
		{
			std::cout << "[" << current->data << "] ";
		}
		else
		{
			std::cout << current->data << " ";
		}
		current = current->next;
		j++;
	}
	std::cout << std::endl;
}

template<class T>
int DulList<T>::Length() const
{
	DulNode<T> *p = first->next;
	int count = 0;
	while( p != first )
	{
		p = p->next;
		count++;
	}
	return count;
}

#endif // DULLIST_H
