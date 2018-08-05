// Planter.h

#ifndef _PLANTER_h
#define _PLANTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "XYMG.h"

class PlanterClass
{
 protected:
	 float Goal_X, Goal_Y, Start_X, Start_Y;
	 float Dis_X, Dis_Y;//how far between Goal and Start
	 float Plus_X, Plus_Y;//how many long in once LinearLnterpolation
	 float Plane_X, Plane_Y;
	 float RadVal_X, RadVal_Y;
	 float Countervail_X;

	 int Times_LinearLnterpolation;
	 int T_LinearLnterpolation;

	 const int Cycle;
	 const float Speed;
	 const float RadVal_MaxAngle;
	 const float Countervail_Voltage;
	 const float Dis_F_Theta;
	 const float Dis_XYMotor;

 public:
	 PlanterClass(float a, float v, float s,float df,float dx ,int c);
	 inline void Plane_XY
	 (float point[3], unsigned short * x, unsigned short * y, int * t);
	int DisToDA_X(float x, float y);
	int DisToDA_Y(float y);

};

#endif

