#include <iostream>
#include <algorithm>
#include <chrono>
#include "kdtree.cpp"


int main() {
	vector<vector<int>> all;
	vector<int> c;
	c.push_back(0); c.push_back(0);
	all.push_back(c);

	int N = 1000;

	kd_tree <int> tree;

	for (int i = 1; i < N; i++) {
		c[0] = i; c[1] = i*2;
		tree.insert(c);
	}

	cout << "Tree: " << endl;
	tree.print();
	cout << endl; 

	auto res = tree.nearest_neighbor(c);
	cout << "Nearest Neighbor: " << *res << endl;

	cout << endl << "Range Search: "<<endl;

	vector<int> lowerBounds;
	lowerBounds.push_back(4);
	lowerBounds.push_back(10);

	vector<int> higherBounds;
	higherBounds.push_back(100);
	higherBounds.push_back(84);

	kd_range <int> r(lowerBounds, higherBounds);
	vector<kd_node<int>*> rangeRes = tree.range_search(r);

	for (int i = 0; i < rangeRes.size(); i++) {
		cout << (*rangeRes[i]) << endl;
	}

	return 0;
}
