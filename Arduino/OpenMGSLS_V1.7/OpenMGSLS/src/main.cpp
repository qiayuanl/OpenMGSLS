/*
 Name:		OpenMGSLS.ino
 Created:	2017/04/25 23:48:16
 Author:	¡Œ«¢‘¥
 Version:	1.7
*/
#include <SPI.h>
#include "XYMG.h"
#include "Planter.h"
#include "Command.h"
#include "Stepper.h"

// the setup function runs once when you press reset or power the board
void setup() {
	Init_Command();
	Init_XYMG();
	Init_Stepper();
}
// the loop function runs over and over again until power down or reset
void loop() {
	if (GCodeBuffLen_int_Command < (GCODE_BUFF_SIZE - 1)) {
		Get_Command();
	}
	if (GCodeBuffLen_int_Command && (DAValBufferLen_int_Planter < (DA_VAL_BUFF_SIZE - 1))) {
		Process_Command();
		if (NeedMove_boolArry_Command[0]) {
			NeedMove_boolArry_Command[0] = false;
			NeedOpenLaser_boolArry_Planter[DAValBufferPlanCouter_int_Planter] = NeedMove_boolArry_Command[1];
			NeedMove_boolArry_Command[1] = false;
			PlaneXY_Planter();
		}
		else if (NeedMove_boolArry_Command[2]) {
			NeedMove_boolArry_Command[2] = false;
			if (abs(GCodeVal_floatArry_Command[2] - Z_Position_Old) < 0.1)
				StepperB_StartMove(0.15);
			else
				StepperB_StartMove((GCodeVal_floatArry_Command[2] - Z_Position_Old)*1.3);
			while (IsMoving_B)
				delay(1);

			StepperC_StartMove(-(GCodeVal_floatArry_Command[2] - Z_Position_Old));
			while (IsMoving_C)
				delay(1);

			StepperA_StartMove(Stepper_A_DISTANCE_MAX);
			while (IsMoving_A)
				delay(1);

			StepperA_StartMove(-Stepper_A_DISTANCE_MAX);
			while (IsMoving_A)
				delay(1);

			Z_Position_Old = GCodeVal_floatArry_Command[2];
		}
		else if (NeedMove_boolArry_Command[3]) {
			NeedMove_boolArry_Command[3] = false;

			StepperA_StartMove(Stepper_A_DISTANCE_MAX);
			while (IsMoving_A)
				delay(1);
			StepperA_StartMove(-Stepper_A_DISTANCE_MAX);
			while (IsMoving_A)
				delay(1);
		}
		else if (NeedMove_boolArry_Command[4]) {
			NeedMove_boolArry_Command[4] = false;
			StepperB_StartMove(GCodeVal_floatArry_Command[4]);
			while (IsMoving_B)
				delay(1);
		}
		else if (NeedMove_boolArry_Command[5]) {
			NeedMove_boolArry_Command[5] = false;
			StepperC_StartMove(GCodeVal_floatArry_Command[5]);
			while (IsMoving_C)
				delay(1);
		}

	}
	if (DAValBufferLen_int_Planter && !IsMoving_XY) {
		DAValMoveX_ushortPointer_XYMG = DAValBufferX_ushortPointer_Planter[DAValBufferMoveCouter_int_Planter];
		DAValMoveY_ushortPointer_XYMG = DAValBufferY_ushortPointer_Planter[DAValBufferMoveCouter_int_Planter];
		NeedOpenLaser_bool_XYMG = NeedOpenLaser_boolArry_Planter[DAValBufferMoveCouter_int_Planter];
		Times_LinearLnterpolation_int_XYMG = Times_LinearLnterpolation_intArry_Planter[DAValBufferMoveCouter_int_Planter];
		XYMG_StartMove();
		DAValBufferMoveCouter_int_Planter = (DAValBufferMoveCouter_int_Planter + 1) % DA_VAL_BUFF_SIZE;
		DAValBufferLen_int_Planter--;
	}
}
