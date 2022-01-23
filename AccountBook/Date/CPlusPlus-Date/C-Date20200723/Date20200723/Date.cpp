#include "Date.h"
#include<ctime>
#pragma warning(disable:4996)

//생성자
Date::Date()
{
	this->year = 1900;
	this->month = JAN;
	this->day = 1;
	this->weekDay = MON;
}

//소멸자
Date::~Date()
{
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

	mktime(&yesterday);//날쩌 형식을 바꾸다.

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

	mktime(&tommorow);//날쩌 형식을 바꾸다.

	tommorow_.year = tommorow.tm_year + 1900;//년 설정
	tommorow_.month = static_cast<Month>(tommorow.tm_mon + 1);//월 설정
	tommorow_.day = tommorow.tm_mday;//일 설정
	tommorow_.weekDay = static_cast<WeekDay>(tommorow.tm_wday);//요일 설정

	return tommorow_;//~Date()
}

#if 0
//TheDayBeforeYesterday
Date Date::TheDayBeforeYesterday()
{
	struct tm theDayBeforeYesterday = { 0, };
	Date theDayBeforeYesterday_;//Date()

	theDayBeforeYesterday.tm_year = this->year - 1900;
	theDayBeforeYesterday.tm_mon = this->month - 1;
	theDayBeforeYesterday.tm_mday = this->day - 2;//그제께이므로 2감소시킴.

	mktime(&theDayBeforeYesterday);//날쩌 형식을 바꾸다.

	theDayBeforeYesterday_.year = theDayBeforeYesterday.tm_year + 1900;//년 설정
	theDayBeforeYesterday_.month = static_cast<Month>(theDayBeforeYesterday.tm_mon + 1);//월 설정
	theDayBeforeYesterday_.day = theDayBeforeYesterday.tm_mday;//일 설정
	theDayBeforeYesterday_.weekDay = static_cast<WeekDay>(theDayBeforeYesterday.tm_wday);//요일 설정

	return theDayBeforeYesterday_;//~Date()
}

//TheDayAfterTomorrow
Date Date::TheDayAfterTommorrow()
{
	struct tm theDayAfterTommorow = { 0, };
	Date theDayAfterTommorow_;//Date()

	theDayAfterTommorow.tm_year = this->year - 1900;
	theDayAfterTommorow.tm_mon = this->month - 1;
	theDayAfterTommorow.tm_mday = this->day + 2;//모레이므로 2증가시킴.

	mktime(&theDayAfterTommorow);//날쩌 형식을 바꾸다.

	theDayAfterTommorow_.year = theDayAfterTommorow.tm_year + 1900;//년 설정
	theDayAfterTommorow_.month = static_cast<Month>(theDayAfterTommorow.tm_mon + 1);//월 설정
	theDayAfterTommorow_.day = theDayAfterTommorow.tm_mday;//일 설정
	theDayAfterTommorow_.weekDay = static_cast<WeekDay>(theDayAfterTommorow.tm_wday);//요일 설정

	return theDayAfterTommorow_;//~Date()
}

//LastWeek
Date Date::LastWeek()
{
	struct tm lastWeek = { 0, };
	Date lastWeek_;//Date()

	lastWeek.tm_year = this->year - 1900;
	lastWeek.tm_mon = this->month - 1;
	lastWeek.tm_mday = this->day - 7;//7일만큼 감소시킴.

	mktime(&lastWeek);//날쩌 형식을 바꾸다.

	lastWeek_.year = lastWeek.tm_year + 1900;//년 설정
	lastWeek_.month = static_cast<Month>(lastWeek.tm_mon + 1);//월 설정
	lastWeek_.day = lastWeek.tm_mday;//일 설정
	lastWeek_.weekDay = static_cast<WeekDay>(lastWeek.tm_wday);//요일 설정

	return lastWeek_;//~Date()
}

//NextWeek
Date Date::NextWeek()
{
	struct tm nextWeek = { 0, };
	Date nextWeek_;//Date()

	nextWeek.tm_year = this->year - 1900;
	nextWeek.tm_mon = this->month - 1;
	nextWeek.tm_mday = this->day + 7;//7일만큼 증가시킴.

	mktime(&nextWeek);//날쩌 형식을 바꾸다.

	nextWeek_.year = nextWeek.tm_year + 1900;//년 설정
	nextWeek_.month = static_cast<Month>(nextWeek.tm_mon + 1);//월 설정
	nextWeek_.day = nextWeek.tm_mday;//일 설정
	nextWeek_.weekDay = static_cast<WeekDay>(nextWeek.tm_wday);//요일 설정

	return nextWeek_;//~Date()
}

//LastMonth
Date Date::LastMonth()
{
	struct tm lastMonth = { 0, };
	Date lastMonth_;//Date()

	lastMonth.tm_year = this->year - 1900;
	lastMonth.tm_mon = this->month - 1;
	lastMonth.tm_mday = this->day - 28;//28일만큼 감소시킴.

	mktime(&lastMonth);//날쩌 형식을 바꾸다.

	lastMonth_.year = lastMonth.tm_year + 1900;//년 설정
	lastMonth_.month = static_cast<Month>(lastMonth.tm_mon + 1);//월 설정
	lastMonth_.day = lastMonth.tm_mday;//일 설정
	lastMonth_.weekDay = static_cast<WeekDay>(lastMonth.tm_wday);//요일 설정

	return lastMonth_;//~Date()
}

//NextMonth
Date Date::NextMonth()
{
	struct tm nextMonth = { 0, };
	Date nextMonth_;//Date()

	nextMonth.tm_year = this->year - 1900;
	nextMonth.tm_mon = this->month - 1;
	nextMonth.tm_mday = this->day + 28;//28일만큼 증가시킴.

	mktime(&nextMonth);//날짜 형식을 바꾸다.

	nextMonth_.year = nextMonth.tm_year + 1900;//년 설정
	nextMonth_.month = static_cast<Month>(nextMonth.tm_mon + 1);//월 설정
	nextMonth_.day = nextMonth.tm_mday;//일 설정
	nextMonth_.weekDay = static_cast<WeekDay>(nextMonth.tm_wday);//요일 설정

	return nextMonth_;//~Date()
}

//LastYear
Date Date::LastYear()
{
	struct tm lastYear = { 0, };
	Date lastYear_;//Date()

	lastYear.tm_year = this->year - 1900;
	lastYear.tm_mon = this->month - 1;
	lastYear.tm_mday = this->day - 365;//365일만큼 감소시킴.

	mktime(&lastYear);//날쩌 형식을 바꾸다.

	lastYear_.year = lastYear.tm_year + 1900;//년 설정
	lastYear_.month = static_cast<Month>(lastYear.tm_mon + 1);//월 설정
	lastYear_.day = lastYear.tm_mday;//일 설정
	lastYear_.weekDay = static_cast<WeekDay>(lastYear.tm_wday);//요일 설정

	return lastYear_;//~Date()
}

//NextYear
Date Date::NextYear()
{
	struct tm nextYear = { 0, };
	Date nextYear_;//Date()

	nextYear.tm_year = this->year - 1900;
	nextYear.tm_mon = this->month - 1;
	nextYear.tm_mday = this->day + 365;//365일만큼 증가시킴.

	mktime(&nextYear);//날쩌 형식을 바꾸다.

	nextYear_.year = nextYear.tm_year + 1900;//년 설정
	nextYear_.month = static_cast<Month>(nextYear.tm_mon + 1);//월 설정
	nextYear_.day = nextYear.tm_mday;//일 설정
	nextYear_.weekDay = static_cast<WeekDay>(nextYear.tm_wday);//요일 설정

	return nextYear_;//~Date()
}
#endif

//PreviousDate
Date Date::PreviousDate(int days)
{
	struct tm previousDate = { 0, };
	Date previousDate_;//Date()

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;//days만큼 감소시킴.

	mktime(&previousDate);//날쩌 형식을 바꾸다.

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

	mktime(&nextDate);//날쩌 형식을 바꾸다.

	nextDate_.year = nextDate.tm_year + 1900;//년 설정
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);//월 설정
	nextDate_.day = nextDate.tm_mday;//일 설정
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);//요일 설정

	return nextDate_;//~Date()
}

//IsEqual
bool Date::IsEqual(Date other)
{
	bool ret = false;
	if (this->year == other.year && this->month == other.month && this->day == other.day)
	{
		ret = true;
	}
	return ret;
}

//IsNotEqual
bool Date::IsNotEqual(Date other)
{
	bool ret = false;
	if (this->year != other.year || this->month != other.month || this->day != other.day)
	{
		ret = true;
	}
	return ret;
}

//IsGreaterThan
bool Date::IsGreaterThan(Date other)
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
bool Date::IsLesserThan(Date other)
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
	//Date theDayBeforeYesterday;//Date()
	//Date theDayAfterTommorow;//Date()
	//Date lastWeek;//Date()
	//Date nextWeek;//Date()
	//Date lastMonth;//Date()
	//Date nextMonth;//Date()
	//Date lastYear;//Date()
	//Date nextYear;//Date()
	//2. 오늘 날짜를 구한다.
	today = Date::Today();//static을 헤더파일에서 했으므로 함수포인터 메세지 대신에 함수호출로 가능
	cout << today.GetYear() << "-"
		<< today.GetMonth() << "-"
		<< today.GetDay() << endl;
	//3. 어제 날짜를 구한다.
	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-"
		<< yesterday.GetMonth() << "-"
		<< yesterday.GetDay() << endl;
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
		<< previousDate.GetDay() << endl;
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
		<< tommorow.GetDay() << endl;
	//8. today를 기준으로 해서 2일 후로 이동한다.
	next2Date = today.NextDate(2);
	cout << next2Date.GetYear() << "-"
		<< next2Date.GetMonth() << "-"
		<< next2Date.GetDay() << endl;
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
		<< next1Date.GetDay() << endl;
	//11. tommorow와 next1Date의 크기가 서로 같은지 비교한다.
	ret = tommorow.IsEqual(next1Date);
	if (ret == true)
	{
		cout << "비교대상과 같습니다." << endl;
	}

#if 0
	//12. 그저께 날짜를 구한다.
	theDayBeforeYesterday = today.TheDayBeforeYesterday();
	cout << theDayBeforeYesterday.GetYear() << "-"
		<< theDayBeforeYesterday.GetMonth() << "-"
		<< theDayBeforeYesterday.GetDay() << endl;
	//13. 모레 날짜를 구한다.
	theDayAfterTommorow = today.TheDayAfterTommorrow();
	cout << theDayAfterTommorow.GetYear() << "-"
		<< theDayAfterTommorow.GetMonth() << "-"
		<< theDayAfterTommorow.GetDay() << endl;
	//14. 지난 주를 구한다.
	lastWeek = today.LastWeek();
	cout << lastWeek.GetYear() << "-"
		<< lastWeek.GetMonth() << "-"
		<< lastWeek.GetDay() << endl;
	//15. 다음 주를 구한다.
	nextWeek = today.NextWeek();
	cout << nextWeek.GetYear() << "-"
		<< nextWeek.GetMonth() << "-"
		<< nextWeek.GetDay() << endl;
	//16. 한달 전을 구한다.
	lastMonth = today.LastMonth();
	cout << lastMonth.GetYear() << "-"
		<< lastMonth.GetMonth() << "-"
		<< lastMonth.GetDay() << endl;
	//17. 한달 후를 구한다.
	nextMonth = today.NextMonth();
	cout << nextMonth.GetYear() << "-"
		<< nextMonth.GetMonth() << "-"
		<< nextMonth.GetDay() << endl;
	//18. 1년 전을 구한다.
	lastYear = today.LastYear();
	cout << lastYear.GetYear() << "-"
		<< lastYear.GetMonth() << "-"
		<< lastYear.GetDay() << endl;
	//19. 1년 후를 구한다.
	nextYear = today.NextYear();
	cout << nextYear.GetYear() << "-"
		<< nextYear.GetMonth() << "-"
		<< nextYear.GetDay() << endl;
#endif

	//20. Date를 없앤다.
	return 0;//~Date()
}
