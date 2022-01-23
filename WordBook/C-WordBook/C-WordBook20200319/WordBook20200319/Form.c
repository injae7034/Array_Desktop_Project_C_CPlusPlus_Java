#include "Form.h"
#include "WordBook.h"
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)

int main(int argc, char* argv[])
{
	//사용량만큼 계속해서 초기화 시켜주어야 함. 그래야 Record함수에서 빈칸을 인식해서 기재할 수 있음.
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
	printf("\t\t\t\t\t단어장version0.05-메뉴\n");
	printf("\t\t\t\t\t======================\n");
	printf("\t\t\t\t\t[1] 기재하기\n");
	printf("\t\t\t\t\t[2] 찾    기\n");
	printf("\t\t\t\t\t[3] 고 치 기\n");
	printf("\t\t\t\t\t[4] 지 우 기\n");
	printf("\t\t\t\t\t[5] 정리하기\n");
	printf("\t\t\t\t\t[6] 전체보기\n");
	printf("\t\t\t\t\t[0] 끝 내 기\n");
	printf("\t\t\t\t\t----------------------\n");
	printf("\t\t\t\t\t메뉴를 선택하십시오! ");
}

//FormFoRecording
void FormFoRecording(WordBook *wordBook)
{
	char spellings[64];
	char partOfSpeech[8];
	char partOfSpeechs[8][8] = {
		"명사",
		"대명사",
		"동사",
		"형용사",
		"부사",
		"전치사",
		"접속사",
		"감탄사"
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
		printf("\t단어장version0.05-기재하기\n");
		printf("\t=======================================================================\n");
		printf("\t철자 : ");rewind(stdin);scanf("%s", spellings);
		printf("\t품사 : 1.명사 2.대명사 3.동사 4.형용사 5.부사 6.전치사 7.접속사 8.감탄사 ");
		rewind(stdin); scanf("%d", &choice);
		choice--;
		strcpy(partOfSpeech, partOfSpeechs[choice]);
		printf("\t의미 : "); rewind(stdin); scanf("%s", meanings);
		printf("\t예시 : "); rewind(stdin); gets(example);
		printf("\t------------------------------------------------------------------------\n");
		printf("\t기재하시겠습니까?(Yes/No) "); rewind(stdin); recording = getchar();
		if (recording == 'Y' || recording == 'y')
		{
			index = Record(wordBook, spellings, partOfSpeech, meanings, example);
			printf("\t=======================================================================\n");
			printf("\t번호  철자\t품사    의미\t예시\n");
			printf("\t-----------------------------------------------------------------------\n");
			printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[index].spellings,
				wordBook->words[index].partOfSpeech, wordBook->words[index].meanings,
				wordBook->words[index].example);
		}
		printf("\t============================================================================\n");
		printf("\t계속하시겠습니까(Yes/No) "); rewind(stdin); going = getchar();
	}
}

//DisplayFindMenu
void DisplayFindMenu(WordBook* wordBook)
{
	int menu;

	system("cls");//clear Screen
	printf("\n\n\n\n\n\n\n\n");
	printf("\t단어장version0.05-찾기\n");
	printf("\t=======================================================================\n");
	printf("\t[1] 철자로 찾기\n");
	printf("\t[2] 의미로 찾기\n");
	printf("\t[0] 상 위 메 뉴\n");
	printf("\t-----------------------------------------------------------------------\n");
	printf("\t메뉴를 선택하십시오! ");rewind(stdin); scanf("%d", &menu);
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
		printf("\t단어장version0.05-찾기\n");
		printf("\t=======================================================================\n");
		printf("\t[1] 철자로 찾기\n");
		printf("\t[2] 의미로 찾기\n");
		printf("\t[0] 상 위 메 뉴\n");
		printf("\t-----------------------------------------------------------------------\n");
		printf("\t메뉴를 선택하십시오! ");rewind(stdin); scanf("%d", &menu);
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
		printf("\t단어장version0.05-철자로 찾기\n");
		printf("\t=======================================================================\n");
		printf("\t철자 : "); rewind(stdin); scanf("%s", spellings);
		printf("\t=======================================================================\n");
		printf("\t번호  철자\t품사    의미\t예시\n");
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
		printf("\t계속하시겠습니까?(Yes/No) ");rewind(stdin);going = getchar();
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
		printf("\t단어장version0.05-의미로 찾기\n");
		printf("\t=======================================================================\n");
		printf("\t의미 : "); rewind(stdin); scanf("%s", meanings);
		printf("\t=======================================================================\n");
		printf("\t번호  의미\t철자    품사\t예시\n");
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
		printf("\t계속하시겠습니까?(Yes/No) ");rewind(stdin);going = getchar();
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
		printf("\t단어장version0.05-고치기\n");
		printf("\t=======================================================================\n");
		printf("\t철자 : "); rewind(stdin); scanf("%s", spellings);
		printf("\t=======================================================================\n");
		printf("\t번호  철자\t품사    의미\t예시\n");
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
			printf("\t번호 : ");rewind(stdin);scanf("%d", &index);
			index--;
			printf("\t=======================================================================\n");
			printf("\t예시 : %s ", wordBook->words[indexes[index]].example);rewind(stdin);gets(example);
			if (strcmp(example, "") == 0)
			{
				strcpy(example, wordBook->words[indexes[index]].example);
			}
			printf("\t-----------------------------------------------------------------------\n");
			printf("\t고치시겠습니까?(Yes/No) ");rewind(stdin);correcting = getchar();
			if (correcting == 'Y' || correcting == 'y')
			{
				index = indexes[index];
				index = Correct(wordBook, index, example);
				printf("\t=======================================================================\n");
				printf("\t번호  철자\t품사    의미\t예시\n");
				printf("\t-----------------------------------------------------------------------\n");
				printf("\t%d  %s\t%s    %s\t%s\n", index + 1, wordBook->words[index].spellings,
					wordBook->words[index].partOfSpeech, wordBook->words[index].meanings,
					wordBook->words[index].example);
			}
		}
		printf("\t=======================================================================\n");
		printf("\t계속하시겠습니까?(Yes/No) ");rewind(stdin);going = getchar();
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
		printf("\t단어장version0.05-지우기\n");
		printf("\t=======================================================================\n");
		printf("\t철자 : "); rewind(stdin); scanf("%s", spellings);
		printf("\t=======================================================================\n");
		printf("\t번호  철자\t품사    의미\t예시\n");
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
			printf("\t번호 : ");rewind(stdin);scanf("%d", &index);
			index--;
			printf("\t=======================================================================\n");
			printf("\t번호  철자\t품사    의미\t예시\n");
			printf("\t-----------------------------------------------------------------------\n");
			printf("\t%d  %s\t%s    %s\t%s\n", indexes[index]+1, wordBook->words[indexes[index]].spellings,
				wordBook->words[indexes[index]].partOfSpeech, wordBook->words[indexes[index]].meanings,
				wordBook->words[indexes[index]].example);
			printf("\t-----------------------------------------------------------------------\n");
			printf("\t지우시겠습니까?(Yes/No) "); rewind(stdin); erasing = getchar();
			if (erasing=='Y' || erasing=='y')
			{
				index = indexes[index];
				index = Erase(wordBook, index);
				printf("\t-----------------------------------------------------------------------\n");
				printf("\t지워졌습니다.\n");
			}
		}
		printf("\t=======================================================================\n");
		printf("\t계속하시겠습니까?(Yes/No) ");rewind(stdin);going = getchar();
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
		printf("\t단어장version0.05-전체보기\n");
		printf("\t=======================================================================\n");
		printf("\t번호  철자\t품사    의미\t예시\n");
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
		printf("\t아무 키나 누르세요!"); rewind(stdin); getchar();
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
		printf("\t단어장version0.05-전체보기\n");
		printf("\t=======================================================================\n");
		printf("\t번호  철자\t품사    의미\t예시\n");
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
		printf("\t아무 키나 누르세요!"); rewind(stdin); getchar();
	}
}
