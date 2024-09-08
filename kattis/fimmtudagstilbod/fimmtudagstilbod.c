#include "stdio.h"
#include "stdlib.h"

#define START_YEAR 2020
#define YEARLY_INCREASE 100
#define START_PRICE 1000
#define MAX_INPUT_SIZE 5   /* Maximum input number is 9 999 */
#define CONVERSION_BASE 10 /* Use the decimal system */

int main(void) {
    char buffer[MAX_INPUT_SIZE];
    fgets(buffer, sizeof(buffer), stdin);

    char *endptr = NULL;
    int end_year = (int)strtol(buffer, &endptr, CONVERSION_BASE) - START_YEAR;

    if (end_year <= 0) {
        end_year = START_PRICE;
    } else {
        end_year = START_PRICE + end_year * YEARLY_INCREASE;
    }

    printf("%d\n", end_year);
    return 0;
}
