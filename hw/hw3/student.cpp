#include <iostream>
#include <string>

using namespace std;

class student {
    public:
        student (int n=3) {
            count = n;
            score = new int[count];
        }
        ~student() {
            delete [] score;
        }
        void print() {
            cout << name << " ";
            for (int i = 0; i < count; ++i)
                cout << score[i] << " ";
            cout << "\n";
        }
        int *score, count;
        string name;
};

int main() {
    student a(3);
    a.name = "John"; a.score[0] = 70; a.score[1] = 80;
    student b = a;
    b.name = "Mary"; b.score[2] = 90;
    a.print();
    b.print();

}
