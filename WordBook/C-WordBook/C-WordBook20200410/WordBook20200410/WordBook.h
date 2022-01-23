#ifndef _WORDBOOK_H
#define _WORDBOOK_H

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
	Word(*words);
	Long capacity;
	Long length;
}WordBook;

void Create(WordBook* wordBook, Long capacity);
Long Load(WordBook* wordBook);
Long Record(WordBook* wordBook, char(*spellings), char(*partOfSpeech), char(*meanings), char(*example));
void FindBySpellings(WordBook* wordBook, char(*spellings), Long* (*indexes), Long* count);
void FindByMeanings(WordBook* wordBook, char(*meanings), Long* (*indexes), Long* count);
Long Correct(WordBook* wordBook, Long index, char(*example));
Long Erase(WordBook* wordBook, Long index);
void Arrange(WordBook* wordBook);
Long Save(WordBook* wordBook);
void Destroy(WordBook* wordBook);

#endif // !_WORDBOOK_H

