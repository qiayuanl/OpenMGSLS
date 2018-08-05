// Command.h

#ifndef _COMMAND_h
#define _COMMAND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "config.h"
extern float GCode_Arry_Command[3];
extern bool NeedPlane_XY_bool_Command;
;

void Command_Init();
void Command_Get();
inline bool Command_Key(char key);
#endif

