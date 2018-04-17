#include <vector>
#include <iostream>

using namespace std;

class myVec {
public:
    myVec(int n){
        size = n;
        data = new int[size];
    }
    
    myVec(const myVec& a);

    myVec& operator=(const myVec& a);

    myVec() {
        size = 10;
        data = new int[size];
    }
    ~myVec() {
        delete[] data; // may cause double deletion
    }
    int *data;
    int size;
};

// Copy constructor
myVec::myVec(const myVec& a) {
    size = a.size;
    data = new int[size];
    for (int i = 0; i < size; ++i)
        data[i] = a.data[i];
}

// Assignment operator
myVec& myVec::operator=(const myVec& a) {
    if (this != &a) {    // avoid self-assignment
        delete [] data; // avoid memory leak
        size = a.size; 
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = a.data[i];
        }

    }
    return *this;
}

int main(int argc, char *argv[]) {
    myVec a;


    return 0;
}
