#include <iostream>

int main(int argc, char *argv[]) {
    
    int* a = new int;
    int c = 5;
    a = &c;

    printf("%d\n", *a);


    return 0;
}
