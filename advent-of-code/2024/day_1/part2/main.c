#include <stdio.h>
#include <stdlib.h>

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

void sort_numbers(int* left_list, int* right_list, FILE* fp){
	for(int line = 0; line < line_count; line++){
		fscanf(fp, "%d   %d\n",&left_list[line], &right_list[line]);
	}
}

int count_appearing_numbers(int* list, int to_search){
	int count = 0;
	for(int i = 0; i < line_count; i++){
		if(list[i] == to_search){
			count++;
		}
	}
	return count;
}

int calculate_difference(int* list1, int* list2){
	int sum = 0;

	for (int i = 0; i < line_count; i++){
		sum +=list1[i] * count_appearing_numbers(list2, list1[i]);
	}

	return sum;
}

int main(void){
	count_lines("input");

	int *left_list = calloc(line_count, sizeof(int));
	int *right_list = calloc(line_count, sizeof(int));

	FILE *fp = fopen("input", "r");

	sort_numbers(left_list, right_list, fp);
	fclose(fp);

	printf("Total difference %d\n",calculate_difference(left_list, right_list));

	free(left_list);
	free(right_list);
	return 0;
}
