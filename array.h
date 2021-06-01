#include <stdio.h>
#include <stdlib.h>

#ifndef ARRAY_H
#define ARRAY_H

#ifdef __CPLUSPLUS
extern "C"{
#endif
void delete(int *array){
}

void resize(void *array, int a){

}

void Resize2D(void *array, int a, int b){

}

void Resize3D(void *array, int a, int b, int c){

}

int LenghtOfArray(void *array){
	return (int)( sizeof(array) / sizeof(array[0]));
}

#ifdef __CPLUSPLUS
}
#endif

#endif
