#include <vector>

#pragma once
class MyPoint
{
public:
	int dimension;
	double* vector;
	
	MyPoint(int, double* vector);
	double dot(const MyPoint*) const;
	~MyPoint(void);
};

inline bool operator==(const MyPoint p1, const MyPoint p2)
{
	if (p1.dimension != p2.dimension)
		return false;
	for(int i = 0; i < p1.dimension; ++ i)
		if (p1.vector[i] != p2.vector[i])
			return false;
	return true;
}
