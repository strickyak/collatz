/* I want to know if we can check all 32-bit unsigned
 * using 64-bit unsigneds.  This assert-fails if
 * intermediate numbers do not fit into uint64.
 */
#include <assert.h>
#include <stdio.h>

#define MAX 0xFFFFFFFFu

typedef unsigned long uint;

uint maximum;
uint maximum_for_a;

void Check(uint a) {
    uint x = a;
    //printf("entry x=%lu\n", x);
    while (x > 1 && x>=a) {
        if (maximum < x) maximum = x, maximum_for_a = a;

        uint y;
        if (x&1) {
            y = x * 3 + 1;
            if (y <= x) {
                fflush(stdout);
                fflush(stderr);
                fprintf(stderr, "\nBAD: y=%lu x=%lu\n", y, x);
                assert(0);
            }
        } else {
            y = x >> 1;
        }
        x = y;
        //printf("now x=%lu\n", x);
    }
}

int main() {
    for (uint i = 2; i <= MAX; i++) {
        if ((i & 0xFFFFF) == 0) printf("%lu ", i), fflush(stdout);
        if ((i & 0xFFFFFF) == 0) printf("\n");
        Check(i);
    }
    printf("\nmaximum: %lu for: %lu\n", maximum, maximum_for_a);
}
