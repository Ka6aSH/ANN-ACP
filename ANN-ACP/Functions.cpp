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
	double res = p1->dot(p2);
	res = res < -1 ? -0.99999 : res;
	res = res > 1 ? 0.99999 : res;
	return std::acos(res);
}

MyPoint* linear_method(std::vector<MyPoint*>* points, const MyPoint* q, double(*distance_func)(const MyPoint*, const MyPoint*))
{
	MyPoint* result = points->at(0);
	double distance = distance_func(result, q);
	double tempDistance;

	for (size_t i = 1; i < points->size(); ++i)
		if ((tempDistance = distance_func(q, points->at(i))) < distance) {
			distance = tempDistance;
			result = points->at(i);
		}
	return result;
}

//std::vector<MyPoint*>* linear_method_eps(std::vector<MyPoint*>* points, const MyPoint* q, double eps)
//{
//	std::vector<MyPoint*>* result = new std::vector<MyPoint*>();
//
//	for (size_t i = 1; i < points->size(); ++i)
//		if (l2_distance(q, points->at(i)) < eps)
//			result->push_back(points->at(i));
//	return result;
//}