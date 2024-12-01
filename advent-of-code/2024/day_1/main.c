
#include <stdio.h>
#include <stdlib.h>

int count_lines(char* filename){
	FILE *fp = fopen(filename, "r");
	int ch = 0;
	int lines = 0;

	if(fp == NULL){
		return 0;
	}

	while(!feof(fp)){
		ch = fgetc(fp);
		if(ch == '\n') {
			lines++;
		}
	}

	fclose(fp);

	return lines;
}

int main(void){

	printf("Linescount: %d\n", count_lines("input"));

	int number_lines = count_lines("input");

	int *left_list = malloc(number_lines * sizeof(int));
	int *right_list = malloc(number_lines * sizeof(int));



	free(left_list);

	
	return 0;
}
