#ifndef TMYDATELIST_H
#define TMYDATELIST_H

#include "TMyNewDate.h"

template <class T>
struct LinkNode {
	T data;
	LinkNode<T> *link = nullptr;
	LinkNode() = default;
	LinkNode(const T &item, LinkNode<T> *prt = nullptr)
	{
		data = item; link = prt;
	}
};

//类模板无法实现分离式编译，故声明与定义置于同一头文件
template <class T>
class TMyDateList {
protected:
	LinkNode<T> *first;
	LinkNode<T> *last;
public:
	TMyDateList();
	~TMyDateList();
	void makeEmpty(void);
	void inputR(T &x);
	LinkNode<T> *Search(T x);
	LinkNode<T> *Locate(int i);
	bool Insert(int i, T &x);
	bool Remove(int i, T &x);
	bool Delete(T &x);
	void Print();
	int Length()const;
};

template <class T>
TMyDateList<T>::TMyDateList()
{
	first = new LinkNode<T>;
	first->link = nullptr;
	last = first;
}

template <class T>
TMyDateList<T>::~TMyDateList()
{
	makeEmpty();
}

template <class T>
void TMyDateList<T>::makeEmpty()
{
	LinkNode<T> *q;
	while( first->link != nullptr )
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

template<class T>
void TMyDateList<T>::inputR(T &x)
{
	LinkNode<T> *newNode;
	newNode = new LinkNode<T>(x);
	last->link = newNode;
	last = newNode;
	last->link = nullptr;
}

template <class T>
LinkNode<T> *TMyDateList<T>::Locate(int i)
{
	if( i < 0 )
	{
		return nullptr;
	}
	LinkNode<T> *current = first;
	int k = 0;
	while( current != nullptr && k < i )
	{
		current = current->link;
		k++;
	}
	return nullptr;
}

template <class T>
LinkNode<T> *TMyDateList<T>::Search(T x)
{
	LinkNode<T> *current = first->link;
	while( current != nullptr )
	{
		if( current->data == x )
		{
			break;
		}
		else
		{
			current = current->link;
		}
	}
	return current;
}

template <class T>
bool TMyDateList<T>::Insert(int i, T &x)
{
	LinkNode<T> *current = Locate(i);
	if( current == nullptr )
	{
		return false;
	}
	LinkNode<T> *newNode = new LinkNode<T>(x);
	if( newNode == nullptr )
	{
		std::cerr << "存储分配错误！" << std::endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

template <class T>
bool TMyDateList<T>::Remove(int i, T &x)
{
	LinkNode <T> *current = Locate(i - 1);
	if( current == nullptr || current->link == nullptr )
	{
		return false;
	}
	LinkNode<T> *del = current->link;
	del->link = current->link;
	x = del->data;
	delete del;
	return true;
}

template<class T>
bool TMyDateList<T>::Delete(T &x)
{
	LinkNode<T> *p = first->link;
	LinkNode<T> *q = first;
	while( p != nullptr )
	{
		if( p->data == x )
		{
			q->link = p->link;
			delete p;
			if( q->link == nullptr )
			{
				last = q;
			}
			return true;
		}
		else
		{
			q = p;
			p = p->link;
		}
	}
	return false;
}

template <class T>
void TMyDateList<T>::Print()
{
	LinkNode<T> *current = first->link;
	while( current != nullptr )
	{
		std::cout << current->data << std::endl;
		current = current->link;
	}
}

template<class T>
int TMyDateList<T>::Length() const
{
	LinkNode<T> *p = first->link;
	int count = 0;
	while( p != nullptr )
	{
		p = p->link;
		count++;
	}
	return count;
}

#endif // TMYDATELIST_H
