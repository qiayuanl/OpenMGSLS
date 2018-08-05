// XYMG.h

#ifndef _XYMG_h
#define _XYMG_h


#include "arduino.h"
#include "DueTimer.h"
#include "Planter.h"
#include "XYMG.h"
#include "SPI.h"
#include <SPI.h>



class XYMGClass
{

 protected:
	static int Pin_XY;
	 const int Speed_SPI;
	 const int Cycle_Linerpolarion;
	static unsigned short * Arry_X;
	static unsigned short * Arry_Y;
	static bool IsMoving;
	static int Times_Now;
 public:
	 static unsigned int T;
	 XYMGClass(int p,int s,int c);
	 void init();
	 static void Write(unsigned short x, unsigned short y);
	 void Move(unsigned short *x,unsigned short *y,int Times);
	static void Move_XY();

};



#endif

