#ifndef _OUTGO_H
#define _OUTGO_H

#include<string>
#include"Date.h"
#include"Account.h"

using namespace std;
class Outgo :public Account
{
public:
	Outgo();//디폴트생성자
	Outgo(Date date, string briefs, Currency amount, Currency balance, string remarks);//매개변수5개생성자
	Outgo(const Outgo& source);//복사생성자
	Outgo& operator=(const Outgo& source);//치환연산자
	virtual ~Outgo();//소멸자
};

#endif // !_OUTGO_H

