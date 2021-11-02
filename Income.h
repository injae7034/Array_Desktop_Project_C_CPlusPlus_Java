#ifndef _INCOME_H
#define _INCOME_H

#include<string>
#include"Date.h"
#include"Account.h"

using namespace std;
class Income :public Account
{
public:
	Income();//디폴트생성자
	Income(Date date, string briefs, Currency amount, Currency balance, string remarks);//매객변수5개생성자
	Income(const Income& source);//복사생성자
	Income& operator=(const Income& source);//치환연산자
	virtual ~Income();//소멸자
};

#endif // !_INCOME_H
