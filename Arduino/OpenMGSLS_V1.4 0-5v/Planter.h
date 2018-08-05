// Planter.h

#ifndef _PLANTER_h
#define _PLANTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "config.h"
extern int Times_LinearLnterpolation_int_Planter;
extern unsigned short* DAValX_ushortPointer_Planter;
extern unsigned short* DAValY_ushortPointer_Planter;
extern bool NeedMove_XY_bool_Command;

void Plane_XY(float point[3]);
inline unsigned short DisToDA_X(float x, float y);
inline unsigned short DisToDA_Y(float y);

#endif

