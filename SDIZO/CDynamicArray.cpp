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
	adaptSize(0);
	array[0] = value;
	counter++;
}

void CDynamicArray::addEnd(int value)
{
	adaptSize();
	array[counter] = value;
	counter++;
}

void CDynamicArray::addOnIndex(int value, int position)
{
	if (position == 0)
		addStart(value);
	else if (position == counter)
		addEnd(value);
	else if (position > counter)
		std::cout << "Invalid index";
	else if (position > 0)
	{
		adaptSize(position);
		array[position] = value;
		counter++;
	}
	else
		std::cout << "Invalid index";
}

void CDynamicArray::removeEnd()
{
	resizeDown(counter-1);
}

void CDynamicArray::removeOnIndex(int position)
{
	if (position < counter && position >= 0)
		resizeDown(position);
}

void CDynamicArray::removeStart()
{
	resizeDown(0);
}

void CDynamicArray::printArray()
{
	for (int i = 0; i < counter; i++)
	{
		std::cout <<i<<". "<< array[i] << std::endl;
	}
	std::cout << "Size (capacity): " << capacity << std::endl;
	std::cout << "Number of elements: " << counter << std::endl;
}

void CDynamicArray::shift(int position)
{
	if (counter == capacity)
	{

	}
	else
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

void CDynamicArray::resizeDown(int position)
{
	if (counter > 0)
	{
		int* temp = new int[--capacity];
		counter--;
		if (position != -1 && position >= 0)
		{
			for (int i = counter-1; i >= position; i--)
				temp[i] = array[i+1];
			for (int i = position - 1; i >= 0; i--)
				temp[i] = array[i];
			delete[] array;
			array = temp;
		}
	}
}

void CDynamicArray::adaptSize(int shiftedIndex)
{
	if (array == nullptr)
	{
		array = new int[++capacity];
		return;
	}
	if (counter == capacity)
	{
		if (shiftedIndex != -1)
			resize(shiftedIndex);
		else
			resize();
	}
	else if (counter < capacity && shiftedIndex != -1)
		shift(shiftedIndex);
}

void CDynamicArray::resize(int shiftedIndex)
{
	int *temp_array = new int[++capacity];

	if (shiftedIndex != -1)
	{
		for (int i = 0; i < shiftedIndex; i++)
			temp_array[i] = array[i];
		for (int i = shiftedIndex + 1; i < capacity; i++)
			temp_array[i] = array[i-1];
	}
	else
	{
		for (int i = 0; i < capacity - 1; i++)
			temp_array[i] = array[i];
	}
	delete[] array;
	array = temp_array;
}
