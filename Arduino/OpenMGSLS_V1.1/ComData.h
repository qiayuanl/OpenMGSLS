// ComData.h

#ifndef _COMDATA_h
#define _COMDATA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
extern bool Move;
extern String ComData;
extern float GCode_Point_Com[4];

float Get_KeyVal();
bool Find_Key(char key);
void Get_Key();
void Get_Comdata();

#endif

