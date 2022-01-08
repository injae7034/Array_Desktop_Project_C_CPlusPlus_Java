#ifndef _PERSONAL_H
#define _PERSONAL_H
//STL(Standard Template Class Library)-C++ Class Library
#include<string>
#include "Array.h"
using namespace std;

class Personal
{
public:
	//디폴트 생성자
	Personal();
	//매개변수를 갖는 생성자
	Personal(string name, string address, string telelphoneNumber, string emailAddress);
	//복사생성자
	Personal(const Personal& source);
	//소멸자
	~Personal();
	bool IsEqual(const Personal& other);
	bool IsNotEqual(const Personal& other);
	//연산자함수
	bool operator==(const Personal& other);
	bool operator!=(const Personal& other);
	//치환연산자
	Personal& operator=(const Personal& source);

	string& GetName() const;
	string& GetAddress() const;
	string& GetTelephoneNumber() const;
	string& GetEmailAddress() const;

private:
	string name;
	string address;
	string telephoneNumber;
	string emailAddress;
};

inline string& Personal::GetName() const
{
	return const_cast<string&>(this->name);
}
inline string& Personal::GetAddress() const
{
	return const_cast<string&>(this->address);
}
inline string& Personal::GetTelephoneNumber() const
{
	return const_cast<string&>(this->telephoneNumber);
}
inline string& Personal::GetEmailAddress() const
{
	return const_cast<string&>(this->emailAddress);
}

#endif // !_PERSONAL_H

