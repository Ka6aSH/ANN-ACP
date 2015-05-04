#include <vector>
#include "Bucket.h"
#include "MyPoint.h"
#include "Functions.h"
#include "IAlgorithm.h"

#pragma once
class LSH : public IAlgorithm
{
public:
	LSH(std::vector<MyPoint*>* points, double eps, double(*distance)(const MyPoint*, const MyPoint*));
	virtual MyPoint* ANN(MyPoint* q);
	//virtual std::vector<MyPoint*>* ENN(MyPoint* q);
	~LSH();

private:
	double eps;
	double(*distance_func)(const MyPoint*, const MyPoint*);
	std::vector<Bucket*> buckets;
	std::vector<MyPoint*>* points;
};

