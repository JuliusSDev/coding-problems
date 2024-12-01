#include <stdio.h>
#include <stdlib.h>

int line_count = 0;
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


void put_new_number_in(int* array, int to_sort_in){
	int i = 0;
	
		printf("----------------------------------------\n");
	for (int j = 0; j < line_count; j++){
		printf("j: %d; array[j]: %d; to_sort_in: %d\n", j, array[j], to_sort_in);
		i = j;
		if(array[j] >= to_sort_in || array[j] == 0){
			break;
		}
	}

	printf("Put new number in at:%d\n",i);
	for(int j = line_count - 2; j >= i; j--){
		printf("swap: j: %d; array[j+1]: %d; array[j]: %d\n",j, array[j+1], array[j]);
		array[j+1] = array [j];
	}
	array[i] = to_sort_in;
}
void sort_numbers(int* left_list, int* right_list, FILE* fp){

	for(int line = 0; line < line_count; line++){
		int left = 0;
		int right = 0;
		fscanf(fp, "%d   %d\n",&left, &right);
		put_new_number_in(left_list, left);
		put_new_number_in(right_list,right);
		printf("sort_numbers: %d %d\n",left, right);

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
	for(int line = 0; line < line_count; line++){

		printf("%d %d\n",left_list[line], right_list[line]);
	}
	fclose(fp);


	printf("Total difference %d\n",calculate_difference(left_list, right_list));






	free(left_list);
	free(right_list);

	
	return 0;
}
