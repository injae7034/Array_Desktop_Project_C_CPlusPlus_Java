#include "Account.h"
#include "Date.h"

//디폴트 생성자
Account::Account()
	:briefs(""), remarks("")
{
	this->amount = 0;
	this->balance = 0;
}

//매개변수 5개 생성자
Account::Account(Date date, string briefs, Currency amount, Currency balance, string remarks)
	:date(date), briefs(briefs), remarks(remarks)
{
	this->amount = amount;
	this->balance = balance;
}

//복사생성자
Account::Account(const Account& source)
	:date(source.date), briefs(source.briefs), remarks(source.remarks)
{
	this->amount = source.amount;
	this->balance = source.balance;
}

//치환연산자
Account& Account::operator=(const Account& source)
{
	this->date = source.date;
	this->briefs = source.briefs;
	this->amount = source.amount;
	this->balance = source.balance;
	this->remarks = source.remarks;

	return *this;
}

//소멸자
Account::~Account()
{

}

//IsEqual
bool Account::IsEqual(const Account& other)
{
	bool ret = false;
	if (this->date.IsEqual(other.date) == true && this->briefs.compare(other.briefs) == 0 &&
		this->amount == other.amount && this->balance == other.balance &&
		this->remarks.compare(other.remarks) == 0)
	{
		ret = true;
	}
	return ret;
}

//IsNotEqual
bool Account::IsNotEqual(const Account& other)
{
	bool ret = false;
	if (this->date.IsEqual(other.date) != true || this->briefs.compare(other.briefs) != 0 ||
		this->amount != other.amount || this->balance != other.balance ||
		this->remarks.compare(other.remarks) != 0)
	{
		ret = true;
	}
	return ret;
}

//operator==
bool Account::operator==(const Account& other)
{
	bool ret = false;
	if (this->date == other.date && this->briefs.compare(other.briefs) == 0 &&
		this->amount == other.amount && this->balance == other.balance &&
		this->remarks.compare(other.remarks) == 0)
	{
		ret = true;
	}
	return ret;
}

//operator!=
bool Account::operator!=(const Account& other)
{
	bool ret = false;
	if (this->date != other.date || this->briefs.compare(other.briefs) != 0 ||
		this->amount != other.amount || this->balance != other.balance ||
		this->remarks.compare(other.remarks) != 0)
	{
		ret = true;
	}
	return ret;
}