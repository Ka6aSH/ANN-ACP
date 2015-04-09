#include "Functions.h"

double l2_distance(const MyPoint* p1, const MyPoint* p2)
{
	double sum = 0;
	for (int i = 0; i < p1->dimension; ++ i)
		sum += (p1->vector[i] - p2->vector[i]) * (p1->vector[i] - p2->vector[i]);
	return sqrt(sum);
}

std::string bits(int n)
{
	std::ostringstream tmp;
	while (n) 
	{ 
		tmp << (n & 1) ? "1" : "0";  
		n >>= 1; 
	}
	return tmp.str();
}