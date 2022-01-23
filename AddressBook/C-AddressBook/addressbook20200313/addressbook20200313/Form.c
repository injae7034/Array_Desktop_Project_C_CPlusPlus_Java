#include "Form.h"
#include "AddressBook.h"
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)

int main(int argc, char* argv[]) {
    AddressBook addressBook = { {{"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""},
                                  {"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""}}, MAX, 0 };
    
    int menu;

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
    
    return 0;

  }

void DisplayMenu() {
    system("cls");//clear Screen
    printf("\n\n\n\n\n\n\n\n\n");
    printf("     \t\t\t\t\t\t�ּҷ�version0.05\n");
    printf("     \t\t\t\t\t\t====================\n");
    printf("     \t\t\t\t\t\t[1] �����ϱ�\n");
    printf("     \t\t\t\t\t\t[2] ã    ��\n");
    printf("     \t\t\t\t\t\t[3] �� ġ ��\n");
    printf("     \t\t\t\t\t\t[4] �� �� ��\n");
    printf("     \t\t\t\t\t\t[5] �����ϱ�\n");
    printf("     \t\t\t\t\t\t[6] ��ü����\n");
    printf("     \t\t\t\t\t\t[0] �� �� ��\n");
    printf("     \t\t\t\t\t\t--------------------\n");
    printf("     \t\t\t\t\t\t�޴��� �����Ͻʽÿ�! ");
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
        printf("     \t\t\t�ּҷ�version0.05-�����ϱ�\n");
        printf("     \t\t\t==============================================\n");
        printf("     \t\t\t��      �� : "); rewind(stdin); scanf("%s", name);
        printf("     \t\t\t��      �� : "); rewind(stdin); gets(address);
        printf("     \t\t\t��ȭ  ��ȣ : "); rewind(stdin); scanf("%s", telephoneNumber);
        printf("     \t\t\t�̸����ּ� : "); rewind(stdin); scanf("%s", emailAddress);
        printf("     \t\t\t----------------------------------------------\n");
        printf("     \t\t\t�����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); recording = getchar();

        if (recording=='Y' || recording=='y')
        {
            index = Record(addressBook, name, address, telephoneNumber, emailAddress);
            printf("     \t\t\t========================================================================\n");
            printf("     \t\t\t��ȣ  ����\t�ּ�\t\t��ȭ��ȣ\t�̸����ּ�\n");
            printf("     \t\t\t------------------------------------------------------------------------\n");
            printf("     \t\t\t%d  %s\t%s\t\t%s\t%s\n", index+1, addressBook->personals[index].name,
                         addressBook->personals[index].address, addressBook->personals[index].telephoneNumber,
                         addressBook->personals[index].emailAddress);
        }
        printf("     \t\t\t============================================================================\n");
        printf("     \t\t\t����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); going = getchar();
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
        printf("     �ּҷ�version0.05-ã��\n");
        printf("     ================================================================================\n");
        printf("     ���� : "); rewind(stdin); scanf("%s", name);
        printf("     ================================================================================\n");
        printf("     ��ȣ  ����\t�ּ�\t\t��ȭ��ȣ\t�̸����ּ�\n");
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
        printf("     ����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); going = getchar();
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
        printf("     �ּҷ�version0.05-��ġ��\n");
        printf("     ====================================================================================\n");
        printf("     ���� : ");rewind(stdin);scanf("%s", name);
        printf("     =====================================================================================\n");
        printf("     ��ȣ  ����\t�ּ�\t\t��ȭ��ȣ\t�̸����ּ�\n");
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
            printf("     ��ȣ : ");rewind(stdin);scanf("%d", &index);
            printf("     --------------------------------------------------------------------------------\n");
            index = index - 1;
            printf("     ��      �� : %s ", addressBook->personals[indexes[index]].address); rewind(stdin); gets(address);
            if (strcmp(address, "")==0)
            {
                strcpy(address, addressBook->personals[indexes[index]].address);
            }
            printf("     ��ȭ  ��ȣ : %s ", addressBook->personals[indexes[index]].telephoneNumber); rewind(stdin); gets(telephoneNumber);
            if (strcmp(telephoneNumber, "")==0)
            {
                strcpy(telephoneNumber, addressBook->personals[indexes[index]].telephoneNumber);
            }
            printf("     �̸����ּ� : %s ", addressBook->personals[indexes[index]].emailAddress); rewind(stdin); gets(emailAddress);
            if (strcmp(emailAddress,"")==0)
            {
                strcpy(emailAddress, addressBook->personals[indexes[index]].emailAddress);
            }
            printf("     ---------------------------------------------------------------------------------\n");
            printf("     ��ġ�ðڽ��ϱ�?(Yes/No) ");rewind(stdin);correcting = getchar();
            if (correcting == 'Y' || correcting == 'y')
            {
                index = indexes[index];
                index = Correct(addressBook, index, address, telephoneNumber, emailAddress);
                printf("     ==============================================================================\n");
                printf("     ��ȣ  ����\t�ּ�\t\t��ȭ��ȣ\t�̸����ּ�\n");
                printf("     ------------------------------------------------------------------------------\n");
                printf("     %d  %s\t%s\t\t%s\t%s\n", index + 1, addressBook->personals[index].name,
                    addressBook->personals[index].address, addressBook->personals[index].telephoneNumber,
                    addressBook->personals[index].emailAddress);
            }
        }
        printf("     ======================================================================================\n");
        printf("     ����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); going = getchar();
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
        printf("     �ּҷ�version-�����\n");
        printf("     ================================================================================\n");
        printf("     ���� : "); rewind(stdin); scanf("%s", name);
        printf("     ================================================================================\n");
        printf("     ��ȣ  ����\t�ּ�\t\t��ȭ��ȣ\t�̸����ּ�\n");
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
            printf("     ��ȣ : ");rewind(stdin);scanf("%d", &index);
            printf("     --------------------------------------------------------------------------------\n");
            index = index - 1;
            printf("     ��ȣ  ����\t�ּ�\t\t��ȭ��ȣ\t�̸����ּ�\n");
            printf("     --------------------------------------------------------------------------------\n");
            printf("     %d  %s\t%s\t\t%s\t%s\n", indexes[index]+1, addressBook->personals[indexes[index]].name,
                addressBook->personals[indexes[index]].address, addressBook->personals[indexes[index]].telephoneNumber,
                addressBook->personals[indexes[index]].emailAddress);
            printf("     ================================================================================\n");
            printf("     ����ðڽ��ϱ�?(Yes/No) "); rewind(stdin); erasing = getchar();
            if (erasing=='Y' || erasing=='y')
            {
                index = indexes[index];
                index = Erase(addressBook, index);
                printf("     --------------------------------------------------------------------------------\n");
                printf("     ���������ϴ�.\n");
            }
        }
        printf("     ================================================================================\n");
        printf("     ����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); going = getchar();
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
        printf("     �ּҷ�version-�����ϱ�\n");
        printf("     ================================================================================\n");
        printf("     ��ȣ  ����\t�ּ�\t\t��ȭ��ȣ\t�̸����ּ�\n");
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
        printf("     �ƹ� Ű�� ��������!"); rewind(stdin); getchar();
    }
}

void FormFoViewingAll(AddressBook* addressBook) {
    Long index = 0;
    Long i;

    while (index<addressBook->length)
    {
        system("cls");//clear Screen
        printf("\n\n\n\n\n\n\n\n\n");
        printf("     �ּҷ�version0.05-��ü����\n");
        printf("     ==============================================================================\n");
        printf("     ��ȣ  ����\t�ּ�\t\t��ȭ��ȣ\t�̸����ּ�\n");
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
        printf("     �ƹ� Ű�� ��������!"); rewind(stdin); getchar();
    }
}