#include <stdio.h>
#include "List_op.h"
#include "Heap.h"
#include "Profiler.h"

Profiler prf("K1 = 5");

#define DEMO_STATE false

//Merge K list alghoritm
NODE *Merge_K(NODE **H_K, int n, int k, Operation *ass , Operation *comp ){

    build_heap_bottom_up(H_K,k, ass, comp);
    NODE *Head = NULL;

    while(k>0){
        if(H_K[1] != NULL){
            NODE *temp = create_new_node(H_K[1]->val);
            if(ass != NULL)
                ass->count();
            temp->next = Head;     
            Head = temp;
        }
        
        NODE *Temp = H_K[1];
        if(H_K[1] != NULL){
            if(ass != NULL)
                ass->count();
            H_K[1]=H_K[1]->next;
        }
        else{
            if(ass != NULL)
                ass->count(3);
            NODE *aux = H_K[1];
            H_K[1] = H_K[k];
            H_K[k] = aux;
            k--;
        }
        sink(H_K,1,k, ass, comp);
        free(Temp);

    }

    return Head;

}

// In lab we discuseed with arrays 
/*int *Merge_K_in_lab(NODE **H_K, int n, int k, Operation *ass , Operation *comp){
    build_heap_bottom_up(H_K,k, ass, comp);

    int indx=0;
    int *arr =(int*)malloc(n * sizeof(int));
    while(k>0){
        if(H_K[1] != NULL){
            arr[indx] = H_K[1]->val;
            indx++;
            if(ass != NULL)
                ass->count();
        }
        
        NODE *Temp = H_K[1];
        if(H_K[1] != NULL){
            if(ass != NULL)
                ass->count();
            H_K[1]=H_K[1]->next;
        }
        else{
            if(ass != NULL)
                ass->count(3);
            NODE *aux = H_K[1];
            H_K[1] = H_K[k];
            H_K[k] = aux;
            k--;
        }
        sink(H_K,1,k, ass, comp);
        free(Temp);

    }

    return arr;
}*/

void Average_case(int k){
    const int TEST = 1000;
    
    char buf_ass[50];
    char buf_comp[50];
    char buf_total[50];
    switch (k)
    {
    case 5:
        strcpy(buf_ass, "Assigments of K1=5 List");
        strcpy(buf_comp, "Comparisons of K1=5 List");
        strcpy(buf_total, "Total of K1=5 List");
        break;
    case 10 :
        strcpy(buf_ass, "Assigments of K1=10 List");
        strcpy(buf_comp, "Comparisons of K1=10 List");
        strcpy(buf_total, "Total of K1=10 List");
        break;
    default:
        strcpy(buf_ass, "Assigments of K1=100 List");
        strcpy(buf_comp, "Comparisons of K1=100 List");
        strcpy(buf_total, "Total of K1=100 List");
        break;
    }

    for(int n = 100; n<= 10000; n+=100){

        Operation ass = prf.createOperation(buf_ass, n);
        Operation comp = prf.createOperation(buf_comp, n);

        for(int test = 1; test <= TEST; test++){
            NODE** k_list = allocate_K_list(k);
            generate_K_random_List(k_list, n, k);
            NODE *List = Merge_K(k_list, n, k, &ass, &comp);
            dealocate_list(List, n);

            dealocate_K_list(k_list,k);
        }
        
    }

    prf.divideValues(buf_ass, TEST);
    prf.divideValues(buf_comp, TEST);
    prf.addSeries(buf_total, buf_ass, buf_comp);

}

void Avg_K_var(){
    
    const int TEST = 10000;
    int n = 10000;
    for(int k = 10; k<= 500; k+=10){
        Operation ass = prf.createOperation("Assigments K list", k);
        Operation comp = prf.createOperation("Comparisons K list", k);

        for(int test = 1; test <= TEST; test++){

            NODE** k_list = allocate_K_list(k);
            generate_K_random_List(k_list, n, k);
            NODE *List = Merge_K(k_list, n, k, &ass, &comp);
            dealocate_list(List, n);
            dealocate_K_list(k_list,k);

        }
        printf("Current k %d It passed 10k tests \n", k);
    }

    prf.divideValues("Assigments K list", TEST);
    prf.divideValues("Comparisons K list", TEST);
    prf.addSeries("Total K list", "Assigments K list", "Comparisons K list");

}

void Demo(){

    int k = 4;
    int n = 20;

    NODE **H_K = allocate_K_list(k);
    generate_K_random_List(H_K, n, k);
    print_k_lists(H_K,k);

    // Heap builded
    build_heap_bottom_up(H_K, k, NULL, NULL);
    // print_Heap(H_K, k);
    printf("List with n elements decreasing from K list merged : ");
    NODE *List = Merge_K(H_K, n, k, NULL, NULL);
    NODE *crt = List;
    while(crt!= NULL){
        printf("%d ", crt->val);
        crt = crt->next;
    }
    dealocate_list(List,n);
    dealocate_K_list(H_K, k);

}


int main(){
    
    if(DEMO_STATE){
        Demo();
    }
    else{
        Average_case(5);
        Average_case(10);
        Average_case(100);
        prf.createGroup("Total k = 5, 10, 100", "Total of K1=5 List", "Total of K1=10 List", "Total of K1=100 List");
        prf.createGroup("Assignments k = 5, 10, 100", "Assigments of K1=5 List", "Assigments of K1=10 List", "Assigments of K1=100 List");
        prf.createGroup("Comparisons k = 5, 10, 100", "Comparisons of K1=5 List", "Comparisons of K1=10 List", "Comparisons of K1=100 List");
        prf.reset("Variables K");
        Avg_K_var();
        prf.createGroup("Total n = 10000, k variable", "Total K list");
        prf.createGroup("Assignments vs Comparisons, k variable", "Assigments K list", "Comparisons K list");
        prf.showReport();

    }
    
}
