#include "types.h"
#include "bin.c"
#include "dec.c"

struct bin a, b, c, d, e, f, g, h;

struct dec z;

int main() {
    Small(&a, 250);
    Small(&b, 1);
    Print(&a);
    Print(&b);
    Add(&c, &a, &b);
    Print(&c);
    Halve(&d, &c);
    Print(&d);

    BinToDec(&z, &d);
    PrintDec(&z);

    Add(&c, &a, &a);
    Print(&c);
    Halve(&d, &c);
    Print(&d);

    BinToDec(&z, &d);
    PrintDec(&z);

    printf("\n");
    return 0;
}
