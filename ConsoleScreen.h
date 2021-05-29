/*
#public
  (int / use as short)ScreenSpace[x][y][(int)PartOfScreen(foreground + background + occupancy)];
                      DeleteScreenSpace()
                      ResizeScreenSpace(NewX,NewY)
  (int / use as bool) ClearColor
  (int / use as bool) RemoveOldOutput
  //whether or not screen will be cleared at runtime;
                      DebugPrint()
  (char)              background_occupancy[101]
                      screen("action(write + print + fill)","PartOfScreen(foreground + background + FullPixel + occupancy)",x,y,color)
                      ScreenPrint()
                      ScreenClear()
  (int / use as bool) SizeChanged
  (int / use as bool) UpdateScreen
                      DebugSettings()

#private
  (int)               ScreenHeight
  (int)               ScreenWidth

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PrintColor.h"
#include "CrossPlatform.h"

//from tstanisl (stackoverflow)
int ScreenHeight = 0;
int ScreenWidth = 0;
int (**ScreenSpace)[3] = NULL;

void DeleteScreenSpace() {
    if (ScreenSpace) {
        free(ScreenSpace[0]);
        free(ScreenSpace);
        ScreenSpace = NULL;
    }
}

#define MIN(x,y) ((x) < (y) ? (x) : (y))

void ResizeScreenSpace(int rows, int cols) {
    // allocate new screen
    int (**scr)[3] = calloc(rows, sizeof *scr);
    int (*data)[cols][3] = calloc(rows, sizeof *data);
    for (int r = 0; r < rows; ++r)
        scr[r] = data[r];

    // copy content of old screen to a new one
    int valid_rows = MIN(rows, ScreenHeight);
    int valid_cols = MIN(cols, ScreenWidth);
    for (int r = 0; r < valid_rows; ++r)
        memcpy(scr[r], ScreenSpace[r], sizeof(int[valid_cols][3]));

    // release old screen
    DeleteScreenSpace();

    // publish a new screen
    ScreenSpace = scr;
    ScreenHeight = rows;
    ScreenWidth = cols;

}

int ClearColor = 0;

int RemoveOldOutput = 1;
int RemoveOldOutputExecuted = 1;

void DebugPrint(void) {
    RemoveOldOutputExecuted = 0;
    puts("----");
    for (int r = 0; r < ScreenHeight; ++r) {
        for (int c = 0; c < ScreenWidth; ++c) {
            for (int d = 0; d < 3; ++d) {
                printf(" %d", ScreenSpace[r][c][d]);
            }
            putchar('|');
        }
        putchar('\n');
    }
}

//by me
char background_occupancy[101] = {' ','@','@','@','@','@','@','W','W','M','M','M','M','M','M','M','M','B','Q','G','P','N','N','&','O','D','g','S','E','m','w','A','8','Z','K','H','6','9','X','C','p','b','q','5','U','2','O','e','3','a','V','V','F','4','h','k','o','s','y','u','n','n','c','T','z','z','7','J','x','L','L','v','?','?','=','f','t','t','j',')','(','(','r','r','i','^','/','*','_',';',';',':','-',',','.','.',' ',' ',' ',' '};

void screen(char mode[5],char AssignToType[10], int x, int y, int color){

  int RunFunction = 1;

  if(x < 0 || y < 0 || x >= ScreenHeight || y >= ScreenWidth){
    RunFunction = 0;
  }

  if(RunFunction == 1){
    char write[] = "write";
    char print[] = "print";
    char fill[] = "fill";
    char foreground[] = "foreground";
    char background[] = "background";
    char FullPixel[] = "FullPixel";
    char occupancy[] = "occupancy";

    if(strcmp(mode,write) == 0){
      if(color > -2){
        if(strcmp(AssignToType,foreground) == 0){
          ScreenSpace[x][y][0] = color;
        }
        if(strcmp(AssignToType,background) == 0){
          ScreenSpace[x][y][1] = color;
        }
        if(strcmp(AssignToType,FullPixel) == 0){
          ScreenSpace[x][y][0] = color;
          ScreenSpace[x][y][1] = color;
        }
        if(strcmp(AssignToType,occupancy) == 0){
          ScreenSpace[x][y][2] = color;
        }
      }
    }

    if(strcmp(mode,print) == 0){

      ClearColor = ClearColor * (ClearColor > -1);

      if(RemoveOldOutputExecuted == 1 && RemoveOldOutput == 1){
        CrossSystem("clear");
      }

      for(int i = 0; i < ScreenHeight; i ++){
        for(int j = 0; j < ScreenWidth; j ++){
          for(int k = 0; k < 3; k ++){
              ScreenSpace[i][j][k] = ScreenSpace[i][j][k] * (ScreenSpace[i][j][k] < 16);
            }

            text_color(ScreenSpace[i][j][0] * !(ScreenSpace[i][j][0] < 0) + ClearColor * (ScreenSpace[i][j][0] < 0));
            background_color(ScreenSpace[i][j][1] * !(ScreenSpace[i][j][1] < 0) + ClearColor * (ScreenSpace[i][j][1] < 0));
            printf("@@");
            reset();
          }
        printf("\n");
      }

    RemoveOldOutputExecuted = 1;
    }

    if(strcmp(mode,fill) == 0){
      for(int i = 0; i < ScreenHeight; i ++){
        for(int j = 0; j < ScreenWidth; j ++){
          if(strcmp(AssignToType,foreground) == 0){
            ScreenSpace[i][j][0] = color;
          }
          if(strcmp(AssignToType,background) == 0){
            ScreenSpace[i][j][1] = color;
          }
          if(strcmp(AssignToType,FullPixel) == 0){
            ScreenSpace[i][j][0] = color;
            ScreenSpace[i][j][1] = color;
          }
          if(strcmp(AssignToType,occupancy) == 0){
            ScreenSpace[i][j][2] = color;
          }
        }
      }
    }
  }
}

void ScreenPrint(){
  screen("print",0,0,0,0);
}

void ScreenClear(){
  screen("fill","FullPixel",0,0,ClearColor);

}

int SizeChanged = 0;
int UpdateScreen = 1;

void DebugSettings(){
  SizeChanged = 0;
  int selector = 0;

  if(RemoveOldOutput == 1 && RemoveOldOutputExecuted == 1){
    CrossSystem("clear");
  }

  reset();
  printf("settings\n");
  printf("-----------------\n");
  printf("1 resolution\n");
  printf("2 ClearColor\n");
  printf("3 DebugPrint\n");
  printf("4 Statistics\n");
  printf("5 RemoveOldOutput\n");
  scanf("%d",&selector);
  if(selector == 1){
    if(RemoveOldOutput == 1 && RemoveOldOutputExecuted == 1){
      CrossSystem("clear");
    }

    int NewX;
    int NewY;

    printf("x: ");
    scanf("%d",&NewX);
    printf("\n");

    printf("y: ");
    scanf("%d", &NewY);
    printf("\n");

    ResizeScreenSpace(NegativeToPositive(NewX), NegativeToPositive(NewY));

    SizeChanged = 1;

    delay(1000);
  }

  if(selector == 2){
    if(RemoveOldOutput == 1 && RemoveOldOutputExecuted == 1){
      CrossSystem("clear");
    }

    int NewColor = 0;
    printf("Color(0-15): ");
    scanf("%d",&NewColor);
    ClearColor = NewColor;

    delay(1000);
  }
  if(selector == 3){
    if(RemoveOldOutput == 1 && RemoveOldOutputExecuted == 1){
      CrossSystem("clear");
    }

    DebugPrint();

    delay(1000);
  }
  if(selector == 4){
    if(RemoveOldOutput == 1 && RemoveOldOutputExecuted == 1){
      CrossSystem("clear");
    }

    printf("Screen Height:     %d\n",ScreenHeight);
    printf("Screen Width:      %d\n",ScreenWidth);
    printf("---------------------\n");
    printf("Clear Color:       %d\n",ClearColor);
    printf("Remove Old Output: %d\n",RemoveOldOutput);

    RemoveOldOutputExecuted = 0;

    delay(1000);
  }
  if(selector == 5){
    int scanner;
    printf("Remove Old Output: ");
    scanf("%d", &scanner);

    RemoveOldOutput = scanner;

    delay(1000);
  }

  UpdateScreen = 1;
}
