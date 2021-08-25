/*
#compiler arguments:
  -lpthreads

hex WindowSpace[x][y]
    ResizeWindowSpace(x,y)
    WindowSpaceWrite(x,y,r,g,b)
    //currently broken
    WindowUpdate()

    WindowResize(height,width)
    WindowAjustSize()
    WindowUpdateThreaded()
*/
#ifndef CROSSWINDOW_H
#define CROSSWINDOW_H

#ifdef __cplusplus
  extern "C"{
#endif

#define USING_WINDOW

#include "CrossPlatform.h"
#include <stdlib.h>
#include <stdio.h>
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


#ifdef UNIX
  #include <unistd.h>
#endif

#ifdef THREADING_AS_DEFAULT
void WindowUpdateCompressed(){
#else
void WindowUpdate(){
#endif
  int n_values = 1;
  printf("1\n");
  hex (*value_list) = malloc(sizeof(hex));

  value_list[0] = WindowSpace[0][0];

  for(int i = 0; i < WindowSpaceHeight; i++){
    for(int j = 0; j <WindowSpaceWidth; j++){
      //printf("%d i %d j",i,j);

      int broke_cycle = 0;

      for(int k = 0; k < n_values; k ++){
        if(WindowSpace[i][j] == value_list[k]){
          broke_cycle = 1;
          break;
        }
      }

      if(broke_cycle == 1){
        n_values ++;

        if(sizeof(hex) * n_values > sizeof(value_list)){
          value_list = (hex*) realloc(value_list,sizeof(hex) *n_values *2);
        }

        //value_list = (hex*) realloc(value_list,sizeof(hex) * n_values);

        value_list[n_values - 1] = WindowSpace[i][j];
      }
    }
  }

  value_list = (hex*) realloc(value_list,sizeof(hex) * n_values);

  printf("2\n");

  printf("%d n_values \n",n_values);

  //int value_list_amounts[n_values];
  int* value_list_amounts = malloc(sizeof(int) * n_values);

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

  printf("3\n");

  int max_n_points = 0;

  for(int i = 0; i < n_values; i ++){
    max_n_points = max(value_list_amounts[i],max_n_points);
  }

  printf("4\n");

  //int value_coords[n_values][2][max_n_points];
  int*** value_coords = malloc(sizeof(int**)*n_values);

  printf("4.1\n");

  for(int i = 0; i < n_values; i ++){
    value_coords[i] = malloc(sizeof(int*) * 2);

    for(int j = 0; j < 2; j ++){
      value_coords[i][j] = malloc(sizeof(int) * max_n_points);
    }
  }

  printf("4.2\n");

  for(int i = 0; i < n_values; i ++){
    for(int j = 0; j < 2; j ++){
      for(int k = 0; k < max_n_points; k ++){
        value_coords[i][j][k] = -1;
      }
    }
    printf("%d i\n",i);
    //crashes at 2% and is increadeably slow
  }

  printf("5\n");

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

      value_coords[value_list_position][0][l_i] = i;
      value_coords[value_list_position][1][l_i] = j;
    }
  }

  printf("6\n");

  for(int i = 0; i < n_values; i ++){
    #ifdef UNIX
      XPoint coords_in_x[max_n_points];

      for(int j = 0; j < max_n_points; j ++){
        coords_in_x[j].x = value_coords[i][0][j];
        coords_in_x[j].y = value_coords[i][1][j];
      }

      XSetForeground(d,gc,value_list[i]);
      XDrawPoints(d,w,gc,coords_in_x,max_n_points,CoordModeOrigin);
    #endif
  }
}

void WindowResize(int height, int width){
  ResizeWindowSpace(height,width);
  WindowScreenResize(height,width);
  WindowUpdateSize();
}

void WindowAdjustSize(){
  WindowUpdateSize();

  if(WindowSizeChanged == 1){
    WindowResize(WindowWidth,WindowHeight);
  }
}

#include <pthread.h>

void *WindowUpdateThread(void* thread){
  int thread_interation = *((int *)thread);

  for(int i = thread_interation; i < WindowHeight; i = i + n_cores){
    for(int j = 0; j < WindowWidth; j ++){
      //a modified version of WindowWrite
      #ifdef UNIX
        XSetForeground(d, gc, WindowSpace[i][j]);

        XDrawPoint(d,w,gc, i, j);
      #endif
    }
  }
}

#ifdef THREADING_AS_DEFAULT
void WindowUpdate(){
#else
void WindowUpdateThreaded(){
#endif

  if(n_cores == 0){
    CountCores();
  }

  pthread_t th_id;

  for(int i = 0; i < n_cores; i ++){
    pthread_create(&th_id,NULL,WindowUpdateThread,(void*) &i);
  }

  pthread_exit(NULL);
}

#ifdef __cplusplus
  }
#endif

#endif
