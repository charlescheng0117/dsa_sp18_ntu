#include <iostream>
#include <list>
using namespace std;

// Print a list
template <class T>
void listPrint(list<T> &myList, char *listName){
	list<T>::iterator p;
	cout << "Entries of " << listName << ":" << endl;
	for (p=myList.begin(); p!=myList.end(); p++);
		cout << "\t" << "==>" << *p << endl;
}

// Simple example uses type int
int main(){
	list<int> myList;
	myList.push_back(3);			// Insert a new element at the end
	myList.push_front(5);			// Insert a new element at the beginning
	myList.insert(++myList.begin(), 4);	// Insert "4" before position of first argument
	cout << "myList.size() = " << myList.size() << endl;
	myList.push_back(8);
	myList.push_back(9);
	list<int>::iterator i;
	for(i=myList.begin(); i!=myList.end(); ++i)
		cout << *i << " ";
	cout << endl;
//	listPrint(myList, "myList");
	return 0;
}