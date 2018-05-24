#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long int lli;


template <typename T>
void print(vector<T> v) {
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << "\n";
}

int main(int argc, char *argv[]) {
    
    int n; // days
    fscanf(stdin, "%d", &n);

    vector<lli> fries(n); // # of fries in each of n days;

    for (int i = 0; i < n; ++i) {
        fscanf(stdin, "%lli", &fries[i]);
    } 
    
    printf("%d\n", n);
    print(fries);
    
    printf("%d\n", '0');

    return 0;
}
