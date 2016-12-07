#include <iostream>
#include <algorithm>
#include <chrono>
#include "kdtree.cpp"


int main() {
	vector<vector<double>> all;
	vector<double> c;
	c.push_back(0); c.push_back(0);
	all.push_back(c);

	int N = 100000;

	kd_tree <double> tree;


	auto startA = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < N; i++) {
		c[0] = i; c[1] = i*2;
		tree.insert(c);
	}


	// kd_tree <double> tree(all);

	auto startB = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1000; i++) {
		c[0] = i; c[1] = i + i*2;
		auto res = tree.nearest_neighbor(c);
	}

	auto end = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> insert = startB - startA;
	std::chrono::duration<double> search = end - startB;
	// cout << insert.count() << endl;
	cout << search.count() << endl;
	// kd_tree <double> *tree = new kd_tree<double>(all);
	// tree.print();
	// cout << *res << endl;

	// tree->insert(c); // root

	// c[0] = 2; c[1] = 6; // left
	// tree->insert(c);

	// c[0] = 6; c[1] = 5; // right
	// tree->insert(c);

	// c[0] = 3; c[1] = 3; // left, left
	// tree->insert(c);

	// c[0] = 2; c[1] = 8; // left, right
	// tree->insert(c);

	// tree->print();

	// c[0] = 3; c[1] = 1;
	// kd_node<int> *res = nullptr;
	// res = tree->nearest_neighbor(c);
	// kd_node<int>* res = tree->nearest_neighbor(c);

	// for (int i = 0; i < res->values.size(); i++) {
	// 	cout << res->values[i] << " " << endl;
	// }

	// delete tree;

	return 0;

}

