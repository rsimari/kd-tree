#include <iostream>
#include "kdtree.cpp"

int main() {
	KDTREE *tree = new KDTREE;
	vector<int> values;
	values.push_back(1);
	values.push_back(2);
	tree->insert(values);
	vector<int> b;
	b.push_back(3);
	b.push_back(3);
	tree->insert(b);
	tree->print();
	return 0;
}

