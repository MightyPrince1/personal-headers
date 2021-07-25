/*
  (int / use as bool) CircleBool[r*2+1][r*2+1]//has to be caluculated to be used
                      CircleBoolCaluclate(r)
  (float)             CircleCircumference
                      CricleCircumferenceCalculate(r)
*/

#ifndef IMPLEMENTATIONS_H
#define IMPLEMENTATIONS_H

#ifdef __cplusplus
  extern "C"{
#endif

#include "AdMath.h"
#include <stdlib.h>

int **CircleBool;

void CircleBoolCaluclate(int r){
  int x_circle_axis = r * 2 + 1;
  int y_circle_axis = x_circle_axis;

  int y_f = 0.7071057812 * r;
  int x_f = round(r - y_f);

  //int **circle;//[x_circle_axis][y_circle_axis];
  for(int i = 0; i < x_circle_axis; i++){
    free(CircleBool[i]);
  }

  free(CircleBool);

  CircleBool = malloc(sizeof(int*) * x_circle_axis);

  for(int i = 0; i < x_circle_axis; i ++){
    CircleBool = malloc(sizeof(int) * y_circle_axis);
  }


  int fract[x_f][y_f];
  for(int i = 0; i < x_circle_axis; i ++){
    for(int j = 0; j < y_circle_axis; j ++){
      CircleBool[i][j] = 0;
    }
  }

  for(int i = 0; i < x_f; i ++){
    for(int j = 0; j < y_f; j ++){
      float tmp = p_theorum(r - i, j);

      fract[i][j] = 1 * (tmp <= r);
    }
  }
  //apply
  for(int i = 0; i < x_f; i ++){
    for(int j = 0; j < y_f; j ++){
      CircleBool[i][j + r] = fract[i][j];
      CircleBool[i][r - j] = fract[i][j];
      CircleBool[2 * r - i][r + j] = fract[i][j];
      CircleBool[2 * r - i][r - j] = fract[i][j];
      CircleBool[r + j][i] = fract[i][j];
      CircleBool[r - j][i] = fract[i][j];
      CircleBool[r + j][2 * r - i] = fract[i][j];
      CircleBool[r - j][2 * r - i] = fract[i][j];

    }
  }

  for(int i = x_f; i < (2 * r - x_f) + 1; i ++){
    for(int j = x_f; j < (2 * r - x_f) + 1; j ++){
      CircleBool[i][j] = 1;
    }
  }
}

float **CircleCircumference;

void CircleCircumferenceCalculate(int r){
  int x_circle_axis = r * 2 + 1;
  int y_circle_axis = x_circle_axis;

  int y_f = 0.7071057812 * r;
  int x_f = round(r - y_f);

  //float **circle;//[x_circle_axis][y_circle_axis];
  for(int i = 0; i < x_circle_axis; i ++){
    free(CircleCircumference[i]);
  }
  free(CircleCircumference);

  CircleCircumference = malloc(sizeof(float*) * x_circle_axis);

  for(int i = 0; i < x_circle_axis; i ++){
    CircleCircumference[i] = malloc(sizeof(float) *  y_circle_axis);
  }


  float fract[x_f][y_f];
  for(int i = 0; i < x_circle_axis; i ++){
    for(int j = 0; j < y_circle_axis; j ++){
      CircleCircumference[i][j] = 0;
    }
  }

  for(int i = 0; i < x_f; i ++){
    for(int j = 0; j < y_f; j ++){
      float tmp = p_theorum(r - i, j);

      fract[i][j] = (6.283185307179586 * tmp * (tmp <= r)) + (-1 * tmp > r);
    }
  }
  //apply
  for(int i = 0; i < x_f; i ++){
    for(int j = 0; j < y_f; j ++){
      CircleCircumference[i][j + r] = fract[i][j];
      CircleCircumference[i][r - j] = fract[i][j];
      CircleCircumference[2 * r - i][r + j] = fract[i][j];
      CircleCircumference[2 * r - i][r - j] = fract[i][j];
      CircleCircumference[r + j][i] = fract[i][j];
      CircleCircumference[r - j][i] = fract[i][j];
      CircleCircumference[r + j][2 * r - i] = fract[i][j];
      CircleCircumference[r - j][2 * r - i] = fract[i][j];

    }
  }

  for(int i = x_f; i < (2 * r - x_f) + 1; i ++){
    for(int j = x_f; j < (2 * r - x_f) + 1; j ++){
      CircleCircumference[i][j] = 6.283185307179586 * p_theorum(r - i, j);
    }
  }
}

#ifdef __cplusplus
  }
#endif

#endif
