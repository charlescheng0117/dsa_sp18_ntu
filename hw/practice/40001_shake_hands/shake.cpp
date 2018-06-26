#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    int n, m, q;

    vector< pair<int, int> > shake_hands;

    scanf("%d %d %d", &n, &m, &q);
    
    int A, B;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &A, &B);
        
        pair<int, int> shake(A, B);
        if (A > B) {
            swap(shake.first, shake.second);
        }
        shake_hands.push_back(shake);
    }

    sort(shake_hands.begin(), shake_hands.end());

    int C, D;
    for (int i = 0; i < q; ++i) {
        scanf("%d %d", &C, &D);
        pair<int, int> query(C, D);
        if (C > D) {
            swap(query.first, query.second);
        }
        if (binary_search (shake_hands.begin(), shake_hands.end(), query)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    } 


    return 0;
}
