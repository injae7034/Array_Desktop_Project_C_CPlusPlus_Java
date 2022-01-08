#include "AddressBook.h"
#include<stdio.h>//printf
#include<string.h>//strcpy, strcmp
#include<stdlib.h>//calloc, free
#pragma warning(disable:4996)

#if 0
int main(int argc, char* argv[])
{
	AddressBook addressBook;
	Long index;
	Long(*indexes);
	Long count;
	Personal personal;

	//�����׽�Ʈ �ó�����
	//1. capacity�� 6�� �Է��Ѵ�.
	AddressBook_Create(&addressBook, 6);
	//2. �ҷ��´�.
	Load(&addressBook);
	//3. ȫ�浿, ���� �߱�, 021766710, Hong�� �����Ѵ�.
	index = Record(&addressBook, "ȫ�浿", "���� �߱�", "021766710", "Hong");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	//4. ��浿, ���� ������, 029575976, Go�� �����Ѵ�.
	index = Record(&addressBook, "��浿", "���� ������", "029575976", "Go");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	//5. ȫ�浿, ��õ ������, 0313267926, Hong2�� �����Ѵ�.
	index = Record(&addressBook, "ȫ�浿", "��õ ������", "0313267926", "Hong2");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	printf("\n");
	//6. ȫ�浿�� ã�´�.
	Find(&addressBook, "ȫ�浿", &indexes, &count);
	index = 0;
	while (index < count)
	{
		personal=AddressBook_GetAt(&addressBook, indexes[index]);
		printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
		index++;
	}
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//7. �� ��° ȫ�浿�� �ּҿ� ��ȭ��ȣ, �̸����ּҸ� ��ģ��.
	index = Correct(&addressBook, 2, "���� ������", "027971723", "Hong2");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	printf("\n");
	//8. ��浿�� �����.
	index = Erase(&addressBook, 1);
	if (index == -1)
	{
		printf("���������ϴ�\n");
	}
	printf("\n");
	//9. �ֱ浿, ���� ������, 023517134, Choi�� �����Ѵ�.
	index = Record(&addressBook, "�ֱ浿", "���� ������", "023517134", "Choi");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	//10. ���浿, ���� ���α�, 024366751, Jung�� �����Ѵ�.
	index = Record(&addressBook, "���浿", "���� ���α�", "024366751", "Jung");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	printf("\n");
	//11. �����Ѵ�.
	Arrange(&addressBook);
	index = 0;
	while (index < addressBook.length)
	{
		personal = AddressBook_GetAt(&addressBook, index);
		printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
		index++;
	}
	//12. �����Ѵ�.
	Save(&addressBook);
	//13. �Ҵ������Ѵ�.
	AddressBook_Destroy(&addressBook);

	return 0;
}
#endif

//Create
void AddressBook_Create(AddressBook* addressBook, Long capacity)
{
	//1. capacity�� �Է¹޴´�.
	//2. �迭�� �Ҵ��Ѵ�.
	Create(&addressBook->personals, capacity, sizeof(Personal));
	//3. �Ҵ緮�� ���Ѵ�.
	addressBook->capacity = capacity;
	//4. ��뷮�� ���Ѵ�.
	addressBook->length = 0;
	//5. ������.
}

//Load
Long Load(AddressBook* addressBook)
{
	Personal personal;
	Long index;
	int flag;
	FILE* file;

	file = fopen("AddressBook.dat", "rb");
	if (file != NULL)
	{
		//1.1 ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޴´�.
		flag = fread(&personal, sizeof(Personal), 1, file);
		//1. ������ ���� �ƴѵ��� �ݺ��Ѵ�.
		while (!feof(file) && flag != 0)
		{
			//1.2 ��뷮�� �Ҵ緮���� ������
			if (addressBook->length < addressBook->capacity)
			{
				//1.2.1 �� �ٿ� ���´�.
				index = Store(&addressBook->personals, addressBook->length, &personal, sizeof(Personal));
			}
			//1.3. �׷��� ������
			else
			{
				//1.3.1 �� �ּҷ��� �����.
				index = AppendFromRear(&addressBook->personals, &personal, sizeof(Personal));
				//1.3.2 �Ҵ緮�� ������Ų��.
				addressBook->capacity++;
			}
			//1.4. ��뷮�� ������Ų��.
			addressBook->length++;
			//1.1 ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޴´�.
			flag = fread(&personal, sizeof(Personal), 1, file);
		}
		fclose(file);
	}
	//2. ��뷮�� ����Ѵ�.
	return addressBook->length;
	//3. ������.
}

//GetAt
Personal AddressBook_GetAt(AddressBook* addressBook, Long index)
{
	Personal personal;
	
	//1. ��ġ�� �Է¹޴´�.
	//2. �ش� ��ġ�� personal�� ���Ѵ�.
	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
	//3. personal�� ����Ѵ�.
	return personal;
	//4. ������.
}

//Record
Long Record(AddressBook* addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress))
{
	Long index;
	Personal personal;

	//1. ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޴´�.
	strcpy(personal.name, name);
	strcpy(personal.address, address);
	strcpy(personal.telephoneNumber, telephoneNumber);
	strcpy(personal.emailAddress, emailAddress);
	//2. ��뷮�� �Ҵ緮���� ������
	if (addressBook->length < addressBook->capacity)
	{
		//2.1 �� �ٿ� ���´�.
		index = Store(&addressBook->personals, addressBook->length, &personal, sizeof(Personal));
	}
	//3. �׷��� ������
	else
	{
		//3.1 �� �ּҷ��� �����.
		index = AppendFromRear(&addressBook->personals, &personal, sizeof(Personal));
		//3.2 �Ҵ緮�� ������Ų��.
		addressBook->capacity++;
	}
	//4. ��뷮�� ������Ų��.
	addressBook->length++;
	//5. ��ġ�� ����Ѵ�.
	return index;
	//6. ������.
}

//Find
void Find(AddressBook* addressBook, char(*name), Long* (*indexes), Long* count)
{
	//1. ������ �Է¹޴´�.
	//2. ������ ã�´�.
	LinearSearchDuplicate(&addressBook->personals, name, indexes, count, sizeof(Personal), CompareNames);
	//3. ��ġ��� ������ ����Ѵ�.
	//4. ������.
}

//Correct
Long Correct(AddressBook* addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress))
{
	Personal personal;

	//1. �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޴´�.
	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
	strcpy(personal.address, address);
	strcpy(personal.telephoneNumber, telephoneNumber);
	strcpy(personal.emailAddress, emailAddress);
	//2. ��ġ�� ���´�.
	index = Modify(&addressBook->personals, index, &personal, sizeof(Personal));
	//3. ��ġ�� ����Ѵ�.
	return index;
	//4. ������.
}

//Erase
Long Erase(AddressBook* addressBook, Long index)
{
	//1. ��ġ�� �Է¹޴´�.
	//2. �ش� ��ġ�� �����.
	index = Delete(&addressBook->personals, index, sizeof(Personal));
	//3. �Ҵ緮�� ���ҽ�Ų��.
	addressBook->capacity--;
	//4. ��뷮�� ���ҽ�Ų��.
	addressBook->length--;
	//5. ��ġ�� ����Ѵ�.
	return index;
	//6. ������.
}

//Arrange
void Arrange(AddressBook* addressBook)
{
	//1. ������������ �����Ѵ�.
	InsertionSort(&addressBook->personals, sizeof(Personal), ComparePersonals);
	//2. ������.
}

//Save
Long Save(AddressBook* addressBook)
{
	Personal personal;
	Long index = 0;
	FILE* file;

	file = fopen("AddressBook.dat", "wb");
	if (file != NULL)
	{
		//1. ��뷮��ŭ �ݺ��Ѵ�.
		while (index < addressBook->length)
		{
			//1.1 ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� ����Ѵ�.
			GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
			fwrite(&personal, sizeof(Personal), 1, file);
			index++;
		}
		fclose(file);
	}
	//2. ��뷮�� ����Ѵ�.
	return addressBook->length;
	//3. ������.
}

//Destroy
void AddressBook_Destroy(AddressBook* addressBook)
{
	//1. �迭�� �Ҵ������Ѵ�.
	Destroy(&addressBook->personals);
	//2. ������.
}


int CompareNames(void* one, void* other)
{
	Personal* one_ = (Personal*)one;
	char(*other_) = (char(*))other;
	
	return strcmp(one_->name, other_);
}

int ComparePersonals(void* one, void* other)
{
	Personal* one_ = (Personal*)one;
	Personal* other_ = (Personal*)other;

	return strcmp(one_->name, other_->name);
}



