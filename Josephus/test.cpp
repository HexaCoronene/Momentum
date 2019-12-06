#include "DulList.h"
#include <iostream>

void ListGen(DulList<int> &ls, int num)
{
	for( int j = 0; j < num; j++ )
	{
		ls.inputR(j + 1);
	}
}

void Josephus(DulList<int> &ls, const int num, const int inter, int begin, std::string route)
{
	ListGen(ls, num);
	DulNode<int> *beg = nullptr,
		*first = ls.GetHead(),
		*p = ls.Locate(begin, "r");
	int x;
	if( route == "r" )
	{
		for( int i = 0; i < num - 1; i++ )
		{
			for( int j = 0; j < inter - 1; j++ )
			{
				beg = p;
				p = p->next;
				if( p == first )
				{
					p = p->next;
				}
			}
			ls.Search(p->data, x);
			ls.EspePrint(x);
			ls.Delete(p->data);
		}
	}
	else
	{
		for( int i = 0; i < num - 1; i++ )
		{
			for( int j = 0; j < inter - 1; j++ )
			{
				beg = p;
				p = p->prior;
				if( p == first )
				{
					p = p->prior;
				}
			}
			ls.Search(p->data, x);
			ls.EspePrint(x);
			ls.Delete(p->data);
		}
	}
}
