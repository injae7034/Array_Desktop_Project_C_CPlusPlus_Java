#include "Date.h"
#include<ctime>
#pragma warning(disable:4996)

//������
Date::Date()
{
	this->year = 1900;
	this->month = JAN;
	this->day = 1;
	this->weekDay = MON;
}

//�Ҹ���
Date::~Date()
{
}

//Today
Date Date::Today()
{
	time_t timer;// �� ���� �Ⱓ�� ���庯�� ����(��Ǫ�͸� ���� �ð�����)
	struct tm* today;// ��, ��, �� ���� �ð� �� ���庯�� ����(����� ���� �ð�����)
	Date today_;//Date()

	time(&timer);//���� �ð��� ���ϴ�.
	today = localtime(&timer);// �� ���� �ð����� ��, ��, �� ������ �ð������� �ٲٴ�.

	today_.year = today->tm_year + 1900;//�� ����
	today_.month = static_cast<Month>(today->tm_mon + 1);//�� ����
	today_.day = today->tm_mday;//�� ����
	today_.weekDay = static_cast<WeekDay>(today->tm_wday);//���� ����

	return today_;//~Date()
}

//Yesterday
Date Date::Yesterday()
{
	struct tm yesterday = { 0, };
	Date yesterday_;//Date()

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;//�����̹Ƿ� 1���ҽ�Ŵ.

	mktime(&yesterday);//��¼ ������ �ٲٴ�.

	yesterday_.year = yesterday.tm_year + 1900;//�� ����
	yesterday_.month = static_cast<Month>(yesterday.tm_mon + 1);//�� ����
	yesterday_.day = yesterday.tm_mday;//�� ����
	yesterday_.weekDay = static_cast<WeekDay>(yesterday.tm_wday);//���� ����

	return yesterday_;//~Date()
}

//Tommorow
Date Date::Tommorow()
{
	struct tm tommorow = { 0, };
	Date tommorow_;//Date()

	tommorow.tm_year = this->year - 1900;
	tommorow.tm_mon = this->month - 1;
	tommorow.tm_mday = this->day + 1;//�����̹Ƿ� 1������Ŵ.

	mktime(&tommorow);//��¼ ������ �ٲٴ�.

	tommorow_.year = tommorow.tm_year + 1900;//�� ����
	tommorow_.month = static_cast<Month>(tommorow.tm_mon + 1);//�� ����
	tommorow_.day = tommorow.tm_mday;//�� ����
	tommorow_.weekDay = static_cast<WeekDay>(tommorow.tm_wday);//���� ����

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
	theDayBeforeYesterday.tm_mday = this->day - 2;//�������̹Ƿ� 2���ҽ�Ŵ.

	mktime(&theDayBeforeYesterday);//��¼ ������ �ٲٴ�.

	theDayBeforeYesterday_.year = theDayBeforeYesterday.tm_year + 1900;//�� ����
	theDayBeforeYesterday_.month = static_cast<Month>(theDayBeforeYesterday.tm_mon + 1);//�� ����
	theDayBeforeYesterday_.day = theDayBeforeYesterday.tm_mday;//�� ����
	theDayBeforeYesterday_.weekDay = static_cast<WeekDay>(theDayBeforeYesterday.tm_wday);//���� ����

	return theDayBeforeYesterday_;//~Date()
}

//TheDayAfterTomorrow
Date Date::TheDayAfterTommorrow()
{
	struct tm theDayAfterTommorow = { 0, };
	Date theDayAfterTommorow_;//Date()

	theDayAfterTommorow.tm_year = this->year - 1900;
	theDayAfterTommorow.tm_mon = this->month - 1;
	theDayAfterTommorow.tm_mday = this->day + 2;//���̹Ƿ� 2������Ŵ.

	mktime(&theDayAfterTommorow);//��¼ ������ �ٲٴ�.

	theDayAfterTommorow_.year = theDayAfterTommorow.tm_year + 1900;//�� ����
	theDayAfterTommorow_.month = static_cast<Month>(theDayAfterTommorow.tm_mon + 1);//�� ����
	theDayAfterTommorow_.day = theDayAfterTommorow.tm_mday;//�� ����
	theDayAfterTommorow_.weekDay = static_cast<WeekDay>(theDayAfterTommorow.tm_wday);//���� ����

	return theDayAfterTommorow_;//~Date()
}

//LastWeek
Date Date::LastWeek()
{
	struct tm lastWeek = { 0, };
	Date lastWeek_;//Date()

	lastWeek.tm_year = this->year - 1900;
	lastWeek.tm_mon = this->month - 1;
	lastWeek.tm_mday = this->day - 7;//7�ϸ�ŭ ���ҽ�Ŵ.

	mktime(&lastWeek);//��¼ ������ �ٲٴ�.

	lastWeek_.year = lastWeek.tm_year + 1900;//�� ����
	lastWeek_.month = static_cast<Month>(lastWeek.tm_mon + 1);//�� ����
	lastWeek_.day = lastWeek.tm_mday;//�� ����
	lastWeek_.weekDay = static_cast<WeekDay>(lastWeek.tm_wday);//���� ����

	return lastWeek_;//~Date()
}

//NextWeek
Date Date::NextWeek()
{
	struct tm nextWeek = { 0, };
	Date nextWeek_;//Date()

	nextWeek.tm_year = this->year - 1900;
	nextWeek.tm_mon = this->month - 1;
	nextWeek.tm_mday = this->day + 7;//7�ϸ�ŭ ������Ŵ.

	mktime(&nextWeek);//��¼ ������ �ٲٴ�.

	nextWeek_.year = nextWeek.tm_year + 1900;//�� ����
	nextWeek_.month = static_cast<Month>(nextWeek.tm_mon + 1);//�� ����
	nextWeek_.day = nextWeek.tm_mday;//�� ����
	nextWeek_.weekDay = static_cast<WeekDay>(nextWeek.tm_wday);//���� ����

	return nextWeek_;//~Date()
}

//LastMonth
Date Date::LastMonth()
{
	struct tm lastMonth = { 0, };
	Date lastMonth_;//Date()

	lastMonth.tm_year = this->year - 1900;
	lastMonth.tm_mon = this->month - 1;
	lastMonth.tm_mday = this->day - 28;//28�ϸ�ŭ ���ҽ�Ŵ.

	mktime(&lastMonth);//��¼ ������ �ٲٴ�.

	lastMonth_.year = lastMonth.tm_year + 1900;//�� ����
	lastMonth_.month = static_cast<Month>(lastMonth.tm_mon + 1);//�� ����
	lastMonth_.day = lastMonth.tm_mday;//�� ����
	lastMonth_.weekDay = static_cast<WeekDay>(lastMonth.tm_wday);//���� ����

	return lastMonth_;//~Date()
}

//NextMonth
Date Date::NextMonth()
{
	struct tm nextMonth = { 0, };
	Date nextMonth_;//Date()

	nextMonth.tm_year = this->year - 1900;
	nextMonth.tm_mon = this->month - 1;
	nextMonth.tm_mday = this->day + 28;//28�ϸ�ŭ ������Ŵ.

	mktime(&nextMonth);//��¥ ������ �ٲٴ�.

	nextMonth_.year = nextMonth.tm_year + 1900;//�� ����
	nextMonth_.month = static_cast<Month>(nextMonth.tm_mon + 1);//�� ����
	nextMonth_.day = nextMonth.tm_mday;//�� ����
	nextMonth_.weekDay = static_cast<WeekDay>(nextMonth.tm_wday);//���� ����

	return nextMonth_;//~Date()
}

//LastYear
Date Date::LastYear()
{
	struct tm lastYear = { 0, };
	Date lastYear_;//Date()

	lastYear.tm_year = this->year - 1900;
	lastYear.tm_mon = this->month - 1;
	lastYear.tm_mday = this->day - 365;//365�ϸ�ŭ ���ҽ�Ŵ.

	mktime(&lastYear);//��¼ ������ �ٲٴ�.

	lastYear_.year = lastYear.tm_year + 1900;//�� ����
	lastYear_.month = static_cast<Month>(lastYear.tm_mon + 1);//�� ����
	lastYear_.day = lastYear.tm_mday;//�� ����
	lastYear_.weekDay = static_cast<WeekDay>(lastYear.tm_wday);//���� ����

	return lastYear_;//~Date()
}

//NextYear
Date Date::NextYear()
{
	struct tm nextYear = { 0, };
	Date nextYear_;//Date()

	nextYear.tm_year = this->year - 1900;
	nextYear.tm_mon = this->month - 1;
	nextYear.tm_mday = this->day + 365;//365�ϸ�ŭ ������Ŵ.

	mktime(&nextYear);//��¼ ������ �ٲٴ�.

	nextYear_.year = nextYear.tm_year + 1900;//�� ����
	nextYear_.month = static_cast<Month>(nextYear.tm_mon + 1);//�� ����
	nextYear_.day = nextYear.tm_mday;//�� ����
	nextYear_.weekDay = static_cast<WeekDay>(nextYear.tm_wday);//���� ����

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
	previousDate.tm_mday = this->day - days;//days��ŭ ���ҽ�Ŵ.

	mktime(&previousDate);//��¼ ������ �ٲٴ�.

	previousDate_.year = previousDate.tm_year + 1900;//�� ����
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);//�� ����
	previousDate_.day = previousDate.tm_mday;//�� ����
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);//���� ����

	return previousDate_;//~Date()
}

//NextDate
Date Date::NextDate(int days)
{
	struct tm nextDate = { 0, };
	Date nextDate_;//Date()

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;//days��ŭ ������Ŵ.

	mktime(&nextDate);//��¼ ������ �ٲٴ�.

	nextDate_.year = nextDate.tm_year + 1900;//�� ����
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);//�� ����
	nextDate_.day = nextDate.tm_mday;//�� ����
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);//���� ����

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
	//1. Date�� �����.
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
	//2. ���� ��¥�� ���Ѵ�.
	today = Date::Today();//static�� ������Ͽ��� �����Ƿ� �Լ������� �޼��� ��ſ� �Լ�ȣ��� ����
	cout << today.GetYear() << "-"
		<< today.GetMonth() << "-"
		<< today.GetDay() << endl;
	//3. ���� ��¥�� ���Ѵ�.
	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-"
		<< yesterday.GetMonth() << "-"
		<< yesterday.GetDay() << endl;
	//4. today�� yesterday���� ū�� ���Ѵ�.
	ret = today.IsGreaterThan(yesterday);
	if (ret == true)
	{
		cout << "�񱳴�󺸴� Ů�ϴ�." << endl;
	}
	//5. today���� 2�������� �̵��Ѵ�.
	previousDate = today.PreviousDate(2);
	cout << previousDate.GetYear() << "-"
		<< previousDate.GetMonth() << "-"
		<< previousDate.GetDay() << endl;
	//6. previousDate�� yesterday���� ������ ���Ѵ�.
	ret = previousDate.IsLesserThan(yesterday);
	if (ret == true)
	{
		cout << "�񱳴�󺸴� �۽��ϴ�." << endl;
	}
	//7. tommorow�� ���Ѵ�.
	tommorow = today.Tommorow();
	cout << tommorow.GetYear() << "-"
		<< tommorow.GetMonth() << "-"
		<< tommorow.GetDay() << endl;
	//8. today�� �������� �ؼ� 2�� �ķ� �̵��Ѵ�.
	next2Date = today.NextDate(2);
	cout << next2Date.GetYear() << "-"
		<< next2Date.GetMonth() << "-"
		<< next2Date.GetDay() << endl;
	//9. next2Date�� tommorow�� ũ�Ⱑ ���� ���� ������ ���Ѵ�.
	ret = next2Date.IsNotEqual(tommorow);
	if (ret == true)
	{
		cout << "�񱳴��� ���� �ʽ��ϴ�." << endl;
	}
	//10. today�� �������� �ؼ� 1���ķ� �̵��Ѵ�.
	next1Date = today.NextDate(1);
	cout << next1Date.GetYear() << "-"
		<< next1Date.GetMonth() << "-"
		<< next1Date.GetDay() << endl;
	//11. tommorow�� next1Date�� ũ�Ⱑ ���� ������ ���Ѵ�.
	ret = tommorow.IsEqual(next1Date);
	if (ret == true)
	{
		cout << "�񱳴��� �����ϴ�." << endl;
	}

#if 0
	//12. ������ ��¥�� ���Ѵ�.
	theDayBeforeYesterday = today.TheDayBeforeYesterday();
	cout << theDayBeforeYesterday.GetYear() << "-"
		<< theDayBeforeYesterday.GetMonth() << "-"
		<< theDayBeforeYesterday.GetDay() << endl;
	//13. �� ��¥�� ���Ѵ�.
	theDayAfterTommorow = today.TheDayAfterTommorrow();
	cout << theDayAfterTommorow.GetYear() << "-"
		<< theDayAfterTommorow.GetMonth() << "-"
		<< theDayAfterTommorow.GetDay() << endl;
	//14. ���� �ָ� ���Ѵ�.
	lastWeek = today.LastWeek();
	cout << lastWeek.GetYear() << "-"
		<< lastWeek.GetMonth() << "-"
		<< lastWeek.GetDay() << endl;
	//15. ���� �ָ� ���Ѵ�.
	nextWeek = today.NextWeek();
	cout << nextWeek.GetYear() << "-"
		<< nextWeek.GetMonth() << "-"
		<< nextWeek.GetDay() << endl;
	//16. �Ѵ� ���� ���Ѵ�.
	lastMonth = today.LastMonth();
	cout << lastMonth.GetYear() << "-"
		<< lastMonth.GetMonth() << "-"
		<< lastMonth.GetDay() << endl;
	//17. �Ѵ� �ĸ� ���Ѵ�.
	nextMonth = today.NextMonth();
	cout << nextMonth.GetYear() << "-"
		<< nextMonth.GetMonth() << "-"
		<< nextMonth.GetDay() << endl;
	//18. 1�� ���� ���Ѵ�.
	lastYear = today.LastYear();
	cout << lastYear.GetYear() << "-"
		<< lastYear.GetMonth() << "-"
		<< lastYear.GetDay() << endl;
	//19. 1�� �ĸ� ���Ѵ�.
	nextYear = today.NextYear();
	cout << nextYear.GetYear() << "-"
		<< nextYear.GetMonth() << "-"
		<< nextYear.GetDay() << endl;
#endif

	//20. Date�� ���ش�.
	return 0;//~Date()
}
