#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <stdlib.h>
#include <queue>
#include <numeric>
#include <functional>

#define FOUND 1
#define NOT_FOUND 2

using namespace std;

struct set_hasher
{
  std::size_t operator()(const multiset<int>& ms) const
  {
      int ret = (0 << 1);
      for (int i : ms) {
        ret ^= (i << 1);
      }
      return ret;
  }
};

void print(const multiset<int>& s) {
    printf("{");
    for (int i : s) {
        printf("%d, ", i);
    }
    printf("}");
    //printf("\n");
}

void print( unordered_map< multiset<int>, int >& my_unordered_map ) {
    //for (auto& x : my_unordered_map) {
    printf("unordered_map has: ");
    for (unordered_map< multiset<int>, int>::iterator it = my_unordered_map.begin(); it != my_unordered_map.end(); ++it) {
        printf("unordered_map[");
        print(it->first);
        printf("] = %d; ", it->second);
        //printf("%d\n", it->second);
    }
    printf("\n");
}

int visit(multiset<int>& state, int len, int N, int M, int K, multiset<int>& now, unordered_map<multiset<int>, int>& dis, queue< multiset<int> >& q) {

    //printf("K = %d, N + M - sum(now) = %d + %d - %d = %d\n", K, N, M, accumulate(now.begin(), now.end(), 0),
    //                                        N + M - accumulate(now.begin(), now.end(), 0));

    if ( (N + M - accumulate(now.begin(), now.end(), 0)) == K ) {
        printf("%d\n", len + 1);
        return FOUND;
    }
    
    if (dis.insert( pair<multiset<int>, int>(state, len + 1) ).second) {
        q.push(state);
    }

    return NOT_FOUND;
}

int insert_visit(multiset<int>& state, int num, int len, int N, int M, int K, multiset<int>& now, unordered_map<multiset<int>, int>& dis, queue< multiset<int> >& q) {

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
    //printf("%d\n", T);

    for (int t = 0; t < T; ++t) {
        int N, M, K;
        scanf("%d %d %d", &N, &M, &K);
        //printf("%d %d %d\n", N, M, K);
        
        unordered_map< multiset<int>, int, set_hasher> dis;
        queue< multiset<int> > q;
        
        multiset<int> tmp;
        tmp.insert(N);

        dis[tmp] = -1; // dis for initial status = 0

        q.push( tmp );
        //print(q.front());

        int cnt = 0;

        bool has_found = false;
        int res;
        while(1) {
            multiset<int> now = q.front(); 
            multiset<int> next = now;
            q.pop();

            int sum = accumulate(now.begin(), now.end(), 0);
            int hold = N + M - sum;
            int len = dis[now];
            
            if (hold > 0) {
                if ( (res = insert_visit(next, hold, len, N, M, K, now, dis, q) ) == FOUND ) {
                    break; 
                }
                if ( (res = insert_visit(next, 1, len, N, M, K, now, dis, q)) == FOUND ) {
                    break;
                }
            } 

            multiset<int>::iterator it;

            for (int i : now) {

                if ((it = next.find(i)) != next.end() ) {
                    next.erase(it);
                

                    if (hold > 0) {
                        //int res = insert_visit(next, i + 1, len, N, M, K, now, dis, q);
                        if ( (res = insert_visit(next, i + 1, len, N, M, K, now, dis, q) ) == FOUND) {
                            has_found = true;
                            break;
                        }
                        if ( (res = insert_visit(next, i + hold, len, N, M, K, now, dis, q)) == FOUND) {
                            has_found = true;
                            break;
                        }
                    } else {
                        
                        if ( (res = visit(next, len, N, M, K, now, dis, q)) == FOUND) {
                            has_found = true;
                            break;
                        }    
                        if (i > 1) {
                            if ( (res = insert_visit(next, i / 2, len, N, M, K, now, dis, q)) == FOUND ) {
                                has_found = true;
                                break;
                            }
                        }

                    }
                    next.insert(i);
                }
            }
            if (has_found) {
                break;
            }
        
        }

    }

    return 0;
}
