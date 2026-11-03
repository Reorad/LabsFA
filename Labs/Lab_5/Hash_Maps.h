#ifndef HASH_MAPS_H
#define HASH_MAPS_H

#include "Struct_def.h"
#include <stdlib.h>
#include <stdio.h>

#define CLEAR_ELEMENT -1
#define DELETED_ID -2

Entry Deleted={.id = DELETED_ID, .name ="Deleted"};
Entry Clear ={.id = CLEAR_ELEMENT, .name = "Gol"};

Hash_Map *Allocate_HashMap(int n = NMAX){

    Hash_Map *H =(Hash_Map*)malloc(sizeof(Hash_Map));
    H->table = (Entry*)malloc(n * sizeof(Entry));
    H->size_hash = n;
    return H;

}

void Dealocate_HashMap(Hash_Map *H ){

    free(H->table);
    free(H);

}


void clear_HASHMAP(Hash_Map *H ){
    
    H->m_filled = 0;
    H->load_factor = 0;
    for(int i = 0; i< H->size_hash ; i++){
        H->table[i] = Clear;
    }

}

void update_load_factor(Hash_Map *H){
    H->load_factor = H->m_filled/(H->size_hash*1.0);
}
   

// Hashing necesary funcs
int hash_aux(int id, Hash_Map *H){
    return id % H->size_hash;
}

int hash_func_linear(int id, int i, Hash_Map *H){

    return (hash_aux(id, H) + i ) % H->size_hash;
    
}


void HashLinear_insert_one_elemnt(Hash_Map *H, const Entry *element){
    
    if(H->m_filled == H->size_hash){
        printf("Full HashMap\n");
        return;
    }

    for(int k=0; k < H->size_hash; k++){
        int key = hash_func_linear(element->id, k, H);
        if(H->table[key].id == CLEAR_ELEMENT or H->table[key].id == DELETED_ID){
            H->m_filled++;
            H->table[key] = *element;
            update_load_factor(H);
            break;
        }
        else if(H->table[key].id == element->id){
            break;
        }
    }
}

int HashLinear_search_element(Hash_Map *H, const Entry *element, int *op = NULL){
    int count_cells = 0;
    int val = element->id;
    
    for(int i=0; i< H->size_hash; i++){       
        int key = hash_func_linear(element->id, i, H);
        count_cells++;
        if(H->table[key].id == CLEAR_ELEMENT){
            if(op != NULL){
                (*op) = count_cells;
            }
            return -1;
            
            }
        else if(H->table[key].id == val){
            if(op != NULL){
                (*op) = count_cells;
            }
            return key;
            }
    }
            if(op != NULL){
                (*op) = count_cells;
            }
    return -1;
}

void HashLinear_Delete(Hash_Map *H, const Entry *element){
    int val = element->id;

    if(H->m_filled == H->size_hash){
        printf("Full HashMap\n");
        return;
    }

    // -2 will be identifier which 
    for(int k=0; k < H->size_hash; k++){
        int key = hash_func_linear(element->id, k, H);
        
        if(H->table[key].id == val){
            H->table[key] = Deleted;
            H->m_filled--;
            update_load_factor(H);
            break;
        }
        else if(H->table[key].id == CLEAR_ELEMENT){
            printf("Not found \n");
            break;
        }

    }

}


// Quadratic Hashing

int hash_func_quad(int id, int i, Hash_Map *H){

    return (hash_aux(id, H) + i*i ) % H->size_hash;
    
}

// Quadratic hashing

void HashQuad_insert_one_elemnt(Hash_Map *H, const Entry *element){
    
    if(H->m_filled == H->size_hash){
        printf("Full HashMap\n");
        return;
    }

    for(int k=0; k < H->size_hash; k++){
        int key = hash_func_quad(element->id, k, H);
        if(H->table[key].id == CLEAR_ELEMENT or H->table[key].id == DELETED_ID){
            H->m_filled++;
            H->table[key] = *element;
            update_load_factor(H);
            break;
        }
        else if(H->table[key].id == element->id){
            break;
        }
    }
}

int HashQuad_search_element(Hash_Map *H, const Entry *element, int *op = NULL){
    int count_cells = 0;
    int val = element->id;
    for(int i=0; i< H->size_hash; i++){
        
        int key = hash_func_quad(element->id, i, H);
        count_cells++;
        if(H->table[key].id == CLEAR_ELEMENT){
            if(op != NULL){
                (*op) = count_cells;
            }
            return -1;
        }
        else if(H->table[key].id == val){
            if(op != NULL){
                (*op) = count_cells;
            }
            return key;
        }
    }
    if(op != NULL){
        (*op) = count_cells;
    }
    return -1;
}

void HashQuad_Delete(Hash_Map *H, const Entry *element){
    int val = element->id;
    // -2 will be identifier which 
    for(int k=0; k < H->size_hash; k++){
        int key = hash_func_quad(element->id, k, H);
        if(H->table[key].id == val){
            H->table[key] = Deleted;
            H->m_filled--;
            update_load_factor(H);
            break;
        }
        else if(H->table[key].id == CLEAR_ELEMENT){
            printf("Not found \n");
            break;
        }

    }

}




// Printing funcs
void print_HashMap(const Hash_Map *H, bool print_empty = false){
    for(int i =0; i< H->size_hash; i++){
        if(print_empty || H->table[i].id != CLEAR_ELEMENT)
            printf("At indx %d its Element with id %d and name %s \n", i, H->table[i].id, H->table[i].name);
    }
}

void print_LoadFactor(const Hash_Map *H){
    printf("Load factor is %f \n", H->load_factor);
}


#endif