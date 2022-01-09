#ifndef _ACCOUNTBOOK_H
#define _ACCOUNTBOOK_H

#include<string>
#include "Date.h"
#include "Array.h"

using namespace std;
typedef double Currency;
typedef signed long int Long;

class Account;//전방선언 AccountBook.cpp에서 Account의 내용이나 함수를 이용할 경우 cpp에서 헤더파일 선언해줘야함.
class AccountBook
{
public:
	AccountBook(Long capacity = 256);//디폴트생성자
	AccountBook(const AccountBook& source);//복사생성자
	AccountBook& operator=(const AccountBook& source);//치환연산자
	~AccountBook();//소멸자
	Account* GetAt(Long index);//정의도 해서 테스트를 해야함 객체라서
	Long Record(Date date, string briefs, Currency amount, string remarks);
	void Find(Date date, Long* (*indexes), Long* count);
	void Find(string briefs, Long* (*indexes), Long* count);
	void Find(Date date, string briefs, Long* (*indexes), Long* count);
	void Find(Date one, Date other, Long* (*indexes), Long* count);
	void Find(Date one, Date other, string briefs, Long* (*indexes), Long* count);
	Long Correct(Long index, Currency amount, string remarks);
	void Calculate(Date one, Date other, Currency* totalIncome, Currency* totalOutgo, Currency* totalBalance);
	//인라인함수
	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<Account*> accounts;
	Long capacity;
	Long length;
};

//인라인함수정의
inline Long AccountBook::GetCapacity() const
{
	return this->capacity;
}
inline Long AccountBook::GetLength() const
{
	return this->length;
}

//함수포인터
int CompareDates(void* one, void* other);
int CompareBriefs(void* one, void* other);

#endif // !_ACCOUNTBOOK_H

