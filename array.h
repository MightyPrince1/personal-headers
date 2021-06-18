#ifndef ARRAY_H
#define ARRAY_H

#ifdef __CPLUSPLUS
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include "AdMath.h"

int LenghtOfArray(void *array){
	return (int)( sizeof(array) / sizeof(array[0]));
}

void delete(int &array){
	if(&array){
		free(&array);
		&array = NULL;
	}
}

void resize(int &array, int array_size_now[], array_size_wanted[]){
	if(LenghtOfArray(*array) != LenghtOfArray(*array_size_now)){
		#ifdef ERROR_RESULTS_IN_EXIT
			exit(1);
		#endif

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
