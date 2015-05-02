#include "Functions.h"

double l2_distance(const MyPoint* p1, const MyPoint* p2)
{
	double sum = 0;
	for (int i = 0; i < p1->dimension; ++ i)
		sum += (p1->vector[i] - p2->vector[i]) * (p1->vector[i] - p2->vector[i]);
	return sqrt(sum);
}

double sphere_distance(const MyPoint* p1, const MyPoint* p2)
{
	return std::acos(p1->dot(p1) + p2->dot(p2));
}

MyPoint* linear_method(std::vector<MyPoint*>* points, const MyPoint* q)
{
	MyPoint* result = points->at(0);
	double distance = l2_distance(result, q);
	double tempDistance;

	for (size_t i = 1; i < points->size(); ++i)
		if ((tempDistance = l2_distance(q, points->at(i))) < distance) {
			distance = tempDistance;
			result = points->at(i);
		}
	return result;
}

std::vector<MyPoint*>* linear_method_eps(std::vector<MyPoint*>* points, const MyPoint* q, double eps)
{
	std::vector<MyPoint*>* result = new std::vector<MyPoint*>();

	for (size_t i = 1; i < points->size(); ++i)
		if (l2_distance(q, points->at(i)) < eps)
			result->push_back(points->at(i));
	return result;
}