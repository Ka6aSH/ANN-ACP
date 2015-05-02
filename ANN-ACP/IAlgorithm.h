#ifndef IALGORITHM_HEADER
#define IALGORITHM_HEADER
#include "MyPoint.h"

class IAlgorithm
{
public:
	virtual MyPoint* ANN(MyPoint*) = 0;
	virtual std::vector<MyPoint*>* ENN(MyPoint*) = 0;
};

#endif