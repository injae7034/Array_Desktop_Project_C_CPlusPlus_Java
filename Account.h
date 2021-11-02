#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include<string>
#include "Date.h"

using namespace std;
typedef double Currency;

class Account
{
public:
	Account();//디폴트생성자
	Account(Date date, string briefs, Currency amount, Currency balance, string remarks);//매개변수 5개 생성자
	Account(const Account& source);//복사생성자
	Account& operator=(const Account& source);//치환연산자
	virtual ~Account() = 0;//추상클래스 소멸자
	//논리함수
	bool IsEqual(const Account& other);
	bool IsNotEqual(const Account& other);
	//연산자함수
	bool operator==(const Account& other);
	bool operator!=(const Account& other);
	//인라인함수
	Date& GetDate() const;
	string& GetBriefs() const;
	Currency GetAmount() const;
	Currency GetBalance() const;
	string& GetRemarks() const;

protected://상속받은 subclass들이 superclass의 데이터멤버에 접근하기 위해서 protected로 해줘야함.
	Date date;
	string briefs;
	Currency amount;
	Currency balance;
	string remarks;
};

//인라인함수 정의
inline Date& Account::GetDate() const
{
	return const_cast<Date&>(this->date);
}
inline string& Account::GetBriefs() const
{
	return const_cast<string&>(this->briefs);
}
inline Currency Account::GetAmount() const
{
	return this->amount;
}
inline Currency Account::GetBalance() const
{
	return this->balance;
}
inline string& Account::GetRemarks() const
{
	return const_cast<string&>(this->remarks);
}

#endif // !_ACCOUNT_H

