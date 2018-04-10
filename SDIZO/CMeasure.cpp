#include "stdafx.h"
#include "CMeasure.h"

void CMeasure::start()
{
	beginning = Clock::now();
}

void CMeasure::elapsed()
{
	std::cout << std::chrono::duration_cast<TIME>(Clock::now() - beginning).count() << "ns\n";
}
