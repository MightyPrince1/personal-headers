/*
											DelayMS(in milliseconds)
											DelayT(time, time_type)
													time_types
														-MIN or MINUTE
														-SEC or SECOND
														-MS or MILLISECOND
														#usage of full words only if #define NO_ACRONYM_INPUT

#usage of following only if #define USING_WINDOW before including this header
	(unsigned long)			CrossRGB(int r, int g, int b);
	(unsigned long)			HexToRGB(int hex_value);

	(unsigned long)			default_foreground_color
	(unsigned long)			default_background_color

#if you want no ConsoleScreen output while having a window do #define DISABLE_CONSOLE_SCREEN_IF_USING_WINDOW

  (int / use as bool) DisplayExists()
                      //if you do #define ERROR_RESULTS_IN_EXIT it will exit instead of running without window stuff
                      WindowCreate(int Width, int Height)
                      WindowWait()
                      WindowWrite(int x, int y, int R, int G, int B)
                      //if you don't want to change the color use out of bounds RGB values
											WindowResize(x,y)
	(int / use as bool) WindowSizeChanged
											WindowUpdateSize()
											WindowClear()
                      WindowClose()

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

#include "AdMath.h"


void DelayMS(int time){
	long pause;

	clock_t time1,time2;
	pause = time * (CLOCKS_PER_SEC / 1000);
	time2 = time1 = clock();

	while( (time1-time2) < pause ){
		time1 = clock();
	}
}

void DelayT(int time, char time_type[]){
	#ifndef NO_ACRONYM_INPUT
		char MIN[] = "MIN";
		char SEC[] = "SEC";
		char MS[] = "MS";
	#else
		char MINUTE[] = "MINUTE";
		char SECOND[] = "SECOND";
		char MILLISECOND[] = "MILLISECOND"
	#endif

	long pause;

	clock_t time1,time2;
	#ifndef NO_ACRONYM_INPUT
		pause = time * (CLOCKS_PER_SEC / 0.1 *(strcmp(time_type, MIN) == 0) + 1 * (strcmp(time_type, SEC) == 0) + 1000 * (strcmp(time_type, MS) == 0));
	#else
		pause = time * (CLOCKS_PER_SEC / 0.1 *(strcmp(time_type, MINUTE) == 0) + 1 * (strcmp(time_type, SECOND) == 0) + 1000 * (strcmp(time_type, MILLISECOND) == 0));
	#endif
	time2 = time1 = clock();

	while( (time1-time2) < pause ){
		time1 = clock();
	}

}



	//crosswindow
#ifdef USING_WINDOW
	#ifdef UNIX
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

		#ifdef _MSC_VER
		#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
		#endif

	#endif

	unsigned long CrossRGB(int r, int g, int b){
		#ifdef __WIN32
			return RGB(int r, int g, int b);
		#else
 	  	return InBoundsInt(b,0,255) + (InBoundsInt(g,0,255)<<8) + (InBoundsInt(r,0,255)<<16);
		#endif
  }

	/*unsigned long HexToRGB(unsigned long hex_value){
		int rgb_values[3];
		#ifdef __WIN32
			sscanf(hex_value, "%02x%02x%02x", &rgb_values[2], &rgb_values[1], &rgb_values[0]);
		#else
			sscanf(hex_value, "%02x%02x%02x", &rgb_values[0], &rgb_values[1], &rgb_values[2]);
		#endif

		return *rgb_values;
	}*/

	//for now in hex code
	unsigned long default_foreground_color = 0x000000;
	unsigned long default_background_color = 0xffffff;

   int DisplayExists(){
		#ifdef UNIX
    	if(d == NULL){
      	printf("Can't open display! Using WSL?\n");
      	#ifdef ERROR_RESULTS_IN_EXIT
        	exit("FAILED TO CREATE WINDOW");
      	#endif

				getchar();
      	return 0;
    	}

			return 1;
		#endif
  }

	int WindowWidth = 0;
	int WindowHeight = 0;

	void WindowCreate(int width, int height){
		#ifdef UNIX
			d = XOpenDisplay(NULL);

			s = DefaultScreen(d);
			w = XCreateSimpleWindow(d,RootWindow(d, s), 10, 10, width, height, 1,
															default_background_color, default_foreground_color);

			XSelectInput(d, w, ExposureMask | ButtonPressMask | KeyPressMask);
			XMapWindow(d, w);
			XInternAtom(d, "WM_DELETE_WINDOW", False);


      //create GC
      gc = XCreateGC(d, w, 0, 0);

      XMapRaised(d, w);
		#endif

		WindowWidth = width;
		WindowHeight = height;

		#define WINDOW_INITIALISED
	}

	void WindowWrite(int x, int y, int r, int g, int b){
    #ifdef UNIX
      XSetForeground(d, gc, CrossRGB(r,g,b));

		  XDrawPoint(d,w,gc, x, y);
    #endif
	}

	void WindowDisplayObjectRectangle(int x, int y, int lenght_along_x, int lenght_along_y, int r, int g, int b){
		#ifdef UNIX
			XSetForeground(d, gc, CrossRGB(r,g,b));

			XFillRectangle(d,w,gc,x,y,lenght_along_y,lenght_along_x);
		#endif
	}

	void WindowDisplayObjectPolygon(int r, int g, int b){
		if(!(r < 0 || r > 255 || g < 0 || g > 255 ||b < 0 || b > 255)){
			#ifdef UNIX
				XSetForeground(d, gc, CrossRGB(r,g,b));
			#endif
		}


	}

	void WindowResize(int Width, int Height){
		#ifdef UNIX

			XResizeWindow(d,w,Width,Height);
		#endif
	}

	int WindowSizeChanged = 0;

	void WindowUpdateSize(){
		WindowSizeChanged = 0;
		#ifdef UNIX
			XWindowAttributes wndAttr;

			XGetWindowAttributes(d,w,&wndAttr);

			if(WindowWidth != wndAttr.width || WindowHeight != wndAttr.height){
				XResizeWindow(d,w,wndAttr.width,wndAttr.height);
				WindowSizeChanged = 1;
			}
		#endif
	}

	void WindowWait(){
		#ifdef UNIX

			XNextEvent(d, &e);
		#endif
	}

	void WindowClear(){
		#ifdef UNIX

			XClearWindow(d,w);
		#endif
	}

	void WindowClose(){
		#ifdef UNIX

			XFreeGC(d, gc);
      XDestroyWindow(d, w);
			XCloseDisplay(d);
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
	#ifdef __WIN32
		system("PowerShell");
		system(command);
		system("exit")
	#else
		system(command);
  #endif
}



#ifdef __cplusplus
}
#endif

#endif /*CROSSPLATFORM_H*/
