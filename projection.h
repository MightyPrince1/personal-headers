/*
//all inputs that use angles are handled in degrees not radians
int ProjectionHeight
int ProjectionWidth
int FoV
int position[3] //x,y,z
int horizontal_rotation
int vertical_rotation
float step_size

projection
*/

#include "SimpleScreen.h"
#include "World.h"

int ProjectionHeight = ScreenHeight;
int ProjectionWidth = ScreenWidth;

int (**ProjectionMap) = NULL;

void release() {
    if (ProjectionMap) {
        free(ProjectionMap);
        ProjectionMap = NULL;
    }
}

#define MIN(x,y) ((x) < (y) ? (x) : (y))

void resize(int rows, int cols) {
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
    release();

    // publish a new screen
    ProjectionMap = scr;
    ProjectionHeight = rows;
    ProjectionWidth = cols;

}

int FoV = 90;
int FoV_v = ProjectionWidth/(FoV * ProjectionHeight);

int position[3] = {0,0,0};
int horizontal_rotation = 0; //in degrees
int vertical_rotation = 0;

float step_size;

projection(char mode[9]){
  int breaker = 0;

  breaker = (ProjectionHeight >= ScreenHeight) + (ProjectionWidth >= ScreenWidth);

  char calculate[9] = "calculate";
  char print[5] = "print";

  if(breaker == 0){
    for(int i = 0; i < ProjectionHeight; i ++){
      for(int j = 0; j < ProjectionWidth; j ++){
        float aplha_vertical = atan(((ProjectionHeight / 2 - i) * tan(FoV_v / 2))/(ProjectionWidth / 2));
        float alpha_horizontal = atan(((ProjectionWidth / 2 - j) * tan(FoV / 2))/(ProjectionHeight / 2));


        float x_step = step_size * cos(DegreesToRadians(alpha_vertical / 2)) * cos(DegreesToRadians(90 - (alpha_horizontal / 2))) * sin(DegreesToRadians(horizontal_rotation))* sin(DegreesToRadians(vertical_rotation));
        float y_step = step_size * cos(DegreesToRadians(alpha_vertical / 2)) * cos(DegreesToRadians(alpha_horizontal / 2))        * sin(DegreesToRadians(horizontal_rotation))* sin(DegreesToRadians(vertical_rotation));
        float z_step = step_size * sin(DegreesToRadians(alpha_vertical / 2))                                                      * sin(DegreesToRadians(horizontal_rotation))* sin(DegreesToRadians(vertical_rotation));

        int NothingHit = 1;

        int x = 0;
        int y = 0;
        int z = 0;

        while(NothingHit == 1){
            NothingHit = (world[x + position[0]][y + position[1]][z + position[2]] < 1);

            if(strcmp(mode, calculate) == 0){
              ProjectionMap = world[x + position[0]][y + position[1]][z + position[2]];
            }

            if(strcmp(mode,print) == 0){
              FullPixel_color(world[x + position[0]][y + position[1]][z + position[2]]);
              printf("  ");
            }

            x = x + x_step;
            y = y + y_step;
            z = z + z_step;
        }

      }
      if(strcmp(mode,print) == 0){
        printf("\n");
      }
    }
  }

}
