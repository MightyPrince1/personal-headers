/*
sprite *SpriteList
        SpriteAddList((sprite) input)
          example.index = SpriteAddList(example);
        SpriteUpdate(input, index)

*/

#ifndef SPRITE_H
#define SPRITE_H

#ifdef __cplusplus
extern "C"{
#endif



#include "types.h"
#include <stdlib.h>

sprite *SpriteList;
int SpriteList_index = 0;

int SpriteAddList(sprite input){
  SpriteList = realloc(SpriteList, sizeof(sprite) * (SpriteList_index + 1));

  for(int i = 0; i < (sizeof(input.vertices) / sizeof(axis)); i ++){
    if(sizeof(SpriteList[SpriteList_index].vertices) < sizeof(input.vertices[i])){
        SpriteList[SpriteList_index].vertices = realloc(SpriteList[SpriteList_index].vertices, sizeof(SpriteList[SpriteList_index].vertices) * 2);
    }

    SpriteList[SpriteList_index].vertices[i] = input.vertices[i];
  }

  SpriteList[SpriteList_index].bitmap = malloc(sizeof(color*) * (sizeof(input.bitmap) / sizeof(input.bitmap[0])));

  for(int i = 0; i < (sizeof(input.bitmap) / sizeof(input.bitmap[0]); i++){
    SpriteList[SpriteList_index].bitmap[i] = malloc(sizeof(input.bitmap[i]));
  }

  for(int i = 0; i < (sizeof(input.bitmap) / sizeof(input.bitmap[0]); i ++){
    for(int j = 0; j < (sizeof(input.bitmap[i]) / sizeof(color)); j ++){
      SpriteList[SpriteList_index].bitmap[i][j] = input.bitmap[i][j];
    }
  }

  SpriteList[SpriteList_index].scale = input.scale;
  SpriteList[SpriteList_index].index = SpriteList_index;

  SpriteList_index ++;
  return SpriteList_index;
}



void SpriteUpdate(sprite input, unsigned int index){
    for(int i = 0; i < (sizeof(input.vertices) / sizeof(axis)); i ++){
    if(sizeof(SpriteList[index].vertices) < sizeof(input.vertices[i])){
        SpriteList[index].vertices = realloc(SpriteList[index].vertices, sizeof(SpriteList[index].vertices) * 2);
    }

    SpriteList[index].vertices[i] = input.vertices[i];
  }

  SpriteList[index].bitmap = malloc(sizeof(color*) * (sizeof(input.bitmap) / sizeof(input.bitmap[0])));

  for(int i = 0; i < (sizeof(input.bitmap) / sizeof(input.bitmap[0]); i++){
    SpriteList[index].bitmap[i] = malloc(sizeof(input.bitmap[i]));
  }

  for(int i = 0; i < (sizeof(input.bitmap) / sizeof(input.bitmap[0]); i ++){
    for(int j = 0; j < (sizeof(input.bitmap[i]) / sizeof(color)); j ++){
      SpriteList[index].bitmap[i][j] = input.bitmap[i][j];
    }
  }

  SpriteList[index].scale = input.scale;
  SpriteList[index].index = index;
}



#ifdef __cplusplus
}
#endif

#endif
