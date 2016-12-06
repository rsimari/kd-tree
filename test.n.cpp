#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main(int argc, char* argv[]) {

	string fileName = argv[1];
	cout << fileName;


	ifstream ifs(fileName);

	if (ifs.is_open()) {
		string line;
		getline(ifs, line);
		//cout << line << endl;

		string output = argv[2];
		//write to file
		ofstream ofs(output);
		ofs << line;
		ifs.close();
		ofs.close();

	}
	else cout << "Unable to read input file." << endl;



	return 0;
}
