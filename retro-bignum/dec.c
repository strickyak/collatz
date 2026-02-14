#include "types.h"
typedef struct dec {
    uint size;
    byte guts[3 * MAX_OCTETS];
} *Dec;

void SmallDec(Dec z, uint a) {
    assert(a < 10);
    z->size = (a > 0);
    z->guts[0] = (byte)a;
}

void AddDec(Dec z, Dec a, Dec b) {
    byte max = MAX(a->size,b->size);
    byte carry = 0;
    for (byte i = 0; i < max; i++) {
        byte t = GET(a,i) + GET(b,i) + carry;
        carry = (t>9);
        z->guts[i] = (t > 9) ? t-10 : t;
    }
    z->size = max;
    if (carry) {
        z->guts[max] = 1;
        z->size++;
    }
    CHECK(z);
}

void PrintDec(Dec a) {
    // printf("[%d# %d %d %d]", a->size, a->guts[2], a->guts[1], a->guts[0]);
    if (!a->size) {
        printf("0 ");
        return;
    }
    byte i = a->size-1; 
    while(1) {
        putchar( '0' + a->guts[i]);

        if (i==0) break;
        i--;
    }
    putchar(' ');
}

struct dec Power2;
void BinToDec(Dec z, Bin a) {
    SmallDec(&Power2, 1);
    SmallDec(z, 0);

    for (byte i = 0; i < a->size; i++) {
        for (byte bit = 1; bit; bit<<=1) {
            if (a->guts[i] & bit) {
                AddDec(z, z, &Power2);
            }
            AddDec(&Power2, &Power2, &Power2);
        }
    }
}
