#include <vector>
#include <iostream>

using namespace std;

void connect(vector<long long int>& nxt, vector<long long int>& prv, long long int a, long long int b) {
    nxt[a] = b; prv[b] = a;
}

int main(int argc, char *argv[]) {
    
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; ++t) {
    
        int N, M, a1;
        scanf("%d %d %d", &N, &M, &a1);
    
        vector<long long int> nxt(N + 3);
        vector<long long int> prv(N + 3);

        connect(nxt, prv, N + 1, a1); // head
        connect(nxt, prv, a1, N + 2); // tail

        int K, A, B, C;
        vector<long long int> ans;
        long long int cnt = 0;
        for (int m = 0; m < M; ++m) {
            scanf("%d %d %d %d", &K, &A, &B, &C);
            if (K == 1) { 
                if (C == 1) {
                    connect(nxt, prv, prv[B], A);
                    connect(nxt, prv, A, B);
                } else {
                    connect(nxt, prv, A, nxt[B]);
                    connect(nxt, prv, B, A);
                }
            } else if (K == 2) {
                connect(nxt, prv, prv[A], nxt[B]);
                connect(nxt, prv, prv[C], A);
                connect(nxt, prv, B, C);
            } else {
                long long int i, j;

                if (C == 1) {
                    for (i = A, j = nxt[A]; i <= N && B; i = prv[i], B--) {
                       ans.push_back(i); 
                    }
                } else {
                    for (j = A, i = prv[A]; j <= N && B; j = nxt[j], B--) {
                       ans.push_back(j); 
                    }
                }
                connect(nxt, prv, i, j);
                cnt += B;
            } 
        } 
        printf("%lld\n", cnt);
        for (long long int i : ans) {
            printf("%lld\n", i);
        }
    }
    return 0;
}
