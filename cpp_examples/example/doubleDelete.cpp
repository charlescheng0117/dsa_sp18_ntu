// Example of memory leak (which doesn't crash)

#include <cstdlib>
#include <iostream>
using namespace std;		// makes std:: available

int main(){
	int *x=new int;
	cout << "x=" << x << endl;
	cout << "*x=" << *x << endl;
	*x=100;
	cout << "*x=" << *x << endl;
	cout << "Try first delete..." << endl;
	delete x;
	cout << "Try second delete..." << endl;
	delete x;
	return EXIT_SUCCESS;
}