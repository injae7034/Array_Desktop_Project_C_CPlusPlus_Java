#include "Personal.h"
#pragma warning(disable:4996)

//����Ʈ ������
Personal::Personal()
	:name(""), address(""), telephoneNumber(""), emailAddress("")//������ Ŭ���� �ݷ��ʱ�ȭ
{

}

//�Ű������� ���� ������
Personal::Personal(string name, string address, string telephoneNumber, string emailAddress)
	: name(name), address(address), telephoneNumber(telephoneNumber), emailAddress(emailAddress)
{

}

//���������
Personal::Personal(const Personal& source)
	:name(source.name), address(source.address), telephoneNumber(source.telephoneNumber),
	emailAddress(source.emailAddress)
{

}

//�Ҹ���
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

//�������Լ�
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

//ġȯ������
Personal& Personal::operator=(const Personal& source)
{
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}