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

extern int DAValBufferPlanCouter_int_Planter;
extern int DAValBufferMoveCouter_int_Planter;
extern int DAValBufferLen_int_Planter;

extern bool NeedOpenLaser_boolArry_Planter[DA_VAL_BUFF_SIZE];
extern int Times_LinearLnterpolation_intArry_Planter[DA_VAL_BUFF_SIZE];
extern unsigned short DAValBufferX_ushortPointer_Planter[DA_VAL_BUFF_SIZE][DA_VAL_ARRY_SIZE];
extern unsigned short DAValBufferY_ushortPointer_Planter[DA_VAL_BUFF_SIZE][DA_VAL_ARRY_SIZE];

void PlaneXY_Planter();
unsigned short DisToDA_X(float x, float y);
unsigned short DisToDA_Y(float y);

#endif
