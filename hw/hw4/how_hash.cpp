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

my_hasher my_hash(string& s) {
    /* return a my_hasher that preprocess s for string matching. */
    int len = s.length();

    // we want hash[0], hash[1], ..., hash[len]
    //            0   ,   s[0] , ...,  s[len - 1]
    my_hasher _hash(len + 1);
    // hash[0] = 0
    _hash[0] = 0;

    for (int i = 1; i <= len; ++i) {
        // TA gives: 
        // S's index: 1, ..., N
        // hash[i] = (hash[i - 1] * x + (S[i] - 'a' + 1) )%M;
       
        _hash[i] = (_hash[i - 1] * x + (s[i - 1] - 'a' + 1) ) % M;
    }

    return _hash;
}

my_hasher my_hash(deque<char>& dq_s) {
    /* return a my_hasher that preprocess s for string matching. */
    int size = dq_s.size();

    // we want hash[0], hash[1], ..., hash[len]
    //            0   ,   s[0] , ...,  s[len - 1]
    my_hasher _hash(size + 1);
    // hash[0] = 0
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
        #ifdef DEBUG
        printf("hash[%d] = %lli\n", i + 1, ret);
        #endif
    }
    
    return ret;
}

lli hash_value(int l, int r, my_hasher& _hash) {
    //return ( _hash[r] - _hash[l - 1] * (x_power[r - l + 1]  % M ) + M) % M;
    return ( _hash[r] - (_hash[l - 1] * x_power[r - l + 1]) % M + M) % M;
}

int count_substring(my_hasher& _hash, string& str_Ti) {

    lli hash_value_Ti;
    if ( (it = str_hash_map.find(str_Ti)) == str_hash_map.end() )
        hash_value_Ti = hash_Ti(str_Ti);
    else
        hash_value_Ti = it->second;
    
    int len_str = _hash.size() - 1;
    int len_Ti = str_Ti.length();
    int end = len_str - len_Ti + 1;
    int count = 0;
    #ifdef DEBUG
    printf("init_str: %s\n", init_str.c_str());
    printf("hash value of Ti: %lli\n", hash_value_Ti);
    #endif
    for (int i = 1; i <= end; ++i) {
        #ifdef DEBUG
        string sub = init_str.substr(i - 1, len_Ti);
        lli tmp = hash_value(i, i + len_Ti - 1, _hash);
        printf("substr: %s, hash value: %lli\n", sub.c_str(), tmp);
        #endif
        if (hash_value(i, i + len_Ti - 1, _hash) == hash_value_Ti)
           ++count;
    } 
    return count;
}

int count_substring(string& init_str, string& str_Ti) {
    
    my_hasher _hash = my_hash(init_str);
    
    // check if str_Ti is in our hash map
    lli hash_value_Ti;
    if ( (it = str_hash_map.find(str_Ti)) == str_hash_map.end() )
        hash_value_Ti = hash_Ti(str_Ti);
    else
        hash_value_Ti = it->second;
    
    int len_str = init_str.length();
    int len_Ti = str_Ti.length();
    int end = len_str - len_Ti + 1;
    int count = 0;
    #ifdef DEBUG
    printf("init_str: %s\n", init_str.c_str());
    printf("hash value of Ti: %lli\n", hash_value_Ti);
    #endif
    for (int i = 1; i <= end; ++i) {
        #ifdef DEBUG
        string sub = init_str.substr(i - 1, len_Ti);
        lli tmp = hash_value(i, i + len_Ti - 1, _hash);
        printf("substr: %s, hash value: %lli\n", sub.c_str(), tmp);
        #endif
        if (hash_value(i, i + len_Ti - 1, _hash) == hash_value_Ti)
           ++count;
    } 
    return count;

}

void update_front(my_hasher& _hash, char c) {
    // update our _hash after insert c at front
    
    // first insert 0 at _hash[0], update _hash[1] as hash_c
    lli hash_c = (c - 'a' + 1);
    _hash.push_front(0);
    _hash[1] = hash_c;
    
    int size = _hash.size();
    
    int prev_tmp, cur_tmp; // to remember the previous, current hash value
    prev_tmp = _hash[0]; // restore _hash[2] for later use
    cur_tmp = _hash[2];
    _hash[2] = (_hash[1] * x + cur_tmp);
    prev_tmp = cur_tmp;

    for (int i = 3; i < size; ++i) {
        cur_tmp = _hash[i];
        _hash[i] = (_hash[i - 1] * x + cur_tmp - x * prev_tmp) % M;
        prev_tmp = cur_tmp;
    }
    
    return; 
}

void update_end(my_hasher& _hash, char c) {
    // update our _hash after insert c at end
    lli hash_c = ( _hash.back() * x + (c - 'a' + 1) ) % M;
    _hash.push_back(hash_c);
}

void print_line(string& msg) {
    printf("----------%s----------\n", msg.c_str());
}

void print_end() {
    printf("----------------------------------------\n");
}

void print(string& s) {
    printf("%s\n", s.c_str());
}

template <typename T>
void print(vector<T> v) {
    // length = 100
    //int len = 10000;
    for (int i = 0; i < v.size(); ++i) {
    //for (int i = 0; i < len; ++i)
        cout << i << ": " << v[i] << "\n";
    }

    cout << "\n";
}

template <typename T>
void print(deque<T> v) {
    // length = 100
    //int len = 10000;
    for (int i = 0; i < v.size(); ++i) {
    //for (int i = 0; i < len; ++i)
        cout << i << ": " << v[i] << "\n";
    }

    cout << "\n";
}


int main(int argc, char *argv[])
{
    #ifdef DEBUG
    string msg;
    #endif

    // 29 ^ N, if N > 13 => overflow
    x_power[0] = 0; // 29 ^ 0
    lli tmp = 1;
    for (int i = 1; i <= highest_power; ++i) {
        tmp = x * tmp % M;
        x_power[i] = tmp;
    }

    char S[BUFFSIZE]; // S, initial string

    fscanf(stdin, "%s", S);
    
    #ifdef DEBUG
    printf("input: %s, len = %lu\n", S, strlen(S));
    #endif

    //deque<char> init_dq (S, S + sizeof(S)/sizeof(char));
    string init_str = string(S);
    deque<char> init_dq(init_str.begin(), init_str.end());
    
    // initialize our hasher
    //my_hasher _hash = my_hash(init_str);
    

    int Q; // Q questions
    fscanf(stdin, "%d", &Q);

    int id;
    char c;
    char Ti[BUFFSIZE];
    for (int i = 0; i < Q; ++i) {
        fscanf(stdin, "%d %s", &id, Ti);
        

        #ifdef DEBUG
        printf("id = %d, Ti = %s\n", id, Ti);
        #endif
        switch (id) {
            case 1: update_front(_hash, Ti[0]);
                    //init_str = Ti[0] + init_str;
                    

                    //print(init_str);
                    //hash_front(dict, init_str);
                    break;

            case 2: update_end(_hash, Ti[0]);
                    //init_str += Ti[0];
                    
                    
                    //print(init_str);
                    //hash_end(dict, init_str);
                    break;
             
            case 3: string str_Ti = string(Ti);
                    int count = count_substring(_hash, str_Ti);
                    #ifdef DEBUG
                    printf("Ti is: %s\n", string(Ti).c_str());
                    printf("count is: %d\n", count);
                    #endif
                    printf("%d\n", count);
                    break;             
        
        
        }

    } 

    return 0;

}
