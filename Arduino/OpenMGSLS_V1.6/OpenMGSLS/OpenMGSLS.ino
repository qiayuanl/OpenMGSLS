/*
 Name:		OpenMGSLS.ino
 Created:	2017/02/12 15:35:51
 Author:	¡Œ«¢‘¥
 Version:	1.6
*/

#include <SPI.h>
#include "XYMG.h"
#include "Planter.h"
#include "Command.h"
#include "Stepper.h"

bool PlanterBufferNumber_bool = false;//the daval buffer have 2 member
bool XYMGBufferNumber_bool = false;

// the setup function runs once when you press reset or power the board
void setup() {
	Command_Init();
	XYMG_Init();
	Stepper_Init();
}
// the loop function runs over and over again until power down or reset
void loop() {
	Command_Get();
	PlaneAndMove();
}

void PlaneAndMove() {
	if (NeedMove_bool_Command[0]) {
		NeedMove_bool_Command[0] = false;
		PlanterBufferNumber_bool = !PlanterBufferNumber_bool;

		if (PlanterBufferNumber_bool == XYMGBufferNumber_bool) {
			XYMGBufferNumber_bool = !XYMGBufferNumber_bool;

			while (IsMoving_XY) {
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
		while (IsMoving_XY) {
			delay(1);
		}
		Times_LinearLnterpolation_int_XYMG = Times_LinearLnterpolation_int_Planter;
		DAValMoveX_ushortPointer_XYMG = DAValBufferX_ushortPointer_Planter[XYMGBufferNumber_bool];
		DAValMoveY_ushortPointer_XYMG = DAValBufferY_ushortPointer_Planter[XYMGBufferNumber_bool];
		XYMG_StartMove(NeedOpen_Laser);
		NeedOpen_Laser = false;
	}

	if (NeedMove_bool_Command[1]) {
		NeedMove_bool_Command[1] = false;
		if (abs(GCode_Arry_Command[2] - Z_Position_Old) < 0.1)
			StepperB_StartMove(0.15);
		else
			StepperB_StartMove((GCode_Arry_Command[2] - Z_Position_Old)*1.2);
		while (IsMoving_B)
			delay(1);
		 
		StepperC_StartMove(-(GCode_Arry_Command[2] - Z_Position_Old));
		while (IsMoving_C)
			delay(1);
		 
		StepperA_StartMove(Stepper_A_DISTANCE_MAX);
		while (IsMoving_A)
			delay(1);

		StepperA_StartMove(-Stepper_A_DISTANCE_MAX);
		while (IsMoving_A)
			delay(1);

		Z_Position_Old = GCode_Arry_Command[2];
	}
	else if (NeedMove_bool_Command[2]) {
		NeedMove_bool_Command[2] = false;

		StepperA_StartMove(Stepper_A_DISTANCE_MAX);
		while (IsMoving_A)
			delay(1);
		StepperA_StartMove(-Stepper_A_DISTANCE_MAX);
		while (IsMoving_A)
			delay(1);
	}
	else if (NeedMove_bool_Command[3]) {
		NeedMove_bool_Command[3] = false;
		StepperB_StartMove(GCode_Arry_Command[4]);
		while (IsMoving_B) 
			delay(1);
	}
	else if (NeedMove_bool_Command[4]) {
		NeedMove_bool_Command[4] = false;
		StepperC_StartMove(GCode_Arry_Command[5]);
		while (IsMoving_C) 
			delay(1);
	}
}