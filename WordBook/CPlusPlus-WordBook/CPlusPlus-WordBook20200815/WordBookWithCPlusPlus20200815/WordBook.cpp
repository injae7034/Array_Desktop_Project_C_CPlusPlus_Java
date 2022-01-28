#include "Word.h"
#include "WordBook.h"

//�⺻������
WordBook::WordBook(Long capacity)
	:words(capacity)//�ݷ��ʱ�ȭ -> Array�⺻������ ȣ��
{
	this->capacity = capacity;
	this->length = 0;
}

//���������
WordBook::WordBook(const WordBook& source)
	:words(source.words)//Array�� ��������� ȣ��
{
	this->capacity = source.capacity;
	this->length = source.length;
}

//ġȯ������->�����ڰ� �ƴϹǷ� �ݷ��ʱ�ȭ�� ����X
WordBook& WordBook::operator=(const WordBook& source)
{
	this->words = source.words;//Array ġȯ������ ȣ��
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

//�Ҹ���
WordBook::~WordBook()
{

}

//GetAt
Word& WordBook::GetAt(Long index)
{
	return this->words.GetAt(index);//Array<Word>�� �ڷ��� GetAt�Լ�ȣ��
}

//Record
Long WordBook::Record(string spellings, string partOfSpeech, string meanings, string example)
{
	//1. word�� �����Ѵ�.
	Word word(spellings, partOfSpeech, meanings, example);
	//2. ��뷮�� �Ҵ緮���� ������
	Long index;
	if (this->length < this->capacity)
	{
		index = this->words.Store(this->length, word);
	}
	//3. �׷��� ������
	else
	{
		index = words.AppendFromRear(word);
		this->capacity++;//�Ҵ緮 ������Ų��.
	}
	//4. ��뷮�� ������Ų��.
	this->length++;
	//5. ��ġ�� ����Ѵ�,
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
	//1. word�� ���Ѵ�.
	Word word = this->words.GetAt(index);
	//2. wordBook�� ���ø� ��ģ��.
	index = this->words.Modify(index, Word(word.GetSpellings(), word.GetPartOfSpeech(), word.GetMeanings(),
		example));
	//3. ��ġ�� ����Ѵ�.
	return index;
}

//Erase
Long WordBook::Erase(Long index)
{
	index = this->words.Delete(index);
	this->capacity--;
	this->length--;
	return index;
}

//Arrange
void WordBook::Arrange()
{
	this->words.SelectionSort(CompareWords);
}



//�����׽�Ʈ�ó�����
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//1. capacity�� 3�� �Է���  wordBook�� �����.
	WordBook wordBook(3);//WordBook �⺻������ ȣ��
	//2. kind, �����, ģ����, You are so kind.�� �����Ѵ�.
	Long index;
	index = wordBook.Record("kind", "�����", "ģ����", "You are so kind.");
	Word word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//3. apple, ���, ���, Apple is sweet.�� �����Ѵ�.
	index = wordBook.Record("apple", "���", "���", "Aa apple is sweet.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//4. kind, ���, ����, We serve two kinds of tea.�� �����Ѵ�.
	index = wordBook.Record("kind", "���", "����", "We serve two kinds of tea.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//5. kind�� ã�´�.
	Long(*indexes) = 0;
	Long count = 0;
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
	//6. very, �λ�, �ſ�, He is very tall.�� �����Ѵ�.
	index = wordBook.Record("very", "�λ�", "�ſ�", "He is very tall.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//7.  extremely, �λ�, �ſ�, The mountain is extremely high.�� �����Ѵ�.
	index = wordBook.Record("extremely", "�λ�", "�ſ�", "The mountain is extremely high.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//8. �ſ츦 ã�´�.
	wordBook.FindByMeanings("�ſ�", &indexes, &count);
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
	//9. �ܾ����� ù��° �ܾ��� ���ø� ��ģ��.
	index = wordBook.Correct(0, "It is so kind for you to help me.");
	word = wordBook.GetAt(index);
	cout << word.GetSpellings() << "-"
		<< word.GetPartOfSpeech() << "-"
		<< word.GetMeanings() << "-"
		<< word.GetExample() << endl;
	//10. �ܾ����� �ι�° �ܾ �����.
	index = wordBook.Erase(1);
	if (index == -1)
	{
		cout << "���������ϴ�." << endl;
	}
	//11. �ܾ����� �����Ѵ�.
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
	//���������
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
	//ġȯ������
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
	return 0;//�Ҹ���
}


//�Լ�������
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