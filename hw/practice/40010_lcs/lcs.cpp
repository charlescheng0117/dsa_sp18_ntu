#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;


int main (int argc, char** argv) {

    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; ++t) {
    
        int N, M;
        scanf("%d %d", &N, &M);
    
        char A[N + 1];
        char B[M + 1];
        
        scanf("%s", A);
        scanf("%s", B);

        if ( strcmp(A, B) == 0) {
            printf("%s\n", A);
            continue;
        }

        vector< vector<int> > dp(N + 1, vector<int>(M + 1, 0)); // all zeros
        // char ans[];
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                //int tmp1 = dp[i][j + 1];
                //int tmp2 = dp[i + 1][j];
                //int tmp3 = A[i] == B[j] ? dp[i][j] + 1 : 0;
                dp[i + 1][j + 1] = max( max(dp[i][j + 1], dp[i + 1][j]) , A[i] == B[j] ? dp[i][j] + 1 : 0 );
            }
        }

        int len = dp[N][M];
        char ans[len + 1];
        ans[len] = '\0';
        if (len == 0) {
            printf("*\n");
        } else {
            int i, j;
            for (i = N, j = M; dp[i][j]; ) {
                if (dp[i][j - 1] == dp[i][j]) {
                    j--;
                } else if (dp[i - 1][j] == dp[i][j]){
                    i--;
                } else {
                    i--;
                    j--;
                    ans[dp[i][j]] = A[i];
                }
            
            }
            printf("%s\n", ans);
        }
    } 
    






}
