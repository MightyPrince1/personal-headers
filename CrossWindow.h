#ifndef CROSSWINDOW_H
#define CROSSWINDOW_H

#ifdef __cplusplus
  extern "C"{
#endif

#include <stdlib.h>

int (**WindowSpace) = NULL;

int WindowSpaceHeight = 0;
int WindowSpaceWidth = 0;

void ResizeWindowSpace(int x, int y){


  int WindowSpaceSave[WindowSpaceHeight][WindowSpaceWidth];

  for(int i = 0; i < WindowSpaceWidth; i ++){
    free(WindowSpace[i]);
    WindowSpace[i] = 0;
  }

  free(WindowSpace);
  WindowSpace = NULL;

  for(int i = 0; i < WindowSpaceHeight;  i ++){
    for(int j = 0; j < WindowSpaceWidth; j ++){
      WindowSpaceSave[i][j] = WindowSpace[i][j];
    }
  }

  WindowSpace = malloc(sizeof(int*) * x);

  for(int i = 0; i < x; i ++){
    WindowSpace[i] = malloc(sizeof(int) * y);
  }

  for(int i = 0; i < min(WindowSpaceHeight,x); i++){
    for(int j = 0; j < min(WindowSpaceWidth,y); j ++){
      WindowSpace[i][j] = WindowSpaceSave[i][j];
    }
  }

  WindowHeight = x;
  WindowWidth = y;
}

void WindowSpaceWrite(int x, int y, int hex_value){

}

#define USING_WINDOW

#include "CrossPlatform.h"

void WindowVectorize(){

}

void WindowUpdate(){

}

#ifdef __cplusplus
  }
#endif

#endif
