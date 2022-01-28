#ifndef _WORDBOOK_H
#define _WORDBOOK_H
//STL(Standard Template Class Library)-C++ Class Library
#include "Array.h"
#include "Word.h"
#include<string>
using namespace std;

typedef signed long int Long;

class WordBook
{
public:
	WordBook(Long capacity = 256);//기본생성자
	WordBook(const WordBook& source);// 복사생성자
	~WordBook();//소멸자
	Word& GetAt(Long index);
	Long Record(string spellings, string partOfSpeech, string meanings, string example);
	void FindBySpellings(string spellings, Long* (*indexes), Long* count);
	void FindByMeanings(string meanings, Long* (*indexes), Long* count);
	Long Correct(Long index, string example);
	Long Erase(Long index);
	void Arrange();
	//치환연산자
	WordBook& operator=(const WordBook& source);

	Long GetCapacity() const;
	Long GetLength() const;

private:
	Array<Word> words;
	Long capacity;
	Long length;
};

inline Long WordBook::GetCapacity() const
{
	return this->capacity;
}
inline Long WordBook::GetLength()const
{
	return this->length;
}
//함수포인터
int CompareSpellings(void* one, void* other);
int CompareMeanings(void* one, void* other);
int CompareWords(void* one, void* other);

#endif // !_WORDBOOK_H

