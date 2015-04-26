#include <vector>
#include "Bucket.h"
#include "MyPoint.h"
#include "Functions.h"

#pragma once
class LSH
{
public:
	LSH(std::vector<MyPoint*>* points, double eps);
	MyPoint* ANN(MyPoint* q);
	~LSH();

private:
	double eps;
	std::vector<Bucket*> buckets;
	std::vector<MyPoint*>* points;
};

