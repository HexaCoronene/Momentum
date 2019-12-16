#include <iostream>
#include <string>
#include "TMyNewDate.h"
#include "TMyDateList.h"
#include "Function.h"

using namespace std;

int main(void)
{
	Welcome();
	TMyDateList<TMyNewDate> ls;
	int res;
	ListGen(ls, res);
	string in;
	bool flag = true;
	FuncChoose();
	while( flag )
	{
		cout << "-------->";
		cin >> in;
		switch( in[0] )
		{
			case '1':AddHoliday(ls); break;
			case '2':DecHoliday(ls); break;
			case '3':CheckDay(ls); break;
			case '4':RestDay(ls); break;
			case '5':WorkDay(ls, res); break;
			case '6':ls.Print(); break;
			case 'q':flag = false; break;
		}
	}
	return 0;
}
