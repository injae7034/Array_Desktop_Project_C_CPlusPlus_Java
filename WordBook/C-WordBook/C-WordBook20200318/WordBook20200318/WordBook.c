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

	//�����Լ� �׽�Ʈ �ó�����

	//Load
	Load(&wordBook);
	//1. kind, �����, ģ����, You are so kind.�� �����Ѵ�.
	index = Record(&wordBook, "kind", "�����", "ģ����", "You are so kind.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		    wordBook.words[index].meanings, wordBook.words[index].example);
	//2. apple, ���, ���, An apple is delicious.�� �����Ѵ�.
	index = Record(&wordBook, "apple", "���", "���", "An apple is delicious.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		   wordBook.words[index].meanings, wordBook.words[index].example);
	//3. very, �λ�, �ſ�, He is very tall.�� �����Ѵ�.
	index = Record(&wordBook, "very", "�λ�", "�ſ�", "He is very tall.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		   wordBook.words[index].meanings, wordBook.words[index].example);
	//4. kind, ���, ����, What kind of movie do you like?�� �����Ѵ�.
	index = Record(&wordBook, "kind", "���", "����", "What kind of movie do you like?");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		   wordBook.words[index].meanings, wordBook.words[index].example);
	//5. kind�� ã�´�.
	FindBySpellings(&wordBook, "kind", indexes, &count);
	index = 0;
	while (index<count)
	{
		printf("%s %s %s %s\n", wordBook.words[indexes[index]].spellings, 
			wordBook.words[indexes[index]].partOfSpeech, wordBook.words[indexes[index]].meanings,
			wordBook.words[indexes[index]].example);
		index++;
	}
	//6. "�ſ�"�� ã�´�
	FindByMeanings(&wordBook, "�ſ�", indexes, &count);
	index = 0;
	while (index < count)
	{
		printf("%s %s %s %s\n", wordBook.words[indexes[index]].spellings,
			wordBook.words[indexes[index]].partOfSpeech, wordBook.words[indexes[index]].meanings,
			wordBook.words[indexes[index]].example);
		index++;
	}
	//7. �׹�° kind�� ���ø� ��ģ��.
	index = Correct(&wordBook, 3, "We serve two kind of tea.");
	printf("%d %s %s %s %s\n", index, wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//8. apple�� �����.
	index = Erase(&wordBook, 1);
	if (index==-1)
	{
		printf("���������ϴ�.\n");
	}
	//9. try, ����, ����ϴ�, I try to study hard.�� �����Ѵ�.
	index = Record(&wordBook, "try", "����", "����ϴ�", "I try to study hard.");
	printf("%s %s %s %s\n", wordBook.words[index].spellings, wordBook.words[index].partOfSpeech,
		wordBook.words[index].meanings, wordBook.words[index].example);
	//10.�����Ѵ�.
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
		//1.1 ö��, ǰ��, �ǹ�, ���ø� �Է¹޴´�.
		flag = fread(&word, sizeof(Word), 1, file);
		//1. ������ ���� �ƴѵ��� �ݺ��Ѵ�.
		while (!feof(file) && flag != 0)
		{
			//1.2 �ܾ�迭�� �����Ѵ�.
			wordBook->words[i] = word;
			wordBook->length++;
			i++;
			//1.1 ö��, ǰ��, �ǹ�, ���ø� �Է��Ѵ�.
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	//2. ������ ����Ѵ�.
	return wordBook->length;
	//3. ������.
}

//Record
Long Record(WordBook* wordBook, char(*spellings), char(*partOfSpeech), char(*meanings), char(*example))
{
	Long index = -1;
	Long i = 0;
	//1. ö��, ǰ��, �ǹ�, ���ø� �Է��Ѵ�.
	//2. �� ���� ã�´�.
	while (i<wordBook->capacity && strcmp(wordBook->words[i].spellings, "")!=0)
	{
		i++;
	}
	//3. �� �ٿ� ���´�.
	if (i<wordBook->capacity)
	{
		index = i;
		strcpy(wordBook->words[index].spellings, spellings);
		strcpy(wordBook->words[index].partOfSpeech, partOfSpeech);
		strcpy(wordBook->words[index].meanings, meanings);
		strcpy(wordBook->words[index].example, example);
		wordBook->length++;
	}
	//4. ��ġ�� ����Ѵ�.
	return index;
	//5 ������.
}

//FindBySpellings
void FindBySpellings(WordBook* wordBook, char(*spellings), Long(*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;
	
	*count = 0;
	
	//1. ö�ڸ� �Է¹޴´�.
	//2. length��ŭ �ݺ��Ѵ�.
	while (i<wordBook->length)
	{
		//2.1 ö�ڰ� ���� ������
		if (strcmp(wordBook->words[i].spellings, spellings)==0)
		{
			//2.1.1 ������ ����.
			(*count)++;
			//2.1.2 ��ġ�� �����Ѵ�.
			indexes[j] = i;
			j++;
		}
		i++;
	}
	//3. ��ġ��� ������ ����Ѵ�.
	//4. ������.
}

//FindByMeanings
void FindByMeanings(WordBook* wordBook, char(*meanings), Long(*indexes), Long* count)
{
	Long i = 0;
	Long j = 0;

	*count = 0;

	//1. �ǹ̸� �Է¹޴´�.
	//2. length��ŭ �ݺ��Ѵ�.
	while (i < wordBook->length)
	{
		//2.1 �ǹ̰� ���� ������
		if (strcmp(wordBook->words[i].meanings, meanings) == 0)
		{
			//2.1.1 ������ ����.
			(*count)++;
			//2.1.2 ��ġ�� �����Ѵ�.
			indexes[j] = i;
			j++;
		}
		i++;
	}
	//3. ��ġ��� ������ ����Ѵ�.
	//4. ������.
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
	//1. ��ġ�� �Է¹޴´�.
	//2. ��ġ�� �����.
	strcpy(wordBook->words[index].spellings, "X");
	index = -1;
	//3. ��ġ�� ����Ѵ�.
	return index;
	//4. ������.
}

//Arrange
void Arrange(WordBook* wordBook)
{
	Long count = 0;
	Long i = wordBook->length - 1;
	Long j;
	Word word;

	//1. ������������ �����Ѵ�.
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
	//2. ������ ����.
	i = 0;
	while (i<wordBook->length && strcmp(wordBook->words[i].spellings, "X")!=0)
	{
		count++;
		i++;
	}
	//3. ���� �ȿ��� ������������ �����Ѵ�.
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
		//1. length��ŭ �ݺ��Ѵ�.
		while (i<wordBook->length)
		{
			//1.1 ö��, ǰ��, �ǹ�, ���ø� ����Ѵ�.
			fwrite(wordBook->words + i, sizeof(Word), 1, file);
			i++;
		}
		fclose(file);
	}
	//2. ������ ����Ѵ�.
	return wordBook->length;
	//3. ������.
}