#define start_year 2020
#define yearly_increase 100
#include "stdio.h"
#include "stdlib.h"
int main(void) {
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);
    int end_year = atoi(buffer) - start_year;
    if (end_year <= 0) {
        end_year = 1000;
    } else {
        end_year = end_year * yearly_increase + 1000;
    }
    printf("%d\n", end_year);
    return 0;
}
