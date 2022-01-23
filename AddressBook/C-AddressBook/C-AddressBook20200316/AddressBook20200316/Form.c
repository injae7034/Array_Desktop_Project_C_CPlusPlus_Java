#include "Form.h"
#include "AddressBook.h"
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)

int main(int argc, char* argv[]) 
{
    //사용량만큼 계속해서 초기화 시켜주어야 함. 그래야 Record함수에서 빈칸을 인식해서 기재할 수 있음.
    AddressBook addressBook = { {{"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""},
                                  {"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""}}, MAX, 0 };
    
    int menu;

    Load(&addressBook);
    DisplayMenu();
    rewind(stdin); scanf("%d", &menu);
    while (menu!=0)
    {
        switch (menu)
        {
        case 1: FormFoRecording(&addressBook); break;
        case 2: FormFoFinding(&addressBook); break;
        case 3: FormFoCorrecting(&addressBook); break;
        case 4: FormFoErasing(&addressBook); break;
        case 5: FormFoArranging(&addressBook); break;
        case 6: FormFoViewingAll(&addressBook); break;
        default: break;
        }
        DisplayMenu();
        rewind(stdin); scanf("%d", &menu);
    }
    Save(&addressBook);

    return 0;

}

void DisplayMenu() {
    system("cls");//clear Screen
    printf("\n\n\n\n\n\n\n\n\n");
    printf("     \t\t\t\t\t\t주소록version0.05\n");
    printf("     \t\t\t\t\t\t====================\n");
    printf("     \t\t\t\t\t\t[1] 기재하기\n");
    printf("     \t\t\t\t\t\t[2] 찾    기\n");
    printf("     \t\t\t\t\t\t[3] 고 치 기\n");
    printf("     \t\t\t\t\t\t[4] 지 우 기\n");
    printf("     \t\t\t\t\t\t[5] 정리하기\n");
    printf("     \t\t\t\t\t\t[6] 전체보기\n");
    printf("     \t\t\t\t\t\t[0] 끝 내 기\n");
    printf("     \t\t\t\t\t\t--------------------\n");
    printf("     \t\t\t\t\t\t메뉴를 선택하십시오! ");
}

void FormFoRecording(AddressBook* addressBook) {
    char name[11];
    char address[32];
    char telephoneNumber[12];
    char emailAddress[32];
    char recording;
    char going = 'Y';
    Long index;

    while (going=='Y' || going=='y')
    {
        system("cls");//clear Screen
        printf("\n\n\n\n\n\n\n\n\n");
        printf("     \t\t\t주소록version0.05-기재하기\n");
        printf("     \t\t\t==============================================\n");
        printf("     \t\t\t성      명 : "); rewind(stdin); scanf("%s", name);
        printf("     \t\t\t주      소 : "); rewind(stdin); gets(address);
        printf("     \t\t\t전화  번호 : "); rewind(stdin); scanf("%s", telephoneNumber);
        printf("     \t\t\t이메일주소 : "); rewind(stdin); scanf("%s", emailAddress);
        printf("     \t\t\t----------------------------------------------\n");
        printf("     \t\t\t기재하시겠습니까?(Yes/No) "); rewind(stdin); recording = getchar();

        if (recording=='Y' || recording=='y')
        {
            index = Record(addressBook, name, address, telephoneNumber, emailAddress);
            printf("     \t\t\t========================================================================\n");
            printf("     \t\t\t번호  성명\t주소\t\t전화번호\t이메일주소\n");
            printf("     \t\t\t------------------------------------------------------------------------\n");
            printf("     \t\t\t%d  %s\t%s\t\t%s\t%s\n", index+1, addressBook->personals[index].name,
                         addressBook->personals[index].address, addressBook->personals[index].telephoneNumber,
                         addressBook->personals[index].emailAddress);
        }
        printf("     \t\t\t============================================================================\n");
        printf("     \t\t\t계속하시겠습니까?(Yes/No) "); rewind(stdin); going = getchar();
    }
}

void FormFoFinding(AddressBook* addressBook) {
    char name[11];
    char going ='Y';
    Long indexes[MAX];
    Long count;
    Long index;

    while (going=='Y' || going=='y')
    {
        system("cls");//clear Screen
        printf("\n\n\n\n\n\n\n\n\n");
        printf("     주소록version0.05-찾기\n");
        printf("     ================================================================================\n");
        printf("     성명 : "); rewind(stdin); scanf("%s", name);
        printf("     ================================================================================\n");
        printf("     번호  성명\t주소\t\t전화번호\t이메일주소\n");
        printf("     --------------------------------------------------------------------------------\n");
        Find(addressBook, name, indexes, &count);
        index = 0;
        while (index<count)
        {
            printf("     %d  %s\t%s\t\t%s\t%s\n", index + 1, addressBook->personals[indexes[index]].name,
                addressBook->personals[indexes[index]].address, addressBook->personals[indexes[index]].telephoneNumber,
                addressBook->personals[indexes[index]].emailAddress);
            index++;
        }
        printf("     ================================================================================\n");
        printf("     계속하시겠습니까?(Yes/No) "); rewind(stdin); going = getchar();
    }
}

void FormFoCorrecting(AddressBook* addressBook) {
    char name[11];
    Long indexes[MAX];
    Long count;
    Long index;
    char address[32];
    char telephoneNumber[12];
    char emailAddress[32];
    char correcting;
    char going = 'Y';

    while (going=='Y' || going=='y')
    {
        system("cls");//clear Screen
        printf("\n\n\n\n\n\n\n\n\n");
        printf("     주소록version0.05-고치기\n");
        printf("     ====================================================================================\n");
        printf("     성명 : ");rewind(stdin);scanf("%s", name);
        printf("     =====================================================================================\n");
        printf("     번호  성명\t주소\t\t전화번호\t이메일주소\n");
        printf("     ------------------------------------------------------------------------------------\n");
        Find(addressBook, name, indexes, &count);
        index = 0;
        while (index<count)
        {
            printf("     %d  %s\t%s\t\t%s\t%s\n", index + 1, addressBook->personals[indexes[index]].name,
                addressBook->personals[indexes[index]].address, addressBook->personals[indexes[index]].telephoneNumber,
                addressBook->personals[indexes[index]].emailAddress);
            index++;
        }
        if (count>0)
        {
            printf("     ================================================================================\n");
            printf("     번호 : ");rewind(stdin);scanf("%d", &index);
            printf("     --------------------------------------------------------------------------------\n");
            index = index - 1;
            printf("     주      소 : %s ", addressBook->personals[indexes[index]].address); rewind(stdin); gets(address);
            if (strcmp(address, "")==0)
            {
                strcpy(address, addressBook->personals[indexes[index]].address);
            }
            printf("     전화  번호 : %s ", addressBook->personals[indexes[index]].telephoneNumber); rewind(stdin); gets(telephoneNumber);
            if (strcmp(telephoneNumber, "")==0)
            {
                strcpy(telephoneNumber, addressBook->personals[indexes[index]].telephoneNumber);
            }
            printf("     이메일주소 : %s ", addressBook->personals[indexes[index]].emailAddress); rewind(stdin); gets(emailAddress);
            if (strcmp(emailAddress,"")==0)
            {
                strcpy(emailAddress, addressBook->personals[indexes[index]].emailAddress);
            }
            printf("     ---------------------------------------------------------------------------------\n");
            printf("     고치시겠습니까?(Yes/No) ");rewind(stdin);correcting = getchar();
            if (correcting == 'Y' || correcting == 'y')
            {
                index = indexes[index];
                index = Correct(addressBook, index, address, telephoneNumber, emailAddress);
                printf("     ==============================================================================\n");
                printf("     번호  성명\t주소\t\t전화번호\t이메일주소\n");
                printf("     ------------------------------------------------------------------------------\n");
                printf("     %d  %s\t%s\t\t%s\t%s\n", index + 1, addressBook->personals[index].name,
                    addressBook->personals[index].address, addressBook->personals[index].telephoneNumber,
                    addressBook->personals[index].emailAddress);
            }
        }
        printf("     ======================================================================================\n");
        printf("     계속하시겠습니까?(Yes/No) "); rewind(stdin); going = getchar();
    }
}

void FormFoErasing(AddressBook* addressBook) {
    char name[11];
    Long indexes[MAX];
    Long count;
    Long index;
    char erasing;
    char going = 'Y';

    while (going=='Y' || going=='y')
    {
        system("cls");//clear Screen
        printf("\n\n\n\n\n\n\n\n\n");
        printf("     주소록version-지우기\n");
        printf("     ================================================================================\n");
        printf("     성명 : "); rewind(stdin); scanf("%s", name);
        printf("     ================================================================================\n");
        printf("     번호  성명\t주소\t\t전화번호\t이메일주소\n");
        printf("     --------------------------------------------------------------------------------\n");
        Find(addressBook, name, indexes, &count);
        index = 0;
        while (index < count)
        {
            printf("     %d  %s\t%s\t\t%s\t%s\n", index + 1, addressBook->personals[indexes[index]].name,
                addressBook->personals[indexes[index]].address, addressBook->personals[indexes[index]].telephoneNumber,
                addressBook->personals[indexes[index]].emailAddress);
            index++;
        }
        if (count>0)
        {
            printf("     ================================================================================\n");
            printf("     번호 : ");rewind(stdin);scanf("%d", &index);
            printf("     --------------------------------------------------------------------------------\n");
            index = index - 1;
            printf("     번호  성명\t주소\t\t전화번호\t이메일주소\n");
            printf("     --------------------------------------------------------------------------------\n");
            printf("     %d  %s\t%s\t\t%s\t%s\n", indexes[index]+1, addressBook->personals[indexes[index]].name,
                addressBook->personals[indexes[index]].address, addressBook->personals[indexes[index]].telephoneNumber,
                addressBook->personals[indexes[index]].emailAddress);
            printf("     ================================================================================\n");
            printf("     지우시겠습니까?(Yes/No) "); rewind(stdin); erasing = getchar();
            if (erasing=='Y' || erasing=='y')
            {
                index = indexes[index];
                index = Erase(addressBook, index);
                printf("     --------------------------------------------------------------------------------\n");
                printf("     지워졌습니다.\n");
            }
        }
        printf("     ================================================================================\n");
        printf("     계속하시겠습니까?(Yes/No) "); rewind(stdin); going = getchar();
    }
}

void FormFoArranging(AddressBook* addressBook) {
    Long index = 0;
    Long i;

    Arrange(addressBook);

    while (index<addressBook->length)
    {
        system("cls");//clear Screen
        printf("\n\n\n\n\n\n\n\n\n");
        printf("     주소록version-정리하기\n");
        printf("     ================================================================================\n");
        printf("     번호  성명\t주소\t\t전화번호\t이메일주소\n");
        printf("     --------------------------------------------------------------------------------\n");
        i = 1;
        while (i<=5 && index<addressBook->length)
        {
            printf("     %d  %s\t%s\t\t%s\t%s\n", index + 1, addressBook->personals[index].name,
                addressBook->personals[index].address, addressBook->personals[index].telephoneNumber,
                addressBook->personals[index].emailAddress);
            index++;
            i++;
        }
        printf("     ================================================================================\n");
        printf("     아무 키나 누르세요!"); rewind(stdin); getchar();
    }
}

void FormFoViewingAll(AddressBook* addressBook) {
    Long index = 0;
    Long i;

    while (index<addressBook->length)
    {
        system("cls");//clear Screen
        printf("\n\n\n\n\n\n\n\n\n");
        printf("     주소록version0.05-전체보기\n");
        printf("     ==============================================================================\n");
        printf("     번호  성명\t주소\t\t전화번호\t이메일주소\n");
        printf("     ------------------------------------------------------------------------------\n");
        i = 1;
        while (i<=5 && index<addressBook->length)
        {
            printf("     %d  %s\t%s\t\t%s\t%s\n", index + 1, addressBook->personals[index].name,
                addressBook->personals[index].address, addressBook->personals[index].telephoneNumber,
                addressBook->personals[index].emailAddress);
            index++;
            i++;
        }
        printf("     ================================================================================\n");
        printf("     아무 키나 누르세요!"); rewind(stdin); getchar();
    }
}