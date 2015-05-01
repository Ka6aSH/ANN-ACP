#include "MyPoint.h"
#include <iostream>
#include <fstream>
#include "Functions.h"

#pragma once
class va_file
{
public:
	va_file(std::vector<MyPoint*>* points, std::string file_name, double eps);
	MyPoint* ANN(MyPoint* q);
	std::vector<MyPoint*>* ENN(MyPoint* q);
	~va_file(void);

private:
	int b;
	double eps;
	double** grid;
	int d;
	int size;
	std::vector<MyPoint*>* points;
	std::string file_name;

	void init_grid();
	void get_bounds();
	void write_points(std::ofstream* file);
	std::string format_block(int i);
};

