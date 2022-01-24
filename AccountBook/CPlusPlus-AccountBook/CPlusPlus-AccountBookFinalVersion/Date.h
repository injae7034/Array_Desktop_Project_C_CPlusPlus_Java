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
public://����Լ�
	//������(Constrcutor)
	Date();//����Ʈ������
	Date(int year, Month month, int day);//Ư����¥ ������
	Date(char(*date));//���ڿ��� ���� ��¥�� �ٲٴ� ������
	Date(const Date& source);//���������
	~Date();//�Ҹ���(Destructor)
	operator char* ();//����ȯ�Լ�: ���� ��¥�� ���ڿ��� �ٲ�
	//�������� �Լ������ͷ� �޼����� ���´µ� Date date�� Today������ ���� �� �ѹ� ����.
	//�� �������� static�� �̿��ϸ� �� �ѹ��� ���� ���� date�̿���� �Լ�ȣ��� today�� ����������.
	static Date Today();//static�� ����ϸ� Date.Today()�� �ʿ���� �Լ�ȣ��� ��� ����.
	Date Yesterday();
	Date Tommorow();
	Date PreviousDate(int days);
	Date NextDate(int days);
	bool IsEqual(const Date& other);
	bool IsNotEqual(const Date& other);
	bool IsGreaterThan(const Date& other);
	bool IsLesserThan(const Date& other);
	//�������Լ�
	bool operator==(const Date& other);//IsEqual
	bool operator!=(const Date& other);//IsNotEqual
	bool operator>(const Date& other);//IsGreaterThan
	bool operator>=(const Date& other);//IsGreaterThan
	bool operator<(const Date& other);//IsLesserThan
	bool operator<=(const Date& other);//IsLesserThan
	Date& operator--();//Yesterday����
	Date operator--(int);//Yesterday����
	Date& operator++();//Tommorow����
	Date operator++(int);//Tommorow����
	Date operator-(int days);//PreviousDate
	Date operator+(int days);//NextDate
	Date& operator=(const Date& source);//ġȯ������
	char* GetWeekDayString();//���� ���ڿ��� ���ϴ��Լ�
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetWeekDay() const;

private://�����͸��
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

