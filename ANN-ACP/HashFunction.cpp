#include "HashFunction.h"


HashFunction::HashFunction(int d)
{
	double* temp = new double[d];
	std::default_random_engine generator(rand());
	std::normal_distribution<double> distribution_norm(0, 1);
	std::uniform_real_distribution<double> distribution_uni(0.0, 1.0);

	for (int i = 0; i < d; ++i) {
		temp[i] = distribution_norm(generator);
	}
	a = new MyPoint(d, temp);
	b = distribution_uni(generator) * w;
}

int HashFunction::getHash(const MyPoint* p)
{
	return (int)((a->dot(p) + b) / w);
}


HashFunction::~HashFunction()
{
	delete a;
}
