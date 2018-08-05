// Planter.h

#ifndef _PLANTER_h
#define _PLANTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "config.h"
#include "Command.h"

extern int Times_LinearLnterpolation_int_Planter;
extern unsigned short* DAValBufferX_ushortPointer_Planter[2];
extern unsigned short* DAValBufferY_ushortPointer_Planter[2];

void Plane_XY(bool bufferNumber);
inline unsigned short DisToDA_X(float x, float y);
inline unsigned short DisToDA_Y(float y);

#endif
