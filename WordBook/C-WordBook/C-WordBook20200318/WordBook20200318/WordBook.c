#include "WordBook.h"
#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	WordBook wordBook = { {{"", "", "", ""}, {"", "", "", ""},{ "", "", "", ""}, {"", "", "", ""},
						{"", "", "", ""}, {"", "", "", ""}}, MAX, 0 };
	Long index;
	Long indexes[MAX];
	Long count;

	//메인함수 테스트 시나리오

	//Load
	Load(&wordBook);
	//1. kind, 형용사, 친절한, You are so kind.를 기재한다.
	index = Record(&wordBook, "kind", "형용사", "친절한", "You are so kind.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		    wordBook.words[index].meanings, wordBook.words[index].example);
	//2. apple, 명사, 사과, An apple is delicious.를 기재한다.
	index = Record(&wordBook, "apple", "명사", "사과", "An apple is delicious.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		   wordBook.words[index].meanings, wordBook.words[index].example);
	//3. very, 부사, 매우, He is very tall.를 기재한다.
	index = Record(&wordBook, "very", "부사", "매우", "He is very tall.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		   wordBook.words[index].meanings, wordBook.words[index].example);
	//4. kind, 명사, 종류, What kind of movie do you like?을 기재한다.
	index = Record(&wordBook, "kind", "명사", "종류", "What kind of movie do you like?");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		   wordBook.words[index].meanings, wordBook.words[index].example);
	//5. kind를 찾는다.
	FindBySpellings(&wordBook, "kind", indexes, &count);
	index = 0;
	while (index<count)
	{
		printf("%s %s %s %s\n", wordBook.words[indexes[index]].spellings, 
			wordBook.words[indexes[index]].partOfSpeech, wordBook.words[indexes[index]].meanings,
			wordBook.words[indexes[index]].example);
		index++;
	}
	//6. "매우"를 찾는다
	FindByMeanings(&wordBook, "매우", indexes, &count);
	index = 0;
	while (index < count)
	{
		printf("%s %s %s %s\n", wordBook.words[indexes[index]].spellings,
			wordBook.words[indexes[index]].partOfSpeech, wordBook.words[indexes[index]].meanings,
			wordBook.words[indexes[index]].example);
		index++;
	}
	//7. 네번째 kind의 예시를 고친다.
	index = Correct(&wordBook, 3, "We serve two kind of tea.");
	printf("%d %s %s %s %s\n", index, wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//8. apple을 지운다.
	index = Erase(&wordBook, 1);
	if (index==-1)
	{
		printf("지워졌습니다.\n");
	}
	//9. try, 동사, 노력하다, I try to study hard.를 기재한다.
	index = Record(&wordBook, "try", "동사", "노력하다", "I try to study hard.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//10.정리한다.
	Arrange(&wordBook);
	index = 0;
	while (index<wordBook.length)
	{
		printf("%d %s %s %s %s\n", index+1, wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
			wordBook.words[index].meanings, wordBook.words[index].example);
		index++;
	}
	//Save
	Save(&wordBook);

	return 0;
}

//Load
Long Load(WordBook* wordBook)
{
	Word word;
	Long i = 0;

	int flag;
	FILE* file;

	file = fopen("WordBook.dat", "rb");
	if (file != NULL)
	{
		//1.1 철자, 품사, 의미, 예시를 입력받는다.
		flag = fread(&word, sizeof(Word), 1, file);
		//1. 파일의 끝이 아닌동안 반복한다.
		while (!feof(file) && flag != 0)
		{
			//1.2 단어배열에 저장한다.
			wordBook->words[i] = word;
			wordBook->length++;
			i++;
			//1.1 철자, 품사, 의미, 예시를 입력한다.
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	//2. 개수를 출력한다.
	return wordBook->length;
	//3. 끝내다.
}

//Record
Long Record(WordBook* wordBook, char(*spellings), char(*partOfSpeech), char(*meanings), char(*example))
{
	Long index = -1;
	Long i = 0;
	//1. 철자, 품사, 의미, 예시를 입력한다.
	//2. 빈 줄을 찾는다.
	while (i<wordBook->capacity && strcmp(wordBook->words[i].spellings, "")!=0)
	{
		i++;
	}
	//3. 빈 줄에 적는다.
	if (i<wordBook->capacity)
	{
		index = i;
		strcpy(wordBook->words[index].spellings, spellings);
		strcpy(wordBook->words[index].partOfSpeech, partOfSpeech);
		strcpy(wordBook->words[index].meanings, meanings);
		strcpy(wordBook->words[index].example, example);
		wordBook->length++;
	}
	//4. 위치를 출력한다.
	return index;
	//5 끝내다.
}

//FindBySpellings
void FindBySpellings(WordBook* wordBook, char(*spellings), Long(*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;
	
	*count = 0;
	
	//1. 철자를 입력받는다.
	//2. length만큼 반복한다.
	while (i<wordBook->length)
	{
		//2.1 철자가 서로 같으면
		if (strcmp(wordBook->words[i].spellings, spellings)==0)
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

//FindByMeanings
void FindByMeanings(WordBook* wordBook, char(*meanings), Long(*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;

	*count = 0;

	//1. 의미를 입력받는다.
	//2. length만큼 반복한다.
	while (i < wordBook->length)
	{
		//2.1 의미가 서로 같으면
		if (strcmp(wordBook->words[i].meanings, meanings) == 0)
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

//Correct
Long Correct(WordBook* wordBook, Long index, char(*example))
{
	//1. 위치, 예시를 입력받는다.
	//2. 위치에 적는다.
	strcpy(wordBook->words[index].example, example);
	//3. 위치를 출력한다.
	return index;
	//4. 끝내다.
}

//Erase
Long Erase(WordBook* wordBook, Long index)
{
	//1. 위치를 입력받는다.
	//2. 위치를 지운다.
	strcpy(wordBook->words[index].spellings, "X");
	index = -1;
	//3. 위치를 출력한다.
	return index;
	//4. 끝내다.
}

//Arrange
void Arrange(WordBook* wordBook)
{
	Long count = 0;
	Long i = wordBook->length - 1;
	Long j;
	Word word;

	//1. 내림차순으로 정렬한다.
	while (i>=0)
	{
		j = 0;
		while (j<i)
		{
			if (strcmp(wordBook->words[j].spellings, wordBook->words[j + 1].spellings) < 0)
			{
				word = wordBook->words[j];
				wordBook->words[j] = wordBook->words[j + 1];
				wordBook->words[j + 1] = word;
			}
			j++;
		}
		i--;
	}
	//2. 개수를 센다.
	i = 0;
	while (i<wordBook->length && strcmp(wordBook->words[i].spellings, "X")!=0)
	{
		count++;
		i++;
	}
	//3. 개수 안에서 오름차순으로 정렬한다.
	i = count - 1;
	while (i>=0)
	{
		j = 0;
		while (j<i)
		{
			if (strcmp(wordBook->words[j].spellings, wordBook->words[j + 1].spellings) > 0)
			{
				word = wordBook->words[j];
				wordBook->words[j] = wordBook->words[j + 1];
				wordBook->words[j + 1] = word;
			}
			j++;
		}
		i--;
	}
}

//Save
Long Save(WordBook* wordBook)
{
	Long i = 0;

	FILE* file;

	file = fopen("WordBook.dat", "wb");
	if (file != NULL)
	{
		//1. length만큼 반복한다.
		while (i<wordBook->length)
		{
			//1.1 철자, 품사, 의미, 예시를 출력한다.
			fwrite(wordBook->words + i, sizeof(Word), 1, file);
			i++;
		}
		fclose(file);
	}
	//2. 개수를 출력한다.
	return wordBook->length;
	//3. 끝내다.
}