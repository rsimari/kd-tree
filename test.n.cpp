#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "kdtree.cpp"
using namespace std;

vector<int> nearestNeighborsAnalysis(ifstream &ifs);
int main(int argc, char* argv[]) {

	if (argc < 3) {
		cout << "Usage: ./test.n inputfile outputfile" << endl;
		return 1;
	}

	string inputFile = argv[1];
	ifstream ifs(inputFile);

	if (ifs.is_open()) {
		vector<int> ids = nearestNeighborsAnalysis(ifs);
		ifs.close();

		string outputFile = argv[2];
		//write to file
		ofstream ofs(outputFile);
		if (ofs.is_open()) {
			for (int i = 0; i < ids.size(); i++) {
				ofs << ids[i] << endl;
			}
			ofs.close();
		}
		else cout << "Unable to open output file." << endl;
	}
	else cout << "Unable to read input file." << endl;
	return 0;
}


vector<int> nearestNeighborsAnalysis(ifstream &ifs) {
	//needs to read in every number, place in kd tree, evaluate based on the first

	kd_tree <double> nearestTree(3);

	vector<double> target;
	int n;
	ifs >> n;

	int id;
	ifs >> id;

	double curr;
	for (int i = 0; i < n-1; i++) {
		ifs >> curr;
		target.push_back(curr);
	}

	ifs >> id;
	while (id > -1) {
		vector<double> data;
		for (int i = 0; i < n-1; i++) {
			ifs >> curr;
			data.push_back(curr);
		}
		nearestTree.insert_with_id(data, id);
		ifs >> id;
	}

	kd_node <double> *k = nearestTree.nearest_neighbor(target);
	cout << *k << endl;

	vector<int> ids;
	ids.push_back(k->id);

	return ids;

}
