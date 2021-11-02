#include "WordBook.h"
#include<stdio.h>//printf
#include<string.h>//strcpy, strcmp
#include<stdlib.h>//calloc, free
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	WordBook wordBook;
	Long index;
	Long(*indexes);
	Long count;
	Word word;

	//메인테스트 시나리오
	//1. capacity에 3을 입력해 배열을 만든다.
	WordBook_Create(&wordBook, 3);
	//2. 불러온다.
	Load(&wordBook);
	//3. kind, 형용사, 친절한, You are so kind.를 기재한다.
	index = Record(&wordBook, "kind", "형용사", "친절한", "You are so kind.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	//4. apple, 명사, 사과, An apple is sweet.을 기재한다.
	index = Record(&wordBook, "apple", "명사", "사과", "An apple is sweet.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	//5. kind, 명사, 종류, We serve two kinds of tea.를 기재한다.
	index = Record(&wordBook, "kind", "명사", "종류", "We serve two kinds of tea.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	printf("\n");
	//6. kind를 찾는다.
	FindBySpellings(&wordBook, "kind", &indexes, &count);
	index = 0;
	while (index < count)
	{
		word = WordBook_GetAt(&wordBook, indexes[index]);
		printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
		index++;
	}
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//7. very, 부사, 매우, He is very tall을 기재한다.
	index = Record(&wordBook, "very", "부사", "매우", "He is very tall.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	//8. extremely, 부사, 매우, The mountain is extremley high.를 기재한다.
	index = Record(&wordBook, "extremely", "부사", "매우", "The mountain is extremely high.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	printf("\n");
	//9. 매우를 찾는다.
	FindByMeanings(&wordBook, "매우", &indexes, &count);
	index = 0;
	while (index < count)
	{
		word = WordBook_GetAt(&wordBook, indexes[index]);
		printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
		index++;
	}
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//10. 첫번째 kind의 예시를 고친다.
	index = Correct(&wordBook, 0, "It is kind for you to help me.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	printf("\n");
	//11. apple을 지운다.
	index = Erase(&wordBook, 1);
	if (index == -1)
	{
		printf("지워졌습니다.\n");
		printf("\n");
	}
	//12. 정리한다.
	Arrange(&wordBook);
	index = 0;
	while (index < wordBook.length)
	{
		word = WordBook_GetAt(&wordBook, index);
		printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
		index++;
	}
	//13. 저장한다.
	Save(&wordBook);
	//14. 할당해제한다.
	WordBook_Destroy(&wordBook);

	return 0;
}

//WordBook_Create
void WordBook_Create(WordBook* wordBook, Long capacity)
{
	//1. capacity를 입력받는다.
	//2. 배열을 만든다.
	Create(&wordBook->words, capacity, sizeof(Word));
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
	Long index;
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
			//1.2 사용량이 할당량보다 작으면
			if (wordBook->length < wordBook->capacity)
			{
				//1.2.1 빈줄에 적는다.
				index = Store(&wordBook->words, wordBook->length, &word, sizeof(Word));
			}
			//1.3 그렇지 않으면
			else
			{
				//1.3.1 새 단어장을 만든다.
				index = AppendFromRear(&wordBook->words, &word, sizeof(Word));
				//1.3.2 할당량을 증가시킨다.
				wordBook->capacity++;
			}
			//1.4. 사용량을 증가시킨다.
			wordBook->length++;
			//1.1 철자, 품사, 의미, 예시를 입력받는다.
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	//2. 사용량을 출력한다.
	return wordBook->length;
	//3. 끝내다.
}

//WordBook_GetAt
Word WordBook_GetAt(WordBook* wordBook, Long index)
{
	Word word;

	//1. 위치를 입력받는다.
	//2. 해댕 위치의 word를 구한다.
	GetAt(&wordBook->words, index, &word, sizeof(Word));
	//3. word를 출력한다.
	return word;
	//4. 끝내다.
}

//Record
Long Record(WordBook* wordBook, char(*spellings), char(*partOfSpeech), char(*meanings), char(*exmaple))
{
	Long index;
	Word word;

	//1. 철자, 품사, 의미, 예시를 입력받는다.
	strcpy(word.spellings, spellings);
	strcpy(word.partOfSpeech, partOfSpeech);
	strcpy(word.meanings, meanings);
	strcpy(word.example, exmaple);
	//2. 사용량이 할당량보다 작으면
	if (wordBook->length < wordBook->capacity)
	{
		//2.1 빈 줄에 적는다.
		index = Store(&wordBook->words, wordBook->length, &word, sizeof(Word));
	}
	//3. 그렇지 않으면
	else
	{
		//3.1 새 단어장을 만든다.
		index = AppendFromRear(&wordBook->words, &word, sizeof(Word));
		//3.2 할당량을 증가시킨다.
		wordBook->capacity++;
	}
	//4. 사용량을 증가시킨다.
	wordBook->length++;
	//5. 위치를 출력한다.
	return index;
	//6. 끝내다.
}

//FindBySpellings
void FindBySpellings(WordBook* wordBook, char(*spellings), Long* (*indexes), Long* count)
{
	//1. 철자를 입력받는다.
	//2. 철자를 찾는다.
	LinearSearchDuplicate(&wordBook->words, spellings, indexes, count, sizeof(Word), CompareSpellings);
	//3. 위치들과 개수를 출력한다.
	//4. 끝내다.
}

//FindByMeanings
void FindByMeanings(WordBook* wordBook, char(*meanings), Long* (*indexes), Long* count)
{
	//1. 의미를 입력받는다.
	//2. 의미를 찾는다.
	LinearSearchDuplicate(&wordBook->words, meanings, indexes, count, sizeof(Word), CompareMeanings);
	//3. 위치들과 개수를 출력한다.
	//4. 끝내다.
}

//Correct
Long Correct(WordBook* wordBook, Long index, char(*example))
{
	Word word;

	//1. 위치를 통해 예시를 입력받는다.
	GetAt(&wordBook->words, index, &word, sizeof(Word));
	//2. 고칠 예제를 적는다.
	strcpy(word.example, example);
	//3. 위치에서 고친다.
	index = Modify(&wordBook->words, index, &word, sizeof(Word));
	//4. 위치를 출력한다.
	return index;
	//5. 끝내다.
}

//Erase
Long Erase(WordBook* wordBook, Long index)
{
	//1. 위치를 입력받는다.
	//2. 위치에서 지운다.
	index = Delete(&wordBook->words, index, sizeof(Word));
	//3. 할당량을 감소시킨다.
	wordBook->capacity--;
	//4. 사용량을 감소시킨다.
	wordBook->length--;
	//5. 위치를 출력한다.
	return index;
	//6. 끝내다.
}

//Arrange
void Arrange(WordBook* wordBook)
{
	//1. 오름차순으로 정렬한다.
	SelectionSort(&wordBook->words, sizeof(Word), CompareWords);
	//2. 끝내다.
}

//Save
Long Save(WordBook* wordBook)
{
	Word word;
	Long index = 0;
	FILE* file;

	file = fopen("WordBook.dat", "wb");
	if (file != NULL)
	{
		//1. 사용량만큼 반복한다.
		while (index < wordBook->length)
		{
			//1.1 철자, 품사, 의미, 예시를 출력한다.
			GetAt(&wordBook->words, index, &word, sizeof(Word));
			fwrite(&word, sizeof(Word), 1, file);
			index++;
		}
		fclose(file);
	}
	//2. 사용량을 출력한다.
	return wordBook->length;
	//3. 끝내다.
}

//WordBook_Destroy
void WordBook_Destroy(WordBook* wordBook)
{
	//1. 할당해제한다.
	Destroy(&wordBook->words);
	//2. 끝내다.
}

int CompareSpellings(void* one, void* other)
{
	Word* one_ = (Word*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->spellings, other_);
}

int CompareMeanings(void* one, void* other)
{
	Word* one_ = (Word*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->meanings, other_);
}

int CompareWords(void* one, void* other)
{
	Word* one_ = (Word*)one;
	Word* other_ = (Word*)other;

	return strcmp(one_->spellings, other_->spellings);
}
