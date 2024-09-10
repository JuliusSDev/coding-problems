#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 7
#define CONVERSION_BASE 10

#define ADDER 5
#define MULTIPLICATOR 3

int main(void) {
    char input_buffer[MAX_INPUT_SIZE];
    fgets(input_buffer, sizeof(input_buffer), stdin);

    char* endptr = NULL;
    int input_number = (int)strtol(input_buffer, &endptr, CONVERSION_BASE);

    input_number *= MULTIPLICATOR;
    input_number += ADDER;

    printf("%d\n", input_number);

    return 0;
}
