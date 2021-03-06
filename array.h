/*
(int)												LenghtOfArray(*array)
														delete(&array);
(double / use as whatever)	equals(value, dimensions_of_array[])
*/

#ifndef ARRAY_H
#define ARRAY_H

#ifdef __CPLUSPLUS
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include "AdMath.h"

int LenghtOfArray(void array){
	return (int)( sizeof(array) / sizeof(array[0]));
}

int HeightOfArray(void array){
	return (int)(sizeof(array[0]) / sizeof(array[0][0]));
}

int DimesionsOfArray(int array){
	int dimensions = 0;

	while(){
		if(dimensions == 0){
			if(sizeof(array) == sizeof(int)){
				break;
			}
			if(dimensions == 1){
				if(sizeof(array[0]) == sizeof(int)){
					break;
				}
			}

			if(dimensions == 2){
				if(sizeof(array[0][0]) == sizeof(int)){
					break;
				}
			}

			if(dimensions == 3){
				if(sizeof(array[0][0][0]) == sizeof(int)){
					break;
				}
			}
		}

		dimensions ++;
	}

	return dimensions;
}

void delete(int &array){
	if(&array){
		free(&array);
		&array = NULL;
	}
}

double* equals(double value, int dimensions_of_array[]){
	int Lenght_of_dimesions_of_array = sizeof(*dimensions_of_array);

	int number_of_elememts_of_result_array = (Lenght_of_dimesions_of_array != 0);

	for(int i = 0; i < Lenght_of_dimesions_of_array; i ++){
		number_of_elememts_of_result_array = number_of_elememts_of_result_array * dimensions_of_array[i];
	}

	double result_array[number_of_elememts_of_result_array];

	for(int i = 0; i < number_of_elememts_of_result_array; i ++){
		result_array[i] = value;
	}

	return result_array;
}

//WIP
void resize(int &array, int array_size_now[], array_size_wanted[]){
	if(LenghtOfArray(*array) != LenghtOfArray(*array_size_now)){
		#ifdef ERROR_RESULTS_IN_EXIT
			exit(1);
		#endif

		return;
	}

	if(*array_size_now == *array_size_wanted){
		return;
	}

	int n_dimensions =  min(LenghtOfArray(*array_size_now), LenghtOfArray(*array_size_wanted));
	int n_dimensions_wanted = LenghtOfArray(*array_size_wanted);
	int n_dimensions_now = LenghtOfArray(*array_size_now);


}


#ifdef __CPLUSPLUS
}
#endif

#endif
