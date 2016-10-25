#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <iostream>
#include <vector>

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

    map <state_t,int> m; // for hubs (i.e., pseudo attractors)
    pair <map<state_t,int>::iterator, bool> pr_m;
    set< set<state_t> > Attrs;
    map < set<state_t>,int > Attrs_maxdepth;
    pair <map < set<state_t>,int>::iterator, bool> pr_am;

    for (int i=0; i<num_total_states; i++) {
        state_t temp = i;
        set <state_t> s;
        pair <set<state_t>::iterator, bool> pr_s;
        vector<state_t> path; //a path
        set<state_t> attr; //attractor of the path

        pr_s = s.insert(temp);
        pr_m = m.insert(pair<state_t,int>(temp,1));
        if (!pr_m.second)
            m[temp]++;
       
        while(pr_s.second) {
            //printState(temp);
            //printf("\n");
            path.push_back(temp);
            temp = updateState(temp);
            pr_s = s.insert(temp);
            pr_m = m.insert(pair<state_t,int>(temp,1));
            if (pr_s.second && !pr_m.second)
                m[temp]++;
        }
        /* Extract attractors */

        state_t s_attr = 0;
        vector<state_t>::size_type it;
        for (it=0; it<path.size(); ++it){
            if (path[it] == temp) {
                s_attr = it;
                break;
            }
        }
        
        for (it=s_attr; it!=path.size(); ++it){
            attr.insert(path[it]);
        }
        Attrs.insert(attr);
    
        
        pr_am = Attrs_maxdepth.insert(pair< set<state_t>,int>(attr,s_attr-1)); 

        if (!pr_am.second) {
            if (Attrs_maxdepth[attr] < s_attr) {
                Attrs_maxdepth[attr] = s_attr;
            }
        }

        //printf("\n");
        /*
        vector<state_t>::iterator it__;
        for (it__=path.begin(); it__ != path.end(); it__++) {
            printState(*it__);
            printf(" -> ");
        }
        printf("\n");
        */
    }
    
    printf("\n*****State pairs*****\n");
    map<state_t,int>::iterator iter;
    for (iter=m.begin(); iter !=m.end(); ++iter) {
        printf("(");
        printState((state_t)iter->first);
        printf(",%d)\n", (int)iter->second);
    }

   
    printf("\n*****Attractors*****\n");
    set< set<state_t> >::iterator it;
    for (it = Attrs.begin(); it !=Attrs.end(); ++it) {
        for (set<state_t>::iterator it2 = (*it).begin(); it2!=(*it).end(); ++it2) {
            printState(*it2);
            printf(" -> ");
        }
        printState(*(*it).begin());
        printf("\n");
    }

    printf("\n*****Max depth*****\n");
    map< set<state_t>,int >::iterator it_;
    for (it_ = Attrs_maxdepth.begin(); it_ != Attrs_maxdepth.end(); ++it_) {
        for (set<state_t>::iterator it2 = (it_->first).begin(); it2!= (it_->first).end(); ++it2) {
            printState(*it2);
            printf(" -> ");
        }
        printState(*((it_->first).begin()));
        printf(" : %d\n", it_->second);  
    }



    /*
    for (set< vector<state_t> >::iterator it = Attrs.begin(); it !=Attrs.end(); ++it)
        cout << *it << endl;
    */
    return 0;
}
