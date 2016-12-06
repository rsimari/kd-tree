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
	vector<T> values;
	kd_node<T> *left;
	kd_node<T> *right;
	int id;

	void print() {
		for (typename vector<T>::iterator it = values.begin(); it < values.end(); it++) cout << *it << " ";
		cout << endl;
	}

	kd_node() { left = nullptr; right = nullptr; }
	~kd_node() { delete left; delete right; }
};