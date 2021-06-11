/*WIP(still have to redo allocation)

*/
#ifndef WORLD_H
#define WORLD_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int WorldHeight = 64;
int WorldWidth = 64;
int WorldLenght = 64;

int WorldMap[64][64][64][3];

int default_WorldState = 0;

void DefaultWorldMap(){
  for(int i = 0; i < WorldHeight; i ++){
    for(int j = 0; j < WorldWidth; j ++){
      for(int k = 0; k < WorldLenght; k ++){
        for(int l = 0; l < 3; l ++)
        WorldMap[i][j][k][l] = default_WorldState;
      }
    }
  }
}

//broken have to do memory allocation
/*
int World_x = 128;
int World_y = 128;
int World_z = 128;

int (**WorldMap) = NULL;

void DeleteWorld() {
    if (WorldMap) {
        free(WorldMap);
        WorldMap = NULL;
    }
}

#define MIN(x,y) ((x) < (y) ? (x) : (y))

void ResizeWorld(int x, int y, int z) {
    // allocate new screen
    int (**scr) = calloc(x, sizeof *scr);
    int (*data)[y] = calloc(x, sizeof *data);
    for (int r = 0; r < x; ++r){
        scr[r] = data[r];
      }
    // copy content of old screen to a new one
    int min_x = MIN(x, World_x);
    int min_y = MIN(y, World_y);
    int min_z = MIN(z, World_z);
    for (int r = 0; r < x; ++r){
      for(int j = 0; j < y; j ++){
        memcpy(scr[r], WorldMap[r], sizeof(int[min_z]));
      }
    }
    // release old screen
    DeleteWorld();

    // publish a new screen
    WroldMap = scr;
    World_x = x;
    World_y = y;
    World_z = z;

}
*/

#ifdef __cplusplus
}
#endif

#endif
