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
	curr = Entr;//��ȡ��ǰλ��Ϊ����Entrλ��
	interMaze[curr].tag = 0;//�ǰ·�ڵı��Ϊ0�������Ѿ��߹����·��
	cout << "��ڣ�" << curr << endl;
	while( true )
	{
		if( curr == Ext )
		{
			Stck->Push(curr);
			cout << "���ڣ�" <<curr << endl;
			break;
		}//�����ǰ·��λ�ã�����Ext�����ӡ��ǰ·�ڣ��˳�����ѭ��

		while( dir != 3 )//ѭ�����ֱ���3�������Խ��뵽��һ��·��
		{
			next = NextPos(curr, dir);//��ȡ��ǰ�����µ���һ��·��λ��
			if( next != 0 && interMaze[next].tag == 1 )//�����һ��·�ڴ��ڣ�λ�ò�Ϊ0������һ��·�ڻ�û���߹������Ϊ1����
			{
				cout << "��" << curr << "�ڽ��뵽";
				Stck->Push(curr);//��ǰ·����ջ
				curr = next;//��ǰ·�ڸ���Ϊ��һ��·��
				cout << curr << "��" << endl;
				interMaze[curr].tag = 0;
				break;
			}
			dir++;
		}
		if( dir == 3 )//�����������û��ͨ������Ҫ�˳���ǰ·�ڣ��ص���һ��·�ڣ���ջ��ȡ��λ�ø���Ϊ��ǰ·��
		{
			cout << "��" << curr << "���˻ص�";
			Stck->Pop(curr);
			cout << curr << "��" << endl;
		}
		dir = -1;
	}
}
