#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

class kd_node {
	// orientation?
	public:
	vector<int> values;
	kd_node* left;
	kd_node* right;
	void print() {
		for (vector<int>::iterator it = values.begin(); it < values.end(); it++) cout << *it << " ";
		cout << endl;
	}
	kd_node() { left = nullptr; right = nullptr; }
	~kd_node() { delete left; delete right; }
};

class KDTREE {
public:
	KDTREE() : dimensions(2) { root = nullptr; }
	KDTREE(int d) : dimensions(d) { root = nullptr; }
	~KDTREE() { delete root; }
	void insert(vector<int> &new_values) {
		// TODO: check size of vector here? must be equal to dimensions
		if (root == nullptr) {
			kd_node* new_node = new kd_node;
			new_node->values = new_values;
			root = new_node;
		} else insert_r(root, new_values, 0);
	}
	vector<int> nearest_neighbor(vector<int> &n) {
		int orientation = 0;
		int max = INT_MAX;
		nearest_neighbor_r(root, n, orientation, max, nearest);
		return nearest->values;
	}

	void print() { print_r(root); }

private:
	kd_node* root;
	int dimensions;
	void insert_r(kd_node* root, vector<int> &new_values, int orientation) {
		if (root == nullptr) return;
		orientation %= dimensions;
		// normal bst insertion except we look at a specific element of the values vector
		if (new_values[orientation] < root->values[orientation])
			if (root->left == nullptr) {
				kd_node* new_node = new kd_node;
				root->left = new_node;
				new_node->values = new_values;
				return;
			} else insert_r(root->left, new_values, orientation + 1);
		else if (new_values[orientation] >= root->values[orientation])
			if (root->right == nullptr) {
				kd_node* new_node = new kd_node;
				root->right = new_node;
				new_node->values = new_values;
				return;
			} else insert_r(root->right, new_values, orientation + 1);
		return;
	}

	void print_r(kd_node* root) {
		// print value in tree using in_order traversal
		if (root == nullptr) return;
		print_r(root->left);
		int size = root->values.size();
		cout << "(";
		for (int i = 0; i < size - 1; i++)
			cout << root->values[i] << ", ";
		cout << root->values[size - 1] << ")" << endl;
		print_r(root->right);
	}

	void nearest_neighbor_r(kd_node* &root, vector<int> &n, int orientation, int &min_dist, kd_node* &near) {

		root->print();
		if (root->left == nullptr && root->right == nullptr) {
			int d = dist(root->values, n);
			min_dist = d;

			near = root;
			return;
		}

		orientation %= dimensions;

		bool wentRight = false;
		if (root->left != nullptr && n[orientation] < root->values[orientation])
			nearest_neighbor_r(root->left, n, orientation + 1, min_dist, near);
		else {
			nearest_neighbor_r(root->right, n, orientation + 1, min_dist, near);
			wentRight = true;
		}

		int d = dist(root->values, n);
		if (d < min_dist) {
			min_dist = d;
			near = root;
		}

		//compare orientation value vs nearest distance
		int thisDim = root->values[orientation];
		int nDim = n[orientation];
		int sum = pow((thisDim - nDim), 2);
		if (sum < min_dist) {
			//recurse in other subtree.
			if (wentRight && root->left != nullptr) {
				nearest_neighbor_r(root->left, n, orientation + 1, min_dist, near);
			}
			else if (!wentRight && root->right != nullptr) {
				nearest_neighbor_r(root->right, n, orientation + 1, min_dist, near);
			}
		}
	}

	int dist(vector<int> &a, vector<int> &b) {

		//validate sizes
		int sizeA = a.size();
		int sizeB = b.size();
		if (sizeA != sizeB) return -1;

		int sum = 0;
		for (int i = 0; i < sizeA; i++)
			sum += pow((a[i] - b[i]), 2);
		// squared sum prevents us from computing sqrt alot
		return sum;
	}
};
