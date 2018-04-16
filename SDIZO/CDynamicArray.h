#pragma once
#include <iostream>

class CDynamicArray
{
public:

	CDynamicArray();
	~CDynamicArray();

	int searchOnIndex(int position);
	int searchValue(int value);

	void addStart(int value);
	void addEnd(int value);
	void addOnIndex(int value, int position);

	void removeEnd();
	void removeOnIndex(int position);
	void removeStart();

	void printArray();

protected:

	void shift(int position);
	void shiftDown(int position);
	void resizeDown(int position);
	void adaptSize(int shiftedIndex = -1);
	void resize(int shiftedIndex = -1);

	int *array, capacity, counter;
};