#include <vector>
#include "Bucket.h"
#include "MyPoint.h"
#include "Functions.h"
#include "IAlgorithm.h"

#pragma once
class LSH : public IAlgorithm
{
public:
	LSH(std::vector<MyPoint*>* points, double eps);
	virtual MyPoint* ANN(MyPoint* q);
	virtual std::vector<MyPoint*>* ENN(MyPoint* q);
	~LSH();

private:
	double eps;
	std::vector<Bucket*> buckets;
	std::vector<MyPoint*>* points;
};

