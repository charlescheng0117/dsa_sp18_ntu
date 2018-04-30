#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    
    stack<int> s;
    queue<int> q;

    int N; // operation
    int t, x;

    int s_front, q_front;

    scanf("%d", &N);

    bool is_stack = true; 
    bool is_queue = true;

    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &t, &x);
        if (t == 1) {
            printf("x = %d\n", x);

            s.push(x);
            q.push(x);
        } else { // t = 2
            s_front = s.top();
            q_front = q.front();
            
            printf("x = %d\n", x);
            printf("s_front: %d, q_front: %d\n", s_front, q_front);

            s.pop();
            q.pop();

            if (s_front != x)
                is_stack = false;

            if (q_front != x)
                is_queue = false;

            if (!is_stack && !is_queue) {
                printf("neither\n");
                return 0;
            }
                

        }
        
    }

    if (is_stack && is_queue) {
        printf("both\n");
    } else if (is_stack && (!is_queue) ) {
        printf("stack\n");
    } else { //( (!is_stack) && is_queue) {
        printf("queue\n");
    }
    

    return 0;
}
