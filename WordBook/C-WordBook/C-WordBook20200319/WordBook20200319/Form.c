#include "Form.h"
#include "WordBook.h"
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)

int main(int argc, char* argv[])
{
	//��뷮��ŭ ����ؼ� �ʱ�ȭ �����־�� ��. �׷��� Record�Լ����� ��ĭ�� �ν��ؼ� ������ �� ����.
	WordBook wordBook = { {{"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""},
						{"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""}, {"", "", "", ""},
						 {"", "", "", ""}, {"", "", "", ""}}, MAX, 0 };
	int menu;

	Load(&wordBook);
	DisplayMenu();
	rewind(stdin);scanf("%d", &menu);
	while (menu!=0)
	{
		switch (menu)
		{
		case 1:FormFoRecording(&wordBook); break;
		case 2:DisplayFindMenu(&wordBook); break;
		case 3:FormFoCorrecting(&wordBook); break;
		case 4:FormFoErasing(&wordBook); break;
		case 5:FormFoArranging(&wordBook); break;
		case 6:FormFoViewingAll(&wordBook); break;
		}
		DisplayMenu();
		rewind(stdin);scanf("%d", &menu);
	}
	Save(&wordBook);
	return 0;

}

//DisPlayMenu
void DisplayMenu()
{
	system("cls");//clear Screen
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t�ܾ���version0.05-�޴�\n");
	printf("\t\t\t\t\t======================\n");
	printf("\t\t\t\t\t[1] �����ϱ�\n");
	printf("\t\t\t\t\t[2] ã    ��\n");
	printf("\t\t\t\t\t[3] �� ġ ��\n");
	printf("\t\t\t\t\t[4] �� �� ��\n");
	printf("\t\t\t\t\t[5] �����ϱ�\n");
	printf("\t\t\t\t\t[6] ��ü����\n");
	printf("\t\t\t\t\t[0] �� �� ��\n");
	printf("\t\t\t\t\t----------------------\n");
	printf("\t\t\t\t\t�޴��� �����Ͻʽÿ�! ");
}

//FormFoRecording
void FormFoRecording(WordBook *wordBook)
{
	char spellings[64];
	char partOfSpeech[8];
	char partOfSpeechs[8][8] = {
		"���",
		"����",
		"����",
		"�����",
		"�λ�",
		"��ġ��",
		"���ӻ�",
		"��ź��"
	};
	char meanings[32];
	char example[128];
	char recording;
	char going = 'Y';
	Long index;
	int choice;

	while (going=='Y' || going=='y')
	{
		system("cls");//clear Screen
		printf("\n\n\n\n\n\n");
		printf("\t�ܾ���version0.05-�����ϱ�\n");
		printf("\t=======================================================================\n");
		printf("\tö�� : ");rewind(stdin);scanf("%s", spellings);
		printf("\tǰ�� : 1.��� 2.���� 3.���� 4.����� 5.�λ� 6.��ġ�� 7.���ӻ� 8.��ź�� ");
		rewind(stdin); scanf("%d", &choice);
		choice--;
		strcpy(partOfSpeech, partOfSpeechs[choice]);
		printf("\t�ǹ� : "); rewind(stdin); scanf("%s", meanings);
		printf("\t���� : "); rewind(stdin); gets(example);
		printf("\t------------------------------------------------------------------------\n");
		printf("\t�����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); recording = getchar();
		if (recording == 'Y' || recording == 'y')
		{
			index = Record(wordBook, spellings, partOfSpeech, meanings, example);
			printf("\t=======================================================================\n");
			printf("\t��ȣ  ö��\tǰ��    �ǹ�\t����\n");
			printf("\t-----------------------------------------------------------------------\n");
			printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[index].spellings,
				wordBook->words[index].partOfSpeech, wordBook->words[index].meanings,
				wordBook->words[index].example);
		}
		printf("\t============================================================================\n");
		printf("\t����Ͻðڽ��ϱ�(Yes/No) "); rewind(stdin); going = getchar();
	}
}

//DisplayFindMenu
void DisplayFindMenu(WordBook* wordBook)
{
	int menu;

	system("cls");//clear Screen
	printf("\n\n\n\n\n\n\n\n");
	printf("\t�ܾ���version0.05-ã��\n");
	printf("\t=======================================================================\n");
	printf("\t[1] ö�ڷ� ã��\n");
	printf("\t[2] �ǹ̷� ã��\n");
	printf("\t[0] �� �� �� ��\n");
	printf("\t-----------------------------------------------------------------------\n");
	printf("\t�޴��� �����Ͻʽÿ�! ");rewind(stdin); scanf("%d", &menu);
	while (menu!=0)
	{
		switch (menu)
		{
		case 1:FormFoFindingBySpellings(wordBook);break;
		case 2:FormFoFindingByMeanings(wordBook);break;
		default:break;
		}
		system("cls");//clear Screen
		printf("\n\n\n\n\n\n\n\n");
		printf("\t�ܾ���version0.05-ã��\n");
		printf("\t=======================================================================\n");
		printf("\t[1] ö�ڷ� ã��\n");
		printf("\t[2] �ǹ̷� ã��\n");
		printf("\t[0] �� �� �� ��\n");
		printf("\t-----------------------------------------------------------------------\n");
		printf("\t�޴��� �����Ͻʽÿ�! ");rewind(stdin); scanf("%d", &menu);
	}
}

//FormFoFindBySpellings
void FormFoFindingBySpellings(WordBook* wordBook)
{
	char spellings[64];
	Long indexes[MAX];
	Long count;
	char going = 'Y';
	Long index;

	while (going == 'Y' || going == 'y')
	{
		system("cls");//clear Screen
		printf("\n\n\n\n\n\n");
		printf("\t�ܾ���version0.05-ö�ڷ� ã��\n");
		printf("\t=======================================================================\n");
		printf("\tö�� : "); rewind(stdin); scanf("%s", spellings);
		printf("\t=======================================================================\n");
		printf("\t��ȣ  ö��\tǰ��    �ǹ�\t����\n");
		printf("\t-----------------------------------------------------------------------\n");
		FindBySpellings(wordBook, spellings, indexes, &count);
		index = 0;
		while (index < count)
		{
			printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[indexes[index]].spellings,
				wordBook->words[indexes[index]].partOfSpeech, wordBook->words[indexes[index]].meanings,
				wordBook->words[indexes[index]].example);
			index++;
		}
		printf("\t=======================================================================\n");
		printf("\t����Ͻðڽ��ϱ�?(Yes/No) ");rewind(stdin);going = getchar();
	}
}

//FormFoFindingByMeanings
void FormFoFindingByMeanings(WordBook* wordBook)
{
	char meanings[32];
	Long indexes[MAX];
	Long count;
	char going = 'Y';
	Long index;

	while (going == 'Y' || going == 'y')
	{
		system("cls");//clear Screen
		printf("\n\n\n\n\n\n");
		printf("\t�ܾ���version0.05-�ǹ̷� ã��\n");
		printf("\t=======================================================================\n");
		printf("\t�ǹ� : "); rewind(stdin); scanf("%s", meanings);
		printf("\t=======================================================================\n");
		printf("\t��ȣ  �ǹ�\tö��    ǰ��\t����\n");
		printf("\t-----------------------------------------------------------------------\n");
		FindByMeanings(wordBook, meanings, indexes, &count);
		index = 0;
		while (index < count)
		{
			printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[indexes[index]].meanings,
				wordBook->words[indexes[index]].spellings, wordBook->words[indexes[index]].partOfSpeech,
				wordBook->words[indexes[index]].example);
			index++;
		}
		printf("\t=======================================================================\n");
		printf("\t����Ͻðڽ��ϱ�?(Yes/No) ");rewind(stdin);going = getchar();
	}

}

//FormFoCorrecting
void FormFoCorrecting(WordBook* wordBook)
{
	char spellings[64];
	Long indexes[MAX];
	Long count;
	Long index;
	char example[128];
	char correcting;
	char going = 'Y';

	while (going=='Y' || going=='y')
	{
		system("cls");//clear Screen
		printf("\n\n\n\n\n\n");
		printf("\t�ܾ���version0.05-��ġ��\n");
		printf("\t=======================================================================\n");
		printf("\tö�� : "); rewind(stdin); scanf("%s", spellings);
		printf("\t=======================================================================\n");
		printf("\t��ȣ  ö��\tǰ��    �ǹ�\t����\n");
		printf("\t-----------------------------------------------------------------------\n");
		FindBySpellings(wordBook, spellings, indexes, &count);
		index = 0;
		while (index < count)
		{
			printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[indexes[index]].spellings,
				wordBook->words[indexes[index]].partOfSpeech, wordBook->words[indexes[index]].meanings,
				wordBook->words[indexes[index]].example);
			index++;
		}
		if (count > 0)
		{
			printf("\t=======================================================================\n");
			printf("\t��ȣ : ");rewind(stdin);scanf("%d", &index);
			index--;
			printf("\t=======================================================================\n");
			printf("\t���� : %s ", wordBook->words[indexes[index]].example);rewind(stdin);gets(example);
			if (strcmp(example, "") == 0)
			{
				strcpy(example, wordBook->words[indexes[index]].example);
			}
			printf("\t-----------------------------------------------------------------------\n");
			printf("\t��ġ�ðڽ��ϱ�?(Yes/No) ");rewind(stdin);correcting = getchar();
			if (correcting == 'Y' || correcting == 'y')
			{
				index = indexes[index];
				index = Correct(wordBook, index, example);
				printf("\t=======================================================================\n");
				printf("\t��ȣ  ö��\tǰ��    �ǹ�\t����\n");
				printf("\t-----------------------------------------------------------------------\n");
				printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[index].spellings,
					wordBook->words[index].partOfSpeech, wordBook->words[index].meanings,
					wordBook->words[index].example);
			}
		}
		printf("\t=======================================================================\n");
		printf("\t����Ͻðڽ��ϱ�?(Yes/No) ");rewind(stdin);going = getchar();
	}
}

//FormFoErasing
void FormFoErasing(WordBook* wordBook)
{
	char spellings[64];
	Long indexes[MAX];
	Long count;
	Long index;
	char erasing;
	char going = 'Y';

	while (going == 'Y' || going == 'y')
	{
		system("cls");//clear Screen
		printf("\n\n\n\n\n\n");
		printf("\t�ܾ���version0.05-�����\n");
		printf("\t=======================================================================\n");
		printf("\tö�� : "); rewind(stdin); scanf("%s", spellings);
		printf("\t=======================================================================\n");
		printf("\t��ȣ  ö��\tǰ��    �ǹ�\t����\n");
		printf("\t-----------------------------------------------------------------------\n");
		FindBySpellings(wordBook, spellings, indexes, &count);
		index = 0;
		while (index < count)
		{
			printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[indexes[index]].spellings,
				wordBook->words[indexes[index]].partOfSpeech, wordBook->words[indexes[index]].meanings,
				wordBook->words[indexes[index]].example);
			index++;
		}
		if (count > 0)
		{
			printf("\t=======================================================================\n");
			printf("\t��ȣ : ");rewind(stdin);scanf("%d", &index);
			index--;
			printf("\t=======================================================================\n");
			printf("\t��ȣ  ö��\tǰ��    �ǹ�\t����\n");
			printf("\t-----------------------------------------------------------------------\n");
			printf("\t%d  %s\t%s    %s\t%s\n", indexes[index]+1, wordBook->words[indexes[index]].spellings,
				wordBook->words[indexes[index]].partOfSpeech, wordBook->words[indexes[index]].meanings,
				wordBook->words[indexes[index]].example);
			printf("\t-----------------------------------------------------------------------\n");
			printf("\t����ðڽ��ϱ�?(Yes/No) "); rewind(stdin); erasing = getchar();
			if (erasing=='Y' || erasing=='y')
			{
				index = indexes[index];
				index = Erase(wordBook, index);
				printf("\t-----------------------------------------------------------------------\n");
				printf("\t���������ϴ�.\n");
			}
		}
		printf("\t=======================================================================\n");
		printf("\t����Ͻðڽ��ϱ�?(Yes/No) ");rewind(stdin);going = getchar();
	}
}

//FormFoArranging
void FormFoArranging(WordBook* wordBook)
{
	Long index = 0;
	Long i;

	Arrange(wordBook);

	while (index < wordBook->length)
	{
		system("cls");//clear Screen
		printf("\n\n\n\n\n\n\n\n");
		printf("\t�ܾ���version0.05-��ü����\n");
		printf("\t=======================================================================\n");
		printf("\t��ȣ  ö��\tǰ��    �ǹ�\t����\n");
		printf("\t-----------------------------------------------------------------------\n");
		i = 1;
		while (i <= 5 && index < wordBook->length)
		{
			printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[index].spellings,
				wordBook->words[index].partOfSpeech, wordBook->words[index].meanings,
				wordBook->words[index].example);
			index++;
			i++;
		}
		printf("\t=======================================================================\n");
		printf("\t�ƹ� Ű�� ��������!"); rewind(stdin); getchar();
	}
}

//FormFoViewingAll
void FormFoViewingAll(WordBook* wordBook)
{
	Long index = 0;
	Long i;

	while (index < wordBook->length)
	{
		system("cls");//clear Screen
		printf("\n\n\n\n\n\n\n\n");
		printf("\t�ܾ���version0.05-��ü����\n");
		printf("\t=======================================================================\n");
		printf("\t��ȣ  ö��\tǰ��    �ǹ�\t����\n");
		printf("\t-----------------------------------------------------------------------\n");
		i = 1;
		while (i<=5 && index < wordBook->length)
		{
			printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[index].spellings,
				wordBook->words[index].partOfSpeech, wordBook->words[index].meanings,
				wordBook->words[index].example);
			index++;
			i++;
		}
		printf("\t=======================================================================\n");
		printf("\t�ƹ� Ű�� ��������!"); rewind(stdin); getchar();
	}
}
