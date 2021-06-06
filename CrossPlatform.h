/*
#usage of following only if #define USING_WINDOW before including this header
	(unsigned long)			CrossRGB(int r, int g, int b);

	(unsigned long)			default_foreground_color
	(unsigned long)			default_background_color

  (int / use as bool) WindowCreationPossible()
                      //if you do #define ERROR_RESULTS_IN_EXIT it will exit instead of running without window stuff
                      WindowCreate(int Width, int Height)
                      WindowWait()
                      WindowWrite(int x, int y, int R, int G, int B)
                      //if you don't want to change the color use out of bunds RGB values
											WindowResize()
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
#include <stdlib.h>
#include <string.h>



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
	#ifdef __linux__
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
	#endif

	#ifdef __WIN32
		#include <windows.h>
	#endif

	unsigned long CrossRGB(int r, int g, int b){
		#ifdef __WIN32
			return RGB(int r, int g, int b);
		#endif
 	  return b + (g<<8) + (r<<16);
  }

	//for now in hex code
	unsigned long default_foreground_color = 0x000000;
	unsigned long default_background_color = 0xffffff;

  int WindowCreationPossible(){
		#ifdef USING_X11
    	if(d == NULL){
      	#undef USING_X11
      	printf("Can't open display! Using WSL?\n");
      	#ifdef ERROR_RESULTS_IN_EXIT
        	exit(1);
      	#endif

				getchar();
      	return 0;
    	}
		#endif
  }

	void WindowCreate(int width, int height){
		#ifdef __linux__
			d = XOpenDisplay(NULL);

      if(d == NULL){
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
      if(d == NULL){
        return;
      }

      if(!(r < 0 || r > 255 || g < 0 || g > 255 ||b < 0 || b > 255)){
        XSetForeground(d, gc, CrossRGB(r,g,b));
      }

		  XDrawPoint(d,w,gc, x, y);
    #endif
	}

	void WindowResize(int Width, int Height){
		#ifdef __linux__
			if(d == NULL){
				return;
			}

			XResizeWindow(d,w,x,y);
		#endif
	}

	void WindowWait(){
		#ifdef __linux__
      if(d == NULL){
        return;
      }
			XNextEvent(d, &e);
		#endif
	}

	void WindowClear(){
		#ifdef __linux__
			if(d == NULL){
				return;
			}

			XClearWindow(d,w);
		#endif
	}

	void WindowClose(){
		#ifdef __linux__
      if(d == NULL){
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

	//currently not working
	#if defined(USING_X11) && !defined(USING_TERMINAL_INPUT)
		 XNextEvent(d, &e);

		 if (e.type == KeyPress){
			 if(e.xkey.keycode == input){
				 PressedKey = input;
				 pressed = 1;
			 }
		 }

	#else
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

#endif /*CROSSPLATFORM_H*/
