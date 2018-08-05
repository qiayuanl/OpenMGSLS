// Command.h

#ifndef _COMMAND_h
#define _COMMAND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "config.h"
extern float GCodeVal_floatArry_Command[6];
extern bool NeedMove_boolArry_Command[6];


extern int GCodeBuffLen_int_Command;
extern int GCodeBuffGetCouter_int_Command;
extern int GCodeBuffProcessCouter_int_Commmand;


void Init_Command();
void Get_Command();
void Process_Command();
inline bool Command_Key(char key);
#endif

