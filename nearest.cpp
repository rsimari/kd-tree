#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "kdtree.cpp"
using namespace std;

void buildNearestTree(ifstream &ifs, kd_tree<double>* &tree);
vector<double> splitData(string &line, char d);
vector<int> nearestNeighbors(kd_tree<double>* &tree, vector<double> &target, int n);

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cout << "Usage: ./nearest inputfile" << endl;
		return 1;
	}

	string inputFile = argv[1];
	ifstream ifs(inputFile);

	if (ifs.is_open()) {
		kd_tree <double> *tree = new kd_tree<double>(3);
		buildNearestTree(ifs, tree);

		ifs.close();

		while (1) {
			string targetStr;
			getline(cin, targetStr);
			vector<double> target = splitData(targetStr, ',');
			vector<double> scores(target.begin() + 1, target.end());
			vector<int> ids = nearestNeighbors(tree, scores, 1);
			for (int i = 0; i < ids.size(); i++) {
				cout << ids[i] << endl;
			}
		}

		/*string outputFile = argv[2];
		//write to file
		ofstream ofs(outputFile);
		if (ofs.is_open()) {
			for (int i = 0; i < ids.size(); i++) {
				ofs << ids[i] << endl;
			}
			ofs.close();
		}
		else cout << "Unable to open output file." << endl;*/
	}
	else cout << "Unable to read input file." << endl;
	return 0;
}


vector<int> nearestNeighbors(kd_tree<double>* &tree, vector<double> &target, int n) {
	vector<int> ids;
	kd_node<double> *r = tree->nearest_neighbor(target);
	ids.push_back(r->id);
	return ids;
}

void buildNearestTree(ifstream &ifs, kd_tree<double>* &tree) {
	//needs to read in every number, place in kd tree, evaluate based on the first
	string currline;
	while (getline(ifs, currline)) {
		vector<double> data = splitData(currline, ',');
		vector<double> scores(data.begin() + 1, data.end());
		tree->insert_with_id(scores, (int)data[0]);
	}
}

vector<double> splitData(string &line, char d) {
	vector<double> results;
	int prevLoc = 0;
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == d) {
			string newString = line.substr(prevLoc, i);
			results.push_back(stod(newString));
			prevLoc = i+1;
		}
	}
	results.push_back(stod(line.substr(prevLoc, line.length())));
	return results;
}
