#ifndef _HEAP_H
#define _HEAP_H

#include "List_op.h"
#include "Profiler.h"

// Building Heap 
bool sink_comp(int a, int b, Operation *op ){
    if(op !=NULL) 
        op->count();
    return a > b; 
   
}

// Sink -> Bottom up

void sink(NODE **H_K, int i , int k, Operation *ass, Operation *comp ){
   
    while(2*i <= k){
        int mini = 2*i; // arr[mini] > arr[mini+1]
        if(2*i+1 <= k && H_K[mini] != NULL && H_K[mini+1] != NULL && sink_comp(H_K[mini] -> val, H_K[mini+1]->val, comp) ){
            mini++;
        } // arr[i] > arr[mini]
        if(H_K[i] != NULL && H_K[mini] != NULL && sink_comp(H_K[i] ->val , H_K[mini]->val, comp) ){ // MIN heap <=> arr[i] will receive min (arr[i] < arr[mini] so we comp) 
            NODE *aux = H_K[i];
            H_K[i] = H_K[mini];
            H_K[mini] = aux;
            if(ass!= NULL)
                ass->count(3);
            i = mini;
        }
        else{
            break;
        }
    }
}

void build_heap_bottom_up(NODE **H_K, int k, Operation *ass, Operation *comp ){
    for(int i = k/2; i>=1; i--){
        sink(H_K,i,k, ass, comp);
    }
}

void print_Heap(NODE **H_K, int k){

    for(int i=1; i<=k;i++){
        printf("%d ", H_K[i]->val);
    }

}

#endif
