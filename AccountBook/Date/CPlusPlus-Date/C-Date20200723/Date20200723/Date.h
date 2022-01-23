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
	Date();//생성자
	~Date();//소멸자
	//기존에는 함수포인터로 메세지를 보냈는데 Date date는 Today생성을 위해 딱 한번 사용됨.
	//이 과정에서 static을 이용하면 그 한번을 위해 굳이 date이용없이 함수호출로 today를 생성가능함.
	static Date Today();//static을 사용하면 함수호출하듯이 사용가능.
	Date Yesterday();
	Date Tommorow();
	//Date TheDayBeforeYesterday();
	//Date TheDayAfterTommorrow();
	//Date LastWeek();
	//Date NextWeek();
	//Date LastMonth();
	//Date NextMonth();
	//Date LastYear();
	//Date NextYear();
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

