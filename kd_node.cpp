#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class kd_node {
	friend ostream& operator<< (ostream& os, kd_node &k) {
		os << "(";
		for (int i = 0; i < k.values.size()-1; i++)
			os << k.values[i] << ", ";
		os << k.values[k.values.size()-1] << ")";
		return os;
	}
	public:
	kd_node() { left = nullptr; right = nullptr; }
	kd_node(vector<T> v) {
		left = nullptr;
		right = nullptr;
		values = v;
	}
	~kd_node() { delete left; delete right; }
	vector<T> values;
	kd_node<T> *left;
	kd_node<T> *right;
	int id;

	void print() {
		for (typename vector<T>::iterator it = values.begin(); it < values.end(); it++) cout << *it << " ";
		cout << endl;
	}

	bool less_than(kd_node* &a, int dimension) {
		return this->values[dimension] < a->values[dimension];
	}

};