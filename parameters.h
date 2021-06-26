/*
list of parameters of headers

Do not use it
*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#ifdef __cplusplus
  extern "C"{
#endif

//used by multiple headers
#define ERROR_RESULTS_IN_EXIT

//CrossPlatform
#define USING_WINDOW
#define USING_TERMINAL_INPUT

//ConsoleScreen
#define DISABLE_CONSOLE_SCREEN_IF_USING_WINDOW

//projection
#define CALCULATE_INSTEAD_OF_RAM

#ifdef __cplusplus
  }
#endif
#endif
