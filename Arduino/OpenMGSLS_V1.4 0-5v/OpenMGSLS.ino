/*
 Name:		OpenMGSLS.ino
 Created:	2017/1/16 23:09:56
 Author:	liaoq
 Version:	1.4
*/

// the setup function runs once when you press reset or power the board
#include <SPI.h>
#include "XYMG.h"
#include "Planter.h"
#include "Command.h"

void setup() {
	Command_Init();
	XYMG_Init();
}
// the loop function runs over and over again until power down or reset
void loop() {
	Command_Get();
	if (NeedPlane_XY_bool_Command) {
		Plane_XY(GCode_Arry_Command);
		NeedPlane_XY_bool_Command = false;
		if (NeedMove_XY_bool_Command)
			XYMG_StartMove();
		NeedMove_XY_bool_Command = false;
	}
	while (1) {
		delay(1);
		if (!IsMoving)
			break;
	}
}

