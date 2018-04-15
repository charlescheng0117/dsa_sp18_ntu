#include <iostream>
#include <vector>

using namespace std;


template <class type>
class myVec {
	int size;
    vector<type> *data;
	
public:
    myVec() {
        size = 0;
        data = new vector<type>;
    }

    myVec(int s) {
        size = s;
        data = new vector<type>(s);
    }
    ~myVec() {
        delete data;
    }

    void add_data(type d) {
        data->push_back(d);
        size += 1;
    }

	int getSize() {
        return size;
    };
    void setSize(int s) {
        size = s;
        delete data;
        data = new vector<type>(s);
    };
    
    void print() {
        for (int i = 0; i < size; ++i) {
           cout << (*data)[i] << " "; 
        }
        cout << "\n";
    }
};


int main(int argc, char const *argv[])
{
	/* code */
	myVec<int> a;
	a.setSize(5);
	cout << a.getSize() << "\n";
    
    a.add_data(2);
    a.add_data(3);

    a.print();
    a.print();


	return 0;
}
