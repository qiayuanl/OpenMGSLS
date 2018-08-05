/*
 Name:		OpenMGSLS.ino
 Created:	2018/1/6 21:51:00
 Author:	QiayuanLiao
 Version:	1.8
*/
#include <Arduino.h>
#include <SPI.h>
#include "XYMG.h"
#include "Planner.h"
#include "Command.h"
#include "Stepper.h"
#include "Heating.h"
// the setup function runs once when you press reset or power the board
void setup() {
	Init_Command();
	Init_XYMG();
	Init_Stepper();
//	Init_Heating();
}
// the loop function runs over and over again until power down or reset
void loop() {
	if (GCodeBuffLen_int_Command < (GCODE_BUFF_SIZE - 1)) {
		Get_Command();
	}
	if (GCodeBuffLen_int_Command && (DAValBufferLen_int_Planner < (DA_VAL_BUFF_SIZE - 1))) {
		Process_Command();
		if (NeedMove_boolArry_Command[0]) {
			NeedMove_boolArry_Command[0] = false;
			NeedOpenLaser_boolArry_Planner[DAValBufferPlanCouter_int_Planner] = NeedMove_boolArry_Command[1];
			NeedMove_boolArry_Command[1] = false;
			PlaneXY_Planner();
		}
		else if (NeedMove_boolArry_Command[2]) {
			NeedMove_boolArry_Command[2] = false;
			if (abs(GCodeVal_floatArry_Command[2] - Z_Position_Old) < 0.1)
				StepperB_StartMove(0.2);
			else
				StepperB_StartMove((GCodeVal_floatArry_Command[2] - Z_Position_Old)*1.5);
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
	if (DAValBufferLen_int_Planner && !IsMoving_XY) {
		DAValMoveX_ushortPointer_XYMG = DAValBufferX_ushortPointer_Planner[DAValBufferMoveCouter_int_Planner];
		DAValMoveY_ushortPointer_XYMG = DAValBufferY_ushortPointer_Planner[DAValBufferMoveCouter_int_Planner];
		NeedOpenLaser_bool_XYMG = NeedOpenLaser_boolArry_Planner[DAValBufferMoveCouter_int_Planner];
		Times_LinearLnterpolation_int_XYMG = Times_LinearLnterpolation_intArry_Planner[DAValBufferMoveCouter_int_Planner];
		XYMG_StartMove();
		DAValBufferMoveCouter_int_Planner = (DAValBufferMoveCouter_int_Planner + 1) % DA_VAL_BUFF_SIZE;
		DAValBufferLen_int_Planner--;
	}
}
