#include "Personal.h"
#include "AddressBook.h"
#pragma warning(disable:4996)

//생성자
AddressBook::AddressBook(Long capacity)
	:personals(capacity)//생성자 클래스 콜론초기화
{
	//this->personals = Array<Personal>(capacity); Array라이브러리의 기본생성자함수 호출함.
	this->capacity = capacity;
	this->length = 0;
}

//복사생성자
AddressBook::AddressBook(const AddressBook& source)
	:personals(source.personals)// 생성자 클래스 콜론초기화
{
	//this->personals = source.personals Array라이브러리의 치환연산자(=)함수를 호출함.
	this->capacity = source.capacity;
	this->length = source.length;
}


//GetAt
Personal& AddressBook::GetAt(Long index)
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

//치환연산자
AddressBook& AddressBook::operator=(const AddressBook& source)
{
	this->personals = source.personals;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

//소멸자
AddressBook::~AddressBook()
{

}

//메인테스트시나리오
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. capacity에 6을 입력해 AddressBook을 만든다.
	AddressBook addressBook = AddressBook();
	//2. 홍길동, 서울 중구, 021766710, Hong을 기재한다.
	Long index;
	index = addressBook.Record("홍길동", "서울 중구", "021766710", "Hong");
	Personal personal;
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//3. 고길동, 서울 성동구, 029575976, Go를 기재한다.
	index = addressBook.Record("고길동", "서울 성동구", "0219575976", "Go");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//4. 홍길동, 인천 연수구, 0313267926, Hong2를 기재한다.
	index = addressBook.Record("홍길동", "인천 연수구", "0313267926", "Hong2");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//5. 홍길동을 찾는다.
	Long(*indexes);
	Long count;
	addressBook.Find("홍길동", &indexes, &count);
	index = 0;
	while (index < count)
	{
		personal = addressBook.GetAt(indexes[index]);
		cout << personal.GetName() << "-"
			<< personal.GetAddress() << "-"
			<< personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		index++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//6. 홍길동의 정보를 고친다.
	index = addressBook.Correct(2, "서울 광진구", "027971723", "Hong2");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//7. 주소록의 두번째를 지운다.
	index = addressBook.Erase(1);
	if (index == -1)
	{
		cout << "지워졌습니다." << endl;
	}
	//8. 최길동, 서울 성동구, 023517134, Choi를 기재한다.
	index = addressBook.Record("최길동", "서울 성동구", "023517134", "Choi");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//9. 정길동, 서울 종로구, 024366751, Jung을 기재한다.
	index = addressBook.Record("정길동", "서울 종로구", "024366751", "Jung");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "-"
		<< personal.GetAddress() << "-"
		<< personal.GetTelephoneNumber() << "-"
		<< personal.GetEmailAddress() << endl;
	//10. 주소록을 정리한다.
	cout << "------------------------정리하기-------------------------" << endl;
	addressBook.Arrange();
	index = 0;
	while (index < addressBook.GetLength())
	{
		personal = addressBook.GetAt(index);
		cout << personal.GetName() << "-"
			<< personal.GetAddress() << "-"
			<< personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		index++;
	}
	//11. 복사생성자
	cout << "------------------------복사생성자-------------------------" << endl;
	AddressBook other(addressBook);
	index = 0;
	while (index < other.GetLength())
	{
		personal = addressBook.GetAt(index);
		cout << personal.GetName() << "-"
			<< personal.GetAddress() << "-"
			<< personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		index++;
	}
	//12. 치환연산자
	cout << "------------------------치환연산자-------------------------" << endl;
	AddressBook theOther(6);
	theOther = other;
	index = 0;
	while (index < theOther.GetLength())
	{
		personal = addressBook.GetAt(index);
		cout << personal.GetName() << "-"
			<< personal.GetAddress() << "-"
			<< personal.GetTelephoneNumber() << "-"
			<< personal.GetEmailAddress() << endl;
		index++;
	}

	return 0;
}

//함수포인터
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
