#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extract_arguments(int *n, int *s, int *m) {
    char input_buffer[10];
    fgets(input_buffer, sizeof(input_buffer), stdin);

    int arg_count = 0;
    char word[10] = "";
    int word_index = 0;
    for (int i = 0; i < sizeof(input_buffer) && input_buffer[i] != '\0'; i++) {

        if (input_buffer[i] == ' ' || input_buffer[i] == '\n') {
            if (word_index > 0) {
                word[word_index] = '\0';

                switch (arg_count) {
                    case 0:
                        *n = atoi(word);
                        break;
                    case 1:
                        *s = atoi(word);
                        break;
                    case 2:
                        *m = atoi(word);
                        break;
                    default:
                        break;
                }
                arg_count++;
                word_index = 0;
            }
        } else {
            word[word_index++] = input_buffer[i];
        }
    }

    if (word_index > 0) {
        word[word_index] = '\0';
        switch (arg_count) {
            case 0:
                *n = atoi(word);
                break;
            case 1:
                *s = atoi(word);
                break;
            case 2:
                *m = atoi(word);
                break;
            default:
                break;
        }
    }
}

void extract_field(int* field, int n){
    char input_buffer[2000];
    fgets(input_buffer, sizeof(input_buffer), stdin);

    char word[10] = "";
    int word_index = 0;
    int arg_count = 0;
    int index = 0;
    for (int i = 0; i < sizeof(input_buffer) && input_buffer[i] != '\0'; i++) {
        if (input_buffer[i] == ' ' || input_buffer[i] == '\n') {
            if (word_index > 0) {
                word[word_index] = '\0';

                field[index] = atoi(word);
                index++;
                arg_count++;
                word_index = 0;
                if(index >= n) return;
            }
        } else {
            word[word_index++] = input_buffer[i];
        }
    }
}

int find_magic(int* field, int n, int m){
    for(int i = 0; i < n; i++){
        if(field[i] == m){
            return i;
        }
    }
}

int calculate(int* field, int n, int s, int m, int* status) {
    int index = s;
    int visited[500];
    int visited_index = 0;
    int hops = 0;

    while (field[index] != m) {
        

        int step = field[index];


        index += step;
        hops++;

        for(int i = 0; i < visited_index; i++) {
            if (visited[i] == index){
                *status = -3;
                return hops;
            }
        }

        visited[visited_index] = index;
        visited_index++;
        

        if(index < 0){
            *status = -1;
            return hops; //left out of bounds
        } else if(index >= n){
            *status = -2;
            return hops; //right out of bounds
        }
    }
    *status = 0;
    return index;
}

int main() {
    int n = 0, s = 0, m = 0;
    extract_arguments(&n, &s, &m);

    int field[500];
    extract_field(field, n);

    int magic_index = find_magic(field, n, m);

    int status = 0;
    int hops = calculate(field, n,s,m, &status);

    const char* word;

    if (status == -1) {
        word = "left";
    } else if (status == -2) {
        word = "right";
    } else if (status == -3) {
        word = "cycle";
    } else {
        word = "magic";
    }

    printf("%s\n%d\n",word, hops);

    return 0;
}
