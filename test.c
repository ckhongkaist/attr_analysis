#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define num_nodes 3
#define num_total_states (int)pow(2,num_nodes)
#define s_size (num_nodes % 32 == 0)? (num_nodes >> 5) : (num_nodes >> 5) + 1 

/* bit operations */
#define SetBit(A,k)     ( A[(k >> 5)] |= (1 << (k%32)) )
#define ClearBit(A,k)   ( A[(k >> 5)] &= ~(1 << (k%32)) )            
#define GetBit(A,k)    ( A[(k >> 5)] & (1 << (k%32)) )
//#define NegBit(A,k)    GetBit(A,k)? GetBit(A,k) & ~(1 << (k%32)) : GetBit(A,k) | ~(1 << (k%32))
#define NegBit(A,k)    GetBit(A,k)? ClearBit(A,k) : SetBit(A,k)


/* bitwise representation for a state */
typedef unsigned int state_t[s_size];

/* print state in two's complement*/ 
void printState(state_t* tState) {
    int t_size = s_size;
    for (int i=0; i<t_size; i++) {
        unsigned int bit = 0x80000000;
        for (int j=0; j<32; j++) {
            if (bit & tState[i]) printf("%d", 1);
            else printf("%d", 0);
            bit = bit >> 1;
        }
    }
    printf("\n");
}

state_t* updateState(state_t* c) {
    int t_size = s_size;
    state_t *temp = (state_t*) malloc(sizeof(int)*t_size);
    state_t *n = (state_t*) malloc(sizeof(int)*t_size);
   
    memcpy(temp, c, sizeof(int)*t_size);
    printf("t: "); printState(*temp);

    NegBit(*c,2);
    GetBit(*c,2)&(GetBit(*c,0)|GetBit(*c,1)) ? SetBit(*n,0) : ClearBit(*n,0);
    memcpy(c, temp, sizeof(state_t));
    printf("c: "); printState(c);
    printf("t: "); printState(temp);
    /*
    GetBit(c,0)&GetBit(c,2) ? SetBit(*n,1) : ClearBit(*n,1);
    memcpy(&c, temp, sizeof(state_t));
    printf("c: "); printState(c);
    printf("t: "); printState(*temp);
    NegBit(c,2);
    GetBit(c,2)|(GetBit(c,0)&GetBit(c,1)) ? SetBit(*n,2) : ClearBit(*n,2);
    memcpy(&c, temp, sizeof(state_t));
    printf("c: "); printState(c);
    printf("t: "); printState(*temp);
    */

    /*
    GetBit(c,2)? printf("1"): printf("0");
    GetBit(c,1)? printf("1"): printf("0");
    GetBit(c,0)? printf("1"): printf("0");
    printf("\n");
    
    NegBit(c,2);
    NegBit(c,1);
    NegBit(c,0);
    GetBit(c,2)? printf("1"): printf("0");
    GetBit(c,1)? printf("1"): printf("0");
    GetBit(c,0)? printf("1"): printf("0");
    printf("\n");
    GetBit(*temp,2)? printf("1"): printf("0");
    GetBit(*temp,1)? printf("1"): printf("0");
    GetBit(*temp,0)? printf("1"): printf("0");
    printf("\n");
    */

    return n;
}


int main(void)
{
    state_t init = {0,};
    int t_size = s_size; //why??

    for (int i=0; i<t_size; i++) {
         srand(time(NULL));
         int rand_num = rand() % num_total_states;
         printf("%d\n", rand_num);
         init[i] = rand_num;
    }

    printf("i: "); printState(init);
    state_t *next = (state_t*) malloc(sizeof(int)*t_size);
    next = updateState(init);
    printf("n: "); printState(next);

    /*
    SetBit(s,0);
    printState(s);
    ClearBit(s,0);
    printState(s);
    */
    return 0;
}
