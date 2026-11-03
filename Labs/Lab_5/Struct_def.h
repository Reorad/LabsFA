#ifndef STRUCT_DEF_H
#define STRUCT_DEF_H

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

#define CLEAR_ELEMENT -1
#define DELETED_ID -2


const int NMAX = 10007;
const int arr_min = 10;
const int arr_max = 31234;
const int RAMAX = 1500;

const int arrEntry_min = 32000;
const int arrEntry_max = arr_max + 45000;

typedef struct{

    int id;
    char name[50];

}Entry;

typedef struct{
    int size_hash;
    int m_filled;
    float load_factor;
    Entry *table;

}Hash_Map;

Entry *Generate_Entry_array(int n){

    Entry *arr = (Entry*)malloc(sizeof(Entry) * n);

    int *int_arr = (int*)malloc(sizeof(int) * n);
    FillRandomArray(int_arr,n, arr_min, arr_max, true, UNSORTED);
        for(int i =0; i<n;i++){
            
            arr[i].id = int_arr[i];
            snprintf(arr[i].name, 50, "Element %d", i);
        }   

    free(int_arr);
    return arr;
}


void Dealocate_Entry_arr(Entry *arr){
    free(arr);
}

Entry *getRandomArr(Hash_Map *H){
    
    Entry *Randomzied_Array = (Entry*)malloc(sizeof(Entry) * 3000);

    // 1500 elemente random
    int *arr =(int*)malloc(H->size_hash * sizeof(int));
    for(int i=0;i<H->size_hash;i++){
        arr[i] = -1;
    }
    
    for(int i=0; i< RAMAX; i++){

        int indx = rand()%H->size_hash;
        while(arr[indx] != -1 || H->table[indx].id == CLEAR_ELEMENT || H->table[indx].id == DELETED_ID){
            indx = rand()%H->size_hash;
        }
        arr[indx] = 1;
        Randomzied_Array[i] = H->table[indx];
    }

    // 1500 de elemente not in array
    Entry *elements_not_in_array = (Entry*)malloc(sizeof(Entry) * 1500);

    int *int_arr = (int*)malloc(sizeof(int) * 1500);

    

    FillRandomArray(int_arr,RAMAX,arrEntry_min, arrEntry_max, true, UNSORTED);
        for(int i =0; i<RAMAX;i++){
            elements_not_in_array[i].id = int_arr[i];
            snprintf(elements_not_in_array[i].name, 50, "Element %d", i);
        }   
    
    for(int i=0; i< 1500; i++){

        Randomzied_Array[i+1500] = elements_not_in_array[i];

    }
    

    free(int_arr);
    free(elements_not_in_array);
    free(arr);
    return Randomzied_Array;
}

Entry *Generate_Deletion_array(int n_delete,  Hash_Map *H){

    if(n_delete > H->m_filled){
        printf("You got %d items and you cant delete more than you already got filled %d\nReturning NULL\n", H->m_filled, n_delete);
        return NULL; 
    }
    
    // randomly select the n elements from HashMap to be deleted will return into an entry array
    // frequency vector
    int *arr_del_keys =(int*)malloc(H->size_hash * sizeof(int));
    for(int i=0; i< H->size_hash; i++){
        arr_del_keys[i]=-1;
    }
    // will send how many you want to delete
    
    Entry *deletion_vec =(Entry *)malloc(n_delete * sizeof(Entry));

    for(int  i=0; i<n_delete; i++){
        
        int indx =rand()%H->size_hash;
        while(arr_del_keys[indx] != -1 || H->table[indx].id == CLEAR_ELEMENT || H->table[indx].id == DELETED_ID){
            indx = rand()%H->size_hash;
        }
        arr_del_keys[indx] = 1;
        deletion_vec[i] = H->table[indx];    
    }

    free(arr_del_keys);

    return deletion_vec;

}



#endif