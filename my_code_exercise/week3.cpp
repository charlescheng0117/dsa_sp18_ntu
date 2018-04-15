#include <iostream>

using namespace std;

class List {
public:
	class Node {
	public:
		Node() {
			key = 0;
			next = NULL;
			cout << "You've created a Node. Address = " << this << "\n";
		}

		~Node() {
			cout << "You've deleted a Node. Address = " << this << "\n";	
		}

		int key;
		Node* next;

	};

	List() {
		cout << "You've created a List. Address = " << this << "\n";
		root = new Node();
		size = 100;
		data = new int[size];
	}

	List(int n) {
		cout << "You've created a List. Address = " << this << "\n";
		size = n;
		data = new int[size];
	}

	~List() {
		delete [] data;
		delete root;
		cout << "You've deleted a List. Address = " << this << "\n";
	}

	Node* root;
	int size;
	int *data;
};


int main(int argc, char const *argv[])
{
	List node1(10);
	bool b = (node1.root == NULL);
	cout << b << "\n";
	cout << node1.root << "\n";

	cout << "Test for default constructor\n";
	List node2;

	return 0;
}
