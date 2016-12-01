#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

struct kd_node {
	// orientation?
	vector<int> values;
	kd_node* left;
	kd_node* right;
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
		kd_node* nearest = nearest_neighbor_r(root, n, 0, numeric_limits<double>::max(), nullptr);
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
		if (new_values[orientation] >= root->values[orientation]) 
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
	kd_node* nearest_neighbor_r(kd_node* root, vector<int> &n, int orientation, double min_dist, kd_node* near) {
		if (root->left == nullptr && root->right == nullptr) return root;
		orientation %= dimensions;
		kd_node* temp;
		// moves down the tree based on n[orientation] value until it finds a leaf node
		if (root->left != nullptr && n[orientation] < root->values[orientation]) 
			temp = nearest_neighbor_r(root->left, n, orientation + 1, min_dist, near);
		else if (root->right != nullptr && n[orientation] >= root->values[orientation])
			temp = nearest_neighbor_r(root->right, n, orientation + 1, min_dist, near);
		// as the levels of recursion pop up this compares the current node to the min dist starting with the leaf
		double d;
		if (near != nullptr) d = dist(temp->values, near->values);
		else d = dist(temp->values);
		if (d < min_dist) near = temp;
		return near;
	}
	double dist(vector<int> &a, vector<int> &b = {}) {
		// finds the distance between two nodes
		int sizeA = a.size();
		if (b.size() == 0) return numeric_limits<double>::max();
		int sizeB = b.size();
		int sum = 0;
		if (sizeA != sizeB) return -1;
		for (int i = 0; i < sizeA; i++)
			sum += pow((a[i] - b[i]), 2);
		// squared sum prevents us from computing sqrt alot
		return sum;
	}
};
