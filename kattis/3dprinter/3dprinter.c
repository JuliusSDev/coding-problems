#include "stdio.h"
#include "stdlib.h"


int main(void) {
    char input_buffer[10];
    fgets(input_buffer, sizeof(input_buffer), stdin);
    int statues_to_print = atoi(input_buffer);
    int printers = 1;
    int optimum = statues_to_print;
    int timestamps = 0;
    int statues_printed = 0;

    while (statues_printed < statues_to_print) {
        timestamps ++;
        //printf("iteration: %d\n", timestamps);
        if(2 * (printers + statues_printed) < statues_to_print){
            //printf("case 1\n");
            printers += printers; 
        } else if ( statues_printed < statues_to_print) {
          //  printf("case 2\n");
            statues_printed += printers;
        } else {
          //  printf("case 3\n");
            printf("%d\n", timestamps);
            return 0;
            
        }
    }
    printf("%d\n", timestamps);
    
    return 0;
}
