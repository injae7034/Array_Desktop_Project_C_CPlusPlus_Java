#ifndef _DATE_H
#define _DATE_H

enum Month
{
	JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6,
	JUL = 7, AUG = 8, SEP = 9, OCT = 10, NOV = 11, DEC = 12
};
enum WeekDay
{
	SUN = 0, MON = 1, TUE = 2, WED = 3, THU = 4, FRI = 5, SAT = 6
};

class Date
{
public:
	Date();//持失切
	~Date();//社瑚切
	Date Today();
	Date Yesterday();
	Date Tommorow();
	Date TheDayBeforeYesterday();
	Date TheDayAfterTommorrow();
	Date LastWeek();
	Date NextWeek();
	Date LastMonth();
	Date NextMonth();
	Date LastYear();
	Date NextYear();
	Date PreviousDate(int days);
	Date NextDate(int days);
	bool IsEqual(Date other);
	bool IsNotEqual(Date other);
	bool IsGreaterThan(Date other);
	bool IsLesserThan(Date other);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetWeekDay() const;

private:
	int year;
	Month month;
	int day;
	WeekDay weekDay;
};



inline int Date::GetYear() const
{
	return this->year;
}

inline int Date::GetMonth() const
{
	return this->month;
}

inline int Date::GetDay() const
{
	return this->day;
}

inline int Date::GetWeekDay() const
{
	return this->weekDay;
}

#endif // !_DATE_H

