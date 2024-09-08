#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE \
    11 /* Max input number is 10^9 + 1 for the terminating symbol*/
#define CONVERSION_BASE 10 /* We want decimal */

int main(void) {
    char input_buffer[MAX_INPUT_SIZE];
    fgets(input_buffer, sizeof(input_buffer), stdin);

    char *endptr = NULL;
    int size = (int)strtol(input_buffer, &endptr, CONVERSION_BASE);

    int *all_numbers = (int *)malloc(size * sizeof(int));

    int index = 0;
    for (int i = 0; i < size; i++) {
        char in_2[MAX_INPUT_SIZE];
        fgets(in_2, sizeof(in_2), stdin);
        all_numbers[index] = (int)strtol(in_2, &endptr, CONVERSION_BASE);
        index++;
    }

    for (int i = index - 1; i >= 0; i--) {
        printf("%d\n", all_numbers[i]);
    }

    free(all_numbers);
    return 0;
}
