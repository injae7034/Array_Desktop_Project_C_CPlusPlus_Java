#include "Date.h"
#include<cstdio>//sprintf
#include<ctime>
#include<cstring>//strcpy
#pragma warning(disable:4996)

//생성자
Date::Date()
{
	this->year = 1900;
	this->month = JAN;
	this->day = 1;
	this->weekDay = MON;
}

Date::Date(int year, Month month, int day)
{
	struct tm specificDay = { 0, };

	specificDay.tm_year = year - 1900;
	specificDay.tm_mon = month - 1;
	specificDay.tm_mday = day;

	mktime(&specificDay);

	this->year = specificDay.tm_year + 1900;
	this->month = static_cast<Month>(specificDay.tm_mon + 1);
	this->day = specificDay.tm_mday;
	this->weekDay = static_cast<WeekDay>(specificDay.tm_wday);
}

Date::Date(char(*date))
{
	struct tm specificDay = { 0, };
	int year;
	Month month;
	int day;

	sscanf(date, "%4d%2d%2d", &year, &month, &day);
	specificDay.tm_year = year - 1900;
	specificDay.tm_mon = month - 1;
	specificDay.tm_mday = day;

	mktime(&specificDay);

	this->year = specificDay.tm_year + 1900;
	this->month=static_cast<Month>(specificDay.tm_mon + 1);
	this->day = specificDay.tm_mday;
	this->weekDay = static_cast<WeekDay>(specificDay.tm_wday);
}


//복사생성자
Date::Date(const Date& source)
{
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;
}

//소멸자
Date::~Date()
{
}

//형변환함수
Date::operator char* ()
{
	static char buffer[9];

	sprintf(buffer, "%4d%02d%02d", this->year, this->month, this->day);
	return buffer;
}

//요일 문자열로 구하는함수
char* Date::GetWeekDayString()
{
	static char weekDay[10];

	if (this->weekDay == SUN)
	{
		strcpy(weekDay, "SUNDAY");
	}
	else if (this->weekDay == MON)
	{
		strcpy(weekDay, "MONDAY");
	}
	else if (this->weekDay == TUE)
	{
		strcpy(weekDay, "TUESDAY");
	}
	else if (this->weekDay == WED)
	{
		strcpy(weekDay, "WEDNESDAY");
	}
	else if (this->weekDay == THU)
	{
		strcpy(weekDay, "THURSDAY");
	}
	else if (this->weekDay == FRI)
	{
		strcpy(weekDay, "FRIDAY");
	}
	else if (this->weekDay == SAT)
	{
		strcpy(weekDay, "SATURDAY");
	}
	return weekDay;
}

//Today
Date Date::Today()
{
	time_t timer;// 초 단위 기간값 저장변수 선언(컴푸터를 위한 시간단위)
	struct tm* today;// 년, 월, 일 형식 시간 값 저장변수 선언(사람을 위한 시간단위)
	Date today_;//Date()

	time(&timer);//현재 시간을 구하다.
	today = localtime(&timer);// 초 단위 시간값을 년, 월, 일 형식의 시간값으로 바꾸다.

	today_.year = today->tm_year + 1900;//년 설정
	today_.month = static_cast<Month>(today->tm_mon + 1);//월 설정
	today_.day = today->tm_mday;//일 설정
	today_.weekDay = static_cast<WeekDay>(today->tm_wday);//요일 설정

	return today_;//~Date()
}

//Yesterday
Date Date::Yesterday()
{
	struct tm yesterday = { 0, };
	Date yesterday_;//Date()

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;//어제이므로 1감소시킴.

	mktime(&yesterday);//날짜 형식을 바꾸다.

	yesterday_.year = yesterday.tm_year + 1900;//년 설정
	yesterday_.month = static_cast<Month>(yesterday.tm_mon + 1);//월 설정
	yesterday_.day = yesterday.tm_mday;//일 설정
	yesterday_.weekDay = static_cast<WeekDay>(yesterday.tm_wday);//요일 설정

	return yesterday_;//~Date()
}

//Tommorow
Date Date::Tommorow()
{
	struct tm tommorow = { 0, };
	Date tommorow_;//Date()

	tommorow.tm_year = this->year - 1900;
	tommorow.tm_mon = this->month - 1;
	tommorow.tm_mday = this->day + 1;//오늘이므로 1증가시킴.

	mktime(&tommorow);//날짜 형식을 바꾸다.

	tommorow_.year = tommorow.tm_year + 1900;//년 설정
	tommorow_.month = static_cast<Month>(tommorow.tm_mon + 1);//월 설정
	tommorow_.day = tommorow.tm_mday;//일 설정
	tommorow_.weekDay = static_cast<WeekDay>(tommorow.tm_wday);//요일 설정

	return tommorow_;//~Date()
}

//PreviousDate
Date Date::PreviousDate(int days)
{
	struct tm previousDate = { 0, };
	Date previousDate_;//Date()

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;//days만큼 감소시킴.

	mktime(&previousDate);//날짜 형식을 바꾸다.

	previousDate_.year = previousDate.tm_year + 1900;//년 설정
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);//월 설정
	previousDate_.day = previousDate.tm_mday;//일 설정
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);//요일 설정

	return previousDate_;//~Date()
}

//NextDate
Date Date::NextDate(int days)
{
	struct tm nextDate = { 0, };
	Date nextDate_;//Date()

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;//days만큼 증가시킴.

	mktime(&nextDate);//날짜 형식을 바꾸다.

	nextDate_.year = nextDate.tm_year + 1900;//년 설정
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);//월 설정
	nextDate_.day = nextDate.tm_mday;//일 설정
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);//요일 설정

	return nextDate_;//~Date()
}

//IsEqual
bool Date::IsEqual(const Date& other)
{
	bool ret = false;
	if (this->year == other.year && this->month == other.month && this->day == other.day)
	{
		ret = true;
	}
	return ret;
}

//IsNotEqual
bool Date::IsNotEqual(const Date& other)
{
	bool ret = false;
	if (this->year != other.year || this->month != other.month || this->day != other.day)
	{
		ret = true;
	}
	return ret;
}

//IsGreaterThan
bool Date::IsGreaterThan(const Date& other)
{
	bool ret = false;

	if (this->year > other.year)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day)
	{
		ret = true;
	}
	return ret;
}

//IsLesserThan
bool Date::IsLesserThan(const Date& other)
{
	bool ret = false;

	if (this->year < other.year)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day)
	{
		ret = true;
	}
	return ret;
}

//연산자함수
// operator==
bool Date::operator==(const Date& other)//IsEqual
{
	bool ret = false;
	if (this->year == other.year && this->month == other.month && this->day == other.day)
	{
		ret = true;
	}
	return ret;
}

//operator!
bool Date::operator!=(const Date& other)//IsNotEqual
{
	bool ret = false;
	if (this->year != other.year || this->month != other.month || this->day != other.day)
	{
		ret = true;
	}
	return ret;
}

//operator>
bool Date::operator>(const Date& other)//IsGreaterThan
{
	bool ret = false;
	if (this->year > other.year)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day)
	{
		ret = true;
	}
	return ret;
}

//operator>=
bool Date::operator>=(const Date& other)
{
	bool ret = false;
	if (this->year > other.year)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day >= other.day)
	{
		ret = true;
	}
	return ret;
}

//operator<
bool Date::operator<(const Date& other)
{
	bool ret = false;

	if (this->year < other.year)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day)
	{
		ret = true;
	}
	return ret;
}

//operator<=
bool Date::operator<=(const Date& other)
{
	bool ret = false;

	if (this->year < other.year)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month)
	{
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day <= other.day)
	{
		ret = true;
	}
	return ret;
}

//operator--전위
Date& Date::operator--()//Yesterday전위
{
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - 1;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return *this;
}

//operator--후위
Date Date::operator--(int)//Yesterday후위
{
	struct tm date = { 0, };
	Date date_(*this);//복사생성자로 데이터멤버값을 복사하면 됨.

	date.tm_year = this->year - 1900;
	date.tm_mon= this->month - 1;
	date.tm_mday = this->day - 1;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}

//operator++전위
Date& Date::operator++()//Tommorow전위
{
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return *this;
}

//operator++후위
Date Date::operator++(int)//Tommorow후위
{
	struct tm date = { 0, };
	Date date_(*this);//복사생성자로 데이터멤버값을 복사하면 됨.

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}

//operator-
Date Date::operator-(int days)//PreviousDate
{
	struct tm previousDate = { 0, };
	Date previousDate_;//Date()

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;//days만큼 감소시킴.

	mktime(&previousDate);//날짜 형식을 바꾸다.

	previousDate_.year = previousDate.tm_year + 1900;//년 설정
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);//월 설정
	previousDate_.day = previousDate.tm_mday;//일 설정
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);//요일 설정

	return previousDate_;//~Date()
}

//operator+
Date Date::operator+(int days)//NextDate
{
	struct tm nextDate = { 0, };
	Date nextDate_;//Date()

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;//days만큼 증가시킴.

	mktime(&nextDate);//날짜 형식을 바꾸다.

	nextDate_.year = nextDate.tm_year + 1900;//년 설정
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);//월 설정
	nextDate_.day = nextDate.tm_mday;//일 설정
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);//요일 설정

	return nextDate_;//~Date()
}

//치환연산자
Date& Date::operator=(const Date& source)
{
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;

	return *this;
}

#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. Date를 만든다.
	Date date;//Date()
	Date today;//Date()
	Date yesterday;//Date()
	bool ret;
	Date previousDate;//Date()
	Date tommorow;//Date()
	Date next2Date;//Date()
	Date next1Date;//Date()

	//2. 오늘 날짜를 구한다.
	today = Date::Today();//static을 헤더파일에서 했으므로 함수포인터 메세지 대신에 함수호출로 가능
	cout << today.GetYear() << "-"
		<< today.GetMonth() << "-"
		<< today.GetDay() << "-"
		<< today.GetWeekDayString() << endl;
	//3. 어제 날짜를 구한다.
	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-"
		<< yesterday.GetMonth() << "-"
		<< yesterday.GetDay() << "-"
		<< yesterday.GetWeekDayString() << endl;
	//4. today가 yesterday보다 큰지 비교한다.
	ret = today.IsGreaterThan(yesterday);
	if (ret == true)
	{
		cout << "비교대상보다 큽니다." << endl;
	}
	//5. today에서 2일전으로 이동한다.
	previousDate = today.PreviousDate(2);
	cout << previousDate.GetYear() << "-"
		<< previousDate.GetMonth() << "-"
		<< previousDate.GetDay() << "-"
		<< previousDate.GetWeekDayString() << endl;
	//6. previousDate가 yesterday보다 작은지 비교한다.
	ret = previousDate.IsLesserThan(yesterday);
	if (ret == true)
	{
		cout << "비교대상보다 작습니다." << endl;
	}
	//7. tommorow를 구한다.
	tommorow = today.Tommorow();
	cout << tommorow.GetYear() << "-"
		<< tommorow.GetMonth() << "-"
		<< tommorow.GetDay() << "-"
		<< tommorow.GetWeekDayString() << endl;
	//8. today를 기준으로 해서 2일 후로 이동한다.
	next2Date = today.NextDate(2);
	cout << next2Date.GetYear() << "-"
		<< next2Date.GetMonth() << "-"
		<< next2Date.GetDay() << "-"
		<< next2Date.GetWeekDayString() << endl;
	//9. next2Date와 tommorow의 크기가 서로 같지 않은지 비교한다.
	ret = next2Date.IsNotEqual(tommorow);
	if (ret == true)
	{
		cout << "비교대상과 같지 않습니다." << endl;
	}
	//10. today를 기준으로 해서 1일후로 이동한다.
	next1Date = today.NextDate(1);
	cout << next1Date.GetYear() << "-"
		<< next1Date.GetMonth() << "-"
		<< next1Date.GetDay() << "-"
		<< next1Date.GetWeekDayString() << endl;
	//11. tommorow와 next1Date의 크기가 서로 같은지 비교한다.
	ret = tommorow.IsEqual(next1Date);
	if (ret == true)
	{
		cout << "비교대상과 같습니다." << endl;
	}
	//12. 형변환함수
	cout << static_cast<char*>(today) << endl;

	//13. 생일 문자열을 정수로 분해한다.
	Date birthday((char*)"20200807");
	cout << birthday.GetYear() << "-"
		<< birthday.GetMonth() << "-"
		<< birthday.GetDay() << "-"
		<< birthday.GetWeekDayString() << endl;
	//14. 생일 날짜를 생성한다.
	Date one(2020, AUG, 07);
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	//15. 복사생성자
	Date other(one);
	cout << other.GetYear() << "-"
		<< other.GetMonth() << "-"
		<< other.GetDay() << "-"
		<< other.GetWeekDayString() << endl;
	//16. tommorow와 next1Date의 크기가 서로 같은지 비교한다.
	if (tommorow == next1Date)
	{
		cout << "비교대상과 같습니다." << endl;
	}
	//17. tommorow와 next2Date의 크기가 서로 다른지 비교한다.
	if (tommorow != next2Date)
	{
		cout << "비교대상과 같지 않습니다." << endl;
	}
	//18. next2Date의 크기가 tommorow보다 큰지 비교한다.
	if (next2Date > tommorow)
	{
		cout << "비교대상보다 큽니다." << endl;
	}
	//19. next2Date의 크기가 tommorow보다 크거나 같은지 비교한다.
	if (next2Date >= tommorow)
	{
		cout << "비교대상보다 크거나 같습니다." << endl;
	}
	//20. next1Date의 크기가 tommorow보다 크거나 같은지 비교한다.
	if (next1Date >= tommorow)
	{
		cout << "비교대상보다 크거나 같습니다." << endl;
	}
	//21. tommorow가 next2Date보다 작은지 비교한다.
	if (tommorow < next2Date)
	{
		cout << "비교대상보다 작습니다." << endl;
	}
	//22. tommorow가 next2Date보다 작거나 같은지 비교한다.
	if(tommorow <= next2Date)
	{
		cout << "비교대상보다 작거나 같습니다." << endl;
	}
	//23. tommorow가 next1Date보다 작거나 같은지 비교한다.
	if (tommorow <= next1Date)
	{
		cout << "비교대상보다 작거나 같습니다." << endl;
	}
	//24. --one 전위
	--one;
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	//25. one-- 후위
	other = one--;
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	cout << other.GetYear() << "-"
		<< other.GetMonth() << "-"
		<< other.GetDay() << "-"
		<< other.GetWeekDayString() << endl;
	//26. ++one 전위
	++one;
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	//27. one++ 후위
	other = one++;
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	cout << other.GetYear() << "-"
		<< other.GetMonth() << "-"
		<< other.GetDay() << "-"
		<< other.GetWeekDayString() << endl;
	//28. operator-10
	other = one - 10;
	cout << other.GetYear() << "-"
		<< other.GetMonth() << "-"
		<< other.GetDay() << "-"
		<< other.GetWeekDayString() << endl;
	//29. operator+20
	other = one + 20;
	cout << other.GetYear() << "-"
		<< other.GetMonth() << "-"
		<< other.GetDay() << "-"
		<< other.GetWeekDayString() << endl;
	//30. Date를 없앤다.
	return 0;//~Date()
}
