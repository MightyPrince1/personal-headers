#ifndef ARRAY_H
#define ARRAY_H

#ifdef __CPLUSPLUS
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void delete(int *array){

}

void resize(void *array, int ArraySizes){
	va_list varlist;

	va_start(varlist, ArraySizes);

	va_arg(varlist, int);

	va_end(varlist);
}

int LenghtOfArray(void *array){
	return (int)( sizeof(array) / sizeof(array[0]));
}

#ifdef __CPLUSPLUS
}
#endif

#endif
