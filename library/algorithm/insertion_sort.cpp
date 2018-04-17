#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// inplace sort implementation
void insertion_sort(vector<int>& arr) {
    int len = arr.size();
    int cur, j;
    for (int i = 1; i < len; ++i) {
        cur = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > cur) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = cur;
    }

}

int main(int argc, char *argv[]) {
    int len = 10;
    vector<int> arr(10);

    for (int i = 1; i < 11; ++i) {
        arr[i] = i;
    }

    random_shuffle(arr.begin(), arr.end());
    cout << "Before sorting.\n";
    for (int i = 0; i < len; ++i)
        cout << arr[i] << " ";
    cout << "\n";

    insertion_sort(arr);

    cout << "After sorting.\n";
    for (int i = 0; i < len; ++i)
        cout << arr[i] << " ";
    cout << "\n";

    return 0;
}


