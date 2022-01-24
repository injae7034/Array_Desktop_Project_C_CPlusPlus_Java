#include "AccountBook.h"
#include "Account.h"
#include "Income.h"
#include "Outgo.h"


//����Ʈ������
AccountBook::AccountBook(Long capacity)
	:accounts(capacity)
{
	this->capacity = capacity;
	this->length = 0;
}

//���������
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

//ġȯ������
AccountBook& AccountBook::operator=(const AccountBook& source)
{
	//1. ���� accountBook�� account�Ҵ�����
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
	//2. Arrray ġȯ������ ȣ��
	this->accounts = source.accounts;
	//3. source�� account�� ���� ������ ���� ���� �Ҵ��ϰ� this->accounts�� �ּ� ����(����)
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
	//1. ��¥, ����, �ݾ�, ��� �Է��Ѵ�.
	//2. ������ account�� ������
	Account* account;
	Currency balance = 0;
	if (this->length > 0)
	{
		//2.1 ������ account�� �ּҸ� ���Ѵ�.
		account = this->accounts.GetAt(this->length - 1);
		//2.2 ������ balance�� ���Ѵ�.
		balance = account->GetBalance();
	}
	//3. ���ο� balance�� �����ش�.
	balance += amount;
	//4. �ݾ��� ����̸�
	if (amount >= 0)
	{
		account = new Income(date, briefs, amount, balance, remarks);
	}
	//5. �ݾ��� �����̸�
	else
	{
		account = new Outgo(date, briefs, amount * (-1), balance, remarks);
	}
	//6. ��뷮�� �Ҵ緮���� ������
	Long index;
	if (this->length < this->capacity)
	{
		index = this->accounts.Store(this->length, account);
	}
	//7. ��뷮�� �Ҵ緮�� ���ų� ũ��
	else
	{
		index = this->accounts.AppendFromRear(account);
		//7.1 �Ҵ緮�� ������Ų��.
		this->capacity++;
	}
	//8. ��뷮�� ������Ų��.
	this->length++;
	//9. index�� ����Ѵ�.
	return index;
	//10. ������.
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
	//1. indexes�� briefs�� �Է¹޴´�.
	//2. date�� ã�´�.
	Long(*dates) = 0;
	Long datesCount = 0;
	this->accounts.LinearSearchDuplicate(&date, &dates, &datesCount, CompareDates);
	//3. datesCount�� 0���� ũ��
	if (datesCount > 0)
	{
		//3.1 ��ġ�� �迭�� �����.
		*indexes = new Long[datesCount];
	}
	//4. datesCount���� �������� �ݺ��Ѵ�.
	Account* account;
	Long i = 0;
	Long j = 0;
	while (j < datesCount)
	{
		//4.1 date�� ã�� account�� ���Ѵ�.
		account = this->accounts.GetAt(dates[j]);
		//4.2 briefs�� ������
		if (account->GetBriefs().compare(briefs) == 0)
		{
			//4.2.1 ��ġ�� �迭�� ��ġ�� �����Ѵ�.
			(*indexes)[i] = dates[j];
			//4.2.2 �迭÷�ڸ� ����.
			i++;
			//4.2.3 �迭 ��뷮 ������ ����.
			(*count)++;
		}
		j++;
	}
	//5. dates�迭�� �Ҵ������Ѵ�.
	if (dates != 0)
	{
		delete[] dates;
	}
	//6. indexes�迭�� count�� ����Ѵ�.
	//7. ������.
}

//Find(date, date)
void AccountBook::Find(Date one, Date other, Long* (*indexes), Long* count)
{
	//�޸����� ������ �ݺ��� 2���ؾ��ؼ� �ð����� ����.
#if 0
	*indexes = 0;
	*count = 0;
	//1. ���ڵ��� �Է¹޴´�.
	//2. date�� other���� �۰ų� �������� �ݺ��Ѵ�.
	Long i;//�ݺ������
	Long j = 0;// �迭÷��
	Long(*dates) = 0;
	Long datesCount = 0;
	Date date = one;
	while (date <= other)
	{
		//2.1 date�� ã�´�.
		this->accounts.LinearSearchDuplicate(&date, &dates, &datesCount, CompareDates);
		//2.2 count�� ������ ����.
		*(count) += datesCount;
		//2.3 �Ҵ������Ѵ�.
		if (dates != 0)
		{
			delete[] dates;
		}
		//2.4 date�� 1�� ������Ų��.
		date++;
	}
	//3. ������ 0���� ũ��
	if (*count > 0)
	{
		//3.1 ��ġ�� �迭�� �����.
		*indexes = new Long[*count];
	}
	//4. date�� other���� �������� �ݺ��Ѵ�.
	date = one;
	while (date <= other)
	{
		//4.1 date�� ã�´�.
		this->accounts.LinearSearchDuplicate(&date, &dates, &datesCount, CompareDates);
		//4.2 datesCount���� �������ȿ� �ݺ��Ѵ�.
		i = 0;
		while (i < datesCount)
		{
			//4.2.1 indexes�迭�� dates�� �迭��ҵ��� �����Ѵ�.
			(*indexes)[j] = dates[i];
			j++;//�迭÷�ڼ���
			i++;//�ݺ����������
		}
		//4.3 dates�迭�� �Ҵ������Ѵ�.
		if (dates != 0)
		{
			delete[] dates;
		}
		//4.4 date�� 1���� ������Ų��.
		date++;
	}
	//5. indexes�迭�� count�� ����Ѵ�.
	//6. ������.
#endif
	//�޸� ���� ����. ������ �ݺ��� �ѹ��� �ص��Ǽ� �ð������� ��. indexes�� �ӽ������� ����
	//�Ҵ��ϴ°Ŷ� �޸𸮳��񺸴� �ð��� �����ϴ°� �� �߿���.
	*indexes = 0;
	*count = 0;
	//1. ���ڵ��� �Է¹޴´�.
	//2. indexes�迭�� �Ҵ��Ѵ�.
	if (this->length > 0)
	{
		*indexes = new Long[this->length];
	}
	//3. one�� other���� �۰ų� ���� ���ȿ� �ݺ��Ѵ�.
	Long i;//�ݺ������
	Long j = 0;//�迭÷��
	Long(*dates) = 0;
	Long datesCount = 0;
	while (one <= other)
	{
		//3.1 one���� ã�´�.
		this->accounts.LinearSearchDuplicate(&one, &dates, &datesCount, CompareDates);
		//3.2 datesCount���� �������ȿ� �ݺ��Ѵ�.
		i = 0;
		while (i < datesCount)
		{
			//3.2.1 indexes�迭�� dates�迭�� �迭��ҵ��� �����Ѵ�.
			(*indexes)[j] = dates[i];
			j++;//�迭÷�ڼ���
			(*count)++;//�迭��뷮��������
			i++;//�ݺ����������
		}
		//3.3 dates�迭�� �Ҵ������Ѵ�.
		if (dates != 0)
		{
			delete[] dates;
		}
		//3.4 one�� 1���� ������Ų��.
		one++;
	}
	//4. indexes�迭�� count�� ����Ѵ�.
	//5. ������.
}

//Find(date, date, briefs)
void AccountBook::Find(Date one, Date other, string briefs, Long* (*indexes), Long* count)
{
	*indexes = 0;
	*count = 0;
	//1. ���ڵ�� ���並 �Է¹޴´�.
	//2. indexes�迭�� �Ҵ��Ѵ�.
	if (this->length > 0)
	{
		*indexes = new Long[this->length];
	}
	//3. one�� other���� �۰ų� ���� ���ȿ� �ݺ��Ѵ�.
	Account* account;
	Long i;//�ݺ������
	Long j = 0;//�迭÷��
	Long(*dates) = 0;
	Long datesCount = 0;
	while (one <= other)
	{
		//3.1 one���� ã�´�.
		this->accounts.LinearSearchDuplicate(&one, &dates, &datesCount, CompareDates);
		//3.2 datesCount���� �������ȿ� �ݺ��Ѵ�.
		i = 0;
		while (i < datesCount)
		{
			//3.2.1 one���� ã�� account�� ���Ѵ�.
			account = this->accounts.GetAt(dates[i]);
			//3.2.2 briefs�� ������
			if (account->GetBriefs().compare(briefs) == 0)
			{
				//3.2.2.1 indexes�迭�� dates�迭�� �迭��ҵ��� �����Ѵ�.
				(*indexes)[j] = dates[i];
				j++;//�迭÷�ڼ���
				(*count)++;//�迭��뷮��������
			}
			i++;//�ݺ����������
		}
		//3.3 dates�迭�� �Ҵ������Ѵ�.
		if (dates != 0)
		{
			delete[] dates;
		}
		//3.4 one�� 1���� ������Ų��.
		one++;
	}
	//4. indexes�迭�� count�� ����Ѵ�.
	//5. ������.
}

//Correct
Long AccountBook::Correct(Long index, Currency amount, string remarks)
{
	//1. index, amount, remarks�� �Է¹޴´�.
	//2. ��ĥ account�� ���Ѵ�.
	Account* account = this->accounts.GetAt(index);
	Account* newAccount = 0;
	Currency balance;
	//3. account�� �����̸�
	if (dynamic_cast<Income*>(account))
	{
		//3.1 balance�� ���Ѵ�.
		balance = account->GetBalance() + (amount - account->GetAmount());
		//3.2 Income�� ���� �Ҵ��Ѵ�.
		newAccount = new Income(account->GetDate(), account->GetBriefs(), amount, balance, remarks);
	}
	//4. account�� �����̸�
	else if(dynamic_cast<Outgo*>(account))
	{
		//4.1 balance�� ���Ѵ�.
		balance = account->GetBalance() + (account->GetAmount() + amount);
		//4.2 Outgo�� ���� �Ҵ��Ѵ�.
		newAccount = new Outgo(account->GetDate(), account->GetBriefs(), amount * (-1), balance, remarks);
	}
	//5. ������ account�� �Ҵ������Ѵ�.
	if (account != 0)
	{
		delete[] account;
	}
	//6. newAccount�� �����Ѵ�.
	this->accounts.Modify(index, newAccount);
	//7. ������ account������ account���� balance�� �����Ѵ�.
	Account* afterAccount;
	Long i = index + 1;
	while (i < this->length)
	{
		//7.1 account�� ���Ѵ�.
		account = this->accounts.GetAt(i - 1);
		//7.2 afterAccount�� ���Ѵ�.
		afterAccount = this->accounts.GetAt(i);
		//7.3 afterAccount�� �����̸�
		if (dynamic_cast<Income*>(afterAccount))
		{
			//7.2.1 balance�� ���Ѵ�.
			balance = account->GetBalance() + afterAccount->GetAmount();
			//7.2.2 Income�� ���� �Ҵ��Ѵ�.
			newAccount = new Income(afterAccount->GetDate(), afterAccount->GetBriefs(), afterAccount->GetAmount(), balance, afterAccount->GetRemarks());
		}
		//7.4 afterAccount�� �����̸�
		else if (dynamic_cast<Outgo*>(afterAccount))
		{
			//7.3.1 balance�� ���Ѵ�.
			balance = account->GetBalance() - afterAccount->GetAmount();
			//7.3.2 Outgo�� ���� �Ҵ��Ѵ�.
			newAccount = new Outgo(afterAccount->GetDate(), afterAccount->GetBriefs(), afterAccount->GetAmount(), balance, afterAccount->GetRemarks());
		}
		//7.5 ������ afterAccount�� �Ҵ������Ѵ�.
		if (afterAccount != 0)
		{
			delete[] afterAccount;
		}
		//7.6 newAccount�� �����Ѵ�.
		this->accounts.Modify(i, newAccount);
		i++;
	}
	//7. index�� ����Ѵ�.
	return index;
	//8. ������.
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
	//1. ����� �Ⱓ�� �Է¹޴´�.
	//2. one�� other���� �۰ų� �������ȿ� �ݺ��Ѵ�.
	*totalIncome = 0;
	*totalOutgo = 0;
	*totalBalance = 0;
	Long(*indexes) = 0;
	Long count = 0;
	Long i;
	Account* account;
	while (one <= other)
	{
		//2.1 one��¥�� account���� ã�´�.
		this->accounts.LinearSearchDuplicate(&one, &indexes, &count, CompareDates);
		//2.2 count���� �������ȿ� �ݺ��Ѵ�.
		i = 0;
		while (i < count)
		{
			//2.2.1 account�� ���Ѵ�.
			account = this->accounts.GetAt(indexes[i]);
			//2.2.2 �����̸�
			if (dynamic_cast<Income*>(account))
			{
				//2.2.2.1 totalIncome�� ���Ѵ�.
				(*totalIncome) += account->GetAmount();
			}
			//2.2.3 �����̸�
			else if (dynamic_cast<Outgo*>(account))
			{
				//2.2.3.1 totalOutgo�� ���Ѵ�.
				(*totalOutgo) += account->GetAmount();
			}
			i++;
		}
		//2.3 indexes�迭�� �Ҵ������Ѵ�.
		if (indexes != 0)
		{
			delete[] indexes;
		}
		one++;
	}
	//3. totalBalance�� ���Ѵ�.
	*totalBalance = (*totalIncome) - (*totalOutgo);
	//4. totalIncome, totalOutgo, totalBalance�� ����Ѵ�.
	//5. ������.
}

//�Ҹ���
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
//�����׽�Ʈ�ó�����
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//����θ� �����.
	AccountBook accountBook;
	//1. ������ �����Ѵ�. c++�� const char*�� ����Ʈ���̱� ������ ���ڿ��� ����ϱ� ���ؼ��� char*�� ����ȯ�������.
	Long index = accountBook.Record(Date((char*)"20201101"), "�뵷", 1000000, "����");//Date�Է½� Date�� �����ڸ� �̿��ؼ� �Ű������� �Է���!!!
	Account* account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//2. ������ �����Ѵ�.
	index = accountBook.Record(Date(2020, NOV, 02), "�Ļ�", -9000, "ȥ��");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//3. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201102"), "�Ļ�", -12000, "ģ��");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//4. ����ö�� �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201102"), "�����", -55000, "����ö");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//5. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201102"), "ȸ��", -30000, "ģ��");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//6. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201102"), "ĳ����", 7500, "üũī��");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//7. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201102"), "��ź�", -58000, "�ڵ���");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//8. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201102"), "����", -49000, "�Ź�");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//9. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201102"), "�߰��Ǹ�", 23000, "�Ź�");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//10. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201107"), "�Ļ�", -11000, "ȥ��");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//11. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201108"), "�Ļ�", -13500, "����");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//12. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201110"), "�Ļ�", -6000, "ȥ��");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//13. ������ �����Ѵ�.
	index = accountBook.Record(Date((char*)"20201111"), "�߰��Ǹ�", 33000, "�Ķ�����");
	account = accountBook.GetAt(index);
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	//14. ��¥�� ã�´�.
	cout << "��¥�� ã��" << endl;
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
	//15. 11/2 ��¥�� ã�� �� �߿� 6��°�� �ݾ��� �����Ѵ�.
	index = accountBook.Correct(indexes[6], -45000, "�Ƿ�");
	account = accountBook.GetAt(index);
	cout << "������ account" << endl;
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	cout << "������ account ������ accounts�� balance�ٲ�" << endl;
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
	//�Ҵ�����
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//16. ����� ������ account�� �����Ѵ�.
	index = accountBook.Correct(12, 35000, "�Ķ�����");
	account = accountBook.GetAt(index);
	cout << "������ ������ account" << endl;
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	cout << "������ account ������ accounts�� balance�ٲ�" << endl;
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
	//17. ����("�뵷")���� ã�´�.
	cout << "�뵷���� ã��" << endl;
	accountBook.Find("�뵷", &indexes, &count);
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
	//18. "�뵷"���� ã�� �� �߿� 1��°�� �ݾ��� �����Ѵ�.
	index = accountBook.Correct(indexes[0], 2000000, "����");
	account = accountBook.GetAt(index);
	cout << "������ account" << endl;
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	cout << "������ account ������ accounts�� balance�ٲ�" << endl;
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
	//�Ҵ�����
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//19. ����("�Ļ�")�� ã�´�.
	cout << "�Ļ�� ã��" << endl;
	accountBook.Find("�Ļ�", &indexes, &count);
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
	//20. "�Ļ�"�� ã�� �� �߿� 2��°�� �ݾ��� �����Ѵ�.
	index = accountBook.Correct(indexes[1], -15000, "ģ��");
	account = accountBook.GetAt(index);
	cout << "������ account" << endl;
	cout << fixed;
	cout.precision(0);
	cout << account->GetDate() << ", "
		<< account->GetBriefs() << ", "
		<< account->GetAmount() << ", "
		<< account->GetBalance() << ", "
		<< account->GetRemarks() << endl;
	cout << "������ account ������ accounts�� balance�ٲ�" << endl;
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
	//�Ҵ�����
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//21. ��¥("20201102")�� ����("�Ļ�")�� ã�´�.
	cout << "20201102�� �Ļ�� ã��" << endl;
	accountBook.Find(Date((char*)"20201102"), "�Ļ�", &indexes, &count);
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
	//�Ҵ�����
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//22. ����Ѵ�.
	Currency totalIncome;
	Currency totalOutgo;
	Currency totalBalance;
	accountBook.Calculate(Date((char*)"20201101"), Date((char*)"20201111"), &totalIncome,
		&totalOutgo, &totalBalance);
	cout << "�Ѽ��� ������ ���ܾ� ����ϱ�" << endl;
	cout << "�Ѽ��� : " << totalIncome << endl;
	cout << "������ : " << totalOutgo << endl;
	cout << "���ܾ� : " << totalBalance << endl;
	//23. ���ڵ�� ã�´�.
	cout << "���ڵ�� ã��" << endl;
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
	//�Ҵ�����
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//24.  ���ڵ�� ����� ã�´�.
	cout << "���ڵ�� ����� ã��" << endl;
	accountBook.Find(Date((char*)"20201102"), Date((char*)"20201111"), "�߰��Ǹ�", &indexes, &count);
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
	//�Ҵ�����
	if (indexes != 0)
	{
		delete[] indexes;
	}
	// ������.
	return 0;
}
#endif


//�Լ������� ����
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

