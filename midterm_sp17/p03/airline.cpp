#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char *argv[]) {
    
    int n, m;
    fscanf(stdin, "%d %d", &n, &m);

    vector<int> salaries(n);
    
    int wi;
    for (int i = 0; i < n; ++i) {
        fscanf(stdin, "%d", &wi);
        salaries[i] = wi;
    }

    int tj, vj;

    int ret = 0;
    for (int i = 0; i < m; ++i) {
        fscanf(stdin, "%d %d", &tj, &vj);
        
        if (tj == 1) {
            salaries.push_back(vj);
            ret = accumulate(salaries.begin(), salaries.end(), ret);

        } else { // tj = 2
            sort(salaries.begin(), salaries.end()); 
            auto upper = upper_bound(salaries.begin(), salaries.end(), vj); 
            salaries.erase(upper, salaries.end());
            ret = accumulate(salaries.begin(), salaries.end(), ret);
        }

    
    }
    printf("%d\n", ret);

    return 0;
}
