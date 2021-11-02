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
{//class scope
public://멤버함수
	//생성자(Constrcutor)
	Date();//디폴트생성자
	Date(int year, Month month, int day);//특정날짜 생성자
	Date(char(*date));//문자열을 정수 날짜로 바꾸는 생성자
	Date(const Date& source);//복사생성자
	~Date();//소멸자(Destructor)
	operator char* ();//형변환함수: 정수 날짜를 문자열로 바꿈
	//기존에는 함수포인터로 메세지를 보냈는데 Date date는 Today생성을 위해 딱 한번 사용됨.
	//이 과정에서 static을 이용하면 그 한번을 위해 굳이 date이용없이 함수호출로 today를 생성가능함.
	static Date Today();//static을 사용하면 Date.Today()할 필요없이 함수호출로 사용 가능.
	Date Yesterday();
	Date Tommorow();
	Date PreviousDate(int days);
	Date NextDate(int days);
	bool IsEqual(const Date& other);
	bool IsNotEqual(const Date& other);
	bool IsGreaterThan(const Date& other);
	bool IsLesserThan(const Date& other);
	//연산자함수
	bool operator==(const Date& other);//IsEqual
	bool operator!=(const Date& other);//IsNotEqual
	bool operator>(const Date& other);//IsGreaterThan
	bool operator>=(const Date& other);//IsGreaterThan
	bool operator<(const Date& other);//IsLesserThan
	bool operator<=(const Date& other);//IsLesserThan
	Date& operator--();//Yesterday전위
	Date operator--(int);//Yesterday후위
	Date& operator++();//Tommorow전위
	Date operator++(int);//Tommorow후위
	Date operator-(int days);//PreviousDate
	Date operator+(int days);//NextDate
	Date& operator=(const Date& source);//치환연산자
	char* GetWeekDayString();//요일 문자열로 구하는함수
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetWeekDay() const;

private://데이터멤버
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

