#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <set>

using namespace std;

#define num_nodes 3
#define num_total_states (int)pow(2,num_nodes)
#define state_t_size 16

#define SetBit(S,k)     (S |= (1 << (k % state_t_size)))
#define ClearBit(S,k)   (S &= ~(1 << (k % state_t_size)))
#define GetBit(S,k)     ((S & (1 << (k % state_t_size))) >> (k % state_t_size))
#define NegBit(S,k)     ((~GetBit(S,k)) & 1)

typedef unsigned short state_t;

void printState(state_t tState) {
    unsigned short flag_bit = 0x8000;
    for (int i=0; i<state_t_size; i++) {
        if (flag_bit & tState) printf("%d", 1);
        else printf("%d", 0);
        flag_bit = flag_bit >> 1;
    }
    printf("\n");
}

state_t updateState(state_t c){
    state_t n = 0;
    NegBit(c,2)&(GetBit(c,0)|GetBit(c,1)) ? SetBit(n,0) : ClearBit(n,0);
    GetBit(c,0)&GetBit(c,2) ? SetBit(n,1): ClearBit(n,1);
    NegBit(c,2)|(GetBit(c,0)&GetBit(c,1)) ? SetBit(n,2) : ClearBit(n,2);

    return n;
}

int main (void) {
    /*
    state_t temp;
    srand(time(NULL));
    unsigned short rand_num = rand() % num_total_states;
    printf("%d\n", rand_num);
    temp = rand_num;
    
    set <state_t> s;
    pair <set<state_t>::iterator, bool> pr;
    
    pr = s.insert(temp);
    while(pr.second == true) {
        printState(temp);
        temp = updateState(temp);
        pr = s.insert(temp);
    }
    */

    for (int i=0; i<num_total_states; i++) {
        state_t temp = i;
        set <state_t> s;
        pair <set<state_t>::iterator, bool> pr;
        pr = s.insert(temp);
        while(pr.second == true) {
            printState(temp);
            temp = updateState(temp);
            pr = s.insert(temp);
        }
        printf("\n");
    }

    return 0;
}
