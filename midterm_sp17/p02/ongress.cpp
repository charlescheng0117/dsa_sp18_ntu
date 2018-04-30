#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


int main(int argc, char *argv[]) {
    
    int n, m;

    fscanf(stdin, "%d %d", &n, &m);

    vector<int> blocks(n);

    int pi;
    for (int i = 0; i < n; ++i) {
        fscanf(stdin, "%d", &pi);
        //printf("%d ", pi);
        blocks[i] = pi;
    }
    //printf("\n");

    int uj, vj;
    int sum;
    for (int i = 0; i < m; ++i) {
        fscanf(stdin, "%d %d", &uj, &vj);
        sum = accumulate(blocks.begin() + uj - 1, blocks.begin() + vj, 0);
        printf("%d\n", sum);
    }

    return 0;
}
