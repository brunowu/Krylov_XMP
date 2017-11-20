#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../includes/constant_data.h"

//random_get function
double random_get(double min, double max);
int matrix_max_count(double ** m);

//main function
int main(void){
	srand(time(NULL));
	double ** mat;
	mat = malloc(sizeof(double *) * ROWS_NUM);
	for(int i=0; i<ROWS_NUM; i++){
		mat[i] = malloc(sizeof(double) * COLS_NUM);
	}

	for(int i=0; i<ROWS_NUM; i++){
		for(int j=0; j<COLS_NUM; j++){
			if( j == i - 1){
				*(*(mat + i) + j) = -3;
			}else if( j == i ){
				*(*(mat + i) + j) = 5;
			}else if( j == i + 1){
				*(*(mat + i) + j) = 1;
			}else{
				*(*(mat + i) + j) = 0;
			}
		}
	}

	//write to mat_sample.txt
	FILE *f1;
	f1 = fopen("mat_10000_10000.txt", "wb+");
	int ret;
	for(int i=0; i<ROWS_NUM; i++){
		ret = fwrite(mat[i], sizeof(double), COLS_NUM, f1);
	}
	fclose(f1);

	for(int i=0; i<ROWS_NUM; i++){
		free(mat[i]);
	}
	free(mat);
	printf("Well Done!!!\n");
}

double random_get(double min, double max){
	double range = max - min;
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

int matrix_max_count(double ** m){
	int * count, * index;
	count = malloc(sizeof(int));
	index = malloc(sizeof(int));

	* count = 0;
	for(int i=0; i<ROWS_NUM; i++){
		* index = 0;
		for(int j=0; j<COLS_NUM; j++){
			if(*(*(m + i) + j) != 0){
				* index = * index + 1;
			}
		}
		if(* index > * count){
			* count = * index;
		}
	}
	free(index); index = NULL;
	return (* count);
}