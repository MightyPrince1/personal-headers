/*
(hex)  WorldMap[WorldHeight][WorldWidth][WorldLenght]
(int)  WorldHeight
(int)  WorldWidth
(int)  WorldLenght
(int)  default_WorldState

        DefaultWorldMap()
        ResizeWorldMap(NewWorldHeight,NewWorldWidth,NewWorldLenght)
*/
#ifndef WORLD_H
#define WORLD_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int WorldHeight = 0;
int WorldWidth = 0;
int WorldLenght = 0;

hex (***WorldMap) = NULL;

int default_WorldState = 0;

void DefaultWorldMap(){
  for(int i = 0; i < WorldHeight; i ++){
    for(int j = 0; j < WorldWidth; j ++){
      for(int k = 0; k < WorldLenght; k ++){
        WorldMap[i][j][k] = default_WorldState;
      }
    }
  }
}

void ResizeWorldMap(NewWorldHeight,NewWorldWidth,NewWorldLenght){
  hex WorldMapSave[WorldHeight][WorldWidth][WorldLenght];

  for(int i = 0; i < WorldHeight; i ++){
    for(int j = 0; j < WorldWidth; j ++){
      for(int k = 0; k < WorldLenght; k ++){
        WorldMapSave[i][j][k] = WorldMap[i][j][k];
      }
    }
  }

  for(int i = 0; i < WorldWidth; i ++){
    for(int j = 0; j < WorldLenght; j ++){
      free(WorldMap[i][j]);
      WorldMap[i][j] = NULL;
    }
  }

  for(int i = i < WorldWidth; i ++){
    free(WorldMap[i]);
    WorldMap[i] = NULL;
  }

  WorldMap = malloc(sizeof(hex**) * NewWorldHeight);

  for(int i = 0; i < NewWorldHeight; i ++){
    WorldMap[i] = malloc(sizeof(hex*) * NewWorldWidth);
  }

  for(int i = 0; i < NewWorldHeight; i ++){
    for(int j = 0; j < NewWorldWidth; j ++){
      WorldMap[i][j] = malloc(sizeof(hex) * NewWorldLenght);
    }
  }

  for(int i = 0; i < min(NewWorldHeight, WorldHeight); i ++){
    for(int j = 0; j < min(NewWorldWidth, WorldWidth); j ++){
      for(int k = 0; k < min(NewWorldLenght, WorldLenght); k ++){
        WorldMap[i][j][k] = WorldMapSave[i][j][k];
      }
    }
  }

  WorldHeight = NewWorldHeight;
  WorldWidth = NewWorldWidth;
  WorldLenght = NewWorldLenght;
}


#ifdef __cplusplus
}
#endif

#endif
