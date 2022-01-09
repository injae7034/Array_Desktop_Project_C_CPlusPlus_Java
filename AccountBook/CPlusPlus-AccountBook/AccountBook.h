#ifndef _ACCOUNTBOOK_H
#define _ACCOUNTBOOK_H

#include<string>
#include "Date.h"
#include "Array.h"

using namespace std;
typedef double Currency;
typedef signed long int Long;

class Account;//���漱�� AccountBook.cpp���� Account�� �����̳� �Լ��� �̿��� ��� cpp���� ������� �����������.
class AccountBook
{
public:
	AccountBook(Long capacity = 256);//����Ʈ������
	AccountBook(const AccountBook& source);//���������
	AccountBook& operator=(const AccountBook& source);//ġȯ������
	~AccountBook();//�Ҹ���
	Account* GetAt(Long index);//���ǵ� �ؼ� �׽�Ʈ�� �ؾ��� ��ü��
	Long Record(Date date, string briefs, Currency amount, string remarks);
	void Find(Date date, Long* (*indexes), Long* count);
	void Find(string briefs, Long* (*indexes), Long* count);
	void Find(Date date, string briefs, Long* (*indexes), Long* count);
	void Find(Date one, Date other, Long* (*indexes), Long* count);
	void Find(Date one, Date other, string briefs, Long* (*indexes), Long* count);
	Long Correct(Long index, Currency amount, string remarks);
	void Calculate(Date one, Date other, Currency* totalIncome, Currency* totalOutgo, Currency* totalBalance);
	//�ζ����Լ�
	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<Account*> accounts;
	Long capacity;
	Long length;
};

//�ζ����Լ�����
inline Long AccountBook::GetCapacity() const
{
	return this->capacity;
}
inline Long AccountBook::GetLength() const
{
	return this->length;
}

//�Լ�������
int CompareDates(void* one, void* other);
int CompareBriefs(void* one, void* other);

#endif // !_ACCOUNTBOOK_H

