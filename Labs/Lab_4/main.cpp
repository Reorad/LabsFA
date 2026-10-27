#include <stdio.h>
#include "List_op.h"
#include "Profiler.h"

Profiler prf("K Lists");



int main(){

    NODE **H_K = allocate_K_list(3);
    generate_K_random_List(H_K, 34, 3);
    print_k_lists(H_K,3);
    free_lists(H_K,3);
    dealocate_K_list(H_K, 3);


}
