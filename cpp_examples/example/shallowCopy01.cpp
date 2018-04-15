// How to show shallow copy 
#include <cstdlib>
#include <iostream>
using namespace std;

class myVec {
	public:
		myVec(){};
		~myVec(){};
		void print();	// Print data
		vec<int> data;
	private:
};

void myVec::print(){
	cout << "[";
	for (int i=0; i<data.size(); i++)
		cout << data[i] << " ";
	cout << "]" << endl;
}

int main(){
	myVec a;
	myVec b=a;

	cout << "Address of a.data: " << a.data << endl;
	cout << "Address of b.data: " << b.data << endl;
	a.data[0]=2;
	cout << "a.data[0]=2 ==>" << endl; 
	cout << "a: "; a.print();
	cout << "b: "; b.print();
	b.data[1]=4;
	cout << "b.data[1]=4 ==>" << endl;
	cout << "a: "; a.print();
	cout << "b: "; b.print();

	return EXIT_SUCCESS;
}
