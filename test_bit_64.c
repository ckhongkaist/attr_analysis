#include <stdio.h>

#define num_nodes 64

/* bit operations */
#define SetBit(A,k)     ( A[(k >> 5)] |= (1 << (k%32)) )
#define ClearBit(A,k)   ( A[(k >> 5)] &= ~(1 << (k%32)) )            
#define TestBit(A,k)    ( A[(k >> 5)] & (1 << (k%32)) )

/* bitwise representation for a state */
typedef unsigned int state_t[num_nodes >> 5];

void printState(state_t tState) {
    unsigned int bit = 0x80000000;
    for (int i=0; i<32; i++) {
        if (bit & tState[1]) printf("%d", 1);
        else printf("%d", 0);
        bit = bit >> 1;
    }
    printf("//");
    bit = 0x80000000;
    for (int i=0; i<32; i++) {
        if (bit & tState[0]) printf("%d", 1);
        else printf("%d", 0);
        bit = bit >> 1;
    }

    printf("\n");
}

int main(void)
{
    state_t s = {1,0};
    printState(s);
    SetBit(s, 1);
    printState(s);
    ClearBit(s ,1);
    printState(s);

    return 0;
}
