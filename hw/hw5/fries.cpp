#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

typedef long long int lli;

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
                    cnt[i] = cnt[i] + cnt[j];
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
    
    printf("%d\n", n);
    print(fries);

    vector<lli> len = compute_len(fries);
    print(len);
    
    vector<lli> cnt = compute_cnt(fries, len);
    print(cnt);
    
    vector<int> pre = compute_pre(fries, len);
    print(pre);
    
    return 0;
}
