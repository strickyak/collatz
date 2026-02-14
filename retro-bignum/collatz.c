#include "types.h"
#include "bin.c"
#include "dec.c"

struct bin a, b, c, d, e, f, g, h;

void PrintBinAsDec(Bin a) {
    static struct dec dec;
    BinToDec(&dec, a);
    PrintDec(&dec);
}

struct bin q; // the question
struct bin biggest;
uint max_steps;

void Traverse(Bin q, Bin one) {
    static struct bin a;
    static struct bin temp;
    a = *q; // copy question to starting point a

    if (Cmp(&a, &biggest) > 0) {
            biggest = a;
            printf("biggest  ");
    }

    uint steps = 0;
    while (! EqSmall(&a, 1)) {
        steps++;

        if (IsEven(&a)) {
            Halve(&temp, &a); // half
            a = temp;
        } else {
            Add(&temp, &a, &a);  // double
            Add(&a, &a, &temp); // triple
            Add(&a, &a, one); // triple+1
        }
        PrintBinAsDec(&a);

        if (Cmp(&a, &biggest) > 0) {
            biggest = a;
            printf(" biggest  ");
        }

    }
    if (steps > max_steps) {
        max_steps = steps;
        printf(" OKAY (MAX steps=%u)\n", steps);
    } else {
        printf(" OKAY (steps=%u)\n", steps);
    }
}

int main(int argc, char *argv[]) {
    static struct bin one;
    Small(&one, 1);

    if (argc > 1) {
        q.size = argc-1;
        for (byte i = 0; i < q.size; i++) {
            q.guts[i] = atoi(argv[i+1]);
        }
    } else {
        Small(&q, 1);
    }
    while(1) {
        printf("Questioning "); PrintBinAsDec(&q); printf(":  ");

        Traverse(&q, &one);
        Add(&q, &q, &one);
    }
}
