#include <iostream>
#include "DulList.h"
#include "Function.h"
using namespace std;

int main(void)
{
	DulList<int> ls;
	int num = 0;
	cout << "人数:" << endl;
	cin >> num;
	int inter = 0;
	cout << "报数间隔：" << endl;
	cin >> inter;
	int begin = 0;
	cout << "开始位置：" << endl;
	cin >> begin;
	string route;
	cout << "循环方向，左侧'l'，右侧'r'" << endl;
	cin >> route;
	Josephus(ls, num, inter, begin, route);
	return 0;
}
