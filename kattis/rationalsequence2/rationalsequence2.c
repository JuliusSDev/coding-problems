#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h> 
#define INPUT_LENGTH 200
#define MAX_DEPTH 1001001

struct node
{
    int p;
    int q;
};



int find_index(int p_wanted, int q_wanted) {
    struct node stack[MAX_DEPTH];
    int new_index = 0;
    printf("Index: %d\n", new_index);

    int p=0;
    int q= 0;


    // create start node and put it on top
    struct node start_node = {.p = 1, .q = 1};
    stack[new_index] = start_node;

    if(new_index < MAX_DEPTH - 1){
        new_index++;
    }

    int index_actual = 0;

    while (p != p_wanted || q != q_wanted)
    {
        //printf("While looop: index %d ; Max: %d\n", index, (2 ^ MAX_DEPTH) - 1 ); MAX_DEPTH - 2
        if(new_index < MAX_DEPTH - 2){
            printf("new: %d;   actual: %d\n", new_index,index_actual);
            // pop the parent node
            struct node parent_node = stack[index_actual];
            printf("Pop parent node: p: %d ; q: %d ; index: %d \n", parent_node.p,parent_node.q, index_actual);
            index_actual++;

            struct node left_child = {.p = parent_node.p, .q = (parent_node.p + parent_node.q)};
            stack[new_index] = left_child;
            printf("Add left child node: p: %d ; q: %d ; index: %d \n", left_child.p,left_child.q, index_actual);
            new_index++;
            if(left_child.p == p_wanted && left_child.q == q_wanted) return index_actual;


            struct node right_child = {.p = (parent_node.p + parent_node.q), .q = parent_node.q};
            stack[new_index] = right_child;
            printf("Add right child node: p: %d ; q: %d ; index: %d \n", right_child.p,right_child.q, index_actual);
            new_index++;
            if(right_child.p == p_wanted && right_child.q == q_wanted) return index_actual;
        }

    }
    


    return -1;
}


int main(void) {
    char input_buffer[INPUT_LENGTH];
    fgets(input_buffer, sizeof(input_buffer), stdin);
    int number_of_lines = atoi(input_buffer);

    printf("%s\n",input_buffer);
    
    const char *line = "";
    const char *p = "50";
    const char *q = "20";
    bool letter = false;
    bool is_p = true;
    printf("FOUND AN EXIT: %d\n", find_index(atoi(p), atoi(q)));
    // for(int i = 0; i < INPUT_LENGTH; i++){
    //     if (input_buffer[i] == ' ' && is_p && !letter){ // start
    //         letter = true;
    //     } else if (letter && input_buffer[i] != '/'){ //if is_letter, decide whether p or q
    //         if(is_p){
    //             p += input_buffer[i];
    //         }else {
    //             q += input_buffer[i];
    //         }
    //     } else if (input_buffer[i] == '/'){ // if number change
    //         letter = true;
    //         is_p = false;
    //     } else if (input_buffer[i] == '\n') {
    //         printf("FOUND AN EXIT: %d\n", find_index(atoi(p), atoi(q)));
    //     }
    // }
   
    return 0;
}