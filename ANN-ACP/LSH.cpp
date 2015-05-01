#include "LSH.h"


LSH::LSH(std::vector<MyPoint*>* points, double eps):
points(points), eps(eps)
{
	int d = points->at(0)->dimension;
	int k = d;
	int l = (int)(std::log(0.9) / std::log(1 - std::pow(0.9, k))) + 1;
	Bucket* b;
	for (int i = 0; i < l; i++)
	{
		b = new Bucket(k, d);
		buckets.push_back(b);
		for (int j = 0; j < points->size(); j++)
			b->addPoint(points->at(j));
	}
}

MyPoint* LSH::ANN(MyPoint* q)
{
	double dist = std::numeric_limits<double>().max();
	double temp_dist = 0;
	MyPoint* res = nullptr;
	std::vector<MyPoint*>* temp_points;
	for (int i = 0; i < buckets.size(); ++i)
		if ((temp_points = buckets.at(i)->getPoints(q)) != nullptr)
			for (int j = 0; j < temp_points->size(); ++j)
				if ((temp_dist = l2_distance(q, temp_points->at(j))) < dist) {
					res = temp_points->at(j);
					dist = temp_dist;
				}
	return res;
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
