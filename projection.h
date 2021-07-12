/*
//all inputs that use angles are handled in degrees not radians
int ProjectionHeight
int ProjectionWidth
int ProjectionMap[ProjectionHeight][ProjectionWidth][3]//3 for RGB

DeleteProjectionMap()
ResizeProjectionMap(x,y)

DeleteProjectionMapResults()
ResizeProjectionMapResults(x,y)
DefaultProjectionResults()

ProjectionMapInitialize(x,y);

ProjectionResize(x,y)

int RenderDistance

int FOV

int position[3] //x,y,z

int RotationHorizontal
int RotationVertical

float d_CamPlayer
float step_size

ProjectionCalculate()

ProjectionToWindow()

ProjectionFitWindow()
*/
#ifndef PROJECTION_H
#define PROJECTION_H

#ifdef __cplusplus
extern "C"{
#endif

#include "world.h"
#include "AdMath.h"



//from tstanisl (stackoverflow)
int ProjectionHeight = 0;
int ProjectionWidth = 0;
int (**ProjectionMap)[3] = NULL;

void DeleteProjectionMap() {
    if (ProjectionMap) {
        free(ProjectionMap[0]);
        free(ProjectionMap);
        ProjectionMap = NULL;
    }
}

#define MIN(x,y) ((x) < (y) ? (x) : (y))

void ResizeProjectionMap(int rows, int cols) {
    // allocate new screen
    int (**scr)[3] = calloc(rows, sizeof *scr);
    int (*data)[cols][3] = calloc(rows, sizeof *data);
    for (int r = 0; r < rows; ++r)
        scr[r] = data[r];

    // copy content of old screen to a new one
    int valid_rows = MIN(rows, ProjectionHeight);
    int valid_cols = MIN(cols, ProjectionWidth);
    for (int r = 0; r < valid_rows; ++r)
        memcpy(scr[r], ProjectionMap[r], sizeof(int[valid_cols][3]));

    // release old screen
    DeleteProjectionMap();

    // publish a new screen
    ProjectionMap = scr;
    ProjectionHeight = rows;
    ProjectionWidth = cols;

}

int ProjectionMapResultsHeight = 0;
int ProjectionMapResultsWidth = 0;
float (**ProjectionMapResults)[3] = NULL;

void DeleteProjectionMapResults(){
  #ifndef  CALCULATE_INSTEAD_OF_RAM
    if(ProjectionMapResults){
      free(ProjectionMapResults[0]);
      free(ProjectionMapResults);
      ProjectionMapResults = NULL;
    }
  #endif
}

void ResizeProjectionMapResults(int rows, int cols){
  #ifndef CALCULATE_INSTEAD_OF_RAM
    // allocate new screen
    int (**scr)[3] = calloc(rows, sizeof *scr);
    int (*data)[cols][3] = calloc(rows, sizeof *data);
    for (int r = 0; r < rows; ++r)
        scr[r] = data[r];

      // copy content of old screen to a new one
    int valid_rows = MIN(rows, ProjectionHeight);
    int valid_cols = MIN(cols, ProjectionWidth);
    for (int r = 0; r < valid_rows; ++r)
        memcpy(scr[r], ProjectionMap[r], sizeof(int[valid_cols][3]));

      // release old screen
    DeleteProjectionMapResults();

    // publish a new screen
    ProjectionMapResults = scr;
    ProjectionHeight = rows;
    ProjectionWidth = cols;
  #endif

}

void DefaultProjectionResults(){
  for(int i = 0; i < ProjectionMapResultsHeight; i ++){
    for(int j = 0; j < ProjectionMapResultsWidth; j ++){
      for(int k = 0; k < 3; k ++){
      ProjectionMapResults[i][j][k] = NULL;
      }
    }
  }
}

void ProjectionMapInitialize(int x, int y){
  ResizeProjectionMap(x,y);
  DefaultWorldMap();
}

void ProjectionResize(int x, int y){
  ResizeProjectionMap(x,y);
  ResizeProjectionMapResults(x,y);
}


int RenderDistance = 128;
int FOV = 90;
int FOV_v;

int position[3] = {0,0,0};

int RotationHorizontal = 0;
int RotoationVertical = 0;

float d_CamPlayer = 1;
float step_size = 1;

int FOV_old = FOV;
int position_old[3] = {0,0,0};
int RotationHorizontal_old = 0;
int RotationVertical_old = 0;
float d_CamPlayer_old = 1;
float step_size_old = 1;

void ProjectionCalculate(){
  #ifndef CALCULATE_INSTEAD_OF_RAM
  int calc_check = 0;

  if(FOV_old != FOV  || d_CamPlayer_old != d_CamPlayer || ProjectionMapResults == NULL){
    calc_check = 1;
    #endif

    FOV_v = FOV * ProjectionHeight / ProjectionWidth;

    float l_screen_h = 2 * d_CamPlayer * tan(FOV / 2);
    float l_screen_v = 2 * d_CamPlayer * tan(FOV_v / 2);

    float diff_i_screen_h = l_screen_h / FOV / 2;
    float diff_j_screen_v = l_screen_v / FOV_v / 2;

    float m_rotation_horizontal = sin(DegreesToRadians(RotationHorizontal));
    float m_rotation_vertical = sin(DegreesToRadians(RotoationVertical));

  #ifndef CALCULATE_INSTEAD_OF_RAM
  }
  #endif


  for(int i = -(ProjectionHeight / 2); i < (ProjectionHeight / 2); i ++){
    for(int j = -(ProjectionWidth / 2); j < (ProjectionWidth / 2); j ++){

      #ifndef CALCULATE_INSTEAD_OF_RAM
      if(calc_check == 1){
      #endif

        float alpha_h = atan(i * diff_i_screen_h / d_CamPlayer);
        float alpha_v = atan(j * diff_j_screen_v / d_CamPlayer);

        float vector_z = sin(alpha_v) * m_rotation_vertical;
        float vector_transit_h = cos(alpha_v);

        float vector_x = vector_transit_h * sin(alpha_h) * m_rotation_horizontal;
        float vector_y = vector_transit_h * cos(alpha_h) * m_rotation_horizontal;

        int TravelledDistance = 0;
        int NothingHit = 1;



        #ifndef CALCULATE_INSTEAD_OF_RAM
        if(ProjectionMapResults[[i + ProjectionMapResultsHeight / 2][j + ProjectionMapResultsWidth / 2] == NULL){
          ProjectionMapResults[0] = vector_x;
          ProjectionMapResults[1] = vector_y;
          ProjectionMapResults[2] = vecotr_z;
        }
        #endif

      #ifndef CALCULATE_INSTEAD_OF_RAM
      }
      else{
        if(RotationHorizontal_old != RotationHorizontal || RotationVertical_old != RotationVertical){
          float vector_x = ProjectionMapResults[0] * sin(DegreesToRadians(RotationHorizontal));
          float vector_y = ProjectionMapResults[1] * sin(DegreesToRadians(RotationHorizontal));
          float vector_z = projectionMapResults[2] * sin(DegreesToRadians(RotoationVertical));
        }
        else{
          float vector_x = ProjectionMapResults[0];
          float vector_y = ProjectionMapResults[1];
          float vector_z = ProjectionMapResults[2];
        }
      }
      #endif

      double x_calc = position[0];
      double y_calc = position[1];
      double z_calc = position[2];

      while(NothingHit == 1 && TravelledDistance < RenderDistance){
        long x_array = (long)x_calc;
        long y_array = (long)y_calc;
        long z_array = (long)z_calc;

        NothingHit = (WorldMap[x_array][y_array][z_array][0] = default_WorldState && WorldMap[x_array][y_array][z_array][1] = default_WorldState && WorldMap[x_array][y_array][z_array][2] = default_WorldState);

        ProjectionMap[i + ProjectionHeight / 2][j + ProjectionWidth / 2][0] = WorldMap[InBunds(x_array,0,WorldHeight - 1)][InBunds(y_array,0,WorldWidth - 1)][InBunds(z_array,0,WorldLenght - 1)][0];
        ProjectionMap[i + ProjectionHeight / 2][j + ProjectionWidth / 2][1] = WorldMap[InBunds(x_array,0,WorldHeight - 1)][InBunds(y_array,0,WorldWidth - 1)][InBunds(z_array,0,WorldLenght - 1)][1];
        ProjectionMap[i + ProjectionHeight / 2][j + ProjectionWidth / 2][2] = WorldMap[InBunds(x_array,0,WorldHeight - 1)][InBunds(y_array,0,WorldWidth - 1)][InBunds(z_array,0,WorldLenght - 1)][2];

        x_calc = x_calc + vector_x * step_size;
        y_calc = y_calc + vector_y * step_size;
        z_calc = z_calc + vector_z * step_size;

        TravelledDistance ++;
      }
    }
  }
}

#ifdef USING_WINDOW
#include "CrossPlatform.h"
void ProjectionToWindow(){
  for(int i = 0; i < ProjectionHeight; i ++){
    for(int j = 0; j < ProjectionWidth; j ++){
      WindowWrite(i,j, ProjectionMap[i][j][0], ProjectionMap[i][j][1], ProjectionMap[i][j][2]);
    }
  }
}

void ProjectionFitWindow(){
  if(WindowSizeChanged == 1){
    ResizeProjectionMap(WindowHeight, WindowWidth);
  }
}
#endif



#ifdef __cplusplus
}
#endif

#endif
