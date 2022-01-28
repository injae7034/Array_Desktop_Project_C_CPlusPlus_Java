#include "Word.h"
#include "WordBook.h"

//기본생성자
WordBook::WordBook(Long capacity)
	:words(capacity)//콜론초기화 -> Array기본생성자 호출
{
	this->capacity = capacity;
	this->length = 0;
}

//복사생성자
WordBook::WordBook(const WordBook& source)
	:words(source.words)//Array의 복사생성자 호출
{
	this->capacity = source.capacity;
	this->length = source.length;
}

//치환연산자->생성자가 아니므로 콜론초기화를 쓰지X
WordBook& WordBook::operator=(const WordBook& source)
{
	this->words = source.words;//Array 치환연산자 호출
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

//소멸자
WordBook::~WordBook()
{

}

//GetAt
Word& WordBook::GetAt(Long index)
{
	return this->words.GetAt(index);//Array<Word>가 자료형 GetAt함수호출
}

//Record
Long WordBook::Record(string spellings, string partOfSpeech, string meanings, string example)
{
	//1. word를 생성한다.
	Word word(spellings, partOfSpeech, meanings, example);
	//2. 사용량이 할당량보다 작으면
	Long index;
	if (this->length < this->capacity)
	{
		index = this->words.Store(this->length, word);
	}
	//3. 그렇지 않으면
	else
	{
		index = words.AppendFromRear(word);
		this->capacity++;//할당량 증가시킨다.
	}
	//4. 사용량을 증가시킨다.
	this->length++;
	//5. 위치를 출력한다,
	return index;
}

//FindBySpellings
void WordBook::FindBySpellings(string spellings, Long* (*indexes), Long* count)
{
	this->words.LinearSearchDuplicate(&spellings, indexes, count, CompareSpellings);
}

//FindByMeanings
void WordBook::FindByMeanings(string meanings, Long* (*indexes), Long* count)
{
	this->words.LinearSearchDuplicate(&meanings, indexes, count, CompareMeanings);
}

//Correct
Long WordBook::Correct(Long index, string example)
{
	//1. word를 구한다.
	Word word = this->words.GetAt(index);
	//2. wordBook의 예시를 고친다.
	index = this->words.Modify(index, Word(word.GetSpellings(), word.GetPartOfSpeech(), word.GetMeanings(),
		example));
	//3. 위치를 출력한다.
	return index;
}

Long WordBook::Erase(Long index)
{
	index = this->words.Delete(index);
	this->capacity--;
	this->length--;
	return index;
}

void WordBook::Arrange()
{
	this->words.SelectionSort(CompareWords);
}



//메인테스트시나리오
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. capacity에 3을 입력해  wordBook을 만든다.
	WordBook wordBook(3);//WordBook 기본생성자 호출
	//2. kind, 형용사, 친절한, You are so kind.를 기재한다.
	Long index;
	index = wordBook.Record("kind", "형용사", "친절한", "You are so kind.");
	Word word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//3. apple, 명사, 사과, Apple is sweet.을 기재한다.
	index = wordBook.Record("apple", "명사", "사과", "Aa apple is sweet.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//4. kind, 명사, 종류, We serve two kinds of tea.를 기재한다.
	index = wordBook.Record("kind", "명사", "종류", "We serve two kinds of tea.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//5. kind를 찾는다.
	Long(*indexes);
	Long count;
	wordBook.FindBySpellings("kind", &indexes, &count);
	index = 0;
	while (index < count)
	{
		word = wordBook.GetAt(indexes[index]);
		cout << word.GetSpellings() << "-"
			<< word.GetPartOfSpeech() << "-"
			<< word.GetMeanings() << "-"
			<< word.GetExample() << endl;
		index++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//6. very, 부사, 매우, He is very tall.을 기재한다.
	index = wordBook.Record("very", "부사", "매우", "He is very tall.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//7.  extremely, 부사, 매우, The mountain is extremely high.를 기재한다.
	index = wordBook.Record("extremely", "부사", "매우", "The mountain is extremely high.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//8. 매우를 찾는다.
	wordBook.FindByMeanings("매우", &indexes, &count);
	index = 0;
	while (index < count)
	{
		word = wordBook.GetAt(indexes[index]);
		cout << word.GetSpellings() << "-"
			<< word.GetPartOfSpeech() << "-"
			<< word.GetMeanings() << "-"
			<< word.GetExample() << endl;
		index++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//9. 단어장의 첫번째 단어의 예시를 고친다.
	index = wordBook.Correct(0, "It is so kind for you to help me.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//10. 단어장의 두번째 단어를 지운다.
	index = wordBook.Erase(1);
	if (index == -1)
	{
		cout << "지워졌습니다." << endl;
	}
	//11. 단어장을 정리한다.
	wordBook.Arrange();
	index = 0;
	while (index < wordBook.GetLength())
	{
		word = wordBook.GetAt(index);
		cout << word.GetSpellings() << "-"
			<< word.GetPartOfSpeech() << "-"
			<< word.GetMeanings() << "-"
			<< word.GetExample() << endl;
		index++;
	}
	//복사생성자
	WordBook other(wordBook);
	index = 0;
	while (index < other.GetLength())
	{
		word = wordBook.GetAt(index);
		cout << word.GetSpellings() << "-"
			<< word.GetPartOfSpeech() << "-"
			<< word.GetMeanings() << "-"
			<< word.GetExample() << endl;
		index++;
	}
	//치환연산자
	WordBook theOther(3);
	theOther = other;
	index = 0;
	while (index < theOther.GetLength())
	{
		word = wordBook.GetAt(index);
		cout << word.GetSpellings() << "-"
			<< word.GetPartOfSpeech() << "-"
			<< word.GetMeanings() << "-"
			<< word.GetExample() << endl;
		index++;
	}
	return 0;//소멸자
}


//함수포인터
int CompareSpellings(void* one, void* other)//FindBySpellings
{
	Word* one_ = (Word*)one;
	string* other_ = (string*)other;

	return(one_->GetSpellings().compare(*other_));
}

int CompareMeanings(void* one, void* other)//FindByMeanings
{
	Word* one_ = (Word*)one;
	string* other_ = (string*)other;

	return (one_->GetMeanings().compare(*other_));
}

int CompareWords(void* one, void* other)//Arrange
{
	Word* one_ = (Word*)one;
	Word* other_ = (Word*)other;

	return (one_->GetSpellings().compare(other_->GetSpellings()));
}