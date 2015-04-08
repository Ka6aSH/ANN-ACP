#include "MyPoint.h"
#include <random>

#pragma once
class HashFunction
{
public:
	double w = 4;
	MyPoint* a;
	double b;

	HashFunction(int d);

	int getHash(const MyPoint* p);

	~HashFunction();
};

