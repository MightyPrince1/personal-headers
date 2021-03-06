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
(double)						LinearApproximation(percent, first, second)
										//percent from 0 - 1 unless you use #define USING_PERCENTAGE (then it's 0 - 100)
(double)						RecoursiveSubstraction(number, upper)
										//the following functions use degrees by default
										// to use radians do #define USING_RADIANS
										sin_pregenerate()
										tan_pregenerate()
										asin_pregenerate()
										atan_pregenerate()
										pregenerate()
(double)						sin_pre(degrees)
(double)						cos_pre(degrees)
(double)						tan_pre(degrees)
(double)						asin_pre(number)
(double)						acos_pre(number)
(double)						atan_pre(number)
(double)						root(number,exponent)

#depricated
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
  return a * (a >= b) + b * (b > a);
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



double LinearApproximation(float percent, double first, double second){
	#ifdef USING_PERCENTAGE
		return (second - first) * (percent / 100) + first;
	#else
		return (second - first) * percent + first;
	#endif
}



double RecoursiveSubstraction(double number, double upper){
	while(NegativeToPositive(number) > upper){
		number = number - (upper * PositiveNegativeBool(number >= 0));
	}

	return number;
}



double sin_pre_values[92];
double tan_pre_values[92];
double asin_pre_values[92];
double atan_pre_values[92];
//the position 92 is there for overflow protection


double sin_pregenerate(){
	for(int i = 0; i <= 90; i ++){
		sin_pre_values[i] = sin(DegreesToRadians(i));
	}
}



double tan_pregenerate(){
	for(int i = 0; i <= 90; i ++){
		tan_pre_values[i] = tan(DegreesToRadians(i));
	}
}



double asin_pregenerate(){
	for(int i = 0; i <= 90; i ++){
		asin_pre_values[i] = RadiansToDegrees(asin(i/90));
	}
}



double atan_pregenerate(){
	for(int i = 0; i <= 90; i ++){
		atan_pre_values[i] = RadiansToDegrees(atan(i));
	}
}



double pregenerate(){
	sin_pregenerate();
	tan_pregenerate();
	asin_pregenerate();
	atan_pregenerate();
}



double sin_pre(float degrees){
	#ifdef USING_RADIANS
		degrees = RadiansToDegrees(degrees);
	#endif

	degrees = NegativeToPositive(degrees);

	while(degrees > 360){
		degrees = degrees - 360;
	}

	degrees = degrees - 180 * (degrees > 180);
	degrees = degrees * (IsEven(degrees / 90)) + InBoundsInverter(degrees,0,180) * !(IsEven(degrees / 90));

	int using_precentage_check = 0;

	double result;

	#ifdef USING_PERCENTAGE
		#undef USING_PERCENTAGE
		using_precentage_check = 1;
	#endif

	result = LinearApproximation(degrees - (int)degrees,sin_pre_values[(int)degrees],sin_pre_values[(int)degrees + 1]) * PositiveNegativeBool(!(degrees > 180));

	#if using_precentage_check == 1
		#define USING_PERCENTAGE
	#endif

	return result;
}



double cos_pre(float degrees){
	#ifdef USING_RADIANS
		return sin_pre(degrees - 0.785398163);
	#endif

	return sin_pre(degrees - 90);
}



double tan_pre(float degrees){
	#ifdef USING_RADIANS
		degrees = RadiansToDegrees(degrees);
	#endif

	int NegativeMultiplier = PositiveNegativeBool(degrees >= 0);

	degrees = NegativeToPositive(degrees);

	while(degrees > 90){
		degrees = degrees - 90;
	}

	int using_precentage_check = 0;

	double result;

	#ifdef USING_PERCENTAGE
		#undef USING_PERCENTAGE
		using_precentage_check = 1;
	#endif

	result = LinearApproximation(degrees - (int)degrees,tan_pre_values[(int)degrees],tan_pre_values[(int)degrees + 1]) * NegativeMultiplier;

	#if using_precentage_check == 1
		#define USING_PERCENTAGE
	#endif

	return result;
}



double asin_pre(float number){
	int NegativeMultiplier = PositiveNegativeBool(number >= 0);

	number = NegativeToPositive(number);
	if(number > 1){
		return 0;
	}

	int using_precentage_check = 0;

	#ifdef USING_PERCENTAGE
		#undef USING_PERCENTAGE
		using_precentage_check = 1;
	#endif

	double result;

	#ifdef USING_RADIANS
		result = DegreesToRadians(LinearApproximation(number - (int)number, asin_pre_values[(int)(number * 90)],asin_pre_values[(int)(number * 90) + 1]) * NegativeMultiplier);
	#endif

	result = LinearApproximation(number - (int)number, asin_pre_values[(int)(number * 90)],asin_pre_values[(int)(number * 90 + 1)]) * NegativeMultiplier;

	#if using_precentage_check == 1
		#define USING_PERCENTAGE
	#endif

	return result;
}



double acos_pre(float number){
	#ifdef USING_RADIANS
		return asin(number * -1) - 1.570796327;
	#endif
		return asin(number * -1) - 180;
}



double atan_pre(float number){
	int NegativeMultiplier = PositiveNegativeBool(number >= 0);

	number = NegativeToPositive(number);
	number = InBounds(number,0,90);

	int using_precentage_check = 0;

	double result;

	#ifdef USING_PERCENTAGE
		#undef USING_PERCENTAGE
		using_precentage_check = 1;
	#endif

	#ifdef USING_RADIANS
		result = DegreesToRadians(LinearApproximation(number - (int)number,tan_pre_values[(int)number],tan_pre_values[(int)number + 1]) * NegativeMultiplier);
	#endif

	result = LinearApproximation(number - (int)number,tan_pre_values[(int)number],tan_pre_values[(int)number + 1]) * NegativeMultiplier;

	#if using_precentage_check == 1
		#define USING_PERCENTAGE
	#endif

	return result;
}



double root(double number, double exponent){
	return pow(number,1/exponent);
}



//somehow broken
/*int IntRoot(int number, int PowerOf){
	int result = 0;
	for(int i = 0; i < number; i++){
		if(!(pow(i,PowerOf) < number)){
			break;
		}
		result = i;
	}

	return result;
}*/

#ifdef __cplusplus
}
#endif

#endif
