#include <bits/stdc++.h>
using namespace std;
// Rabin-Karp Algorithm
int main() {
	static char s[100005], buf[300005], cmd[16];
	static const int64_t mod = 1000000007;
	static const int64_t hbase = 64;
	int head, tail;
	int q;
	while (head = 100000, scanf("%s", buf+head) == 1) {
		int n = strlen(buf+head);
		tail = head+n-1;
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%s%s", cmd, s);
			if (cmd[0] == '1') {
				buf[--head] = s[0];
			} else if (cmd[0] == '2') {
				buf[++tail] = s[0];
			} else {
				int64_t h = 0, f = 1;
				n = strlen(s);
				for (int i = 0; i < n; i++)
					h = (h*hbase + s[i])%mod, f = f*hbase%mod;
				int64_t g = 0;
				int ret = 0;
				for (int i = head; i <= tail; i++) {
					g = g*hbase + buf[i];
					g %= mod;
					if (i-n >= head)
						g -= f*buf[i-n]%mod;
					g = (g%mod + mod)%mod;
					if (i-head >= n-1) {
						if (g == h) {
							int valid = 1, j = 0;
//							for (j = 0; j < n && valid; j++)
//								valid &= s[j] == buf[i-n+1+j];
//							valid &= j == n;
							ret += valid;
						}
					}
				}
				printf("%d\n", ret);
			}
		}
	}
	return 0;
}
/*
cd
5
1 b
1 a
2 e
3 cd
3 aa 	

1
0 

d
8
1 a
2 e
1 b
2 n
2 d
3 ba
3 bad
3 badend 

ababa
1
3 aba 

2

*/
