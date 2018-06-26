#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    vector< pair<int, int> > shakes(m);

    int Ai, Bi;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &Ai, &Bi);
        pair<int, int> tmp(Ai, Bi);
        if (Ai > Bi) {
            swap(tmp.first, tmp.second);
        }
        shakes[i] = tmp;
    }

    sort(shakes.begin(), shakes.end());

    int Ci, Di;
    for (int i = 0; i < q; ++i) {
        scanf("%d %d", &Ci, &Di);
        pair<int, int> query(Ci, Di);
        if (Ci > Di) {
            swap(query.first, query.second);
        }
        if (binary_search(shakes.begin(), shakes.end(), query)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }



}
