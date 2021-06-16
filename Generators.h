#ifndef GENERATORS_H_
#define GENERATORS_H_
class Generators
{
private:
	int kernel_;
	const double M = 2147483647.0;
	static const int A = 16807;
	static const int Q = 127773;
	static const int R = 2836;
public:
	Generators(int seed);
	~Generators();

	double Rand();
	int Rand(int min, int max);
	int RandEXP(double lambda);
	int RandZeroOne(double probability);
	int get_kernel() { return kernel_; }

};

#endif
