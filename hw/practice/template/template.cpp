#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>


#include <string>

#include <stdio.h> // fopen

#include <algorithm> // find

using namespace std;

long long inf = numeric_limits<long long>::max()


template <class T>
void print(vector<T>& vec) {
    int size = vec.size();
    for (int i = 0; i < size; ++i)
        cout << vec[i] << " ";
    cout << "\n";
}

void print_line(string& message) {
    printf("----------%s----------\n", message.c_str());
}

int main(int argc, char *argv[]) {
   
    string msg;
    // open file
    msg = "using fopen";
    print_line(msg);
    FILE *fp = fopen(argv[1], "r");
    
    int n, m;
    fscanf(fp, "%d %d", &n, &m);
    printf("n, m = %d, %d\n", n, m);
    
    vector<int> wages;
    int wi;
    for (int i = 0; i < n; ++i) {
        fscanf(fp, "%d", &wi);
        wages.push_back(wi);
    }

    int tj, vj;
    
    vector<int> action;
    vector<int> new_wage;

    for (int i = 0; i < m; ++i) {
        fscanf(fp, "%d %d", &tj, &vj);
        action.push_back(tj);
        new_wage.push_back(vj);
    }


    // using auto
    for ( auto wi : wages )
        cout << wi << " ";
    cout << "\n";

    // find element in the wages
    //printf("----------using ``find''----------\n");
    msg = "using ``find''";
    print_line(msg);
    auto got = find(wages.begin(), wages.end(), 30000); // or vector<int>::iterator got = find(wages.begin(), wages.end(), 30000);
    if (got != wages.end())
        printf("Found %d\n", *got);
    got = find(wages.begin(), wages.end(), 1126);
    if (got == wages.end())
        printf("Can't find %d\n", 1126);


    // queue and stack
    msg = "stack and queue";
    print_line(msg);
    
    queue<int> q;
    stack<int> s;
    for (int i = 0; i < 10; ++i) {
        printf("pushing %d to queue and stack.\n", i);
        q.push(i);
        s.push(i);
    }
    
    printf("size of q: %lu\n", q.size());
    printf("content of q: ");
    while (!q.empty()) {
        int from_q = q.front();
        q.pop();
        cout << from_q << " ";
    }
    cout << "\n";

    printf("size of s: %lu\n", s.size());
    printf("content of s: ");
    while (!s.empty()) {
        int from_s = s.top();
        s.pop();
        cout << from_s << " ";
    }
    cout << "\n";

    msg = "unordered_map";
    print_line(msg);
    unordered_map<int, string> map = { {1, "CMU"}, {2, "UCBerkeley"}, {3, "Stanford"}, {4, "MIT"}, {5, "UIUC"} };

    printf("access ele: m[1]: %s\n", map[1].c_str());
    printf("find 1 in map:\n");
    unordered_map<int, string>::iterator it = map.find(1); // or: auto it = m.find(1);
    if (it != map.end()) {
        printf("key = %d, found value: %s\n", it->first, it->second.c_str());
    }
    unordered_map<int, string>::iterator it2 = map.find(6);
    if (it2 == map.end()) {
        printf("key = %d, can't find key.\n", 6);
    }
    map.insert( {6, "Columbia"} );
    it2 = map.find(6);
    if (it2 != map.end()) {
        printf("Now we can find key. key = %d, value = %s\n", it2->first, it2->second.c_str());
    }
    cout << "size of map: " << map.size() << "\n"; 

    msg = "unordered_set";
    print_line(msg);
    unordered_set<int> a = {1, 2, 3, 4, 5};   
    printf("size of unordered_set: %lu\n", a.size());
    unordered_set<int>::iterator it3 = a.find(3);
    if (it3 != a.end()) {
        printf("find %d in unordered_set\n", *it3);
    }

    it3 = a.find(6);
    if (it3 == a.end()) {
        printf("Can't find %d in unordered_set\n", 6);
    }
    return 0;
}


