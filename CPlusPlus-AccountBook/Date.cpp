#include "Date.h"
#include<cstdio>//sprintf
#include<ctime>
#include<cstring>//strcpy
#pragma warning(disable:4996)

//������
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


//���������
Date::Date(const Date& source)
{
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;
}

//�Ҹ���
Date::~Date()
{
}

//����ȯ�Լ�
Date::operator char* ()
{
	static char buffer[9];

	sprintf(buffer, "%4d%02d%02d", this->year, this->month, this->day);
	return buffer;
}

//���� ���ڿ��� ���ϴ��Լ�
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

	mktime(&yesterday);//��¥ ������ �ٲٴ�.

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

	mktime(&tommorow);//��¥ ������ �ٲٴ�.

	tommorow_.year = tommorow.tm_year + 1900;//�� ����
	tommorow_.month = static_cast<Month>(tommorow.tm_mon + 1);//�� ����
	tommorow_.day = tommorow.tm_mday;//�� ����
	tommorow_.weekDay = static_cast<WeekDay>(tommorow.tm_wday);//���� ����

	return tommorow_;//~Date()
}

//PreviousDate
Date Date::PreviousDate(int days)
{
	struct tm previousDate = { 0, };
	Date previousDate_;//Date()

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;//days��ŭ ���ҽ�Ŵ.

	mktime(&previousDate);//��¥ ������ �ٲٴ�.

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

	mktime(&nextDate);//��¥ ������ �ٲٴ�.

	nextDate_.year = nextDate.tm_year + 1900;//�� ����
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);//�� ����
	nextDate_.day = nextDate.tm_mday;//�� ����
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);//���� ����

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

//�������Լ�
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

//operator--����
Date& Date::operator--()//Yesterday����
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

//operator--����
Date Date::operator--(int)//Yesterday����
{
	struct tm date = { 0, };
	Date date_(*this);//��������ڷ� �����͸������ �����ϸ� ��.

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

//operator++����
Date& Date::operator++()//Tommorow����
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

//operator++����
Date Date::operator++(int)//Tommorow����
{
	struct tm date = { 0, };
	Date date_(*this);//��������ڷ� �����͸������ �����ϸ� ��.

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
	previousDate.tm_mday = this->day - days;//days��ŭ ���ҽ�Ŵ.

	mktime(&previousDate);//��¥ ������ �ٲٴ�.

	previousDate_.year = previousDate.tm_year + 1900;//�� ����
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);//�� ����
	previousDate_.day = previousDate.tm_mday;//�� ����
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);//���� ����

	return previousDate_;//~Date()
}

//operator+
Date Date::operator+(int days)//NextDate
{
	struct tm nextDate = { 0, };
	Date nextDate_;//Date()

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;//days��ŭ ������Ŵ.

	mktime(&nextDate);//��¥ ������ �ٲٴ�.

	nextDate_.year = nextDate.tm_year + 1900;//�� ����
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);//�� ����
	nextDate_.day = nextDate.tm_mday;//�� ����
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);//���� ����

	return nextDate_;//~Date()
}

//ġȯ������
Date& Date::operator=(const Date& source)
{
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;

	return *this;
}

#if 0
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

	//2. ���� ��¥�� ���Ѵ�.
	today = Date::Today();//static�� ������Ͽ��� �����Ƿ� �Լ������� �޼��� ��ſ� �Լ�ȣ��� ����
	cout << today.GetYear() << "-"
		<< today.GetMonth() << "-"
		<< today.GetDay() << "-"
		<< today.GetWeekDayString() << endl;
	//3. ���� ��¥�� ���Ѵ�.
	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-"
		<< yesterday.GetMonth() << "-"
		<< yesterday.GetDay() << "-"
		<< yesterday.GetWeekDayString() << endl;
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
		<< previousDate.GetDay() << "-"
		<< previousDate.GetWeekDayString() << endl;
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
		<< tommorow.GetDay() << "-"
		<< tommorow.GetWeekDayString() << endl;
	//8. today�� �������� �ؼ� 2�� �ķ� �̵��Ѵ�.
	next2Date = today.NextDate(2);
	cout << next2Date.GetYear() << "-"
		<< next2Date.GetMonth() << "-"
		<< next2Date.GetDay() << "-"
		<< next2Date.GetWeekDayString() << endl;
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
		<< next1Date.GetDay() << "-"
		<< next1Date.GetWeekDayString() << endl;
	//11. tommorow�� next1Date�� ũ�Ⱑ ���� ������ ���Ѵ�.
	ret = tommorow.IsEqual(next1Date);
	if (ret == true)
	{
		cout << "�񱳴��� �����ϴ�." << endl;
	}
	//12. ����ȯ�Լ�
	cout << static_cast<char*>(today) << endl;

	//13. ���� ���ڿ��� ������ �����Ѵ�.
	Date birthday((char*)"20200807");
	cout << birthday.GetYear() << "-"
		<< birthday.GetMonth() << "-"
		<< birthday.GetDay() << "-"
		<< birthday.GetWeekDayString() << endl;
	//14. ���� ��¥�� �����Ѵ�.
	Date one(2020, AUG, 07);
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	//15. ���������
	Date other(one);
	cout << other.GetYear() << "-"
		<< other.GetMonth() << "-"
		<< other.GetDay() << "-"
		<< other.GetWeekDayString() << endl;
	//16. tommorow�� next1Date�� ũ�Ⱑ ���� ������ ���Ѵ�.
	if (tommorow == next1Date)
	{
		cout << "�񱳴��� �����ϴ�." << endl;
	}
	//17. tommorow�� next2Date�� ũ�Ⱑ ���� �ٸ��� ���Ѵ�.
	if (tommorow != next2Date)
	{
		cout << "�񱳴��� ���� �ʽ��ϴ�." << endl;
	}
	//18. next2Date�� ũ�Ⱑ tommorow���� ū�� ���Ѵ�.
	if (next2Date > tommorow)
	{
		cout << "�񱳴�󺸴� Ů�ϴ�." << endl;
	}
	//19. next2Date�� ũ�Ⱑ tommorow���� ũ�ų� ������ ���Ѵ�.
	if (next2Date >= tommorow)
	{
		cout << "�񱳴�󺸴� ũ�ų� �����ϴ�." << endl;
	}
	//20. next1Date�� ũ�Ⱑ tommorow���� ũ�ų� ������ ���Ѵ�.
	if (next1Date >= tommorow)
	{
		cout << "�񱳴�󺸴� ũ�ų� �����ϴ�." << endl;
	}
	//21. tommorow�� next2Date���� ������ ���Ѵ�.
	if (tommorow < next2Date)
	{
		cout << "�񱳴�󺸴� �۽��ϴ�." << endl;
	}
	//22. tommorow�� next2Date���� �۰ų� ������ ���Ѵ�.
	if(tommorow <= next2Date)
	{
		cout << "�񱳴�󺸴� �۰ų� �����ϴ�." << endl;
	}
	//23. tommorow�� next1Date���� �۰ų� ������ ���Ѵ�.
	if (tommorow <= next1Date)
	{
		cout << "�񱳴�󺸴� �۰ų� �����ϴ�." << endl;
	}
	//24. --one ����
	--one;
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	//25. one-- ����
	other = one--;
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	cout << other.GetYear() << "-"
		<< other.GetMonth() << "-"
		<< other.GetDay() << "-"
		<< other.GetWeekDayString() << endl;
	//26. ++one ����
	++one;
	cout << one.GetYear() << "-"
		<< one.GetMonth() << "-"
		<< one.GetDay() << "-"
		<< one.GetWeekDayString() << endl;
	//27. one++ ����
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
	//30. Date�� ���ش�.
	return 0;//~Date()
}
#endif
