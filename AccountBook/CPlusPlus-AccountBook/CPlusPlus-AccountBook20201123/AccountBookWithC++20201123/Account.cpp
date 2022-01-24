#include "Account.h"
#include "Date.h"

//����Ʈ ������
Account::Account()
	:briefs(""), remarks("")
{
	this->amount = 0;
	this->balance = 0;
}

//�Ű����� 5�� ������
Account::Account(Date date, string briefs, Currency amount, Currency balance, string remarks)
	:date(date), briefs(briefs), remarks(remarks)
{
	this->amount = amount;
	this->balance = balance;
}

//���������
Account::Account(const Account& source)
	:date(source.date), briefs(source.briefs), remarks(source.remarks)
{
	this->amount = source.amount;
	this->balance = source.balance;
}

//ġȯ������
Account& Account::operator=(const Account& source)
{
	this->date = source.date;
	this->briefs = source.briefs;
	this->amount = source.amount;
	this->balance = source.balance;
	this->remarks = source.remarks;

	return *this;
}

//�Ҹ���
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