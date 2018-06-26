#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
   
    int M, N, K;

    scanf("%d %d %d", &M, &N, &K);

    //int M = m;
    //int N = n;
    //int K = k;

    char a[5001];
    char b[5001];

    scanf("%s", a);
    scanf("%s", b);

    //printf("%s\n%s\n", a, b);

    vector< vector< vector<long long> > > dp (2, vector< vector<long long> >(M + 1, vector<long long>(K + 1, 0) ));
    vector< vector< vector<long long> > > dp2 (2, vector< vector<long long> >(M + 1, vector<long long>(K + 1, 0) ));


    /*
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < M+1; ++j) {
            for (int k = 0; k < K+1; ++k) {
                printf("%d ", dp[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }*/
       
    for (int ti = 1, i = 1; ti <= N; ti++, i ^= 1) {
        
        // fill dp[i], dp2[i] = 0
        for (int r = 0; r < M + 1; ++r) {
            for (int c = 0; c < K + 1; ++c) {
                dp[i][r][c] = 0;
                dp2[i][r][c] = 0;
            }
        }
        
        for (int j = 1; j <= M; ++j) {
            if (a[ti - 1] == b[j - 1]) {
                for (int k = 1; k <= K; ++k) {
                    dp2[i][j][k] = max(dp2[i^1][j - 1][k], dp[i^1][j-1][k-1]) + 2*(a[ti-1] == 'a');
                    dp[i][j][k] = max(dp[i][j-1][k], dp[i^1][j][k]);
                    dp[i][j][k] = max(dp[i][j][k], dp2[i][j][k]);
                }
            } else {
                for (int k = 1; k <= K; ++k) {
                    dp[i][j][k] = max(dp[i^1][j][k], dp[i][j-1][k]);
                } 
            
            }
        } 
        
    }
    
    printf("%lld\n", dp[N&1][M][K]);

    return 0;
}
