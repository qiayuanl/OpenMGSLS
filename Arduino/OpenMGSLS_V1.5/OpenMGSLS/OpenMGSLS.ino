/*
 Name:		OpenMGSLS.ino
 Created:	2017/1/20 16:36:51
 Author:	liaoq
 Version:	1.5
*/

// the setup function runs once when you press reset or power the board
#include <SPI.h>
#include "XYMG.h"
#include "Planter.h"
#include "Command.h"

bool PlanterBufferNumber_bool = false;//the daval buffer have 2 member
bool XYMGBufferNumber_bool = false;

bool BufferVal_int = false;

void setup() {
	Command_Init();
	XYMG_Init();
}
// the loop function runs over and over again until power down or reset
void loop() {
	Command_Get();
	if (NeedPlane_XY_bool_Command) {
		PlanterBufferNumber_bool = !PlanterBufferNumber_bool;

		if (PlanterBufferNumber_bool == XYMGBufferNumber_bool) {
			XYMGBufferNumber_bool = !XYMGBufferNumber_bool;

			while (IsMoving) {
				delay(1);
			}
			Times_LinearLnterpolation_int_XYMG = Times_LinearLnterpolation_int_Planter;
			DAValMoveX_ushortPointer_XYMG = DAValBufferX_ushortPointer_Planter[XYMGBufferNumber_bool];
			DAValMoveY_ushortPointer_XYMG = DAValBufferY_ushortPointer_Planter[XYMGBufferNumber_bool];
			XYMG_StartMove(NeedOpen_Laser);
			NeedOpen_Laser = false;
		}

		Plane_XY(PlanterBufferNumber_bool);

		XYMGBufferNumber_bool = !XYMGBufferNumber_bool;
		while (IsMoving) {
			delay(1);
		}
		Times_LinearLnterpolation_int_XYMG = Times_LinearLnterpolation_int_Planter;
		DAValMoveX_ushortPointer_XYMG = DAValBufferX_ushortPointer_Planter[XYMGBufferNumber_bool];
		DAValMoveY_ushortPointer_XYMG = DAValBufferY_ushortPointer_Planter[XYMGBufferNumber_bool];
		XYMG_StartMove(NeedOpen_Laser);
		NeedOpen_Laser = false;
	}

}
