#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
//STL(Standard Template Class Library)-C++ Class Library
#include<string>
#include "Array.h"
#include "Personal.h"
using namespace std;
typedef signed long int Long;

class AddressBook
{
public:
	//생성자
	AddressBook(Long capacity = 256);
	//복사생성자
	AddressBook(const AddressBook& source);
	//소멸자
	~AddressBook();

	Personal& AddressBook_GetAt(Long index);
	Long Record(string name, string address, string telelphoneNumber, string emailAddress);
	void Find(string name, Long* (*indexes), Long* count);
	Long Correct(Long index, string address, string telephoneNumber, string emailAddress);
	Long Erase(Long index);
	void Arrange();

	//치환연산자
	AddressBook& operator=(const AddressBook& source);

	Long GetCapacity() const;
	Long GetLength() const;

private:
	Array<Personal> personals;
	Long capacity;
	Long length;
};

inline Long AddressBook::GetCapacity() const
{
	return this->capacity;
}
inline Long AddressBook::GetLength() const
{
	return this->length;
}

int CompareNames(void* one, void* other);
int ComparePersonals(void* one, void* other);

#endif // !_ADDRESSBOOK_H

