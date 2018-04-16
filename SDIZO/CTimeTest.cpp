#include "stdafx.h"
#include <vector>
#include <list>
#include <algorithm>


CTimeTest::CTimeTest() : gen(10000)
{
	testProcedure();
}


CTimeTest::~CTimeTest()
{
}

void CTimeTest::testProcedure()
{
	const int D_SIZE = 1000000;
	int repeats = 100;
	CFileStream file;
	for (int i = 0; i < 37; i++)
		time_table[i] = 0;
	
	do {
		//randomData(D_SIZE);
		//testArray(D_SIZE);
		//testList(D_SIZE);
		//testHeap(D_SIZE);
		testRBT(D_SIZE);
		testAVL(D_SIZE);
	   // testVector(D_SIZE);
		//testSTList(D_SIZE);
		repeats--;
	} while (repeats > 0);
		std::cout << "End of simulation";
	//file.write(time_table, 37);
}

void CTimeTest::testArray(const int SIZE)
{
	CDynamicArray testArray;
	for (int i = 0; i < SIZE; i++)
		testArray.addEnd(array[i]);
	int value = gen.randomNumber();
	time.start();
	testArray.addEnd(value);
	time_table[0] += time.elapsed();

	while (value>=SIZE || value < 0)
	{
		value = gen.randomNumber();
	}

	time.start();
	testArray.removeOnIndex(value);
	time_table[5] += time.elapsed();

	value = gen.randomNumber();
	int x = 0; // zmienna potrzebna aby program wykonal metode szukaj, 
	time.start(); // w innym wypadku pomija ja ze wzgledu na brak przechowywania zwracanej wartosci
	x = testArray.searchValue(value);
	time_table[10] += time.elapsed();
	value = gen.randomNumber();
	time.start();
	testArray.addStart(value);
	time_table[15] += time.elapsed();

	int index = -1;
	while (index>=SIZE || index < 0)
	{
		index = gen.randomNumber();
	}

	value = gen.randomNumber();
	time.start();
	testArray.addOnIndex(value, index);
	time_table[17] += time.elapsed();

	time.start();
	testArray.removeStart();
	time_table[19] += time.elapsed();

	time.start();
	testArray.removeEnd();
	time_table[21] += time.elapsed();

}

void CTimeTest::testList(const int SIZE)
{
	CLinkedList testList;
	for (int i = 0; i < SIZE; i++)
		testList.addOnEnd(array[i]);
	int value = gen.randomNumber();
	time.start();
	testList.addOnEnd(value);
	time_table[1] += time.elapsed();

	while (value>=SIZE || value < 0)
	{
		value = gen.randomNumber();
	}

	time.start();
	testList.removeOnIndex(value);
	time_table[6] += time.elapsed();

	value = gen.randomNumber();
	int x = 0;
	time.start();
	x = testList.searchValue(value);
	time_table[11] += time.elapsed();

	value = gen.randomNumber();
	time.start();
	testList.addOnStart(value);
	time_table[16] += time.elapsed();

	int index = -1;
	while (index >= SIZE || index < 0)
	{
		index = gen.randomNumber();
	}

	value = gen.randomNumber();
	time.start();
	testList.addOnIndex(value, index);
	time_table[18] += time.elapsed();

	time.start();
	testList.removeStart();
	time_table[20] += time.elapsed();

	time.start();
	testList.removeEnd();
	time_table[22] += time.elapsed();

}

void CTimeTest::testHeap(const int SIZE)
{
	CHeap testHeap;
	for (int i = 0; i < SIZE; i++)
		testHeap.add(array[i]);
	int value = gen.randomNumber();
	time.start();
	testHeap.add(value);
	time_table[2] += time.elapsed();

	value = gen.randomNumber();
	time.start();
	testHeap.removeValue(value);
	time_table[7] += time.elapsed();

	int x = 0;
	value = gen.randomNumber();
	time.start();
	x = testHeap.search(value);
	time_table[12] += time.elapsed();




}

void CTimeTest::testRBT(const int SIZE)
{
	CRedBlackTree testRBT;
	for (int i = 0; i < SIZE; i++)
		testRBT.add(array[i]);
	int value = gen.randomNumber();
	time.start();
	testRBT.add(value);
	time_table[3] += time.elapsed();

	value = gen.randomNumber();
	time.start();
	testRBT.remove(value);
	time_table[8] += time.elapsed();

	int x = 0;
	value = gen.randomNumber();
	time.start();
	x = testRBT.search(value);
	time_table[13] += time.elapsed();
	std::cout << x;


}

void CTimeTest::testAVL(const int SIZE)
{
	CAVLTree testAVL;
	for (int i = 0; i < SIZE; i++)
		testAVL.add(array[i]);
	int value = gen.randomNumber();
	time.start();
	testAVL.add(value);
	time_table[4] += time.elapsed();

	value = gen.randomNumber();
	time.start();
	testAVL.remove(value);
	time_table[9] += time.elapsed();
	int x = 0;
	value = gen.randomNumber();
	time.start();
	x = testAVL.search(value);
	time_table[14] += time.elapsed();
	std::cout << x;




}

void CTimeTest::testVector(const int SIZE)
{
	std::vector<int> testVector;
	
	for (int i = 0; i < SIZE; i++)
		testVector.push_back(array[i]);
	int value = gen.randomNumber();
	time.start();
	testVector.push_back(value);
	time_table[23] += time.elapsed();

	while (value >= SIZE || value < 0)
	{
		value = gen.randomNumber();
	}

	time.start();
	testVector.erase(testVector.begin() + value);
	time_table[25] += time.elapsed();
	
	value = gen.randomNumber();
	time.start();
	std::find(testVector.begin(), testVector.end(), value);
	time_table[27] += time.elapsed();

	value = gen.randomNumber();
	time.start();
	testVector.insert(testVector.begin() + 0, value);
	time_table[29] += time.elapsed();

	int index = -1;
	while (index >= SIZE || index < 0)
	{
		index = gen.randomNumber();
	}

	value = gen.randomNumber();
	time.start();
	auto x = testVector.insert(testVector.begin() + index, value);
	time_table[31] += time.elapsed();

	time.start();
	testVector.erase(testVector.begin() + 0);
	time_table[33] += time.elapsed();

	time.start();
	testVector.pop_back();
	time_table[35] += time.elapsed();
}

void CTimeTest::testSTList(const int SIZE)
{
	std::list<int> testList;

	for (int i = 0; i < SIZE; i++)
		testList.push_back(array[i]);
	
	int value = gen.randomNumber();
	time.start();
	testList.push_back(value);
	time_table[24] += time.elapsed();

	while (value >= SIZE || value < 0)
	{
		value = gen.randomNumber();
	}

	time.start();
	testList.remove(value);
	time_table[26] += time.elapsed();

	value = gen.randomNumber();
	time.start();
	auto y =std::find(testList.begin(), testList.end(), value);
	time_table[28] += time.elapsed();

	value = gen.randomNumber();
	time.start();
	testList.push_front(value);
	time_table[30] += time.elapsed();

	int index = -1;
	while (index >= SIZE || index < 0)
	{
		index = gen.randomNumber();
	}
	
	auto x = testList.begin();
	for (int i = 0; i < index; i++)
		x++;
	value = gen.randomNumber();
	time.start();
	testList.insert(x, value);
	time_table[32] += time.elapsed();

	time.start();
	testList.pop_front();
	time_table[34] += time.elapsed();

	time.start();
	testList.pop_back();
	time_table[36] += time.elapsed();
}