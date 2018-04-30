#include <iostream>
#include <vector>

using namespace std;

#define SIZE 30

// min heap
class Heap {
public:    
    //int min_ele;
    int size;
    vector<int> data;

    Heap () {
        data = vector<int>(SIZE);

    }

    Heap (int root) {
        //min_ele = root;
        size = 1;
        data = vector<int>(SIZE);
        data[1] = root;
    }

    int get_min() {
        return data[1];
    }

    int get_size() {
        return size;
    }

    bool empty() {
        return (size == 0);
    }
    
    int parent(int idx) {
        return idx / 2;
    }

    int left_child(int idx) {
        return 2 * idx;
    }

    int right_child(int idx) {
        return 2 * idx + 1;
    }

    void swim(int idx) {
        int tmp = data[idx];
        data[idx] = data[parent(idx)];
        data[parent(idx)] = tmp;
    }

    char sink(int idx) {
        int cur_val = data[idx];
        int left_val = data[left_child(idx)];
        int right_val = data[right_child(idx)];
        
        char direction; // sink left or right

        if (left_val < cur_val && left_val < right_val) {
            data[idx] = left_val;
            data[left_child(idx)] = cur_val;
            direction = 'l';
        } else if (right_val < cur_val && right_val < left_val) {
            data[idx] = right_val;
            data[right_child(idx)] = cur_val;
            direction = 'r';
        }
        return direction;

    }

    void insert (int e) {
        data[size + 1] = e;
        int cur_idx = size + 1;
        while (data[cur_idx] < data[parent(cur_idx)]) {
            swim(cur_idx);
            cur_idx = parent(cur_idx);
        }
        ++size;

        return;
    }
    
    int remove_min() {
        int ret = data[1];
        data[1] = data[size];
        data[size] = 10e7; // blank
    
        int cur_idx = 1;
        char direction;


        
        while ( (data[cur_idx] > data[left_child(cur_idx)] && left_child(cur_idx) <= size) || 
                (data[cur_idx] > data[right_child(cur_idx)] && right_child(cur_idx) <= size) ) {
            
                direction = sink(cur_idx);
                if (direction == 'l') {
                    cur_idx = left_child(cur_idx);
                } else {
                    cur_idx = right_child(cur_idx);
                }
            }

        --size;
        return ret;
    }
    

    void print() {
        for (int i = 1; i <= size; ++i)
            printf("%d ", data[i]);
        printf("\n");
    }


};


int main(int argc, char *argv[]) {
    Heap h = Heap(3);
    h.print();
    
    // testing insert
    h.insert(2);
    h.insert(10);
    h.insert(1);
    h.insert(100);
    h.insert(5); 
    h.print();
    
    printf("min_ele = %d, size = %d\n", h.get_min(), h.get_size());

    // testing remove_min
    int tmp;
    tmp = h.remove_min();
    printf("ele removed = %d\n", tmp);
    tmp = h.remove_min();
    printf("ele removed = %d\n", tmp);
    h.print();
    tmp = h.remove_min();
    printf("ele removed = %d\n", tmp);
    h.print();
    tmp = h.remove_min();
    printf("ele removed = %d\n", tmp);

    h.insert(30);
    h.insert(50);
    printf("min_ele = %d, size = %d\n", h.get_min(), h.get_size());

    h.print();
    tmp = h.remove_min();
    printf("ele removed = %d\n", tmp);
    h.print();
    tmp = h.remove_min();
    printf("ele removed = %d\n", tmp);
    h.print();
    
    


    return 0;
}
