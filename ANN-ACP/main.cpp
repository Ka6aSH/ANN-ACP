#include "BBF.h"
#include "va_file.h"
#include "LSH.h"
#include <random>
#include <time.h>
#include <iostream>
#include <numeric>

std::vector<MyPoint*>* read_points(int d, std::string file_name);
void to_string(MyPoint* p, std::ostream& sout);
MyPoint* linear_method(std::vector<MyPoint*>* points, const MyPoint* q);
std::vector<MyPoint*>* linear_method_eps(std::vector<MyPoint*>* points, const MyPoint* q, double eps);

void main() 
{
	int d = 4;
	std::vector<MyPoint*>* points_list = read_points(d, "Points8.1k.txt");

	std::vector<double> coords;
	double query[] = { 0.5, 0.5, 0.5, 0.5};
	coords.assign(query, query + 2);
	MyPoint* q = new MyPoint(d, query);
	MyPoint* res;
	// Linear
	std::cout << "Linear: " << std::endl;
	res = linear_method(points_list, q);
	std::cout << "\tPoint: ";
	to_string(res, std::cout);
	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
	// BBF
	std::cout << "BBF: " << std::endl;
	BBF bbf(points_list);
	res = bbf.ANN(q);
	std::cout << "\tPoint: ";
	to_string(res, std::cout);
	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
	// VA-File
	std::cout << "VA-File: " << std::endl;
	va_file vaf(points_list, "smth", 0.15);
	res = vaf.ANN(q);
	std::cout << "\tPoint: ";
	to_string(res, std::cout);
	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
	// LSH
	std::cout << "LSH: " << std::endl;
	LSH lsh(points_list, 0.15);
	res = lsh.ANN(q);
	std::cout << "\tPoint: ";
	to_string(res, std::cout);
	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
}

MyPoint* linear_method(std::vector<MyPoint*>* points, const MyPoint* q)
{
	MyPoint* result = points->at(0);
    double distance = l2_distance(result, q);
    double tempDistance;

	for(int i = 1; i < points->size(); ++ i)
		if ((tempDistance = l2_distance(q, points->at(i))) < distance) {
            distance = tempDistance;
            result = points->at(i);
        }
	return result;
}

std::vector<MyPoint*>* linear_method_eps(std::vector<MyPoint*>* points, const MyPoint* q, double eps)
{
	std::vector<MyPoint*>* result = new std::vector<MyPoint*>();

	for (int i = 1; i < points->size(); ++i)
		if (l2_distance(q, points->at(i)) < eps)
			result->push_back(points->at(i));
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

std::vector<MyPoint*>* read_points(int d, std::string file_name)
{
	std::ifstream file;
	std::vector<MyPoint*>* points = new std::vector<MyPoint*>();
	file.open(file_name);
	while (!file.eof()) 
	{
		double* vector = new double[d];
		for (int i = 0; i < d; ++i)
			file >> vector[i];
		points->push_back(new MyPoint(d, vector));
	}
	file.close();
	return points;
}

void to_string(MyPoint* p, std::ostream& sout)
{
	for (int i = 0; i < p->dimension; ++i)
		sout << p->vector[i];
	sout << std::endl;
}