#include <iostream>
#include "kdtree.cpp"

int main() {

	kd_tree <int> *tree = new kd_tree<int>();

	vector<int> c;
	c.push_back(4); c.push_back(5);
	tree->insert(c); // root

	c[0] = 2; c[1] = 6; // left
	tree->insert(c);

	c[0] = 6; c[1] = 5; // right
	tree->insert(c);

	c[0] = 3; c[1] = 3; // left, left
	tree->insert(c);

	c[0] = 2; c[1] = 8; // left, right
	tree->insert(c);

	tree->print();

	c[0] = 3; c[1] = 1;
	kd_node<int> *res = nullptr;
	res = tree->nearest_neighbor(c);
	// kd_node<int>* res = tree->nearest_neighbor(c);

	for (int i = 0; i < res->values.size(); i++) {
		cout << res->values[i] << " " << endl;
	}

	delete tree;

	return 0;

}
