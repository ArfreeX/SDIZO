#pragma once
#include <iostream>

class CDynamicArray
{
public:

	CDynamicArray();
	virtual ~CDynamicArray();

	int searchOnIndex(int position);
	int searchValue(int value);
	void addStart(int value);
	void addEnd(int value);
	void addOnIndex(int value, int position);

	void removeEnd();
	void removeOnIndex(int position);
	void removeStart();

	void showArray();

protected:

	int *array, capacity, counter;

	void shift(int position);
	void shiftDown(int position);

	void checkSize();
	void resize();
};