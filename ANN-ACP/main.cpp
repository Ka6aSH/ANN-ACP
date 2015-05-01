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

void mainANN() 
{
	int d = 8;
	std::vector<MyPoint*>* points_list = read_points(d, "Points8.1k.txt");

	std::vector<double> coords;
	double query[] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
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
	BBF bbf(points_list, 0.5);
	res = bbf.ANN(q);
	std::cout << "\tPoint: ";
	to_string(res, std::cout);
	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
	// VA-File
	std::cout << "VA-File: " << std::endl;
	va_file vaf(points_list, "smth", 0.5);
	res = vaf.ANN(q);
	std::cout << "\tPoint: ";
	to_string(res, std::cout);
	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
	// LSH
	std::cout << "LSH: " << std::endl;
	LSH lsh(points_list, 0.5);
	res = lsh.ANN(q);
	std::cout << "\tPoint: ";
	to_string(res, std::cout);
	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
	system("pause");
}

void main()
{
	int d = 2;
	double eps = 0.05;
	std::vector<MyPoint*>* points_list = read_points(d, "Points2.1k.txt");
	std::vector<MyPoint*>* temp;
	double count;

	//double query[] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
	MyPoint* q = new MyPoint(d, new double[] { 0.5, 0.5});
	// Linear
	std::cout << "Linear: " << std::endl;
	temp = linear_method_eps(points_list, q, eps);
	std::cout << "\tPoints: ";
	for (auto point = temp->begin(); point != temp->end(); ++point)
		to_string(*point, std::cout);
	std::cout << "\tSize:" << temp->size() << std::endl;
	count = temp->size();
	temp->clear();
	// BBF
	std::cout << "BBF: " << std::endl;
	BBF bbf(points_list, eps);
	temp = bbf.ENN(q);
	std::cout << "\tPoint: ";
	for (auto point = temp->begin(); point != temp->end(); ++point)
		to_string(*point, std::cout);
	std::cout << "\tSize:" << temp->size() << std::endl;
	temp->clear();
	// VA-File
	std::cout << "VA-File: " << std::endl;
	va_file vaf(points_list, "smth", eps);
	temp = vaf.ENN(q);
	std::cout << "\tPoint: ";
	for (auto point = temp->begin(); point != temp->end(); ++point)
		to_string(*point, std::cout);
	std::cout << "\tSize:" << temp->size() << std::endl;
	temp->clear();
	// LSH
	std::cout << "LSH: " << std::endl;
	LSH lsh(points_list, eps);
	temp = lsh.ENN(q);
	std::cout << "\tPoints: ";
	for (auto point = temp->begin(); point != temp->end(); ++point)
		to_string(*point, std::cout);
	std::cout << "\tSize:" << temp->size() << std::endl;
	temp->clear();
	system("pause");
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
		sout << p->vector[i] << ' ';
	sout << std::endl;
}