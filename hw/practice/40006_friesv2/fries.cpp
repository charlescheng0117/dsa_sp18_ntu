#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

int main (int arc, char** argv) {
    
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; ++i) {
        int N;
        scanf("%d", &N);
        vector<int> a(N);
         
        for (int j = 0; j < N; ++j) {
            scanf("%d", &(a[j]));
        }
        
        vector<int> D;
        for (int k : a) {
            vector<int>::iterator it = upper_bound(D.begin(), D.end(), -k);
            if (it == D.end()) {
                D.push_back(-k);
            } else {
                *it = -k;
            }
        }
        printf("%d\n", D.size());
    
    
    }



}
