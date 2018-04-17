#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

int getMinPos(vector<int>& arr, int start) {
    int minPos = start;
    int len = arr.size();
    for (int i = start; i < len; ++i) {
        if (arr[i] < arr[minPos]) {
            minPos = i;
        }
    }
    return minPos;
}

// inplace sort
void selection_sort(vector<int>& arr) {
    int len = arr.size();
    int minPos = 0;
    int tmp;
    for (int i = 0; i < len; ++i) {
        minPos = getMinPos(arr, i);
        //cout << "minPos = " << minPos << "\n"; 
        tmp = arr[i];
        arr[i] = arr[minPos];
        arr[minPos] = tmp;
    }
    return;
}


int main(int argc, char *argv[]){
    
    vector<int> arr;

    for (int i = 1; i < 11; ++i) {
        arr.push_back(i);
    }

    random_shuffle(arr.begin(), arr.end());

    cout << "arr is:\n";
    int len = arr.size();
    for (int i = 0; i < len; ++i)
        cout << arr[i] << " ";
    cout << "\n";

    cout << "after sorting:\n";
    selection_sort(arr);
    
    for (int i = 0; i < len; ++i)
        cout << arr[i] << " ";
    cout << "\n";

    return 0;
}
