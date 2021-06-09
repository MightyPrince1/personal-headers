/*
//all inputs that use angles are handled in degrees not radians
int ProjectionHeight
int ProjectionWidth
int ProjectionMap[ProjectionHeight][ProjectionWidth][3]//3 for RGB

DeleteProjectionMap()
ResizeProjectionMap(x,y)

int RenderDistance

int FOV

int position[3] //x,y,z

int RotationHorizontal
int RotationVertical

float d_CamPlayer
float step_size

ProjectionCalculate()

ProjectionToWindow()
*/
#ifndef PROJECTION_H
#define PROJECTION_H

#ifdef __cplusplus
extern "C"{
#endif

#include "world.h"



//from tstanisl (stackoverflow)
int ProjectionHeight = 0;
int ProjectionWidth = 0;
int (**ProjectionMap)[3] = NULL;

void DeleteProjectionMap() {
    if (ProjectionMap) {
        free(ProjectionMap[0]);
        free(ProjectionMap);
        ScreenSpace = NULL;
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



int RenderDistance = 128;
int FOV = 90;

int position[3] = {0,0,0};

int RotationHorizontal = 0;
int RotoationVertical = 0;

float d_CamPlayer = 1;
float step_size = 1;

//90 degrees
void CalculateProjection(){
  int FOV_v = FOV * ProjectionHeight / ProjectionWidth;

  float l_screen_h = 2 * d_CamPlayer * tan(FOV);
  float l_screen_v = 2 * d_CamPlayer * tan(FOV_v);

  float diff_i_screen_h = l_screen_h / FOV / 2;
  float diff_j_screen_v = l_screen_v / FOV_v / 2;

  float m_rotation_horizontal = sin(DegreesToRadians(RotationHorizontal));
  float m_rotation_vertical = sin(DegreesToRadians(RotoationVertical))

  for(int i = -(ProjectionHeight / 2); i < (ProjectionHeight / 2); i ++){
    for(int j = -(ProjectionWidth / 2); j < (ProjectionWidth / 2); j ++){
      alpha_h = atan(i * diff_i_screen_h / d_CamPlayer);
      alpha_v = atan(j * diff_j_screen_v / d_CamPlayer);

      float vector_z = sin(alpha_v) * m_rotation_vertical;
      float vector_transit_h = cos(alpha_v);

      float vector_x = vector_transit_h * sin(alpha_h) * m_rotation_horizontal;
      float vector_y = vector_transit_h * cos(alpha_h) * m_rotation_horizontal;

      int TravelledDistance = 0;

      while(NothingHit == 1 && TravelledDistance < RenderDistance){
        double x_calc;
        double y_calc;
        double z_calc;

        long x_array = x_calc;
        long y_array = y_calc;
        long z_array = z_calc;

        NothingHit = (WorldMap[x_array + position[0]][y_array + position[1]][z_array + position[2]] < 1);

        ProjectionMap[i + ProjectionHeight / 2][j + ProjectionWidth / 2][0] = WorldMap[NotNegative(x_array + position[0])][NotNegative(y_array + position[1])][NotNegative(z_array + position[2])][0];
        ProjectionMap[i + ProjectionHeight / 2][j + ProjectionWidth / 2][1] = WorldMap[NotNegative(x_array + position[0])][NotNegative(y_array + position[1])][NotNegative(z_array + position[2])][1];
        ProjectionMap[i + ProjectionHeight / 2][j + ProjectionWidth / 2][2] = WorldMap[NotNegative(x_array + position[0])][NotNegative(y_array + position[1])][NotNegative(z_array + position[2])][2];

        x_calc = x_calc + vector_x * step_size;
        y_calc = y_calc + vector_y * step_size;
        z_calc = z_calc + vector_z * step_size;

        TravelledDistance ++;
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
#endif



#ifdef __cplusplus
}
#endif

#endif


//broken have to do memory allocation

//3000 fps(on a Radeon 560)

/*
int RenderDistance = 128;


int FoV = 90;

int position[3] = {0,0,0};
int horizontal_rotation = 0;
int vertical_rotation = 0;

float step_size;

void CalculateProjection(){
  int breaker = 0;

  breaker = (ProjectionHeight >= ScreenHeight) + (ProjectionWidth >= ScreenWidth);

  int FoV_v = ProjectionWidth/(FoV * ProjectionHeight);

  if(breaker == 0){
    for(int i = 0; i < ProjectionHeight; i ++){
      for(int j = 0; j < ProjectionWidth; j ++){
        float alpha_vertical = RadiansToDegrees(atan(((ProjectionHeight / 2 - i) * tan(FoV_v / 2))/(ProjectionWidth / 2)));
        float alpha_horizontal = RadiansToDegrees(atan(((ProjectionWidth / 2 - j) * tan(FoV / 2))/(ProjectionHeight / 2)));


        float x_step = step_size * cos(DegreesToRadians(alpha_vertical / 2)) * cos(DegreesToRadians(90 - (alpha_horizontal / 2))) * sin(DegreesToRadians(horizontal_rotation))* sin(DegreesToRadians(vertical_rotation));
        float y_step = step_size * cos(DegreesToRadians(alpha_vertical / 2)) * cos(DegreesToRadians(alpha_horizontal / 2))        * sin(DegreesToRadians(horizontal_rotation))* sin(DegreesToRadians(vertical_rotation));
        float z_step = step_size * sin(DegreesToRadians(alpha_vertical / 2))                                                      * sin(DegreesToRadians(horizontal_rotation))* sin(DegreesToRadians(vertical_rotation));

        int NothingHit = 1;

        double x = 0;
        double y = 0;
        double z = 0;

        int TravelledDistance = 0;

        while(NothingHit == 1 && TravelledDistance < RenderDistance){
          long x_array = x;
          long y_array = y;
          long z_array = z;

          NothingHit = (WorldMap[x_array + position[0]][y_array + position[1]][z_array + position[2]] < 1);

          ProjectionMap[i][j] = WorldMap[x_array + position[0]][y_array + position[1]][z_array + position[2]];

          x = x + x_step;
          y = y + y_step;
          z = z + z_step;

          TravelledDistance ++;
        }
      }
    }
  }
}*/
