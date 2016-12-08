#include <iostream>
#include <algorithm>
#include <chrono>
#include "../kdtree.cpp"


int main() {
	vector<vector<double>> all;
	vector<double> c;
	c.push_back(0); c.push_back(0);
	all.push_back(c);

	int N = 1000;

	kd_tree <double> tree;


	auto startA = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < N; i++) {
		c[0] = i; c[1] = i*2;
		tree.insert(c);
	}

	auto startB = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1000; i++) {
		c[0] = i; c[1] = i + i*2;
		auto res = tree.nearest_neighbor(c);
	}

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> search = end - startB;
	cout << search.count() << endl;

	return 0;

}

