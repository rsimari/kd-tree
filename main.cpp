#include <iostream>
#include "kdtree.cpp"

int main() {

	kd_tree *tree = new kd_tree();

	// vector<int> values;
	// values.push_back(1);
	// values.push_back(2);
	// tree->insert(values);

	// vector<int> c;
	// c.push_back(4);
	// c.push_back(2);
	// tree->insert(c);

	// vector<int> d;
	// d.push_back(8);
	// d.push_back(5);
	// tree->insert(d);


	// vector<int> e;
	// e.push_back(9);
	// e.push_back(10);
	// tree->insert(e);


	// vector<int> f;
	// f.push_back(9);
	// f.push_back(2);
	// tree->insert(f);


	// vector<int> b;
	// b.push_back(3);
	// b.push_back(3);
	// tree->insert(b);

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

	c[0] = 3; c[1] = 1; 
	vector<int> d = tree->nearest_neighbor(c);

	tree->print();

	cout << endl;

	// vector<int> searchTerm = {1,1};
	// vector<int> nearest = tree->nearest_neighbor(searchTerm);

	for (int i = 0; i < d.size(); i++) {
		cout << d[i] << " " << endl;
	}

	return 0;

}
