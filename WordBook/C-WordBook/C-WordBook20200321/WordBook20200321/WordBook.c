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

	//�����׽�Ʈ �ó�����
	//1. capacity�� 6�� �Է��Ѵ�.
	Create(&wordBook, 6);
	//Load
	Load(&wordBook);
	//2. kind, �����, ģ����, You are so kind.�� �����Ѵ�.
	index = Record(&wordBook, "kind", "�����", "ģ����", "You are so kind.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//3. apple, ���, ���, An apple is sweet.�� �����Ѵ�.
	index = Record(&wordBook, "apple", "���", "���", "An apple is sweet.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//4. kind, ���, ����, We serve two kinds of tea.�� �����Ѵ�.
	index = Record(&wordBook, "kind", "���", "����", "We serve two kinds of tea.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//5. very, �λ�, �ſ�, He is very tall.�� �����Ѵ�.
	index = Record(&wordBook, "very", "�λ�", "�ſ�", "He is very tall.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	printf("\n");
	//6. kind�� ã�´�.
	FindBySpellings(&wordBook, "kind", &indexes, &count);
	index = 0;
	while (index < count)
	{
		printf("%s %s %s %s\n", wordBook.words[indexes[index]].spellings, wordBook.words[indexes[index]].partOfSpeech,
			wordBook.words[indexes[index]].meanings, wordBook.words[indexes[index]].example);
		index++;
	}
	//indexes�迭�� �Ҵ������Ѵ�.
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//7. extremely, �λ�, �ſ�, The mountain is extremely high.�� �����Ѵ�.
	index = Record(&wordBook, "extremely", "�λ�", "�ſ�", "The mountain is extremely high.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	printf("\n");
	//8. �ſ츦 ã�´�.
	FindByMeanings(&wordBook, "�ſ�", &indexes, &count);
	index = 0;
	while (index < count)
	{
		printf("%s %s %s %s\n", wordBook.words[indexes[index]].meanings, wordBook.words[indexes[index]].spellings,
			wordBook.words[indexes[index]].partOfSpeech, wordBook.words[indexes[index]].example);
		index++;
	}
	//indexes�迭�� �Ҵ������Ѵ�.
	if (indexes != NULL)
	{
		free(indexes);
	}
	printf("\n");
	//9. ù ��° kind�� ���ø� ��ģ��.
	index = Correct(&wordBook, 0, "It is kind for you to help me.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	printf("\n");
	//10. apple�� �����.
	index = Erase(&wordBook, 1);
	if (index == -1)
	{
		printf("���������ϴ�.\n");
	}
	printf("\n");
	//11. �����Ѵ�.
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
	//12. �Ҵ������Ѵ�.
	Destroy(&wordBook);

	return 0;
}

//Create
void Create(WordBook* wordBook, Long capacity)
{
	//1. capacity�� �Է¹޴´�.
	//2. �ܾ�� �迭�� �����.
	wordBook->words = (Word(*))calloc(capacity, sizeof(Word));
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
	Word(*words);
	Long i = 0;
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
			//1.2 ��뷮�� �Ҵ緮���� ũ�ų� ������
			if (wordBook->length >= wordBook->capacity)
			{
				//1.2.1 ���ܾ����� �����.
				words = (Word(*))calloc(wordBook->capacity + 1, sizeof(Word));
				//1.2.2 ���� ������ �Ű����´�.
				i = 0;
				while (i < wordBook->length)
				{
					words[i] = wordBook->words[i];
					i++;
				}
				//1.2.3 ���� �ܾ����� �����.
				if (wordBook->words != NULL)
				{
					free(wordBook->words);
				}
				wordBook->words = words;
				wordBook->capacity++;
			}
			//1.3 �� �ٿ� ���´�.
			wordBook->words[i] = word;
			wordBook->length++;
			i++;
			//1.1 ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	//2. ��뷮�� ����Ѵ�.
	return wordBook->length;
	//3. ������.
}

//Record
Long Record(WordBook* wordBook, char(*spellings), char(*partOfSpeech), char(*meanings), char(*example))
{
	Long index = -1;
	Word(*words);
	Long i;

	//1. ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
	//2. ��뷮�� �Ҵ緮���� ũ�ų� ������
	if (wordBook->length >= wordBook->capacity)
	{
		//2.1 ���ܾ����� �����.
		words = (Word(*))calloc(wordBook->capacity + 1, sizeof(Word));
		//2.2 ���� �ܾ����� ������ �Ű����´�.
		i = 0;
		while (i < wordBook->length)
		{
			words[i] = wordBook->words[i];
			i++;
		}
		//2.3 ���� �ܾ����� �����.
		if (wordBook->words != NULL)
		{
			free(wordBook->words);
		}
		wordBook->words = words;
		wordBook->capacity++;
	}
	//3. �� �ٿ� ���´�.
	index = wordBook->length;
	strcpy(wordBook->words[index].spellings, spellings);
	strcpy(wordBook->words[index].partOfSpeech, partOfSpeech);
	strcpy(wordBook->words[index].meanings, meanings);
	strcpy(wordBook->words[index].example, example);
	wordBook->length++;
	//4. ��ġ�� ����Ѵ�.
	return index;
	//5. ������.
}

//FindBySpellings
void FindBySpellings(WordBook* wordBook, char(*spellings), Long* (*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;
	*count = 0;
	
	//1. ö�ڸ� �Է¹޴´�.
	//2. ��뷮���� �۰ų� ���� ���� �ݺ��Ѵ�.
	while (i < wordBook->length)
	{
		//2.1 ö�ڰ� ���� ������
		if (strcmp(wordBook->words[i].spellings, spellings) == 0)
		{
			//2.1.1 ������ ����.
			(*count)++;
		}
		i++;
	}
	//3. ������ 0���� ũ��
	if (*count > 0)
	{
		//3.1 ��ġ�� �迭�� �����.
		*indexes = (Long(*))calloc(*count, sizeof(Long));
	}
	//4. ��뷮���� �۰ų� ���� ���� �ݺ��Ѵ�.
	i = 0;
	while (i < wordBook->length)
	{
		//4.1 ö�ڰ� ���� ������
		if (strcmp(wordBook->words[i].spellings, spellings) == 0)
		{
			//4.1.1 ��ġ�� �����Ѵ�.
			(*indexes)[j] = i;
			j++;
		}
		i++;
	}
	//5. ��ġ��� ������ ����Ѵ�.
	//6. ������.
}

//findByMeanings
void FindByMeanings(WordBook* wordBook, char(*meanings), Long* (*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;
	*count = 0;
	//1. �ǹ̸� �Է¹޴´�.
	//2. ��뷮���� ������ �������� �ݺ��Ѵ�.
	while (i < wordBook->length)
	{
		//2.1 �ǹ̰� ���� ������
		if (strcmp(wordBook->words[i].meanings, meanings) == 0)
		{
			//2.1.1 ������ ����.
			(*count)++;
		}
		i++;
	}
	//3. ������ 0���� ũ��
	if (*count > 0)
	{
		//3.1 ��ġ�� �迭�� �����.
		*indexes = (Long(*))calloc(*count, sizeof(Long));
	}
	//4. ��뷮���� �۰ų� �������� �ݺ��Ѵ�.
	i = 0;
	while (i < wordBook->length)
	{
		//4.1 �ǹ̰� ���� ������
		if (strcmp(wordBook->words[i].meanings, meanings) == 0)
		{
			//4.1.1 ��ġ�� �����Ѵ�.
			(*indexes)[j] = i;
			j++;
		}
		i++;
	}
	//5. ��ġ��� ������ ����Ѵ�.
	//6. ������.
}

//Correct
Long Correct(WordBook* wordBook, Long index, char(*example))
{
	//1. ��ġ, ���ø� �Է¹޴´�.
	//2. ��ġ�� ���´�.
	strcpy(wordBook->words[index].example, example);
	//3. ��ġ�� ����Ѵ�.
	return index;
	//4. ������.
}

//Erase
Long Erase(WordBook* wordBook, Long index)
{
	Word(*words) = NULL;
	Long i = 0;
	Long j = 0;

	//1. ��ġ�� �Է¹޴´�.
	//2. �Ҵ緮�� 1���� ũ��
	if (wordBook->capacity > 1)
	{
		//2.1 ���ּҷ��� �����.
		words = (Word(*))calloc(wordBook->capacity + 1, sizeof(Word));
	}
	//3. ���� �ּҷ��� ������ �Ű����´�.
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
	//4. �����ּҷ��� �����.
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
	//5. ��ġ�� ����Ѵ�.
	return index;
	//6. ������.
}

//Arrange
void Arrange(WordBook* wordBook)
{
	Word word;
	Long i = wordBook->length - 1;
	Long j;
	//1. ������������ �����Ѵ�.
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
	//2. ������.
}

//Save
Long Save(WordBook* wordBook)
{
	Long i = 0;
	FILE* file;

	file = fopen("WordBook.dat", "wb");
	if (file != NULL)
	{
		//1. ��뷮��ŭ �ݺ��Ѵ�.
		while (i < wordBook->length)
		{
			//1.1 ö��, ǰ��, �ǹ�, ���ø� ����Ѵ�.
			fwrite(wordBook->words + i, sizeof(Word), 1, file);
			i++;
		}
		fclose(file);
	}
	//2. ��뷮�� ����Ѵ�.
	return wordBook->length;
	//3. ������.
}

//Destroy
void Destroy(WordBook* wordBook)
{
	//1. �Ҵ������Ѵ�.
	if (wordBook->words != NULL)
	{
		free(wordBook->words);
	}
	//2. ������.
}