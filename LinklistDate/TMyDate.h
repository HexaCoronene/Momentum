#ifndef TMYDATE_H
#define TMYDATE_H
#include <string>
#include <ostream>

class TMyDate {
public:
	TMyDate() = default;
	TMyDate(int y, int m, int d);
	TMyDate(std::string);
	void AddDays(int);
	void DecDays(int);
	void Standardize(void);
	int DaysBetween(TMyDate);
	void Input(std::string);
	void Input(int y, int m, int d);
	void Print();
	void NowInit(void);
	static bool Leap(int);
	int GetWday(void);
	TMyDate operator+(const int);
	TMyDate operator-(const int);
	bool operator==(TMyDate);
	bool operator<(TMyDate);
	bool operator>(TMyDate);
	int operator-(const TMyDate);
	friend std::ostream &operator<<(std::ostream &os, TMyDate &MyDate)
	{
		os << MyDate.year << "-" << MyDate.month << "-" << MyDate.day;
		return os;
	}

private:
	int day;
	int month;
	int year;
	bool isLeap;
};


#endif // TMYDATE_H
