#ifndef TYPES_H__
#define TYPES_H__

typedef unsigned char bool;
typedef unsigned char byte;
typedef unsigned int uint;

typedef unsigned char gbool;
typedef unsigned char gbyte;
typedef unsigned int gword;

#if   defined(__M6809__)

#include <stdarg.h>

#define assert(B)  assert_6809(B,__FILE__,__LINE__)
void assert_6809(bool b, const char* s, uint n) {
    printf("\nASSERT FAILS at %s:%d\n");
    while (1) {}
}

void putchar_raw(int ch) {
    *(volatile byte*)0xFF04 = (byte)ch;
}

#elif defined(unix)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#else
#error Unknown architecture in types.h
#endif

#define MAX_OCTETS 250 /* short of 255 */

#define false 0
#define true 1

#endif // TYPES_H__
