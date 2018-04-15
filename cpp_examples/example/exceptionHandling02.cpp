#include <iostream>
#include <exception>
using namespace std;

void badAllocation(){
	int *myArray;
	for (int i=0; i<100; i++)
		myArray=new int[100000000];
}

int main (){
	try {
		int x[3];
		for (int i=0; i<1000; i++)
			x[i]=i;
		badAllocation();
		int *myArray;
		for (int i=0; i<100; i++)
			myArray=new int[100000000];
	} catch(exception& e) {
		cerr << "Standard exception: " << e.what() << endl;
	}
	return 0;
}
