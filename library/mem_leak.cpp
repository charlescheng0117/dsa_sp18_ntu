#include <vector>

int main(int argc, char *argv[]) {

    // correct
    int *data = new int;
    delete data;

    // memery leak
    int *leak = new int;
    // no delete

    return 0;
}
