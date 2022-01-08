#include "Array.h"
#include<iostream>
using namespace std;
#pragma warning(disable:4996)

int Compare(void* one, void* other);//�Լ�������

int main(int argc, char* argv[])
{
	//1. capacity�� 3�� �Է��� �迭�� �����.
	Array<int>array(3);
	//2. 1�� 100�� �����Ѵ�.
	Long index;
	index = array.Store(0, 100);
	int value;
	value = array.GetAt(index);
	cout << value << endl;
	//3. 2�� 50�� �����Ѵ�.
	index = array.Store(1, 50);
	value = array.GetAt(index);
	cout << value << endl;
	//4. 3�� 200�� �����Ѵ�.
	index = array.Store(2, 200);
	value = array.GetAt(index);
	cout << value << endl;
	//5. �Ǿտ� 300�� �߰��Ѵ�.
	index = array.AppendFromFront(300);
	value = array.GetAt(index);
	cout << value << endl;
	//6. �ǵڿ� 150�� �߰��Ѵ�.
	index = array.AppendFromRear(150);
	value = array.GetAt(index);
	cout << value << endl;
	//7. 3�� 400�� �����Ѵ�.
	index = array.Insert(2, 400);
	value = array.GetAt(index);
	cout << value << endl;
	//8. 4�� ��ġ�� �迭��Ҹ� �����.
	index = array.Delete(3);
	if (index == -1)
	{
		cout << "���������ϴ�." << endl;
	}
	//9. �Ǿտ� 300�� �����.
	index = array.DeleteFromFront();
	if (index == -1)
	{
		cout << "���������ϴ�." << endl;
	}
	//10. �ǵڿ� 150�� �����.
	index = array.DeleteFromRear();
	if (index == -1)
	{
		cout << "���������ϴ�." << endl;
	}
	//11. ������ 200�� ã�´�.
	Long key = 200;
	index = array.LinearSearchUnique(&key, Compare);
	value = array.GetAt(index);
	cout << value << endl;
	//12. �Ǿտ� 200�� �߰��Ѵ�.
	index = array.AppendFromFront(200);
	value = array.GetAt(index);
	cout << value << endl;
	//13. �ߺ��� 200�� ã�´�.
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
	//14. 4�� �迭��Ҹ� 50���� ��ģ��.
	index = array.Modify(3, 50);
	value = array.GetAt(index);
	cout << value << endl;
	//15. 2�� ��ġ�� 250�� �����Ѵ�.
	index = array.Insert(1, 250);
	value = array.GetAt(index);
	cout << value << endl;
	//16. ���������Ѵ�.
	array.SelectionSort(Compare);
	index = 0;
	while (index < array.GetLength())
	{
		value = array.GetAt(index);
		cout << value << endl;
		index++;
	}
	//17. �����˻����� ������ 400�� ã�´�.
	key = 400;
	index = array.BinarySearchUnique(&key, Compare);
	value = array.GetAt(index);
	cout << value << endl;
	//18. 4�� �迭��Ҹ� 400���� ��ģ��.
	index = array.Modify(3, 400);
	value = array.GetAt(index);
	cout << value << endl;
	//19. �����˻����� �ߺ��� 400�� ã�´�.
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
	//20. Clear�Ѵ�.
	array.Clear();
	//21. capacity�� 3�� �Է��� one�迭�� �����.
	Array<int>one(3);
	//22. 1�� 100�� �����Ѵ�.
	index = one.Store(0, 100);
	value = one.GetAt(index);
	cout << value << endl;
	//23. 2�� 50�� �����Ѵ�.
	index = one.Store(1, 50);
	value = one.GetAt(index);
	cout << value << endl;
	//24. 3�� 200�� �����Ѵ�.
	index = one.Store(2, 200);
	value = one.GetAt(index);
	cout << value << endl;
	//25. ���������Ѵ�.
	one.BubbleSort(Compare);
	index = 0;
	while (index < one.GetLength())
	{
		value = one.GetAt(index);
		cout << value << endl;
		index++;
	}
	//26. capacity�� 3�� �Է��� other �迭�� �����.
	Array<int>other(3);
	//27. 1�� 70�� �����Ѵ�.
	index = other.Store(0, 70);
	value = other.GetAt(index);
	cout << value << endl;
	//28. 2�� 20�� �����Ѵ�.
	index = other.Store(1, 20);
	value = other.GetAt(index);
	cout << value << endl;
	//29. 3�� 300�� �����Ѵ�.
	index = other.Store(2, 300);
	value = other.GetAt(index);
	cout << value << endl;
	//30. ���������Ѵ�.
	other.InsertionSort(Compare);
	index = 0;
	while (index < other.GetLength())
	{
		value = other.GetAt(index);
		cout << value << endl;
		index++;
	}
	//31. �����Ѵ�.
	array.Merge(one, other, Compare);
	index = 0;
	while (index < array.GetLength())
	{
		value = array.GetAt(index);
		cout << value << endl;
		index++;
	}
	//32. ���������
	Array<int>theOther(array);
	index = 0;
	while (index < theOther.GetLength())
	{
		value = theOther.GetAt(index);
		cout << value << endl;
		index++;
	}
	//33. ġȯ������
	one = other;
	index = 0;
	while (index < one.GetLength())
	{
		value = one.GetAt(index);
		cout << value << endl;
		index++;
	}
	//34. ÷�ڿ�����
	cout << array[2] << endl;
	//34. ������ ������
	cout << *(array + 2) << endl;
	//�׽�Ʈ
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
	//36. �Ҵ������Ѵ�.
	return 0;
}

//�Լ�������
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