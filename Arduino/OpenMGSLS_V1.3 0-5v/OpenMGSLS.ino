/*
 Name:		OpenMGSLS.ino
 Created:	2016/11/23 12:18:13
 Author:	liaoq
*/

// the setup function runs once when you press reset or power the board
#include <SPI.h>
#include "config.h"
#include "ComData.h"
#include "Planter.h"
#include "XYMG.h"

ComDataClass ComData(DELAY_SERIAL);
PlanterClass Planter(ANGLE_MG_MAX,BASE_VOLTAGE,SPEED_XY,DIS_F_THETA,DIS_XYMOTOR,CYCLE_LNTERPOLARION);
XYMGClass XYMG(SSPIN_XY,SPEED_SPI,CYCLE_LNTERPOLARION);

unsigned short * DAValArry_X;
unsigned short * DAValArry_Y;


int Times;

void setup() {
	Serial.begin(SPEED_SERIAL);
}

// the loop function runs over and over again until power down or reset
void loop() {
	ComData.Get();
	if (ComData.NeedMove_XY) {
		Planter.Plane_XY(ComData.GCode_Point, DAValArry_X, DAValArry_Y,&Times);
		XYMG.Move(DAValArry_X, DAValArry_Y,Times);
	}
}

