/*
  (int / use as bool) CircleBool(r)
  //returns *array[r * 2 +1][r * 2 + 1]
*/

#ifndef IMPLEMENTATIONS_H
#define IMPLEMENTATIONS_H

#ifdef __cplusplus
  extern "C"{
#endif

#include <math.h>

int CircleBool(int r){
  int x_circle_axis = r * 2 + 1;
  int y_circle_axis = x_circle_axis;

  int y_f = 0.7071057812 * r;
  int x_f = round(r - y_f);

  int circle[x_circle_axis][y_circle_axis];


  int fract[x_f][y_f];
  for(int i = 0; i < x_circle_axis; i ++){
    for(int j = 0; j < y_circle_axis; j ++){
      circle[i][j] = 0;
    }
  }

  for(int i = 0; i < x_f; i ++){
    for(int j = 0; j < y_f; j ++){
      float tmp = pow((r - i), 2) + pow((j), 2);
      if(sqrt(tmp) <= r){
        fract[i][j] = 1;
      }
      else{
        fract[i][j] = 0;
      }

      if(i > x_circle_axis  - 2 * y_f){
        circle[i][i] = 1;
      }
    }
  }
  //apply
  for(int i = 0; i < x_f; i ++){
    for(int j = 0; j < y_f; j ++){
      circle[i][j + r] = fract[i][j];
      circle[i][r - j] = fract[i][j];
      circle[2 * r - i][r + j] = fract[i][j];
      circle[2 * r - i][r - j] = fract[i][j];
      circle[r + j][i] = fract[i][j];
      circle[r - j][i] = fract[i][j];
      circle[r + j][2 * r - i] = fract[i][j];
      circle[r - j][2 * r - i] = fract[i][j];

    }
  }

  for(int i = x_f; i < (2 * r - x_f) + 1; i ++){
    for(int j = x_f; j < (2 * r - x_f) + 1; j ++){
      circle[i][j] = 1;
    }
  }



  return *circle;
}

int Circle(int r){

}

#ifdef __cplusplus
  }
#endif

#endif
