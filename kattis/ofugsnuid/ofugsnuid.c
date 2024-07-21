#include "stdio.h"
#include "stdlib.h"
int main(void){
    char input_buffer[8];

    int all_numbers[100000];
    fgets(input_buffer, sizeof(input_buffer), stdin);
    int index = 0;
    for(int i = 0; i < atoi(input_buffer); i++){
        char in_2[32];
        fgets(in_2, sizeof(in_2),stdin);
        all_numbers[index] = atoi(in_2);
        index++;
    }
    for(int i = index-1; i >= 0; i--){
        printf("%d\n", all_numbers[i]);
    }

    return 0;
}
