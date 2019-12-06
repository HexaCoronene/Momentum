#include "MyExp.h"
#include <string>
#include <sstream>
#include <stack>
#include <iostream>

using std::string;

MyExp::MyExp(string &in)
{
	expre = in;
	try
	{
		BrackInit();
	}
	catch( ... )
	{
		std::cerr << "Wrong!" << std::endl;
		exit(1);
	}
	CreateList();
}

void MyExp::CreateList()
{
	unsigned int i = 0;
	std::stack<GenListNode<string> *> st;
	char ch;
	GenListNode<string> *p = first;
	while( i != expre.size() )
	{
		ch = expre[i++];
		if( isalnum(ch) )
		{
			p->tlink = new GenListNode<string>(1);
			p = p->tlink;
			char temp[2] = { ch, 0 };
			p->info.value += std::string(temp);
			ch = expre[i++];
			while( isalnum(ch) || ch == '.' )
			{
				char temp2[2] = { ch, 0 };
				p->info.value += std::string(temp2);
				ch = expre[i++];
			}
		}
		if( ch == '(' )
		{
			p->tlink = new GenListNode<string>(2);
			st.push(p->tlink);
			p = p->tlink;
			p->info.hlink = new GenListNode<string>(0);
			p = p->info.hlink;
			continue;
		}
		else if( isPrCal(ch) || isLoCal(ch) )
		{
			p->tlink = new GenListNode<string>(1);
			p = p->tlink;
			char temp[2] = { ch, 0 };
			p->info.value = std::string(temp);
			continue;
		}
		else if( ch == ')' )
		{
			p->tlink = nullptr;
			p = st.top();
			st.pop();
		}
	}
}

double MyExp::Calculate(void)
{
	std::stack<GenListNode<string> *> st;
	GenListNode<string> *p = first;
	double left, right;
	std::stringstream ss;
	while( true )
	{
		switch( p->utype )
		{
			case 0:
			case 1:
				if( ChildCheck(p) )
				{
					while( p->utype != 2 ) { p = p->tlink; }
				}
				else
				{
					if( st.size() == 0 )
					{
						ss << first->tlink->info.value;
						ss >> left;
						return left;
					}
					else
					{
						GenListNode<string> *q = st.top();
						st.pop();
						if( p->tlink == nullptr )
						{
							p = q->info.hlink;
						}
						if( p != first )
						{
							if( p->utype == 0 )
							{
								p = p->tlink;
							}
							//取左值
							ss << p->info.value;
							ss >> left;
							ss.clear();
							//取运算符
							char ch;
							p = p->tlink;
							if( p == nullptr )
							{
								Remove(q->info.hlink);
								q->info.value = std::to_string(left);
								q->utype = 1;
								p = q;
								break;
							}
							ss << p->info.value;
							ss >> ch;
							ss.clear();
							//取右值
							p = p->tlink;
							ss << p->info.value;
							ss >> right;
							ss.clear();
							//一定要记得clear()

							switch( ch )
							{
								case '+':
									q->info.value = std::to_string(left + right);
									break;
								case '-':
									q->info.value = std::to_string(left - right);
									break;
								case '*':
									q->info.value = std::to_string(left * right);
									break;
								case '/':
									if( right - 0.0 < 1e-9 )
									{
										std::cerr << "ZeroDiv!" << std::endl;
										exit(1);
									}
									q->info.value = std::to_string(left / right);
									break;
							}
							//子表结点被替换为原子结点
							//子表被释放
							q->utype = 1;
							Remove(p);
							p = q;
						}
					}
				}
				break;
			case 2:
				st.push(p);
				p = p->info.hlink;
				break;
		}
	}
}

void MyExp::BrackInit()
{
	int beg = 0, end = 0;
	bool flag = false;


	//负数处理
	if( expre[0] == '-' )
	{
		expre = string("0") + expre;
	}
	while( expre.find("(-") != string::npos )
	{
		expre.replace(expre.find("(-"), 2, "(0-");
	}


	for( int j = 0; j < 2; j++ )
	{
		for( unsigned int i = 0; i < expre.size(); i++ )
		{
			switch( j )
			{
				case 0:flag = isPrCal(expre[i]); break;
				case 1:flag = isLoCal(expre[i]); break;
			}
			if( flag )
			{
				beg = LeftFind(i);
				end = RightFind(i);
				if( !(beg == -1 && end == -1) )
				{
					string temp = expre.substr(beg, end - beg);
					temp = string("(") + temp + string(")");
					expre.replace(beg, end - beg, temp);
					i++;
				}
			}
			flag = false;
		}
	}

	//纯数字处理
	if( expre[0] != '(' && expre[expre.size() - 1] != ')' )
	{
		expre = string("(") + expre + string(")");
	}
}

/*
**是不是'*','/'
*/
bool MyExp::isPrCal(char ch)
{
	return ch == '*' || ch == '/';
}

/*
**是不是'+','-'
*/
bool MyExp::isLoCal(char ch)
{
	return ch == '+' || ch == '-';
}

int MyExp::LeftFind(int num)
{
	int ParCount = 0;
	int i = num - 1;
	do
	{
		if( isPrCal(expre[i]) || isLoCal(expre[i]) )
		{
			return i + 1;
		}
		if( expre[i] == '(' )
		{
			return -1;
		}
		if( expre[i] == ')' )
		{
			ParCount++;
			while( ParCount != 0 )
			{
				i--;
				if( expre[i] == '(' )
				{
					ParCount--;
				}
				else if( expre[i] == ')' )
				{
					ParCount++;
				}
			}
			if( i > 0 )
			{
				if( expre[i - 1] == '(' )
				{
					return -1;
				}
			}
			return i;
		}
		i--;
	}
	while( i >= 0 );
	return 0;
}

int MyExp::RightFind(int num)
{
	int ParCount = 0;
	int i = num + 1;
	int size = expre.size();
	do
	{
		if( isPrCal(expre[i]) || isLoCal(expre[i]) )
		{
			return i;
		}
		if( expre[i] == ')' )
		{
			return -1;
		}
		if( expre[i] == '(' )
		{
			ParCount--;
			while( ParCount != 0 )
			{
				i++;
				if( expre[i] == '(' )
				{
					ParCount--;
				}
				else if( expre[i] == ')' )
				{
					ParCount++;
				}
			}
			if( i < expre.size() - 1 )
			{
				if( expre[i + 1] == ')' )
				{
					return -1;
				}
			}
			return i;
		}
		i++;
	}
	while( i < size );
	return size;
}

/*
**线性查找有没有子表结点
*/
bool MyExp::ChildCheck(GenListNode<std::string> *ls)
{
	GenListNode<std::string> *p = ls;
	while( p != nullptr )
	{
		if( p->utype == 2 )
		{
			return true;
		}
		p = p->tlink;
	}
	return false;
}
