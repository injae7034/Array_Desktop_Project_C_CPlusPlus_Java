#include "WordBook.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	WordBook wordBook;
	Long index;
	Long(*indexes);
	Long count;

	//메인테스트 시나리오
	//1. capacity에 6을 입력한다.
	Create(&wordBook, 6);
	//Load
	Load(&wordBook);
	//2. kind, 형용사, 친절한, You are so kind.를 기재한다.
	index = Record(&wordBook, "kind", "형용사", "친절한", "You are so kind.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//3. apple, 명사, 사과, An apple is sweet.을 기재한다.
	index = Record(&wordBook, "apple", "명사", "사과", "An apple is sweet.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//4. kind, 명사, 종류, We serve two kinds of tea.를 기재한다.
	index = Record(&wordBook, "kind", "명사", "종류", "We serve two kinds of tea.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//5. very, 부사, 매우, He is very tall.을 기재한다.
	index = Record(&wordBook, "very", "부사", "매우", "He is very tall.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	printf("\n");
	//6. kind를 찾는다.
	FindBySpellings(&wordBook, "kind", &indexes, &count);
	index = 0;
	while (index < count)
	{
		printf("%s %s %s %s\n", wordBook.words[indexes[index]].spellings, wordBook.words[indexes[index]].partOfSpeech,
			wordBook.words[indexes[index]].meanings, wordBook.words[indexes[index]].example);
		index++;
	}
	//indexes배열을 할당해제한다.
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//7. extremely, 부사, 매우, The mountain is extremely high.를 기재한다.
	index = Record(&wordBook, "extremely", "부사", "매우", "The mountain is extremely high.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	printf("\n");
	//8. 매우를 찾는다.
	FindByMeanings(&wordBook, "매우", &indexes, &count);
	index = 0;
	while (index < count)
	{
		printf("%s %s %s %s\n", wordBook.words[indexes[index]].meanings, wordBook.words[indexes[index]].spellings,
			wordBook.words[indexes[index]].partOfSpeech, wordBook.words[indexes[index]].example);
		index++;
	}
	//indexes배열을 할당해제한다.
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//9. 첫 번째 kind의 예시를 고친다.
	index = Correct(&wordBook, 0, "It is kind for you to help me.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	printf("\n");
	//10. apple을 지운다.
	index = Erase(&wordBook, 1);
	if (index == -1)
	{
		printf("지워졌습니다.\n");
	}
	printf("\n");
	//11. 정리한다.
	Arrange(&wordBook);
	index = 0;
	while (index < wordBook.length)
	{
		printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
			wordBook.words[index].meanings, wordBook.words[index].example);
		index++;
	}
	//Save
	Save(&wordBook);
	//12. 할당해제한다.
	Destroy(&wordBook);

	return 0;
}

//Create
void Create(WordBook* wordBook, Long capacity)
{
	//1. capacity를 입력받는다.
	//2. 단어들 배열을 만든다.
	wordBook->words = (Word(*))calloc(capacity, sizeof(Word));
	//3. 할당량을 정한다.
	wordBook->capacity = capacity;
	//4. 사용량을 정한다.
	wordBook->length = 0;
	//5. 끝내다.
}

//Load
Long Load(WordBook* wordBook)
{
	Word word;
	Word(*words);
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
			//1.2 사용량이 할당량보다 크거나 같으면
			if (wordBook->length >= wordBook->capacity)
			{
				//1.2.1 새단어장을 만든다.
				words = (Word(*))calloc(wordBook->capacity + 1, sizeof(Word));
				//1.2.2 기존 내용을 옮겨적는다.
				i = 0;
				while (i < wordBook->length)
				{
					words[i] = wordBook->words[i];
					i++;
				}
				//1.2.3 기존 단어장을 지운다.
				if (wordBook->words != NULL)
				{
					free(wordBook->words);
				}
				wordBook->words = words;
				wordBook->capacity++;
			}
			//1.3 빈 줄에 적는다.
			wordBook->words[i] = word;
			wordBook->length++;
			i++;
			//1.1 철자, 품사, 의미, 예시를 입력받는다.
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	//2. 사용량을 출력한다.
	return wordBook->length;
	//3. 끝내다.
}

//Record
Long Record(WordBook* wordBook, char(*spellings), char(*partOfSpeech), char(*meanings), char(*example))
{
	Long index = -1;
	Word(*words);
	Long i;

	//1. 철자, 품사, 의미, 예시를 입력받는다.
	//2. 사용량이 할당량보다 크거나 같으면
	if (wordBook->length >= wordBook->capacity)
	{
		//2.1 새단어장을 만든다.
		words = (Word(*))calloc(wordBook->capacity + 1, sizeof(Word));
		//2.2 기존 단어장의 내용을 옮겨적는다.
		i = 0;
		while (i < wordBook->length)
		{
			words[i] = wordBook->words[i];
			i++;
		}
		//2.3 기존 단어장을 지운다.
		if (wordBook->words != NULL)
		{
			free(wordBook->words);
		}
		wordBook->words = words;
		wordBook->capacity++;
	}
	//3. 빈 줄에 적는다.
	index = wordBook->length;
	strcpy(wordBook->words[index].spellings, spellings);
	strcpy(wordBook->words[index].partOfSpeech, partOfSpeech);
	strcpy(wordBook->words[index].meanings, meanings);
	strcpy(wordBook->words[index].example, example);
	wordBook->length++;
	//4. 위치를 출력한다.
	return index;
	//5. 끝내다.
}

//FindBySpellings
void FindBySpellings(WordBook* wordBook, char(*spellings), Long* (*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;
	*count = 0;
	
	//1. 철자를 입력받는다.
	//2. 사용량보다 작거나 같은 동안 반복한다.
	while (i < wordBook->length)
	{
		//2.1 철자가 서로 같으면
		if (strcmp(wordBook->words[i].spellings, spellings) == 0)
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
	//4. 사용량보다 작거나 같은 동안 반복한다.
	i = 0;
	while (i < wordBook->length)
	{
		//4.1 철자가 서로 같으면
		if (strcmp(wordBook->words[i].spellings, spellings) == 0)
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

//findByMeanings
void FindByMeanings(WordBook* wordBook, char(*meanings), Long* (*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;
	*count = 0;
	//1. 의미를 입력받는다.
	//2. 사용량보다 적가나 같은동안 반복한다.
	while (i < wordBook->length)
	{
		//2.1 의미가 서로 같으면
		if (strcmp(wordBook->words[i].meanings, meanings) == 0)
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
	//4. 사용량보다 작거나 같은동안 반복한다.
	i = 0;
	while (i < wordBook->length)
	{
		//4.1 의미가 서로 같으면
		if (strcmp(wordBook->words[i].meanings, meanings) == 0)
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
	Word(*words) = NULL;
	Long i = 0;
	Long j = 0;

	//1. 위치를 입력받는다.
	//2. 할당량이 1보다 크면
	if (wordBook->capacity > 1)
	{
		//2.1 새주소록을 만든다.
		words = (Word(*))calloc(wordBook->capacity + 1, sizeof(Word));
	}
	//3. 기존 주소록의 내용을 옮겨적는다.
	while (i < index)
	{
		words[j] = wordBook->words[i];
		j++;
		i++;
	}
	i = index + 1;
	while (i < wordBook->length)
	{
		words[j] = wordBook->words[i];
		j++;
		i++;
	}
	//4. 기존주소록을 지운다.
	if (wordBook->words != NULL)
	{
		free(wordBook->words);
		wordBook->words = NULL;
	}
	if (wordBook->capacity > 1)
	{
		wordBook->words = words;
	}
	wordBook->capacity--;
	wordBook->length--;
	index = -1;
	//5. 위치를 출력한다.
	return index;
	//6. 끝내다.
}

//Arrange
void Arrange(WordBook* wordBook)
{
	Word word;
	Long i = wordBook->length - 1;
	Long j;
	//1. 오름차순으로 정렬한다.
	while (i >= 0)
	{
		j = 0;
		while (j < i)
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
	//2. 끝내다.
}

//Save
Long Save(WordBook* wordBook)
{
	Long i = 0;
	FILE* file;

	file = fopen("WordBook.dat", "wb");
	if (file != NULL)
	{
		//1. 사용량만큼 반복한다.
		while (i < wordBook->length)
		{
			//1.1 철자, 품사, 의미, 예시를 출력한다.
			fwrite(wordBook->words + i, sizeof(Word), 1, file);
			i++;
		}
		fclose(file);
	}
	//2. 사용량을 출력한다.
	return wordBook->length;
	//3. 끝내다.
}

//Destroy
void Destroy(WordBook* wordBook)
{
	//1. 할당해제한다.
	if (wordBook->words != NULL)
	{
		free(wordBook->words);
	}
	//2. 끝내다.
}