/*
#compiler agruments:
-lm

(int) 	IsEven(number)
(int)		NegativeToPositive(number)
(int) 	power(number,PowerOf)
(int)	 	min(a,b)
(int) 	max(a,b)
(float) p_theorum(a,b)
(int)		IntRoot(number,RootOf)	//broken

*/

#include <math.h>

int IsEven(int number){
	int remainder = number % 2;

	return 1 * (remainder == 0);
}

int NegativeToPositive(int number){
	return -number * (number < 0) + number * !(number < 0);
}

int power(int number, int PowerOf){
	int result = 1;

	for(int i = 0; i < NegativeToPositive(PowerOf); i ++){
		result = result * number;
	}

	return (1/result) * (PowerOf < 0) + result * !(PowerOf < 0);
}


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
