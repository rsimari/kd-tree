#include <iostream>
#include <algorithm>
#include "kdtree.cpp"
// #include "kd_node_compare.cpp"


int main() {
	vector<vector<double>> all;
	vector<double> c;
	c.push_back(4); c.push_back(5);
	all.push_back(c);

	int N = 100;

	for (int i = 0; i < N; i++) {
		c[0] = i; c[0] = i*2;
		all.push_back(c);
	}
	// c[0] = 2; c[1] = 3;
	// all.push_back(c);

	// kd_tree <double> *tree = new kd_tree<double>(all);
	kd_tree <double> tree(all);
	c[0] = 3; c[1] = 6;
	auto res = tree.nearest_neighbor(c);
	cout << *res << endl;

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

