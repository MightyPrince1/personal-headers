/*
#compiler agruments:
-lm

(int) 	IsEven(number)
(int)		NegativeToPositive(number)
(int)	 	min(a,b)
(int) 	max(a,b)
(float) p_theorum(a,b)
(double)RoundBetween(int number, lower, upper)
(int)		RoundIntervals(int number, int interval);
(int)		IntRoot(number,RootOf)	//broken

*/

#ifndef ADMATH_H
#define ADMATH_H

#ifdef __cplusplus
extern "C"{
#endif

#include <math.h>



int IsEven(int number){
	int remainder = number % 2;

	return 1 * (remainder == 0);
}



int NegativeToPositive(int number){
	return -number * (number < 0) + number * !(number < 0);
}



//redundant !!!
/*int power(int number, int PowerOf){
	int result = 1;

	for(int i = 0; i < NegativeToPositive(PowerOf); i ++){
		result = result * number;
	}

	return (1/result) * (PowerOf < 0) + result * !(PowerOf < 0);
}*/



int min(int a,int b){
  return a * (a <= b) + b * (b < a);
}



int max(int a,int b){
  return a * (a >= b) + b * (b > a);;
}



float p_theorum(float a,float b){

  float tmp = pow(a,2) + pow(b,2);

  return sqrt(tmp);
}



int RadiansToDegrees(int radians){
	return radians * 180 / M_PI;
}



int DegreesToRadians(int degrees){
	return degrees * M_PI / 180;
}



int NotNegative(int number){
	return number * (number > 0);
}



int InBunds(int number, int lower_limit, int upper_limit){
	return number * (number >= lower_limit && number <= upper_limit) + lower_limit * (number < lower_limit) + upper_limit * (number > upper_limit);
}



double RoundBetween(double number, double lower, double upper){
	while(number > upper){
		number = number - (upper - lower);
	}

	return lower * (number < (lower + upper) / 2) + upper * (number >= (lower + upper) / 2);
}



int RoundIntervals(int number, int interval){
	if(interval == 0 || number == 0){
		return 0;
	}

	int mulitplier = 0;

	while(number < 0 * (number > interval * multiplier) + number > 0 * (number < interval * multiplier)){
		multiplier = multiplier + (number > 0) - (number < 0);
	}

	int InBetween = (number < 0) * (number > (interval * mulitplier)) + (number > 0) * (number > (interval * mulitplier));

	multiplier = mulitplier * (InBetween == 0 && !(number < ((interval * multiplier) + (interval * multiplier)) / 2)) + multiplier * !(InBetween == 0 && !(number < ((interval * multiplier) + (interval * multiplier)) / 2))*(multiplier + (number > 0) - (number < 0));

	return interval * multiplier;
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
