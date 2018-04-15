#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    //string::size_type sz;

    int n;

    do {

    	cout << "Please enter a positive integer: ";
    	cin >> n;
    }
    while (n < 0);
    
    int fac = 1;

    for (int i = 1; i <= n; i += 1) {
	    fac *= i;

    }
    printf("n = %d, fac = %d\n", n, fac);
}
