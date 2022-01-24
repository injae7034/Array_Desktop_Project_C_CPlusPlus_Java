#include "Income.h"

//디폴트생성자
Income::Income()
{

}

//매개변수5개생성자
Income::Income(Date date, string briefs, Currency amount, Currency balance, string remarks)
	:Account(date, briefs, amount, balance, remarks)
{

}

//복사생성자
Income::Income(const Income& source)
	:Account(source)
{

}

//치환연산자
Income& Income::operator=(const Income& source)
{
	Account::operator=(source);

	return *this;
}

//소멸자
Income::~Income()
{

}