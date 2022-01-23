#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
#define MAX 20

typedef signed long int Long;

typedef struct _personal
{
    char name[11];
    char address[64];
    char telephoneNumber[12];
    char emailAddress[32];
}Personal;

typedef struct _addressBook
{
    Personal personals[MAX];
    Long capacity;
    Long length;
}AddressBook;

int main(int argc, char* argv[]);
Long Load(AddressBook* addressBook);
Long Record(AddressBook* addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress));
void Find(AddressBook* addressBook, char(*name), Long(*indexes), Long* count);
Long Correct(AddressBook* addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress));
Long Erase(AddressBook* addressBook, Long index);
void Arrange(AddressBook* addressBook);
Long Save(AddressBook* addressBook);

#endif //_ADDRESSBOOK_H
