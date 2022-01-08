#ifndef _WORDBOOK_H
#define _WORDBOOK_H

#include "Array.h"

typedef signed long int Long;
typedef struct _word
{
	char spellings[64];
	char partOfSpeech[8];
	char meanings[32];
	char example[128];
}Word;
typedef struct _wordBook
{
	Array words;
	Long capacity;
	Long length;
}WordBook;

void WordBook_Create(WordBook* wordBook, Long capacity);
Long Load(WordBook* wordBook);
Word WordBook_GetAt(WordBook* wordBook, Long index);
Long Record(WordBook* wordBook, char(*spellings), char(*partOfSpeech), char(*meanings), char(*exmaple));
void FindBySpellings(WordBook* wordBook, char(*spellings), Long* (*indexes), Long* count);
void FindByMeanings(WordBook* wordBook, char(*meanings), Long* (*indexes), Long* count);
Long Correct(WordBook* wordBook, Long index, char(*example));
Long Erase(WordBook* wordBook, Long index);
void Arrange(WordBook* wordBook);
Long Save(WordBook* wordBook);
void WordBook_Destroy(WordBook* wordBook);

int CompareSpellings(void* one, void* other);
int CompareMeanings(void* one, void* other);
int CompareWords(void* one, void* other);

#endif // !_WORDBOOK_H
