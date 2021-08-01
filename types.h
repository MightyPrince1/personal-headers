#ifndef TYPES_H
#define TYPES_H

#ifdef __CPLUSPLUS
	extern "C"{
#endif

typedef struct{
	unsigned short r;
	unsigned short g;
	unsigned short b;
}color;



typedef unsigned long hex;



typedef struct{
	double x;
	double y;
	double z;
}axis;

#ifdef __CPLUSPLUS
}
#endif
#endif
