#include "AddressBook.h"
#include<stdio.h>
#include<string.h>//strcmp, strcpy
#include<stdlib.h>//calloc, free
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	AddressBook addressBook;
	Long index;
	Long(*indexes);
	Long count;

	//���� �׽�Ʈ �ó�����
	//1.capacity=6�� �Է��Ѵ�.
	Create(&addressBook, 6);
	//2. ȫ�浿, ���� �߱�, 021766710, Hong�� �����Ѵ�.
	index = Record(&addressBook, "ȫ�浿", "���� �߱�", "021766710", "Hong");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//3. ��浿, ���� ������, 029575976, Go�� �����Ѵ�.
	index = Record(&addressBook, "��浿", "���� ������", "029575976", "Go");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//4. ȫ�浿, ��õ ������, 0313267926, Hong2�� �����Ѵ�.
	index = Record(&addressBook, "ȫ�浿", "��õ ������", "0313267926", "Hong2");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//5. ȫ�浿�� ã�´�.
	Find(&addressBook, "ȫ�浿", &indexes, &count);
	index = 0;
	while (index<count)
	{
		printf("%s %s %s %s\n", addressBook.personals[indexes[index]].name,
			addressBook.personals[indexes[index]].address, addressBook.personals[indexes[index]].telephoneNumber,
			addressBook.personals[indexes[index]].emailAddress);
		index++;
	}
	if (indexes!=NULL)
	{
		free(indexes);
	}
	//6. �� ��° ȫ�浿�� �ּҿ� ��ȭ��ȣ, �̸����ּҸ� ��ģ��.
	index = Correct(&addressBook, 2, "���� ������", "027971723", "Hong2");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//7. ��浿�� �����.
	index = Erase(&addressBook, 1);
	if (index == -1)
	{
		printf("���������ϴ�.\n");
	}
	//8. �ֱ浿, ���� ������, 023517134, Choi�� �����Ѵ�.
	index = Record(&addressBook, "�ֱ浿", "���� ������", "023517134", "Choi");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//9. ���浿, ���� ���α�, 024366751, NA�� �����Ѵ�.
	index = Record(&addressBook, "���浿", "���� ���α�", "024366751", "NA");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//10. �ֱ浿�� ã�´�.
	Find(&addressBook, "�ֱ浿", &indexes, &count);
	index = 0;
	while (index < count)
	{
		printf("%s %s %s %s\n", addressBook.personals[indexes[index]].name,
			addressBook.personals[indexes[index]].address, addressBook.personals[indexes[index]].telephoneNumber,
			addressBook.personals[indexes[index]].emailAddress);
		index++;
	}
	if (indexes != NULL)
	{
		free(indexes);
	}
    //11. �� ��° ���浿�� �ּҿ� ��ȭ��ȣ, �̸����ּҸ� ��ģ��.
	index = Correct(&addressBook, 3, "��� �ϱ�", "0529517699", "NA");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("=============================================================\n");
    //12. �����Ѵ�.
	Arrange(&addressBook);

	index = 0;
	while (index<addressBook.length)
	{
		printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
			addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
		index++;
	}
    //13. �Ҵ������Ѵ�.
    Destroy(&addressBook);

	return 0;
}

//Create
void Create(AddressBook* addressBook, Long capacity)
{
	//1. capacity�� �Է¹޴´�.
	//2. ���ε� �迭�� �����.
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	//3. �Ҵ緮�� ���Ѵ�.
	addressBook->capacity = capacity;
	//4. ��뷮�� ���Ѵ�.
	addressBook->length = 0;
	//5. ������.
}

//Record
Long Record(AddressBook* addressBook, char(*name), char(*address),
	char(*telephoneNumber), char(*emailAddress))
{
	Long index = -1;
	Personal(*personals)=NULL;
	Long i=0;
	
	//1. ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޴´�.
	//2. �� ���� ã�´�.
	while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0)
	{
		i++;
	}
	//3. �� ���� ������
	if (i >= addressBook->capacity)
	{
		//3.1 ���ּҷ��� �����.
		personals = (Personal(*))calloc(addressBook->capacity + 1, sizeof(Personal));
		//3.2 ���� �ּҷ��� ������ �Ű����´�.
		i = 0;
		while (i<addressBook->length)
		{
			personals[i] = addressBook->personals[i];
			i++;
		}
		//3.3 �����ּҷ��� �����.
		if (addressBook->personals != NULL)
		{
			free(addressBook->personals);
		}
		addressBook->personals = personals;
		addressBook->capacity++;
	}
	//4. ���ٿ� ���´�.
	index = i;
	strcpy(addressBook->personals[index].name, name);
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	addressBook->length++;
	//5. ��ġ�� ����Ѵ�.
	return index;
	//6. ������.
}

//Find
void Find(AddressBook* addressBook, char(*name), Long* (*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;

	*count = 0;
	//1. ������ �Է¹޴´�.
	//2. ����� ���뺸�� �۰ų� ���� ���� �ݺ��Ѵ�.
	while (i<addressBook->length)
	{
		//2.1 �̸��� ���� ������
		if (strcmp(addressBook->personals[i].name, name)==0)
		{
			//2.1.1 ������ ����.
			(*count)++;
		}
		i++;
	}
	//3. ������ 0���� ũ��
	if (*count > 0)
	{
		//3.1 ��ġ�� �迭�� �����.
		*indexes = (Long(*))calloc(*count, sizeof(Long));
	}
	//4. ����� ���뺸�� �۰ų� �������� �ݺ��Ѵ�.
	i = 0;
	while (i<addressBook->length)
	{
		//4.1 �̸��� ���� ������
		if (strcmp(addressBook->personals[i].name, name)==0)
		{
			//4.1.1 ��ġ�� �����Ѵ�.
			(*indexes)[j] = i;
			j++;
		}
		i++;
	}
	//5. ��ġ��� ������ ����Ѵ�.
	//6. ������.
}

//Correct
Long Correct(AddressBook* addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress))
{
	//1. ��ġ, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޴´�.
	//2. ��ġ�� ���´�.
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	//3. ��ġ�� ����Ѵ�.
	return index;
	//4. ������.
}

//Erase
Long Erase(AddressBook* addressBook, Long index)
{
	Personal(*personals)=NULL;
	Long i = 0;
	Long j = 0;
	//1. ��ġ�� �Է¹޴´�.
	//2. ���ּҷ��� �����.
	if (addressBook->capacity > 1)
	{
		personals = (Personal(*))calloc(addressBook->capacity - 1, sizeof(Personal));
	}
	//3. �����ּҷ��� ������ �Ű����´�.
	while (i<index)
	{
		personals[j] = addressBook->personals[i];
		j++;
		i++;
	}
	i = index + 1;
	while (i < addressBook->length)
	{
		personals[j] = addressBook->personals[i];
		j++;
		i++;
	}
	//4. �����ּҷ��� �����.
	if (addressBook->personals!=NULL)
	{
		free(addressBook->personals);
		addressBook->personals = NULL;
	}
	if (addressBook->capacity > 1)
	{
		addressBook->personals = personals;
	}
	addressBook->capacity--;
	addressBook->length--;
	index = -1;
	//5. ��ġ�� ����Ѵ�.
	return index;
	//6. ������.
}

//Arrange
void Arrange(AddressBook* addressBook)
{
	Personal personal;
	Long i = 1;
	Long j;
	//1. ������������ �����Ѵ�.
	while (i<addressBook->length)
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
	//2. ������.
}

//Destroy

void Destroy(AddressBook* addressBook)
{
	//1. �Ҵ������Ѵ�.
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
	}
	//2. ������.
}

