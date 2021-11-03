#include "Date.h"
#include<time.h>
#include<stdio.h>//printf
#pragma warning(disable:4996)

//Create
void Create(Date* date)
{
	date->year = 1900;
	date->month = JAN;
	date->day = 1;
	date->weekDay = MON;

	date->Today = Today;
	date->Yesterday = Yesterday;
	date->IsGreaterThan = IsGreaterThan;
	date->PreviousDate = PreviousDate;
	date->IsLesserThan = IsLesserThan;
	date->Tommorow = Tommorow;
	date->NextDate = NextDate;
	date->IsNotEqual = IsNotEqual;
	date->IsEqual = IsEqual;
}

//Today
Date Today(Date* date)
{
	time_t timer;//�� ���� �Ⱓ�� ���� ���� ����
	struct tm* today;//��, ��, �� ���� �ð� �� ���� ���� ����
	
	Date today_;
	Create(&today_);

	time(&timer);//����ð��� ���ϴ�.
	today = localtime(&timer);// �� ���� �ð����� ��, ��, �� ������ �ð������� �ٲٴ�.

	today_.year = today->tm_year + 1900;//�� ����
	today_.month = (Month)(today->tm_mon + 1);//�� ����
	today_.day = today->tm_mday;// �� ����
	today_.weekDay = (WeekDay)(today->tm_wday);//���� ����

	Destroy(&today_);

	return today_;
}

//Yesterday
Date Yesterday(Date* date)
{
	struct tm yesterday = { 0, };
	Date yesterday_;

	Create(&yesterday_);

	yesterday.tm_year = date->year - 1900;
	yesterday.tm_mon = date->month - 1;
	yesterday.tm_mday = date->day - 1;//�����̹Ƿ� 1���ҽ�Ŵ

	mktime(&yesterday);//��¥ ������ �ٲٴ�

	yesterday_.year = yesterday.tm_year + 1900;
	yesterday_.month = (Month)(yesterday.tm_mon + 1);
	yesterday_.day = yesterday.tm_mday;
	yesterday_.weekDay = (WeekDay)(yesterday.tm_wday);

	Destroy(&yesterday_);

	return yesterday_;
}

//Tommorow
Date Tommorow(Date* date)
{
	struct tm tommorow = { 0, };
	Date tommorow_;

	Create(&tommorow_);

	tommorow.tm_year = date->year - 1900;
	tommorow.tm_mon = date->month - 1;
	tommorow.tm_mday = date->day + 1;//�����̹Ƿ� 1������Ŵ

	mktime(&tommorow);//��¥ ������ �ٲٴ�

	tommorow_.year = tommorow.tm_year + 1900;
	tommorow_.month = (Month)(tommorow.tm_mon + 1);
	tommorow_.day = tommorow.tm_mday;
	tommorow_.weekDay = (WeekDay)(tommorow.tm_wday);

	Destroy(&tommorow_);

	return tommorow_;
}

//PreviousDate
Date PreviousDate(Date* date, Long days)
{
	struct tm previousDate = { 0, };
	Date previousDate_;

	Create(&previousDate_);

	previousDate.tm_year = date->year - 1900;
	previousDate.tm_mon = date->month - 1;
	previousDate.tm_mday = date->day - days;//days��ŭ ���ҽ�Ŵ

	mktime(&previousDate);//��¥ ������ �ٲٴ�

	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = (Month)(previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = (WeekDay)(previousDate.tm_wday);

	Destroy(&previousDate_);

	return previousDate_;
}

//NextDate
Date NextDate(Date* date, Long days)
{
	struct tm nextDate = { 0, };
	Date nextDate_;

	Create(&nextDate_);

	nextDate.tm_year = date->year - 1900;
	nextDate.tm_mon = date->month - 1;
	nextDate.tm_mday = date->day + days;//days��ŭ ������Ŵ

	mktime(&nextDate);//��¥ ������ �ٲٴ�

	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = (Month)(nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = (WeekDay)(nextDate.tm_wday);

	Destroy(&nextDate_);

	return nextDate_;
}

//IsEqual
Boolean IsEqual(Date* date, Date* other)
{
	Boolean ret = FALSE;

	if (date->year == other->year && date->month == other->month && date->day == other->day)
	{
		ret = TRUE;
	}
	return ret;
}

//IsNotEqual
Boolean IsNotEqual(Date* date, Date* other)
{
	Boolean ret = FALSE;

	if (date->year != other->year || date->month != other->month || date->day != other->day)
	{
		ret = TRUE;
	}
	return ret;
}

//IsGreaterThan
Boolean IsGreaterThan(Date* date, Date* other)
{
	Boolean ret = FALSE;
	if (date->year > other->year)
	{
		ret = TRUE;
	}
	else if (date->year == other->year && date->month > other->month)
	{
		ret = TRUE;
	}
	else if (date->year == other->year && date->month == other->month && date->day > other->day)
	{
		ret = TRUE;
	}
	return ret;
}

//IsLesserThan
Boolean IsLesserThan(Date* date, Date* other)
{
	Boolean ret = FALSE;
	if (date->year < other->year)
	{
		ret = TRUE;
	}
	else if (date->year == other->year && date->month < other->month)
	{
		ret = TRUE;
	}
	else if (date->year == other->year && date->month == other->month && date->day < other->day)
	{
		ret = TRUE;
	}
	return ret;
}

//Destroy
void Destroy(Date* date)
{

}

//main
int main(int argc, char* argv[])
{
	Date date;
	Date today;
	Date yesterday;
	Boolean ret;
	Date previousDate;
	Date tommorow;
	Date next2Date;
	Date next1Date;

	//1. Date�� �����.
	Create(&date);
	Create(&today);
	Create(&yesterday);
	Create(&previousDate);
	Create(&tommorow);
	Create(&next2Date);
	Create(&next1Date);
	//2. today�� ���Ѵ�.
	today = date.Today(&date);
	printf("%4d-%2d-%2d\n", today.year, today.month, today.day);
	//3. ���� ��¥�� ���Ѵ�.
	yesterday = today.Yesterday(&today);
	printf("%4d-%2d-%2d\n", yesterday.year, yesterday.month, yesterday.day);
	//4. today�� yesterday���� ū�� ���Ѵ�.
	ret = today.IsGreaterThan(&today, &yesterday);
	if (ret == TRUE)
	{
		printf("�� ��󺸴� Ů�ϴ�.\n");
	}
	//5. today�� 2�������� �̵��Ѵ�.
	previousDate = today.PreviousDate(&today, 2);
	printf("%4d-%2d-%2d\n", previousDate.year, previousDate.month, previousDate.day);
	//6. previousDate�� yesterday���� ������ ���Ѵ�.
	ret = previousDate.IsLesserThan(&previousDate, &yesterday);
	if (ret == TRUE)
	{
		printf("�� ��󺸴� �۽��ϴ�.\n");
	}
	//7. tommorow�� ���Ѵ�.
	tommorow = today.Tommorow(&today);
	printf("%4d-%2d-%2d\n", tommorow.year, tommorow.month, tommorow.day);
	//8. today�� �������� �ؼ� 2���ķ� �̵��Ѵ�.
	next2Date = today.NextDate(&today, 2);
	printf("%4d-%2d-%2d\n", next2Date.year, next2Date.month, next2Date.day);
	//9. next2Date�� tommorow�� ũ�Ⱑ ���� ���� ������ ���Ѵ�.
	ret = next2Date.IsNotEqual(&next2Date, &tommorow);
	if (ret == TRUE)
	{
		printf("�� ���� ���� �ʽ��ϴ�.\n");
	}
	//10. today�� �������� �ؼ� 1�� �ķ� �̵��Ѵ�.
	next1Date = today.NextDate(&today, 1);
	printf("%4d-%2d-%2d\n", next1Date.year, next1Date.month, next1Date.day);
	//11. tommorow�� next1Date�� ũ�Ⱑ ���� ������ ���Ѵ�.
	ret = tommorow.IsEqual(&tommorow, &next1Date);
	if (ret == TRUE)
	{
		printf("�� ���� �����ϴ�.\n");
	}
	//12. Date�� ���ش�.
	Destroy(&next1Date);
	Destroy(&next2Date);
	Destroy(&tommorow);
	Destroy(&previousDate);
	Destroy(&yesterday);
	Destroy(&today);
	Destroy(&date);

	return 0;
}