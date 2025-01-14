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
    // return the hash value of S[l, r], inclusive
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
    printf("str_Ti = %s, hash_value_Ti = %lli\n", str_Ti.c_str(), hash_value_Ti);
    #endif 
    for (int i = 1; i <= end; ++i) {
        #ifdef DEBUG
        //string sub = init_str.substr(i - 1, len_Ti);
        lli tmp = hash_value(i, i + len_Ti - 1, _hash);
        printf("i = %d, hash value: %lli\n", i, tmp);
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


// has bug
void update_front(my_hasher& _hash, char c) {
    // update our _hash after insert c at front
    
    // first insert 0 at _hash[0], update _hash[1] as hash_c
   
    _hash.push_front(0);

    lli _hash1 = (c - 'a' + 1);

    _hash[1] = _hash1;
    int size = _hash.size();

    for (int i = 2; i < size; ++i) {
        _hash[i] = (_hash[i] + x_power[i - 1] * _hash1 % M ) % M;
    }


    /*
    _hash.push_front(0);
    
    int size = _hash.size();

    for (int i = 1; i < size; ++i) {
        _hash[i] = (_hash[i - 1] * x + (dq_str[i - 1] - 'a' + 1) ) % M;
    }*/
    
    return; 
}

void update_front(my_hasher& _hash, deque<char> dq_str) {
    // update our _hash after insert c at front
    
    // first insert 0 at _hash[0], update _hash[1] as hash_c
    
    _hash = my_hash(dq_str);
    /*
    _hash.push_front(0);
    
    int size = _hash.size();

    for (int i = 1; i < size; ++i) {
        _hash[i] = (_hash[i - 1] * x + (dq_str[i - 1] - 'a' + 1) ) % M;
    }*/
    
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

void print_deque(deque<char>& dq_str) {
    for (int i = 0; i < dq_str.size(); ++i)
        printf("%c", dq_str[i]);
    printf("\n");

    for (int i = 0; i < dq_str.size(); ++i)
        printf("%d", i);

    printf("\n");
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
    // 29 ^ N, if N > 13 => overflow
    x_power[0] = 0; // 29 ^ 0
    lli tmp = 1;
    for (int i = 1; i <= highest_power; ++i) {
        tmp = x * tmp % M;
        x_power[i] = tmp;
    }


    #ifdef DEBUG
    string msg;
    #endif

    #ifdef DEBUG
    string test, sub_test;
    printf("input your string: ");
    cin >> test;
    printf("input your sub_test: ");
    cin >> sub_test;
    
    deque<char> dq_test(test.begin(), test.end());
    my_hasher test_hash = my_hash(dq_test);
    print_deque(dq_test);
    print(test_hash);
    
    int tmp_op;
    char tmp_c;

    while(true) {
        int i, test_len;
        printf("input i, test_len of your substring of test: ");
        cin >> i >> test_len;
        string tmp = test.substr(i, test_len);

        printf("i = %d, test_len = %d\n", i, test_len);
        printf("your substring: %s\n", tmp.c_str());
        printf("your substring's hash value: %lli\n", hash_value(i + 1, i + 1 + test_len - 1, test_hash));
        printf("sub_test's hash value: %lli\n", hash_Ti(sub_test));

        printf("input your operation(1 c, 2, c), (0, _) to test current string, or (3, _) to quit: ");
        cin >> tmp_op >> tmp_c;
        
        if (tmp_op == 0) {
            ;
        } else if (tmp_op == 1) {
            dq_test.push_front(tmp_c);
            printf("string becomes:\n");
            print_deque(dq_test);
            test_hash = my_hash(dq_test);

        } else if (tmp_op == 2) {
            dq_test.push_back(tmp_c);
            printf("string becomes:\n");
            print_deque(dq_test);
            test_hash = my_hash(dq_test);
        }
        test = string(dq_test.begin(), dq_test.end());

        if (tmp_op == 3)
            break;
         
    }
    if (tmp_op == 3)
        return 0;
    #endif

    char S[BUFFSIZE]; // S, initial string

    fscanf(stdin, "%s", S);
    
    #ifdef DEBUG
    printf("input: %s, len = %lu\n", S, strlen(S));
    #endif

    //deque<char> init_dq (S, S + sizeof(S)/sizeof(char));
    string init_str = string(S);

    vector< deque<char> > all_string;
    deque<char> dq_str(init_str.begin(), init_str.end());
    deque<int> dq_ascii;
    
    //hash_all(dq_str);
    

    // initialize our hasher
    // my_hasher _hash = my_hash(init_str);
    bool update_flag = false;
    my_hasher _hash = my_hash(dq_str);
    
    #ifdef DEBUG
    printf("initial string: %s\ninitial _hash:\n", S);
    print(_hash);
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
            case 1: update_flag = true;
                    //dq_str.push_front(Ti[0]);
                    update_front(_hash, Ti[0]);

                    //init_str = Ti[0] + init_str;
                    //print(init_str);
                    //hash_front(dict, init_str);
                    break;

            case 2: update_flag = true;
                    //dq_str.push_back(Ti[0]);
                    update_end(_hash, Ti[0]); // no need to reconstruct _hash
                    #ifdef DEBUG
                    printf("current string: ");
                    print_deque(dq_str);
                    printf("current hash: \n");
                    print(_hash);
                    #endif
                    //init_str += Ti[0];
                    
                    
                    //print(init_str);
                    //hash_end(dict, init_str);
                    break;
             
            case 3: string str_Ti = string(Ti);
                   
                    
                    if (update_flag) {
                        update_front(_hash, dq_str); // need to reconstruct _hash
                        update_flag = false;
                        #ifdef DEBUG
                        printf("current string: ");
                        print_deque(dq_str);
                        printf("current hash: \n");
                        print(_hash);
                        #endif 
                    }
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
