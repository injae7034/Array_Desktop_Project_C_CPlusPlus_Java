#include"Word.h"
#pragma warning(disable:4996)

//디폴트 생성자
Word::Word()
	:spellings(""), partOfSpeech(""), meanings(""), example("")//콜론초기화
{

}

//매개변수를 갖는 생성자
Word::Word(string spellings, string partOfSpeech, string meainings, string example)
	:spellings(spellings), partOfSpeech(partOfSpeech), meanings(meainings), example(example)
{

}

//복사생성자
Word::Word(const Word& source)
	:spellings(source.spellings), partOfSpeech(source.partOfSpeech), meanings(source.meanings), example(source.example)
{

}

//소멸자
Word::~Word()
{

}

//논리연산자
bool Word::IsEqual(const Word& other)
{
	bool ret = false;
	if (this->spellings.compare(other.spellings) == 0 && this->partOfSpeech.compare(other.partOfSpeech) == 0
		&& this->meanings.compare(other.meanings) == 0 && this->example.compare(other.example) == 0)
	{
		ret = true;
	}
	return ret;
}

bool Word::IsNotEqual(const Word& other)
{
	bool ret = false;
	if (this->spellings.compare(other.spellings) != 0 || this->partOfSpeech.compare(other.partOfSpeech) != 0
		|| this->partOfSpeech.compare(other.partOfSpeech) != 0 || this->example.compare(other.example) != 0)
	{
		ret = true;
	}
	return ret;
}

bool Word::operator==(const Word& other)
{
	bool ret = false;
	if (this->spellings.compare(other.spellings) == 0 && this->partOfSpeech.compare(other.partOfSpeech) == 0
		&& this->meanings.compare(other.meanings) == 0 && this->example.compare(other.example) == 0)
	{
		ret = true;
	}
	return ret;
}

bool Word::operator!=(const Word& other)
{
	bool ret = false;
	if (this->spellings.compare(other.spellings) != 0 || this->partOfSpeech.compare(other.partOfSpeech) != 0
		|| this->partOfSpeech.compare(other.partOfSpeech) != 0 || this->example.compare(other.example) != 0)
	{
		ret = true;
	}
	return ret;
}

//치환연산자
Word& Word::operator=(const Word& source)
{
	this->spellings = source.spellings;
	this->partOfSpeech = source.partOfSpeech;
	this->meanings = source.meanings;
	this->example = source.example;

	return *this;
}