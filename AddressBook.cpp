#include "Personal.h"
#include "AddressBook.h"
#pragma warning(disable:4996)

//������
AddressBook::AddressBook(Long capacity)
	:personals(capacity)//������ Ŭ���� �ݷ��ʱ�ȭ
{
	//this->personals = Array<Personal>(capacity);
	this->capacity = capacity;
	this->length = 0;
}

//���������
AddressBook::AddressBook(const AddressBook& source)
	:personals(source.personals)// ������ Ŭ���� �ݷ��ʱ�ȭ
{
	this->capacity = source.capacity;
	this->length = source.length;
}


//GetAt
Personal& AddressBook::AddressBook_GetAt(Long index)
{
	return this->personals.GetAt(index);
}

//Record
Long AddressBook::Record(string name, string address, string telephoneNumber, string emailAddress)
{
	Long index;
	Personal personal(name, address, telephoneNumber, emailAddress);
	if (this->length < this->capacity)
	{
		index = this->personals.Store(this->length, personal);
	}
	else
	{
		index = this->personals.AppendFromRear(personal);
		this->capacity++;
	}
	this->length++;

	return index;
}

//Find
void AddressBook::Find(string name, Long* (*indexes), Long* count)
{
	this->personals.LinearSearchDuplicate(&name, indexes, count, CompareNames);
}

//Correct
Long AddressBook::Correct(Long index, string address, string telephoneNumber, string emailAddress)
{
	Personal personal = this->personals.GetAt(index);
	index = this->personals.Modify(index, Personal(personal.GetName(), address, telephoneNumber,
		emailAddress));

	return index;
}

//Erase
Long AddressBook::Erase(Long index)
{
	index = this->personals.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

//Arrange
void AddressBook::Arrange()
{
	this->personals.InsertionSort(ComparePersonals);
}

//ġȯ������
AddressBook& AddressBook::operator=(const AddressBook& source)
{
	this->personals = source.personals;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

//�Ҹ���
AddressBook::~AddressBook()
{
	//<����>AddressBook �Ҹ��ڰ� ȣ��Ǹ� �� ����鵵 ���� �� �Ҹ�ȴ�.
	//Array<Personal> personals�� AddressBook�� ����̱� ������ ���� �Ҹ�Ǵµ� 
	//�̶� Array���̺귯���� �Ҹ��ڰ� ȣ��Ǽ� Array�� �� �Ҵ������� �Ǳ� ������ 
	//AddressBook�� �Ҹ��ڿ��� �ƹ� ������ ��� �ȴ�.
}

#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. capacity�� 6�� �Է��� AddressBook�� �����.
	AddressBook addressBook(6);
	//2. ȫ�浿, ���� �߱�, 021766710, Hong�� �����Ѵ�.
	Long index;
	index = addressBook.Record("ȫ�浿", "���� �߱�", "021766710", "Hong");
	Personal personal;
	personal = addressBook.AddressBook_GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//3. ��浿, ���� ������, 029575976, Go�� �����Ѵ�.
	index = addressBook.Record("��浿", "���� ������", "0219575976", "Go");
	personal = addressBook.AddressBook_GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//4. ȫ�浿, ��õ ������, 0313267926, Hong2�� �����Ѵ�.
	index = addressBook.Record("ȫ�浿", "��õ ������", "0313267926", "Hong2");
	personal = addressBook.AddressBook_GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//5. ȫ�浿�� ã�´�.
	Long(*indexes);
	Long count;
	addressBook.Find("ȫ�浿", &indexes, &count);
	index = 0;
	while (index < count)
	{
		personal = addressBook.AddressBook_GetAt(indexes[index]);
		cout << personal.GetName() << "-"
			<< personal.GetAddress() << "-"
			<< personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		index++;
	}
	//6. ȫ�浿�� ������ ��ģ��.
	index = addressBook.Correct(2, "���� ������", "027971723", "Hong2");
	personal = addressBook.AddressBook_GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//7. �ּҷ��� �ι�°�� �����.
	index = addressBook.Erase(1);
	if (index == -1)
	{
		cout << "���������ϴ�." << endl;
	}
	//8. �ֱ浿, ���� ������, 023517134, Choi�� �����Ѵ�.
	index = addressBook.Record("�ֱ浿", "���� ������", "023517134", "Choi");
	personal = addressBook.AddressBook_GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//9. ���浿, ���� ���α�, 024366751, Jung�� �����Ѵ�.
	index = addressBook.Record("���浿", "���� ���α�", "024366751", "Jung");
	personal = addressBook.AddressBook_GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//10. �ּҷ��� �����Ѵ�.
	cout << "------------------------�����ϱ�-------------------------" << endl;
	addressBook.Arrange();
	index = 0;
	while (index < addressBook.GetLength())
	{
		personal = addressBook.AddressBook_GetAt(index);
		cout << personal.GetName() << "-"
			<< personal.GetAddress() << "-"
			<< personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		index++;
	}
	//11. ���������
	cout << "------------------------���������-------------------------" << endl;
	AddressBook other(addressBook);
	index = 0;
	while (index < other.GetLength())
	{
		personal = addressBook.AddressBook_GetAt(index);
		cout << personal.GetName() << "-"
			<< personal.GetAddress() << "-"
			<< personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		index++;
	}
	//12. ġȯ������
	cout << "------------------------ġȯ������-------------------------" << endl;
	AddressBook theOther(6);
	theOther = other;
	index = 0;
	while (index < theOther.GetLength())
	{
		personal = addressBook.AddressBook_GetAt(index);
		cout << personal.GetName() << "-"
			<< personal.GetAddress() << "-"
			<< personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		index++;
	}

	return 0;
}

//�Լ�������
int CompareNames(void* one, void* other)
{
	Personal* one_ = (Personal*)one;
	string* other_ = (string*)other;
	
	return (one_->GetName().compare(*other_));
}

int ComparePersonals(void* one, void* other)
{
	Personal* one_ = (Personal*)one;
	Personal* other_ = (Personal*)other;

	return (one_->GetName().compare(other_->GetName()));
}
