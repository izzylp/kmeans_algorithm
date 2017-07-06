/* Compile and run: g++ -std=c++11 -W -Wall -o kmeans kmeans.cpp && ./kmeans
 */

#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/tokenizer.hpp>

#include "kmeans.hpp"

/* For testing purposes */
std::vector<kmeans_point> generate_points(size_t n_dimensions_, size_t n_points_, size_t min_, size_t max_)
{
	std::vector<kmeans_point> p_ret;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min_, max_);

	for (size_t i = 0; i < n_points_; ++i) {
		kmeans_point p(n_dimensions_);
		for (size_t j = 0; j < n_dimensions_; ++j) {
			p.push_back(dis(gen));

		}
		p_ret.push_back(p);
	}

	return p_ret;
}

void print(std::vector<kmeans_point> v)
{
	for (const kmeans_point& item : v) {
		std::cout << item.to_string() << std::endl;
	}
}

std::vector<kmeans_point> read_file(const std::string& filename_, const std::vector<size_t>& labels_)
{
	std::vector<kmeans_point> ret;
	std::ifstream file(filename_);
	std::string line;
	bool first_line = true;

	while (std::getline(file, line)) {
		if (first_line) {
			first_line = false;
			continue;
		}

		std::stringstream linestream(line);
		std::string data;

		std::getline(linestream, data, '\0');

		boost::char_separator<char> sep(";");
		boost::tokenizer<boost::char_separator<char>> tokens(data, sep);
		size_t count = 0;
		kmeans_point point;
		for (const auto& t : tokens) {
			if (std::find(labels_.begin(), labels_.end(), count) != labels_.end()) {
				point.push_back_label(t);
			} else {
				point.push_back(std::stod(t));
			}
			++count;
		}
		ret.push_back(point);
	}

	return ret;
}

int main()
{
	/* Teste com pontos aleatórios */
	/*{
		size_t k = 2;
		size_t n_dimensions = 4;
		size_t n_points = 10;
		size_t min = 1;
		size_t max = 10;

		std::vector<kmeans_point> points = generate_points(n_dimensions, n_points, min, max);
		std::vector<kmeans_point> centroids = kmeans_solve(k, points);
		std::sort(points.begin(), points.end());

		std::cout << "CENTROIDS: \n";
		print(centroids);
		std::cout << "\n\n";
		std::cout << "POINTS: \n";
		print(points);
		std::cout << "\n\n";
	}*/
	/* Iris dataset */
	{
		size_t k = 3;
		std::vector<size_t> labels({4});
		std::string filename = "test/iris.csv";

		std::vector<kmeans_point> points = read_file(filename, labels);
		std::vector<kmeans_point> centroids = kmeans_solve(k, points);
		std::sort(points.begin(), points.end());

		std::cout << "IRIS DATASET: \n";
		std::cout << "CENTROIDS: \n";
		print(centroids);
		std::cout << "\n\n";
		std::cout << "POINTS: \n";
		print(points);
		std::cout << "\n\n";
	}
	/* Sao Paulo dataset */
	{
		size_t k = 15;
		std::vector<size_t> labels({0, 3});
		std::string filename = "test/sao_paulo.csv";

		std::vector<kmeans_point> points = read_file(filename, labels);
		std::vector<kmeans_point> centroids = kmeans_solve(k, points);
		std::sort(points.begin(), points.end());

		std::cout << "SAO PAULO DATASET: \n";
		std::cout << "CENTROIDS: \n";
		print(centroids);
		std::cout << "\n\n";
		std::cout << "POINTS: \n";
		print(points);
		std::cout << "\n\n";
	}
	/* Test dataset */
	/*{
		size_t k = 2;
		std::vector<size_t> labels;
		std::string filename = "test_";

		std::vector<kmeans_point> points = read_file(filename, labels);
		std::vector<kmeans_point> centroids = kmeans_solve(k, points);
		std::sort(points.begin(), points.end());

		std::cout << "TEST DATASET: \n";
		std::cout << "CENTROIDS: \n";
		print(centroids);
		std::cout << "\n\n";
		std::cout << "POINTS: \n";
		print(points);
		std::cout << "\n\n";
	}*/

	return 0;
}
