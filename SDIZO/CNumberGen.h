#pragma once
#include <random>

class CNumberGen
{
public:
	CNumberGen(int maxRand);
	int randomNumber();
	~CNumberGen();
private:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;
};

