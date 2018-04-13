#pragma once
#include "CDynamicArray.h"
#include <iostream>
#include <string>
class CHeap :
	private CDynamicArray
{
public:
	CHeap();
	~CHeap();

	void add(int value);
	void addOnArray(int value);
	int search(int value, int index = 0);
	int pop();

	
	void buildHeap();
	void heapSort();
	void printHeap();
	void showSorted();
	

private:

	void heapify(int index);
	void printHeap(std::string sp, std::string sn, int v);
	int arraySize;


	
};
