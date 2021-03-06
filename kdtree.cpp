#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;
#include "kd_range.cpp"
#include "kd_node_compare.cpp"

template<typename T>
class kd_tree {
public:

	kd_tree() : dimensions(2), SIZE(0), root(nullptr) {}
	kd_tree(int d) :  SIZE(0) {
		if (d <= 1) dimensions = 2;
		else dimensions = d;
		root = nullptr;
	}
	kd_tree(vector<vector<T>> nodes) : dimensions(nodes[0].size()) {
		int depth = 0;
		int start = 0;
		int end = nodes.size() - 1;
		root = make_balanced(nodes, start, end, depth);
	}

	~kd_tree() { delete root; }

	//insert a vector into KD tree
	void insert(vector<T> &new_values) {
		if (new_values.size() != dimensions) return;
		kd_node<T> *new_node = new kd_node<T>();
		new_node->values = new_values;
		SIZE++;
		if (root == nullptr) {
			root = new_node;
		} else insert_r(root, new_node, 0);
	}

	void insert(kd_node<T>* &new_node) {
		if (new_node->values.size() != dimensions) return;
		if (root == nullptr) {
			root = new_node;
		} else insert_r(root, new_node, 0);
	}

	void insert_with_id(vector<T> &new_values, int id) {
		if (new_values.size() != dimensions) return;
		kd_node<T> *new_node = new kd_node<T>();
		new_node->values = new_values;
		SIZE++;
		new_node->id = id;

		if (root == nullptr) {
			root = new_node;
		} else insert_r(root, new_node, 0);
	}

	//search KD tree based on coordinate values
	kd_node<T>* search(vector<T> &search_vals) {
		if (search_vals.size() != dimensions) return nullptr;
		if (root == nullptr) return nullptr;

		return search_r(root, search_vals, 0);

	}

	//find nearest neighbor to KD tree by vector
	kd_node<T>* nearest_neighbor(vector<T> &n) {
		int max = INT_MAX;
		kd_node<T>* nearest = nullptr;
		nearest_neighbor_r(root, n, 0, max, nearest);
		return nearest;
	}

	//find nearest neighbor to KD by node
	kd_node<T>* nearest_neighbor(kd_node<T>* &n) {
		kd_node<T>* nearest = nullptr;
		int max = INT_MAX;
		nearest_neighbor_r(root, n->values, 0, max, nearest);
		return nearest;
	}

	//get all nodes falling with in a range specified by a kd_range object
	vector<kd_node<T>*> range_search(kd_range<T> &r) {
		vector<kd_node<T>* > results;
		range_search_r(root, r, results, 0);
		return results;
	}

	vector<kd_node<T>*> range_search(vector<T> &l, vector<T> &u) {
		kd_range<T> r(l, u);
		return range_search(r);
	}

	void print() { print_r(root); }
	size_t size() const { return SIZE; }
	int dimension() const { return dimensions; }
	void setDimension(int d) { dimensions = d; }

private:
	kd_node<T>* root;
	int dimensions;
	size_t SIZE;

	//recursively insert into KD tree
	void insert_r(kd_node<T>* root, kd_node<T>* &new_node, int orientation) {
		if (root == nullptr) return;
		orientation %= dimensions;
		// normal bst insertion except we look at a specific element of the values vector
		if (new_node->values[orientation] < root->values[orientation]) {
			if (root->left == nullptr) {
				root->left = new_node;
				return;
			} else {
				insert_r(root->left, new_node, orientation + 1);
			}
		}
		else if (new_node->values[orientation] >= root->values[orientation]) {
			if (root->right == nullptr) {
				root->right = new_node;
				return;
			} else  {
				insert_r(root->right, new_node, orientation + 1);
			}
		}
	}

	//recursively search KD tree
	kd_node<T>* search_r(kd_node<T> *root, vector<T> &search_vals, int orientation) {
		if (root == nullptr) return nullptr;

		orientation %= dimensions;

		//normal bst search. -- all elements must match
		if (search_vals[orientation] < root->values[orientation])
			return search_r(root->left, search_vals, orientation+1);
		else if (search_vals[orientation] == root->values[orientation])
			if (compare_values(search_vals, root->values)) return root;
			else return search_r(root->right, search_vals, orientation+1);
		else
			return search_r(root->right, search_vals, orientation+1);

	}

	//print in order
	void print_r(kd_node<T>* root) {
		// print value in tree using in_order traversal
		if (root == nullptr) return;
		print_r(root->left);
		int sz = root->values.size();
		cout << (*root) << endl;
		print_r(root->right);
	}

	//recursively find nearest neighbor
	void nearest_neighbor_r(kd_node<T>* &root, vector<T> &n, int orientation, int &min_dist, kd_node<T>* &near) {
		if (root == nullptr) return;
		// root->print();
		if (root->left == nullptr && root->right == nullptr) {
			int d = dist(root->values, n);
			// only set near = root if its distance to target is less than min_dist
			// this will automatically happen for first leaf we hit -- right
			if (d < min_dist && d != 0) {
				min_dist = d;
				near = root;
			}
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
		if (d < min_dist && d != 0) {
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

	//performs a range search
	void range_search_r(kd_node<T> *&root, kd_range<T> &r, vector<kd_node<T>* > &n, int orientation) {
		if (root == nullptr) return;

		orientation %= dimensions;
		
		int currVal = root->values[orientation];

		if (currVal > r.upper[orientation])
			range_search_r(root->left, r, n, orientation+1);
		else if (currVal < r.lower[orientation])
			range_search_r(root->right, r, n, orientation+1);
		else {
			//in the range for this orientation
			if (r.contains(root))
				n.push_back(root);
			range_search_r(root->right, r, n, orientation+1);
			range_search_r(root->left, r, n, orientation+1);
		}
	}

	int dist(vector<T> &a, vector<T> &b) {
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

	bool compare_values(vector<T> &a, vector<T> &b) {
		if (a.size() != b.size()) return false;
		if (a.size() != dimensions) return false;

		for (int i = 0; i < dimensions; i++) {
			if (a[i] != b[i]) return false;
		}

		return true;
	}

	kd_node<T>* make_balanced(vector<vector<T>> &nodes, const int &start, const int &end, const int &depth) {
		int size = end - start;
		// size of list is just one element so return that node
		if (size == 0) {
			kd_node<T>* new_node = new kd_node<T>(nodes[start]);
			return new_node;
		} 
		else if (size < 0) { // the case where a node will have an empty child
			return nullptr;
		}

		auto s = nodes.begin() + start;
		auto e = nodes.begin() + end + 1;
		// sort nodes based on a certain dimension
		sort(s, e, compare_kd_nodes(depth));
		int median_index = start + size / 2;

		kd_node<T>* new_node = new kd_node<T>(nodes[median_index]);
		// left subtree
		new_node->left = make_balanced(nodes, start, median_index - 1, depth % dimensions + 1);
		// right subtree
		new_node->right = make_balanced(nodes, median_index + 1, end, depth % dimensions + 1);

		return new_node;
	}

};
