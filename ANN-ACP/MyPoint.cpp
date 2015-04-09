#include "MyPoint.h"


MyPoint::MyPoint(int d, double* arr) : dimension(d), vector(arr) {}

double MyPoint::dot(const MyPoint* point)
{
	double res = 0;
	for (int i = 0; i < dimension; ++i) {
		res += vector[i] * point->vector[i];
	}
	return res;
}

MyPoint::~MyPoint(void)
{
	delete[] vector;
}
