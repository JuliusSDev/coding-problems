#include "stdio.h"
#include "stdlib.h"

#define MAX_NUMBER_SIZE 5 /* Maximum input size is 10 000 */
#define BASE_FOR_CONVERSION 10

int main(void) {
    // Get the input
    char input_buffer[MAX_NUMBER_SIZE];
    fgets(input_buffer, sizeof(input_buffer), stdin);

    // Convert the input into an integer
    char* endpointer = NULL; /* Needed for strtol */
    int statues_to_print = (int)strtol(input_buffer, &endpointer, BASE_FOR_CONVERSION);

    int printers = 1;
    int timestamps = 0;
    int statues_printed = 0;

    while (statues_printed < statues_to_print) {
        timestamps++;
        // printf("iteration: %d\n", timestamps);
        if (2 * (printers + statues_printed) < statues_to_print) {
            // printf("case 1\n");
            printers += printers;
        } else if (statues_printed < statues_to_print) {
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
