#include "Array.h"
#include<stdlib.h>//free
#include<stdio.h>//printf

//함수포인터 선언
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

	//메인 테스트 시나리오
	//1. capacity에 3을 입력해 배열을 만든다.
	Create(&array, 3, sizeof(Long));
	//2. 0에 100을 저장한다.
	object = 100;
	index = Store(&array, 0, &object, sizeof(Long));
	GetAt(&array, index, &value, sizeof(Long));
	printf("%d\n", value);
	//3. 1에 50을 저장한다.
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
	//4. 2에 200을 저장한다.
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
	//5. 맨 앞에 300을 추가한다.
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

	//테스트
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}

	//6. 맨 뒤에 150을 추가한다.
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
	//7. 2에 400을 삽입한다.
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
	//8. 3에 50을 지운다.
	index = Delete(&array, 3, sizeof(Long));
	if (index == -1)
	{
		printf("지워졌습니다.\n");
	}
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//9. 맨 앞에 300을 지운다.
	index = DeleteFromFront(&array, sizeof(Long));
	if (index == -1)
	{
		printf("지워졌습니다.\n");
	}
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//10. 맨 뒤에 150을 지운다.
	index = DeleteFromRear(&array, sizeof(Long));
	if (index == -1)
	{
		printf("지워졌습니다.\n");
	}

	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//11. 단일의 200을 찾는다.
	object = 200;
	index = LinearSearchUnique(&array, &object, sizeof(Long), Compare);
	GetAt(&array, index, &value, sizeof(Long));
	printf("%d %d\n", index, value);
	//12. 맨 앞에 200을 추가한다.
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
	//13. 중복의 200을 찾는다.
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
	//14. 3의 200을 50으로 고친다.
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
	//15. 1에 250을 삽입한다.
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
	//16. 선택정렬한다.
	SelectionSort(&array, sizeof(Long), Compare);
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//17. 이진검색으로 단일의 400을 찾는다.
	object = 400;
	index = BinarySearchUnique(&array, &object, sizeof(Long), Compare);
	GetAt(&array, index, &value, sizeof(Long));
	printf("%d %d\n", index, value);
	//18. 3의 250을 400으로 고친다.
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
	//19. 이진검색으로 중복의 400을 찾는다.
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
	//20. clear한다.
	Clear(&array);
	index = 0;
	if (array.length == 0)
	{
		printf("모두 다 지워졌습니다.\n");
	}
	//21. capacity에 3을 입력해 one배열을 만든다.
	Create(&one, 3, sizeof(Long));
	//22. 0에 100을 저장한다.
	object = 100;
	index = Store(&one, 0, &object, sizeof(Long));
	GetAt(&one, index, &value, sizeof(Long));
	printf("%d\n", value);
	//23. 1에 50을 저장한다.
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
	//24. 2에 80을 저장한다.
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
	//25. 버블정렬한다.
	BubbleSort(&one, sizeof(Long), Compare);
	index = 0;
	while (index < one.length)
	{
		GetAt(&one, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//26. capacity에 3을 입력해 other배열을 만든다.
	Create(&other, 3, sizeof(Long));
	//27. 0에 70을 저장한다.
	object = 70;
	index = Store(&other, 0, &object, sizeof(Long));
	GetAt(&other, index, &value, sizeof(Long));
	printf("%d\n", value);
	//28. 1에 20을 저장한다.
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
	//29. 2에 10을 저장한다.
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
	//30. 삽입정렬한다.
	InsertionSort(&other, sizeof(Long), Compare);
	index = 0;
	while (index < other.length)
	{
		GetAt(&other, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//31. 병합한다.
	Merge(&array, &one, &other, sizeof(Long), Compare);
	index = 0;
	while (index < array.length)
	{
		GetAt(&array, index, &value, sizeof(Long));
		printf("%d ", value);
		index++;
	}
	printf("\n");
	//32. 할당해제한다.
	Destroy(&other);
	Destroy(&one);

	Destroy(&array);

	return 0;
}

//함수포인터 정의
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
