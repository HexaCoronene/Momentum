#include <iostream>
#include "DulList.h"
#include "Function.h"
using namespace std;

int main(void)
{
	DulList<int> ls;
	int num = 0;
	cout << "����:" << endl;
	cin >> num;
	int inter = 0;
	cout << "���������" << endl;
	cin >> inter;
	int begin = 0;
	cout << "��ʼλ�ã�" << endl;
	cin >> begin;
	string route;
	cout << "ѭ���������'l'���Ҳ�'r'" << endl;
	cin >> route;
	Josephus(ls, num, inter, begin, route);
	return 0;
}
