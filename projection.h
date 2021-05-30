/*
//all inputs that use angles are handled in degrees not radians
int ProjectionHeight
int ProjectionWidth
int FoV
int position[3] //x,y,z
int horizontal_rotation
int vertical_rotation
float step_size
int RenderDistance

DeleteProjection()
ResizeProjection(int x, int y)

CalculateProjection()
*/
#ifndef PROJECTION_H
#define PROJECTION_H


#include "ConsoleScreen.h"
#include "World.h"

int ProjectionMap[28][60];

int ProjectionHeight = 28;
int ProjectionWidth = 60;

//broken have to do memory allocation
/*
//3000 fps(on a Radeon 560)

int (**ProjectionMap) = NULL;

void DeleteProjection() {
    if (ProjectionMap) {
        free(ProjectionMap[0]);
        free(ProjectionMap);
        ProjectionMap = NULL;
    }
}

#define MIN(x,y) ((x) < (y) ? (x) : (y))

void ResizeProjection(int rows, int cols) {
    // allocate new screen
    int (**scr) = calloc(rows, sizeof *scr);
    int (*data)[cols] = calloc(rows, sizeof *data);
    for (int r = 0; r < rows; ++r)
        scr[r] = data[r];

    // copy content of old screen to a new one
    int valid_rows = MIN(rows, ProjectionHeight);
    int valid_cols = MIN(cols, ProjectionWidth);
    for (int r = 0; r < valid_rows; ++r)
        memcpy(scr[r], ProjectionMap[r], sizeof(int[valid_cols]));

    // release old screen
    DeleteProjection();

    // publish a new screen
    ProjectionMap = scr;
    ProjectionHeight = rows;
    ProjectionWidth = cols;

}
*/
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
  }

#endif
