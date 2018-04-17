#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    // row: m, col: n
    int m = 3, n = 5;

    // with array, create
    int ** oldM = new int*[n];
    for (int i = 0; i < m; ++i) {
        oldM[i] = new int[n];
    }

    // with array, delete
    for (int i = 0; i < m; ++i) {
        delete [] M[i];
    }
    delete [] M;

    // use STL vectors
    // create
    vector< vector<int> > M(m, vector<int>(n));
    // delete: do nothing

    return 0;
}
