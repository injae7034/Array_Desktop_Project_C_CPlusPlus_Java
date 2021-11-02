#include "Personal.h"
#pragma warning(disable:4996)

//디폴트 생성자
Personal::Personal()
	:name(""), address(""), telephoneNumber(""), emailAddress("")//생성자 클래스 콜론초기화
{

}

//매개변수를 갖는 생성자
Personal::Personal(string name, string address, string telephoneNumber, string emailAddress)
	: name(name), address(address), telephoneNumber(telephoneNumber), emailAddress(emailAddress)
{

}

//복사생성자
Personal::Personal(const Personal& source)
	:name(source.name), address(source.address), telephoneNumber(source.telephoneNumber),
	emailAddress(source.emailAddress)
{

}

//소멸자
Personal::~Personal()
{

}

bool Personal::IsEqual(const Personal& other)
{
	bool ret = false;
	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->emailAddress.compare(other.emailAddress) == 0)
	{
		ret = true;
	}
	return ret;
}

bool Personal::IsNotEqual(const Personal& other)
{
	bool ret = false;
	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->emailAddress.compare(other.emailAddress) != 0)
	{
		ret = true;
	}
	return ret;
}

//연산자함수
bool Personal::operator==(const Personal& other)
{
	bool ret = false;
	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->emailAddress.compare(other.emailAddress) == 0)
	{
		ret = true;
	}
	return ret;
}

bool Personal::operator!=(const Personal& other)
{
	bool ret = false;
	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->emailAddress.compare(other.emailAddress) != 0)
	{
		ret = true;
	}
	return ret;
}

//치환연산자
Personal& Personal::operator=(const Personal& source)
{
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}