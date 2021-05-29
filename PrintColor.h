/*
#parameters
(short / use as bool) bold
(short / use as bool) LessVisible
(short / use as bool) cursive
(short / use as bool) underline
(short / use as bool) SwapBackground
(short / use as bool) SameBackground
(short / use as bool) crossed
(short / use as bool) LineOver

#functions
                      text_color(color)
                      background_color(color)
                      reset_text()
*/

#include <stdio.h>
#include "AdMath.h"

//parameters
short bold = 0;//1
short LessVisible = 0; //2
short cursive = 0;//3
short underline = 0;//4
short blinking = 0;//5
short SwapBackground = 0; //7
short SameBackground = 0;//8
short crossed = 0;//9
short LineOver = 0; //53

void text_color(unsigned short color){

  short print_mode_1 = (bold == 1);
  short print_mode_2 = 2 * (LessVisible == 1);
  short print_mode_3 = 3 * (cursive == 1);
  short print_mode_4 = 4 * (underline == 1);
  short print_mode_5 = 5 * (blinking == 1);
  //print_mode_6 = print_mode_5
  short print_mode_7 = 7 * (SwapBackground == 1);
  short print_mode_8 = 8 * (SameBackground == 1);
  short print_mode_9 = 9 * (crossed == 1);
  short print_mode_53 = 53 * (LineOver == 1);

  int color_value = 30 + (color/2 + 60 * (IsEven(color) == 0)) * (color < 16);

  printf("\e[%d;%d;%d;%d;%d;%d;%d;%d;%d;%dm",print_mode_1,print_mode_2,print_mode_3,print_mode_4,print_mode_5,print_mode_7,print_mode_8,print_mode_9,print_mode_53,color_value);
}

void background_color(unsigned short color){
  int color_value = 40 + (color/2 + 60 * (IsEven(color) == 0)) * (color < 16);
  printf("\e[%dm",color_value);
}

void FullPixel_color(unsigned short color){
  int color_value = 30 + (color/2 + 60 * (IsEven(color) == 0)) * (color < 16);
  printf("\e[0;%dm",color_value);
  int color_value = 40 + (color/2 + 60 * (IsEven(color) == 0)) * (color < 16);
  printf("\e[%dm",color_value);
}

void reset_text(){
  printf("\e[0m");
}
