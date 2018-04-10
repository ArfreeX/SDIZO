#pragma once
#include "CDynamicArray.h"
#include <iostream>
#include <string>
class CHeap :
	private CDynamicArray
{
public:
	CHeap();
	void add(int value);
	int search(int value);
	int push();
	void printHeap();
	void buildHeap();
	void heapSort();
	void showSorted();
	~CHeap();

private:

	void heapify(int index);
	void printHeap(std::string sp, std::string sn, int v);
	int arraySize = 0;


	
};
