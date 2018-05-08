#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <string>
#include <cmath>

using namespace std;

//#define DEBUG 1
//#define BASIC_STR 1

#define BUFFSIZE 100000
#define x 29
#define M 1000000007

typedef long long int lli;
typedef vector<lli> my_hasher;

vector<lli> x_power;

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
    return ( (_hash[r] - _hash[l - 1] * x_power[r - l + 1] ) % M \
           + M) % M;
}

int count_substring(string& init_str, string& Ti) {
    
    my_hasher _hash = my_hash(init_str);
    lli hash_value_Ti = hash_Ti(str_Ti);
    int len_str = init_str.length();
    int len_Ti = str_Ti.length();
    int end = len_str - len_Ti + 1;
    int count = 0;
    for (int i = 0; i < end; ++i) {
       if (hash_value(i, i + len_Ti, _hash) == hash_value_Ti)
           ++count;
    } 
    return count;

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
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    cout << "\n";
}

int main(int argc, char *argv[])
{
    #ifdef DEBUG
    string msg;
    #endif

    // 29 ^ N, if N > 13 => overflow
    x_power.push_back(1); // 29 ^ 0

    for (int i = 1; i <= 12; ++i) {
        lli tmp = pow(x, i);
        x_power.push_back(tmp);
    }
    
    #ifdef DEBUG
    print(x_power);
    #endif

    char S[BUFFSIZE]; // S, initial string

    fscanf(stdin, "%s", S);
    
    #ifdef DEBUG
    printf("input: %s, len = %lu\n", S, strlen(S));
    #endif

    string init_str = string(S);
    
    #ifdef BASIC_STR
    printf("string = %s\n", init_str.c_str());
    printf("add CMU at the end = %s\n", init_str.append("CMU").c_str());
    printf("add UCBerkeley at the front = %s\n", init_str.insert(0, "UCBerkeley").c_str());
    #endif

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
            case 1: //init_str.append(string(Ti[0]));
                    init_str = Ti[0] + init_str;
                    //print(init_str);
                    //hash_front(dict, init_str);
                    break;

            case 2: //init_str.push_back(Ti[0]);
                    init_str += Ti[0];
                    //print(init_str);
                    //hash_end(dict, init_str);
                    break;
             
            case 3: printf("%d\n", dict[string(Ti)]);
                    string str_Ti = string(Ti);
                    my_hasher _hash = my_hash(init_str);
                    lli hash_value_Ti = hash_Ti(str_Ti);
                    int len_Ti = str_Ti.length();
                    int count = count_substring(init_str, str_Ti);
                    printf("%d\n", count);
                    break;             
        
        
        }

    } 

    return 0;
}
