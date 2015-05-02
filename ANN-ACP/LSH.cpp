#include "LSH.h"


LSH::LSH(std::vector<MyPoint*>* points, double eps):
points(points), eps(eps)
{
	int d = points->at(0)->dimension;
	int k = d;
	int l = 1;
	Bucket* b;
	for (int i = 0; i < l; i++)
	{
		b = new Bucket(k, d);
		buckets.push_back(b);
		for (size_t j = 0; j < points->size(); j++)
			b->addPoint(points->at(j));
	}
}

MyPoint* LSH::ANN(MyPoint* q)
{
	double dist = std::numeric_limits<double>().max();
	double temp_dist = 0;
	MyPoint* res = nullptr;
	std::vector<MyPoint*>* temp_points;
	for (size_t i = 0; i < buckets.size(); ++i)
		if ((temp_points = buckets.at(i)->getPoints(q)) != nullptr)
			for (size_t j = 0; j < temp_points->size(); ++j)
				if ((temp_dist = l2_distance(q, temp_points->at(j))) < dist) {
					res = temp_points->at(j);
					dist = temp_dist;
				}
	return res;
}

std::vector<MyPoint*>* LSH::ENN(MyPoint* q)
{
	std::vector<MyPoint*>* result = new std::vector<MyPoint*>();
	std::vector<MyPoint*>* temp_points;
	for (auto bucket = buckets.begin(); bucket != buckets.end(); ++bucket)
		if ((temp_points = (*bucket)->getPoints(q)) != nullptr)
			for (auto point = temp_points->begin(); point != temp_points->end(); ++point)
				if (l2_distance(q, *point) < eps)
					result->push_back(*point);
	return result;
}

static bool deleteBuckets(Bucket* bucket)
{
	delete bucket;
	return true;
}

LSH::~LSH()
{
	std::remove_if(buckets.begin(), buckets.end(), deleteBuckets);
}
