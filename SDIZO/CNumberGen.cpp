#include "stdafx.h"

CNumberGen::CNumberGen(int maxRand) : gen(rd()), dist(1, maxRand)
{
}

int CNumberGen::randomNumber()
{
	return dist(gen);
}
