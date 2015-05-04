#include "BBF.h"
#include "va_file.h"
#include "LSH.h"
#include <random>
#include <time.h>
#include <iostream>
#include <numeric>
#include <chrono>
#include <iterator>
#include "IAlgorithm.h"

//std::vector<MyPoint*>* read_points(int d, std::string file_name);
//void to_string(MyPoint* p, std::ostream& sout);
//int output_points(std::vector<MyPoint*>* points);
//double* run_test(IAlgorithm*,
//	std::vector<MyPoint*>* queries,
//	std::vector<double>* counts);
//std::pair<double, std::vector<double>*> get_sample(std::vector<MyPoint*>* points,
//	std::vector<MyPoint*>* queries,
//	double eps);


//void main1() 
//{
//	int d = 8;
//	std::vector<MyPoint*>* points_list = read_points(d, "Uniform.Points.8.100000.data");
//
//	std::vector<double> coords;
//	double query[] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
//	coords.assign(query, query + 2);
//	MyPoint* q = new MyPoint(d, query);
//	MyPoint* res;
//	// Linear
//	std::cout << "Linear: " << std::endl;
//	res = linear_method(points_list, q);
//	std::cout << "\tPoint: ";
//	to_string(res, std::cout);
//	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
//	// BBF
//	std::cout << "BBF: " << std::endl;
//	BBF bbf(points_list, 0.5, l2_distance);
//	res = bbf.ANN(q);
//	std::cout << "\tPoint: ";
//	to_string(res, std::cout);
//	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
//	// VA-File
//	//std::cout << "VA-File: " << std::endl;
//	//va_file vaf(points_list, "smth", 0.5);
//	//res = vaf.ANN(q);
//	//std::cout << "\tPoint: ";
//	//to_string(res, std::cout);
//	//std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
//	// LSH
//	std::cout << "LSH: " << std::endl;
//	LSH lsh(points_list, 0.5);
//	res = lsh.ANN(q);
//	std::cout << "\tPoint: ";
//	to_string(res, std::cout);
//	std::cout << "\tDistance:" << l2_distance(res, q) << std::endl;
//	system("pause");
//}
//
//void mainENN()
//{
//	int d = 2;
//	double eps = 0.05;
//	std::vector<MyPoint*>* points_list = read_points(d, "Points2.1k.txt");
//	std::vector<MyPoint*>* temp;
//
//	//double query[] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
//	MyPoint* q = new MyPoint(d, new double[] { 0.5, 0.5});
//	// Linear
//	std::cout << "Linear: " << std::endl;
//	temp = linear_method_eps(points_list, q, eps);
//	output_points(temp);
//	temp->clear();
//	// BBF
//	std::cout << "BBF: " << std::endl;
//	BBF bbf(points_list, eps, l2_distance);
//	temp = bbf.ENN(q);
//	output_points(temp);
//	temp->clear();
//	// VA-File
//	std::cout << "VA-File: " << std::endl;
//	va_file vaf(points_list, "smth", eps);
//	temp = vaf.ENN(q);
//	output_points(temp);
//	temp->clear();
//	// LSH
//	std::cout << "LSH: " << std::endl;
//	LSH lsh(points_list, eps);
//	temp = lsh.ENN(q);
//	output_points(temp);
//	temp->clear();
//	system("pause");
//}

std::vector<MyPoint*>* read_points(int d, std::string file_name)
{
	std::ifstream file;
	std::vector<MyPoint*>* points = new std::vector<MyPoint*>();
	file.open(file_name);
	while (!file.eof())
	{
		double* vector = new double[d];
		for (int i = 0; i < d; ++i) {
		file >> vector[i];
		//vector[i] *= 100;
		}
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

int output_points(std::vector<MyPoint*>* points)
{
	std::cout << "\tPoints: ";
	for (auto point = points->begin(); point != points->end(); ++point)
		to_string(*point, std::cout);
	std::cout << "\tSize:" << points->size() << std::endl;
	return points->size();
}

double* run_test(IAlgorithm* nn_alg,
	std::vector<MyPoint*>* queries,
	std::vector<double>* distances,
	double(*distance_func)(const MyPoint*, const MyPoint*))
{
	clock_t start, finish;
	MyPoint* result;
	std::vector<MyPoint*>::iterator point;
	std::vector<double>::iterator distance;
	double mean_time = 0;
	double mean_distance = 0;
	int not_found = 0;
	int mean_exactly = 0;
	for (point = queries->begin(), distance = distances->begin();
		point != queries->end(); 
		++point, ++distance)
	{
		start = clock();
		result = nn_alg->ANN(*point);
		finish = clock();
		mean_time += ((double)(finish - start)) / CLOCKS_PER_SEC;
		if (result != nullptr)
		{
			if (std::abs(distance_func(*point, result) - *distance) < 0.0001)
				mean_exactly++;
			mean_distance += distance_func(*point, result) / *distance;
		}
		else
			not_found++;
	}
	mean_time /= queries->size();
	mean_distance /= (queries->size() - not_found);
	return new double[4]{
		mean_time, 
		mean_distance, 
		(double)mean_exactly / queries->size(), 
		(double)not_found / queries->size()};
}

std::pair<double, std::vector<double>*> get_sample(std::vector<MyPoint*>* points, 
	std::vector<MyPoint*>* queries, 
	double eps,
	double(*distance_func)(const MyPoint*, const MyPoint*))
{
	clock_t start, finish;
	MyPoint* result;
	std::vector<double>* counts = new std::vector<double>();
	double mean_time = 0;
	for (auto point = queries->begin(); point != queries->end();	++point)
	{
		start = clock();
		result = linear_method(points, *point, distance_func);
		finish = clock();
		mean_time += ((double)(finish - start)) / CLOCKS_PER_SEC;
		counts->push_back(distance_func(*point, result));
	}
	return std::pair<double, std::vector<double>*>(mean_time / queries->size(), counts);
}

void print_results(int d, int n, double linear_time, double* bbf, double* lsh, std::ofstream& output)
{
	char del = ',';
	output << d << del << n << del << linear_time;
	for (int i = 0; i < 4; ++i)
		output << del << bbf[i];
	for (int i = 0; i < 4; ++i)
		output << del << lsh[i];
	output << std::endl;
}

static bool deletePoints(MyPoint* point)
{
	delete point;
	return true;
}

void run_algs(int d, int n, char* distr, double(*distance_func)(const MyPoint*, const MyPoint*), std::ofstream& output)
{
	char buff[100];
	std::cout << "Dimension: " << d << std::endl;
	std::cout << "Count: " << n << std::endl;
	std::cout << "Reading..." << std::endl;
	sprintf_s(buff, "%sPoints.%d.%d.data", distr, d, n);
	std::vector<MyPoint*>* points_list = read_points(d, buff);
	sprintf_s(buff, "%sQueries.%d.%d.data", distr, d, 1000);
	std::vector<MyPoint*>* queries_list = read_points(d, buff);
	//std::ofstream file;
	//sprintf_s(buff, "%sResults.%d.%d.data", distr, d, n);
	//file.open(buff);
	std::pair<double, std::vector<double>*> linear_results;
	double* bbf_res, *lsh_res;
	/* Find sanity eps*/
	std::cout << "Finding eps..." << std::endl;
	double eps = 0;
	double distance;
	MyPoint* p;
	for (auto point = queries_list->begin(); point != queries_list->end(); ++point) {
		p = linear_method(points_list, *point, distance_func);
		if ((distance = distance_func(p, *point)) > eps)
			eps = distance;
	}
	eps *= 2;
	/* Initialize algorithms */
	std::cout << "Initializing BBF" << std::endl;
	BBF bbf(points_list, eps, distance_func);
	//std::cout << "Initializing VA-File" << std::endl;
	//va_file vaf(points_list, "smth", eps);
	std::cout << "Initializing LSH" << std::endl;
	LSH lsh(points_list, eps, distance_func);
	/* Run tests */
	std::cout << "Linear" << std::endl;
	linear_results = get_sample(points_list, queries_list, eps, distance_func);
	//std::cout << "\tMean Time:" << linear_results.first << std::endl;
	//file << d << ' ' << n << ' ' << linear_results.first << ' ';

	std::cout << "BBF" << std::endl;
	bbf_res = run_test(&bbf, queries_list, linear_results.second, distance_func);
	//std::cout << "\tMean Time: " << alg_result.first << std::endl;
	//std::cout << "\tMean Part: " << alg_result.second << std::endl;
	//file << alg_result.first << ' ' << alg_result.second << ' ';

	//std::cout << "VA-File:" << std::endl;
	//alg_result = run_test(&vaf, queries_list, linear_results.second);
	//std::cout << "\tMean Time: " << alg_result.first << std::endl;
	//std::cout << "\tMean Part: " << alg_result.second << std::endl;
	//file << alg_result.first << ' ' << alg_result.second << ' ';

	std::cout << "LSH" << std::endl;
	lsh_res = run_test(&lsh, queries_list, linear_results.second, distance_func);
	//std::cout << "\tMean Time: " << alg_result.first << std::endl;
	//std::cout << "\tMean Part: " << alg_result.second << std::endl;
	//file << alg_result.first << ' ' << alg_result.second << ' ';
	std::cout << "Output results" << std::endl;
	print_results(d, n, linear_results.first, bbf_res, lsh_res, output);
	std::cout << "Cleaning memory" << std::endl;
	delete linear_results.second;
	delete bbf_res;
	delete lsh_res;
	std::remove_if(points_list->begin(), points_list->end(), deletePoints);
	std::remove_if(queries_list->begin(), queries_list->end(), deletePoints);
	delete points_list;
	delete queries_list;
	std::cout << "Done!" << std::endl << std::endl;
	//file.close();
}

void main()
{
	//char* dist = "..\\UniformData\\Uniform.";
	//char* dist = "..\\NormalData\\Normal.";
	//char* dist = "..\\NormalReversedData\\NormalReversed.";
	char* dist = "..\\SphereData\\Sphere.";
	char buff[100];
	int n[] = { 1000, 5000, 10000, 50000, 100000 };
	sprintf_s(buff, "%sResults.data", dist);
	std::ofstream file;
	file.open(buff);
	int d_max = 64;
	int n_max = 5;
	for (int i = 2; i <= d_max; i <<= 1) {
		for (int j = 0; j < n_max; ++j)
			run_algs(i, n[j], dist, sphere_distance, file);
		file.flush();
	}
	file.close();
	//system("pause");
}