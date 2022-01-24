#include "AccountBook.h"
#include "Account.h"
#include "Income.h"
#include "Outgo.h"


//디폴트생성자
AccountBook::AccountBook(Long capacity)
	:accounts(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

//복사생성자
AccountBook::AccountBook(const AccountBook& source)
	:accounts(source.accounts)
{
	Account* account;
	Long i = 0;
	while (i < source.length)
	{
		account = const_cast<AccountBook&>(source).accounts.GetAt(i);
		if (dynamic_cast<Income*>(account))
		{
			this->accounts.Modify(i, new Income(*dynamic_cast<Income*>(account)));
		}
		else if (dynamic_cast<Outgo*>(account))
		{
			this->accounts.Modify(i, new Outgo(*dynamic_cast<Outgo*>(account)));
		}
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

//치환연산자
AccountBook& AccountBook::operator=(const AccountBook& source)
{
	//1. 기존 accountBook의 account할당해제
	Account* account;
	Long i = 0;
	while (i < this->length)
	{
		account = this->accounts.GetAt(i);
		if (account != 0)
		{
			delete account;
		}
		i++;
	}
	//2. Arrray 치환연산자 호출
	this->accounts = source.accounts;
	//3. source의 account와 같은 내용을 새로 힙에 할당하고 this->accounts에 주소 저장(변경)
	i = 0;
	while (i < source.length)
	{
		account = const_cast<AccountBook&>(source).accounts.GetAt(i);
		if (dynamic_cast<Income*>(account))
		{
			this->accounts.Modify(i, new Income(*dynamic_cast<Income*>(account)));
		}
		else if (dynamic_cast<Outgo*>(account))
		{
			this->accounts.Modify(i, new Outgo(*dynamic_cast<Outgo*>(account)));
		}
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

//Record
Long AccountBook::Record(Date date, string briefs, Currency amount, string remarks)
{
	//1. 날짜, 적요, 금액, 비고를 입력한다.
	//2. 이전의 account가 있으면
	Account* account;
	Currency balance = 0;
	if (this->length > 0)
	{
		//2.1 이전의 account의 주소를 구한다.
		account = this->accounts.GetAt(this->length - 1);
		//2.2 이전의 balance를 구한다.
		balance = account->GetBalance();
	}
	//3. 새로운 balance를 구해준다.
	balance += amount;
	//4. 금액이 양수이면
	if (amount >= 0)
	{
		account = new Income(date, briefs, amount, balance, remarks);
	}
	//5. 금액이 음수이면
	else
	{
		account = new Outgo(date, briefs, amount * (-1), balance, remarks);
	}
	//6. 사용량이 할당량보다 작으면
	Long index;
	if (this->length < this->capacity)
	{
		index = this->accounts.Store(this->length, account);
	}
	//7. 사용량이 할당량과 같거나 크면
	else
	{
		index = this->accounts.AppendFromRear(account);
		//7.1 할당량을 증가시킨다.
		this->capacity++;
	}
	//8. 사용량을 증가시킨다.
	this->length++;
	//9. index를 출력한다.
	return index;
	//10. 끝내다.
}

//Find(date)
void AccountBook::Find(Date date, Long* (*indexes), Long* count)
{
	this->accounts.LinearSearchDuplicate(&date, indexes, count, CompareDates);
}

//Find(briefs)
void AccountBook::Find(string briefs, Long* (*indexes), Long* count)
{
	this->accounts.LinearSearchDuplicate(&briefs, indexes, count, CompareBriefs);
}

//Find(date, briefs)
void AccountBook::Find(Date date, string briefs, Long* (*indexes), Long* count)
{
	*indexes = 0;
	*count = 0;
	//1. indexes와 briefs를 입력받는다.
	//2. date로 찾는다.
	Long(*dates) = 0;
	Long datesCount = 0;
	this->accounts.LinearSearchDuplicate(&date, &dates, &datesCount, CompareDates);
	//3. datesCount가 0보다 크면
	if (datesCount > 0)
	{
		//3.1 위치들 배열을 만든다.
		*indexes = new Long[datesCount];
	}
	//4. datesCount보다 작은동안 반복한다.
	Account* account;
	Long i = 0;
	Long j = 0;
	while (j < datesCount)
	{
		//4.1 date로 찾은 account를 구한다.
		account = this->accounts.GetAt(dates[j]);
		//4.2 briefs와 같으면
		if (account->GetBriefs().compare(briefs) == 0)
		{
			//4.2.1 위치들 배열에 위치를 저장한다.
			(*indexes)[i] = dates[j];
			//4.2.2 배열첨자를 센다.
			i++;
			//4.2.3 배열 사용량 개수를 센다.
			(*count)++;
		}
		j++;
	}
	//5. dates배열을 할당해제한다.
	if (dates != 0)
	{
		delete[] dates;
	}
	//6. indexes배열과 count를 출력한다.
	//7. 끝내다.
}

//Find(date, date)
void AccountBook::Find(Date one, Date other, Long* (*indexes), Long* count)
{
	//메모리절약 하지만 반복을 2번해야해서 시간낭비가 심함.
#if 0
	*indexes = 0;
	*count = 0;
	//1. 일자들을 입력받는다.
	//2. date가 other보다 작거나 같은동안 반복한다.
	Long i;//반복제어변수
	Long j = 0;// 배열첨지
	Long(*dates) = 0;
	Long datesCount = 0;
	Date date = one;
	while (date <= other)
	{
		//2.1 date로 찾는다.
		this->accounts.LinearSearchDuplicate(&date, &dates, &datesCount, CompareDates);
		//2.2 count의 개수를 센다.
		*(count) += datesCount;
		//2.3 할당해제한다.
		if (dates != 0)
		{
			delete[] dates;
		}
		//2.4 date를 1일 증가시킨다.
		date++;
	}
	//3. 개수가 0보다 크면
	if (*count > 0)
	{
		//3.1 위치들 배열을 만든다.
		*indexes = new Long[*count];
	}
	//4. date가 other보다 작은동안 반복한다.
	date = one;
	while (date <= other)
	{
		//4.1 date로 찾는다.
		this->accounts.LinearSearchDuplicate(&date, &dates, &datesCount, CompareDates);
		//4.2 datesCount보다 작은동안에 반복한다.
		i = 0;
		while (i < datesCount)
		{
			//4.2.1 indexes배열에 dates의 배열요소들을 저장한다.
			(*indexes)[j] = dates[i];
			j++;//배열첨자세기
			i++;//반복제어변수세기
		}
		//4.3 dates배열을 할당해제한다.
		if (dates != 0)
		{
			delete[] dates;
		}
		//4.4 date에 1일을 증가시킨다.
		date++;
	}
	//5. indexes배열과 count를 출력한다.
	//6. 끝내다.
#endif
	//메모리 낭비 심함. 하지만 반복을 한번만 해도되서 시간절약이 됨. indexes는 임시적으로 힙에
	//할당하는거라서 메모리낭비보다 시간을 절약하는게 더 중요함.
	*indexes = 0;
	*count = 0;
	//1. 일자들을 입력받는다.
	//2. indexes배열을 할당한다.
	if (this->length > 0)
	{
		*indexes = new Long[this->length];
	}
	//3. one이 other보다 작거나 같은 동안에 반복한다.
	Long i;//반복제어변수
	Long j = 0;//배열첨자
	Long(*dates) = 0;
	Long datesCount = 0;
	while (one <= other)
	{
		//3.1 one으로 찾는다.
		this->accounts.LinearSearchDuplicate(&one, &dates, &datesCount, CompareDates);
		//3.2 datesCount보다 작은동안에 반복한다.
		i = 0;
		while (i < datesCount)
		{
			//3.2.1 indexes배열에 dates배열의 배열요소들을 저장한다.
			(*indexes)[j] = dates[i];
			j++;//배열첨자세기
			(*count)++;//배열사용량개수세기
			i++;//반복제어변수세기
		}
		//3.3 dates배열을 할당해제한다.
		if (dates != 0)
		{
			delete[] dates;
		}
		//3.4 one에 1일을 증가시킨다.
		one++;
	}
	//4. indexes배열과 count를 출력한다.
	//5. 끝내다.
}

//Find(date, date, briefs)
void AccountBook::Find(Date one, Date other, string briefs, Long* (*indexes), Long* count)
{
	*indexes = 0;
	*count = 0;
	//1. 일자들과 적요를 입력받는다.
	//2. indexes배열을 할당한다.
	if (this->length > 0)
	{
		*indexes = new Long[this->length];
	}
	//3. one이 other보다 작거나 같은 동안에 반복한다.
	Account* account;
	Long i;//반복제어변수
	Long j = 0;//배열첨자
	Long(*dates) = 0;
	Long datesCount = 0;
	while (one <= other)
	{
		//3.1 one으로 찾는다.
		this->accounts.LinearSearchDuplicate(&one, &dates, &datesCount, CompareDates);
		//3.2 datesCount보다 작은동안에 반복한다.
		i = 0;
		while (i < datesCount)
		{
			//3.2.1 one으로 찾은 account를 구한다.
			account = this->accounts.GetAt(dates[i]);
			//3.2.2 briefs와 같으면
			if (account->GetBriefs().compare(briefs) == 0)
			{
				//3.2.2.1 indexes배열에 dates배열의 배열요소들을 저장한다.
				(*indexes)[j] = dates[i];
				j++;//배열첨자세기
				(*count)++;//배열사용량개수세기
			}
			i++;//반복제어변수세기
		}
		//3.3 dates배열을 할당해제한다.
		if (dates != 0)
		{
			delete[] dates;
		}
		//3.4 one에 1일을 증가시킨다.
		one++;
	}
	//4. indexes배열과 count를 출력한다.
	//5. 끝내다.
}

//Correct
Long AccountBook::Correct(Long index, Currency amount, string remarks)
{
	//1. index, amount, remarks를 입력받는다.
	//2. 고칠 account를 구한다.
	Account* account = this->accounts.GetAt(index);
	Account* newAccount = 0;
	Currency balance;
	//3. account가 수입이면
	if (dynamic_cast<Income*>(account))
	{
		//3.1 balance를 구한다.
		balance = account->GetBalance() + (amount - account->GetAmount());
		//3.2 Income을 힙에 할당한다.
		newAccount = new Income(account->GetDate(), account->GetBriefs(), amount, balance, remarks);
	}
	//4. account가 지출이면
	else if(dynamic_cast<Outgo*>(account))
	{
		//4.1 balance를 구한다.
		balance = account->GetBalance() + (account->GetAmount() + amount);
		//4.2 Outgo를 힙에 할당한다.
		newAccount = new Outgo(account->GetDate(), account->GetBriefs(), amount * (-1), balance, remarks);
	}
	//5. 기존의 account를 할당해제한다.
	if (account != 0)
	{
		delete[] account;
	}
	//6. newAccount를 저장한다.
	this->accounts.Modify(index, newAccount);
	//7. 수정된 account이후의 account들의 balance를 수정한다.
	Account* afterAccount;
	Long i = index + 1;
	while (i < this->length)
	{
		//7.1 account를 구한다.
		account = this->accounts.GetAt(i - 1);
		//7.2 afterAccount를 구한다.
		afterAccount = this->accounts.GetAt(i);
		//7.3 afterAccount가 수입이면
		if (dynamic_cast<Income*>(afterAccount))
		{
			//7.2.1 balance를 구한다.
			balance = account->GetBalance() + afterAccount->GetAmount();
			//7.2.2 Income을 힙에 할당한다.
			newAccount = new Income(afterAccount->GetDate(), afterAccount->GetBriefs(), afterAccount->GetAmount(), balance, afterAccount->GetRemarks());
		}
		//7.4 afterAccount가 지출이면
		else if (dynamic_cast<Outgo*>(afterAccount))
		{
			//7.3.1 balance를 구한다.
			balance = account->GetBalance() - afterAccount->GetAmount();
			//7.3.2 Outgo를 힙에 할당한다.
			newAccount = new Outgo(afterAccount->GetDate(), afterAccount->GetBriefs(), afterAccount->GetAmount(), balance, afterAccount->GetRemarks());
		}
		//7.5 기존의 afterAccount를 할당해제한다.
		if (afterAccount != 0)
		{
			delete[] afterAccount;
		}
		//7.6 newAccount를 저장한다.
		this->accounts.Modify(i, newAccount);
		i++;
	}
	//7. index를 출력한다.
	return index;
	//8. 끝내다.
}

//GetAt
Account* AccountBook::GetAt(Long index)
{
	return this->accounts.GetAt(index);
}

//Calculate
void AccountBook::Calculate(Date one, Date other, Currency* totalIncome,
	Currency* totalOutgo, Currency* totalBalance)
{
	//1. 계산할 기간을 입력받는다.
	//2. one이 other보다 작거나 같은동안에 반복한다.
	*totalIncome = 0;
	*totalOutgo = 0;
	*totalBalance = 0;
	Long(*indexes) = 0;
	Long count = 0;
	Long i;
	Account* account;
	while (one <= other)
	{
		//2.1 one날짜의 account들을 찾는다.
		this->accounts.LinearSearchDuplicate(&one, &indexes, &count, CompareDates);
		//2.2 count보다 작은동안에 반복한다.
		i = 0;
		while (i < count)
		{
			//2.2.1 account를 구한다.
			account = this->accounts.GetAt(indexes[i]);
			//2.2.2 수입이면
			if (dynamic_cast<Income*>(account))
			{
				//2.2.2.1 totalIncome을 구한다.
				(*totalIncome) += account->GetAmount();
			}
			//2.2.3 지출이면
			else if (dynamic_cast<Outgo*>(account))
			{
				//2.2.3.1 totalOutgo를 구한다.
				(*totalOutgo) += account->GetAmount();
			}
			i++;
		}
		//2.3 indexes배열을 할당해제한다.
		if (indexes != 0)
		{
			delete[] indexes;
		}
		one++;
	}
	//3. totalBalance를 구한다.
	*totalBalance = (*totalIncome) - (*totalOutgo);
	//4. totalIncome, totalOutgo, totalBalance를 출력한다.
	//5. 끝내다.
}

//소멸자
AccountBook::~AccountBook()
{
	Account* account;
	Long i = 0;
	while (i < this->length)
	{
		account = this->GetAt(i);
		if (account != 0)
		{
			delete account;
		}
		i++;
	}
}

#if 0
//메인테스트시나리오
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//가계부를 만든다.
	AccountBook accountBook;
	//1. 수입을 기재한다. c++은 const char*가 디폴트값이기 때문에 문자열을 사용하기 위해서는 char*로 형변환해줘야함.
	Long index = accountBook.Record(Date((char*)"20201101"), "용돈", 1000000, "형님");//Date입력시 Date의 생성자를 이용해서 매개변수를 입력함!!!
	Account* account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//2. 지출을 기재한다.
	index = accountBook.Record(Date(2020, NOV, 02), "식사", -9000, "혼자");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//3. 지출을 기재한다.
	index = accountBook.Record(Date((char*)"20201102"), "식사", -12000, "친구");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//4. 지하철을 기재한다.
	index = accountBook.Record(Date((char*)"20201102"), "교통비", -55000, "지하철");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//5. 지출을 기재한다.
	index = accountBook.Record(Date((char*)"20201102"), "회식", -30000, "친구");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//6. 수입을 기재한다.
	index = accountBook.Record(Date((char*)"20201102"), "캐쉬백", 7500, "체크카드");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//7. 지출을 기재한다.
	index = accountBook.Record(Date((char*)"20201102"), "통신비", -58000, "핸드폰");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//8. 지출을 기재한다.
	index = accountBook.Record(Date((char*)"20201102"), "쇼핑", -49000, "신발");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//9. 수입을 기재한다.
	index = accountBook.Record(Date((char*)"20201102"), "중고판매", 23000, "신발");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//10. 지출을 기재한다.
	index = accountBook.Record(Date((char*)"20201107"), "식사", -11000, "혼자");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//11. 지출을 기재한다.
	index = accountBook.Record(Date((char*)"20201108"), "식사", -13500, "동생");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//12. 지출을 기재한다.
	index = accountBook.Record(Date((char*)"20201110"), "식사", -6000, "혼자");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//13. 수입을 기재한다.
	index = accountBook.Record(Date((char*)"20201111"), "중고판매", 33000, "후라이팬");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//14. 날짜로 찾는다.
	cout << "날짜로 찾기" << endl;
	Long(*indexes);
	Long count;
	accountBook.Find(Date((char*)"20201102"), &indexes, &count);
	Long i = 0;
	while (i < count)
	{
		account= accountBook.GetAt(indexes[i]);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//15. 11/2 날짜로 찾은 것 중에 6번째의 금액을 수정한다.
	index = accountBook.Correct(indexes[6], -45000, "의류");
	account = accountBook.GetAt(index);
	cout << "수정된 account" << endl;
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	cout << "수정된 account 이후의 accounts들 balance바뀜" << endl;
	i = indexes[6] + 1;
	while (i < accountBook.GetLength())
	{
		account = accountBook.GetAt(i);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//할당해제
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//16. 가계부 마지막 account를 수정한다.
	index = accountBook.Correct(12, 35000, "후라이팬");
	account = accountBook.GetAt(index);
	cout << "수정된 마지막 account" << endl;
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	cout << "수정된 account 이후의 accounts들 balance바뀜" << endl;
	i = index + 1;
	while (i < accountBook.GetLength())
	{
		account = accountBook.GetAt(i);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//17. 적요("용돈")으로 찾는다.
	cout << "용돈으로 찾기" << endl;
	accountBook.Find("용돈", &indexes, &count);
	i = 0;
	while (i < count)
	{
		account = accountBook.GetAt(indexes[i]);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//18. "용돈"으로 찾은 것 중에 1번째의 금액을 수정한다.
	index = accountBook.Correct(indexes[0], 2000000, "형님");
	account = accountBook.GetAt(index);
	cout << "수정된 account" << endl;
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	cout << "수정된 account 이후의 accounts들 balance바뀜" << endl;
	i = indexes[0] + 1;
	while (i < accountBook.GetLength())
	{
		account = accountBook.GetAt(i);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//할당해제
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//19. 적요("식사")로 찾는다.
	cout << "식사로 찾기" << endl;
	accountBook.Find("식사", &indexes, &count);
	i = 0;
	while (i < count)
	{
		account = accountBook.GetAt(indexes[i]);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//20. "식사"로 찾은 것 중에 2번째의 금액을 수정한다.
	index = accountBook.Correct(indexes[1], -15000, "친구");
	account = accountBook.GetAt(index);
	cout << "수정된 account" << endl;
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	cout << "수정된 account 이후의 accounts들 balance바뀜" << endl;
	i = indexes[1] + 1;
	while (i < accountBook.GetLength())
	{
		account = accountBook.GetAt(i);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//할당해제
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//21. 날짜("20201102")와 적요("식사")로 찾는다.
	cout << "20201102와 식사로 찾기" << endl;
	accountBook.Find(Date((char*)"20201102"), "식사", &indexes, &count);
	i = 0;
	while (i < count)
	{
		account = accountBook.GetAt(indexes[i]);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//할당해제
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//22. 계산한다.
	Currency totalIncome;
	Currency totalOutgo;
	Currency totalBalance;
	accountBook.Calculate(Date((char*)"20201101"), Date((char*)"20201111"), &totalIncome,
		&totalOutgo, &totalBalance);
	cout << "총수입 총지출 총잔액 계산하기" << endl;
	cout << "총수입 : " << totalIncome << endl;
	cout << "총지출 : " << totalOutgo << endl;
	cout << "총잔액 : " << totalBalance << endl;
	//23. 일자들로 찾는다.
	cout << "일자들로 찾기" << endl;
	accountBook.Find(Date((char*)"20201107"), Date((char*)"20201111"), &indexes, &count);
	i = 0;
	while (i < count)
	{
		account = accountBook.GetAt(indexes[i]);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//할당해제
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//24.  일자들과 적요로 찾는다.
	cout << "일자들과 적요로 찾기" << endl;
	accountBook.Find(Date((char*)"20201102"), Date((char*)"20201111"), "중고판매", &indexes, &count);
	i = 0;
	while (i < count)
	{
		account = accountBook.GetAt(indexes[i]);
		cout << fixed;
		cout.precision(0);
		cout << account->GetDate() << ", "
			<< account->GetBriefs() << ", "
			<< account->GetAmount() << ", "
			<< account->GetBalance() << ", "
			<< account->GetRemarks() << endl;
		i++;
	}
	//할당해제
	if (indexes != 0)
	{
		delete[] indexes;
	}
	// 끝내다.
	return 0;
}
#endif


//함수포인터 정의
int CompareDates(void* one, void* other)
{
	Account** one_ = (Account**)one;
	Date* other_ = (Date*)other;

	int ret;
	if ((*one_)->GetDate().IsEqual(*other_) == true)
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}

int CompareBriefs(void* one, void* other)
{
	Account** one_ = (Account**)one;
	string* other_ = (string*)other;

	return((*one_)->GetBriefs().compare(*other_));
}

