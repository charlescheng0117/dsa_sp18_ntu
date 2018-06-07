#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>

using namespace std;

typedef long long int lli;
#define M 1000000007
#define DEBUG

struct answer {
    int m;
    lli q;
    vector<int> days_seq;

    answer() {}

    answer(int _m, lli _q, vector<int> _days_seq) {
        m = _m;
        q = _q;
        days_seq = _days_seq;
    }

};

vector<lli> compute_len(vector<int>& fries) {
    int num = fries.size() - 1;
    vector<lli> len(num + 1); // ret[1, 2, ..., N]
    len[1] = 1; // len[1] can be defined as 1

    for (int i = 2; i <= num; ++i) {
        //len[i] = 1;
        //int candidate_len = - numeric_limits<int>::infinity();
        lli candidate_len = 0;
        for (int j = 1; j < i; ++j) {
            if (fries[j] <= fries[i]) {
                if (len[j] > candidate_len) {
                    candidate_len = len[j];
                } 
            }
        }
        len[i] = candidate_len + 1;
    }
    
    return len;
}

vector<lli> compute_cnt(vector<int>& fries, vector<lli>& len) {
    int N = len.size() - 1;
    vector<lli> cnt(N + 1);
    for (int i = 1; i <= N; ++i) {
        if (len[i] == 1) {
            cnt[i] = 1;
        } else {
            cnt[i] = 0;

            for (int j = 1; j < i; ++j) {
                if (len[j] == (len[i] - 1) && fries[j] <= fries[i]) {
                    cnt[i] = (cnt[i] + cnt[j]) % M;
                    //printf("%d. %lld\n", i, cnt[i]);
                }
            
            }     
        
        }
    
    }
    return cnt;

}

vector<int> compute_pre(vector<int>& fries, vector<lli>& len) {
    int N = len.size() - 1;
    vector<int> pre(N + 1);
    for (int i = 1; i <= N; ++i) {
        if (len[i] == 1) {
            pre[i] = 0;
        } else {
            
            for (int j = 1; j < i; ++j) { // j = i - 1, i - 2, ..., 1
                if (len[j] == len[i] - 1 && fries[j] <= fries[i]) {
                    pre[i] = j;
                    break;
                }
            }    
        }
    }
    return pre;

}


int find_earliest_fries(vector<lli>& len) {
    int ret = 0;
    int n = len.size();
    for (int i = 1; i < n; ++i) {
        if (len[i] > len[ret]) {
            ret = i;
        }
    }
    return ret;
}

answer compute_ans(vector<int>& fries, vector<lli>& len, vector<lli>& cnt, vector<int>& pre) {
    // a map to record, for a given len arr,
    // ex. 
    // len: 0 1 2 3 2 4 1 1 2 3 4 
    // cnt: 0 1 1 1 1 1 1 1 1 1 1 
    // pre: 0 0 1 2 1 3 0 0 7 8 9  
    // 
    // then create a map len 
    
    int n = len.size() - 1;

    answer out;
    int idx_max = find_earliest_fries(len);
    int m = len[idx_max];
    
    // compute q
    lli q = 0;
    for (int i = 1; i <= n; ++i) {
        if (len[i] == m) {
            q = (q + cnt[i]) % M;
        } 
    }

    vector<int> days_seq(m);

    int previous_day = idx_max;
    for (int i = m - 1; i >= 0; --i) {
        days_seq[i] = previous_day;
        previous_day = pre[previous_day];
    }

    out.m = m;
    out.q = q;
    out.days_seq = days_seq;

    return out;
}

template <typename T>
void print(vector<T> v) {
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << "\n";
}

int main(int argc, char *argv[]) {
    
    int n; // days
    fscanf(stdin, "%d", &n);

    vector<int> fries(n + 1); // # of fries in each of n days;
    fries[0] = 0;
    for (int i = 1; i <= n; ++i) {
        //fscanf(stdin, "%lli", &fries[i]);
        fscanf(stdin, "%d", &fries[i]);
    } 
    

    #ifdef DEBUG
    printf("num days: %d\n", n);
    printf("idx: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", i);
    }
    printf("%d\n", n);
    printf("arr: ");
    print(fries);
    #endif
    
    vector<lli> len = compute_len(fries);
    #ifdef DEBUG
    printf("len: ");
    print(len);
    #endif
    
    vector<lli> cnt = compute_cnt(fries, len);
    #ifdef DEBUG
    printf("cnt: ");
    print(cnt);
    #endif
    
    vector<int> pre = compute_pre(fries, len);
    #ifdef DEBUG
    printf("pre: ");
    print(pre);
    #endif

    answer ans = compute_ans(fries, len, cnt, pre);
    
    printf("%d\n", ans.m);
    printf("%lld\n", ans.q);
   

    int m = ans.m;
    vector<int> days_seq = ans.days_seq;
    for (int i = 0; i < m - 1; ++i) {
        printf("%d ", days_seq[i]);
    }
    printf("%d\n", days_seq[m - 1]);

    return 0;
}
