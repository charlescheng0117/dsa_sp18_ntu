#include <iostream>
#include <vector>

using namespace std;

int cnt;

void print(vector<int> v, int l, int r) {
    for (vector<int>::iterator it = v.begin() + l; it != v.begin() + r; ++it) {
        printf("%d ", *it);
    }
    printf("\n");

}

void merge_sort(vector<int>& a, vector<int>& b, int l, int r, long long int& ans) {
    if (r - l == 1) {
        return;
    }

    int m = (l + r) / 2;
    merge_sort(a, b, l, m, ans);
    merge_sort(a, b, m, r, ans);

    copy(a.begin() + l, a.begin() + r, b.begin() + l);
    printf("recursion %d. a[%d] ~ a[%d]: ", cnt, l, r);
    print(a, l, r);


    int i = l, j = m, k = l;

    for (; i < m && j < r; k++ ) {
        if (b[j] < b[i]) {
            // equivalent to return b[j]
            // then j++
            a[k] = b[j++];
            ans += (m - i);
        } else {
            a[k] = b[i++];
        }
    }
    copy(b.begin() + i, b.begin() + m, a.begin() + k);
    printf("recursion %d. a[%d] ~ a[%d]: ", cnt, l, a.size());
    print(a, k, a.size());
    printf("recursion %d. b[%d] ~ b[%d]: ", cnt, i, m);
    print(b, i, m);
    copy(b.begin() + j, b.begin() + r, a.begin() + k);
    printf("recursion %d. a[%d] ~ a[%d]: ", cnt, k, a.size());
    print(a, k, a.size());
    printf("recursion %d. b[%d] ~ b[%d]: ", cnt, j, r);
    print(b, j, r);
    cnt++;

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
        print(a, 0, a.size());
        
        cnt = 0;
        merge_sort(a, b, 0, N, ans);
        printf("%lld\n", ans);
    
    
    }

    return 0;
}
