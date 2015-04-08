#include "Bucket.h"


Bucket::Bucket(int k, int d)
{

}

int Bucket::getHash(MyPoint* p)
{

}

void Bucket::addPoint(MyPoint* p)
{
	int hash = getHash(p);
	if (points.find(hash) == points.end()) {
		points.insert(std::pair<int, std::vector<MyPoint*>>(hash, std::vector<MyPoint*>()));
	}
	points.at(hash).push_back(p);
}

std::vector<MyPoint*> Bucket::getPoints(MyPoint* q)
{
	return points.at(getHash(q));
}

Bucket::~Bucket()
{
}
