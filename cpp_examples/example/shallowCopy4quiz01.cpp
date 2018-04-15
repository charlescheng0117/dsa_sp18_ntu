// Demo of shallow copy ==> Use array of fixed size to avoid problems
#include <cstdlib>
#include <iostream>
using namespace std;
#define N 4

class student {
	public:
		student(){}
		~student(){}
		void print();	// Print score
		int score[N];
		string name;
};

void student::print(){
	cout << "name=" << name.c_str() << ", ";
	cout << "score=[";
	for (int i=0; i<N; i++)
		cout << score[i] << " ";
	cout << "]" << endl;
}

int main(){
	student a;
	a.name="John"; a.score[0]=70;
	student b=a;
	b.name="Mary"; b.score[2]=90;

	cout << "Address of a.score: " << a.score << endl;
	cout << "Address of b.score: " << b.score << endl;
	cout << "a: "; a.print();
	cout << "b: "; b.print();

	return EXIT_SUCCESS;
}
