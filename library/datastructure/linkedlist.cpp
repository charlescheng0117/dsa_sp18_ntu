#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *next;
    Node *prev;
    Node () { }
    Node (int v) {
        val = v;
        next = NULL;
        prev = NULL;  
    }
};

class List {
public:
    int length;
    Node *head;

        
    List() { length = 0; }

    List (Node* new_node) {
        head = new_node;
        length = 1;
    }

    void insertFront (Node* new_node) {
        if (length == 0) {
            head = new_node;
        } else {
            cout << "inserting node\n";
            Node* tmp = head;
            head = new_node;
            
            head->prev = NULL;
            head->next = tmp;
        }
        ++length;
    }

    Node* removeFront () {
        Node* tmp = head;
        head = head->next;
        head->prev = NULL;
        return tmp;
    }

    void print() {
        Node* tmp = head;
        while (tmp != NULL) {
            printf("%d ", tmp->val);
            tmp = tmp->next;
        }
        printf("\n");
    }
};


int main(int argc, char *argv[]) {
    List l;
    Node n1(1), n2(2), n3(3);
    Node* tmp;

    // testing insert front
    l.insertFront(&n1);
    l.insertFront(&n2);
    l.insertFront(&n3);
    l.print();
    
    // testing remove front
    tmp = l.removeFront();
    printf("Node got removed: %d\n", tmp->val);
    printf("Now l = \n");
    l.print();

    return 0;
}
