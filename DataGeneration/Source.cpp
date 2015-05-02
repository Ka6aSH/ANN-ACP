#include <string>
#include <fstream>
#include <random>
#include <chrono>

void generate_uniform_point(int d, int n, bool query = false)
{
	std::ofstream file;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	char buff[100];
	if (!query) 
		sprintf_s(buff, "Uniform.Points.%d.%d.data", d, n);
	else
		sprintf_s(buff, "Uniform.Queries.%d.%d.data", d, n);
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

void main()
{
	int query_size = 1000;
	for (int i = 2; i <= 64; i <<= 1)
	{
		for (int j = 1000; j <= 1000000; j *= 10)
			generate_uniform_point(i, j);
		generate_uniform_point(i, query_size, true);
	}
}