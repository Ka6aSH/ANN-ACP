#include <vector>
#include <algorithm>
#include "HashFunction.h"
#include <map>

#pragma once
class Bucket
{
public:
	std::vector<HashFunction*> functions;
	std::map<int, std::vector<MyPoint*>> points;

	Bucket(int k, int d);
	int getHash(MyPoint* p);
	void addPoint(MyPoint* p);
	std::vector<MyPoint*>* getPoints(MyPoint* q);

	~Bucket();
};

