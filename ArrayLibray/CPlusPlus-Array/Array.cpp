#include "Array.h"
#include<iostream>
using namespace std;
#pragma warning(disable:4996)

int Compare(void* one, void* other);//함수포인터

int main(int argc, char* argv[])
{
	//1. capacity에 3을 입력해 배열을 만든다.
	Array<int>array(3);
	//2. 1에 100을 저장한다.
	Long index;
	index = array.Store(0, 100);
	int value;
	value = array.GetAt(index);
	cout << value << endl;
	//3. 2에 50을 저장한다.
	index = array.Store(1, 50);
	value = array.GetAt(index);
	cout << value << endl;
	//4. 3에 200을 저장한다.
	index = array.Store(2, 200);
	value = array.GetAt(index);
	cout << value << endl;
	//5. 맨앞에 300을 추가한다.
	index = array.AppendFromFront(300);
	value = array.GetAt(index);
	cout << value << endl;
	//6. 맨뒤에 150을 추가한다.
	index = array.AppendFromRear(150);
	value = array.GetAt(index);
	cout << value << endl;
	//7. 3에 400을 삽입한다.
	index = array.Insert(2, 400);
	value = array.GetAt(index);
	cout << value << endl;
	//8. 4에 위치한 배열요소를 지운다.
	index = array.Delete(3);
	if (index == -1)
	{
		cout << "지워졌습니다." << endl;
	}
	//9. 맨앞에 300을 지운다.
	index = array.DeleteFromFront();
	if (index == -1)
	{
		cout << "지워졌습니다." << endl;
	}
	//10. 맨뒤에 150을 지운다.
	index = array.DeleteFromRear();
	if (index == -1)
	{
		cout << "지워졌습니다." << endl;
	}
	//11. 단일의 200을 찾는다.
	Long key = 200;
	index = array.LinearSearchUnique(&key, Compare);
	value = array.GetAt(index);
	cout << value << endl;
	//12. 맨앞에 200을 추가한다.
	index = array.AppendFromFront(200);
	value = array.GetAt(index);
	cout << value << endl;
	//13. 중복의 200을 찾는다.
	Long(*indexes);
	Long count;
	key = 200;
	array.LinearSearchDuplicate(&key, &indexes, &count, Compare);
	index = 0;
	while (index < count)
	{
		value = array.GetAt(indexes[index]);
		cout << value << endl;
		index++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//14. 4의 배열요소를 50으로 고친다.
	index = array.Modify(3, 50);
	value = array.GetAt(index);
	cout << value << endl;
	//15. 2의 위치에 250을 삽입한다.
	index = array.Insert(1, 250);
	value = array.GetAt(index);
	cout << value << endl;
	//16. 선택정렬한다.
	array.SelectionSort(Compare);
	index = 0;
	while (index < array.GetLength())
	{
		value = array.GetAt(index);
		cout << value << endl;
		index++;
	}
	//17. 이진검색으로 단일의 400을 찾는다.
	key = 400;
	index = array.BinarySearchUnique(&key, Compare);
	value = array.GetAt(index);
	cout << value << endl;
	//18. 4의 배열요소를 400으로 고친다.
	index = array.Modify(3, 400);
	value = array.GetAt(index);
	cout << value << endl;
	//19. 이진검색으로 중복의 400을 찾는다.
	key = 400;
	array.BinarySearchDuplicate(&key, &indexes, &count, Compare);
	index = 0;
	while (index < count)
	{
		value = array.GetAt(indexes[index]);
		cout << value << endl;
		index++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}
	//20. Clear한다.
	array.Clear();
	//21. capacity에 3을 입력해 one배열을 만든다.
	Array<int>one(3);
	//22. 1에 100을 저장한다.
	index = one.Store(0, 100);
	value = one.GetAt(index);
	cout << value << endl;
	//23. 2에 50을 저장한다.
	index = one.Store(1, 50);
	value = one.GetAt(index);
	cout << value << endl;
	//24. 3에 200을 저장한다.
	index = one.Store(2, 200);
	value = one.GetAt(index);
	cout << value << endl;
	//25. 버블정렬한다.
	one.BubbleSort(Compare);
	index = 0;
	while (index < one.GetLength())
	{
		value = one.GetAt(index);
		cout << value << endl;
		index++;
	}
	//26. capacity에 3을 입력해 other 배열을 만든다.
	Array<int>other(3);
	//27. 1에 70을 저장한다.
	index = other.Store(0, 70);
	value = other.GetAt(index);
	cout << value << endl;
	//28. 2에 20을 저장한다.
	index = other.Store(1, 20);
	value = other.GetAt(index);
	cout << value << endl;
	//29. 3에 300을 저장한다.
	index = other.Store(2, 300);
	value = other.GetAt(index);
	cout << value << endl;
	//30. 삽입정렬한다.
	other.InsertionSort(Compare);
	index = 0;
	while (index < other.GetLength())
	{
		value = other.GetAt(index);
		cout << value << endl;
		index++;
	}
	//31. 병합한다.
	array.Merge(one, other, Compare);
	index = 0;
	while (index < array.GetLength())
	{
		value = array.GetAt(index);
		cout << value << endl;
		index++;
	}
	//32. 복사생성자
	Array<int>theOther(array);
	index = 0;
	while (index < theOther.GetLength())
	{
		value = theOther.GetAt(index);
		cout << value << endl;
		index++;
	}
	//33. 치환연산자
	one = other;
	index = 0;
	while (index < one.GetLength())
	{
		value = one.GetAt(index);
		cout << value << endl;
		index++;
	}
	//34. 첨자연산자
	cout << array[2] << endl;
	//34. 포인터 연산자
	cout << *(array + 2) << endl;
	//테스트
	cout << "array-----------------------------------" << endl;
	index = 0;
	while (index < array.GetLength())
	{
		value = array.GetAt(index);
		cout << value << endl;
		index++;
	}
	cout << "one-----------------------------------" << endl;
	index = 0;
	while (index < one.GetLength())
	{
		value = one.GetAt(index);
		cout << value << endl;
		index++;
	}
	cout << "other-----------------------------------" << endl;
	index = 0;
	while (index < other.GetLength())
	{
		value = other.GetAt(index);
		cout << value << endl;
		index++;
	}
	cout << "theOther-----------------------------------" << endl;
	index = 0;
	while (index < theOther.GetLength())
	{
		value = theOther.GetAt(index);
		cout << value << endl;
		index++;
	}
	//36. 할당해제한다.
	return 0;
}

//함수포인터
int Compare(void* one, void* other)
{
	int* one_ = (int*)one;
	int* other_ = (int*)other;
	int ret;

	if (*one_ > * other_)
	{
		ret = 1;
	}
	else if (*one_ == *other_)
	{
		ret = 0;
	}
	else if (*one_ < *other_)
	{
		ret = -1;
	}
	return ret;
}