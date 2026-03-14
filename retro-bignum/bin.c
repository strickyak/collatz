#include "types.h"
typedef struct bin {
    byte size;
    byte guts[MAX_OCTETS];
} *Bin;

void Small(Bin z, uint a) {
    //printf(" [small %d.] ", a);
    assert(a < 256);
    z->size = (a > 0);
    z->guts[0] = (byte)a;
}

bool EqSmall(Bin z, uint a) {
    if (z->size == 0) return (a==0);
#if BUGGGGG
    for (byte i = 0; i < z->size; i++) {
        if (z->guts[i] != (i == 0 ? a : 0)) return false;
    }
#else
    if (z->guts[0] != 1) return false;
    for (byte i = 1; i < z->size; i++) {
        if (z->guts[i] != 0) return false;
    }
#endif
    return true;
}

bool IsEven(Bin a) {
    //printf(" [even? %d] ", (a->size == 0));
    if (a->size == 0) return true;
    return (a->guts[0] & 1) == 0;
}

void Dup(Bin z, Bin a) {
    //printf(" [d] ");
    byte sz = a->size;
    z->size = sz;
    for (byte i = 0; i < sz; i++) {
        z->guts[i] = a->guts[i];
    }
}

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define GET(BIN,I) ((I)<(BIN)->size ? (BIN)->guts[I] : 0u)
#define CHECK(BIN) assert(BIN->size <= MAX_OCTETS)

void Add(Bin z, Bin a, Bin b) {
    //printf(" [a] ");
    byte max = MAX(a->size,b->size);
    byte carry = 0;
    for (byte i = 0; i < max; i++) {
        uint t = GET(a,i) + GET(b,i) + carry;
        carry = (t>255);
        z->guts[i] = (byte)t;
    }
    z->size = max;
    if (carry) {
        z->guts[max] = 1;
        z->size++;
    }
    CHECK(z);
}

int Cmp(Bin a, Bin b) {
    //printf(" [c] ");
    byte max = MAX(a->size,b->size);
    if (max==0) return 0;

    byte i = max-1;
    while(1) {
        if (GET(a,i) < GET(b,i)) return -1;
        if (GET(a,i) > GET(b,i)) return +1;

        if (i==0) break;
        i--;
    }
    return 0;
}

void Halve(Bin z, Bin a) {
    //printf(" [h] ");
    z->size = a->size;
    if (a->size==0) return;

    byte i = a->size-1; 
    byte carry = 0;
    while(1) {
        z->guts[i] = a->guts[i] >> 1;
        if (carry) z->guts[i] |= 0x80u;
        carry = 0x01u & a->guts[i];

        if (i==0) break;
        i--;
    }
    if (z->guts[z->size-1]==0) z->size--;
}

void Print(Bin a) {
    printf("$");
    if (!a->size) {
        printf("0 ");
        return;
    }
    byte i = a->size-1; 
    while(1) {
        printf("%02x", a->guts[i]);

        if (i==0) break;
        i--;
    }
    printf(" ");
}
