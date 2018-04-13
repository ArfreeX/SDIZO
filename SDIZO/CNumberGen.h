#pragma once
#include <random>

class CNumberGen // source http://antoni.sterna.staff.iiar.pwr.wroc.pl/sdizo/SDiZO_random.pdf
{
public:
	CNumberGen(int maxRand);
	int randomNumber();
private:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> dist;
};

