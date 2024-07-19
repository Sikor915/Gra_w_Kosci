#include "Die.h"



void die::Roll()
{
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> rolled(1, 6);
	number = rolled(rng);
}

void die::set(int& numberOnDie)
{
	number = numberOnDie;
}

int die::GetNumber()
{
	return number;
}

die::die()
{
	number = 1;
	
	
}
die::~die()
{
	
}