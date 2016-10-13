#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define num_nodes 3
#define num_total_states (int)pow(2,num_nodes)
#define s_size 1
//#define s_size (num_nodes % 32 == 0)? (num_nodes >> 5) : (num_nodes >> 5) + 1 

/* bit operations */
#define SetBit(A,k)     (A[(k >> 5)] |= (1 << (k%32)))
#define ClearBit(A,k)   (A[(k >> 5)] &= ~(1 << (k%32)))            
#define GetBit(A,k)     (A[(k >> 5)] & (1 << (k%32))) >> (k%32)
#define NegBit(A,k)     (~GetBit(A,k)) & 1

typedef struct{
    unsigned int s[s_size];
} state_t;

void printState(state_t* tState) {
    for (int i=0; i<s_size; i++) {
        unsigned int bit = 0x80000000;
        for (int j=0; j<32; j++) {
            if (bit & tState->s[i]) printf("%d", 1);
            else printf("%d", 0);
            bit = bit >> 1;
        }
    }
    printf("\n");
}

state_t* updateState(state_t* c) {
    state_t *n = (state_t*) malloc(sizeof(state_t));
    memset(n, 0, sizeof(state_t));
    
    
    NegBit(c->s,2)&(GetBit(c->s,0)|GetBit(c->s,1)) ? SetBit(n->s,0) : ClearBit(n->s,0);
    GetBit(c->s,0)&GetBit(c->s,2) ? SetBit(n->s,1) : ClearBit(n->s,1);
    NegBit(c->s,2)|(GetBit(c->s,0)&GetBit(c->s,1)) ? SetBit(n->s,2) : ClearBit(n->s,2);
    return n;
}

int main(void)
{
    state_t init;
    
    for (int i=0; i<s_size; i++) {
         srand(time(NULL));
         int rand_num = rand() % num_total_states;
         printf("%d\n", rand_num);
         init.s[i] = rand_num;
    }

    printf("i: "); printState(&init);
    state_t *next = (state_t*) malloc(sizeof(state_t));
    next = updateState(&init);
    printf("f: "); printState(next);

    return 0;
}

