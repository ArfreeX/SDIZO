#include "stdafx.h"



CDynamicArray::CDynamicArray()
{
	array = nullptr;
	capacity = 0;
	counter = 0;
}


CDynamicArray::~CDynamicArray()
{
	delete[] array;
}


int CDynamicArray::searchOnIndex(int position)
{
	if (position >= counter)
	{
		std::cout << "Invalid index";
		return 0;
	}

	return array[position];
}

int CDynamicArray::searchValue(int value)
{
	for (int i = 0; i < counter; i++)
		if (array[i] == value)
			return i;
	return -1;
}

void CDynamicArray::addStart(int value)
{
	checkSize();
	shift(0);
	array[0] = value;
	counter++;
}

void CDynamicArray::addEnd(int value)
{
	checkSize();
	array[counter] = value;
	counter++;
}

void CDynamicArray::addOnIndex(int value, int position)
{
	checkSize();
	if (position == 0)
		addStart(value);
	else if (position == counter)
		addEnd(value);
	else if (position > counter)
		std::cout << "Invalid index";
	else
	{
		shift(position);
		array[position] = value;
	}
}

void CDynamicArray::removeEnd()
{
	counter--;
}

void CDynamicArray::removeOnIndex(int position)
{
	if (position < counter)
		shiftDown(position);
}

void CDynamicArray::removeStart()
{
	shiftDown(0);
}

void CDynamicArray::showArray()
{
	for (int i = 0; i < counter; i++)
	{
		std::cout << array[i] << std::endl;
	}
	std::cout << "Size is: " << capacity << std::endl;
}

void CDynamicArray::shift(int position)
{
	for (int i = counter; i > position; i--)
	{
		array[i] = array[i - 1];
	}
}

void CDynamicArray::shiftDown(int position)
{
	for (int i = position; i < capacity - 1; i++)
	{
		array[i] = array[i + 1];
	}
	counter--;
}

void CDynamicArray::checkSize()
{
	if (array == nullptr)
	{
		array = new int[++capacity];
	}
	else if (counter == capacity)
		resize();
}

void CDynamicArray::resize()
{
	int *temp_array = new int[++capacity];

	for (int i = 0; i < capacity-1; i++)
		temp_array[i] = array[i];

	delete[] array;
	array = temp_array;
}
