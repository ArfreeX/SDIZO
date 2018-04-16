#pragma once
#include "CNumberGen.h"
#include "CMeasure.h"

class CTimeTest : private CInterface
{
public:
	CTimeTest();
	~CTimeTest();
private:

	void testProcedure();
	void testArray(const int SIZE);
	void testList(const int SIZE);
	void testHeap(const int SIZE);
	void testRBT(const int SIZE);
	void testAVL(const int SIZE);
	void testVector(const int SIZE);
	void testSTList(const int SIZE);
	
	CNumberGen gen;
	CMeasure time;
	long long int time_table[37];
};

