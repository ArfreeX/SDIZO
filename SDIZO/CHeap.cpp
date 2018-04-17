#include "stdafx.h"




CHeap::CHeap() : CDynamicArray()
{
	arraySize = 0;
}

CHeap::~CHeap()
{
	//delete[] array;// array destuctor handles freeing memory;
}

void CHeap::add(int value)
{
	adaptSize();		// CDynamicArray:: ; check: if array == nullptr && if size == capacity, resize table;
	int index = counter++;
	array[index] = value;

	while (index > 0 && array[index] > array[(index - 1) / 2]) // sprawdzenie czy dziecko jest wieksze od rodzica
	{
		int temp = array[(index - 1) / 2];
		array[(index - 1) / 2] = array[index];
		array[index] = temp;		// zamiana dziecka z rodzicem miejscami

		index = (index - 1) / 2; // za indeks przyjmujemy indeks rodzica
	}
}

void CHeap::addOnArray(int value)
{
	addEnd(value);
}

int CHeap::search(int value, int index)
{
	int temp = 0;
	if (value == array[index])
		return index;
	if (2 * index + 1 < counter && value <= array[2 * index + 1])
	{
		temp = search(value, 2 * index + 1);
		if (temp != -1)
			return temp;
	}
	if (2 * index + 2 < counter && value <= array[2 * index + 2])
	{
		temp = search(value, 2 * index + 2);
		if (temp != -1)
			return temp;
	}
	return -1;	
}

int CHeap::pop()		// returns max value and remove it from the array
{
	int value = array[0];
	int index = --counter;
	array[0] = array[index];
	heapify(0);

	return value;
}

void CHeap::removeValue(int value)		//search value and then remove it from the array
{
	int index2 = search(value);
	if (index2 != -1)
	{
		int index = (counter - 1);
		array[index2] = array[index];
		resizeDown(index);
		heapify(index2);
	}
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
		array[i] = pop();
		heapify(i);
	}
	counter = arraySize;
}

void CHeap::printHeap()
{
	printHeap("", "", 0);
}

void CHeap::showSorted()
{
	for (int i = 0; i < arraySize; i++)
		std::cout<< array[i] << " ";
}

//============= private methods =============

void CHeap::heapify(int index)
{
	int indxLeft, indxRight, indxParent;

	indxLeft = index * 2 + 1;
	indxRight = index * 2 + 2;

	if (indxLeft < counter && array[index] < array[indxLeft]) // porownanie z lewym dzieckiem
		indxParent = indxLeft;
	else
		indxParent = index;

	if (indxRight < counter && array[indxParent] < array[indxRight]) // porownanie z 'parentem'
		indxParent = indxRight;

	if (indxParent != index) // jezeli jakiekolwiek dziecko > od rodzica wtedy swappujemy
	{
		std::swap(array[index], array[indxParent]);
		heapify(indxParent); // rekurencyjne wywolanie po swappie dla dziecka, sprawdzamy warunek kopca poziom nizej
	}
}

void CHeap::printHeap(std::string sp, std::string sn, int v) // source: http://eduinf.waw.pl/inf/alg/001_search/0113.php
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
