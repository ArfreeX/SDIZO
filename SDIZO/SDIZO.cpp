// SDIZO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"





int main()
{
	CHeap kopiec;
	kopiec.add(10);
	kopiec.add(5);
	kopiec.add(20);
	kopiec.add(500);
	kopiec.add(-10);
	kopiec.add(53);
	kopiec.printHeap();
	kopiec.heapSort();
	kopiec.showSorted();
	system("PAUSE");
	return 0;
}
