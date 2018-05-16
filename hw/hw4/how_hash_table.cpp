#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cmath>
#include <unordered_map>

using namespace std;

//#define DEBUG 1
//#define BASIC_STR 1

#define BUFFSIZE 100000
#define x 29
#define highest_power 100000
#define M 1000000007

typedef long long int lli;
typedef deque<lli> my_hasher;

// global variable
vector<lli> x_power(highest_power);

// map to store hash value
unordered_map<string, lli> str_hash_map;
unordered_map<string, lli>::iterator it;

// map hash value to count
unordered_map<lli, int> hash_to_count;

my_hasher my_hash(deque<char>& dq_s) {
    /* return a my_hasher that preprocess s for string matching. */
    int size = dq_s.size();

    // we want hash[0], hash[1], ..., hash[len]
    //            0   ,   s[0] , ...,  s[len - 1]
    my_hasher _hash(size + 1);
    _hash[0] = 0;

    for (int i = 1; i <= size; ++i) {
        // TA gives: 
        // S's index: 1, ..., N
        // hash[i] = (hash[i - 1] * x + (S[i] - 'a' + 1) )%M;
        
        _hash[i] = (_hash[i - 1] * x + (dq_s[i - 1] - 'a' + 1) ) % M;
    }

    return _hash;
}

lli hash_Ti(string &Ti) {
    /* get the hash value of Ti */
    lli ret = 0;
    int len = Ti.length();
    for (int i = 0; i < len; ++i) {
        ret = (ret * x + (Ti[i] - 'a' + 1)) % M;
    }
    
    return ret;
}

lli hash_value(int l, int r, my_hasher& _hash) {
    return ( _hash[r] - (_hash[l - 1] * x_power[r - l + 1]) % M + M) % M;
}


void print(string& s) {
    printf("%s\n", s.c_str());
}

void print_deque(deque<char>& dq_str, int start, int end) {
    // [start, end)
    for (int i = start; i < end; ++i)
        printf("%c", dq_str[i]);
    printf("\n");
}

void print_deque(deque<char>& dq_str) {
    for (int i = 0; i < dq_str.size(); ++i)
        printf("%c", dq_str[i]);
    printf("\n");

    for (int i = 0; i < dq_str.size(); ++i)
        printf("%d", i + 1);

    printf("\n");
}

template <typename T>
void print(vector<T> v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << i << ": " << v[i] << "\n";
    }

    cout << "\n";
}

template <typename T>
void print(deque<T> v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << i << ": " << v[i] << "\n";
    }

    cout << "\n";
}

void hash_all(my_hasher& _hash, deque<char>& dq_str) {

    int length = _hash.size();
    lli hash_v;
    for (int len = 1; len <= 10; ++len) {
        for (int idx_start = 0; idx_start + len < length; ++idx_start) {
            hash_v = hash_value(idx_start + 1, idx_start + len, _hash);
            ++hash_to_count[hash_v];
        }
    }
}


void update_insert_front(my_hasher& hasher_front_t4, deque<char>& dq_str) {
    // update our _hash after insert c at front
    // c has been insert at the front of dq_str
    int hash_c = (dq_str.front() - 'a' + 1);

    ++hash_to_count[hash_c];

    // update hash_t3 by insert hash_c at hash_t3[1]
    hasher_front_t4.push_front(0);
    hasher_front_t4[1] = hash_c;

    int len_str = dq_str.size();
    
    lli hash_v;
    lli tmp;
    for (int len = 2; len <= 10 && len <= len_str; ++len) {
        hasher_front_t4[len] = (hasher_front_t4[len] + (x_power[len - 1] * hash_c) % M + M ) % M; 
        
        ++hash_to_count[hasher_front_t4[len]];
    }
    
    return; 
}

void update_insert_end(my_hasher& hasher_end_t4, deque<char>& dq_str) {
    // update our _hash after insert c at end
    int ascii_c = dq_str.back();
    lli hash_end = ( hasher_end_t4.back() * x + (ascii_c - 'a' + 1) ) % M;
    hasher_end_t4.push_back(hash_end);

    lli hash_v;
    int N = hasher_end_t4.size() - 1;
    int len_str = dq_str.size();
    for (int len = 1; len <= 10 && len <= len_str; ++len) {
        // i represents length of string to hash_c
        // i = 2 => hash 'ab'
        
        //hash_value = ( _hash[r] - (_hash[l - 1] * x_power[r - l + 1]) % M + M) % M;
        hash_v = hash_value(N - len + 1 , N, hasher_end_t4);
        //printf("substr: ");     print_deque(dq_str, len_str - len, len_str); 
        //printf("len = %d, hash_v = %lli\n", len, hash_v);
        ++hash_to_count[hash_v];
    }
    
}

void update_end(my_hasher& _hash, char c) {
    // update our _hash after insert c at end

    lli hash_c = ( _hash.back() * x + (c - 'a' + 1) ) % M;
    _hash.push_back(hash_c);
}

int count_substring(my_hasher& hasher_t3, string& str_Ti) {

    lli hash_value_Ti;
    if ( (it = str_hash_map.find(str_Ti)) == str_hash_map.end() )
        hash_value_Ti = hash_Ti(str_Ti);
    else
        hash_value_Ti = it->second;
    
    int len_str = hasher_t3.size() - 1;
    int len_Ti = str_Ti.length();
    int end = len_str - len_Ti + 1;
    int count = 0;

    for (int i = 1; i <= end; ++i) {
        if (hash_value(i, i + len_Ti - 1, hasher_t3) == hash_value_Ti)
           ++count;
    } 
    return count;
}


int main(int argc, char *argv[])
{
    // 29 ^ N, if N > 13 => overflow
    x_power[0] = 1; // 29 ^ 0
    lli tmp = 1;
    for (int i = 1; i <= highest_power; ++i) {
        tmp = x * tmp % M;
        x_power[i] = tmp;
    }

    char S[BUFFSIZE]; // S, initial string

    fscanf(stdin, "%s", S);

    string init_str = string(S);

    deque<char> dq_str(init_str.begin(), init_str.end());
    
    my_hasher initial_hasher = my_hash(dq_str);
    my_hasher hasher_t3, hasher_front_t4, hasher_end_t4;

    hasher_front_t4 = hasher_end_t4 = hasher_t3 = initial_hasher;
    
    hash_all(initial_hasher, dq_str);
    
    bool update_flag = false;
    
    int Q; // Q questions
    fscanf(stdin, "%d", &Q);

    int id;
    char c;
    char Ti[BUFFSIZE];
    for (int i = 0; i < Q; ++i) {
        fscanf(stdin, "%d %s", &id, Ti);
        

        switch (id) {
            case 1: update_flag = true;
                    dq_str.push_front(Ti[0]);
                    update_insert_front(hasher_front_t4, dq_str);
                    if (dq_str.size() <= 10) {
                        hasher_end_t4 = hasher_front_t4;
                    } 
                    break;

            case 2: update_flag = true;
                    dq_str.push_back(Ti[0]);
                    update_insert_end(hasher_end_t4, dq_str);
                    if (dq_str.size() <= 10) {
                        hasher_front_t4 = hasher_end_t4;
                    }
                    
                    break;
             
            case 3: string str_Ti = string(Ti);
                    
                    if (str_Ti.length() > 10) {
                        if (update_flag) {
                            
                            hasher_t3 =  my_hash(dq_str); // need to reconstruct _hash
                            update_flag = false;
                        }
                        int count = count_substring(hasher_t3, str_Ti);
                        printf("%d\n", count);
                    } else { // task 4
                        lli hash_v = hash_Ti(str_Ti);
                        printf("%d\n", hash_to_count[hash_v]);    
                    
                    }
                    break;             
        }
    } 
    return 0;
}
