/*
#usage of following only if #define USING_WINDOW before including this header
	(unsigned long)			RGB(int r, int g, int b);

	(unsigned long)			default_foreground_color
	(unsigned long)			default_background_color

  (int / use as bool) WindowCreationPossible()
                      //if you do #define ERROR_RESULTS_IN_EXIT it will exit instead of running without window stuff
                      WindowCreate(int Width, int Height)
                      WindowUpdate()
                      WindowWrite(int x, int y, int R, int G, int B)
                      //if you don't want to change the color use out of bunds RGB values
											WindowClear()
                      WindowClose()

if you want no ConsoleScreen output while having a window do #define DISABLE_CONSOLE_SCREEN_IF_USING_WINDOW
#

											delay(in milliseconds)
	(int / use as bool) WaitForInput
	(char)							PressedKey
											KeyPressed()
											CrossSystem()
*/
#ifndef CROSSPLATFORM_H
#define CROSSPLATFORM_H

#ifdef __cplusplus
extern "C"{
#endif



#include <time.h>
#include <stdio.h>

void delay(int time){
	long pause;

	clock_t time1,time2;
	pause = time * (CLOCKS_PER_SEC / 1000);
	time2 = time1 = clock();

	while( (time1-time2) < pause ){
		time1 = clock();
	}
}



	//crosswindow
#ifdef USING_WINDOW
  unsigned long RGB(int r, int g, int b){
 	  return b + (g<<8) + (r<<16);
  }
	//for now in hex code
	unsigned long default_foreground_color = 0x000000;
	unsigned long default_background_color = 0xffffff;


	#ifdef __linux__
    #define USING_X11
		#include <X11/Xlib.h>
		#include <X11/Xcms.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
		#include <string.h>

		Display *d;
		Window w;
		XEvent e;
    int s;
    KeySym key;
    GC gc;


	#elif __WIN32
		#include <windows.h>

	#endif
  int WindowCreationPossible(){
    if(d == NULL){
      #undef USING_X11
      printf("Can't open display! Using WSL?\n");
      getchar();
      #ifdef ERROR_RESULTS_IN_EXIT
        exit(1);
      #endif

      return 0;
    }
  }

	void WindowCreate(int width, int height){
		#ifdef USING_X11
			d = XOpenDisplay(NULL);

      if(WindowCreationPossible == 0){
        return;
      }

			s = DefaultScreen(d);
			w = XCreateSimpleWindow(d,RootWindow(d, s), 10, 10, width, height, 1,
															default_background_color, default_foreground_color);

			XSelectInput(d, w, ExposureMask | ButtonPressMask | KeyPressMask);
			XMapWindow(d, w);

      //create GC
      gc = XCreateGC(d, w, 0, 0);

      XMapRaised(d, w);
		#endif

		#define WINDOW_INITIALISED
	}

  int PixelWidth = 1;
  int PixelHeight = 1;

	void WindowWrite(int x, int y, int r, int g, int b){
    #ifdef USING_X11
      if(WindowCreationPossible == 0){
        return;
      }

      if(!(r < 0 || r > 255 || g < 0 || g > 255 ||b < 0 || b > 255)){
        XSetForeground(d, gc, RGB(r,g,b));
      }
		  XDrawRectangle(d,w,gc, x, y, PixelWidth, PixelHeight);
    #endif
	}

	void WindowUpdate(){
		#ifdef USING_X11
      if(WindowCreationPossible == 0){
        return;
      }
			XNextEvent(d, &e);
		#endif
	}

	void WindowClear(){
		#ifdef USING_X11
			XClearWindow(d,w);
		#endif
	}

	void WindowClose(){
		#ifdef USING_X11
      if(WindowCreationPossible == 0){
        return;
      }

			XFreeGC(d, gc);
      XDestroyWindow(d, w);
			XCloseDisplay(d);
		#endif

		#ifdef DISABLE_CONSOLE_SCREEN_IF_USING_WINDOW
			#undef DISABLE_CONSOLE_SCREEN_IF_USING_WINDOW
		#endif

		#undef WINDOW_INITIALISED
	}

#endif



int WaitForInput = 0;
char PressedKey;

int KeyPressed(char input){
	int pressed = 0;
	#ifdef __WIN32
		#include <windows.h>
		if(GetKeyState(input) < 0){
			pressed = 1;
		}
  #endif

	#ifdef USING_X11
		 XNextEvent(d, &e);
     XRefreshKeyboardMapping();

     char key_output;

		 if(event.type == KeyPress && XLookupString(&event.xkey, key_output, 255, &key,0) == 1){

			 if(key_output == input){
				 pressed = 1;
			 }
		 }

	#else

		#include <stdlib.h>

		if(WaitForInput == 0){
			system("/bin/stty raw");
		}

		PressedKey = getchar();

		if(WaitForInput == 0){
			system("/bin/stty cooked");
		}

		PressedKey = PressedKey;
		pressed = (input == PressedKey);

	#endif

	return pressed;
}



void CrossSystem(char command[50]){
	#include <stdlib.h>
	#include <string.h>

	char dir[3] = "dir";

	if(strcmp(command,dir) == 0){
		#ifdef __WIN32
			system("dir");
		#eldef __linux__
			system("ls");
		#endif
	}
	else{
		#ifdef __WIN32
			system("PowerShell");
			system(command);
			system("exit")
		#else
			system(command);
    #endif
	}
}



#ifdef __cplusplus
}
#endif

#endif
