#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    
    long long int N;
    scanf("%lld", &N);

    vector<long long int> weights(N);

    long long int torque = 0;
    long long int sum = 0;

    for (long long int i = 0; i < N; ++i) {
        scanf("%lld", &(weights[i]));
    }

    for (long long int i = 0; i < N; ++i) {
        sum += weights[i];
        torque += i * weights[i];
    }

    for (long long int x = 0; ; ++x) {
        if ((torque % sum) == 0) {
            printf("%lld %lld\n", x, torque/sum);
            return 0;
        }
        torque += (N - 2 * x - 1) * (weights[x] - weights[N - x - 1]);
    }


    return 0;
}
