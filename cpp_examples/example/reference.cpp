#include <cstdlib>
#include <iostream>
using namespace std;
#include <string>
using std::string;

void test() {
	string author="Confucious";
	cout << "author = " << author << endl;
	string& penName=author;
	penName="James bond";
	cout << "author = " << author << endl;

	string name = author;
	cout << "name = " << name << endl;
	name = "E.W.Dijkstra";

	cout << "name = " << name << endl;
	cout << "author = " << author << endl;
}

void test_int() {
	int i = 3;
	cout << "i = " << i << endl;
	int& j = i;
	j = 1;
	cout << "i = " << i << endl;
}

int main(){
	string author="Confucious";
	cout << "author = " << author << endl;
	string& penName=author;
	penName="James bond";
	cout << "author = " << author << endl;

	test_int();

	return EXIT_SUCCESS;
}
