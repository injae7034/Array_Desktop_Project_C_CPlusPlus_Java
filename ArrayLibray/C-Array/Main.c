#include "Array.h"
#include<stdlib.h>//free
#include<stdio.h>//printf

//�Լ������� ����
int Compare(void* one, void* other);

int main(int argc, char* argv[])
{
	Array array;
	Array one;
	Array other;
	Long index;
	Long(*indexes);
	Long count;
	Long object;
	Long value;

	//���� �׽�Ʈ �ó�����
	//1. capacity�� 3�� �Է��� �迭�� �����.
	Create(&array, 3, sizeof(Long));
	//2. 0�� 100�� �����Ѵ�.
	object = 100;
	index = Store(&array, 0, &object, sizeof(Long));
	GetAt(&array, index, &value, sizeof(Long));
	printf("%d\n", value);
	//3. 1�� 50�� �����Ѵ�.
	object = 50;
	index = Store(&array, 1, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//4. 2�� 200�� �����Ѵ�.
	object = 200;
	index = Store(&array, 2, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//5. �� �տ� 300�� �߰��Ѵ�.
	object = 300;
	index = AppendFromFront(&array, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");

	//�׽�Ʈ
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}

	//6. �� �ڿ� 150�� �߰��Ѵ�.
	object = 150;
	index = AppendFromRear(&array, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//7. 2�� 400�� �����Ѵ�.
	object = 400;
	index = Insert(&array, 2, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//8. 3�� 50�� �����.
	index = Delete(&array, 3, sizeof(Long));
	if (index == -1)
	{
		printf("���������ϴ�.\n");
	}
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//9. �� �տ� 300�� �����.
	index = DeleteFromFront(&array, sizeof(Long));
	if (index == -1)
	{
		printf("���������ϴ�.\n");
	}
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//10. �� �ڿ� 150�� �����.
	index = DeleteFromRear(&array, sizeof(Long));
	if (index == -1)
	{
		printf("���������ϴ�.\n");
	}

	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//11. ������ 200�� ã�´�.
	object = 200;
	index = LinearSearchUnique(&array, &object, sizeof(Long), Compare);
	GetAt(&array, index, &value, sizeof(Long));
	printf("%d %d\n", index, value);
	//12. �� �տ� 200�� �߰��Ѵ�.
	object = 200;
	index = AppendFromFront(&array, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//13. �ߺ��� 200�� ã�´�.
	object = 200;
	LinearSearchDuplicate(&array, &object, &indexes, &count, sizeof(Long), Compare);
	index = 0;
	while (index < count)
	{
		GetAt(&array, indexes[index], &value, sizeof(Long));
		printf("%d %d  ", indexes[index], value);
		index++;
	}
	printf("\n");
	if (indexes != NULL)
	{
		free(indexes);
	}
	//14. 3�� 200�� 50���� ��ģ��.
	object = 50;
	index = Modify(&array, 3, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//15. 1�� 250�� �����Ѵ�.
	object = 250;
	index = Insert(&array, 1, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//16. ���������Ѵ�.
	SelectionSort(&array, sizeof(Long), Compare);
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//17. �����˻����� ������ 400�� ã�´�.
	object = 400;
	index = BinarySearchUnique(&array, &object, sizeof(Long), Compare);
	GetAt(&array, index, &value, sizeof(Long));
	printf("%d %d\n", index, value);
	//18. 3�� 250�� 400���� ��ģ��.
	object = 400;
	index = Modify(&array, 3, &object, sizeof(Long));
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//19. �����˻����� �ߺ��� 400�� ã�´�.
	object = 400;
	BinarySearchDuplicate(&array, &object, &indexes, &count, sizeof(Long), Compare);
	index = 0;
	while (index < count)
	{
		GetAt(&array, indexes[index], &value, sizeof(Long));
		printf("%d %d  ", indexes[index], value);
		index++;
	}
	printf("\n");
	if (indexes != NULL)
	{
		free(indexes);
	}
	//20. clear�Ѵ�.
	Clear(&array);
	index = 0;
	if (array.length == 0)
	{
		printf("��� �� ���������ϴ�.\n");
	}
	//21. capacity�� 3�� �Է��� one�迭�� �����.
	Create(&one, 3, sizeof(Long));
	//22. 0�� 100�� �����Ѵ�.
	object = 100;
	index = Store(&one, 0, &object, sizeof(Long));
	GetAt(&one, index, &value, sizeof(Long));
	printf("%d\n", value);
	//23. 1�� 50�� �����Ѵ�.
	object = 50;
	index = Store(&one, 1, &object, sizeof(Long));
	index = 0;
	while (index < one.length)
	{
		GetAt(&one, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//24. 2�� 80�� �����Ѵ�.
	object = 80;
	index = Store(&one, 2, &object, sizeof(Long));
	index = 0;
	while (index < one.length)
	{
		GetAt(&one, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//25. ���������Ѵ�.
	BubbleSort(&one, sizeof(Long), Compare);
	index = 0;
	while (index < one.length)
	{
		GetAt(&one, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//26. capacity�� 3�� �Է��� other�迭�� �����.
	Create(&other, 3, sizeof(Long));
	//27. 0�� 70�� �����Ѵ�.
	object = 70;
	index = Store(&other, 0, &object, sizeof(Long));
	GetAt(&other, index, &value, sizeof(Long));
	printf("%d\n", value);
	//28. 1�� 20�� �����Ѵ�.
	object = 20;
	index = Store(&other, 1, &object, sizeof(Long));
	index = 0;
	while (index < other.length)
	{
		GetAt(&other, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//29. 2�� 10�� �����Ѵ�.
	object = 10;
	index = Store(&other, 2, &object, sizeof(Long));
	index = 0;
	while (index < other.length)
	{
		GetAt(&other, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//30. ���������Ѵ�.
	InsertionSort(&other, sizeof(Long), Compare);
	index = 0;
	while (index < other.length)
	{
		GetAt(&other, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//31. �����Ѵ�.
	Merge(&array, &one, &other, sizeof(Long), Compare);
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//32. �Ҵ������Ѵ�.
	Destroy(&other);
	Destroy(&one);

	Destroy(&array);

	return 0;
}

//�Լ������� ����
int Compare(void* one, void* other)
{
	Long* one_ = (Long*)one;
	Long* other_ = (Long*)other;
	int ret;
	if (*one_ > *other_)
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
