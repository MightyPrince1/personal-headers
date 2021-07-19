/*
#compiler agruments:
-lm

(int / use as bool) IsEven(number)
(double)						NegativeToPositive(number)
(double)					 	min(a,b)
(double)					 	max(a,b)
(double) 						p_theorum(a,b)
(double)						RadiansToDegrees(radians)
(double)						DegreesToRadians(degrees)
(double)						NotNegative(number)
(double)						InBounds(number, lower limit, upper limit)
(int)								InBoundsInt(number,lower_limit,upper_limit)
(int / use as bool)	PositiveNegativeBool(branchless_condition)
(double)						RoundBetween(number, lower,upper)
(double)						RoundIntervals(number, interval)
(double)						NotZero(number)
(double)						InBoundsInverter(number,lower,upper)
(int)								IntRoot(number,RootOf)	//broken

*/

#ifndef ADMATH_H
#define ADMATH_H

#ifdef __cplusplus
extern "C"{
#endif

#include <math.h>



int IsEven(int number){
	return (number % 2 == 0);
}



double NegativeToPositive(double number){
	return -number * (number < 0) + number * !(number < 0);
}



double min(double a,double b){
  return a * (a <= b) + b * (b < a);
}



double max(double a,double b){
  return a * (a >= b) + b * (b > a);;
}



double p_theorum(double a,double b){

  double tmp = pow(a,2) + pow(b,2);

  return sqrt(tmp);
}



double RadiansToDegrees(double radians){
	return radians * 180 / M_PI;
}



double DegreesToRadians(double degrees){
	return degrees * M_PI / 180;
}



double NotNegative(double number){
	return number * (number > 0);
}



double InBounds(double number, double lower_limit, double upper_limit){
	return number * (number >= lower_limit && number <= upper_limit) + lower_limit * (number < lower_limit) + upper_limit * (number > upper_limit);
}



int InBoundsInt(int number, int lower_limit, int upper_limit){
	return number * (number >= lower_limit && number <= upper_limit) + lower_limit * (number < lower_limit) + upper_limit * (number > upper_limit);
}



int PositiveNegativeBool(int branchless_condition){
	return (branchless_condition == 1) + -(branchless_condition == 0);
}



double RoundBetween(double number, double lower, double upper){
	while(number > upper){
		number = number - (upper - lower);
	}

	return lower * (number < (lower + upper) / 2) + upper * (number >= (lower + upper) / 2);
}



double RoundIntervals(int number, unsigned int interval){
	int multiplier = number / (interval + (interval == 0)) + 0.5 * PositiveNegativeBool(number > 0);

	return (interval * multiplier) * (interval != 0);
}



double NotZero(double number){
	return number + (number == 0);
}



double InBoundsInverter(double number, double lower, double upper){
		return upper - InBounds(number,lower,upper) + lower;
}



//somehow broken
int IntRoot(int number, int PowerOf){
	int result = 0;
	for(int i = 0; i < number; i++){
		if(!(pow(i,PowerOf) < number)){
			break;
		}
		result = i;
	}

	return result;
}

#ifdef __cplusplus
}
#endif

#endif
