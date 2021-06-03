/*
				 							delay(in milliseconds)
	(int / usa as bool)	WaitForInput
	(char) 							PressedKey
				 							KeyPressed()
				 							CrossSystem()
*/
#ifndef CROSSPLATFORM_H
#define CROSSPLATFORM_H

#ifdef __cplusplus
extern "C"{
#endif

#include <time.h>



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
		#define USING_X11

		#include <X11/Xlib.h>
		#include <X11/Xcms.h>
		#include <string.h>

		Display *d;
		Window w;
		XEvent e;


	#elif __WIN32
		#define USING_WIN32

		#include <windows.h>

	#endif

	void WindowCreate(){
		#ifdef USING_X11
			d = XOpenDisplay(NULL);

			if(d == NULL){
				printf("Can't open display! Using WSL?\n");
				exit(1);
			}

			s = DefaultScreen(d);
			w = XCreateSimpleWindow(d,RootWindow(d, s), 10, 10, 100, 100, 1,
															BlackPixel(d, s), WhitePixel(d, s));

			XSelectInput(d, w, ExposureMask | KeyPressMask);
			XMapWindow(d, w);

		#endif
	}

	void WindowWrite(int x, int y, int r, int g, int b){

	}

	void WindowUpdate(){
		#ifdef USING_X11
			XNextEvent(d, &e);
		#endif
	}

	void WindowClose(){
		#ifdef USING_X11
			XCloseDisplay(d);
		#endif
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

	#elif USING_X11
		 XNextEvent(display, &event);

		 if (event.type == KeyPress){

			 if(event.xkey.keycode == input){
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
		int UsedWindows = 0;
		#ifdef __WIN32
			UsedWindows = 1;
			system("PowerShell");
			system(command);
			system("exit")
		#endif
		if(UsedWindows == 0){
			system(command);
		}
	}
}



#ifdef __cplusplus
}
#endif

#endif
