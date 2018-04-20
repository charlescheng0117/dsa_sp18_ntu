#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int GLOBAL = 3;

int test_scope() {

    printf("GLOBAL = %d\n", GLOBAL);
    return GLOBAL;
}

int main(int argc, char *argv[]) {
    int a = 3;
    cout << "a = " << a << "\n";

    a = (a << 2);

    cout << "a after shifting 2 bits = " << a << "\n";
    
    vector<int> b;
    b.reserve(20);

    cout << b.capacity() << " " << b.size() << "\n";

    b.push_back(20);

    cout << b.capacity() << " " << b.size() << "\n";

    int c = test_scope();
    cout << "after return, c = " << c << "\n";


    int min_ele = min(1, -1);
    cout << min_ele << "\n";

    return 0;
}
