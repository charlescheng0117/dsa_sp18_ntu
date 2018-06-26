#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

typedef long long ll;
typedef vector< vector<ll> > Graph;

ll inf = numeric_limits<ll>::max() / 10;

ll gcd(ll a, ll b) {
    while (a) {
        b %= a;
        swap(a, b);
    }
    return b;
}

struct Fraction {
    ll a;
    ll b;

    Fraction () {}

    Fraction (ll new_a, ll new_b) {
        a = new_a;
        b = new_b;
    }

    bool operator< (const Fraction& x) const {
        return a * x.b < b * x.a;
    }

    void reduce() {
        ll tmp = gcd(a, b);
        a /= tmp;
        b /= tmp;
    }

    void print() {
        printf("%lld/%lld", a, b);
    }
};


int main(int argc, char *argv[]) {
    
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; ++t) {
        int N;
        scanf("%d", &N);
        vector< vector<ll> > A(N + 1, vector<ll>(N + 1, 0));
        vector< vector<ll> > dp(N + 1, vector<ll>(N + 1, inf));
        
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                scanf("%lld", &(A[i][j]));
                if (A[i][j] == 0) {
                    A[i][j] = inf;
                }
            }
        }

        for (int i = 0; i <= N; ++i) {
            A[i][0] = inf;
        }

        for (int i = 1; i <= N; ++i) {
            dp[0][i] = 0; // super vertex to other vertex
        }

        for (int k = 1; k <= N; ++k) {
            for (int i = 0; i <= N; ++i) {
                for (int j = 0; j <= N; ++j) {
                    dp[k][i] = min(dp[k][i], dp[k - 1][j] + A[j][i]);
                }
            
            }
        }
        
        Fraction ans(1, (ll) 0); // +infinity
        for (int i = 1; i <= N; ++i) {
            if (dp[N][i] == inf) {
                continue;
            }
            Fraction now(-1, (ll) 0); // -inifinity
            for (int j = 0; j < N; ++j) {
                Fraction tmp(dp[N][i] - dp[j][i], (long) N - j);
                tmp.reduce();
                now = max(now, tmp);
            }
            ans = min(ans, now);
        }

        Fraction inf_F(inf, (ll) 1);
        if (ans.a == 1 && ans.b == 0) {
            printf("-1 -1\n");
        } else {
            ans.reduce();
            printf("%lld %lld\n", ans.a, ans.b);
        }

    }
    return 0;
}
