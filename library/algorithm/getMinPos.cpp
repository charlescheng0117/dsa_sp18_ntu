#include <vector>
#include <iostream>

using namespace std;

int getMinPos(vector<int>& arr) {
    int minPos = 0;
    int len = arr.size();
    for (int i = 0; i < len; ++i) {
        if (arr[i] < arr[minPos]) {
            minPos = i;
        }
    }
    return minPos;
}


int main(int argc, char *argv[]) {
    
    vector<int> arr = {5, 3, 8, 9, 6, 7, 2, 30, 3};
    
    int minPos = getMinPos(arr);
    
    int len = arr.size();
    for (int i = 0; i < len; ++i)
        cout << arr[i] << " ";
    cout << "\n";

    cout << "minPos = " << minPos << "\n";

    return 0;
}

