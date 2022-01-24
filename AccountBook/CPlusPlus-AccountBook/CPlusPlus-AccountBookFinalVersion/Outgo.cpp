#include "Outgo.h"

//디폴트생성자
Outgo::Outgo()
{

}

//매개변수5개생성자
Outgo::Outgo(Date date, string briefs, Currency amount, Currency balance, string remarks)
	:Account(date, briefs, amount, balance, remarks)
{

}

//복사생성자
Outgo::Outgo(const Outgo& source)
	:Account(source)
{

}

//치환연산자
Outgo& Outgo::operator=(const Outgo& source)
{
	Account::operator=(source);

	return *this;
}

//소멸자
Outgo::~Outgo()
{

}