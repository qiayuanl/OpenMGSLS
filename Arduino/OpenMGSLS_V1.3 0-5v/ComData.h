// ComData.h

#ifndef _COMDATA_h
#define _COMDATA_h


#include "arduino.h"
#include "Planter.h"

class ComDataClass
{
 protected:
	 int KeyStart;
	 int KeyEnd;
	 const int Delay;
	 String GCode;
	 struct 
	 {
		 String S = "";
		 float F = 0;
	 }KeyVal;
	 bool Key(char key);

 public:
	 bool NeedMove_XY;
	 float GCode_Point[3];//{X,Y,E}		
	 ComDataClass(int d);
	 void Get();
};

#endif

