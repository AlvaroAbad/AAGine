#include <conio.h>
#include "Essentials.h"
#include "Array.h"

bool sortInt(int& first, int& second) {
	return first > second;
}

int main() {
	Array<int> intArray(5);
	intArray.Push(1);
	intArray.Push(5);
	intArray.Push(7);
	intArray.Push(3);
	intArray.Push(5);
	intArray.Push(10);
	intArray.Push(6);
	intArray.Push(23);
	intArray.Push(5);
	intArray.Push(5);
	intArray.Push(51);
	intArray.Push(5);
	intArray.Push(12);
	intArray.Push(35);

	printf("TEST OF NEXT METHOD\n");
	for (uint32 i = 0; i < intArray.Size()*2; i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}
	printf("TEST OF [] OVERRIDE\n");
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray[i]);
	}

	printf("TEST OF POPLAST AND LAST METHOD\n");
	printf("Last: %i\n", intArray.Last());
	int printableInt = intArray.PopLast();
	printf("PopedLast: %i\n",printableInt);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}
	printf("Last: %i\n", intArray.Last());
	printableInt = intArray.PopLast();
	printf("PopedLast: %i\n", printableInt);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}

	printf("TEST OF POPFIRST AND FIRST METHOD\n");
	printf("First: %i\n", intArray.first());
	printableInt = intArray.PopFirst();
	printf("PopedFirst: %i\n", printableInt);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}
	printf("First: %i\n", intArray.first());
	printableInt = intArray.PopFirst();
	printf("PopedFirst: %i\n", printableInt);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}

	printf("TEST OF INSERT METHOD\n");
	printf("old [3] Value: %i\n", intArray[3]);
	int testInsertion = 20;
	intArray.Insert(3, testInsertion);
	printf("new [3] Value: %i\n", intArray[3]);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}

	printf("TEST OF SET METHOD\n");
	printf("[4]: %i\n", intArray[4]);
	int testSet = 15;
	intArray.Set(4, testSet);
	printf("[4]: %i\n", intArray[4]);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}

	printf("TEST OF REMOVE METHOD\n");
	int testRemove = 7;
	intArray.Remove(testRemove);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}

	printf("TEST OF REMOVEAT METHOD\n");
	printf("[1]: %i\n", intArray[1]);
	intArray.RemoveAt(1);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}

	printf("TEST OF REMOVEALL METHOD\n");
	int testRemoveAll = 5;
	intArray.RemoveAll(testRemoveAll);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}
	printf("TEST OF SORT METHOD\n");
	intArray.Sort(sortInt);
	for (uint32 i = 0; i < intArray.Size(); i++) {
		printf("[%i]: %i\n", i, intArray.Next());
	}

	getchar();
}