/*
hex WindowSpace[x][y]
    ResizeWindowSpace(x,y)
    WindowSpaceWrite(x,y,r,g,b)
    WindowUpdate()
    WindowResize(height,width)
*/
#ifndef CROSSWINDOW_H
#define CROSSWINDOW_H

#ifdef __cplusplus
  extern "C"{
#endif

#define USING_WINDOW

#include "CrossPlatform.h"
#include <stdlib.h>
#include "AdMath.h"

hex (**WindowSpace) = NULL;

int WindowSpaceHeight = 0;
int WindowSpaceWidth = 0;

void ResizeWindowSpace(int x, int y){


  hex WindowSpaceSave[WindowSpaceHeight][WindowSpaceWidth];

  for(int i = 0; i < WindowSpaceHeight;  i ++){
    for(int j = 0; j < WindowSpaceWidth; j ++){
      WindowSpaceSave[i][j] = WindowSpace[i][j];
    }
  }

  for(int i = 0; i < WindowSpaceWidth; i ++){
    free(WindowSpace[i]);
    WindowSpace[i] = NULL;
  }

  free(WindowSpace);
  WindowSpace = NULL;

  WindowSpace = malloc(sizeof(hex*) * x);

  for(int i = 0; i < x; i ++){
    WindowSpace[i] = malloc(sizeof(hex) * y);
  }

  for(int i = 0; i < min(WindowSpaceHeight,x); i++){
    for(int j = 0; j < min(WindowSpaceWidth,y); j ++){
      WindowSpace[i][j] = WindowSpaceSave[i][j];
    }
  }

  WindowSpaceHeight = x;
  WindowSpaceWidth = y;
}

void WindowSpaceWrite(int x, int y, int r,int g, int b){
  if(x >= WindowSpaceHeight || y >= WindowSpaceWidth){
      return;
  }

  WindowSpace[x][y] = CrossRGB(r,g,b);
}



void WindowUpdate(){
  int n_values = 1;
  hex (*value_list) = malloc(sizeof(hex));

  value_list[0] = WindowSpace[0][0];

  for(int i = 0; i < WindowSpaceHeight; i++){
    for(int j = 0; j <WindowSpaceWidth; j++){
      int broke_cycle = 0;

      for(int k = 0; k < n_values; k ++){
        if(WindowSpace[i][j] == value_list[k]){
          broke_cycle = 1;
          break;
        }
      }

      if(broke_cycle == 1){
        n_values ++;
        value_list = malloc(sizeof(hex));

        value_list[n_values - 1] = WindowSpace[i][j];
      }
    }
  }

  int value_list_amounts[n_values];

  for(int i = 0; i < WindowSpaceHeight; i ++){
    for(int j = 0; j < WindowSpaceWidth; j ++){
      for(int k = 0; k < n_values; k ++){
        if(WindowSpace[i][j] == value_list[k]){
          value_list_amounts[k] ++;
          break;
        }
      }
    }
  }

  int max_n_points = 0;

  for(int i = 0; i < n_values; i ++){
    max_n_points = max(value_list_amounts[i],max_n_points);
  }

  int value_coords[n_values][max_n_points];

  for(int i = 0; i < n_values; i ++){
    for(int j = 0; j < max_n_points; j ++){
      value_coords[i][j] = -1;
    }
  }

  for(int i = 0; i < WindowSpaceHeight; i ++){
    for(int j = 0; j < WindowSpaceWidth; j ++){
      int value_list_position;
      for(int k = 0; k < n_values; k ++){
        if(WindowSpace[i][j] == value_list[k]){
          value_list_position = k;
          break;
        }
      }

      int l_i = 0;
      while(value_list[l_i] != -1){
        l_i ++;
      }

      value_coords[value_list_position][l_i] = NotNegative((i - 1) * WindowWidth) + j;
    }
  }

  for(int i = 0; i < n_values; i ++){
    #ifdef UNIX
      XSetForeground(d,gc,value_list[i]);
      XDrawPoints(d,w,gc,value_coords[i],max_n_points,CoordModeOrigin);
    #endif
  }
}

void WindowResize(int height, int width){
  ResizeWindowSpace(height,width);
  WindowScreenResize(height,width);
  WindowUpdateSize();
}

#ifdef __cplusplus
  }
#endif

#endif
