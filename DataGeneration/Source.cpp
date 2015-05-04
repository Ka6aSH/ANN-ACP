#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <math.h>

void generate_uniform_point(int d, int n, bool query = false)
{
	std::ofstream file;
	unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	char buff[100];
	if (!query) 
		sprintf_s(buff, "..\\UniformData\\Uniform.Points.%d.%d.data", d, n);
	else
		sprintf_s(buff, "..\\UniformData\\Uniform.Queries.%d.%d.data", d, n);
	file.open(buff);
	for (int j = 0; j < d; ++j)
		file << ' ' << distribution(generator);
	for (int i = 1; i < n; ++i)
	{
		file << std::endl;
		for (int j = 0; j < d; ++j)
			file << ' ' << distribution(generator);
	}
	file.close();
}

void generate_normal_point(int d, int n, bool query = false)
{
	std::ofstream file;
	unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::normal_distribution<double> distribution(0.5, 1.0 / 6);
	char buff[100];
	if (!query)
		sprintf_s(buff, "..\\NormalData\\Normal.Points.%d.%d.data", d, n);
	else
		sprintf_s(buff, "..\\NormalData\\Normal.Queries.%d.%d.data", d, n);
	file.open(buff);
	double rnd_numb;
	for (int j = 0; j < d; ++j)
	{
		rnd_numb = distribution(generator);
		rnd_numb = rnd_numb > 1 ? 1 : rnd_numb;
		rnd_numb = rnd_numb < 0 ? 0 : rnd_numb;
		file << ' ' << rnd_numb;
	}

	for (int i = 1; i < n; ++i)
	{
		file << std::endl;
		for (int j = 0; j < d; ++j)
		{
			rnd_numb = distribution(generator);
			rnd_numb = rnd_numb > 1 ? 1 : rnd_numb;
			rnd_numb = rnd_numb < 0 ? 0 : rnd_numb;
			file << ' ' << rnd_numb;
		}
	}
	file.close();
}

void generate_normal_reversed_point(int d, int n, bool query = false)
{
	std::ofstream file;
	unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::normal_distribution<double> distribution(0.5, 1.0 / 6);
	char buff[100];
	if (!query)
		sprintf_s(buff, "..\\NormalReversedData\\NormalReversed.Points.%d.%d.data", d, n);
	else
		sprintf_s(buff, "..\\NormalReversedData\\NormalReversed.Queries.%d.%d.data", d, n);
	file.open(buff);
	double rnd_numb;
	for (int j = 0; j < d; ++j)
	{
		rnd_numb = distribution(generator);
		rnd_numb = rnd_numb > 1 ? 1 : rnd_numb;
		rnd_numb = rnd_numb < 0 ? 0 : rnd_numb;
		rnd_numb = rnd_numb > 0.5 ? 1.5 - rnd_numb : 0.5 - rnd_numb;
		file << ' ' << rnd_numb;
	}

	for (int i = 1; i < n; ++i)
	{
		file << std::endl;
		for (int j = 0; j < d; ++j)
		{
			rnd_numb = distribution(generator);
			rnd_numb = rnd_numb > 1 ? 1 : rnd_numb;
			rnd_numb = rnd_numb < 0 ? 0 : rnd_numb;
			rnd_numb = rnd_numb > 0.5 ? 1.5 - rnd_numb : 0.5 - rnd_numb;
			file << ' ' << rnd_numb;
		}
	}
	file.close();
}

void generate_sphere_point(int d, int n, bool query = false)
{
	std::ofstream file;
	unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	char buff[100];
	if (!query)
		sprintf_s(buff, "..\\SphereData\\Sphere.Points.%d.%d.data", d, n);
	else
		sprintf_s(buff, "..\\SphereData\\Sphere.Queries.%d.%d.data", d, n);
	file.open(buff);
	double coord;
	for (int i = 0; i < n; ++i) {
		file << std::endl;
		double* alphas = new double[d - 1];
		double* sin_alphas = new double[d - 1];
		for (int j = 0; j < d - 1; j++)
		{
			alphas[j] = 2 * M_PI * distribution(generator);
			sin_alphas[j] = std::sin(alphas[j]);
		}
		coord = 1;
		for (int j = 0; j < d - 1; j++)
			coord *= sin_alphas[j];
		file << coord;
		for (int j = 1; j < d; j++)
		{
			coord = std::cos(alphas[j - 1]);
			for (int k = j; k < d - 1; k++)
				coord *= sin_alphas[k];
			file << ' ' << coord;
		}
		delete alphas;
		delete sin_alphas;
	}
	file.close();
}

void main()
{
	int n[] = { 1000, 5000, 10000, 50000, 100000 };
	for (int i = 2; i <= 64; i <<= 1)
	{
		for (int j = 0; j < 5; ++j)
			generate_sphere_point(i, n[j]);
		generate_sphere_point(i, n[0], true);
	}
}