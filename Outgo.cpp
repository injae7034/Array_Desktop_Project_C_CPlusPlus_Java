#include "Outgo.h"

//����Ʈ������
Outgo::Outgo()
{

}

//�Ű�����5��������
Outgo::Outgo(Date date, string briefs, Currency amount, Currency balance, string remarks)
	:Account(date, briefs, amount, balance, remarks)
{

}

//���������
Outgo::Outgo(const Outgo& source)
	:Account(source)
{

}

//ġȯ������
Outgo& Outgo::operator=(const Outgo& source)
{
	Account::operator=(source);

	return *this;
}

//�Ҹ���
Outgo::~Outgo()
{

}