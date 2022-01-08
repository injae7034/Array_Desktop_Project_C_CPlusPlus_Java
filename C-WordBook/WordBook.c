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

	//�����׽�Ʈ �ó�����
	//1. capacity�� 3�� �Է��� �迭�� �����.
	WordBook_Create(&wordBook, 3);
	//2. �ҷ��´�.
	Load(&wordBook);
	//3. kind, �����, ģ����, You are so kind.�� �����Ѵ�.
	index = Record(&wordBook, "kind", "�����", "ģ����", "You are so kind.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	//4. apple, ���, ���, An apple is sweet.�� �����Ѵ�.
	index = Record(&wordBook, "apple", "���", "���", "An apple is sweet.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	//5. kind, ���, ����, We serve two kinds of tea.�� �����Ѵ�.
	index = Record(&wordBook, "kind", "���", "����", "We serve two kinds of tea.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	printf("\n");
	//6. kind�� ã�´�.
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
	//7. very, �λ�, �ſ�, He is very tall�� �����Ѵ�.
	index = Record(&wordBook, "very", "�λ�", "�ſ�", "He is very tall.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	//8. extremely, �λ�, �ſ�, The mountain is extremley high.�� �����Ѵ�.
	index = Record(&wordBook, "extremely", "�λ�", "�ſ�", "The mountain is extremely high.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	printf("\n");
	//9. �ſ츦 ã�´�.
	FindByMeanings(&wordBook, "�ſ�", &indexes, &count);
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
	//10. ù��° kind�� ���ø� ��ģ��.
	index = Correct(&wordBook, 0, "It is kind for you to help me.");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
	printf("\n");
	//11. apple�� �����.
	index = Erase(&wordBook, 1);
	if (index == -1)
	{
		printf("���������ϴ�.\n");
		printf("\n");
	}
	//12. �����Ѵ�.
	Arrange(&wordBook);
	index = 0;
	while (index < wordBook.length)
	{
		word = WordBook_GetAt(&wordBook, index);
		printf("%s %s %s %s\n", word.spellings, word.partOfSpeech, word.meanings, word.example);
		index++;
	}
	//13. �����Ѵ�.
	Save(&wordBook);
	//14. �Ҵ������Ѵ�.
	WordBook_Destroy(&wordBook);

	return 0;
}

//WordBook_Create
void WordBook_Create(WordBook* wordBook, Long capacity)
{
	//1. capacity�� �Է¹޴´�.
	//2. �迭�� �����.
	Create(&wordBook->words, capacity, sizeof(Word));
	//3. �Ҵ緮�� ���Ѵ�.
	wordBook->capacity = capacity;
	//4. ��뷮�� ���Ѵ�.
	wordBook->length = 0;
	//5. ������.
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
		//1.1 ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
		flag = fread(&word, sizeof(Word), 1, file);
		//1. ������ ���� �ƴѵ��� �ݺ��Ѵ�.
		while (!feof(file) && flag != 0)
		{
			//1.2 ��뷮�� �Ҵ緮���� ������
			if (wordBook->length < wordBook->capacity)
			{
				//1.2.1 ���ٿ� ���´�.
				index = Store(&wordBook->words, wordBook->length, &word, sizeof(Word));
			}
			//1.3 �׷��� ������
			else
			{
				//1.3.1 �� �ܾ����� �����.
				index = AppendFromRear(&wordBook->words, &word, sizeof(Word));
				//1.3.2 �Ҵ緮�� ������Ų��.
				wordBook->capacity++;
			}
			//1.4. ��뷮�� ������Ų��.
			wordBook->length++;
			//1.1 ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	//2. ��뷮�� ����Ѵ�.
	return wordBook->length;
	//3. ������.
}

//WordBook_GetAt
Word WordBook_GetAt(WordBook* wordBook, Long index)
{
	Word word;

	//1. ��ġ�� �Է¹޴´�.
	//2. �ش� ��ġ�� word�� ���Ѵ�.
	GetAt(&wordBook->words, index, &word, sizeof(Word));
	//3. word�� ����Ѵ�.
	return word;
	//4. ������.
}

//Record
Long Record(WordBook* wordBook, char(*spellings), char(*partOfSpeech), char(*meanings), char(*exmaple))
{
	Long index;
	Word word;

	//1. ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
	strcpy(word.spellings, spellings);
	strcpy(word.partOfSpeech, partOfSpeech);
	strcpy(word.meanings, meanings);
	strcpy(word.example, exmaple);
	//2. ��뷮�� �Ҵ緮���� ������
	if (wordBook->length < wordBook->capacity)
	{
		//2.1 �� �ٿ� ���´�.
		index = Store(&wordBook->words, wordBook->length, &word, sizeof(Word));
	}
	//3. �׷��� ������
	else
	{
		//3.1 �� �ܾ����� �����.
		index = AppendFromRear(&wordBook->words, &word, sizeof(Word));
		//3.2 �Ҵ緮�� ������Ų��.
		wordBook->capacity++;
	}
	//4. ��뷮�� ������Ų��.
	wordBook->length++;
	//5. ��ġ�� ����Ѵ�.
	return index;
	//6. ������.
}

//FindBySpellings
void FindBySpellings(WordBook* wordBook, char(*spellings), Long* (*indexes), Long* count)
{
	//1. ö�ڸ� �Է¹޴´�.
	//2. ö�ڸ� ã�´�.
	LinearSearchDuplicate(&wordBook->words, spellings, indexes, count, sizeof(Word), CompareSpellings);
	//3. ��ġ��� ������ ����Ѵ�.
	//4. ������.
}

//FindByMeanings
void FindByMeanings(WordBook* wordBook, char(*meanings), Long* (*indexes), Long* count)
{
	//1. �ǹ̸� �Է¹޴´�.
	//2. �ǹ̸� ã�´�.
	LinearSearchDuplicate(&wordBook->words, meanings, indexes, count, sizeof(Word), CompareMeanings);
	//3. ��ġ��� ������ ����Ѵ�.
	//4. ������.
}

//Correct
Long Correct(WordBook* wordBook, Long index, char(*example))
{
	Word word;

	//1. ��ġ�� ���� ���ø� �Է¹޴´�.
	GetAt(&wordBook->words, index, &word, sizeof(Word));
	//2. ��ĥ ������ ���´�.
	strcpy(word.example, example);
	//3. ��ġ���� ��ģ��.
	index = Modify(&wordBook->words, index, &word, sizeof(Word));
	//4. ��ġ�� ����Ѵ�.
	return index;
	//5. ������.
}

//Erase
Long Erase(WordBook* wordBook, Long index)
{
	//1. ��ġ�� �Է¹޴´�.
	//2. ��ġ���� �����.
	index = Delete(&wordBook->words, index, sizeof(Word));
	//3. �Ҵ緮�� ���ҽ�Ų��.
	wordBook->capacity--;
	//4. ��뷮�� ���ҽ�Ų��.
	wordBook->length--;
	//5. ��ġ�� ����Ѵ�.
	return index;
	//6. ������.
}

//Arrange
void Arrange(WordBook* wordBook)
{
	//1. ������������ �����Ѵ�.
	SelectionSort(&wordBook->words, sizeof(Word), CompareWords);
	//2. ������.
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
		//1. ��뷮��ŭ �ݺ��Ѵ�.
		while (index < wordBook->length)
		{
			//1.1 ö��, ǰ��, �ǹ�, ���ø� ����Ѵ�.
			GetAt(&wordBook->words, index, &word, sizeof(Word));
			fwrite(&word, sizeof(Word), 1, file);
			index++;
		}
		fclose(file);
	}
	//2. ��뷮�� ����Ѵ�.
	return wordBook->length;
	//3. ������.
}

//WordBook_Destroy
void WordBook_Destroy(WordBook* wordBook)
{
	//1. �Ҵ������Ѵ�.
	Destroy(&wordBook->words);
	//2. ������.
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
