#include <iostream>
using namespace std;

unsigned long long factorial(int n) {
	if (n==0) return 1;
	return n*factorial(n-1);
}

int main() {
	int nbits=8*sizeof(unsigned long long);
	cout << "sizeof(unsigned long long) = " << nbits << endl;
	cout << "Max of \"unsigned long long\" = " << pow(2, nbits) << endl;
	for (int i=5; i<=25; i=i+5)
		cout << i << "! == " << factorial (i) << endl;
}
