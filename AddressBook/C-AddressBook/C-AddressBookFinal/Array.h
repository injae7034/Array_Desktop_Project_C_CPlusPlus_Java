#ifndef _ARRAY_H
#define _ARRAY_H
#include<stddef.h>//size_t

typedef signed long int Long;
typedef enum _boolean { ARRAY_FALSE=0, ARRAY_TRUE=1 }Boolean;
typedef struct _array
{
	void(*front);
	Long capacity;
	Long length;
}Array;

void Create(Array* array, Long capacity, size_t size);
void GetAt(Array* array, Long index, void* object, size_t size);
//Insert
Long Store(Array* array, Long index, void* object, size_t size);
Long Insert(Array* array, Long index, void* object, size_t size);
Long AppendFromFront(Array* array, void* object, size_t size);
Long AppendFromRear(Array* array, void* object, size_t size);
//Delete
Long Delete(Array* array, Long index, size_t size);
Long DeleteFromFront(Array* array, size_t size);
Long DeleteFromRear(Array* array, size_t size);
void Clear(Array* array);
//Modify
Long Modify(Array* array, Long index, void* object, size_t size);
//Search
Long LinearSearchUnique(Array* array, void* key, size_t size, int (*compare)(void*, void*));
void LinearSearchDuplicate(Array* array, void* key, Long* (*indexes), Long* count,
	size_t size, int (*compare)(void*, void*));
Long BinarySearchUnique(Array* array, void* key, size_t size, int (*compare)(void*, void*));
void BinarySearchDuplicate(Array* array, void* key, Long* (*indexes), Long* count,
	size_t size, int (*compare)(void*, void*));
//Sort
void SelectionSort(Array* array, size_t size, int (*compare)(void*, void*));
void BubbleSort(Array* array, size_t size, int (*compare)(void*, void*));
void InsertionSort(Array* array, size_t size, int (*compare)(void*, void*));
void Merge(Array* array, Array* one, Array* other, size_t size, int (*compare)(void*, void*));
void Destroy(Array* array);

#endif // !_ARRAY_H
