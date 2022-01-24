#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include<string>
#include "Date.h"

using namespace std;
typedef double Currency;

class Account
{
public:
	Account();//����Ʈ������
	Account(Date date, string briefs, Currency amount, Currency balance, string remarks);//�Ű����� 5�� ������
	Account(const Account& source);//���������
	Account& operator=(const Account& source);//ġȯ������
	virtual ~Account() = 0;//�߻�Ŭ���� �Ҹ���
	//���Լ�
	bool IsEqual(const Account& other);
	bool IsNotEqual(const Account& other);
	//�������Լ�
	bool operator==(const Account& other);
	bool operator!=(const Account& other);
	//�ζ����Լ�
	Date& GetDate() const;
	string& GetBriefs() const;
	Currency GetAmount() const;
	Currency GetBalance() const;
	string& GetRemarks() const;

protected://��ӹ��� subclass���� superclass�� �����͸���� �����ϱ� ���ؼ� protected�� �������.
	Date date;
	string briefs;
	Currency amount;
	Currency balance;
	string remarks;
};

//�ζ����Լ� ����
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

