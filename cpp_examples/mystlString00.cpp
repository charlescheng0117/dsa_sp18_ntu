#include <iostream>
#include <string>
#include <vector>
//using std::string;


using namespace std;

int main(int argc, char const *argv[]) {
	string I = "I'm going";
	string to = " to ";
	string school = "CMU/UCBerkeley/Stanford.";

	string *ad = &I;
	string **adofad = &ad;


	if (I > to) 
		cout << I + to + school << "\n";
	
	cout << "Address of I is 	 	    " << ad << "\n";
	cout << "Address of address of I is  " << &ad << "\n"; 
	cout << "Ad of ad of ad of I is      " << &adofad << "\n"; 
	cout << *( *( adofad) ) << "\n";

	int n = 3, m = 5;
	vector< vector<int> > mat(n, vector<int>(m));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << mat[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}
