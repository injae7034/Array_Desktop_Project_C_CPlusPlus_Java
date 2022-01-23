/***************************************************************************************************************
 �����̸�: AddressBook.c
 ���: �ּҷϿ� ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �����ϰ�, �̸��� ���� �����
       �ּҷϿ��� ������ ã��, ����� ������ �����ϰų� �����ϰ� �ٽ� �����Ѵ�.
 �ۼ���: ������
 �ۼ�����: 2020/03/10
****************************************************************************************************************/
#include<stdio.h>
#include<string.h>
#include "AddressBook.h"
#pragma warning(disable:4996)


int main(int argc, char* argv[]) {
    AddressBook addressBook = { {{"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""},
                                 {"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""}}, MAX, 0 };
    Long index;
    Long indexes[MAX];
    Long count;

    //1. ȫ�浿, �����߱�, 021766710, Hong�� �����Ѵ�.
    index = Record(&addressBook, "ȫ�浿", "���� �߱�", "021766710", "Hong");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //2. ��浿, ���Ｚ����, 025979576, Go�� �����Ѵ�.
    index = Record(&addressBook, "��浿", "���� ������", "025979576", "Go");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //3. ȫ�浿, �λ꿬����, 0513267920, Hong2�� �����Ѵ�.
    index = Record(&addressBook, "ȫ�浿", "�λ� ������", "0513267920", "Hong2");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //4. ���浿, �������α�, 024366751, Jung�� �����Ѵ�.
    index= Record(&addressBook, "���浿", "���� ���α�", "024366751", "Jung");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //5. ȫ�浿�� ã�´�.
    Find(&addressBook, "ȫ�浿", indexes, &count);
    index = 0;
    while (index<count)
    {
        printf("%d %s %s %s %s\n", indexes[index], addressBook.personals[indexes[index]].name, 
            addressBook.personals[indexes[index]].address, addressBook.personals[indexes[index]].telephoneNumber,
            addressBook.personals[indexes[index]].emailAddress);
        index++;
    }
    //6. ����° ȫ�浿�� �ּҿ� ��ȭ��ȣ, �̸��� �ּҸ� ��ģ��.
    index = Correct(&addressBook, 2, "���� ������", "027971723", "Hong2");
    printf("%d %s %s %s\n", index, addressBook.personals[index].address, 
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //7. ��浿�� �����.
    index = Erase(&addressBook, 1);
    if (index==-1)
    {
        printf("���������ϴ�.\n");
    }
    //8. �ֱ浿, ���Ｚ����, 023517134, choi�� �����Ѵ�.
    index = Record(&addressBook, "�ֱ浿", "���� ������", "023517134", "choi");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //9. ����, ������ı�, 021579134, Gobo�� �����Ѵ�.
    index = Record(&addressBook, "����", "���� ���ı�", "021579134", "Gobo");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //10. ������ �����.
    index = Erase(&addressBook, 5);
    if (index == -1)
    {
        printf("���������ϴ�.\n");
    }
    //11. �����Ѵ�.
    Arrange(&addressBook);
    index = 0;
    while (index<addressBook.length)
    {
        printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
            addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
        index++;
    }

    return 0;
}

/***************************************************************************************************************
 �Լ���Ī: Record
 ���: �ּҷϿ� ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �����Ѵ�.
 �Է�: �ּҷ�, ����, �ּ�, ��ȭ��ȣ, �̸����ּ�
 ���: ��ġ
****************************************************************************************************************/

Long Record(AddressBook* addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress)) {
    Long index = -1;
    Long i = 0;

    //1. ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է��Ѵ�.
    //2. �� ���� ã�´�.
    while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0) {
        i++;
    }
    //3. ���ٿ� ���´�.
    if (i < addressBook->capacity) {
        index = i;
        strcpy(addressBook->personals[index].name, name);
        strcpy(addressBook->personals[index].address, address);
        strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
        strcpy(addressBook->personals[index].emailAddress, emailAddress);
        addressBook->length++;
    }
    //4. ���� ���� ��ġ�� ����Ѵ�.
    return index;
    //5. ������.
}

/***************************************************************************************************************
 �Լ���Ī: Find
 ���: �������� ã���� �ϴ� ������ ã�´�.
 �Է�: �ּҷ�, ����
 ���: ��ġ��, ����
****************************************************************************************************************/
void Find(AddressBook* addressBook, char(*name), Long(*indexes), Long* count) {
    Long i = 0;
    Long j = 0;

    *count = 0;
    //1. ������ �Է��Ѵ�.
    //2. ��뷮���� �۰ų� ���� ���� �ݺ��Ѵ�.
    while (i<addressBook->length)
    {
        //2.1 ����� �̸��� ã���� �ϴ� �̸��� ������
        if (strcmp(addressBook->personals[i].name, name)==0)
        {
            //2.1.1 ������ ����.
            (*count)++;
            //2.1.2 ��ġ�� �����Ѵ�.
            indexes[j] = i;
            j++;
        }
        i++;
    }
    //3. ��ġ��� ������ ����Ѵ�.
    //4. ������.
}

/***************************************************************************************************************
 �Լ���Ī: Correct
 ���: ã���� �ϴ� ��ġ�� ������ ������ �Է��Ѵ�.
 �Է�: �ּҷ�, ��ġ, �ּ�, ��ȭ��ȣ, �̸����ּ�
 ���: ��ġ
****************************************************************************************************************/
Long Correct(AddressBook* addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress)) {
    //1. ��ġ, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է��Ѵ�.
    //2. ��ġ�� ���´�.
    strcpy(addressBook->personals[index].address, address);
    strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
    strcpy(addressBook->personals[index].emailAddress, emailAddress);
    //3. ��ġ�� ����Ѵ�.
    return index;
    //4. ������.
}

/***************************************************************************************************************
 �Լ���Ī: Erase
 ���: ���� ��ġ�� �̸��� �����.
 �Է�: �ּҷ�, ��ġ
 ���: ��ġ
****************************************************************************************************************/
Long Erase(AddressBook* addressBook, Long index) {
    //1. ���� ��ġ�� �Է��Ѵ�.
    //2. ��ġ�� �����.
    strcpy(addressBook->personals[index].name, "X");
    index = -1;
    //3. ��ġ�� ����Ѵ�.
    return index;
    //4. ������.
}

/***************************************************************************************************************
 �Լ���Ī: Arrange
 ���: �ּҷ��� �����Ѵ�.
 �Է�: �ּҷ�
 ���: ����
****************************************************************************************************************/
void Arrange(AddressBook* addressBook) {
    Personal personal;
    Long i = 1;
    Long j;
    Long count=0;

    //1. ��뷮���� �۰ų� �������� �ݺ��Ѵ�.
    while (i<addressBook->length)
    {
        //1.1 ������������ �����Ѵ�.
        personal = addressBook->personals[i];
        j = i - 1;
        while (j>=0 && strcmp(addressBook->personals[j].name, personal.name)<0)
        {
            addressBook->personals[j + 1] = addressBook->personals[j];
            j--;
        }
        addressBook->personals[j + 1] = personal;
        i++;
    }
    //2. ������ ����.
    i = 0;
    while (i<addressBook->length && strcmp(addressBook->personals[i].name, "X")!=0)
    {
        count++;
        i++;
    }
    //3. ������������ �����Ѵ�.
    i = 1;
    while (i<count)
    {
        personal = addressBook->personals[i];
        j = i - 1;
        while (j>=0 && strcmp(addressBook->personals[j].name, personal.name)>0)
        {
            addressBook->personals[j + 1] = addressBook->personals[j];
            j--;
        }
        addressBook->personals[j + 1] = personal;
        i++;
    }
    //4. ������.
}