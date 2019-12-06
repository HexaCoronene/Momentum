#include "Maze.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int Maze::NextPos(int Curpos, int direction)
{
	switch( direction )
	{
		case -1:return interMaze[Curpos].left;
		case 0:return interMaze[Curpos].forw;
		case 1:return interMaze[Curpos].right;
		case 2:return interMaze[Curpos].back;
		default:exit(1);
	}
}

Maze::Maze()
{
	std::string filename = "Maze.txt";
	ifstream fin;
	fin.open(filename, ios::in);
	if( !fin )
	{
		cerr << "Cannot Open Maze File:Maze.txt" << endl;
		exit(1);
	}
	fin >> MazeSize;
	Stck = new Stack<int>(MazeSize + 1);
	interMaze = new Intersection[MazeSize + 1];
	for( int i = 1; i <= MazeSize; i++ )
	{
		fin >> interMaze[i].left >> interMaze[i].forw >> interMaze[i].right >> interMaze[i].back;
		interMaze[i].tag = 1;
		interMaze[i].pos = i;
	}
	fin.close();
}

void Maze::ReadMazeGraph(void)
{
	std::string filename = "MazeGraph.txt";
	ifstream fin;
	string m, temp;
	fin.open(filename, ios::in);
	if( !fin )
	{
		cerr << "Cannot Open Maze File:MazeGraph.txt" << endl;
		exit(1);
	}
	while( fin )
	{
		getline(fin, temp);
		m = m + temp + "\n";
	}
	cout << m << endl;
}

void Maze::TraverseMazeStack(int Entr, int Ext)
{
	int dir = -1, next = 0;
	curr = Entr;//获取当前位置为参数Entr位置
	interMaze[curr].tag = 0;//令当前路口的标记为0，代表已经走过这个路口
	cout << "入口：" << curr << endl;
	while( true )
	{
		if( curr == Ext )
		{
			Stck->Push(curr);
			cout << "出口：" <<curr << endl;
			break;
		}//如果当前路口位置＝参数Ext，则打印当前路口，退出无限循环

		while( dir != 3 )//循环，分别向3个方向尝试进入到下一个路口
		{
			next = NextPos(curr, dir);//获取当前方向下的下一个路口位置
			if( next != 0 && interMaze[next].tag == 1 )//如果下一个路口存在（位置不为0）且下一个路口还没有走过（标记为1）则
			{
				cout << "由" << curr << "口进入到";
				Stck->Push(curr);//当前路口入栈
				curr = next;//当前路口更新为下一个路口
				cout << curr << "口" << endl;
				interMaze[curr].tag = 0;
				break;
			}
			dir++;
		}
		if( dir == 3 )//如果三个方向都没走通，则需要退出当前路口，回到上一个路口：出栈，取出位置更新为当前路口
		{
			cout << "由" << curr << "口退回到";
			Stck->Pop(curr);
			cout << curr << "口" << endl;
		}
		dir = -1;
	}
}
