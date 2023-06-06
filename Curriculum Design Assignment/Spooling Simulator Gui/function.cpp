// Spooling Simulation build in 2021.07.01
// file name: function.cpp
// Edit by @Michael Zhou
#include "pch.h"
#include "Foundation_Data.h"
#include <ctime>
#include <ios>
#include <random>
#include "WinRandom.h"

double GetRandomDouble(const double min, const double max)
{
	std::uniform_real_distribution<double> dist(min, max);
	std::default_random_engine random(static_cast<unsigned>(time(nullptr)));
	return dist(random);
}

int GetRandomInteger(const int min, const int max)
{
	static unsigned int seed = 0;
	seed++;
	srand(static_cast<unsigned>(time(nullptr)) + seed * seed);
	return rand() % (max - min) + min;
}
