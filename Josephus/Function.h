#ifndef FUNCTION_H
#define FUNCTION_H
#include "DulList.h"
#include <iostream>

void ListGen(DulList<int> &ls, const int num)
{
	for( int j = 0; j < num; j++ )
	{
		ls.inputR(j + 1);
	}
}

//void Josephus(DulList<int> &ls, const int num, const int inter, int begin, std::string route)
//{
//	ListGen(ls, num);
//	int beg = begin;
//	int del = 0;
//	DulNode<int> *that = nullptr;
//	int len = ls.Length();
//	while( len != 1 )
//	{
//		that = ls.NoStLocate(beg, inter - 1, route);
//		ls.Search(that->data, del);
//		ls.EspePrint(del);
//		ls.Delete(that->data);
//		len = ls.Length();
//		if( route == "r" )
//		{
//			beg = del + 1;
//			if( beg > len )
//			{
//				beg = 1;
//			}
//		}
//		else
//		{
//			beg = del - 1;
//			if( beg < 0 )
//			{
//				beg = len;
//			}
//		}
//	}
//	ls.Print();
//}

void Josephus(DulList<int> &ls, const int num, const int inter, const int begin, std::string route)
{
	ListGen(ls, num);
	DulNode<int> *beg = ls.Locate(begin, "r"),
		*first = ls.GetHead(),
		*p = nullptr;
	int x;
	bool flag = false;
	std::string s;
	std::cout << "是否显示过程？[y/n]" << std::endl;
	std::cin >> s;
	if( s == "y" )
	{
		flag = true;
	}
	if( route == "r" )
	{
		for( int i = 0; i < num - 1; i++ )
		{
			p = beg;
			for( int j = 0; j < inter - 1; j++ )
			{
				if( p == first )
				{
					p = p->next;
				}
				p = p->next;
				if( p == first )
				{
					p = p->next;
				}
				beg = p->next;
			}
			ls.Search(p->data, x);
			if( flag )
			{
				ls.EspePrint(x);
			}
			ls.Delete(p->data);
		}
	}
	else
	{
		for( int i = 0; i < num - 1; i++ )
		{
			p = beg;
			for( int j = 0; j < inter - 1; j++ )
			{
				if( p == first )
				{
					p = p->prior;
				}
				p = p->prior;
				if( p == first )
				{
					p = p->prior;
				}
				beg = p->prior;
			}
			ls.Search(p->data, x);
			if( flag )
			{
				ls.EspePrint(x);
			}
			ls.Delete(p->data);
		}
	}
	ls.Print();
}
#endif //FUNCTION_H