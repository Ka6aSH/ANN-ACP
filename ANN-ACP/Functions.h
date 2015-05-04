#include "MyPoint.h"
#include <sstream>

double l2_distance(const MyPoint* p1, const MyPoint* p2);

double sphere_distance(const MyPoint* p1, const MyPoint* p2);

MyPoint* linear_method(std::vector<MyPoint*>* points, const MyPoint* q, double(*distance_func)(const MyPoint*, const MyPoint*));

std::vector<MyPoint*>* linear_method_eps(std::vector<MyPoint*>* points, const MyPoint* q, double eps);

