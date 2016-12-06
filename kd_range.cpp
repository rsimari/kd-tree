#include <iostream>
#include <vector>
using namespace std;
#include "kd_node.cpp"

template<typename T>
class kd_range {
	friend ostream& operator<<(ostream &os, kd_range &r) {
		os << "(";
		for (int i = 0; i < r.dimensions; i++) {
			os << r.lower[i] << "..." << r.upper[i] << ", ";
		}
		os << ")";
		return os;
	}

	public:
	vector<T> lower;
	vector<T> upper;

	kd_range() : dimensions(0) {}
	kd_range(vector<T> &l, vector<T> &u) {
		if (l.size() < u.size()) dimensions = l.size();
		else dimensions = u.size();

		lower = l;
		upper = u;

	}

	bool contains(kd_node<T> *&n) {
		return contains(n->values);
	}

	bool contains(vector<T> &n) {
		if (dimensions == 0) return false;

		for (int i = 0; i < dimensions; i++) {
			if (n[i] < lower[i] || n[i] > upper[i]) {
				return false;
			}
		}
		return true;
	}

	~kd_range() {};
	int dimension() const { return dimensions; }

	private:
	int dimensions;

};