#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stdlib.h>
#include <queue>
#include <numeric>

#define FOUND 1
#define NOT_FOUND 2

using namespace std;

int visit(set<int>& state, int len, int N, int M, int K, set<int>& now, map<set<int>, int>& dis, queue< set<int> >& q) {

    printf("K = %d, N + M - sum(now) = %d + %d - %d = %d\n", K, N, M, accumulate(now.begin(), now.end(), 0),
                                            N + M - accumulate(now.begin(), now.end(), 0));

    if ( (N + M - accumulate(now.begin(), now.end(), 0)) == K ) {
        printf("%d\n", len + 1);
        return FOUND;
    }
    
    if (dis.insert( pair<set<int>, int> (state, len + 1) ).second) {
        q.push(state);
    }

    return NOT_FOUND;
}

int insert_visit(set<int>& state, int num, int len, int N, int M, int K, set<int>& now, map<set<int>, int>& dis, queue< set<int> >& q) {

    state.insert(num);
    int result = visit(state, len, N, M, K, now, dis, q);
    if (result == FOUND) {
        return result;
    }
    state.erase(state.find(num));
    return result;
}

int main(int argc, char *argv[]) {
    
    int T;
    
    scanf("%d", &T);
    printf("%d\n", T);

    for (int t = 0; t < T; ++t) {
        int N, M, K;
        scanf("%d %d %d", &N, &M, &K);
        printf("%d %d %d\n", N, M, K);
        
        map< set<int>, int > dis;
        queue< set<int> > q;
        
        set<int> tmp;
        tmp.insert(N);
        dis[tmp] = 0; // dis for initial status = 0
        q.push( tmp );

        int cnt = 0;

        bool has_found = false;
        while(1) {
            set<int> now = q.front(); 
            set<int> next = now;
            q.pop();

            int hold = N + M - accumulate(now.begin(), now.end(), 0);
            //printf("N = %d, M = %d, hold = %d\n", N, M, hold);
            int len = dis[now];
            
            if (hold > 0) {
                int res = insert_visit(next, hold, len, N, M, K, now, dis, q);
                if (res == FOUND) {
                    break;
                }
                res = insert_visit(next, 1, len, N, M, K, now, dis, q);
                if (res == FOUND) {
                    break;
                }
            } 
            
            //printf("here\n");
            printf("%d. now has:\n", cnt);
            cnt += 1;
            for (int i : now) {
                printf("%d ", i);
            }
            printf("\n");

            for (int i : now) {
                next.erase(next.find(i));
                if (hold > 0) {
                    int res = insert_visit(next, i + 1, len, N, M, K, now, dis, q);
                    if (res == FOUND) {
                        has_found = true;

                        break;
                    }
                    res = insert_visit(next, i + hold, len, N, M, K, now, dis, q);
                    if (res == FOUND) {
                        has_found = true;
                        break;
                    }
                } else {
                    int res = visit(next, len, N, M, K, now, dis, q);
                    if (res == FOUND) {
                        has_found = true;
                        break;
                    }
                    if (i > 1) {
                        int res = insert_visit(next, i / 2, len, N, M, K, now, dis, q);
                        if (res == FOUND) {
                            has_found = true;
                            break;
                        }
                    }

                }
                next.insert(i);
            }
            if (has_found) {
                break;
            }
        
        }

    }

    return 0;
}
