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

//putting results in memory is redundant
#define CALCULATE_INSTEAD_OF_RAM;

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
float (**ProjectionMapResults)[3];

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
    float (**scr)[3] = calloc(rows, sizeof *scr);
    float (*data)[cols][3] = calloc(rows, sizeof *data);
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

      //ProjectionMapResults can only have a value between -1 & 1 (that's how math works)
      ProjectionMapResults[i][j][k] = 2;
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
  DefaultProjectionResults();
}


int RenderDistance = 128;
int FOV = 90;
int FOV_v;

int position[3] = {0,0,0};

int RotationHorizontal = 0;
int RotationVertical = 0;

float d_CamPlayer = 1;
float step_size = 1;

int FOV_old = 90;
int position_old[3] = {0,0,0};
int RotationHorizontal_old = 0;
int RotationVertical_old = 0;
float d_CamPlayer_old = 1;

int __calculated_once = 0;

void ProjectionCalculate(){
  int calc_check = 0;

  float l_screen_h;
  float l_screen_v;

  float diff_i_screen_h;
  float diff_j_screen_v;

  float m_rotation_horizontal;
  float m_rotation_vertical;

  float vector_x;
  float vector_y;
  float vector_z;


  #ifndef CALCULATE_INSTEAD_OF_RAM
  if(__calculated_once == 0|| FOV_old != FOV  || d_CamPlayer_old != d_CamPlayer){
    calc_check = 1;
    #endif

    FOV_v = FOV * ProjectionHeight / ProjectionWidth;

    l_screen_h = 2 * d_CamPlayer * tan_pre((FOV / 2));
    l_screen_v = 2 * d_CamPlayer * tan_pre((FOV_v / 2));

    diff_i_screen_h = l_screen_h / FOV / 2;
    diff_j_screen_v = l_screen_v / FOV_v / 2;

    m_rotation_horizontal = sin_pre((RotationHorizontal));
    m_rotation_vertical = sin_pre((RotationVertical));

  #ifndef CALCULATE_INSTEAD_OF_RAM
  }
  #endif


  for(int i = -(ProjectionHeight / 2); i < (ProjectionHeight / 2); i ++){
    for(int j = -(ProjectionWidth / 2); j < (ProjectionWidth / 2); j ++){

      #ifndef CALCULATE_INSTEAD_OF_RAM
      if(calc_check == 1){
      #endif

        float alpha_h = atan_pre(i * diff_i_screen_h / d_CamPlayer);
        float alpha_v = atan_pre(j * diff_j_screen_v / d_CamPlayer);

        vector_z = sin(alpha_v) * m_rotation_vertical;
        float vector_transit_h = cos_pre((alpha_v));

        vector_x = vector_transit_h * sin_pre(alpha_h) * m_rotation_horizontal;
        vector_y = vector_transit_h * cos_pre(alpha_h) * m_rotation_horizontal;



        #ifndef CALCULATE_INSTEAD_OF_RAM
          ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][0] = vector_x;
          ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][1] = vector_y;
          ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][2] = vector_z;
        #endif

      #ifndef CALCULATE_INSTEAD_OF_RAM
      }
      else{
        if(RotationHorizontal_old != RotationHorizontal || RotationVertical_old != RotationVertical){
          vector_x = ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][0] * sin_pre((RotationHorizontal));
          vector_y = ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][1] * sin_pre((RotationHorizontal));
          vector_z = ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][2] * sin_pre((RotationVertical));
        }
        else if(__calculated_once == 0){
          vector_x = ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][0];
          vector_y = ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][1];
          vector_z = ProjectionMapResults[i + ProjectionHeight / 2][j + ProjectionWidth / 2][2];
        }
      }
      #endif

      double x_calc = position[0];
      double y_calc = position[1];
      double z_calc = position[2];

      int TravelledDistance = 0;
      int NothingHit = 1;

      while(NothingHit == 1 && TravelledDistance < RenderDistance){
        long x_array = (long)x_calc;
        long y_array = (long)y_calc;
        long z_array = (long)z_calc;

        NothingHit = ((WorldMap[x_array][y_array][z_array][0] == default_WorldState) && (WorldMap[x_array][y_array][z_array][1] == default_WorldState) && (WorldMap[x_array][y_array][z_array][2] == default_WorldState));

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
  __calculated_once = 1;
}

#ifdef USING_WINDOW
#include "CrossPlatform.h"
void ProjectionToWindow(){
  for(int i = 0; i < ProjectionHeight; i ++){
    for(int j = 0; j < ProjectionWidth; j ++){
      WindowSpaceWrite(i,j, ProjectionMap[i][j][0], ProjectionMap[i][j][1], ProjectionMap[i][j][2]);
    }
  }

  WindowUpdate();
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
