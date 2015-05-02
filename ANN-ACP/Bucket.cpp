#include "Bucket.h"


Bucket::Bucket(int k, int d)
{
	while (k-- > 0)
		functions.push_back(new HashFunction(d));
}

int Bucket::getHash(MyPoint* p)
{
	int hash = 1;
	for (size_t i = 0; i < functions.size(); ++i)
		hash = 32 * hash + functions.at(i)->getHash(p);
	return hash;
}

void Bucket::addPoint(MyPoint* p)
{
	int hash = getHash(p);
	if (points.find(hash) == points.end())
		points.insert(std::pair<int, std::vector<MyPoint*>>(hash, std::vector<MyPoint*>()));
	points.at(hash).push_back(p);
}

std::vector<MyPoint*>* Bucket::getPoints(MyPoint* q)
{
	int hash = getHash(q);
	if (points.find(hash) == points.end()) {
		return nullptr;
	}
	return &points.at(hash);
}

static bool deleteHashFunctions(HashFunction* hash_func) 
{ 
	delete hash_func; 
	return true;
}


Bucket::~Bucket()
{
	std::remove_if(functions.begin(), functions.end(), deleteHashFunctions);
}
