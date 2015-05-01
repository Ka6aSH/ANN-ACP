#include "va_file.h"


va_file::va_file(std::vector<MyPoint*>* points, std::string file_name, double eps):
points(points), file_name(file_name), eps(eps)
{
	if (points->size() == 0)
		return;
	this->d = points->at(0)->dimension;

	init_grid();
	get_bounds();
	std::ofstream file;
	file.open(file_name);
	write_points(&file);
	file.close();
}

void va_file::init_grid()
{
	grid = new double*[d];
}

void va_file::get_bounds()
{
	MyPoint* temp = points->at(0);
	double* lower_bound = new double[d];
	double* higher_bound = new double[d];
	// init start values
	for (int i = 0; i < d; ++ i)
	{
		higher_bound[i] = temp->vector[i];
		lower_bound[i] = temp->vector[i];
	}
	// go through
	for (int i = 1; i < points->size(); ++ i)
	{
		temp = points->at(i);
		for (int j = 0; j < d; ++ j)
		{
			if (temp->vector[j] > higher_bound[j])
				higher_bound[j] = temp->vector[j];
			if (temp->vector[j] < lower_bound[j])
				lower_bound[j] = temp->vector[j];
		}
	}
	// get bits
	int max_bit = 0;
	int max_count = 0;
	for (int i = 0; i < d; ++ i)
	{
		int count = (int)((higher_bound[i] - lower_bound[i]) / (2 * eps)) + 1;
		int bits = 0;
		if (count > max_count)
			max_count = count;
		while (count > 0)
		{
			count /= 10;
			bits ++;
		}
		if (bits > max_bit)
			max_bit = bits;
	}
	b = max_bit;
	size = max_count + 1;
	// set lower bound
	double shift = ((double)rand() / (RAND_MAX)) * eps;
	for (int i = 0; i < d; ++ i)
	{
		grid[i] = new double[size];
		grid[i][0] = lower_bound[i] - shift;
		for (int j = 1; j < size; ++j)
			grid[i][j] = grid[i][j - 1] + 2 * eps;
	}
	delete[] lower_bound;
	delete[] higher_bound;
}

void va_file::write_points(std::ofstream* file)
{
	MyPoint* temp;
	for (int l = 0; l < points->size(); ++l)
	{
		temp = points->at(l);
		*file << l << '\t';
		for (int k = 0; k < d; ++k)
		{
			int i = 0;
			int j = size - 1;
			while (j - i != 1)
			{
				if (temp->vector[k] < grid[k][j + i / 2 - j / 2])
					j = j + i / 2 - j / 2;
				else
					i = j + i / 2 - j / 2;
			}
			*file << format_block(i);
		}
		*file << '\n';
	}
}

MyPoint* va_file::ANN(MyPoint* q)
{
	std::stringstream code;

	for (int k = 0; k < d; ++k)
	{
		int i = 0;
		int j = size - 1;
		while (j - i != 1)
		{
			if (q->vector[k] < grid[k][j + i / 2 - j / 2])
				j = j + i / 2 - j / 2;
			else
				i = j + i / 2 - j / 2;
		}
		code << format_block(i);
	}
	std::ifstream file;
	file.open(file_name);
	const std::string tmp = code.str();
	const char* buf = tmp.c_str();
	std::string code_read;
	int index;
	MyPoint* res = nullptr;
	double dist = std::numeric_limits<double>().max();
	while (file >> index >> code_read)
	{
		if (!std::strcmp(buf, code_read.c_str()) &&
			(l2_distance(q, points->at(index))) < dist)
		{
			dist = l2_distance(q, points->at(index));
			res = points->at(index);
		}
	}
	return res;
}

std::vector<MyPoint*>* va_file::ENN(MyPoint* q)
{
	std::stringstream code;

	for (int k = 0; k < d; ++k)
	{
		int i = 0;
		int j = size - 1;
		while (j - i != 1)
		{
			if (q->vector[k] < grid[k][j + i / 2 - j / 2])
				j = j + i / 2 - j / 2;
			else
				i = j + i / 2 - j / 2;
		}
		code << format_block(i);
	}
	std::ifstream file;
	file.open(file_name);
	const std::string tmp = code.str();
	const char* buf = tmp.c_str();
	std::string code_read;
	int index;
	std::vector<MyPoint*>* result = new std::vector<MyPoint*>();
	while (file >> index >> code_read)
	{
		if (!std::strcmp(buf, code_read.c_str()) &&	(l2_distance(q, points->at(index))) < eps)
			result->push_back(points->at(index));
	}
	return result;
}

std::string va_file::format_block(int i)
{
	std::string res = std::to_string(i);
	if (res.length() < b)
	{
		return std::string(b - res.length(), '0') + res;
	}
	return res;
}

va_file::~va_file(void)
{
	for (int i = 0; i < d; ++i) 
	{
		delete[] grid[i];
	}
	delete[] grid;
}