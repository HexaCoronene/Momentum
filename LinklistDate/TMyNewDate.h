#ifndef TMYNEWDATE_H
#define TMYNEWDATE_H

#include "TMyDate.h"

class TMyNewDate : public TMyDate {
public:
	TMyNewDate() = default;
	TMyNewDate(std::string s) : TMyDate(s) {}
	bool IsWeekday(void);
	bool IsWeekend(void);
	bool IsDateEqual(TMyNewDate date);
	bool IsDateAfter(TMyNewDate date);
	bool IsDateBefore(TMyNewDate date);
};

#endif // TMYNEWDATE_H
