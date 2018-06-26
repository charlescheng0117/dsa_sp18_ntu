#include <queue>
#include <vector>
#include <iostream>
#include <functional> // greater


using namespace std;


int main(int argc, char *argv[])
{
    int N, M;

    scanf("%d %d", &N, &M);

    priority_queue<int, vector<int>, greater<int> > pq;
    for (int i = 0; i < M; ++i)
        pq.push(0);

    int ni, tmp = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &ni);
        tmp = pq.top() + ni;
        pq.pop();
        pq.push(tmp);
    }

    for (int i = 0; i < M - 1; ++i)
        pq.pop();

    printf("%d\n", pq.top());

    return 0;
}
