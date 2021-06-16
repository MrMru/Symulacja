#include "Generators.h"

#include <cmath>

Generators::Generators(int kernel)
{
	kernel_ = kernel;
}
Generators::~Generators()
{
	
}
double Generators::Rand()
{
	int h = floor(kernel_ / Q);
	kernel_ = A * (kernel_ - Q * h) - R * h;
	if (kernel_ < 0)
	{
		kernel_ = kernel_ + static_cast<int>(M);
	}
	return kernel_ / M;
}
int Generators::Rand(int min, int max)
{
	return Rand() * (max - min) + min;
}
int Generators::RandEXP(double lambda)
{
	auto k = Rand();
	return -(1.0 / lambda) * log(k);
}
int Generators::RandZeroOne(double probability)
{
	auto k = Rand();
	if (k < probability)
		return 1;
	else
		return 0;
}


