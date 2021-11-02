#include"Word.h"
#pragma warning(disable:4996)

//����Ʈ ������
Word::Word()
	:spellings(""), partOfSpeech(""), meanings(""), example("")//�ݷ��ʱ�ȭ
{

}

//�Ű������� ���� ������
Word::Word(string spellings, string partOfSpeech, string meainings, string example)
	:spellings(spellings), partOfSpeech(partOfSpeech), meanings(meainings), example(example)
{

}

//���������
Word::Word(const Word& source)
	:spellings(source.spellings), partOfSpeech(source.partOfSpeech), meanings(source.meanings), example(source.example)
{

}

//�Ҹ���
Word::~Word()
{

}

//��������
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

//ġȯ������
Word& Word::operator=(const Word& source)
{
	this->spellings = source.spellings;
	this->partOfSpeech = source.partOfSpeech;
	this->meanings = source.meanings;
	this->example = source.example;

	return *this;
}