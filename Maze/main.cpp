#include "Maze.h"
#include "Stack.h"
#include <iostream>

using namespace std;

int main(void)
{
	Maze maze;
	int enter = 0, exit = 0;
	maze.ReadMazeGraph();
	cout << "���������" << endl;
	cin >> enter;
	cout << "���������" << endl;
	cin >> exit;
	maze.TraverseMazeStack(enter, exit);
	maze.OutputStack();
	return 0;
}