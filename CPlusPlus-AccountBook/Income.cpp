#include "Income.h"

//����Ʈ������
Income::Income()
{

}

//�Ű�����5��������
Income::Income(Date date, string briefs, Currency amount, Currency balance, string remarks)
	:Account(date, briefs, amount, balance, remarks)
{

}

//���������
Income::Income(const Income& source)
	:Account(source)
{

}

//ġȯ������
Income& Income::operator=(const Income& source)
{
	Account::operator=(source);

	return *this;
}

//�Ҹ���
Income::~Income()
{

}