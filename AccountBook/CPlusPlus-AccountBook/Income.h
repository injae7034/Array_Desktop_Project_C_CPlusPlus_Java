#ifndef _INCOME_H
#define _INCOME_H

#include<string>
#include"Date.h"
#include"Account.h"

using namespace std;
class Income :public Account
{
public:
	Income();//����Ʈ������
	Income(Date date, string briefs, Currency amount, Currency balance, string remarks);//�Ű�����5��������
	Income(const Income& source);//���������
	Income& operator=(const Income& source);//ġȯ������
	virtual ~Income();//�Ҹ���
};

#endif // !_INCOME_H
