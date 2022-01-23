/***************************************************************************************************************
 파일이름: AddressBook.c
 기능: 주소록에 성명, 주소, 전화번호, 이메일주소를 기재하고, 이름을 통해 기재된
       주소록에서 정보를 찾고, 기재된 정보를 변경하거나 삭제하고 다시 정렬한다.
 작성자: 박인재
 작성일자: 2020/03/10
****************************************************************************************************************/
#include<stdio.h>
#include<string.h>
#include "AddressBook.h"
#pragma warning(disable:4996)
#if 0
int main(int argc, char* argv[]) {
    AddressBook addressBook = { {{"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""},
                                 {"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""}}, MAX, 0 };
    Long index;
    Long indexes[MAX];
    Long count;

    //1. 홍길동, 서울중구, 021766710, Hong을 기재한다.
    index = Record(&addressBook, "홍길동", "서울 중구", "021766710", "Hong");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //2. 고길동, 서울성동구, 025979576, Go를 기재한다.
    index = Record(&addressBook, "고길동", "서울 성동구", "025979576", "Go");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //3. 홍길동, 부산연수구, 0513267920, Hong2를 기재한다.
    index = Record(&addressBook, "홍길동", "부산 연수구", "0513267920", "Hong2");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //4. 정길동, 서울종로구, 024366751, Jung을 기재한다.
    index= Record(&addressBook, "정길동", "서울 종로구", "024366751", "Jung");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //5. 홍길동을 찾는다.
    Find(&addressBook, "홍길동", indexes, &count);
    index = 0;
    while (index<count)
    {
        printf("%d %s %s %s %s\n", indexes[index], addressBook.personals[indexes[index]].name, 
            addressBook.personals[indexes[index]].address, addressBook.personals[indexes[index]].telephoneNumber,
            addressBook.personals[indexes[index]].emailAddress);
        index++;
    }
    //6. 세번째 홍길동의 주소와 전화번호, 이메일 주소를 고친다.
    index = Correct(&addressBook, 2, "서울 광진구", "027971723", "Hong2");
    printf("%d %s %s %s\n", index, addressBook.personals[index].address, 
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //7. 고길동을 지운다.
    index = Erase(&addressBook, 1);
    if (index==-1)
    {
        printf("지워졌습니다.\n");
    }
    //8. 최길동, 서울성동구, 023517134, choi를 기재한다.
    index = Record(&addressBook, "최길동", "서울 성동구", "023517134", "choi");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //9. 고보건, 서울송파구, 021579134, Gobo를 기재한다.
    index = Record(&addressBook, "고보건", "서울 송파구", "021579134", "Gobo");
    printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address,
        addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
    //10. 고보건을 지운다.
    index = Erase(&addressBook, 5);
    if (index == -1)
    {
        printf("지워졌습니다.\n");
    }
    //11. 정리한다.
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
#endif
/***************************************************************************************************************
 함수명칭: Record
 기능: 주소록에 성명, 주소, 전화번호, 이메일주소를 기재한다.
 입력: 주소록, 성명, 주소, 전화번호, 이메일주소
 출력: 위치
****************************************************************************************************************/

Long Record(AddressBook* addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress)) {
    Long index = -1;
    Long i = 0;

    //1. 성명, 주소, 전화번호, 이메일주소를 입력한다.
    //2. 빈 줄을 찾는다.
    while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0) {
        i++;
    }
    //3. 빈줄에 적는다.
    if (i < addressBook->capacity) {
        index = i;
        strcpy(addressBook->personals[index].name, name);
        strcpy(addressBook->personals[index].address, address);
        strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
        strcpy(addressBook->personals[index].emailAddress, emailAddress);
        addressBook->length++;
    }
    //4. 적힌 줄의 위치를 출력한다.
    return index;
    //5. 끝내다.
}

/***************************************************************************************************************
 함수명칭: Find
 기능: 성명으로 찾고자 하는 정보를 찾는다.
 입력: 주소록, 성명
 출력: 위치들, 개수
****************************************************************************************************************/
void Find(AddressBook* addressBook, char(*name), Long(*indexes), Long* count) {
    Long i = 0;
    Long j = 0;

    *count = 0;
    //1. 성명을 입력한다.
    //2. 사용량보다 작거나 같을 동안 반복한다.
    while (i<addressBook->length)
    {
        //2.1 기재된 이름과 찾고자 하는 이름이 같으면
        if (strcmp(addressBook->personals[i].name, name)==0)
        {
            //2.1.1 개수를 센다.
            (*count)++;
            //2.1.2 위치를 저장한다.
            indexes[j] = i;
            j++;
        }
        i++;
    }
    //3. 위치들과 개수를 출력한다.
    //4. 끝내다.
}

/***************************************************************************************************************
 함수명칭: Correct
 기능: 찾고자 하는 위치와 변경할 내용을 입력한다.
 입력: 주소록, 위치, 주소, 전화번호, 이메일주소
 출력: 위치
****************************************************************************************************************/
Long Correct(AddressBook* addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress)) {
    //1. 위치, 주소, 전화번호, 이메일주소를 입력한다.
    //2. 위치에 적는다.
    strcpy(addressBook->personals[index].address, address);
    strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
    strcpy(addressBook->personals[index].emailAddress, emailAddress);
    //3. 위치를 출력한다.
    return index;
    //4. 끝내다.
}

/***************************************************************************************************************
 함수명칭: Erase
 기능: 지울 위치의 이름을 지운다.
 입력: 주소록, 위치
 출력: 위치
****************************************************************************************************************/
Long Erase(AddressBook* addressBook, Long index) {
    //1. 지울 위치를 입력한다.
    //2. 위치를 지운다.
    strcpy(addressBook->personals[index].name, "X");
    index = -1;
    //3. 위치를 출력한다.
    return index;
    //4. 끝내다.
}

/***************************************************************************************************************
 함수명칭: Arrange
 기능: 주소록을 정렬한다.
 입력: 주소록
 출력: 없음
****************************************************************************************************************/
void Arrange(AddressBook* addressBook) {
    Personal personal;
    Long i = 1;
    Long j;
    Long count=0;

    //1. 사용량보다 작거나 같은동안 반복한다.
    while (i<addressBook->length)
    {
        //1.1 내림차순으로 정렬한다.
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
    //2. 개수를 센다.
    i = 0;
    while (i<addressBook->length && strcmp(addressBook->personals[i].name, "X")!=0)
    {
        count++;
        i++;
    }
    //3. 오름차순으로 정렬한다.
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
    //4. 끝내다.
}