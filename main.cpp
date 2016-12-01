#include <iostream>
#include "kdtree.cpp"

int main() {

	KDTREE *tree = new KDTREE();

	vector<int> values;
	values.push_back(1);
	values.push_back(2);
	tree->insert(values);

	vector<int> c;
	c.push_back(4);
	c.push_back(2);
	tree->insert(c);

	vector<int> d;
	d.push_back(8);
	d.push_back(5);
	tree->insert(d);


	vector<int> e;
	e.push_back(9);
	e.push_back(10);
	tree->insert(e);


	vector<int> f;
	f.push_back(9);
	f.push_back(2);
	tree->insert(f);


	vector<int> b;
	b.push_back(3);
	b.push_back(3);
	tree->insert(b);

	tree->print();

	cout << endl;

	vector<int> searchTerm = {1,1};
	vector<int> nearest = tree->nearest_neighbor(searchTerm);

	for (int i = 0; i < nearest.size(); i++) {
		cout << nearest[i] << " " << endl;
	}

	return 0;

}
