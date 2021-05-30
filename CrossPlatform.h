/*
				 							delay(in milliseconds)
	(int / usa as bool)	WaitForInput
	(char) 							PressedKey
				 							KeyPressed()
				 							CrossSystem()
*/
#ifndef CROSSPLATFORM_H
#define CROSSPLATFORM_H

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

int WaitForInput = 0;
char PressedKey;

int KeyPressed(char input){
	int pressed = 0;

	#ifdef __linux__
		#include <stdlib.h>

		char  SystemInput;

		if(WaitForInput == 0){
			system("/bin/stty raw");
		}

		SystemInput = getchar();

		if(WaitForInput == 0){
			system("/bin/stty cooked");
		}

		PressedKey = SystemInput;
		pressed = (input == SystemInput);

	#elif _WIN32
		#include <windows.h>
		if(GetKeyState(input) < 0){
			pressed = 1;
		}
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

#endif
