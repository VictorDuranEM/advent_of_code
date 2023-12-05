#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    unsigned long total = 0;
    for (int i = 1; i <= 15; i++) {
        total += pow(26, i);
    }
    printf("%lu\n", total);
}