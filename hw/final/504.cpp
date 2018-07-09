#include <queue>
#include <vector>
#include <iostream>
#include <functional> // greater
#include <unordered_map>
 
 
using namespace std;
 
 
void connect(vector<int>& nxt, vector<int>& prv, int a, int b) {
    nxt[a] = b; prv[b] = a;
}
 
int main(int argc, char *argv[])
{
    int T;
    scanf("%d", &T);
 
    for (int t = 0; t < T; ++t) {
 
        int N;
        scanf("%d", &N);
 
        vector<int> nxt(N + 3);
        vector<int> prv(N + 3);
 
        //vector<int> arr(N);
        unordered_map<int, int> map_num_idx;
 
        int a1;
        scanf("%d", &a1);
        //map_num_idx[a1] = 0;
 
        connect(nxt, prv, N + 1, a1); // head
        connect(nxt, prv, a1, N + 2); // tail
 
        int ai;
        int tmp = a1;
        for (int i = 1; i < N; ++i) {
            scanf("%d", &ai );
            //map_num_idx[ai] = i;
            //connect(nxt, prv, A, nxt[B]);
            //connect(nxt, prv, B, A);
            connect(nxt, prv, ai, nxt[tmp]);
            connect(nxt, prv, tmp, ai);
            tmp = ai;
        }
 
        tmp = N+1;
        tmp = nxt[tmp];
        for (int i = 0; i < N; ++i) {
            cout << tmp << " ";
            tmp = nxt[tmp];
        }
        cout << "\n";
 
        int Q;
        scanf("%d", &Q);
        //cout << Q << "\n";
        int ans;
 
        //cout << "hey\n";
 
        for (int i = 0; i < Q; ++i) {
            int q;
            scanf("%d", &q);
            if (q == 1) {
 
                int x1, y1, x2, y2;
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                //scanf("%d %d %d %d", x1, y1, x2, y2);
                int x1_prv = prv[x1], y1_nxt = nxt[y1];
                int x2_prv = prv[x2], y2_nxt = nxt[y2];

                connect(nxt, prv, prv[x1], nxt[y1]);
                connect(nxt, prv, prv[x2], nxt[y2]);

                connect(nxt, prv, x1_prv, x2);
                connect(nxt, prv, y2, y1_nxt);

                connect(nxt, prv, x2_prv, x1);
                connect(nxt, prv, y1, y2_nxt);
 
            } else { // q = 2
                int x, d;
                scanf("%d %d", &x, &d);
 
                if (d == 0) {
                    ans = prv[x];
                    if ( (ans == (N + 1)) || (ans == (N + 2) ) ) {
                        printf("meow\n");
                    } else {
                        printf("%d\n", ans);
                    }
                } else {
                    ans = nxt[x];
                    if ( (ans == (N + 2)) || (ans == (N + 1))  ) {
                        printf("meow\n");
                    } else {
                        printf("%d\n", ans);
                    }
                }
 
            }
 
        }
    }
 
    return 0;
}
