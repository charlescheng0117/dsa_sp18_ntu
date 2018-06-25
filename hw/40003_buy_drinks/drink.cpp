#include <vector>
#include <iostream>
#include <queue>          // std::priority_queue
#include <functional>     // std::greater

using namespace std;

int main(int argc, char *argv[])
{
    
    int N, M;
    scanf("%d %d", &N, &M);

    vector<int> order(N);
    
    priority_queue<int, vector<int>, greater<int> > pq; // min element is on top

    for (int i = 0; i < N; ++i) {
        scanf("%d", &(order[i]));
    } 

    for (int i = 0; i < M; ++i) {
        pq.push(0); 
    }

    int tmp;
    for (int i = 0; i < N; ++i) {
        tmp = pq.top();
        pq.pop();
        pq.push(tmp + order[i]);
    }

    for (int i = 0; i < M - 1; ++i) {
        pq.pop();
    }
    printf("%d\n", pq.top());

    return 0;
}
