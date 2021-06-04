#define USING_WINDOW
#define ERROR_RESULTS_IN_EXIT
#define DISABLE_CONSOLE_SCREEN_IF_USING_WINDOW

#include "ConsoleScreen.h"

int main(){
	ResizeScreenSpace(28,60);
	WindowCreate(100,100);
	//WindowCreationPossible();

	int x = 0;
	int y = 0;

	while(1){
		if(ScreenUpdate == 1){
			WindowClear();
			ScreenClear();
			WindowWrite(x,y,28,119,22);
			screen("write","FullPixel",x,y,8);
			WindowUpdate();
			ScreenPrint();
		}

		//input
		{
			KeyPressed(' ');

			if(PressedKey == 'w'){
				x --;

				ScreenUpdate = 1;
			}

			if(PressedKey == 'a'){
				y --;

				ScreenUpdate = 1;
			}

			if(PressedKey == 's'){
				x ++;

				ScreenUpdate = 1;
			}

			if(PressedKey == 'd'){
				y ++;

				ScreenUpdate = 1;
			}

			if(PressedKey == 'q'){
				WindowClose();
				CrossSystem("clear");
				return 0;
			}

			if(PressedKey == 'e'){
				ConsoleScreenSettings();

				ScreenUpdate = 1;
			}
		}
	}
}
