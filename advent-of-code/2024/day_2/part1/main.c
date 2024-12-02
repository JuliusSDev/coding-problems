#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int line_count = 0; /* total number of lines */

void count_lines(char* filename){
	FILE *fp = fopen(filename, "r");
	int ch = 0;
	int lines = 0;

	if(fp == NULL){
		return;
	}

	while(!feof(fp)){
		ch = fgetc(fp);
		if(ch == '\n') {
			lines++;
		}
	}

	fclose(fp);

	line_count = lines;
}

bool check_increasing(int* numbers, int num_count){
	bool correct_increasing = true;
	printf("in check increasing\n");

	for(int i = num_count-1; i > 1; i-- ){
		printf("checking numbers[i]: %d\n",numbers[i]);
		if (numbers[i] <= numbers[i-1]){
			printf("%d and %d are not increasing\n", numbers[i], numbers[i-1]);
			correct_increasing = false;
		}
	}
	return correct_increasing;
}
bool check_decreasing(int* numbers, int num_count){
	bool correct_decreasing = true;
	printf("in check decreasing\n");

	for(int i = num_count-1; i > 1; i-- ){
		printf("checking numbers[i]: %d\n",numbers[i]);
		if (numbers[i] >= numbers[i-1]){
			printf("%d and %d are not decreasing\n", numbers[i], numbers[i-1]);
			correct_decreasing = false;
		}
	}
	return correct_decreasing;
}


bool check_max_difference(int* numbers, int num_count){
	bool correct_difference = true;
	for (int i = num_count; i > 0; i--){
		if(abs(numbers[i]-numbers[i-1]) > 3){
			correct_difference = false;
		}
	}

	return correct_difference;
	
}

void process_line(FILE* fp){
	if(fp == NULL){
		return;
	}

	int safe = 0;
	
	char* line;
	size_t len = 0;
	while (getline(&line, &len, fp) != -1){
		printf("----------------------------------------------------------\n");
		printf("line:%s\n",line);
		int numbers[20];
		int num_count = 0;
		
		char* token;
		char str[80];
		token = strtok(line, " ");
		numbers[num_count] = atoi(token);
		num_count++;
		while(token != NULL){
			if(*token != '\n' && *token != '\0'){
				printf("%s\n",token);
				numbers[num_count] = atoi(token);
				num_count++;

			}
			token = strtok(NULL, " ");

		}
		if(check_max_difference(&numbers[0], num_count-1) && (check_decreasing(&numbers[0], num_count) || check_increasing(numbers, num_count))){
			printf("line is safe\n");
			safe++;
		}

	}
	safe--; /* Last line*/

	printf("Safe_count: %d\n", safe);
}

int main(void){
	count_lines("input");
	FILE* fp = fopen("input", "r");
	process_line(fp);
	fclose(fp);
	return 0;
}
