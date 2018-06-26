#include <stdio.h>

int main(int argc, char** argv) {

    int a_int;
    float a_float;
    char s1[32];
    char s2[32];
    char c0, c1, c2, c3, c4;
    long long int a_longlongint;
    fscanf(stdin, "%d %f", &a_int, &a_float);
    printf("%d %f\n", a_int, a_float);
    fscanf(stdin, "%s %s", s1, s2); // s1 s2: already a pointer
    printf("%s %s", s1, s2);
    
    for (int i = 0; i < 2; ++i) {
       fscanf(stdin, "%c%c%c%c%c", &c0, &c1, &c2, &c3, &c4); 
       printf("%c%c%c%c%c", c0, c1, c2, c3, c4);
    }
    fscanf(stdin, "%c", &c0); // can't read 'y', don't know why
    printf("%c", c0); 

    printf("\n");
    fscanf(stdin, "%lld", &a_longlongint);
    printf("%lld\n", a_longlongint);



}
