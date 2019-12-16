#include "TMyNewDate.h"

bool TMyNewDate::IsWeekday()
{
	int i = GetWday();
	if( i >= 1 && i <= 5 )
	{
		return true;
	}
	return false;
}

bool TMyNewDate::IsWeekend()
{
	return !IsWeekday();
}

bool TMyNewDate::IsDateAfter(TMyNewDate date)
{
	return *this > date;
}

bool TMyNewDate::IsDateBefore(TMyNewDate date)
{
	return *this < date;
}

bool TMyNewDate::IsDateEqual(TMyNewDate date)
{
	return *this == date;
}
