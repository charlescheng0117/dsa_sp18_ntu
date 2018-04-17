#include <vector>

using namespace std;

int ROW = 3;
int COL = 5;

int rowSum(int array[][COL]) {
    int sum = 0;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            sum += array[i][j];
        }
    }
    return sum;
}

int colSum(int array[][COL]) {
    int sum = 0;
    for (int i = 0; i < COL; ++j) {
        for (int j = 0; j < ROW; ++i) {
            sum += array[i][j];
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    
    return 0;
}
