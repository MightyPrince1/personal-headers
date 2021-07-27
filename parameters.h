/*
list of parameters of headers

these parameters have to be set before doing #include "<their respective header>"

as a best practise define them before including any headers

Do not #include this header!
*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#ifdef __cplusplus
  extern "C"{
#endif

//used by multiple headers
#define ERROR_RESULTS_IN_EXIT
#define THREADING_AS_DEFAULT

//CrossPlatform
#define NO_ACRONYM_INPUT
#define USING_WINDOW
#define USING_TERMINAL_INPUT

//ConsoleScreen
#define DISABLE_CONSOLE_SCREEN_IF_USING_WINDOW

//projection
#define CALCULATE_INSTEAD_OF_RAM

//AdMath
#define USING_PERCENTAGE
#define USING_RADIANS

#ifdef __cplusplus
  }
#endif
#endif
