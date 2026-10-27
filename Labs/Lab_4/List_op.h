#ifndef _LIST_OH_H
#define _LIST_OH_H
#include "Profiler.h"
#include <stdlib.h>

// Structure of Node
typedef struct NODE {
    int val;
    struct NODE *next;
} NODE;

NODE *create_new_node(int val){

    NODE *new_node = (NODE*)malloc(sizeof(NODE));
    new_node->next = NULL;
    new_node->val = val;
    return new_node;
}

//Alocation 
NODE **allocate_K_list(int k){

    NODE **H_K = (NODE**)malloc( (k+1) * sizeof(NODE*));
    for(int i=0;i<=k; i++){
        H_K[i] = NULL;
    }
    NODE *INIT_START = create_new_node(-1);
    H_K[0] = INIT_START;
    return H_K;
}

// Useless tbh but maybe could add it in future
void append_to_K_list(NODE **H_K, NODE *List, int K_indx){
    H_K[K_indx] = List;
}

// Delocate 
void dealocate_K_list(NODE **H_K, int k){

    for(int i=0;i<=k;i++){
        while(H_K[i]!=NULL){
            NODE *temp = H_K[i];
            H_K[i] = H_K[i]->next;
            free(temp);
        }
    }

    for(int i=0; i<=k;i++){
        free(H_K[i]);
    }
    free (H_K);
}

void dealocate_list(NODE *head, int k){
    for(int i=0;i<=k;i++){
        while(head!=NULL){
            NODE *temp = head;
            head = head->next;
            free(temp);
        }
    }
}

/* void generate_K_random_List(NODE **H_K, int n, int k){

    // n -> elements have to split between k lists
    int *arr = (int*)malloc( n * sizeof(int));
    FillRandomArray(arr, n, 10,25000, false, ASCENDING);

    // 1->k lists will take first k elemetns
    for(int i = 1;i<=k;i++){
        int j = i-1;
        NODE *temp = create_new_node(arr[j]);
        H_K[i] = temp;
    }
    memmove(arr , arr + k, (n - k ) * sizeof(int));
    n -= k ;  
    for(int i=1; i<=k;i++){
        if(n>0){
            int rand_n = 1 + rand() % n; 

            // int *arr_new =(int*)malloc
            
            NODE *T = H_K[i]; // tail
            for(int j=0;j<rand_n;j++){
                NODE *temp = create_new_node(arr[j]);
                H_K[i] -> next = temp;
                H_K[i] = H_K[i]->next;
            }
            H_K[i] = T; // back to tail

            // shift reamining elements back
            memmove(arr, arr+rand_n, (n-rand_n)*sizeof(int));
            n-= rand_n;
        }
            
    }
        
    free(arr);
} */

void generate_K_random_List(NODE **H_K, int n, int k){

    // will change into n vectors of size K 
   
    for(int i = 1;i<=k;i++){
        int *arr_init=(int*)malloc(k * sizeof(int));
        FillRandomArray(arr_init, k, 10, 100, false, ASCENDING);
        NODE *temp = create_new_node(arr_init[0]);
        H_K[i] = temp;
        free(arr_init);
    }
    n-=k;
    for(int i=1; i<=k;i++){
        if(n>0){
            int rand_n = 1 + rand() % n; // l + rand() %(r-l+1) 
            if(i == k)
                rand_n = n;
            int *arr_new=(int*)malloc(rand_n * sizeof(int));
            FillRandomArray(arr_new, rand_n, 101,1000, false, ASCENDING);
            
            NODE *T = H_K[i]; // Head
            for(int j=0;j<rand_n;j++){
                NODE *temp = create_new_node(arr_new[j]);
                H_K[i] -> next = temp;
                H_K[i] = H_K[i]->next;
            }
            H_K[i] = T; // back to HEAD
            n-= rand_n;
            free(arr_new);
        }       
    }
}

int get_size_of_List(NODE *Head){
    int size = 0;
    while(Head != NULL){
        size++;
        Head=Head->next;
    }
    return size;
}

void print_k_lists(NODE **H_K, int k){

    for(int i=0;i<=k;i++){
        NODE *T = H_K[i];
        printf("List %d ", i);
        while(H_K[i] !=NULL){
            printf("%d ", H_K[i]->val);
            H_K[i] = H_K[i]->next;
        }
        H_K[i]=T;
        printf("of size %d \n", get_size_of_List(H_K[i]));

    }
    
}


#endif