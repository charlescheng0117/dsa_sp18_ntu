#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <utility> // pair
#include <map>
#include <bitset> // count 1
#include <unordered_set> // record single pig
#include <climits>


using namespace std;
typedef long long int lli;

#define epsilon 10e-7
#define PIG 1
#define NOPIG 0
#define M 1000000007
//#define DEBUG 1


struct point {
    long long int x, y;
    point() {}
    point(long long int coor_x, long long int coor_y) {
        x = coor_x;
        y = coor_y;
    }
};

//int ith_pig(int num_pigs, int i) {
int ith_pig(int i) {
    // return the integer representing the ith pig
    // e.g: num_pigs = 5, i = 2
    // then ith_pig is:
    //      4 3 2 1 0
    //      0 0 1 0 0
    return (1 << i);
}

//int is_pig(int num_pigs, int pig_set, int i) {
int is_pig(int pig_set, int i) {
    return ( (pig_set >> i) & 1 ) == PIG;
    //return ((pig_set >> (num_pigs - i - 1)) & 1) == PIG;
}

void show_pigs(int num_pigs, int pig_set) {
    for (int i = num_pigs - 1; i >= 0; --i) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = num_pigs - 1; i >= 0; --i) {
        if (is_pig(pig_set, i))
           printf("%d ", PIG);
        else
           printf("%d ", NOPIG);
    }
    printf("\n");
}

bool is_valid_parabola(vector<point>& pigs, int i, int j) {
    long long int x0 = pigs[i].x, y0 = pigs[i].y;
    long long int x1 = pigs[j].x, y1 = pigs[j].y;
    
    if (x0 == x1) {
        return false;
    }

    long long int num1 = ( x1 * y0 - x0 * y1 );
    long long int num2 = ( x0 - x1 );
    return ( (num1 < 0) && (num2 > 0) ) || ( (num1 > 0) && (num2 < 0) );

}

bool is_on_parabola(vector<point>& pigs, int pig_i, int pig_j, int pig_k) {
    long long int x0 = pigs[pig_i].x, y0 = pigs[pig_i].y;
    long long int x1 = pigs[pig_j].x, y1 = pigs[pig_j].y;
    long long int x  = pigs[pig_k].x, y  = pigs[pig_k].y;

    if (x0 == x1) {
        return false;
    }

    long long int lhs = x0 * x1 * (x0 - x1) * y;
    long long int rhs = y0 * x1 * x * (x - x1) - y1 * x0 * x * (x - x0);

    return lhs == rhs;
}

// iterate all pigs, compuate all coef, record all points on that parabola
void compute_all_parabola(vector<point>& pigs, vector< vector<int> >& all_pigs) {
    // if we found multiple pigs on a parabola
    // we substract it from 1111...1111 to form the pig_set_single
    int num_pigs = pigs.size();
    int pig_set;
    for (int i = 0; i < num_pigs; ++i) {
        for (int j = i + 1; j < num_pigs; ++j) {
            if (is_valid_parabola(pigs, i, j)) {
                pig_set = (1 << i) + (1 << j);
                point pig_i = pigs[i], pig_j = pigs[j];
                
                for (int k = 0; k < num_pigs; ++k) {
                    if (k == i || k == j) {
                        continue;
                    } else {
                        if (is_on_parabola(pigs, i, j, k) ) {
                            pig_set += (1 << k);
                        }
                    }
                }
                all_pigs[i][j] = pig_set;
            } else {
                // or pig_set == 0
                pig_set = (1 << i);
                all_pigs[i][j] = (1 << i);
                all_pigs[j][i] = (1 << j);
            }
            #ifdef DEBUG
            printf("\n%d, %d, birds: %d\n", i, j, pig_set);
            printf("current point: %d: [%d, %d], %d: [%d, %d]\n", i, pigs[i].x, pigs[i].y, j, pigs[j].x, pigs[j].y);
            show_pigs(num_pigs, pig_set);
            #endif    
        }
    }
}

void compute_dp(vector<point>& pigs, vector<int>& dp, vector< vector<int> >& all_pigs) {
    
    // dp[S] = min (dp[S / A]) + 1, for all A where A = pigs on a certain parabola
    // S = pig_set = 11111...1111, initially
    // iterate through the parabola
    int min_total = 1000000007;
    
    int S = dp.size() - 1;
    int n = pigs.size();
    dp[0] = 0;
    dp[1] = 1;
    for (int s = 2; s <= S; ++s) {
        dp[s] = min_total;
        if ( (s & (s - 1) ) == 0 ) {
            dp[s] = 1;
        } else {
            for (int i = 0; i < n; ++i) {
                int pig_i = (1 << i);
                // pig_i \in S
                // s: 1 1 1 0 1
                // i: 0 0 0 1 0
                // &  ---------
                //    0 0 0 0 0
                if (pig_i & s) { 
                    for (int j = i + 1; j < n; ++j) {
                         int pig_set = all_pigs[i][j];
                         int pig_left = s & (~ pig_set );
                         //printf("i = %d, j = %d, s = %d, pig_set = %d, pig_left = %d, dp[s] = %d, dp[pig_left] =  %d\n", i, j, s, pig_set, pig_left, dp[s], dp[pig_left]);
                         dp[s] = min(dp[s], dp[pig_left] + 1);
                    }
                    break; 
               }
           }
        }
            
        /*
        for (int i = 0; i < n; ++i) {
            int pig_i = (1 << i);
            // pig_i \in S
            // s: 1 1 1 0 1
            // i: 0 0 0 1 0
            // &  ---------
            //    0 0 0 0 0
            if (pig_i & s) { 
                for (int j = i + 1; j < n; ++j) {
                     int pig_set = all_pigs[i][j];
                     int pig_left = s & (~ pig_set );
                     printf("i = %d, j = %d, s = %d, pig_set = %d, pig_left = %d, dp[s] = %d, dp[pig_left] =  %d\n", i, j, s, pig_set, pig_left, dp[s], dp[pig_left]);
                     dp[s] = min(dp[s], dp[pig_left] + 1);
                }
               //break; 
           }
        }*/
    }
    
    return;
}

int main(int argc, char *argv[]) {
    
    int T; // number of test cases
    fscanf(stdin, "%d", &T);

    for (int i = 0; i < T; ++i) {
        int n; // number of pigs 
        fscanf(stdin, "%d", &n);
       
        vector<point> pigs(n); // vector of the location of the pigs
        long long int x, y;
        for (int j = 0; j < n; ++j) {
            fscanf(stdin, "%lld %lld", &x, &y);
            pigs[j] = point(x, y);
        }
        // set pig_set = 111111111, n 1's
        // so we want 000000111111, n 1's
        int pig_set = (1 << n) - 1;
        #ifdef DEBUG
        print(pigs); 
        printf("showing initial %d pigs: \n", n);
        show_pigs(n, pig_set);
        #endif

        vector< vector<int> > all_pigs(n, vector<int>(n)); // all_pigs[i][j] = all pigs on the parabola formed by pig_i, pig_j
        vector<int> dp(pig_set + 1); // dp[0], dp[1], ..., dp[2^n - 1]
            
        compute_all_parabola(pigs, all_pigs);
        compute_dp(pigs, dp, all_pigs);
        
        // dp to solve the total shots needed for non-single pigs
        printf("%d\n", dp[pig_set]);
    }
    return 0;
}
