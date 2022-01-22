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

	//메인테스트 시나리오
	//1. capacity에 6을 입력한다.
	AddressBook_Create(&addressBook, 6);
	//2. 불러온다.
	Load(&addressBook);
	//3. 홍길동, 서울 중구, 021766710, Hong을 기재한다.
	index = Record(&addressBook, "홍길동", "서울 중구", "021766710", "Hong");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	//4. 고길동, 서울 성동구, 029575976, Go를 기재한다.
	index = Record(&addressBook, "고길동", "서울 성동구", "029575976", "Go");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	//5. 홍길동, 인천 연수구, 0313267926, Hong2를 기재한다.
	index = Record(&addressBook, "홍길동", "인천 연수구", "0313267926", "Hong2");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	printf("\n");
	//6. 홍길동을 찾는다.
	Find(&addressBook, "홍길동", &indexes, &count);
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
	//7. 세 번째 홍길동의 주소와 전화번호, 이메일주소를 고친다.
	index = Correct(&addressBook, 2, "서울 광진구", "027971723", "Hong2");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	printf("\n");
	//8. 고길동을 지운다.
	index = Erase(&addressBook, 1);
	if (index == -1)
	{
		printf("지워졌습니다\n");
	}
	printf("\n");
	//9. 최길동, 서울 성동구, 023517134, Choi를 기재한다.
	index = Record(&addressBook, "최길동", "서울 성동구", "023517134", "Choi");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	//10. 정길동, 서울 종로구, 024366751, Jung을 기재한다.
	index = Record(&addressBook, "정길동", "서울 종로구", "024366751", "Jung");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
	printf("\n");
	//11. 정리한다.
	Arrange(&addressBook);
	index = 0;
	while (index < addressBook.length)
	{
		personal = AddressBook_GetAt(&addressBook, index);
		printf("%s %s %s %s\n", personal.name, personal.address, personal.telephoneNumber, personal.emailAddress);
		index++;
	}
	//12. 저장한다.
	Save(&addressBook);
	//13. 할당해제한다.
	AddressBook_Destroy(&addressBook);

	return 0;
}
#endif

//Create
void AddressBook_Create(AddressBook* addressBook, Long capacity)
{
	//1. capacity를 입력받는다.
	//2. 배열을 할당한다.
	Create(&addressBook->personals, capacity, sizeof(Personal));
	//3. 할당량을 정한다.
	addressBook->capacity = capacity;
	//4. 사용량을 정한다.
	addressBook->length = 0;
	//5. 끝내다.
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
		//1.1 성명, 주소, 전화번호, 이메일주소를 입력받는다.
		flag = fread(&personal, sizeof(Personal), 1, file);
		//1. 파일의 끝이 아닌동안 반복한다.
		while (!feof(file) && flag != 0)
		{
			//1.2 사용량이 할당량보다 작으면
			if (addressBook->length < addressBook->capacity)
			{
				//1.2.1 빈 줄에 적는다.
				index = Store(&addressBook->personals, addressBook->length, &personal, sizeof(Personal));
			}
			//1.3. 그렇지 않으면
			else
			{
				//1.3.1 새 주소록을 만든다.
				index = AppendFromRear(&addressBook->personals, &personal, sizeof(Personal));
				//1.3.2 할당량을 증가시킨다.
				addressBook->capacity++;
			}
			//1.4. 사용량을 증가시킨다.
			addressBook->length++;
			//1.1 성명, 주소, 전화번호, 이메일주소를 입력받는다.
			flag = fread(&personal, sizeof(Personal), 1, file);
		}
		fclose(file);
	}
	//2. 사용량을 출력한다.
	return addressBook->length;
	//3. 끝내다.
}

//GetAt
Personal AddressBook_GetAt(AddressBook* addressBook, Long index)
{
	Personal personal;
	
	//1. 위치를 입력받는다.
	//2. 해당 위치의 personal을 구한다.
	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
	//3. personal을 출력한다.
	return personal;
	//4. 끝내다.
}

//Record
Long Record(AddressBook* addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress))
{
	Long index;
	Personal personal;

	//1. 성명, 주소, 전화번호, 이메일주소를 입력받는다.
	strcpy(personal.name, name);
	strcpy(personal.address, address);
	strcpy(personal.telephoneNumber, telephoneNumber);
	strcpy(personal.emailAddress, emailAddress);
	//2. 사용량이 할당량보다 작으면
	if (addressBook->length < addressBook->capacity)
	{
		//2.1 빈 줄에 적는다.
		index = Store(&addressBook->personals, addressBook->length, &personal, sizeof(Personal));
	}
	//3. 그렇지 않으면
	else
	{
		//3.1 새 주소록을 만든다.
		index = AppendFromRear(&addressBook->personals, &personal, sizeof(Personal));
		//3.2 할당량을 증가시킨다.
		addressBook->capacity++;
	}
	//4. 사용량을 증가시킨다.
	addressBook->length++;
	//5. 위치를 출력한다.
	return index;
	//6. 끝내다.
}

//Find
void Find(AddressBook* addressBook, char(*name), Long* (*indexes), Long* count)
{
	//1. 성명을 입력받는다.
	//2. 성명을 찾는다.
	LinearSearchDuplicate(&addressBook->personals, name, indexes, count, sizeof(Personal), CompareNames);
	//3. 위치들과 개수를 출력한다.
	//4. 끝내다.
}

//Correct
Long Correct(AddressBook* addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress))
{
	Personal personal;

	//1. 주소, 전화번호, 이메일주소를 입력받는다.
	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
	strcpy(personal.address, address);
	strcpy(personal.telephoneNumber, telephoneNumber);
	strcpy(personal.emailAddress, emailAddress);
	//2. 위치에 적는다.
	index = Modify(&addressBook->personals, index, &personal, sizeof(Personal));
	//3. 위치를 출력한다.
	return index;
	//4. 끝내다.
}

//Erase
Long Erase(AddressBook* addressBook, Long index)
{
	//1. 위치를 입력받는다.
	//2. 해당 위치를 지운다.
	index = Delete(&addressBook->personals, index, sizeof(Personal));
	//3. 할당량을 감소시킨다.
	addressBook->capacity--;
	//4. 사용량을 감소시킨다.
	addressBook->length--;
	//5. 위치를 출력한다.
	return index;
	//6. 끝내다.
}

//Arrange
void Arrange(AddressBook* addressBook)
{
	//1. 오름차순으로 정렬한다.
	InsertionSort(&addressBook->personals, sizeof(Personal), ComparePersonals);
	//2. 끝내다.
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
		//1. 사용량만큼 반복한다.
		while (index < addressBook->length)
		{
			//1.1 성명, 주소, 전화번호, 이메일주소를 출력한다.
			GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
			fwrite(&personal, sizeof(Personal), 1, file);
			index++;
		}
		fclose(file);
	}
	//2. 사용량을 출력한다.
	return addressBook->length;
	//3. 끝내다.
}

//Destroy
void AddressBook_Destroy(AddressBook* addressBook)
{
	//1. 배열을 할당해제한다.
	Destroy(&addressBook->personals);
	//2. 끝내다.
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



