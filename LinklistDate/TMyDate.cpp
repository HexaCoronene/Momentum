#include "TMyDate.h"
#include <iostream>
#include <sstream>
#include <ctime>

const int MONTH[13] = { 29, 31, 28, 31, 30, 31,
						30, 31, 31, 30, 31, 30, 31 };

using namespace std;

void TMyDate::AddDays(int DayCount)
{
	day += DayCount;
	Standardize();
}

void TMyDate::DecDays(int DayCount)
{
	day -= DayCount;
	Standardize();
}

void TMyDate::Standardize(void)
{
	while( day > MONTH[month] )
	{
		if( isLeap && month == 2 && day >= 29 )
		{
			if( day == 29 )
			{
				break;
			}
			day -= MONTH[0];
			month++;
		}
		else
		{
			day -= MONTH[month];
			month++;
		}
		if( month > 12 )
		{
			year++;
			month = 1;
			isLeap = Leap(year);
		}
	}
	while( day < 1 )
	{
		if( month == 1 )
		{
			year--;
			month = 12;
			day += MONTH[12];
			isLeap = Leap(year);
		}
		else if( month == 3 )
		{
			if( isLeap )
				day += MONTH[0];
			else
				day += MONTH[2];
			month = 2;
		}
		else
		{
			month--;
			day += MONTH[month];
		}
	}
}

TMyDate TMyDate::operator+(const int d)
{
	TMyDate sum(year, month, day + d);
	sum.Standardize();
	return sum;
}

TMyDate TMyDate::operator-(const int d)
{
	TMyDate sum(year, month, day - d);
	sum.Standardize();
	return sum;
}

bool TMyDate::operator==(TMyDate MyDate)
{
	return (year == MyDate.year)
		&& (month == MyDate.month)
		&& (day == MyDate.day);
}

bool TMyDate::operator<(TMyDate MyDate)
{
	if( year < MyDate.year )
	{
		return true;//年小于
	}
	else if( (year == MyDate.year) && (month < MyDate.month) )
	{
		return true;//年等，月小于
	}
	else if( (year == MyDate.year) && (month == MyDate.month) && (day < MyDate.day) )
	{
		return true;//年月等，日小于
	}
	return false;
}

bool TMyDate::operator>(TMyDate MyDate)
{
	return !((*this < MyDate) || (*this == MyDate));//偷懒写法
}

int TMyDate::operator-(const TMyDate MyDate)
{
	return this->DaysBetween(MyDate);
}

int TMyDate::DaysBetween(TMyDate MyDate)
{
	int min = (year < MyDate.year) ? year : MyDate.year;
	int date[2][4] = {
		{year, month, day, isLeap},
		{MyDate.year, MyDate.month, MyDate.day, MyDate.isLeap}
	};
	int day[2] = {};

	for( int i = 0; i != 2; ++i )
	{
		day[i] += date[i][2];
		date[i][1]--;
		for( ; date[i][1] > 0; date[i][1]-- )
		{
			if( isLeap && (date[i][1] == 2) )
			{
				day[i] += MONTH[0];
			}
			else
			{
				day[i] += MONTH[date[i][1]];
			}
		}

		for( ; date[i][0] > min; date[i][0]-- )
		{
			if( Leap(date[i][0]) )
			{
				day[i] += 366;
			}
			else
			{
				day[i] += 365;
			}
		}
	}
	return abs(day[0] - day[1]);
}

void TMyDate::Input(string s)
{
	stringstream stream;
	stream << s.substr(0, 4);
	stream >> year;
	stream.clear();
	stream << s.substr(4, 2);
	stream >> month;
	stream.clear();
	stream << s.substr(6, 2);
	stream >> day;
	stream.clear();
	isLeap = Leap(year);
	Standardize();
}

void TMyDate::Input(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
	isLeap = Leap(year);
	Standardize();
}

void TMyDate::Print()
{
	this->Standardize();
	cout << year << "-" << month << "-" << day << endl;
}

bool TMyDate::Leap(int y)
{
	return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

int TMyDate::GetWday(void)
{
	tm t = { 0 };
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;
	t.tm_mday = day;
	time_t t_ = mktime(&t);
	localtime_s(&t, &t_);
	if( t.tm_wday == 0 )
	{
		return 7;
	}
	return t.tm_wday;
}

TMyDate::TMyDate(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
	isLeap = Leap(year);
}

TMyDate::TMyDate(std::string s)
{
	Input(s);
}

void TMyDate::NowInit(void)
{
	time_t t;
	t = time(&t);
	struct tm t_;
	localtime_s(&t_, &t);
	this->Input(t_.tm_year + 1900, t_.tm_mon + 1, t_.tm_mday);
}