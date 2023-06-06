#include "seed.h"
#include <cmath>


auto rs::RandInt(const long long seed, const unsigned low, const unsigned high) -> int
{
	double seed_old = (1 + static_cast<double>(seed)) * static_cast<double>(125);
	double seed_new = seed_old - 8192.0 * trunc(seed_old / 8192);

	double random = (seed_new + 0.5) / 8192;

	int decLen = 0;

	while (random < 10e+6)
	{
		random *= 10;
	}
	random = static_cast<unsigned>(random) % high + static_cast<unsigned>(low);
	return static_cast<int>(random);
}
