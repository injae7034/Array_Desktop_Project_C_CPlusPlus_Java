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

	//메인 테스트 시나리오
	//1.capacity=6을 입력한다.
	Create(&addressBook, 6);
	//2. 홍길동, 서울 중구, 021766710, Hong을 기재한다.
	index = Record(&addressBook, "홍길동", "서울 중구", "021766710", "Hong");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//3. 고길동, 서울 성동구, 029575976, Go를 기재한다.
	index = Record(&addressBook, "고길동", "서울 성동구", "029575976", "Go");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//4. 홍길동, 인천 연수구, 0313267926, Hong2를 기재한다.
	index = Record(&addressBook, "홍길동", "인천 연수구", "0313267926", "Hong2");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//5. 홍길동을 찾는다.
	Find(&addressBook, "홍길동", &indexes, &count);
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
	//6. 세 번째 홍길동의 주소와 전화번호, 이메일주소를 고친다.
	index = Correct(&addressBook, 2, "서울 광진구", "027971723", "Hong2");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//7. 고길동을 지운다.
	index = Erase(&addressBook, 1);
	if (index == -1)
	{
		printf("지워졌습니다.\n");
	}
	//8. 최길동, 서울 성동구, 023517134, Choi를 기재한다.
	index = Record(&addressBook, "최길동", "서울 성동구", "023517134", "Choi");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//9. 나길동, 서울 종로구, 024366751, NA을 기재한다.
	index = Record(&addressBook, "나길동", "서울 종로구", "024366751", "NA");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	//10. 최길동을 찾는다.
	Find(&addressBook, "최길동", &indexes, &count);
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
    //11. 네 번째 정길동의 주소와 전화번호, 이메일주소를 고친다.
	index = Correct(&addressBook, 3, "울산 북구", "0529517699", "NA");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
		addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("=============================================================\n");
    //12. 정리한다.
	Arrange(&addressBook);

	index = 0;
	while (index<addressBook.length)
	{
		printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
			addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
		index++;
	}
    //13. 할당해제한다.
    Destroy(&addressBook);

	return 0;
}

//Create
void Create(AddressBook* addressBook, Long capacity)
{
	//1. capacity를 입력받는다.
	//2. 개인들 배열을 만든다.
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	//3. 할당량을 정한다.
	addressBook->capacity = capacity;
	//4. 사용량을 정한다.
	addressBook->length = 0;
	//5. 끝내다.
}

//Record
Long Record(AddressBook* addressBook, char(*name), char(*address),
	char(*telephoneNumber), char(*emailAddress))
{
	Long index = -1;
	Personal(*personals)=NULL;
	Long i;
	
	//1. 성명, 주소, 전화번호, 이메일주소를 입력받는다.
	//2. 빈 줄을 찾는다.
	//3. 빈 줄이 없으면
	if (addressBook->length >= addressBook->capacity)
	{
		//3.1 새주소록을 만든다.
		personals = (Personal(*))calloc(addressBook->capacity + 1, sizeof(Personal));
		//3.2 기존 주소록의 내용을 옮겨적는다.
		i = 0;
		while (i<addressBook->length)
		{
			personals[i] = addressBook->personals[i];
			i++;
		}
		//3.3 기존주소록을 지운다.
		if (addressBook->personals != NULL)
		{
			free(addressBook->personals);
		}
		addressBook->personals = personals;
		addressBook->capacity++;
	}
	//4. 빈줄에 적는다.
	index = addressBook->length;
	strcpy(addressBook->personals[index].name, name);
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	addressBook->length++;
	//5. 위치를 출력한다.
	return index;
	//6. 끝내다.
}

//Find
void Find(AddressBook* addressBook, char(*name), Long* (*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;

	*count = 0;
	//1. 성명을 입력받는다.
	//2. 기재된 내용보다 작거나 같은 동안 반복한다.
	while (i<addressBook->length)
	{
		//2.1 이름이 서로 같으면
		if (strcmp(addressBook->personals[i].name, name)==0)
		{
			//2.1.1 개수를 센다.
			(*count)++;
		}
		i++;
	}
	//3. 개수가 0보다 크면
	if (*count > 0)
	{
		//3.1 위치들 배열을 만든다.
		*indexes = (Long(*))calloc(*count, sizeof(Long));
	}
	//4. 기재된 내용보다 작거나 같은동안 반복한다.
	i = 0;
	while (i<addressBook->length)
	{
		//4.1 이름이 서로 같으면
		if (strcmp(addressBook->personals[i].name, name)==0)
		{
			//4.1.1 위치를 저장한다.
			(*indexes)[j] = i;
			j++;
		}
		i++;
	}
	//5. 위치들과 개수를 출력한다.
	//6. 끝내다.
}

//Correct
Long Correct(AddressBook* addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress))
{
	//1. 위치, 주소, 전화번호, 이메일주소를 입력받는다.
	//2. 위치에 적는다.
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	//3. 위치를 출력한다.
	return index;
	//4. 끝내다.
}

//Erase
Long Erase(AddressBook* addressBook, Long index)
{
	Personal(*personals)=NULL;
	Long i = 0;
	Long j = 0;
	//1. 위치를 입력받는다.
	//2. 새주소록을 만든다.
	if (addressBook->capacity > 1)
	{
		personals = (Personal(*))calloc(addressBook->capacity - 1, sizeof(Personal));
	}
	//3. 기존주소록의 내용을 옮겨적는다.
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
	//4. 기존주소록을 지운다.
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
	//5. 위치를 출력한다.
	return index;
	//6. 끝내다.
}

//Arrange
void Arrange(AddressBook* addressBook)
{
	Personal personal;
	Long i = 1;
	Long j;
	//1. 오름차순으로 정렬한다.
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
	//2. 끝내다.
}

//Destroy

void Destroy(AddressBook* addressBook)
{
	//1. 할당해제한다.
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
	}
	//2. 끝내다.
}

