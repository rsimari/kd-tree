#include <iostream>
#include "kdtree.cpp"

int main() {

	kd_tree *tree = new kd_tree();

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
	vector<int> d = tree->nearest_neighbor(c);

	for (int i = 0; i < d.size(); i++) {
		cout << d[i] << " " << endl;
	}

	return 0;

}
