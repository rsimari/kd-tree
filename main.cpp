#include <iostream>
#include <algorithm>
#include "kdtree.cpp"
// #include "kd_node_compare.cpp"

// void balance(vector<kd_node<double>*>&);

int main() {
	vector<vector<double>> all;
	vector<double> c;
	c.push_back(4); c.push_back(5);
	all.push_back(c);

	// kd_tree <double> *tree = new kd_tree<double>(all);
	kd_tree <double> tree(all);

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

// void balance(vector<vector<double>> &nodes, int depth = 0) {
// 	int size = nodes[0].values.size();
// 	if (size < 1) return;
// 	int dimension = depth % size;

// 	sort(nodes.begin(), nodes.end(), kd_node_compare(dimension));

// 	int median_index = size / 2;



// 	return;
// }

