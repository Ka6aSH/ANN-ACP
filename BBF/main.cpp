#include "BBF.h"
#include "va_file.h"
#include <random>
#include <time.h>
#include <iostream>
#include <numeric>

void main() 
{
	//double points[20][2] =
	//{	{ -2 , 9 },
	//	{ -3 , -6 },
	//	{ -2 , 4 },
	//	{ -9 , 10 },
	//	{ -1 , 0 },
	//	{ 5 , -6 },
	//	{ 7 , -9 },
	//	{ -9 , 9 },
	//	{ 5 , -3 },
	//	{ 4 , 2 },
	//	{ 7 , 9 },
	//	{ -2 , 3 },
	//	{ -2 , 7 },
	//	{ -8 , -10 },
	//	{ 5 , -2 },
	//	{ 1 , 3 },
	//	{ 10 , -6 },
	//	{ -9 , -5 },
	//	{ 2 , 6 },
	//	{ -7 , 9 }};
	double points[100][2] = {
		{ 9, -6 },
		{ 1, 9 },
		{ -7, -1 },
		{ -9, -7 },
		{ -4, 6 },
		{ 8, -6 },
		{ -9, 9 },
		{ -2, 8 },
		{ -3, 9 },
		{ 1, -8 },
		{ -1, 7 },
		{ -2, -7 },
		{ 10, -9 },
		{ -1, -6 },
		{ 5, 2 },
		{ 7, 3 },
		{ 4, -6 },
		{ 1, -2 },
		{ 6, 4 },
		{ -10, 6 },
		{ 8, -4 },
		{ -8, -8 },
		{ 6, -6 },
		{ 8, -6 },
		{ 9, 2 },
		{ 8, 9 },
		{ -8, 9 },
		{ -10, 9 },
		{ -9, -6 },
		{ -3, -10 },
		{ -1, 5 },
		{ -6, 6 },
		{ -10, 1 },
		{ -5, -5 },
		{ 6, 6 },
		{ 9, 8 },
		{ 8, -7 },
		{ 3, 2 },
		{ -2, -6 },
		{ 7, -8 },
		{ -10, 6 },
		{ 3, 10 },
		{ 3, -10 },
		{ -4, -5 },
		{ 3, -7 },
		{ 1, 5 },
		{ -7, 4 },
		{ -8, 2 },
		{ 7, -4 },
		{ 8, -1 },
		{ -4, -4 },
		{ -7, -1 },
		{ -3, -3 },
		{ -8, 7 },
		{ -3, 10 },
		{ 0, 10 },
		{ 7, 4 },
		{ 2, -5 },
		{ 7, 0 },
		{ 1, -9 },
		{ -2, 8 },
		{ 6, -1 },
		{ -8, 5 },
		{ 8, 2 },
		{ 9, -6 },
		{ 3, 1 },
		{ 10, 8 },
		{ 2, -2 },
		{ 6, -7 },
		{ 0, -8 },
		{ 4, -2 },
		{ -1, -9 },
		{ -9, 9 },
		{ 8, 9 },
		{ 2, 9 },
		{ 7, -7 },
		{ -9, 1 },
		{ 10, 10 },
		{ -5, -2 },
		{ 6, -6 },
		{ 1, 10 },
		{ 4, 6 },
		{ -10, 7 },
		{ 1, -6 },
		{ 4, 5 },
		{ 2, 0 },
		{ 5, -2 },
		{ -8, -7 },
		{ 9, -6 },
		{ 2, 10 },
		{ 9, -5 },
		{ -3, -6 },
		{ 6, 1 },
		{ -1, 5 },
		{ 0, 4 },
		{ 8, 1 },
		{ -5, -3 },
		{ -9, -2 },
		{ -7, -8 },
		{ -8, -7 },
	};
	//double points[10][2] = {
	//	{6.29447, -7.29046},
	//	{8.11584, 6.70017},
	//	{-7.46026, 9.37736},
	//	{8.26752, -5.57932},
	//	{2.64718, -3.83666},
	//	{-8.04919, 0.944412},
	//	{-4.43004, -6.23236},
	//	{0.93763, 9.85763},
	//	{9.15014, 9.92923},
	//	{9.29777, 9.3539}
	//};
	int d = 2;
	std::vector<MyPoint*> points_list;
	std::vector<double> coords;
	MyPoint* p;
	for (int i = 0; i < 100; ++i) {
		coords.assign(points[i], points[i] + 2);
		p = new MyPoint(d, points[i]);
		points_list.push_back(p);
	}
	//double query[] = {-4.46154,	7.44858};
	double query[] = { 0, 0};
	coords.assign(query, query + 2);
	p = new MyPoint(d, query);
	//BBF bbf(&points_list);
	//bbf.ANN(p);
	va_file vaf(&points_list, "smth");
	vaf.ANN(p);
}

MyPoint* linear_method(std::vector<MyPoint*>* points, const MyPoint* q)
{
	MyPoint* result = points->at(0);
    double distance = l2_distance(result, q);
    double tempDistance;

	for(int i = 1; i < points->size(); ++ i)
	{
		tempDistance = l2_distance(q, points->at(i));
        if (tempDistance < distance) {
            distance = tempDistance;
            result = points->at(i);
        }
	}
	return result;
}


void run_test_1()
{
	//system("pause");
	int D = 8;
	int N = 1000000;
	int N_EXPR = 100;
	std::vector<double> linear_r;
	std::vector<double> bbf_r;
	double* coords;
	std::vector<MyPoint*> points;
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(-10.0,10.0);
	std::cout << "Generating of Data is started\n";
	for (int i = 0; i < N; ++i)
	{
		coords = new double[D];
		for (int j = 0; j < D; ++j)
			coords[j] = distribution(generator);
		points.push_back(new MyPoint(D, coords));
	}
	std::cout << "Data was generated\n";
	std::cout << "Init BBF\n";
	BBF bbf(&points);
	clock_t t1, t2;
	MyPoint* res;
	MyPoint* res2;
	MyPoint* q;
	coords = new double[D];
	for (int i = 0; i < N_EXPR; ++i) {
		for (int j = 0; j < D; ++j)
			coords[j] = distribution(generator);
		q = new MyPoint(D, coords);
		t1 = clock();
		res = linear_method(&points, q);
		t2 = clock();
		linear_r.push_back(((double)(t2 - t1))/ CLOCKS_PER_SEC);
		
		t1 = clock();
		res2 = bbf.ANN(q);
		t2 = clock();
		bbf_r.push_back(((double)(t2 - t1))/ CLOCKS_PER_SEC);

		if (std::abs(l2_distance(q, res) - l2_distance(q, res2)) > 0.00001) {
			std::cout << "Query point: ";
			//for (auto k = coords.begin(); k != coords.end(); ++k)
			//	std::cout << *k << "\t";
			//std::cout << "\n";
			//for (auto l = points.begin(); l != points.end(); ++l)
			//{
			//	for (auto k = l->vector.begin(); k != l->vector.end(); ++k)
			//		std::cout << *k << "\t";
			//	std::cout << "\n";
			//}
			std::cout << "q_linear: " << l2_distance(q, res) << "\n";
			std::cout << "q_bbf: " << l2_distance(q, res2) << "\n";
			std::cout << "FAIL\n";
			bbf.ANN(q);
			delete q;
			break;
		} else {
			std::cout << "OK\n";
		}
		delete q;
	}
	double sum = std::accumulate(linear_r.begin(), linear_r.end(), 0.0);
	double mean = sum /linear_r.size();
	std::cout << "Linear: " << mean;
	sum = std::accumulate(bbf_r.begin(), bbf_r.end(), 0.0);
	mean = sum /bbf_r.size();
	std::cout << "\nBBF: " << mean;
//	system("pause");
}

void main1()
{
	run_test_1();
}