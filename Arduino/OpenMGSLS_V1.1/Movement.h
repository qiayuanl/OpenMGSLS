// Movement.h

#ifndef _MOVEMENT_h
#define _MOVEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
void Movement_setup();
int X_DistanToDA(float X_Dis, float Y_Dis);
int Y_DistanToDA(float dis);
float X_Countervail(float X_Dis, float Y_Dis);
void Move_XY();
void Move_X(float X_Goal, float Y_Goal);
void Move_Y(float Y_Goal);
#endif

