//#include "Profiler.h"


#include "Struct_def.h"
#include "Hash_Maps.h"
#include <stdio.h>

//Profiler pf("Hashmaphings");

const bool DEMO_STATE = false;

enum {LINEAR, QUADRATIC} ;

void print_Table(Hash_Map *H, float AVG_EFFORT, float MAX_EFFORT, float AVG_EFFORT_NF, float MAX_EFFORT_NF){


   printf("%8.2f %12.2f %12.2f %14.2f %14.2f\n", H->load_factor, AVG_EFFORT, MAX_EFFORT, AVG_EFFORT_NF, MAX_EFFORT_NF);

}

void GetTableFactor(Hash_Map *H, Entry *random_arr, float *AVG_EFFORT_FOUND, int *MAX_EFFORT_FOUND, float *AVG_EFFORT_NOT_FOUND, int *MAX_EFFORT_NOT_FOUND, int algo_choice = QUADRATIC ){

    // Found


    int MAX_Effort = 0;
    int total_operations = 0;
    int operation_at_one_search = 0;

    for(int i=0; i<1500;i++){
        if(algo_choice == QUADRATIC)
            HashQuad_search_element(H, &random_arr[i], &operation_at_one_search);
        else
            HashLinear_search_element(H, &random_arr[i], &operation_at_one_search);
        if(operation_at_one_search > MAX_Effort ){
            MAX_Effort  = operation_at_one_search;
        }
        total_operations+= operation_at_one_search;
    }

    float Avg_Effort = total_operations/1500.0;

    // Not Found


    int MAX_Effort_nf = 0;
    int total_operations_nf = 0;
    int operation_at_one_search_nf = 0;
    for(int i = 1500; i<3000; i++){
        if(algo_choice == QUADRATIC)
            HashQuad_search_element(H, &random_arr[i], &operation_at_one_search_nf);
        else
            HashLinear_search_element(H, &random_arr[i], &operation_at_one_search_nf);
        if(operation_at_one_search_nf > MAX_Effort_nf){
            MAX_Effort_nf  = operation_at_one_search_nf;
        }
        total_operations_nf+= operation_at_one_search_nf;
    }

    float Avg_Effort_nf = total_operations_nf/1500.0;

    *AVG_EFFORT_FOUND = Avg_Effort;
    *MAX_EFFORT_FOUND = MAX_Effort;
    *AVG_EFFORT_NOT_FOUND = Avg_Effort_nf;
    *MAX_EFFORT_NOT_FOUND = MAX_Effort_nf;
    // Found printing


}






void Average_case(int algo_choice = QUADRATIC, float load_factor = 0.95){

	int N_PRIME = 10007;
    Hash_Map *H = Allocate_HashMap(N_PRIME);
    float total_MAX_EFF =0;
    float total_MAX_EFF_NF =0;
    float total_AVG_EFF =0;
    float total_AVG_EFF_NF = 0;

        for(int Test =0; Test <5 ; Test++){

            int MAX_EFF, MAX_EFF_NF;
            float AVG_EFF, AVG_EFF_NF;


            clear_HASHMAP(H);

            int N_numb = (load_factor*N_PRIME);

            Entry *elms = Generate_Entry_array(N_numb);

            for(int i =0; i<N_numb; i++){
                if(algo_choice == QUADRATIC)
                    HashQuad_insert_one_elemnt(H,&elms[i]);
                else
                    HashLinear_insert_one_elemnt(H,&elms[i]);
            }

            Entry *e = getRandomArr(H);


            GetTableFactor(H, e, &AVG_EFF, &MAX_EFF, &AVG_EFF_NF, &MAX_EFF_NF, algo_choice);

            total_AVG_EFF += AVG_EFF;
            total_MAX_EFF += MAX_EFF;
            total_AVG_EFF_NF +=AVG_EFF_NF;
            total_MAX_EFF_NF += MAX_EFF_NF;



            Dealocate_Entry_arr(elms);

            Dealocate_Entry_arr(e);


    }

    total_AVG_EFF /= 5;
    total_AVG_EFF_NF /=5;
    total_MAX_EFF /=5;
    total_MAX_EFF_NF /=5;

    if(algo_choice == QUADRATIC)
        printf("Quadratic Hashing \n");
    else
        printf("Linear Hashing \n");

    printf("Example 1 \n");
    printf("%8s %12s %12s %14s %14s\n", "Factor", "Avg found", "Max found", "Avg not found", "Max not found");
    print_Table(H, total_AVG_EFF, total_MAX_EFF, total_AVG_EFF_NF, total_MAX_EFF_NF);

    Dealocate_HashMap(H);

}

void Average_case_p2(int algo_choice = QUADRATIC){

      float load_factor[]={0.8, 0.85, 0.9, 0.95, 0.99};
      if(algo_choice == QUADRATIC)
        printf("Quadratic Hashing \n");
      else
        printf("Linear Hashing \n");

      printf("Example 2 - Load factor at different \n");
      for(int i=0; i<5; i++){

        int N_PRIME = 10007;
        Hash_Map *H = Allocate_HashMap(N_PRIME);

        float total_MAX_EFF =0;
        float total_MAX_EFF_NF =0;
        float total_AVG_EFF =0;
        float total_AVG_EFF_NF = 0;
        float load_fa = load_factor[i];
        for(int Test =0; Test <5 ; Test++){

                int MAX_EFF, MAX_EFF_NF;
                float AVG_EFF, AVG_EFF_NF;


                clear_HASHMAP(H);

                int N_numb = (load_fa*N_PRIME);

                Entry *elms = Generate_Entry_array(N_numb);

                for(int i =0; i<N_numb; i++){
                    if(algo_choice == QUADRATIC)
                        HashQuad_insert_one_elemnt(H,&elms[i]);
                    else
                        HashLinear_insert_one_elemnt(H,&elms[i]);
                }

                Entry *e = getRandomArr(H);


                GetTableFactor(H, e, &AVG_EFF, &MAX_EFF, &AVG_EFF_NF, &MAX_EFF_NF, algo_choice);

                total_AVG_EFF += AVG_EFF;
                total_MAX_EFF += MAX_EFF;
                total_AVG_EFF_NF +=AVG_EFF_NF;
                total_MAX_EFF_NF += MAX_EFF_NF;



                Dealocate_Entry_arr(elms);

                Dealocate_Entry_arr(e);


        }

        total_AVG_EFF /= 5;
        total_AVG_EFF_NF /=5;
        total_MAX_EFF /=5;
        total_MAX_EFF_NF /=5;



        printf("%8s %12s %12s %14s %14s\n", "Factor", "Avg found", "Max found", "Avg not found", "Max not found");

        print_Table(H, total_AVG_EFF, total_MAX_EFF, total_AVG_EFF_NF, total_MAX_EFF_NF);

        Dealocate_HashMap(H);

      }


}

void deletion_case(int algo_choice = QUADRATIC){



    int N_PRIME = 10007;
    Hash_Map *H = Allocate_HashMap(N_PRIME);
    float total_MAX_EFF =0;
    float total_MAX_EFF_NF =0;
    float total_AVG_EFF =0;
    float total_AVG_EFF_NF = 0;

    for(int Test =0; Test <5 ; Test++){

            int MAX_EFF, MAX_EFF_NF;
            float AVG_EFF, AVG_EFF_NF;

            // Insertion in HashMap
            clear_HASHMAP(H);

            int N_numb = (0.99*N_PRIME);

            Entry *elms = Generate_Entry_array(N_numb);

            for(int i =0; i<N_numb; i++){
                if(algo_choice == QUADRATIC)
                    HashQuad_insert_one_elemnt(H,&elms[i]);
                else
                    HashLinear_insert_one_elemnt(H,&elms[i]);
            }



            //print_LoadFactor(H);

            // Deletion now soo we have 0.99 x N prime numbers
            // 0.80 should be desired soo
            int N_Remainig = 0.80 * N_PRIME;
            int N_to_DELETE = N_numb - N_Remainig;
            Entry *del = Generate_Deletion_array(N_to_DELETE, H);

            for(int i =0 ; i<N_to_DELETE; i++){
                if(algo_choice == QUADRATIC)
                    HashQuad_Delete(H, &del[i]);
                else
                    HashLinear_Delete(H, &del[i]);
            }
            //print_LoadFactor(H);

            Entry *e = getRandomArr(H);


            GetTableFactor(H, e, &AVG_EFF, &MAX_EFF, &AVG_EFF_NF, &MAX_EFF_NF, algo_choice);

            total_AVG_EFF += AVG_EFF;
            total_MAX_EFF += MAX_EFF;
            total_AVG_EFF_NF +=AVG_EFF_NF;
            total_MAX_EFF_NF += MAX_EFF_NF;



            Dealocate_Entry_arr(elms);
            Dealocate_Entry_arr(del);
            Dealocate_Entry_arr(e);


    }

    total_AVG_EFF /= 5;
    total_AVG_EFF_NF /=5;
    total_MAX_EFF /=5;
    total_MAX_EFF_NF /=5;

        if(algo_choice == QUADRATIC)
            printf("Quadratic Hashing \n");
        else
            printf("Linear Hashing \n");

    printf("Deletion Case from 0.99 \n");

    printf("%8s %12s %12s %14s %14s\n", "Factor", "Avg found", "Max found", "Avg not found", "Max not found");
    print_Table(H, total_AVG_EFF, total_MAX_EFF, total_AVG_EFF_NF, total_MAX_EFF_NF);

    Dealocate_HashMap(H);


}

void DEMO(){
        int n = 10;
        int H_n = 13;

        Hash_Map *H = Allocate_HashMap(H_n);
        clear_HASHMAP(H);
        print_HashMap(H,true);

        // Hash Insertion
        printf("Insrting \n");
        Entry *elm_arr = Generate_Entry_array(n);

        strcpy(elm_arr[0].name,"Cristiano");
        strcpy(elm_arr[1].name, "Andrei");
        strcpy(elm_arr[2].name, "Mihai");
        strcpy(elm_arr[3].name,"Dragos");
        strcpy(elm_arr[4].name, "Alexie");
        strcpy(elm_arr[5].name, "Andi");
        strcpy(elm_arr[6].name,"David");
        strcpy(elm_arr[7].name, "Iasmina");
        strcpy(elm_arr[8].name, "Catalin Talent");
        strcpy(elm_arr[9].name,"CRUDU");

        for(int i=0; i<n;i++){
            HashQuad_insert_one_elemnt(H, &elm_arr[i]);
        }

        // Printing Hash
        print_HashMap(H);
        print_LoadFactor(H);

        // Finding
        Entry elm = elm_arr[2];

        printf("Finding element with id %d and name %s\n",elm.id, elm.name );

        if(HashQuad_search_element(H, &elm) != -1){
            printf("%s \n", H->table[HashQuad_search_element(H, &elm_arr[2])].name);
        }
        else{
            printf("Not found \n");
        }

        Entry elm_2 ={.id = 1111, .name ="Gata"};
        printf("Finding element with id %d and name %s \n", elm_2.id, elm_2.name);
        if(HashQuad_search_element(H, &elm_2) != -1 ){
            printf("%s \n", H->table[HashQuad_search_element(H, &elm_2)].name);
        }
        else{
            printf("Not found \n");
        }

        // Hash Deletion
        printf("Will be deleting Element with id %d and name %s \n", elm_arr[3].id, elm_arr[3].name);
        HashQuad_Delete(H, &elm_arr[3]);
        print_HashMap(H);

        HashQuad_search_element(H, &elm_arr[3]);
        printf("Finding deleted element with id : %d and name : %s \n", elm_arr[3].id, elm_arr[3].name);
        if(HashQuad_search_element(H, &elm_2) != -1 ){
            printf("%s \n", H->table[HashQuad_search_element(H, &elm_2)].name);
        }
        else{
            printf("Not found \n");
        }

        

        print_LoadFactor(H);

        Dealocate_Entry_arr(elm_arr);
        Dealocate_HashMap(H);

}


int main(){



    if(DEMO_STATE){
        DEMO();
    }
    else{

      Average_case();
      printf("\n");
      Average_case(LINEAR);
      printf("\n");
      Average_case_p2();
      printf("\n");
      Average_case(QUADRATIC,0.80);
      Average_case(QUADRATIC,0.99);
      deletion_case();
      printf("\n");
      // pf.showreport();
    }



}
