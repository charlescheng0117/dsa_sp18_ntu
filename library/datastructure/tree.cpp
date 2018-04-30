#include <iostream>
#include <vector>

using namespace std;

// unfinished

struct Node {
    int data;
    Node* left;
    Node* right;
};

class Tree {
public:    
    Node* root;
    vector<Node*> child;

    Tree () {}

    Tree (Node* r) {
        root = r;
    }

    
};


int main(int argc, char *argv[]) {
    
    return 0;
}


