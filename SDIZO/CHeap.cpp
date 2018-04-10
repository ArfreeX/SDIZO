#include "stdafx.h"



CHeap::CHeap() : CDynamicArray()
{
}

void CHeap::add(int value)
{
	checkSize();
	int index = counter++;
	array[index] = value;

	while (index > 0 && array[index] > array[(index - 1) / 2])
	{
		int temp = array[(index - 1) / 2];
		array[(index - 1) / 2] = array[index];
		array[index] = temp;

		index = (index - 1) / 2;
	}
}

int CHeap::search(int value)
{
	return searchValue(value);
}

int CHeap::push()
{
	int value = array[0];
	int index = --counter;
	array[0] = array[index];
	heapify(0);

	return value;
}

void CHeap::printHeap()
{
	printHeap("", "", 0);
}

void CHeap::buildHeap()
{
	for (int i = 0; i < counter; i++)
		heapify(i);
}

void CHeap::heapSort()
{
	arraySize = counter;
	buildHeap();
	for (int i = counter - 1; i > 0; i--)
	{
		array[i] = push();
		heapify(i);
	}
}

void CHeap::showSorted()
{
	for (int i = 0; i < arraySize; i++)
		std::cout<< array[i] << " ";
}
void CHeap::heapify(int index)
{
	int indxLeft, indxRight, indxParent;

	indxLeft = index * 2 + 1;
	indxRight = index * 2 + 2;

	if (indxLeft < counter && array[index] < array[indxLeft])
		indxParent = indxLeft;
	else
		indxParent = index;

	if (indxRight < counter && array[indxParent] < array[indxRight])
		indxParent = indxRight;

	if (indxParent != index)
	{
		std::swap(array[index], array[indxParent]);
		heapify(indxParent);
	}
}

void CHeap::printHeap(std::string sp, std::string sn, int v)
{
	std::string s, cr, cl, cp;
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	if (v < counter)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		printHeap(s + cp, cr, 2 * v + 2);

		s = s.substr(0, sp.length() - 2);

		std::cout << s << sn << array[v] << std::endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		printHeap(s + cp, cl, 2 * v + 1);
	}
}

CHeap::~CHeap()
{
}
