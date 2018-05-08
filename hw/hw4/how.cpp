#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <string>

using namespace std;

//#define DEBUG 1
//#define BASIC_STR 1

#define BUFFSIZE 100000

template <typename T>
void print_deque(deque<T> dq) {
    for (auto ele : dq) {
        cout << ele << " ";
    }
    cout << "\n";
}

void print_line(string& msg) {
    printf("----------%s----------\n", msg.c_str());
}

void print_end() {
    printf("----------------------------------------\n");
}

void hash_front(unordered_map<string, int>& dict, string& init_str) {
    int str_len = init_str.length();
    int pos = 0;
    #ifdef DEBUG
    printf("init_str: %s\n", init_str.c_str());
    printf("hash all front string.\n");
    #endif

    for (int len = 1; len <= str_len; ++len) {
        string sub = init_str.substr(pos, len);
        #ifdef DEBUG
        printf("sub = %s\n", sub.c_str());
        #endif
        ++dict[init_str.substr(pos, len)];
    }

    return;
}

void hash_end(unordered_map<string, int>& dict, string& init_str) {
    
    int str_len = init_str.length();
    #ifdef DEBUG
    printf("init_str: %s\n", init_str.c_str());
    printf("hash all end string.\n");
    #endif 
    for (int pos = 0; pos < str_len; ++pos) {
        string sub = init_str.substr(pos);
        #ifdef DEBUG
        printf("sub = %s\n", sub.c_str());
        #endif
        ++dict[init_str.substr(pos)];
    }

    return;
}

void print(string& s) {
    printf("%s\n", s.c_str());
}

int main(int argc, char *argv[])
{
    #ifdef DEBUG
    string msg;
    #endif

    char S[BUFFSIZE]; // S, initial string

    fscanf(stdin, "%s", S);
    
    #ifdef DEBUG
    printf("input: %s, len = %lu\n", S, strlen(S));
    #endif

    /*
    deque<char> init_str(len);
    for (int i = 0; i < len; ++i) {
        init_str[i] = S[i];
    }*/
    string init_str = string(S);
    
    #ifdef BASIC_STR
    printf("string = %s\n", init_str.c_str());
    printf("add CMU at the end = %s\n", init_str.append("CMU").c_str());
    printf("add UCBerkeley at the front = %s\n", init_str.insert(0, "UCBerkeley").c_str());
    #endif

    #ifdef USE_DEQUE
    msg = "deque's content";
    print_line(msg);
    print_deque(init_str);
    print_end();
    #endif

    int Q; // Q questions
    fscanf(stdin, "%d", &Q);

    unordered_map<string, int> dict;
     
    // hash all strings into dict
    int str_len = init_str.length();
    for (int len = 1; len <= str_len; ++len) {
        for (int pos = 0; pos <= str_len - len; ++pos) {
            string sub = init_str.substr(pos, len);
            #ifdef DEBUG
            printf("sub = %s\n", sub.c_str());
            #endif
            ++dict[init_str.substr(pos, len)];
        }
    }
   
    #ifdef DEBUG 
    //for( auto pair : dict ) {
    //    printf("%s: %d\n", pair.first.c_str(), pair.second);
    //}
    #endif

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
                    hash_front(dict, init_str);
                    break;

            case 2: //init_str.push_back(Ti[0]);
                    init_str += Ti[0];
                    //print(init_str);
                    hash_end(dict, init_str);
                    break;
             
            case 3: printf("%d\n", dict[string(Ti)]);
                            
                    break;             
        
        
        }

    } 

    return 0;
}
