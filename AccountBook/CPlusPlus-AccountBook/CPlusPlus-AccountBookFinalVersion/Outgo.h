#ifndef _OUTGO_H
#define _OUTGO_H

#include<string>
#include"Date.h"
#include"Account.h"

using namespace std;
class Outgo :public Account
{
public:
	Outgo();//����Ʈ������
	Outgo(Date date, string briefs, Currency amount, Currency balance, string remarks);//�Ű�����5��������
	Outgo(const Outgo& source);//���������
	Outgo& operator=(const Outgo& source);//ġȯ������
	virtual ~Outgo();//�Ҹ���
};

#endif // !_OUTGO_H

