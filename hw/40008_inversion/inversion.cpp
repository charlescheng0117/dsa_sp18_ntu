#include <iostream>
#include <vector>

using namespace std;

void merge_sort(vector<int>& a, vector<int>& b, int l, int r, long long int& ans) {
    if (r - l == 1) {
        return;
    }

    int m = (l + r) / 2;
    merge_sort(a, b, l, m, ans);
    merge_sort(a, b, m, r, ans);

    copy(a.begin() + l, a.begin() + r, b.begin() + l);
    
    int i = l, j = m, k = l;

    for (; i < m && j < r; k++ ) {
        if (b[j] < b[i]) {
            a[k] = b[j++];
            ans += (m - i);
        } else {
            a[k] = b[i++];
        }
    }
    copy(b.begin() + i, b.begin() + m, a.begin() + k);
    copy(b.begin() + j, b.begin() + r, a.begin() + k);

}


int main(int argc, char *argv[]) {
    
    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; ++t) {
        int N;
        scanf("%d", &N);

        vector<int> a(N);
        vector<int> b(N, 0);

        long long int ans = 0;
        
        for (int i = 0; i < N; ++i) {
            scanf("%d", &(a[i]));
        }
        
        merge_sort(a, b, 0, N, ans);
        printf("%lld\n", ans);
    
    
    }

    return 0;
}
