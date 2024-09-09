#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_SIZE 23
#define BASE 10

int main(void) {
    typedef unsigned long long int ulli_t;
    ulli_t number1 = 0;
    ulli_t number2 = 0;

    int size = 0;

    ulli_t* array = malloc(sizeof(ulli_t));

    // Get the input
    char input_buffer[MAX_NUMBER_SIZE];
    fgets(input_buffer, sizeof(input_buffer), stdin);

    char* endptr = NULL;

    while (strtoull(input_buffer, &endptr, BASE) != (ulli_t)EOF) {
        size++;
        array = realloc(array, size * sizeof(ulli_t));
        if (number1 > number2) {
            number1 -= number2;
        } else {
            number1 = number2 - number1;
        }
        array[size - 1] = number1;

        fgets(input_buffer, sizeof(input_buffer), stdin);
    }

    for (int i = 0; i < size; i++) {
        printf("%llu\n", array[i]);
    }

    free(array);

    return 0;
}
