#include <vector>
#include <iostream>

using namespace std;

class myVec {
public:
    myVec(int n){
        size = n;
        data = new int[size];
    }

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

int main(int argc, char *argv[]) {
    myVec a(100);
    myVec b = a; // Shared memory & double deletion
    myVec c;
    c = a;       // Default assignment operator invoked
                 // Share memory, memory leak and double deletion

    return 0;
}
