class compare_kd_nodes {
public:
	compare_kd_nodes() : dimension(2) {}
	compare_kd_nodes(int d) : dimension(d) {}
	bool operator () (vector<double> &a, vector<double> &b) {
		return a[dimension] < b[dimension];
	}
private:
	int dimension;
};