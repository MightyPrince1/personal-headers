#ifndef TYPES_H
#define TYPES_H

#ifdef __CPLUSPLUS
	extern "C"{
#endif

typedef struct{
	unsigned short r;
	unsigned short g;
	unsigned short b;
	unsigned short a;
}color;



typedef unsigned long hex;



typedef struct{
	double x;
	double y;
	double z;
}axis;



typedef struct{
	axis *vertices;
	color **bitmap;
	float scale;
	unsigned int index;
}sprite;

#ifdef __CPLUSPLUS
}
#endif
#endif
